#include <common.h>
#include <mmu.h>

void mmu_enable(void)
{
    __asm__ __volatile__(
        "mrc p15, 0, r0, c1, c0, 0\n"
        "orr r0, r0, #1\n"
        "mcr p15, 0, r0, c1, c0, 0\n"
        :::"r0"
    );
}

void mmu_disable(void)
{
    __asm__ __volatile__(
        "mrc p15, 0, r0, c1, c0, 0\n"
        "bic r0, r0, #1\n"
        "mcr p15, 0, r0, c1, c0, 0\n"
        :::"r0"
    );
}

//运行一次映射4K内存
//my_mmap(sssss, aaaa, 0x12345000, 0x56789000);
void my_mmap(unsigned int *ttb1, unsigned int *ttb2, unsigned int va, unsigned int pa)
{
    ttb1[va >> 20] = ((unsigned int)ttb2 & (~0x3ff)) | 1;
    ttb2[(va >> 12) & 0xff] = (pa & (~0xfff)) | 2;
}

/*
armv7-A_mmu.docx
page : 4G = 4K * 256 * 4k
*/
void ttb_init(unsigned int *ttb1, unsigned int *ttb2)
{
    int va, pa;
    int va1;
/*va从0开始，每次加0x100000和段映射一样，
表示0-2G的内容全部映射。而且物理地址和虚拟地址一样*/
    for(va = 0; va < 0x80000000; va += 0x100000){
        /* 0----1M,ttb1[va>>20]就是把0x100000*0-0x100000*0x800>>20位，
        右移后相当于i=0;ttb1[i++] */
        /* figure10-3表明一级页表的内容为
        二级页表的基地址的高22位|表明是页映射*/
        ttb1[va >> 20] = ((unsigned int)ttb2 & (~0x3ff)) | 1;

	//0-4K 4K-8K 8K-12K 1M
        /*va1=va是因为外循环一次就映射了1M的物理内存，
        而pa=va1主要是为了得到正确的物理内存偏移值；va1 */
        for(va1 = va; va1 < va + 0x100000; va1 += 0x1000){
            pa = va1;
            //求得虚拟地址的中间8位 = 物理地址的高20位
            ttb2[(va1 >> 12) & 0xff] = (pa & (~0xfff)) | 2;
        }
        ttb2 += 0x100;//二级页表每执行一次需要移动256个条目=1k=256*4
    }

    __asm__ __volatile__(
        "mcr p15, 0, %0, c2, c0, 0\n"
        "mvn r0, #0\n"
        "mcr p15, 0, r0, c3, c0, 0\n"
        :
        :"r"(ttb1)
        :"r0"
    );
}

