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

typedef char           XD_INT8;
typedef short          XD_INT16;
typedef int            XD_INT32;
typedef int_least64_t  XD_INT64;
typedef long           XD_LONG;
typedef long long      XD_LONGLONG;

typedef unsigned char  XD_UINT8;
typedef unsigned short XD_UINT16;
typedef unsigned int   XD_UINT32;
typedef uint_least64_t XD_UINT64;

typedef unsigned char  XD_BYTE;

typedef uint_least16_t XD_WORD;
typedef uint_least32_t XD_DWORD;

typedef float          XD_FLOAT;
typedef double         XD_DOUBLE;
typedef XD_FLOAT*      XD_LPFLOAT;
typedef XD_DOUBLE*     XD_LPDOUBLE;

typedef char           XD_CHAR;
typedef unsigned char  XD_UCHAR;
typedef XD_CHAR*       XD_LPCHAR;
typedef XD_UCHAR*      XD_LPUCHAR;

typedef const XD_CHAR* XD_STRING;

typedef _Bool          XD_BOOL;
typedef XD_BOOL*       XD_LPBOOL;

typedef void           XD_VOID;
typedef XD_VOID*       XD_LPVOID;

typedef XD_UINT32      XD_TEXTURE;
typedef XD_TEXTURE*    XD_LPTEXTURE;

typedef XD_FLOAT       XD_MATRIX4[4][4];

#endif //UNTITLED_TYPES_H
