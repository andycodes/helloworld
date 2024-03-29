/*
sizeof ( x )  
������, ������, ������,  ���Ǻ��� ! 

�ڱ���ʱȷ����ֵ,  �����x���ڴ�����ռ�ֽ���. 

 ����, �����ڵĸ�ֵ�ͺ���, ���ᱻִ��, ������ִ��, ûһ��Ǯ��ϵ.
*/

#include <stdio.h>


//  1. sizeof ( ��ֵ )  
void sizeof_data(void)
{
    char c=8;
    int  i=32;
    printf("%ld ", sizeof(c    ));  // ���:1, ��Ϊchar����1�ֽ�
    printf("%ld ", sizeof(c+i  ));  // ���:4, i��4�ֽ�, ����ʱcֵ����ʽת����int, ����ֵ��4�ֽ�
    printf("%ld ", sizeof(c=c+i));  // ���:1, ��ͬ��(c), ����ʱ, ��Ϊ=����ִ��, ����=���ұ�ֻ�Ǹ�ƨ 
}

//  2. sizeof ( �ַ� )
void sizeof_char(void)
{
    // С��, char��'a'�ڱ�=����ǰ, ��������������, û����
    char c = 'a';  
    printf("%ld ", sizeof(c));      // ���:1, char������1�ֽ�
    printf("%ld ", sizeof('a'));    // C���:4��C++���:1
                                // C99�ı�׼��    'a'�������ַ�����������!����!����!��������int�ͣ� ����ռ4�ֽڡ�
                                // ISO C++�ı�׼��'a'���ַ�������  ����������char�ͣ�����ռ1�ֽڡ�
}

// 3. sizeof ( �ַ��� )
void sizeof_string(void)
{
    printf("%ld ", sizeof("abc")); // ���:4��˫���Ż���β���Զ����ת���ַ�'\0',������0X00, ������4   
                                // ˫��������: (1)�ַ���β����0, (2)�����ڴ�ռ�, (3)��ȡ��ַ
}

//4. sizeof ( ���� )
void sizeof_array(void)
{
    char a[50]="hello";
    printf("%ld ", sizeof(a));      // ���:50, �����������ֽڴ�С
}

/*
5. sizeof ( ָ�� )
 sizeof_point,8(64bit) 1
  *p �� p ָ������ݣ�*p �Ĵ�С��ָ�����ݵĴ�С
*/
void sizeof_point(void)
{
    char *p="hello";
    printf("%s,%zu %zu \n", __func__, sizeof(p), sizeof(*p));     
}

//6. sizeof ( �ṹ�� )  
// �ֽڶ���,Ϊ���ٴ�������,�ڴ��ǰ�32λ��ȡд��,������һ�ֽ�һ�ֽڵض�д
// �ṹ����׵�ַ�Զ��������ܱ������ֽ�����С��������
// �ṹ��ÿ����Ա�ڽṹ���ڵ�ƫ�Ƶ�ַ���ǳ�Ա��С��������������, ��ǰ�����byte��
// �ṹ����ܴ�СΪ�ṹ������ֽ�����С��������

void sizeof_struct(void)
{
struct T1{
    int   a;                  // ��Ա����λ��
    char  b;
    int   c;
    short d;
}t1;
printf("%ld ", sizeof(t1));   // ���:16, 4+4+4+4
 
struct T2{
    int   a;                  // �����ų�Աλ��
    char  b;
    short d;
    int   c;
}t2;
printf("%ld ", sizeof(t2));     // ���:12, 4+4+4, ��ƽṹʱ��������Ա��λ�ã��ɽ�ʡ�洢�ռ䡣
}

//7. sizeof ( ���� )
// С��, ������ִ��
char Sum(int i, short s)
{return i + s;}

void sizeof_func(void)
{
    printf("%ld ", sizeof(Sum(32, 8)));  // ���:1, ֻ���жϷ������͵Ĵ�С. �����ǲ���ִ�е�! 
}

int main(void)
{
    sizeof_data();
    sizeof_char();
    sizeof_string();
    sizeof_array();
    sizeof_point();
    sizeof_struct();
    sizeof_func();
    printf("\n"); 
}