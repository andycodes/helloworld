#include <stdio.h>

int global_init_var = 84; //.data
int global_uninit_var; //*COM*
static int sg_init_var = 77; //.data
static int sg_uninit_var; //.bss

void func1(int i)
{
	printf("%d\n",i);
}

int main(void)
{
	static int static_init_var = 85; //.data
	static int static_uninit_val; //.bss
	int a = 1;
	int b;

	func1(static_init_var + static_uninit_val + a + b); //.text
	func1(sg_init_var + sg_uninit_var);

	return 0;
}

/*
arm-linux-gnueabi-gcc -c elf_analysis.c
arm-linux-gnueabi-objdump -x elf_analysis.o
*/

