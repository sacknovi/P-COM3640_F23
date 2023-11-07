#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "typedef.h"

int error(int error_code, const char *error_message);
int read_img_operation(int argc, char *argv[], img_operation_t *img_operation);
int read_bmpheader(bmpheader_t *bmpheader);
void extract_image_info(const bmpheader_t *bmpheader, imageinfo_t *imageinfo);
void print_image_info(const imageinfo_t *imageinfo);
void output_header(img_operation_t img_operation, const bmpheader_t *bmpheader, const imageinfo_t *imageinfo);
uchar rgb_to_gray(pixel_t *pixel);
void process_color_table(img_operation_t operation, imageinfo_t *imageinfo);
int process_hflip(const imageinfo_t *imageinfo);
int process_vflip(const imageinfo_t *imageinfo);
int process_grayscale(const imageinfo_t *imageinfo);
void swapBytes(char *left, char *right, uint count);

int main(int argc, char *argv[])
{
#ifdef DEBUG
    FILE *file = fopen("images/snow_32A.bmp", "rb");
    if (file)
    {
        // Replace stdin with file for this debug session
        stdin = file;
    }
#endif

    img_operation_t img_operation;
    if (!read_img_operation(argc, argv, &img_operation))
        return error(1, "Invalid operation specified on the command line\n");

    bmpheader_t bmpheader;
    if (!read_bmpheader(&bmpheader))
        return error(1, "Invalid BMP header\n");

    imageinfo_t imageinfo;
    extract_image_info(&bmpheader, &imageinfo);

    if (img_operation == INFO)
        print_image_info(&imageinfo);
    else if (img_operation == RGB & !process_rgb(&imageinfo))
        return error(1, "Error processing image\n");
    else
    {
        output_header(img_operation, &bmpheader, &imageinfo);

        process_color_table(img_operation, &imageinfo);

        if (img_operation == HFLIP && !process_hflip(&imageinfo))
            return error(1, "Error processing image\n");

        else if (img_operation == VFLIP && !process_vflip(&imageinfo))
            return error(1, "Error processing image\n");

        else if (img_operation == GRAYSCALE & !process_grayscale(&imageinfo))
            return error(1, "Error processing image\n");
    }

#ifdef DEBUG
    if (file)
        fclose(file);
#endif

    return 0;
}

int read_img_operation(int argc, char *argv[], img_operation_t *img_operation)
{
    if (argc < 2)
        return 0;

    else if (STRING_COMPARE(argv[1], "HFLIP") == 0)
        *img_operation = HFLIP;

    else if (STRING_COMPARE(argv[1], "VFLIP") == 0)
        *img_operation = VFLIP;

    else if (STRING_COMPARE(argv[1], "GRAYSCALE") == 0)
        *img_operation = GRAYSCALE;

    else if (STRING_COMPARE(argv[1], "INFO") == 0)
        *img_operation = INFO;

    else if (STRING_COMPARE(argv[1], "RGB") == 0)
        *img_operation = RGB;

    else
        return 0;
}

int error(int error_code, const char *error_message)
{
    fprintf(stderr, "%s", error_message);
    return error_code;
}

int read_bmpheader(bmpheader_t *bmpheader)
{
    // read the bmp header data
    if (!fread(bmpheader, sizeof(bmpheader_t), 1, stdin))
        return 0;

    // check if the file is a bmp file
    if ((*bmpheader)[0] != 'B' || (*bmpheader)[1] != 'M')
        return 0;

    return 1;
}

void extract_image_info(const bmpheader_t *bmpheader, imageinfo_t *imageinfo)
{
    imageinfo->dataOffset = *(uint *)&(*bmpheader)[DATAOFFSET_OFFSET];
    imageinfo->pxWidth = *(uint *)&(*bmpheader)[WIDTH_OFFSET];
    imageinfo->pxHeight = *(uint *)&(*bmpheader)[HEIGHT_OFFSET];
    imageinfo->bitDepth = *(ushort *)&(*bmpheader)[BITS_PER_PX_OFFSET];

    double bytes = imageinfo->pxWidth * imageinfo->bitDepth / 8.0;
    imageinfo->byteWidth = ceil(bytes / 4.0) * 4;
}

void print_image_info(const imageinfo_t *imageinfo)
{
    fprintf(stdout, "Pixel Width: %u\n", imageinfo->pxWidth);
    fprintf(stdout, "Pixel Height: %u\n", imageinfo->pxHeight);
    fprintf(stdout, "Bit depth: %u\n", imageinfo->bitDepth);
    fprintf(stdout, "Row width (bytes): %u\n", imageinfo->byteWidth);
    fprintf(stdout, "Bytes per pixel: %u\n", imageinfo->bitDepth / 8);
    fprintf(stdout, "Data offset: %u\n", imageinfo->dataOffset);
}

void output_header(img_operation_t img_operation, const bmpheader_t *bmpheader, const imageinfo_t *imageinfo)
{
    fwrite(bmpheader, sizeof(bmpheader_t), 1, stdout);
}

void process_color_table(img_operation_t operation, imageinfo_t *imageinfo)
{
    int totalBytes = imageinfo->dataOffset - sizeof(bmpheader_t);
    if (totalBytes == 0)
        return;

    // read the color table from stdin
    uchar buffer[totalBytes];
    fread(buffer, sizeof(buffer), 1, stdin);

    // for 8-bit images, for GRAYSCALE operation only
    // convert color table to grayscale
    if (operation == GRAYSCALE && imageinfo->bitDepth == 8)
    {
        for (int i = 0; i < totalBytes; i += 4)
        {
            uchar gray = rgb_to_gray((pixel_t*)&buffer[i]);
            buffer[i] = gray;
            buffer[i + 1] = gray;
            buffer[i + 2] = gray;
        }
    }

    // write the color table to stdout
    fwrite(buffer, sizeof(buffer), 1, stdout);
}

uchar rgb_to_gray(pixel_t *pixel)
{
    return 0.299 * pixel->depth24.red + 0.587 * pixel->depth24.green + 0.114 * pixel->depth24.blue;
}


int process_hflip(const imageinfo_t *imageinfo)
{
    int bytesPerPixel = imageinfo->bitDepth / 8;
    char buffer[imageinfo->byteWidth];

    for (int row = 0; row < imageinfo->pxHeight; row++)
    {
        if (!fread(buffer, sizeof(buffer), 1, stdin))
            return 0;

        for (int col = 0; col < imageinfo->pxWidth / 2; col++)
        {
            uint left = col * bytesPerPixel;
            uint right = (imageinfo->pxWidth - col - 1) * bytesPerPixel;
            swapBytes(&buffer[left], &buffer[right], bytesPerPixel);
        }

        fwrite(buffer, sizeof(buffer), 1, stdout);
    }

    return 1;
}

int process_vflip(const imageinfo_t *imageinfo)
{
    int totalBytes = imageinfo->byteWidth * imageinfo->pxHeight;
    char *buffer = (char *)malloc(totalBytes);

    if (!fread(buffer, sizeof(char), totalBytes, stdin))
    {
        free(buffer);
        return 0;
    }

    for (int col = 0; col < imageinfo->byteWidth; col++)
    {
        for (int row = 0; row < imageinfo->pxHeight / 2; row++)
        {
            uint top = row * imageinfo->byteWidth + col;
            uint bottom = (imageinfo->pxHeight - row - 1) * imageinfo->byteWidth + col;
            swapBytes(&buffer[top], &buffer[bottom], 1);
        }
    }

    fwrite(buffer, sizeof(char), totalBytes, stdout);
    free(buffer);
    return 1;
}

int process_grayscale(const imageinfo_t *imageinfo)
{
    int bytesPerPixel = imageinfo->bitDepth / 8;
    char buffer[imageinfo->byteWidth];

    for (int row = 0; row < imageinfo->pxHeight; row++)
    {
        if (!fread(buffer, sizeof(buffer), 1, stdin))
            return 0;

        for (int col = 0; col < imageinfo->pxWidth; col++)
        {
            uint offset = col * bytesPerPixel;
            uint gray = rgb_to_gray((pixel_t*)&buffer[offset]);
            buffer[offset] = gray;
            buffer[offset + 1] = gray;
            buffer[offset + 2] = gray;
        }

        fwrite(buffer, sizeof(buffer), 1, stdout);
    }

    return 1;
}

void swapBytes(char *left, char *right, uint count)
{
    for (int i = 0; i < count; i++)
    {
        char temp = *(left + i);
        *(left + i) = *(right + i);
        *(right + i) = temp;
    }
}
