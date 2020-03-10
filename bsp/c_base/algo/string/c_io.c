/********************************************
                                sscanf
��һ���ַ����ж�����ָ����ʽ���������

����ԭ��:

Int  sscanf( string str, string fmt, mixed var1, mixed var2 ... );

int  scanf( const char *format [,argument]... );


˵����

sscanf��scanf���ƣ�������������ģ�
ֻ�Ǻ�������Ļ(stdin)Ϊ����Դ��
ǰ���Թ̶��ַ���Ϊ����Դ��
���е�format������һ������
{%[*] [width] [{h | l | I64 | L}]type | �� �� | ��\t�� | ��\n�� | ��%����}


********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[512] = {0};
int a,b,c;

int sscanf_test(void)
{
        sscanf("123456","%s",buf);
        printf("%s\n",buf);

/*ȡָ�����ȵ��ַ�����
���������У�ȡ��󳤶�Ϊ
4�ֽڵ��ַ�����*/
        sscanf("123456 ", "%4s", buf);
        printf("%s\n",buf);

/* ȡ��ָ���ַ�Ϊֹ��
�ַ��������������У�
ȡ�����ո�Ϊֹ�ַ�����*/
        sscanf("123456 abcdedf", "%[^ ]", buf);
        printf("%s\n",buf);

/* ȡ������ָ���ַ�����
�ַ��������������У�
ȡ������1��9��Сд��ĸ���ַ�����*/
        sscanf("123456bcTedfBCDEF", "%[1-9a-z]", buf);
        printf("%s\n",buf);//123456bc

/*����һ���ַ���iios/12DDWDFF@122��
��ȡ / �� @ ֮����ַ�����
�Ƚ� "iios/"���˵���
�ٽ���'@'��һ�������͵�buf��*/
        sscanf("iios/12DDWDFF@122", "%*[^/]/%[^@]", buf);
        printf("%s\n",buf);

/*����һ���ַ���"hello, world"��
������world��
��ע�⣺"��"֮����һ�ո�
%s���ո�ֹͣ����*���Ǻ��Ե�һ
���������ַ�����*/

/*%*s��ʾ��һ��ƥ�䵽��%s������
������hello��������*/

/*���û�пո�����ΪNULL��*/
        sscanf("hello, world", "%*s%s", buf);
        printf("%s\n",buf);

        sscanf("2006:03:18", "%d:%d:%d", &a, &b, &c);
        printf("a %d b %d c %d\n",a,b,c);

/*ȡ��ָ���ַ�Ϊֹ���ַ�����
���������У�ȡ�����ո�Ϊֹ�ַ���*/
        sscanf("123456 abcdedf", "%[^ ]", buf);
        printf("%s\n", buf);

/*ȡ��ָ���ַ���Ϊֹ���ַ�����
���������У�ȡ������д��ĸΪֹ���ַ���*/
        sscanf("123456abcdedfBCDEF", "%[^A-Z]", buf);
        printf("%s\n", buf);


}



int main()
{
    int a,b;
    while( scanf( "%d%d" , &a , &b ) != EOF )   //����ֱ���ļ���β
    {
        printf( "%d\n" , a+b );   //һ��һ�����
    }

    return 0;
}

