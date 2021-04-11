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

/*eg�������ַ0x12356789��Ҫ���������ַ��
����c2+0x123�ҵ�ҳ���Ӧ����Ŀ��
ȡ����12λ(&0xfff00000)+0x56789=��ʵ�����ַ*/
void my_mmap(unsigned int *ttb, unsigned int va, unsigned int pa)
{
/*ҳ����Ŀ����ַ[ƫ��] = ҳ�����ݣ�
Ҳ���������ַ�ĸ�12λ | 2����2����ʾ����Ŀ�Ƕ�ӳ��*/
/*�������ַ��ǰ3λ��Ѱ����Ŀ��ԭ��
һ����Ŀ����Ѱַ1M����ô3λhex,2^12��4k��4K*1M=4G*/
    ttb[va >> 20] = (pa & 0xfff00000) | 2;
}

/* section : 4G = 4K * 1M */
void ttb_init(unsigned int *ttb)
{
	int va, pa;
/*va��0��ʼ��ԭ�򣺾���bootlader����֮����MMU���
ȫ�������ַ=�����ַ*/
/*vaÿ��+0x100000��ԭ����Ŀֻ���������ַ�ĸ�12λ��
Ҳ���ǵ�20λ����0x0~0xfffff(2^20=1M)*/
	for(va = 0; va < 0x80000000; va += 0x100000) {
		pa = va;
		my_mmap(ttb, va, pa);
	}

	__asm__ __volatile__(
		"mcr p15, 0, %0, c2, c0, 0\n"
		"mvn r0, #0\n"
		/*c3�Ĵ�����ʾ�����ַ�ķ���Ȩ��(����д��֮��)��
		c3�Ĵ���ÿ2λ��ʾһ��Ȩ��(00,01,10,11)�ܹ���16����
		�����ҳ����Ŀ��5-8λ��3����ô��ȥc3�Ĵ����ĵ�4��
		ȥ�鿴��Ӧ��Ȩ�ޡ�*/
		"mcr p15, 0, r0, c3, c0, 0\n"
		:
		:"r"(ttb)
		:"r0"
	);
}

