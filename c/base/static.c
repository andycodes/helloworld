
#include<stdio.h>

int sum(int a)
{
	auto int c=0;
	static int b=3;// static,��������
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
���н���ǣ�8,10,12,14,16,
  Auto �ں����� ջ�ռ� ���壬�������� ջ�ռ� �ͷ� �´����·���
  Static ������ BSS�� ����ջ�ռ��ͷ� ����Ӱ��
*/

