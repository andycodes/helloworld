#include <stdio.h>

void foo1(int a)
{
	int i;
	i = a;
}
int fun(int a, int b, int c)
{
	char buf[14];
	int sum;
	sum = a + b + c;
	foo1(a);
	return sum;
}