#include <stdio.h>


typedef int (*FUNC) (int a, int b, int *c);


 static int  after(int a, int b, int *c);


 static int  before(int a, int b, int *c)
{
	int d;
	*c = a + b;
	d= a -b;
	return d;
}

static inline int  loop(int a, int b, int *c)
{
	int d,i;

	for(i = 0; i < 1000; i++) {
		*c = a + b;
		d= a -b;/*编译器能识别跟循环没有关系，进而优化成内联*/
	}
	return d;
}

inline int  loop1(int a, int b, int *c)/*没有static :生成独立的汇编码,满足外文件调用，但不是内联*/
{
	int d,i;
	int k = 100;

	for(i = 0; i < 1000; i++) {
		*c = a + b;
		d= k++ -b;/*被优化*/
	}
	return d;
}

static inline int  loop2(int a, int b, int *c)
{
	int d,i;
	int k = 100;

	for(i = 0; i < 1000; i++) {
		*c = a + b;
		d= rand();/*无法优化*/
	}
	return d;
}


static inline int if_else(int a, int b, int *c)
{
	int d = 0;
	int i = 0;
	if (c) {
		*c = a + b;
	}else {
		d= a -b;
	}

	return d;
}


/*
static 即使是通过指针应用或者是递归调用也不会让编译器为它生成汇编码
*/
static inline int f(int n)
{
	if(n<=2) return 1;
	return f(n-1)+f(n-2);
}



int main()
{
	int i,j,q,t,l,m,n,p;
	int k,z,y,s;

	FUNC pfunc = loop;

	k = 1;
	z = 2;
	i = before(k, z, &y);
	j = after(k, z, &y);
	q = loop(k,z,&y);
	t = loop1(k,z,&y);
	l =  loop2(k,z,&y);
	m = if_else(k,z,&y);

	n = pfunc(k,z,&y);
	p = f(100);
	s = i + z + i + j + q + l +m;

 	printf("%d",s);

}

 int  after(int a, int b, int*c)
{
	int d;
	*c =a + b;
	d=a -b;
	return d;
}

/*
arm-linux-gcc -O3 -finline-functions inline.c
arm-linux-objdump -d a.out >O3_inline_ifelse_static.log
*/

