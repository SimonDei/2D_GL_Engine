//
// Created by a00007 on 09.12.2020.
//

#ifndef UNTITLED_TGA_LOADER_H
#define UNTITLED_TGA_LOADER_H

#include "macros.h"
#include "types.h"

typedef struct _TGAFILE {
    unsigned char imageTypeCode;
    short int imageWidth;
    short int imageHeight;
    unsigned char bitCount;
    unsigned char* imageData;
} XD_TGAFILE;

EXPORT XD_BOOL load_tga_file(
    _In_ XD_STRING filename,
    _Out_ PTR(XD_TGAFILE) tga_file);

#endif //UNTITLED_TGA_LOADER_H
