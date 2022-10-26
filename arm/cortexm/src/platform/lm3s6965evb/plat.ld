/* Linker script to configure memory regions. */
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
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
	. = ALIGN(8);
    } > FLASH

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

    . = ALIGN(32);
    _p_StackLimit = .;
    . = . + 0x4000;
    _p_StackTop = .;
    . = . + 0x4000;
    __StackTop = .;
}
