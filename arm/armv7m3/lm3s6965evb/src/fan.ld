MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K /* 0x20040000 */
}

SECTIONS
{
    .text :
    {
	. = ALIGN(8);
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
	. = ALIGN(8);
    } > FLASH

    /DISCARD/ :
    {
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
    }

    .data : AT(ADDR(.text) + SIZEOF(.text))
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

    . = ALIGN(32);           /*Not sure if this needs to be done, but why not.*/
    _p_stack_bottom = .;
    . = . + 0x4000;
    _p_stack_top = 0x20008000;
    . = . + 0x4000;          /*Allocate 4K for the Stack.*/
    _stack_top = 0x2000c000;  /*Address of the top of the heap, also end of RAM.*/
    _heap_bottom = .;        /*Address of the bottom of the heap.*/
    _heap_top = 0x20040000;  /*Address of the top of the heap, also end of RAM.*/
}
