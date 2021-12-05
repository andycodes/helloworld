#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "SMM_MPS3.h"
#include "core_cm55.h"

void system_init(void)
{
    unsigned int core_clock = MPS3_SCC->CFG_ACLK;
    if(core_clock != 0)
        SystemCoreClockUpdate();
        
    UartStdOutInit();
}
///////////////////////////////////////
#include "common.h"


// Return status
typedef enum sts
{
    TEST_S_UNKNOWN,
    TEST_S_NOTRUN,
    TEST_S_SUCCESS,
    TEST_S_FAILURE,
    MAX_STATUS
} Status_t;

char    *status_str[MAX_STATUS];

typedef struct test
{
    apError     (*test)(void);
    int         auto_run;
    char        *name;
}Test_t;

apError apQSPI_TEST()
{
    printk("hello apQSPI_TEST OK\n");
    return apERR_NONE;
}

// Table of available tests
static Test_t tests[] =
{
    {&apQSPI_TEST,          0,  "QSPI                   "}
};
#define NO_OF_TESTS (sizeof(tests) / sizeof(tests[0]))
Status_t test_status[NO_OF_TESTS];

// Initialisation routines
void Test_Init (void)
{
    int i;

    // Init test status and status strings.
    for (i = 0; i < MAX_STATUS; i++)
        status_str[i]  = "Unknown";

    status_str[TEST_S_NOTRUN]  = "Not Run";
    status_str[TEST_S_SUCCESS] = "PASS";
    status_str[TEST_S_FAILURE] = "FAIL";

    for (i = 0; i < NO_OF_TESTS; i++)
        test_status[i] = TEST_S_NOTRUN;
}

int Select_Test (void)
{
    return 0;
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

   // test--;
    printk ("\nTesting %s\n", tests[test].name);

    status = (*tests[test].test)();

    if (status == apERR_NONE)
        test_status[test] = TEST_S_SUCCESS;
    else
        test_status[test] = TEST_S_FAILURE;

    printk ("%s    : test result : %s\n\n", tests[test].name, Get_Status (test_status[test]));
}


void Print_Results (void)
{
    int i;
    int counts[MAX_STATUS];

    for (i = 0; i < MAX_STATUS; i++)
        counts[i] = 0;

        printk ("Summary of results\n");
        printk ("====================================\n");

    for (i = 0; i < NO_OF_TESTS; i++) {
        printk ("%2d : %-20s : %s\n",(i+1), tests[i].name, Get_Status (test_status[i]));

        if (test_status[i] < MAX_STATUS)
            counts[test_status[i]]++;
    }
    printk("11 : Run All Tests\n");
}



void Run_All_Tests (void)
{
    for (int i = 0; i < NO_OF_TESTS; i++) {
        Run_Test(i + 1);
    }

    Print_Results();
}

void test(void)
{
    int choice;

    Test_Init();

    //NVIC_ClearAllPendingIRQ();
    NVIC->ICPR[0] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[1] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[2] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[3] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[4] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[5] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[6] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[7] = 0xFFFFFFFF;         /* Clear all pending interrupts */

    choice = Select_Test();
     if (choice == NO_OF_TESTS + 1) {
         Run_All_Tests();
     } else {
         Run_Test(choice);
     }
}

void test_result_info(void)
{
    Print_Results();
}

void main(void)
{
    system_init();
    printk("hello %s ^-^^-^^-^^-^\n", get_boardinfo());
    test();

    while (1){
        printk("hello %s\n", get_boardinfo());
        test_result_info();
    };
}
