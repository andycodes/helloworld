#include "os_stdio.h"
#include "testcase.h"
#include "test_table.h"

#define SIZE_OF_TESTS 1024

char    *status_str[MAX_STATUS];
extern Test_t tests[SIZE_OF_TESTS]; 
Status_t test_status[SIZE_OF_TESTS];

static unsigned int g_testcase_cnt = 0;

Test_t tests[] =
{
   // {&mpu_test,          0,  "mpu write  ", TEST_S_UNKNOWN},
};

unsigned int testcase_register(Test_t *testcase)
{
    if (testcase == NULL)
        return -1;

    if (g_testcase_cnt >= SIZE_OF_TESTS)
        return -2;

    tests[g_testcase_cnt].test = &testcase->test;
    tests[g_testcase_cnt].auto_run = testcase->auto_run;
    tests[g_testcase_cnt].name = testcase->name;
    tests[g_testcase_cnt].status = TEST_S_UNKNOWN;

    g_testcase_cnt++;

    return 0;
}


void Test_Init (void)
{
    int i;

    for (i = 0; i < MAX_STATUS; i++)
        status_str[i]  = "Unknown";

    status_str[TEST_S_NOTRUN]  = "Not Run";
    status_str[TEST_S_SUCCESS] = "PASS";
    status_str[TEST_S_FAILURE] = "FAIL";
}

// User interface
char *Get_Status (Status_t status)
{
    if (status >= MAX_STATUS)
        status = TEST_S_UNKNOWN;

    return status_str[status];
}

void Run_Test (int test)
{
    apError status;

    printk ("\nTesting %s\n", tests[test].name);

    status = (*tests[test].test)();

    if (status == apERR_NONE)
        tests[test].status = TEST_S_SUCCESS;
    else
        tests[test].status = TEST_S_FAILURE;

    printk ("%s    : test result : %s\n\n", tests[test].name, Get_Status (tests[test].status));
}

void Print_Results (void)
{
    int i;
    int counts[MAX_STATUS];

    for (i = 0; i < MAX_STATUS; i++)
        counts[i] = 0;

        printk ("Summary of results\n");
        printk ("====================================\n");

    for (i = 0; i < g_testcase_cnt; i++) {
        printk ("%2d : %-20s : %s\n",(i+1), tests[i].name, Get_Status (tests[i].status));

        if (tests[i].status < MAX_STATUS)
            counts[tests[i].status]++;
    }
    printk("11 : Run All Tests\n");
}

void test_go(void)
{
    for (int i = 0; i < g_testcase_cnt; i++) {
        Run_Test(i);
    }

    Print_Results();
}

void testcase(void)
{
        Test_Init();
        test_go();
        Print_Results();
}
