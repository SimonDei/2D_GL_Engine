//
// Created by a00007 on 09.12.2020.
//

#include "tga_loader.h"

#include <stdlib.h>
#include <stdio.h>

XD_BOOL load_tga_file(XD_STRING filename,
                      PTR(XD_TGAFILE) tga_file) {
    FILE* filePtr;
    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;

    // Open the TGA file.
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        return FALSE;
    }

    // Read the two first bytes we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Which type of image gets stored in imageTypeCode.
    fread(&tga_file->imageTypeCode, sizeof(unsigned char), 1, filePtr);

    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (tga_file->imageTypeCode != 2 && tga_file->imageTypeCode != 3) {
        fclose(filePtr);
        return FALSE;
    }

    // Read 13 bytes of data we don't need.
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);

    // Read the image's width and height.
    fread(&tga_file->imageWidth, sizeof(short int), 1, filePtr);
    fread(&tga_file->imageHeight, sizeof(short int), 1, filePtr);

    // Read the bit depth.
    fread(&tga_file->bitCount, sizeof(unsigned char), 1, filePtr);

    // Read one byte of data we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Color mode -> 3 = BGR, 4 = BGRA.
    colorMode = tga_file->bitCount / 8;
    imageSize = tga_file->imageWidth * tga_file->imageHeight * colorMode;

    // Allocate memory for the image data.
    tga_file->imageData = (unsigned char*) malloc(sizeof(unsigned char) * imageSize);

    // Read the image data.
    fread(tga_file->imageData, sizeof(unsigned char), imageSize, filePtr);

    // Change from BGR to RGB so OpenGL can read the image data.
    for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode) {
        colorSwap = tga_file->imageData[imageIdx];
        tga_file->imageData[imageIdx] = tga_file->imageData[imageIdx + 2];
        tga_file->imageData[imageIdx + 2] = colorSwap;
    }

    fclose(filePtr);
    return TRUE;
}
