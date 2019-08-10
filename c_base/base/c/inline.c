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
		d= a -b;/*��������ʶ���ѭ��û�й�ϵ�������Ż�������*/
	}
	return d;
}

inline int  loop1(int a, int b, int *c)/*û��static :���ɶ����Ļ����,�������ļ����ã�����������*/
{
	int d,i;
	int k = 100;

	for(i = 0; i < 1000; i++) {
		*c = a + b;
		d= k++ -b;/*���Ż�*/
	}
	return d;
}

static inline int  loop2(int a, int b, int *c)
{
	int d,i;
	int k = 100;

	for(i = 0; i < 1000; i++) {
		*c = a + b;
		d= rand();/*�޷��Ż�*/
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
static ��ʹ��ͨ��ָ��Ӧ�û����ǵݹ����Ҳ�����ñ�����Ϊ�����ɻ����
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

