
#include<stdio.h>

int sum(int a)
{
	auto int c=0;
	static int b=3;// static,不可重入
	c+=1;
	b+=2;
	printf("[%s]b[%d]c[%d]\n,", __func__,b,c);
	return(a+b+c);
}

int main(int argc, char* argv[])
{
	int I;
	int a=2;
	for(I=0;I<5;I++)
	{
		printf("%d,", sum(a));
	}
}
/*
运行结果是：8,10,12,14,16,
  Auto 在函数内 栈空间 定义，函数结束 栈空间 释放 下次重新分配
  Static 分配在 BSS段 函数栈空间释放 不受影响
*/

