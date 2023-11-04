
__STACK_SIZE = 8K;

MEMORY
{
   ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128M
}
/*
hexdump -C -s 0x40000 bin/mps3-an547/felix.bin 
*/