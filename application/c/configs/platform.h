// platform.h: 
//
//////////////////////////////////////////////////////////////////////

#ifndef _PLATFORM_H_
#define _PLATFORM_H_


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
//	basic types definition
#if !defined(NO_BASIC_TYPES)

#ifndef BOOL
typedef int                 BOOL;
typedef unsigned char       U8;
typedef char                I8;
typedef unsigned short      U16;
typedef short               I16;
typedef unsigned int        U32;
typedef int                 I32;
typedef unsigned long long  U64;
typedef long long           I64;
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#endif //!defined(NO_BASIC_TYPES)

////////////////////////////////////////////////////////////////////////////////
//	platform types definition

#if defined(WIN32)   
#else
#define strcmpi  strcasecmp
#endif

#if !defined(NO_PLATFORM_TYPES)

typedef void*           LPVOID;
typedef void*           PVOID;
typedef long            LONG;
typedef unsigned long   DWORD;
typedef DWORD*          PDWORD;
typedef DWORD*          LPDWORD;
typedef unsigned short  WORD;
typedef WORD*           PWORD;
typedef WORD*           LPWORD;
typedef U8              BYTE;
typedef U8              UCHAR;
typedef U8*             LPBYTE;
typedef U8*             PUCHAR;
typedef I8*             LPSTR;

#endif //!defined(NO_PLATFORM_TYPES)
////////////////////////////////////////////////////////////////////////////////
//	OS wrappers

BOOL OSSleep(U32 nMS);

U32	OSRandom(U32 range = 0);


typedef long TOSProcessID;

TOSProcessID OSDaemonize(BOOL close_io);	//return process_id in the parent process, 0 in the child daemon, -1 for fail
//TOSProcessID OSExecCmd(const char *cmd, 
//	BOOL wait_term = FALSE, int *status = NULL);	//return process_id in the parent process, no return in the child process, -1 for fail
int OSSystemCmd(const char *cmd);

typedef void (*FOnSignal)(int sig);
void OSSetSignalHandler(int sig, FOnSignal fOnSignal);


const char* OSGetEnv(const char *name);
BOOL OSSetEnv(const char *name, const char *value);
BOOL OSRemoveEnv(const char *name);


typedef int TOSFileHandle;
#define INVALID_FILE_HANDLE -1

TOSFileHandle OSGetStdInput();
TOSFileHandle OSGetStdOutput();

int OSReadFile(TOSFileHandle file, void *buff, int len);
int OSReadFileLine(TOSFileHandle file, void *buff, int len);
int OSWriteFile(TOSFileHandle file, const void *buff, int len);

int OSReadFileDatagram(TOSFileHandle file, void *buff, int len);
int OSWriteFileDatagram(TOSFileHandle file, const void *buff, int len);

TOSFileHandle OSDuplicateFile(TOSFileHandle file);
BOOL OSCloseFile(TOSFileHandle file);




#ifdef __cplusplus
}

////////////////////////////////////////////////////////////////////////////////
//	C++ STL includings

#if defined(WIN32)
#pragma warning(disable: 4786)
#endif //defined(WIN32)

#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>


#include <fstream>
#include <iostream>

using namespace std;


//#include "util_mk_map.h"

#define LIST_ITERATOR_TYPE(type) _List_iterator<type>


////////////////////////////////////////////////////////////////////////////////
//	utility functions & classes



#endif //__cplusplus


#endif // _PLATFORM_H_


