#ifndef __CLIB_H__
#define __CLIB_H__

#include "typedef.h"

int is_dec_asc(char ch);
int is_hex_asc(char ch);
int memset(void *mem, uint8_t val, uint32_t sz);
int memcpy(void *dst, const void *src, uint32_t sz);
int memcmp(void *mem1, void *mem2, uint32_t sz);
int strcmp(char *str1, char *str2);
int strncmp(char *str1, char *str2, uint32_t sz);
int strtoul(char *str, uint32_t *val);
int strtol(char *str, int *val);
uint32_t strlen(char *str);
int strcpy(char *dst, char *src);

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