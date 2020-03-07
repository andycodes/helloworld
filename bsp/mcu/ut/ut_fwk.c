#include <stdlib.h>
#include <stdio.h>
#include "ut_fwk.h"

/* function */
int sub(int a, int b)
{
    return 0;
}

/* test case */
static void test_sub1(void)
{
    mcut_assert(sub(10, 5) == 5);
}

static void test_sub2(void)
{
    mcut_assert_msg(sub(2, 5) == -3, "Error: sub(2, 5) != -3");
}

static void test_sub3(void)
{
    mcut_assert_int(sub(2, 0), ==, 2);
}

static void test_sub4(void)
{
    mcut_assert_int(sub(0, 0), ==, 0);
}
#if 0
/* run test case */
int main(int argc, char *argv[])
{
    mcut_run_test(test_sub1);
    mcut_run_test(test_sub2);
    mcut_run_test(test_sub3);
    mcut_run_test(test_sub4);

    mcut_show_statistics();
    return 0;
}
#endif