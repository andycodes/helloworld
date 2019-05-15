#include <stdio.h>
#include <string.h>

#include "memory.h"

int main(int argc, char* argv[])
{
	char mem_space[1024*1024];
	char *p_mem[10];
	int i;
	int size = 2048;

	osRtxMemoryInit(mem_space, sizeof(mem_space));

	for (i = 0; i < 10; i++)
	{
		size = size/2;
		p_mem[i] = akmem_alloc(size);
		if (NULL == p_mem[i]) {
			printf("akmem_alloc err\n");
			return -1;
		}

		memset(p_mem[i],i,size);
	}

	for (i = 9; i >= 0; i--)
	{
		char *pchar = p_mem[i];
		printf("char[%d] ",*pchar);
		akmem_free(pchar);
	}

	return 0;
}

