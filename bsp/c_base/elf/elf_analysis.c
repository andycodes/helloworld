#include <stdio.h>

int global_init_var = 84;
int global_uninit_var;

void func1(int i)
{
	printf("%d\n",i);
}

int main(void)
{
	static int static_init_var = 85;
	static int static_uninit_val;
	int a = 1;
	int b;

	func1(static_init_var + static_uninit_val + a + b);

	return 0;
}

