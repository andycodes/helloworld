#ifndef __BASE__TYPE__H__
#define __BASE__TYPE__H__

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

#ifndef NULL
#define NULL                         (0)
#endif

extern void no_printk(const char *fmt, ...);
extern void printk(const char *fmt, ...);

#define NEED_DEBUG
#ifdef NEED_DEBUG
#define DEBUG printk
#define LOG_D printk
#define LOG_I printk
#define LOG_W printk
#define LOG_E printk
#define rt_kprintf printk
#else
#define DEBUG no_printk
#endif /*DEBUG*/

#endif /*__BASE__TYPE__H__*/
