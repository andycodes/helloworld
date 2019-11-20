#include <stdio.h>
#include <string.h>
#include<stdlib.h>


/*
#include <string.h>
查找子字符串
意义为 判断str2是否为str1的字串，
若是则返回str2在str1中首次出现的指针位置，
若不是返回NULL；

*/
extern char *strstr(char *str1, const char *str2);


/*
查找字符
参数说明：
str：被查找的字符串。
c：要查找的字符。

strchr() 函数会依次检索字符串 str 中的每一个字符，
直到遇见字符 c，或者到达字符串末尾（遇见\0）。

返回值：返回在字符串 str 中第一次出现字符 c 的位置，
如果未找到该字符 c 则返回 NULL。
*/
char* strchr(const char* str, int c);





/*
C语言提供了几个标准库函数，可以将任意类型(整型、长整型、浮点型等)的数字转换为字符串，下面列举了各函数的方法及其说明。
● ltoa()：将长整型值转换为字符串。
● ultoa()：将无符号长整型值转换为字符串。
● gcvt()：将浮点型数转换为字符串，取四舍五入。
● ecvt()：将双精度浮点型值转换为字符串，转换结果中不包含十进制小数点。
● fcvt()：指定位数为转换精度，其余同ecvt()。

除此外，还可以使用sprintf系列函数把数字转换成字符串，其比itoa()系列函数运行速度慢

2. string/array to int/float
C/C++语言提供了几个标准库函数，可以将字符串转换为任意类型(整型、长整型、浮点型等)。
● atof()：将字符串转换为双精度浮点型值。
● atoi()：将字符串转换为整型值。
● atol()：将字符串转换为长整型值。
● strtod()：将字符串转换为双精度浮点型值，并报告不能被转换的所有剩余数字。
● strtol()：将字符串转换为长整值，并报告不能被转换的所有剩余数字。
● strtoul()：将字符串转换为无符号长整型值，并报告不能被转换的所有剩余数字。
*/

/*
提取字符串
从src start 位置提取长度为len的字符串到dst
*/
void substr(char dst[], char src[],int start,int len)
{
	char* sc = src+start;
	int n = strlen(sc);
	int i = 0;
	int **ret=NULL;
	//assert(dst != NULL );
	//assert(src != NULL );
    if(n < len)
    {
        len = n;
    }
    while(len)
    {
        dst[i] = sc[i];
        len--;
        i++;
    }
    dst[i] = '\0';
}


//字符串替换函数
// 参数说明:
// in， 源字符串
// out, 存放最后结果的字符串
// outlen，out最大的大小
// src，要替换的字符串
// dst，替换成什么字符串
char *strrpl(char *in, char *out, int outlen, const char *src, char *dst)
{
    char *p = in;
    unsigned int  len = outlen - 1;

    // 这几段检查参数合法性
    if((NULL == src) || (NULL == dst) || (NULL == in) || (NULL == out))
    {
        return NULL;
    }
    if((strcmp(in, "") == 0) || (strcmp(src, "") == 0))
    {
        return NULL;
    }
    if(outlen <= 0)
    {
        return NULL;
    }

    while((*p != '\0') && (len > 0))
    {
        if(strncmp(p, src, strlen(src)) != 0)
        {
            int n = strlen(out);

            out[n] = *p;
            out[n + 1] = '\0';

            p++;
            len--;
        }
        else
        {
            strcat(out, dst);
            p += strlen(src);
            len -= strlen(dst);
        }
    }

    return out;
}


void test_strrpl(void)
{
	char ss[] = "abcd";
	char out[32] = {'\0'};
	strrpl(ss,out,sizeof(out),"ab","ff");

	printf("%s\n",out);
}


/*
子序列
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

你可以认为 s 和 t 中仅包含英文小写字母。字符串 t 可能会很长（长度 ~= 500,000），而 s 是个短字符串（长度 <=100）。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

示例 1:
s = "abc", t = "ahbgdc"

返回 true.

示例 2:
s = "axc", t = "ahbgdc"

返回 false.

*/
bool isSubsequence(char * s, char * t){
	unsigned int i;
	unsigned int j;
	unsigned int s_size = strlen(s);
	unsigned int t_size = strlen(t);

    if(s_size == 0)
        return true;

	for(i = 0,j = 0; i< t_size;i++) {
		if(t[i] == s[j]){
			j++;
		}
        if(j == s_size) return true;
	}

	return false;
}



/*
C语言strrev()函数：字符串逆置（倒序、逆序）
*/
char* strrev(char* s)
{
    /* h指向s的头部 */
    char* h = s;
    char* t = s;
    char ch;

    /* t指向s的尾部 */
    while(*t++){};
    t--;    /* 与t++抵消 */
    t--;    /* 回跳过结束符'\0' */

    /* 当h和t未重合时，交换它们所指向的字符 */
    while(h < t)
    {
        ch = *h;
        *h++ = *t;    /* h向尾部移动 */
        *t-- = ch;    /* t向头部移动 */
    }

    return(s);
}


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
● itoa()：将整型值转换为字符串。
原型说明：

value：欲转换的数据。
string：目标字符串的地址。
radix：转换后的进制数，可以是10进制、16进制等，范围必须在 2-36。

功能：将整数value 转换成字符串存入string 指向的内存空间 ,radix 为转换时所用基数(保存到字符串中的数据的进制基数)。
返回值：函数返回一个指向 str，无错误返回。

*/
char *itoa( int value, char *string,int radix);


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
	switch(atoi(argv[1])) {
	case 1:
	str_to_hex_by_sscanf(argv[2]);
	break;
	case 2:
	str_to_hex_by_strtol(argv[2]);
	break;
	case 3:
	test_strrpl();
	break;
	default:
	break;
	}
}


