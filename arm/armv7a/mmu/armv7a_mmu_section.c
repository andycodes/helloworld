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

/*eg：虚拟地址0x12356789想要访问物理地址，
则用c2+0x123找到页表对应的条目，
取出高12位(&0xfff00000)+0x56789=真实物理地址*/
void my_mmap(unsigned int *ttb, unsigned int va, unsigned int pa)
{
/*页表条目基地址[偏移] = 页表内容，
也就是物理地址的高12位 | 2，或2，表示此条目是段映射*/
/*用虚拟地址的前3位来寻找条目的原因：
一个条目可以寻址1M，那么3位hex,2^12是4k，4K*1M=4G*/
    ttb[va >> 20] = (pa & 0xfff00000) | 2;
}

/* section : 4G = 4K * 1M */
void ttb_init(unsigned int *ttb)
{
	int va, pa;
/*va从0开始的原因：就是bootlader起来之后开启MMU想把
全部虚拟地址=物理地址*/
/*va每次+0x100000的原因：条目只保存物理地址的高12位，
也就是低20位都补0x0~0xfffff(2^20=1M)*/
	for(va = 0; va < 0x80000000; va += 0x100000) {
		pa = va;
		my_mmap(ttb, va, pa);
	}

	__asm__ __volatile__(
		"mcr p15, 0, %0, c2, c0, 0\n"
		"mvn r0, #0\n"
		/*c3寄存器表示虚拟地址的访问权限(读？写？之类)，
		c3寄存器每2位表示一个权限(00,01,10,11)总过有16个，
		如果段页表条目的5-8位是3，那么就去c3寄存器的第4个
		去查看相应的权限。*/
		"mcr p15, 0, r0, c3, c0, 0\n"
		:
		:"r"(ttb)
		:"r0"
	);
}

