/* mcut.h: Minimalist C Unit Test framework */
#ifndef __MCUT_H
#define __MCUT_H

#include <stdlib.h>
#include <stdio.h>

static int __MCUT_RAN = 0;
static int __MCUT_FAILED = 0;

#define mcut_assert_msg(expr, ...) \
do { \
    __MCUT_RAN++; \
    if (!(expr)) { \
        printf("%s(%d): ", __func__, __LINE__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
        __MCUT_FAILED++; \
    } \
} while (0)

#define mcut_assert(expr) \
    mcut_assert_msg(expr, "Assertion '"#expr"' failed")

/* O may be any comparion operator. */
#define mcut_assert_int(X, O, Y) \
    mcut_assert_msg((X) O (Y), \
                    "Assertion '"#X#O#Y"' failed: "#X"==%d, "#Y"==%d", X, Y)

#define mcut_run_test(test_case) test_case()

#define mcut_show_statistics() \
do { \
    float passed = 0; \
    if (__MCUT_RAN != 0) { \
        passed = (__MCUT_RAN - __MCUT_FAILED) * 100.00 / __MCUT_RAN; \
    } \
    printf("\n---------- Run Summary ----------\n"); \
    printf("Passed: %.2f%%, Ran: %d, Failed: %d\n", \
           passed, __MCUT_RAN, __MCUT_FAILED); \
    if (__MCUT_FAILED) return 1; \
} while (0)

#endif
