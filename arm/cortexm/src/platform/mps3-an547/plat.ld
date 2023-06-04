
INCLUDE src/platform/mps3-an547/mem.ld

/* Entry Point */
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

        /* section information for utest */
        . = ALIGN(4);
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
          __dny0_vdm_start = ORIGIN(TEXT_RAM_DYN_SECTION);
          __dny0_ldm_start = ORIGIN(TEXT_ROM_DYN_SECTION);
            *overlay0.o(.text)    
            *overlay0.o(.text*)  
          __dny0_vdm_end = .;
          . = ALIGN(8);
      }

      .dyn_fn1  {
          . = ALIGN(8);
          __dny1_vdm_start = ORIGIN(TEXT_RAM_DYN_SECTION);
          __dny1_ldm_start = __dny0_ldm_start + __dny0_vdm_end - __dny0_vdm_start;
            *overlay1.o(.text)    
            *overlay1.o(.text*) 
          __dny1_vdm_end = .; 

          . = ALIGN(8);
      }
    } > TEXT_RAM_DYN_SECTION AT> TEXT_ROM_DYN_SECTION

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
        . = ORIGIN(DATA_RAM_VDM_SECTION);
        __data_vdm_start = .;
        __data_ldm_start = ORIGIN(DATA_ROM_LDM_SECTION);
        *(.data)
        __data_vdm__end = .;
    } > DATA_RAM_VDM_SECTION AT> DATA_ROM_LDM_SECTION

/*
    .ovlytable_sec :
    {
      . = ALIGN(8);
      __ovly_table = .; 
      LONG(ABSOLUTE(ADDR(.dyn_fn0))); LONG(SIZEOF(.dyn_fn0)); LONG(LOADADDR(.dyn_fn0));
      LONG(ABSOLUTE(ADDR(.dyn_fn1))); LONG(SIZEOF(.dyn_fn1)); LONG(LOADADDR(.dyn_fn1));
      . = ALIGN(8);
    }  >DATA_RAM_SECTION 
*/
    .bss :
    {
        . = ALIGN(8);
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
        . = ALIGN(8);
    } > DATA_RAM_SECTION

    . = ALIGN(8);
    __StackLimit = .;
    . = . + __STACK_SIZE;
    . = ALIGN(8);

    /* Set stack top to end of TEXT_1_SECTION. */
    __StackTop = ORIGIN(DATA_RAM_SECTION) + LENGTH(DATA_RAM_SECTION);
}


