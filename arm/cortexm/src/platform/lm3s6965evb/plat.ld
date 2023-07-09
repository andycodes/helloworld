
INCLUDE src/platform/lm3s6965evb/mem.ld
SECTIONS
{
    .text :
    {
	    . = ALIGN(8);
        _text = .;
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;

        /* section information for utest */
        . = ALIGN(4);
        __rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        __rt_utest_tc_tab_end = .;
    } > TEXT_1_SECTION

    .init_fn :
    {
        . = ALIGN(8);
        _init_fn_start = .;
        KEEP(*(.initcall6.init))
        _init_fn_end = .;
	      . = ALIGN(8);
    } > TEXT_1_SECTION

    .data : 
    {
	. = ALIGN(8);
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
	. = ALIGN(8);
    } > DATA_RAM_SECTION

    .bss :
    {
        . = ALIGN(8);
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
        . = ALIGN(8);
    } > DATA_RAM_SECTION

    .stack : {
        . = ALIGN(8);
        __StackLimit = .;
        . = . + __STACK_SIZE;
        __PspStart = .;
        . = . + __STACK_SIZE;
         __PspTop = .;
        . = . + __STACK_SIZE;
        __StackTop = .;
        . = ALIGN(8);
    } > DATA_RAM_SECTION

    .heap : {
      __heap_start = .;
      . = . + 4096 * 6;
      __heap_end = .;
    } > DATA_RAM_SECTION
}

