
void delChar(char *s, int num)
{
	char *p = s;
	char *q = s;
	for (int i = 0; i < strlen(s); i++) {
		if (i == num) {
			q++;
		}
		*(p++) = *(q++);
	}

	*p = '\0';
}

/*
memset的头文件是<string.h>  why ?
int array[10];
memset(array,1,10);//或者memset(array,1,sizeof(array))，都是不对的！

memset函数使用说明中提到的是按照byte来填充。
char arr[10]; memset(arr,'a',10);
由于char只占一个字节(byte)，因此函数的结果是将连续的10个字节都填充为'a'。这是我们所期待的结果！
*/
void * memset(void *s, int c, size_t n);

/*
(1) 如果格式化后的字符串长度 < size，
则将此字符串全部复制到str中，
并给其后添加一个字符串结束符('\0')；
(2) 如果格式化后的字符串长度 >= size，
则只将其中的(size-1)个字符复制到str中，
并给其后添加一个字符串结束符('\0')，
返回值为欲写入的字符串长度。
返回值为字符串的真实长度。

一定有'\0';最大拷贝size -1长度用户数据
*/
int snprintf ( char * str, size_t size, const char * format, ... );


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
int atoi(char * str){
	long int num = 0;
	int sign = 1;
	const int len = strlen(str);
	int i = 0;

	while (str[i] == ' ' && i < len)
		i++;

	if (str[i] == '+')
		i++;
	else if (str[i] == '-') {
		sign = -1;
		i++;
	}

	for (; i < len; i++) {
		if (str[i] < '0' || str[i] > '9')//if (!isdigit(str[i]))
			break;
		//if (num > INT_MAX / 10 ||  (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
		//	return sign == -1 ? INT_MIN : INT_MAX;
		//}

		num = num * 10 + str[i] - '0';
		if ((int)num != num) {
			return sign == -1 ? INT_MIN : INT_MAX;
		}
	}

	return (int)(num * sign);

}
long int atol(char * str);//将字符串转换为长整型值。
float atof(char * str);//将字符串转换为双精度浮点型值。

void str2digit_sscanf(char * str)
{
	int value;
	sscanf(str, "%x", &value);
	printf("0x%x\n",value);
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

char *strrpl(char *dstStr, int dstSize, char *srcStr, const char *oldSubStr, char *newSubStr)
{
	char *it = srcStr;
	unsigned int  len = dstSize - 1;

	if(oldSubStr == NULL ||newSubStr == NULL || srcStr == NULL
		|| dstStr  == NULL || dstSize <= 0) {
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


/*
392. 判断子序列
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
你可以认为 s 和 t 中仅包含英文小写字母。
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
/*删除多余空格*/
char * deblank(char * str)
{
    char *left = str;//前面的指针，负责赋值
    char *right = str;//后面寻找非空格字符的指针

    while (*right != '\0') {
        if (*right != ' ') {
            if (left < right) {
                *left = *right;
            }
            left++;
        }

//寻找到下一个单词时，对left的操作
        if (*right == ' ' && *(right + 1) != ' ') {
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


size_t strlen(const char *str)
{
	const char *s;
	for (s = str; *s; ++s) {}
	return(s - str);
}


char* strcpy(char *dest, const char *src)
{
    if(dest == NULL || src == NULL)
		return NULL;

    char *p = dest;
    while ((*p++ = *src++) != '\0');
    return dest;
}
/*当src len 大于maxlen 则截断复制maxlen到dest,
dest尾部没有结束符'\0
dest[maxlen] = '\0''*/
char *strncpy(char *dest, char *src, int maxlen);
/*
提取字符串
从src start 位置提取长度为len的字符串到dst
*/
void substr(char* dst, char* src, int start, int cpLen)
{
	strncpy(dst, src + start, cpLen);
	dst[cpLen] = '\0';
}

char * strncat(char *dest, const char *src, size_t n);

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

/*
isalpha
函数名称: isalpha
函数原型:
函数功能: 检查ch是否是字母.
函数返回: 是字母返回非0(在vs2015中为2) ,否则返回 0.
*/
int isalpha(char ch);
/*
islower
函数名称: islower
函数原型: int islower(int ch);
函数功能: 检查ch是否小写字母(a-z)
函数返回: 是返回非0,否则返回0
参数说明:
所属文件: <ctype.h>
*/
int islower(int ch);
/*
isupper
函数名称: isupper
函数原型: int isupper(int ch);
函数功能: 检查ch是否是大写字母(A-Z)
函数返回: 是返回非0,否则返回0
*/
int isupper(int ch);
/*
tolower
函数名称: tolower
函数原型: int tolower(int ch);
函数功能: 将ch字符转换为小写字母
函数返回: 返回ch所代表的字符的小写字母
*/
int tolower(int ch);
/*
toupper
函数名称: toupper
函数原型: int toupper(int ch);
函数功能: 将ch字符转换成大写字母
函数返回: 与ch相应的大写字母
*/
int toupper(int ch);
/*
isalnum
函数名称: isalnum
函数原型: int isalnum(int ch);
函数功能: 检查ch是否是字母或数字
函数返回: 是字母或数字返回非0,否则返回0
*/
int isalnum(int ch);
/*
isspace
函数名称: isspace
函数原型: int isspace(int ch);
函数功能: 检查ch是否是空格符和跳格符(控制字符)或换行符
函数返回: 是返回非0,否则返回0
参数说明:
所属文件: <ctype.h>
*/
 int isspace(int ch);
 /*
isxdigit
函数名称: isxdigit
函数原型: int isxdigit(int ch);
函数功能: 检查ch是否是一个16进制数学字符(即0-9,或A-F,或a-f)
函数返回: 是返回非0,否则返回0
参数说明:
所属文件: <ctype.h>
*/
int isxdigit(int ch);
 /*
isascii
函数名称: isascii
函数原型: int isascii(int ch)
函数功能: 测试参数是否是ASCII码0-127
函数返回: 是返回非0,否则返回0
参数说明: ch-被测参数
*/
int isascii(int ch);

/*
除了字母和十进制数字以外的所有图形字符都会被判定为标点符号；
*/
int ispunct ( int c );

