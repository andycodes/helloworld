/*---------------------- Flash Configuration ----------------------------------
  <h> Flash Configuration
    <o0> Flash Base Address <0x0-0xFFFFFFFF:8>
    <o1> Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__ROM_BASE = 0x00000000;
__ROM_SIZE = 0x00040000;

/*--------------------- Embedded RAM Configuration ----------------------------
  <h> RAM Configuration
    <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
    <o1> RAM Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
 -----------------------------------------------------------------------------*/
__RAM_BASE = 0x20000000;
__RAM_SIZE = 0x00020000;

/*--------------------- Stack / Heap Configuration ----------------------------
  <h> Stack / Heap Configuration
    <o0> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
    <o1> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__STACK_SIZE = 0x00001000;
__HEAP_SIZE  = 0x00000C00;

/*
 *-------------------- <<< end of configuration section >>> -------------------
 */

/* ARMv8-M stack sealing:
   to use ARMv8-M stack sealing set __STACKSEAL_SIZE to 8 otherwise keep 0
 */
__STACKSEAL_SIZE = 0;


/* Linker script to configure memory regions. */
MEMORY
{
   NORMAL_S_TEXT_SEC (rx) : ORIGIN = 0x10000000, LENGTH = 256k
   CPUIDLE_S_TEXT_SEC (rx) : ORIGIN = 0x10040000, LENGTH = 256k
   S_RAM   (rwx) : ORIGIN = 0x30000000, LENGTH = 512k
}