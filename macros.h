//
// Created by a00007 on 09.12.2020.
//

#ifndef UNTITLED_MACROS_H
#define UNTITLED_MACROS_H

#ifndef CLEAR_MEMORY
    #define CLEAR_MEMORY(x) (memset((x), 0, sizeof(*(x))))
#endif

#ifndef XD_FAILED
    #define XD_FAILED(x) ((XD_RESULT)(x) > 0x00)
#endif

#ifndef XD_SUCCEEDED
    #define XD_SUCCEEDED(x) ((XD_RESULT)(x) == 0x00)
#endif

#ifndef PTR
    #define PTR(x) x*
#endif

#ifndef CONST_PTR
    #define CONST_PTR(x) const x*
#endif

#ifndef FORWARD_TYPEDEF
    #define FORWARD_TYPEDEF(s, x) typedef struct s x;
#endif

#ifndef EXPORT
    #define EXPORT __declspec(dllexport)
#endif

#ifndef NO_ARGUMENTS
    #define NO_ARGUMENTS XD_VOID
#endif

#ifndef _In_
    #define _In_
#endif

#ifndef _Out_
    #define _Out_
#endif

#endif //UNTITLED_MACROS_H
