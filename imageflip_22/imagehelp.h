#ifndef __IMAGEHELP_H__
#define __IMAGEHELP_H__

#include <stdio.h>

typedef unsigned int uint;

#define MISSING_CMDLINE_ARG1 0b1
#define MISSING_CMDLINE_ARG2 0b10
#define INPUT_FILE_ERROR 4
#define OUTPUT_FILE_ERROR 8
#define INVALID_BMP_FILE 16

#define HEADER_SIZE 54
#define DATAOFFSET_OFFSET 0xA
#define WIDTH_OFFSET 0x12
#define HEIGHT_OFFSET 0x16
#define BITS_PER_PX_OFFSET 0x1C

typedef struct {
    uint dataOffset; // Offset of the image data (used to skip over the color table)
    uint pxWidth;    // Width of the image in pixels
    uint pxHeight;   // Height of the image in pixels
    uint bitDepth;  // Number of bits used to represent a single pixel
    uint byteWidth; // Width is padded to align to a 4-byte boundary
} ImageInfo;

FILE *openFileForReading(const char *filename);

FILE *openFileForWriting(const char *filename);

uint readBytesFromFile(FILE *fp, uint byteCount, char *buffer);

uint writeBytesToFile(FILE *fp, uint byteCount, char *buffer);

ImageInfo extractDataFromHeader(const char *header);

void swapBytes(char *left, char *right, uint count);

#endif