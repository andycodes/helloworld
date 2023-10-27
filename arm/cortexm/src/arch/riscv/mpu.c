#include <stdbool.h>
#include "arch.h"
#include "mpu.h"

struct mpu_table {
    unsigned int addr;
    unsigned int size;
    unsigned int flag;
};

#define RX 0
#define RWX 1

struct mpu_table g_mpu_table[] = 
{
    {0x00000000, 256k, RX}, 
    {0x00040000, 256k, RX}, 
    {0x10000000, 256k, RX}, 
    {0x10040000, 256k, RWX}, 
    {0x20000000, 256k, RWX}, 
    {0x20040000, 256k, RWX}, 
    {0x30000000, 256k, RWX}, 
};

/*
mpu_priv_stronglyordered
    
*/

void mpu_init(void)
{
    unsigned int t_size = sizeof(g_mpu_table) / sizeof(struct mpu_table);
    for (unsigned int i = 0; i < t_size; i++)
        mpu_user_intsram(g_mpu_table[i].addr, g_mpu_table[i].size);

    mpu_control(true, true, true);
}