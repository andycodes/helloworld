
INCLUDE src/platform/lm3s6965evb/mem.ld
ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        . = ALIGN(8);
        _text = .;
        KEEP(*(.vectors))
        *(EXCLUDE_FILE(*cpuidle.o *overlay*.o) .text)    
        *(EXCLUDE_FILE(*cpuidle.o *overlay*.o) .text*)   
        *(.rodata*)
        _etext = .;

        . = ALIGN(8);
        _init_fn_start = .;
        KEEP(*(.initcall6.init))
        _init_fn_end = .;
	      . = ALIGN(8);

        /* section information for utest */
        . = ALIGN(8);
        __rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        __rt_utest_tc_tab_end = .;
    } > TEXT_1_SECTION

    .cpuidle_fn :
    {
        . = ALIGN(8);
          *cpuidle.o(.text)    
          *cpuidle.o(.text*)      
	      . = ALIGN(8);
    } > TEXT_2_SECTION

    OVERLAY : NOCROSSREFS
    {
      .dyn_fn0  {
          . = ALIGN(8);
            *overlay0.o(.text)
            *overlay0.o(.text*)
          . = ALIGN(8);
      }

      .dyn_fn1  {
          . = ALIGN(8);
            *overlay1.o(.text)    
            *overlay1.o(.text*) 
          . = ALIGN(8);
      }
    } > TEXT_RAM_DYN_SECTION AT> TEXT_ROM_DYN_SECTION

    .data :
    {
        *(.data)
    } > DATA_RAM_VDM_SECTION

    .ovlytable_sec :
    {
      . = ALIGN(8);
      __ovly_table = .; 
      LONG(ABSOLUTE(ADDR(.dyn_fn0))); LONG(SIZEOF(.dyn_fn0)); LONG(LOADADDR(.dyn_fn0));
      LONG(ABSOLUTE(ADDR(.dyn_fn1))); LONG(SIZEOF(.dyn_fn1)); LONG(LOADADDR(.dyn_fn1));
      . = ALIGN(8);
    }  > DATA_RAM_SECTION 

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
