#ifndef OS_STDIO_H_TMP
#define OS_STDIO_H_TMP

#include <stdint.h>

#define  EOK                          0               /**< There is no error */
#define  ERROR                        1               /**< A generic error happens */
#define  ETIMEOUT                     2               /**< Timed out */
#define  EFULL                        3               /**< The resource is full */
#define  EEMPTY                       4               /**< The resource is empty */
#define  ENOMEM                       5               /**< No memory */
#define  ENOSYS                       6               /**< No system */
#define  EBUSY                        7               /**< Busy */
#define  EIO                          8               /**< IO error */
#define  EINTR                        9               /**< Interrupted system call */
#define  EINVAL                       10              /**< Invalid argument */

#define SECTION(x)                  __attribute__((section(x)))
#define RT_UNUSED                   __attribute__((unused))
#define RT_USED                     __attribute__((used))
#define ALIGN(n)                    __attribute__((aligned(n)))
#define RT_WEAK                     __attribute__((weak))


#define RT_ASSERT(EX)  

/**@}*/

/**
 * @ingroup BasicDef
 *
 * @def RT_ALIGN(size, align)
 * Return the most contiguous size aligned at specified width. RT_ALIGN(13, 4)
 * would return 16.
 */
#define RT_ALIGN(size, align)           (((size) + (align) - 1) & ~((align) - 1))

/**
 * @ingroup BasicDef
 *
 * @def RT_ALIGN_DOWN(size, align)
 * Return the down number of aligned at specified width. RT_ALIGN_DOWN(13, 4)
 * would return 12.
 */
#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))

/**
 * @ingroup BasicDef
 *
 * @def RT_NULL
 * Similar as the \c NULL in C library.
 */
#define RT_NULL                         (0)

extern void printk(const char *fmt, ...);
extern int memset(void *mem, uint8_t val, uint32_t sz);
extern int memcpy(void *dst, const void *src, uint32_t sz);
extern int memcmp(void *mem1, void *mem2, uint32_t sz);
extern int strcmp(char *str1, char *str2);
extern int strncmp(char *str1, char *str2, uint32_t sz);
extern int strtoul(char *str, uint32_t *val);
extern int strtol(char *str, int *val);
extern uint32_t strlen(char *str);
extern int strcpy(char *dst, char *src);
extern void no_printk(const char *fmt, ...);

#define NEED_DEBUG
#ifdef NEED_DEBUG
#define DEBUG printk
#else
#define DEBUG no_printk
#endif /*DEBUG*/

#endif /*OS_STDIO_H_TMP*/
