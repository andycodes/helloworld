#ifndef __CLIB_H__
#define __CLIB_H__

#include "typedef.h"

extern int memset(void *mem, uint8_t val, uint32_t sz);
extern int memcpy(void *dst, const void *src, uint32_t sz);
extern int memcmp(void *mem1, void *mem2, uint32_t sz);
extern int strcmp(char *str1, char *str2);
extern int strncmp(char *str1, char *str2, uint32_t sz);
extern int strtoul(char *str, uint32_t *val);
extern int strtol(char *str, int *val);
extern uint32_t strlen(char *str);
extern int strcpy(char *dst, char *src);

char *strncpy(char *dst, const char *src, rt_ubase_t n);
char *strrchr(const char *t, int c);
int atoi(const char* s);

#define rt_memset memset
#define rt_memcpy memcpy
#define rt_memcmp memcmp
#define rt_strcmp strcmp
#define rt_strncmp strncmp
#define rt_strlen strlen
#define rt_strncpy strncpy

#endif /*__CLIB_H__*/