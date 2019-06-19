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
    /dev/mem是物理内存的全映像，可以用来访问物理内存，
    一般用法是open("/dev/mem",O_RDWR|O_SYNC)，然后mmap，
    接着就可以用mmap的地址来访问物理内存，这实际上就是实现用户空间驱动的一种方法。
    /dev/kmem：内核看到的虚拟内存的全映像，可以用来访问kernel的内容。
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
当CONFIG_X86_PAT=y的情况下，无法mmap；
当CONFIG_X86_PAT=n的情况下，同时CONFIG_STRICT_DEVMEM必须是n，否则无法mmap；

总结：
如果需要mmap，则必须
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

