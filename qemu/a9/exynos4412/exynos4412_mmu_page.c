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

//����һ��ӳ��4K�ڴ�
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
/*va��0��ʼ��ÿ�μ�0x100000�Ͷ�ӳ��һ����
��ʾ0-2G������ȫ��ӳ�䡣���������ַ�������ַһ��*/
    for(va = 0; va < 0x80000000; va += 0x100000){
        /* 0----1M,ttb1[va>>20]���ǰ�0x100000*0-0x100000*0x800>>20λ��
        ���ƺ��൱��i=0;ttb1[i++] */
        /* figure10-3����һ��ҳ�������Ϊ
        ����ҳ��Ļ���ַ�ĸ�22λ|������ҳӳ��*/
        ttb1[va >> 20] = ((unsigned int)ttb2 & (~0x3ff)) | 1;

	//0-4K 4K-8K 8K-12K 1M
        /*va1=va����Ϊ��ѭ��һ�ξ�ӳ����1M�������ڴ棬
        ��pa=va1��Ҫ��Ϊ�˵õ���ȷ�������ڴ�ƫ��ֵ��va1 */
        for(va1 = va; va1 < va + 0x100000; va1 += 0x1000){
            pa = va1;
            //��������ַ���м�8λ = �����ַ�ĸ�20λ
            ttb2[(va1 >> 12) & 0xff] = (pa & (~0xfff)) | 2;
        }
        ttb2 += 0x100;//����ҳ��ÿִ��һ����Ҫ�ƶ�256����Ŀ=1k=256*4
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

