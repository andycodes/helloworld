#ifndef  _C_TYPE_H
#define  _C_TYPE_H

#define __inline  inline

#define __align(x)    __attribute__ ((aligned (x)))

typedef unsigned char BYTE;
typedef unsigned char       u8;
typedef unsigned char       U8;
typedef char                I8;
typedef signed char         s8;
typedef unsigned short      U16;
typedef short signed int    s16;
typedef short unsigned int  u16;
typedef short               I16;
typedef signed int          s32;

typedef unsigned int        u32;
typedef unsigned int        U32;
typedef unsigned int        uint32_t;

typedef int                 I32;
typedef unsigned long long  U64;
typedef long long           I64;

#ifndef BOOL
typedef int BOOL;
#endif

typedef int bool;

#ifndef __cdecl
#define __cdecl
#endif

#define	TRUE  	1
#define	true	1
#define 	FALSE	0
#define	false	0
#ifndef   NULL
#define	NULL	0
#endif
#define	__WEAK

enum FLAG
{
    ERROR = -1,
    OK    =  0
}FLAG;

#endif
