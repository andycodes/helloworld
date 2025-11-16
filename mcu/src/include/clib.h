#ifndef __CLIB_H__
#define __CLIB_H__

#include "typedef.h"
#include <stddef.h>

int is_dec_asc(char ch);
int is_hex_asc(char ch);
int strcmp(const char *str1, const char *str2);
int strtoul(char *str, uint32_t *val);
int strtol(char *str, int *val);
size_t strlen(const char *str);
char *strrchr(const char *t, int c);
int atoi(const char* s);

#define rt_memset memset
#define rt_memcpy memcpy
#define rt_memcmp memcmp
#define rt_strncmp strncmp
#define rt_strlen strlen
#define rt_strncpy strncpy

#endif /*__CLIB_H__*/