
INCLUDE src/platform/cm85/mem.ld

/* Entry Point */
ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        . = ALIGN(8);
        _text = .;
        KEEP(*(.vectors))
        *(EXCLUDE_FILE(*cpuidle.o) .text)    
        *(EXCLUDE_FILE(*cpuidle.o) .text*)    
        *(.rodata*)
        _etext = .;

        /* section information for utest */
        . = ALIGN(4);
        __rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        __rt_utest_tc_tab_end = .;

    } > NORMAL_S_TEXT_SEC

    .cpuidle_fn :
    {
        . = ALIGN(8);
          *cpuidle.o(.text)    
          *cpuidle.o(.text*)   
	      . = ALIGN(8);
    } > CPUIDLE_S_TEXT_SEC

    .init_fn :
    {
        . = ALIGN(8);
        _init_fn_start = .;
        KEEP(*(.initcall6.init))
        _init_fn_end = .;
	      . = ALIGN(8);
    } > NORMAL_S_TEXT_SEC



    .data :
    {
        . = ORIGIN(S_RAM);
        __data_vdm_start = .;
        __data_ldm_start = ORIGIN(S_ROM);
        *(.data)
        __data_vdm__end = .;
    } > S_RAM AT> S_ROM

    .bss :
    {
    	. = ALIGN(8);
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
	. = ALIGN(8);
    } > S_RAM

    _p_StackLimit = .;
    . = . + __STACK_SIZE;
    . = ALIGN(8);
    _p_StackTop = .;

    . = ALIGN(8);
    __StackLimit = .;
    . = . + __STACK_SIZE;
    . = ALIGN(8);

    /* Set stack top to end of NORMAL_S_TEXT_SEC. */
    __StackTop = ORIGIN(S_RAM) + LENGTH(S_RAM);
}


