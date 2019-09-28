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
将一个无符号短整形数从网络字
节顺序转换为主机字节顺序
*/
unsigned short ntohs(unsigned short s)
{
    return (s >> 8) | (s << 8);
}

/*
将一个无符号长整形数从
网络字节顺序转换为主机字节顺序

*/
unsigned long ntohl(unsigned long l)
{
    return  ((l >> 24) & 0x000000ff) |
        ((l >>  8) & 0x0000ff00) |
        ((l <<  8) & 0x00ff0000) |
        ((l << 24) & 0xff000000);
}

/*

将主机的无符号短整形数转换成网络字节顺序
*/
unsigned short htons(unsigned short s)
{
    return (s >> 8) | (s << 8);
}

/*
将主机的无符号长整形数转换成网络字节顺序

*/
unsigned long htonl(unsigned long l)
{
    return ntohl(l);
}


/*大小写字母相差32,又因为异或重要特性:不进位加法,
所以大写字母和(1<<5)异或变成变成小写字母,
小写字母和(1<<5)异或变成大写字母*/
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
 * 写一个函数,它的原型是int continummax(char *outputstr,char *inputstr)
 * 功能：在字符串中找出连续最长的数字串,并把这个串的长度返回,并把这个最长
 * 数字串赋给其中一个函数参数outputstr所指内存.例如:"abcd12345ed125ss123456789"
 * 的首地址传给inputstr后,函数将返回9,outputstr所指的值为123456789
 */
/*abcd12345ed125ss123456789*/
int continummax(char *outputstr,char *inputstr)
{
    //当前的连续数字个数
   int count=0;
    //字符串中连续数字个数的最大值
    int max=0;
    //保存取得最大值的指针
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

    //有可能字符串末尾取到最大值
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


