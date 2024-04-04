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

#endif /*__CLIB_H__*/