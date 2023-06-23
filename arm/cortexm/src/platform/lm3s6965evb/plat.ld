/* Linker script to configure memory regions. */
MEMORY
{
    TEXT_1_SECTION (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K /* 0x20040000 */
}

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
    } > SRAM

    .bss :
    {
    	. = ALIGN(8);
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
	. = ALIGN(8);
    } > SRAM

    . = ALIGN(32);
    _p_StackLimit = .;
    . = . + 0x4000;
    _p_StackTop = .;
    . = . + 0x4000;
    __StackTop = .;
}
