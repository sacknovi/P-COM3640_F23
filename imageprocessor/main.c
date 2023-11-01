#include <stdio.h>
#include <string.h>
#include "typedef.h"

int read_img_operation(int argc, char *argv[], img_operation_t *img_operation);

int main(int argc, char *argv[])
{

    img_operation_t img_operation;
    if (!read_img_operation(argc, argv, &img_operation))
    {
        fprintf(stderr, "Invalid operation specified on the command line\n");
        return 1;
    }

    // TODO: Implement image processing based on img_operation

    return 0;
}

int read_img_operation(int argc, char *argv[], img_operation_t *img_operation)
{
    if (argc < 2)
    {
        return 0;
    }
    else if (stricmp(argv[1], "HFLIP") == 0)
    {
        *img_operation = HFLIP;
    }
    else if (stricmp(argv[1], "VFLIP") == 0)
    {
        *img_operation = VFLIP;
    }
    else if (stricmp(argv[1], "GRAYSCALE") == 0)
    {
        *img_operation = GRAYSCALE;
    }
    else if (stricmp(argv[1], "INFO") == 0)
    {
        *img_operation = INFO;
    }
    else
    {
        return 0;
    }

    return 1;
}
