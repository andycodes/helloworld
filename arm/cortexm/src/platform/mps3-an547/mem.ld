
__STACK_SIZE = 8K;

MEMORY
{
   TEXT_1_SECTION (rx) : ORIGIN = 0x00000000, LENGTH = 64k
   /*vectors*/
   /*rodata*/
   /*init_fn*/
   /*UtestTcTab*/

   TEXT_2_SECTION (rx) : ORIGIN = 0x00010000, LENGTH = 64k
   /*cpuidle*/

   TEXT_RAM_DYN_SECTION (rx) : ORIGIN = 0x00020000, LENGTH = 64k 
   TEXT_ROM_DYN_SECTION (r) : ORIGIN = 0x00030000, LENGTH = 64k
   /*OVERLAY*/
   
   DATA_ROM_LDM_SECTION (r) : ORIGIN = 0x00040000, LENGTH = 64k
   DATA_RAM_VDM_SECTION (rw) : ORIGIN = 0x00050000, LENGTH = 64k
   /*data*/
   
   DATA_RAM_SECTION (rw) : ORIGIN = 0x00060000, LENGTH = 64k
   /*__ovly_table*/
   /*_bss*/
   /*stack*/
   /*heap*/
}
/*
hexdump -C bin/mps3-an547/felix.bin -s 0x40000
*/