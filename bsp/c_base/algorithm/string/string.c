#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../flag_type.h"
#include "../math/math.h"

/*
isdigit

函数名称: isdigit

函数原型: int isdigit(char ch);

函数功能: 检查ch是否是数字(0-9)

函数返回: 是返回非0,否则返回0
*/
void digit2Str_sprintf(char *str, int digit)
{
	sprintf(str, "%d", digit);
	sprintf(str, "%x", digit);
}


int isdigit(char ch)
{
	if (ch < '0' || ch > '9')
		return 0;
	else
		return 1;
}


/*字符串转整形*/
int atoi(const char *str) {
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
		num = num * 10 + str[i] - '0';
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
#endif
}


void substr_test(void)
{
	char *src = "hello felix";
	char dst[128];
	memset(dst, '\0', sizeof(dst));
	substr(dst, src, 6, 100);
	printf("%s\n", dst);
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


void strrev_pos(char* s, int begin, int end)
{
	char* h = s + begin;
	char* t = s + end;

	if (begin == end)
		return;

	while(h < t) {
		swap(*h, *t);
		h++;
		t--;
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
void reverseWords(char* s, int sSize){
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
//char *strncpy(char *destinin, char *source, int maxlen);

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
	}else if(*s >= '0' && *s <= '9') {/*上面两个分支去掉就是纯数字子串*/
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


void max_num_in_string_test(void)
{
	char input[] = "q21u+231y-123.456789y-0.23";
	char output[1024];
	int ret = max_num_in_string(input,output);
	printf("%d:%s\n",ret,output);
}

/*
给定一个字符串 s ，找出 至多 包含两个不同字符的最长子串 t 。

示例 1:

输入: "eceba"
输出: 3
解释: t 是 "ece"，长度为3。
示例 2:

输入: "ccaabbb"
输出: 5
解释: t 是 "aabbb"，长度为5。

*/
int lengthOfLongestSubstringTwoDistinct(char * s){

	int sSize = strlen(s);
	if (sSize <= 2)
		return sSize;

	int left = 0;
	int max = 0;

	while( left + max < sSize) {
		int tempLeft = left;

		while(left < sSize && s[left] == s[tempLeft]) {
			left++;
		}

		int right = left;
		int tempRight = right;

		while(right < sSize && (s[right] == s[tempRight] || s[right] == s[tempLeft] )) {
			right++;
		}

		max = max > (right - tempLeft) ? max :(right - tempLeft);
		left = tempRight;
	}

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
给出 字符串 text 和 字符串列表 words, 返回所有的索引对 [i, j] 使得在索引对范围内的子字符串 text[i]...text[j]（包括 i 和 j）属于字符串列表 words。



示例 1:

输入: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
输出: [[3,7],[9,13],[10,17]]
示例 2:

输入: text = "ababa", words = ["aba","ab"]
输出: [[0,1],[0,2],[2,3],[2,4]]
解释:
注意，返回的配对可以有交叉，比如，"aba" 既在 [0,2] 中也在 [2,4] 中

*/
int cmp(const void *a,const void *b)
{
    int *ap = *(int **)a;
    int *bp = *(int **)b;

    if(ap[0] == bp[0])
        return ap[1] - bp[1];
    else
        return ap[0] - bp[0];
}

int** indexPairs(char * text, char ** words, int wordsSize, int* returnSize, int** returnColumnSizes){
    int i, j;
    int** res = (int **)malloc(sizeof(int *) * 1000);
    int cnt = 0;
    int len1 = strlen(text);

    for (i = 0; i < wordsSize; i++) {
        int len2 = strlen(words[i]);
        if(len2 > len1)
		continue;

	for (j = 0; j < len1 - len2 + 1; j++) {
            if (strncmp(text + j, words[i], strlen(words[i])) == 0) {
                res[cnt] = (int *)malloc(sizeof(int) * 2);
                res[cnt][0] = j;
                res[cnt][1] = j + strlen(words[i]) - 1;
                cnt++;
                //printf("j = %d endIdx = %d cnt = %d\n", j, j + strlen(words[i]) - 1, cnt);
            }
        }
	}

    qsort(res, cnt, sizeof(res[0]), cmp); // 二维数组排序
    *returnSize = cnt;
    returnColumnSizes[0] = (int *)malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; i++) {
        returnColumnSizes[0][i] = 2;
    }
    return res;
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

void test()
{

}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("argc err\n");
		return -1;
	}

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
	case 4:
		strtok_test();
	break;
	case 5: max_num_in_string_test();
	break;
	case 6: substr_test();
	break;
	case 7: test();
	break;
	default:
	break;
	}

	return 0;
}


