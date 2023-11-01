#include "imagehelp.h"
#include <math.h>

FILE *openFileForReading(const char *filename) {
    return fopen(filename, "rb");
}

FILE *openFileForWriting(const char *filename) {
    return fopen(filename, "wb");
}

uint readBytesFromFile(FILE *fp, uint byteCount, char *buffer) {
    return fread(buffer, sizeof(char), byteCount, fp);
}

uint writeBytesToFile(FILE *fp, uint byteCount, char *buffer) {
    return fwrite(buffer, sizeof(char), byteCount, fp);
}

ImageInfo extractDataFromHeader(const char *header) {
    ImageInfo info;
    info.dataOffset = *(uint *) &header[DATAOFFSET_OFFSET];
    info.pxWidth = *(uint *) &header[WIDTH_OFFSET];
    info.pxHeight = *(uint *) &header[HEIGHT_OFFSET];
    info.bitDepth = *(unsigned short*) &header[BITS_PER_PX_OFFSET];

    double bytes = info.pxWidth * info.bitDepth / 8.0;
    info.byteWidth = ceil(bytes / 4.0) * 4;

    return info;
}

void swapBytes(char *left, char *right, uint count) {
    for (int i = 0; i < count; i++) {
        char temp = *(left + i);
        *(left + i) = *(right + i);
        *(right + i) = temp;
    }
}
