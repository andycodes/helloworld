#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(int argc, char* argv[])
{
    unsigned long phymem_addr, phymem_size;
    char *map_addr;
    char s[256];
    int fd;
    
    if(argc != 2)
    {
        printf("Usage: %s string\n", argv[0]);
       // return -1;
    }

    /*get the physical address of allocated memory in kernel*/
    fd = open("/proc/memshare/phymem_addr", O_RDONLY);
    if(fd < 0)
    {
            printf("cannot open file /proc/memshare/phymem_addr\n");
            return 0;
    }
    
    read(fd, s, sizeof(s));
    sscanf(s, "%lx", &phymem_addr);
    close(fd);

    /*get the size of allocated memory in kernel*/
    fd = open("/proc/memshare/phymem_size", O_RDONLY);
    if(fd < 0)
    {
            printf("cannot open file /proc/memshare/phymem_size\n");
            return 0;
    }
    read(fd, s, sizeof(s));
    sscanf(s, "%lu", &phymem_size);
    close(fd);

    printf("phymem_addr=%lx, phymem_size=%lu\n", phymem_addr, phymem_size);

    /*memory map*/
/*  
    /dev/mem�������ڴ��ȫӳ�񣬿����������������ڴ棬
    һ���÷���open("/dev/mem",O_RDWR|O_SYNC)��Ȼ��mmap��
    ���žͿ�����mmap�ĵ�ַ�����������ڴ棬��ʵ���Ͼ���ʵ���û��ռ�������һ�ַ�����
    /dev/kmem���ں˿����������ڴ��ȫӳ�񣬿�����������kernel�����ݡ�
*/
    int map_fd = open("/dev/mem", O_RDWR);
    if(map_fd < 0)
    {
            printf("cannot open file /dev/mem\n");
            return 0;
    }

    map_addr = mmap(0, phymem_size, PROT_READ|PROT_WRITE, MAP_SHARED, map_fd, phymem_addr);
    if((void*)-1 == map_addr)
    {
 /*
��CONFIG_X86_PAT=y������£��޷�mmap��
��CONFIG_X86_PAT=n������£�ͬʱCONFIG_STRICT_DEVMEM������n�������޷�mmap��

�ܽ᣺
�����Ҫmmap�������
CONFIG_X86_PAT=n
CONFIG_STRICT_DEVMEM=n

 */
        printf("mmap err\n");
        return -1;
    }

    printf("map_addr %p \n",map_addr);
    //strcpy(map_addr, argv[1]);
    strcpy((char*)map_addr, "fansaihua");
    munmap(map_addr, phymem_size);
    close(map_fd);
    return 0;  
}

