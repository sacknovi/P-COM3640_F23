#include "imagehelp.h"
#include <string.h>
#include <malloc.h>

/***************************************************

****************************************************/

int main(int argc, char **argv) {
    if (argc == 1) {
        // print to the stderr
        printf("Missing input file name argument\n");
        //return MISSING_CMDLINE_ARG1 | MISSING_CMDLINE_ARG2;
    }
    if (argc == 2) {
        printf("Missing image output file name argument\n");
        //return MISSING_CMDLINE_ARG2;
    }

    const char* filename = "C:\\temp\\snail-16.bmp";
    const char* outfname = "out.bmp";

    FILE *fIn, *fOut;

    // check if the input file has been opened succesfully.
    if (!(fIn = openFileForReading(filename))) {
        printf("Could not open input file: %s\n", filename);
        return INPUT_FILE_ERROR;
    }

    // check if the output file has been opened succesfully.
    if (!(fOut = openFileForWriting(outfname))) {
        printf("Could not open output file for writing: %s\n", outfname);
        return OUTPUT_FILE_ERROR;
    }

    char header[HEADER_SIZE];

    if (readBytesFromFile(fIn, HEADER_SIZE, header) < HEADER_SIZE) {
        printf("File is not a valid BMP file\n");
        return INVALID_BMP_FILE;
    }

    char signature[3] = {header[0], header[1], '\0'};
    if (strcmp(signature, "BM")) {
        printf("File is not a valid BMP file\n");
        return INVALID_BMP_FILE;
    }

    writeBytesToFile(fOut, HEADER_SIZE, header);

    // extract image height, width and bitDepth from imageHeader
    ImageInfo info = extractDataFromHeader(header);

    // Print image information
    printf("px width: %d\n", info.pxWidth);
    printf("px height: %d\n", info.pxHeight);
    printf("bitDepth: %d\n", info.bitDepth);
    printf("byte width: %d\n", info.byteWidth);
    printf("data offset: 0x%x", info.dataOffset);

    // Read and write until the image data begins.
    // For images with a bit depth of 8 or less, the color table is embedded in the file.

    unsigned color_table_size = info.dataOffset - HEADER_SIZE;
    if (color_table_size) {
        char table[color_table_size];
        readBytesFromFile(fIn, color_table_size, table);
        writeBytesToFile(fOut, color_table_size, table);
    }

    /*******************************
     Processing Image Data
    ********************************/

    unsigned int bytesPerPixel = info.bitDepth / 8;

    char* buffer = (char*)malloc(info.byteWidth*info.pxHeight);
    readBytesFromFile(fIn,info.byteWidth*info.pxHeight, buffer);

    // Iterate over all the rows
    for (int i = 0; i < info.pxHeight; i++) {
        int rowoff = i * info.byteWidth;

        // Iterate over the row pixels/bytes until the halfway point
        for (int j = 0; j < info.pxWidth / 2; j++) {
            uint lidx = j * bytesPerPixel;
            uint ridx = (info.pxWidth - j - 1) * bytesPerPixel;
            swapBytes(buffer+rowoff+lidx, buffer+rowoff+ridx, bytesPerPixel);
        }
    }

    for (int i=0; i < info.byteWidth; i++) {
        for (int j = 0; j < info.pxHeight / 2; j++) {
            uint tidx = j * info.byteWidth;
            uint bidx = (info.pxHeight-j-1) * info.byteWidth;
            swapBytes(buffer+tidx+i, buffer+bidx+i, 1);
        }
    }
    writeBytesToFile(fOut,info.byteWidth*info.pxHeight, buffer);

    free(buffer);
    // Close file pointers
    fclose(fIn);
    fclose(fOut);

    return 0;
}

