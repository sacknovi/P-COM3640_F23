#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <string.h>
#define STRING_COMPARE(str1, str2) stricmp((str1), (str2))
#else
#include <strings.h>
#define STRING_COMPARE(str1, str2) strcasecmp((str1), (str2))
#endif

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef enum
{
    HFLIP,
    VFLIP,
    GRAYSCALE,
    INFO,
    RGB
} img_operation_t;

#define BMP_HEADER_SIZE 54
#define DATAOFFSET_OFFSET 0xA
#define WIDTH_OFFSET 0x12
#define HEIGHT_OFFSET 0x16
#define BITS_PER_PX_OFFSET 0x1C

typedef char bmpheader_t[BMP_HEADER_SIZE];

typedef struct {
    uint dataOffset; // Offset of the image data (used to skip over the color table)
    uint pxWidth;    // Width of the image in pixels
    uint pxHeight;   // Height of the image in pixels
    uint bitDepth;   // Number of bits used to represent a single pixel
    uint byteWidth;  // Width is padded to align to a 4-byte boundary
} imageinfo_t;

typedef struct {
    uchar value;
} depth8_t;

typedef struct {
    ushort value;
} depth16_t;

typedef struct {
    uchar blue;
    uchar green;
    uchar red;
} depth24_t;

typedef struct {
    uchar blue;
    uchar green;
    uchar red;
    uchar alpha;
} depth32_t;

typedef union {
    depth8_t depth8;
    depth16_t depth16;
    depth24_t depth24;
    depth32_t depth32;
} pixel_t;


