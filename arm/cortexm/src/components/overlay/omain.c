#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"

extern void overlay_function1();
extern void overlay_function2();

extern unsigned int __ovly_table[2][3];


void ovly_table_show(void)
{
    printk("ovly_table_show: \n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printk("0x%x ", __ovly_table[i][j]);
        }
        printk("\n");
    }
}

void move_data0(void)
{
    char *src = (char *)__ovly_table[0][2];
    char *dst = (char *)__ovly_table[0][0];

    while (dst < (char *)(__ovly_table[0][0] + __ovly_table[0][1])) {
        *dst++ = *src++;
    }
}

void move_data1(void)
{
    char *src = (char *)__ovly_table[1][2];
    char *dst = (char *)__ovly_table[1][0];

    while (dst < (char *)(__ovly_table[1][0] + __ovly_table[1][1])) {
        *dst++ = *src++;
    }
}

void overlay_main(void)
{
    ovly_table_show();

    move_data0();
    overlay_function1();

    move_data1();
    overlay_function2();
}