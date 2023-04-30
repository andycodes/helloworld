#if 0
extern unsigned int _ovly_table[2][3];

void eeprom_load_overlay(int n)
{
    uart_print("--- loading overlay ");
    uart_print_dec(n);
    uart_print(" from ");
    uart_print_number(_ovly_table[n][2], 16, 0);
    uart_print(" to ");
    uart_print_number(_ovly_table[n][0], 16, 0);
    uart_print(" size ");
    uart_print_dec(_ovly_table[n][1]);
    uart_print("\r\n");

    eeprom_read(HIGH_EEPROM_OFFSET(_ovly_table[n][2]), (uint8_t *)_ovly_table[n][0], _ovly_table[n][1]);
}

void main(void)
{
    uart_print("\r\n*** OVERLAY DEMO ***\r\n\r\n");
    eeprom_load_overlay(0);
    overlay_function1();
    eeprom_load_overlay(1);
    overlay_function2();
}
#endif

extern void overlay_function1();
extern void overlay_function2();


extern unsigned int __dny0_ldm_start;
extern unsigned int __dny0_vdm_start;
extern unsigned int __dny0_vdm_end;

extern unsigned int __dny1_ldm_start;
extern unsigned int __dny1_vdm_start;
extern unsigned int __dny1_vdm_end;

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
    move_data0();
    overlay_function1();
    move_data1();
    overlay_function2();
}