#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../flag_type.h"
#include "../math/math.h"

void digit2Str_sprintf(char *str, int digit)
{
	sprintf(str, "%d", digit);
	sprintf(str, "%x", digit);
}
/*
isdigit

函数名称: isdigit

函数原型: int isdigit(char ch);

函数功能: 检查ch是否是数字(0-9)

函数返回: 是返回非0,否则返回0
*/
int isdigit(char ch)
{
	if (ch < '0' || ch > '9')
		return 0;
	else
		return 1;
}

/*字符串转整形*/
int atoi(const char *str)
{
	int num = 0;
	int sign = 1;
	const int len = strlen(str);
	int i = 0;

	while (str[i] == ' ' && i < len)i++;

	if (str[i] == '+') i++;
	if (str[i] == '-') {
		sign = -1;
		i++;
	}

	for (; i < len; i++) {
		if (str[i] < '0' || str[i] > '9')
			break;
		if (num > INT_MAX / 10 ||  (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
			return sign == -1 ? INT_MIN : INT_MAX;
		}

		num = str[i] - '0' + num * 10;
	}
	return num * sign;
}

void str2digit_sscanf(char * str)
{
	int value;
	sscanf(str, "%x", &value);
	printf("0x%x\n",value);
}

void str2digit_strtol(char * str)
{
	char* p;
	long value = strtol(str, &p, 16);
	printf("0x%lx\n",value);
}

unsigned long str2digit(char *str, int len)
{
	unsigned long i, data = 0;

	for(i = 0; i < len; i++) {
		if (!isdigit(str[i]))
			return -1;
		data *= 10;
		data += str[i]-'0';
	}

	return data;
}



/*
#include <string.h>
查找子字符串
意义为 判断str2是否为str1的字串，
若是则返回str2在str1中首次出现的指针位置，
若不是返回NULL；
*/
char *strstr(const char *str1, const char *str2);


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
maxlen：表示复制的字符串长度
（c/c++）复制字符串source中的内容（字符，数字、汉字....）
到字符串destinin中，复制多少由maxlen的值决定。
如果source的前n个字符不含NULL字符，
则结果不会以NULL字符结束。
如果n<source的长度，只是将source的前n个字符复制到
destinin的前n个字符，不自动添加'\0'，
也就是结果destinin不包括'\0'，需要再手动添加一个'\0'。
如果source的长度小于n个字节，则以NULL填充
destinin直到复制完n个字节。
source和destinin所指内存区域不可以重叠且
destinin必须有足够的空间来容纳source的字符长度+'\0'。
*/
/*
char *strncpy(char *destinin, char *source, int maxlen);
destinin[maxlen] = '\0';
*/

/*
提取字符串
从src start 位置提取长度为len的字符串到dst
*/
void substr(char* dst, char* src, int start, int cpLen)
{
#if 0
    char* sc = src + start;
    int srcLen = strlen(sc);
    int i = 0;


    if (srcLen < cpLen) {
        cpLen = srcLen;
    }

    while (srcLen) {
        dst[i] = sc[i];
        srcLen--;
        i++;
    }
    dst[i] = '\0';
#else
	strncpy(dst, src + start, cpLen);
	dst[cpLen] = '\0';
#endif
}

char *strrpl(char *srcStr, char *dstStr, int dstSize, const char *oldSubStr, char *newSubStr)
{
	char *it = srcStr;
	unsigned int  len = dstSize - 1;

	if(oldSubStr == NULL ||newSubStr== NULL || srcStr == NULL || dstStr  == NULL || dstSize <= 0) {
		return NULL;
	}

	if((strcmp(srcStr, "") == 0) || (strcmp(oldSubStr, "") == 0)) {
		return NULL;
	}

	while(*it != '\0' && len > 0) {
		if(strncmp(it, oldSubStr, strlen(oldSubStr)) != 0) {
			int n = strlen(dstStr);
			dstStr[n] = *it;
			dstStr[n + 1] = '\0';
			it++;
			len--;
		} else {
			strcat(dstStr, newSubStr);
			it += strlen(oldSubStr);
			len -= strlen(newSubStr);
		}
	}

	return dstStr;
}

void strreplace(char *text, char *oldsubstr, char *newsubstr)
{
	int oldsublen = strlen(oldsubstr);
	int newsublen = strlen(newsubstr);
	char *temp = text;

	while ( (temp = strstr(temp, oldsubstr)) != NULL ) {
		memmove(temp + newsublen, temp + oldsublen, strlen(temp) - oldsublen + 1);
		memcpy(temp, newsubstr, newsublen);
		temp = temp + newsublen;
	}
}


/*
子序列
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

你可以认为 s 和 t 中仅包含英文小写字母。
字符串 t 可能会很长（长度 ~= 500,000），
而 s 是个短字符串（长度 <=100）。

字符串的一个子序列是原始字符串删除
一些（也可以不删除）字符而不改变剩
余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一
个子序列，而"aec"不是）。

示例 1:
s = "abc", t = "ahbgdc"

返回 true.

示例 2:
s = "axc", t = "ahbgdc"

返回 false.

*/
bool isSubsequence(char * s, char * t)
{
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

/*删除首尾空格*/
char* trim(char *a)
{
	char *p1 = a;
	char *p2 = a + strlen(a) - 1;
	int len;

	while (p1 <= p2 && *p1 == ' ') {
		p1++;
	}
	while (p2 >= p1 && *p2 == ' ') {
		p2--;
	}
/* 若字符串全为空格，
p1会移到p2的后面，那么如果p1>p2，返回空。*/
	len = (p2 < p1) ? 0 : (p2 - p1) + 1;
	p1[len] = '\0';
	return p1;
}

void deblank(char string[])
{
    int i=0;
    int j=0;
    while(string[j]!='\0'){
        if(string[j]!=' '||string[j+1]!=' '){
            string[i]=string[j];
            i++;
            j++;
        }
        else
        {
            string[i]=string[j+1];
            j++;
        }
    }
    string[i]='\0';
}

char * deblank_trim(char * str)
{
    char * left = str;//前面的指针，负责赋值
    char * right = str;//后面寻找非空格字符的指针

    while (*right != '\0') {
        if (*right != ' ') {
            if (left < right) {
                *left = *right;
            }
            left++;
        }

        if (*right == ' ' && *(right + 1) != ' ')//寻找到下一个单词时，对left的操作
        {
            *left = ' ';
            left++;
        }

        right++;
    }

    *left = '\0';
    return *str != ' ' ?str:(str + 1);//防止首单词之前有空格现象
}


void strrev_pos(char* s, int begin, int end)
{
	char* left = s + begin;
	char* right = s + end;

	if (begin == end)
		return;

	while(left < right) {
		swap(*left, *right);
		left++;
		right--;
	}
}


void strrev(char* s)
{
	strrev_pos(s, 0, strlen(s) -1);
}

/*
给定一个字符串，逐个翻转字符串中的每个单词。

示例：

输入: ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
输出: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
注意：

单词的定义是不包含空格的一系列字符
输入字符串中不会包含前置或尾随的空格
单词与单词之间永远是以单个空格隔开的

*/
void reverseWords(char* s, int sSize)
{
    	int len = 0;

	strrev_pos(s, 0, sSize -1);
	for (int i = 0; i < sSize; ) {
		len = 0;
		while ((i + len) < sSize && s[i + len] != ' ') {
			len++;
		}
		strrev_pos(s, i, i + len - 1);
		i = i + len + 1;
	}
}


size_t strlen(const char *str) {
	const char *s;
	for (s = str; *s; ++s) {}
	return(s - str);
}


char* strcpy(char *to, const char *from) {
    if(to == NULL && from == NULL)
		return 0;

    char *p = to;
    while ((*p++ = *from++) != '\0')
    ;
    return to;
}


/*利用或操作 | 和空格将英文字符转换为小写
('a' | ' ') = 'a'
('A' | ' ') = 'a'
*/

/*利用与操作 & 和下划线将英文字符转换为大写
('b' & '_') = 'B'
('B' & '_') = 'B'
*/

/*
利用异或操作 ^ 和空格进行英文字符大小写互换
('d' ^ ' ') = 'D'
('D' ^ ' ') = 'd'

大小写字母相差32,又因为异或重要特性:不进位加法,
所以大写字母和(1<<5)异或变成变成小写字母,
小写字母和(1<<5)异或变成大写字母*/
char *alpha_low_upper( char *Str )
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



/* 最长带+-符号 小数点的连续数字串*/
int max_num_in_string(char *inputstr, char *outputstr)
{
	int count=0;
	int numCnt = 0;
	int pointCnt = 0;
	//字符串中连续数字个数的最大值
	int max=0;
	//保存取得最大值的指针
	char *mPos;
	char *s = inputstr;
	int i = 0;

    while(*s != '\0') {
	if (count == 0 && (*s == '+' || *s == '-')) {
		count++;
	} else if (*s == '.' && numCnt > 0 && pointCnt == 0) {
		count++;
		pointCnt = 1;
	}else if(isdigit(*s)) {/*上面两个分支去掉就是纯数字子串*/
		count++;
		numCnt++;
	} else {
            if(count > max) {
                max = count;
		 /*s当前位置回退count字符到max子串开始位置*/
                mPos = s - count;
            }

		count = 0;
		numCnt = 0;
		pointCnt = 0;
        }

        s++;
    }

    //有可能字符串末尾取到最大值
    if(count>max) {
        max=count;
        mPos=s-max;
    }

#if 1
	memcpy(outputstr, mPos,max);
	outputstr[max] = '\0';
#else
	while(i<max) {
		*outputstr=*(mPos+i);
		outputstr++;
		i++;
	}

	*outputstr='\0';
#endif
    return max;
}


/*
函数原型：char * strtok (char *str, const char * delimiters);
参数：str，待分割的字符串（c-string）；
delimiters，分割符字符串。
该函数用来将字符串分割成一个个片段。
参数str指向欲分割的字符串，
参数delimiters则为分割字符串中包含的所有字符。
当strtok()在参数s的
字符串中发现参数delimiters中包涵的分割字符时，
则会将该字符改为\0 字符。在第一次调用时，
strtok()必需给予参数s字符串，
往后的调用则将参数s设置成NULL。
每次调用成功则返回指向被分割出片段的指针。
需要注意的是，使用该函数进行字符串分割时，
会破坏被分解字符串的完整，
调用前和调用后的s已经不一样了。
第一次分割之后，
原字符串str是分割完成之后的第一个字符串，
剩余的字符串存储在一个静态变量中，
因此多线程同时访问该静态变量时，
则会出现错误

strtok_r函数是linux下分割字符串的安全函数，函数声明如下：
char *strtok_r(char *str, const char *delim, char **saveptr);
该函数也会破坏带分解字符串的完整性，
但是其将剩余的字符串保存在saveptr变量中，保证了安全性。
例子：
*/


/*
str 一直是"ab"
iterator 迭代器成员依次是"ab"/"cd"/"ef";iterator只取出有效字段
p 剩余子串依次是"cd,ef"/"ef"/"NULL"
*/
void strtok_test(void)
{
	char str[]="ab,cd,ef";
	char *iterator;
	char *p;
	iterator = strtok_r(str, ",", &p);
	while(iterator != NULL) {
		/*iterator*/
		iterator = strtok_r(NULL, ",", &p);
	}
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

#include <ctype.h>
/*
isalpha

函数名称: isalpha

函数原型:

函数功能: 检查ch是否是字母.

函数返回: 是字母返回非0(在vs2015中为2) ,否则返回 0.
*/
int isalpha(char ch);


/*

iscntrl

函数名称: iscntrl

函数原型: int iscntrl(int ch);

函数功能: 检查ch是否控制字符(其ASCII码在0和0x1F之间,数值为 0-31).

函数返回: 是返回非0,否则返回 0.

参数说明:

*/



/*

isgraph

函数名称: isgraph

函数原型: int isgraph(int ch);

函数功能: 检查ch是否可显示字符(其ASCII码在0x21到0x7E之间),不包括空格

函数返回: 是返回非0,否则返回0


islower

函数名称: islower

函数原型: int islower(int ch);

函数功能: 检查ch是否小写字母(a-z)

函数返回: 是返回非0,否则返回0

参数说明:

所属文件: <ctype.h>

isupper

函数名称: isupper

函数原型: int isupper(int ch);

函数功能: 检查ch是否是大写字母(A-Z)

函数返回: 是返回非0,否则返回0


tolower

函数名称: tolower

函数原型: int tolower(int ch);

函数功能: 将ch字符转换为小写字母

函数返回: 返回ch所代表的字符的小写字母


toupper

函数名称: toupper

函数原型: int toupper(int ch);

函数功能: 将ch字符转换成大写字母

函数返回: 与ch相应的大写字母

isalnum

函数名称: isalnum

函数原型: int isalnum(int ch);

函数功能: 检查ch是否是字母或数字

函数返回: 是字母或数字返回非0,否则返回0


isprint

函数名称: isprint

函数原型: int isprint(int ch);

函数功能: 检查ch是否是可打印字符(包括空格),其ASCII码在0x20到0x7E之间

函数返回: 是返回非0,否则返回0

*/


/*

函数名称: ispunct

函数原型: int ispunct(int ch);

函数功能: 检查ch是否是标点字符(不包括空格),
即除字母,数字和空格以外的所有可打印字符

函数返回: 是返回非0,否则返回0
*/
int ispunct(int ch);


/*
isspace

函数名称: isspace

函数原型: int isspace(int ch);

函数功能: 检查ch是否是空格符和跳格符(控制字符)或换行符

函数返回: 是返回非0,否则返回0

参数说明:

所属文件: <ctype.h>

isxdigit

函数名称: isxdigit

函数原型: int isxdigit(int ch);

函数功能: 检查ch是否是一个16进制数学字符(即0-9,或A-F,或a-f)

函数返回: 是返回非0,否则返回0

参数说明:

所属文件: <ctype.h>

isascii

函数名称: isascii

函数原型: int isascii(int ch)

函数功能: 测试参数是否是ASCII码0-127

函数返回: 是返回非0,否则返回0

参数说明: ch-被测参数

*/


snprintf
/*
(1) 如果格式化后的字符串长度 < size，则将此字符串全部复制到str中，并给其后添加一个字符串结束符('\0')；
(2) 如果格式化后的字符串长度 >= size，则只将其中的(size-1)个字符复制到str中，并给其后添加一个字符串结束符('\0')，返回值为欲写入的字符串长度。
*/
strncat
//区别