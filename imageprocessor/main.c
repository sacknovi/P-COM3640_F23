#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "typedef.h"

int read_img_operation(int argc, char *argv[], img_operation_t *img_operation);
int read_bmpheader(bmpheader_t *bmpheader);
void extract_image_info(const bmpheader_t *bmpheader, imageinfo_t *imageinfo);
void print_image_info(const imageinfo_t *imageinfo);
void output_header(img_operation_t img_operation, const bmpheader_t *bmpheader, const imageinfo_t *imageinfo);
int process_hflip(const imageinfo_t *imageinfo);
int process_vflip(const imageinfo_t *imageinfo);
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
    {
        fprintf(stderr, "Invalid operation specified on the command line\n");
        return 1;
    }

    bmpheader_t bmpheader;
    if (!read_bmpheader(&bmpheader))
    {
        fprintf(stderr, "Invalid BMP header\n");
        return 1;
    }

    imageinfo_t imageinfo;
    extract_image_info(&bmpheader, &imageinfo);

    if (img_operation == INFO)
    {
        print_image_info(&imageinfo);
    }
    else
    {
        output_header(img_operation, &bmpheader, &imageinfo);

        if (img_operation == HFLIP)
        {
            if (!process_hflip(&imageinfo))
            {
                fprintf(stderr, "Error processing image\n");
                return 1;
            }
        }
        else if (img_operation == VFLIP)
        {
            if (!process_vflip(&imageinfo))
            {
                fprintf(stderr, "Error processing image\n");
                return 1;
            }
        }
        else if (img_operation == GRAYSCALE)
        {

            // Your regular code here
        }
    }

    fprintf(stdout, "Performing operation: %d\n", img_operation);

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

    else
        return 0;
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

    if (imageinfo->dataOffset > sizeof(bmpheader_t))
    {
        char buffer[imageinfo->dataOffset - sizeof(bmpheader_t)];
        fread(buffer, sizeof(buffer), 1, stdin);
        fwrite(buffer, sizeof(buffer), 1, stdout);
    }
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

void swapBytes(char *left, char *right, uint count)
{
    for (int i = 0; i < count; i++)
    {
        char temp = *(left + i);
        *(left + i) = *(right + i);
        *(right + i) = temp;
    }
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
