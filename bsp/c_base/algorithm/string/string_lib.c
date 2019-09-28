#include <stdio.h>
#include <string.h>
#include<stdlib.h>

//The strchr() function returns a pointer to the first occurrence of the character c in the string s.


size_t strlen(const char *str) {
	const char *s;
	for (s = str; *s; ++s) {}
	return(s - str);
}


char* strcpy(char *to, const char *from) {
    if(to == NULL && from == NULL) return 0;

    char *p = to;
    while ((*p++ = *from++) != '\0')
    ;
    return to;
}


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


/*��Сд��ĸ���32,����Ϊ�����Ҫ����:����λ�ӷ�,
���Դ�д��ĸ��(1<<5)����ɱ��Сд��ĸ,
Сд��ĸ��(1<<5)����ɴ�д��ĸ*/
char *str_letter_big_little( char *Str )
{
    char *cp;
    cp = Str;

    while (*cp != 0)
    {
        *cp^=(1<<5);
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

#define INT_MAX 2147483647
#define INT_MIN -2147483648
int atoi(const char *str) {
    int num = 0;
    int sign = 1;
    const int len = strlen(str);
    int i = 0;
    while (str[i] == ' ' && i < len) i++;
    if (str[i] == '+') i++;
    if (str[i] == '-') {
    sign = -1;
    i++;
    }
    for (; i < len; i++) {
        if (str[i] < '0' || str[i] > '9')
        break;
        if (num > INT_MAX / 10 ||
        (num == INT_MAX / 10 &&
        (str[i] - '0') > INT_MAX % 10)) {
            return sign == -1 ? INT_MIN : INT_MAX;
        }
        num = num * 10 + str[i] - '0';
    }
    return num * sign;
}


/*
 * дһ������,����ԭ����int continummax(char *outputstr,char *inputstr)
 * ���ܣ����ַ������ҳ�����������ִ�,����������ĳ��ȷ���,��������
 * ���ִ���������һ����������outputstr��ָ�ڴ�.����:"abcd12345ed125ss123456789"
 * ���׵�ַ����inputstr��,����������9,outputstr��ָ��ֵΪ123456789
 */
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


