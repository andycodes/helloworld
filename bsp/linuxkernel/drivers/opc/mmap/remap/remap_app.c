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
	int dev_fd;
    void *src = NULL;
    
    if ((dev_fd = open("/dev/simple_remap", O_RDWR)) < 0)
	{
    	printf("can't open /dev/simple_remap for reading\n");
    }

    if ((src = mmap(NULL, 4096*2, PROT_READ, MAP_SHARED,
	    dev_fd, 0)) == MAP_FAILED)
    {
		printf("mmap error  \n");
    }

    /*get src to opreate*/

    close(dev_fd);
    return 0;
}

