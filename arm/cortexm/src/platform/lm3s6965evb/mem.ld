
__STACK_SIZE = 8K;

/* Linker script to configure memory regions. */
MEMORY
{
    TEXT_1_SECTION (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    DATA_RAM_SECTION (rwx) : ORIGIN = 0x20000000, LENGTH = 256K /* 0x20040000 */
}
