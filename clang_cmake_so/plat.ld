
INCLUDE mem.ld
ENTRY(main)

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
        #__data_vdm_start并不是一个变量，它只是一个值，并不需要在内存中留出一段空间来保存它；
        #在C语言中，符号表中会有一个名为__data_vdm_start的项，这个项目中的值（地址值）是0x40000；
        #注意，这个0x40000并没有实际存在的内存。
        #编译器处理后，二进制文件直接对0x40000地址处理
        #这个值只是链接脚本中定义的值，并不表示某个变量的地址。
        #使用取址符号&去得到它在符号表中的值。      
        __data_vdm_start = .;
        __data_ldm_start = ORIGIN(DATA_ROM_LDM_SECTION);
        #ORIGIN(memory)  返回名为 memory 的内存区域的起始地址。
        #ABSOLUTE来强制一个本来是相对地址的表达式变为绝对地址
        LONG(ABSOLUTE(ADDR(.data)));LONG(ABSOLUTE(LOADADDR(.data)));
        #LONG(ABSOLUTE(ADDR(.text))); LONG(SIZEOF(.text)); LONG(LOADADDR(.text));
        *(.data)
        __data_vdm__end = .;
    } > DATA_RAM_VDM_SECTION AT> DATA_ROM_LDM_SECTION

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
