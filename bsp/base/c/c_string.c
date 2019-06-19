#include <stdio.h>
#include <string.h>

/*
��һ���޷��Ŷ���������������
��˳��ת��Ϊ�����ֽ�˳��
*/
unsigned short ntohs(unsigned short s)
{
    return (s >> 8) | (s << 8);
}

/*
��һ���޷��ų���������
�����ֽ�˳��ת��Ϊ�����ֽ�˳��

*/
unsigned long ntohl(unsigned long l)
{
    return  ((l >> 24) & 0x000000ff) |
        ((l >>  8) & 0x0000ff00) |
        ((l <<  8) & 0x00ff0000) |
        ((l << 24) & 0xff000000);
}

/*

���������޷��Ŷ�������ת���������ֽ�˳��
*/
unsigned short htons(unsigned short s)
{
    return (s >> 8) | (s << 8);
}

/*
���������޷��ų�������ת���������ֽ�˳��

*/
unsigned long htonl(unsigned long l)
{
    return ntohl(l);
}

char *strupr( char *Str )       //��һ���ַ��������Сд��ĸ��Ϊ��д
{
    char *cp;
    cp = Str;

    while (*cp != 0)
    {
        if (*cp >= 'a' && *cp <= 'z' )
        {
            *cp -= 'a' - 'A';
        }

        cp++;
    }

    return Str;
}


unsigned long strtobcd(char *s)
{
    unsigned long ret;
    int i;

    ret = 0;

    while (*s != '\0') {
        if (*s >= '0' && *s <= '9')
            i = *s - '0';
        else
            return -1;
        ret = (ret << 4) + i;
        s++;
    }

    return ret;
}

unsigned long strtodec(char *str, int cnt)
{
    unsigned long i, data = 0;

    for(i=0; i<cnt; i++)
    {
        data *= 10;
        if(str[i]<'0'||str[i]>'9')
            return -1;
        data += str[i]-'0';
    }
    return data;
}

void ultostr(char *s, unsigned long data)
{
    int i;

    s[8] = 0;
    for(i=7; i>=0; i--, data >>=4)
    {
        if((data&0xf)<=9)
            s[i] = (data&0xf)+'0';
        else
            s[i] = (data&0xf)+'a'-0x0a;
    }
}

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


/*
 * дһ������,����ԭ����int continummax(char *outputstr,char *inputstr)
 * ���ܣ����ַ������ҳ�����������ִ�,����������ĳ��ȷ���,��������
 * ���ִ���������һ����������outputstr��ָ�ڴ�.����:"abcd12345ed125ss123456789"
 * ���׵�ַ����inputstr��,����������9,outputstr��ָ��ֵΪ123456789
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*abcd12345ed125ss123456789*/
int continummax(char *outputstr,char *inputstr)
{
    //��ǰ���������ָ���
   int count=0;
    //�ַ������������ָ��������ֵ
    int max=0;
    //����ȡ�����ֵ��ָ��
    char *m;
    char *s=inputstr;
    int i=0;

    while(*s != '\0')
    {
        if(*s>='0'&&*s<='9')
        {
            count++;
        }
        else
        {
            if(count>max)
            {
                max=count;
                m=s-max;
            }
            count=0;
        }

        s++;
    }

    //�п����ַ���ĩβȡ�����ֵ
    if(count>max)
    {
        max=count;
        m=s-max;
    }

    while(i<max)
    {
        *outputstr=*(m+i);
        outputstr++;
        i++;
    }

    *outputstr='\0';
    return max;
}


void str_to_hex_by_sscanf(char * str)
{
	int value;
	sscanf(str, "%x", &value);
	printf("0x%x\n",value);
}


void str_to_hex_by_strtol(char * str)
{
	char* p;
	long value = strtol(str, &p, 16);

	printf("0x%lx\n",value);
}


int main(int argc, char* argv[])
{
	switch(atoi(argv[1]))
	{
		case 1:
			str_to_hex_by_sscanf(argv[2]);
		break;
		case 2:
			str_to_hex_by_strtol(argv[2]);
		break;
		default:
		break;
	}
}


