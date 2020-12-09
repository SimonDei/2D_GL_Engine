//
// Created by a00007 on 09.12.2020.
//

#ifndef UNTITLED_TYPES_H
#define UNTITLED_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifndef NULL
    #define NULL ((void*)0)
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

typedef unsigned char  XD_UINT8;
typedef unsigned short XD_UINT16;
typedef unsigned int   XD_UINT32;

typedef float          XD_FLOAT;
typedef double         XD_DOUBLE;

typedef _Bool          XD_BOOL;

typedef const char*    XD_STRING;

typedef void           XD_VOID;

typedef XD_UINT32      XD_TEXTURE;

#endif //UNTITLED_TYPES_H
