#include <stdint.h>
#include "typedef.h"
#include "clib.h"

int memset(void *mem, uint8_t val, uint32_t sz)
{
    uint8_t *p = (uint8_t *)mem;
    int i = 0;

    for (i = 0; i < sz; i++, *p++ = val) ;

    return 0;
}

int memcpy(void *dst, const void *src, uint32_t sz)
{
    uint8_t *p_dst = (uint8_t *)dst;
    uint8_t *p_src = (uint8_t *)src;
    int i = 0;

    for (i = 0; i < sz; i++, *p_dst++ = *p_src++) ;

    return 0;
}

int memcmp(void *mem1, void *mem2, uint32_t sz)
{
    uint8_t *p_mem1 = (uint8_t *)mem1;
    uint8_t *p_mem2 = (uint8_t *)mem2;
    int i = 0;

    for (i = 0; i < sz; i++, p_mem1++, p_mem2++) {
        if (*p_mem1 != *p_mem2) {
            break;
        }
    }

    if (i < sz) {
        return 1;
    } else {
        return 0;
    }
}

int strcmp(char *str1, char *str2)
{
    char *p1 = str1, *p2 = str2;

    while ((*p1 != 0) && (*p2 != 0) && (*p1 == *p2)) {
        p1++;
        p2++;
    }

    return *p1 - *p2;
}

int strncmp(char *str1, char *str2, uint32_t sz)
{
    char *p1 = str1, *p2 = str2;
    int i = 0;

    for (; i < sz; i++, p1++, p2++) {
        if (*p1 > *p2) {
            return 1;
        }
        if (*p1 < *p2) {
            return -1;
        }
    }

    return 0;
}

int strtoul(char *str, uint32_t *val)
{
    char *p = str;
    uint32_t multiplier = 10;
    uint32_t result = 0, num = 0;

    if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X')) {
        p += 2;
        multiplier = 0x10;
    }

    while (0 != *p) {
        if (multiplier == 0x10) {
            if (!is_hex_asc(*p)) {
                return -1;
            }
            if (*p >= '0' && *p <= '9') {
                num = *p - '0';
            } else if (*p >= 'a' && *p <= 'f') {
                num = *p - 'a' + 10;
            } else {
                num = *p - 'A' + 10;
            }
        } else {
            if (!is_dec_asc(*p)) {
                return -2;
            }

            num = *p - '0';
        }

        result = result * multiplier + num;

        p++;
    }

    *val = result;

    return 0;
}

int strtol(char *str, int *val)
{
    char *p = str;
    int ret;

    if (*p == '-') {
        ret = strtoul(++p, (uint32_t *)val);
        *val = -(*val);
        return ret;
    } else
        return strtoul(p, (uint32_t *)val);

}

uint32_t strlen(char *str)
{
    char *p = str;

    while (*p++ != '\0') ;

    return (uint32_t)(p - str);
}

int strcpy(char *dst, char *src)
{
    char *p_dst = dst, *p_src = src;

    while (*p_src != '\0') {
        *p_dst = *p_src;
        p_dst++;
        p_src++;
    }
    *p_dst = '\0';

    return 0;
}

char *strrchr(const char *t, int c) 
{
	register char ch;
	register const char *l=0;

	ch = c;
	for (;;) 
	{
		if (*t == ch) l=t; 
		if (!*t) return (char*)l; 
		++t;
	}
	
	return (char*)l;
}


char *strncpy(char *dst, const char *src, rt_ubase_t n)
{
    if (n != 0)
    {
        char *d = dst;
        const char *s = src;

        do
        {
            if ((*d++ = *s++) == 0)
            {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0)
                    *d++ = 0;
                break;
            }
        } while (--n != 0);
    }

    return (dst);
}

int atoi(const char* s)
{
	long int v=0;
	int sign=1;
	while ( *s == ' '  ||  (unsigned int)(*s - 9) < 5u) s++;

	switch (*s)
	{
	case '-': sign=-1;
	case '+': ++s;
	}

	while ((unsigned int) (*s - '0') < 10u)
	{
		v=v*10+*s-'0'; ++s;
	}

	return sign==-1?-v:v;
}