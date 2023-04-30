#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"

extern void overlay_function1();
extern void overlay_function2();

extern unsigned int __dny0_ldm_start;
extern unsigned int __dny0_vdm_start;
extern unsigned int __dny0_vdm_end;

extern unsigned int __dny1_ldm_start;
extern unsigned int __dny1_vdm_start;
extern unsigned int __dny1_vdm_end;

extern unsigned int __ovly_table[2][3];


void ovly_table_show(void)
{
#if 0
    printk("ovly_table_show \n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printk("%d", __ovly_table[i][j]);
        }
        printk("\n");
    }
#endif
}

void move_data0(void)
{
    char *src = &__dny0_ldm_start;
    char *dst = &__dny0_vdm_start;

    while (dst < &__dny0_vdm_end) {
        *dst++ = *src++;
    }
}

void move_data1(void)
{
    char *src = &__dny1_ldm_start;
    char *dst = &__dny1_vdm_start;

    while (dst < &__dny1_vdm_end) {
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