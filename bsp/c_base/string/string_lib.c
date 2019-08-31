#include <stdio.h>
#include <string.h>
#include<stdlib.h>

size_t strlen(const char *str) {
	const char *s;
	for (s = str; *s; ++s) {}
	return(s - str);
}


char* strcpy(char *to, const char *from) {
assert(to != NULL && from != NULL);
char *p = to;
while ((*p++ = *from++) != '\0')
;
return to;
}

/*暴力算法的复杂度是O(m  n)*/
char *strstr(const char *haystack, const char *needle) {
// if needle is empty return the full string
if (!*needle) return (char*) haystack;
const char *p1;
const char *p2;
const char *p1_advance = haystack;
for (p2 = &needle[1]; *p2; ++p2) {
p1_advance++; // advance p1_advance M-1 times
}
for (p1 = haystack; *p1_advance; p1_advance++) {
char *p1_old = (char*) p1;
p2 = needle;
while (*p1 && *p2 && *p1 == *p2) {
p1++;
p2++;
}
if (!*p2) return p1_old;
p1 = p1_old + 1;
}
return NULL;
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

char *strupr( char *Str )       //将一组字符串里面的小写字母变为大写
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

#define INT_MAX 2147483647
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

/********************************************
                                sscanf
从一个字符串中读进与指定格式相符的数据

函数原型:

Int  sscanf( string str, string fmt, mixed var1, mixed var2 ... );

int  scanf( const char *format [,argument]... );


说明：

sscanf与scanf类似，都是用于输入的，
只是后者以屏幕(stdin)为输入源，
前者以固定字符串为输入源。
其中的format可以是一个或多个
{%[*] [width] [{h | l | I64 | L}]type | ‘ ‘ | ‘\t‘ | ‘\n‘ | 非%符号}


********************************************/
char buf[512] = {0};
int a,b,c;

int sscanf_test(void)
{
        sscanf("123456","%s",buf);
        printf("%s\n",buf);

/*取指定长度的字符串。
如在下例中，取最大长度为
4字节的字符串。*/
        sscanf("123456 ", "%4s", buf);
        printf("%s\n",buf);

/* 取到指定字符为止的
字符串。如在下例中，
取遇到空格为止字符串。*/
        sscanf("123456 abcdedf", "%[^ ]", buf);
        printf("%s\n",buf);

/* 取仅包含指定字符集的
字符串。如在下例中，
取仅包含1到9和小写字母的字符串。*/
        sscanf("123456bcTedfBCDEF", "%[1-9a-z]", buf);
        printf("%s\n",buf);//123456bc

/*给定一个字符串iios/12DDWDFF@122，
获取 / 和 @ 之间的字符串，
先将 "iios/"过滤掉，
再将非'@'的一串内容送到buf中*/
        sscanf("iios/12DDWDFF@122", "%*[^/]/%[^@]", buf);
        printf("%s\n",buf);

/*给定一个字符串"hello, world"，
仅保留world。
（注意："，"之后有一空格，
%s遇空格停止，加*则是忽略第一
个读到的字符串）*/

/*%*s表示第一个匹配到的%s被过滤
掉，即hello被过滤了*/

/*如果没有空格则结果为NULL。*/
        sscanf("hello, world", "%*s%s", buf);
        printf("%s\n",buf);

        sscanf("2006:03:18", "%d:%d:%d", &a, &b, &c);
        printf("a %d b %d c %d\n",a,b,c);

/*取到指定字符为止的字符串。
如在下例中，取遇到空格为止字符串*/
        sscanf("123456 abcdedf", "%[^ ]", buf);
        printf("%s\n", buf);

/*取到指定字符集为止的字符串。
如在下例中，取遇到大写字母为止的字符串*/
        sscanf("123456abcdedfBCDEF", "%[^A-Z]", buf);
        printf("%s\n", buf);


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


