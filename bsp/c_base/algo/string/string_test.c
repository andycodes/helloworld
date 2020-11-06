int expandAroundCenter(char *s, int left, int right)
{
    int L = left, R = right;
    while (L >= 0 && R < strlen(s) && s[L] == s[R]) {
        L--;
        R++;
    }
    return R - L - 1;
}

/*中心扩展算法*/
char * longestPalindrome(char * s)
{
	if (s == NULL || strlen(s) < 1)
	return "";

	if (strlen(s) == 1)
		return s;

	int start = 0, end = 0;
	int mlen = 0;
	for (int i = 0; i < strlen(s); i++) {
		int len1 = expandAroundCenter(s, i, i);//一个元素为中心
		int len2 = expandAroundCenter(s, i, i + 1);//两个元素为中心
		mlen = fmax(fmax(len1, len2), mlen);
		if (mlen > end - start + 1) {
			start = i - (mlen - 1) / 2;
			end = i + mlen / 2;
		}
	}

	char *ret = strdup(s + start);
	ret[mlen] = '\0';
	return ret;
}

/*
670. 最大交换
难度中等77
给定一个非负整数，你至多可以交换一次数字中的任意两位。
返回你能得到的最大值。
示例 1 :
输入: 2736
输出: 7236
解释: 交换数字2和数字7。
示例 2 :
输入: 9973
输出: 9973
解释: 不需要交换。

*/
static int cmp(const void *a, const void *b)
{
    return *((char*)b) - *((char*)a);
}

int maximumSwap(int num)
{
	if (num == 0) {
		return 0;
	}

	char str0[16] = {0};
	char sortstr[16] = {0};

	sprintf(str0, "%d", num);
	sprintf(sortstr, "%d", num);

	int len = (int) strlen(sortstr);

	qsort(sortstr, len, sizeof(char), cmp);

	for (int i = 0; i < len; i++) {
		if (sortstr[i] != str0[i]) {
			char *p = strrchr(&str0[i], sortstr[i]);
			*p = str0[i];
			str0[i] = sortstr[i];
			break;
		}
	}

	return atoi(str0);
}


/*
43. 字符串相乘
难度中等329
给定两个以字符串形式表示的非负整数 num1 和 num2，
返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
示例 1:
输入: num1 = "2", num2 = "3"
输出: "6"
示例 2:
输入: num1 = "123", num2 = "456"
输出: "56088"

*/
char * multiply(char * num1, char * num2)
{
	if (num1[0] == '0' || num2[0] == '0')
		return "0";

	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int dp[len1 + len2 + 1];
	memset(dp, 0, sizeof(dp));
	//算出错位相乘的乘积每个元素的数字
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			dp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
		}
	}
/*
从数组的尾部开始遍历，将第i位的高位通过/累加到第i-1位，
然后通过%求余获得当前位的数字。
*/
	for (int i = len1 + len2; i > 0; i--) {
		if (dp[i] < 10)
			continue;
		dp[i - 1] += dp[i] / 10;
		dp[i] %= 10;
	}

	char *ret = (char *)calloc(1024, sizeof(char));
	for (int i = 0, j = 0;  i < len1 + len2; i++) {
		// 排除起始开始的'0'直到第一个非0出现
		if ((j == 0) && (dp[i] == 0)) {
			continue;
		}
		ret[j++] = dp[i] + '0';
	}

	return ret;
}

/*
161. 相隔为 1 的编辑距离
难度中等27
给定两个字符串 s 和 t，判断他们的编辑距离是否为 1。
注意：
满足编辑距离等于 1 有三种可能的情形：
1.	往 s 中插入一个字符得到 t
2.	从 s 中删除一个字符得到 t
3.	在 s 中替换一个字符得到 t
示例 1：
输入: s = "ab", t = "acb"
输出: true
解释: 可以将 'c' 插入字符串 s 来得到 t。
*/
bool isOneEditDistance(char * s, char * t)
{
    int ns=strlen(s),nt=strlen(t);
    if(ns>nt)
        return isOneEditDistance(t,s);
    if(nt-ns>1)return 0;
    int replace=0;
    for(int i=0;i<ns;i++){
        if(s[i]!=t[i]){
            if(nt!=ns)
              //  return (s[i] ==t.substr(i+1));
			return !strcmp(s + i, t + i + 1);
            //else return (i==ns-1)||(s.substr(i+1)==t.substr(i+1));
		else return (i==ns-1)||(!strcmp(s + i+1, t +i+1));
        }
    }
    return nt!=ns;
}

/*
459. 重复的子字符串
难度简单243
给定一个非空的字符串，判断它是否可以由它的一个子串重
复多次构成。给定的字符串只含有小写英文字母，并且长度
不超过10000。
示例 1:
输入: "abab"
输出: True
解释: 可由子字符串 "ab" 重复两次构成。
示例 2:
输入: "aba"
输出: False
*/
bool repeatedSubstringPattern(char * s)
{
	int len = strlen(s);
	char cmp[len * 2];
	memset(cmp, 0, sizeof(cmp));

	memcpy(cmp, s + 1, len);
	strncat(cmp, s, len - 1);
	bool ret = strstr(cmp, s);
	return ret;
}

/*
214. 最短回文串
难度困难176
给定一个字符串 s，你可以通过在字符串前面添加字符将其转
换为回文串。找到并返回可以用这种方式转换的最短回文串。
示例 1:
输入: "aacecaaa"
输出: "aaacecaaa"
示例 2:
输入: "abcd"
输出: "dcbabcd"


*/
//判断是否是回文串, 传入字符串的范围
bool isPalindromic(char *s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

char * shortestPalindrome(char * s)
{
	int slen = strlen(s);
	int end = slen - 1;
    //找到回文串的结尾, 用 end 标记
    for (; end > 0; end--) {
        if (isPalindromic(s, 0, end)) {
            break;
        }
    }


    //将末尾的几个倒置然后加到原字符串开头
	char *res = (char *)calloc(2 * slen + 1, sizeof(char));
	int j = 0;
	for (int i = slen - 1; i > end; i--) {
		res[j++] = s[i];
	}

	strcat(res, s);
	return res;
}

/*
564. 寻找最近的回文数
难度困难70
给定一个整数 n ，你需要找到与它最近的回文数（不包括自身）。
"最近的"定义为两个整数差的绝对值最小。
示例 1:
输入: "123"
输出: "121"
注意:
1.	n 是由字符串表示的正整数，其长度不超过18。
2.	如果有多个结果，返回最小的那个。
通过次数2,444
提交次数15,226
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE    18
typedef long long int64;

static int64 CalcHighHalfVal(char *n)
{
    char high_half[MAX_SIZE / 2 + 2];
    int  inputlen, halflen;

    inputlen = strlen(n);
    halflen = (inputlen + 1) / 2;
    strncpy(high_half, n, halflen);
    high_half[halflen] = '\0';

    return atoll(high_half);
}

/* 根据输入数字的高半部分hhalf，计算高半部分的回文数字。lowhalflen表示需要补齐的低半部分长度 */
static int64 PalindByHighHalf(int64 hhalfval, int lowhalflen)
{
    int halflen, i;
    char buff[MAX_SIZE + 2];

    if (hhalfval == 0) {
        /* 10~19之间的数字，减1后的回文数字固定为9 */
        return 9;
    }

    snprintf(buff, sizeof(buff), "%lld", hhalfval);
    halflen = strlen(buff);

    if (lowhalflen <= halflen) {
        for (i = 0; i < lowhalflen; i++) {
            buff[halflen + lowhalflen - 1 - i] = buff[i];
        }
    } else {
        /* 例如输入数为1000，前半部分为10，当计算减1时变成9，此时lowhalflen为2，halflen为1，出现低半部分长度大于高半部分的情况
            此时就需要对低半部分全部填充9 */
        for (i = 0; i < lowhalflen; i++) {
            buff[halflen + i] = '9';
        }
    }
    buff[halflen + lowhalflen] = '\0';

    return atoll(buff);
}


static char strbuff[MAX_SIZE + 2];
char *nearestPalindromic(char *n)
{
    int64 inputval, outval, outval0, outval1;
    int64 halfval;
    int  inputlen, halflen;

    inputval = atoll(n);
    if (inputval <= 10) {
        outval = inputval - 1;
        snprintf(strbuff, sizeof(strbuff), "%lld", outval);
        return strbuff;
    }

    inputlen = strlen(n);
    halflen = (inputlen + 1) / 2;
    halfval = CalcHighHalfVal(n);

    outval1 = PalindByHighHalf(halfval, inputlen - halflen);
    if (outval1 > inputval) {
        outval0 = PalindByHighHalf(halfval - 1, inputlen - halflen);
    } else if (outval1 < inputval){
        outval0 = PalindByHighHalf(halfval + 1, inputlen - halflen);
    } else {
        outval0 = PalindByHighHalf(halfval - 1, inputlen - halflen);
        outval1 = PalindByHighHalf(halfval + 1, inputlen - halflen);
    }

    outval = ABS(inputval - outval0) < ABS(inputval - outval1) ? outval0 : outval1;
    outval = ABS(inputval - outval0) == ABS(inputval - outval1) ? MIN(outval0, outval1) : outval;

    snprintf(strbuff, sizeof(strbuff), "%lld", outval);
    return strbuff;
}

/*
696. 计数二进制子串
给定一个字符串 s，计算具有相同数量0和1的非空(连续)子字符串的数量，并且这些子字符串中的所有0和所有1都是组合在一起的。

重复出现的子串要计算它们出现的次数。

示例 1 :

输入: "00110011"
输出: 6
解释: 有6个子串具有相同数量的连续1和0：“0011”，“01”，“1100”，“10”，“0011” 和 “01”。

请注意，一些重复出现的子串要计算它们出现的次数。

另外，“00110011”不是有效的子串，因为所有的0（和1）没有组合在一起。
*/
int countBinarySubstrings(char* s) {
    int n = strlen(s);
    int counts[n], counts_len = 0;
    memset(counts, 0, sizeof(counts));
    int ptr = 0;
    while (ptr < n) {
        char c = s[ptr];
        int count = 0;
        while (ptr < n && s[ptr] == c) {
            ++ptr;
            ++count;
        }
        counts[counts_len++] = count;
    }
    int ans = 0;
    for (int i = 1; i < counts_len; ++i) {
        ans += fmin(counts[i], counts[i - 1]);
    }
    return ans;
}

int countBinarySubstrings(char* s) {
    int ptr = 0, n = strlen(s), last = 0, ans = 0;
    while (ptr < n) {
        char c = s[ptr];
        int count = 0;
        while (ptr < n && s[ptr] == c) {
            ++ptr;
            ++count;
        }
        ans += fmin(count, last);
        last = count;
    }
    return ans;
}

/*
541. 反转字符串 II
给定一个字符串 s 和一个整数 k，你需要对从字符串开头算起的每隔 2k 个字符的前 k 个字符进行反转。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。


示例:

输入: s = "abcdefg", k = 2
输出: "bacdfeg"
*/
char * reverseStr(char * s, int k)
{
        for (int start = 0; start < strlen(s); start += 2 * k) {
            int i = start, j = fmin(start + k - 1, strlen(s) - 1);
            while (i < j) {
                char tmp = s[i];
                s[i++] = s[j];
                s[j--] = tmp;
            }
        }
        return s;
}

/*
38. 外观数列
给定一个正整数 n ，输出外观数列的第 n 项。

「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。

你可以将其视作是由递归公式定义的数字字符串序列：

countAndSay(1) = "1"
countAndSay(n) 是对 countAndSay(n-1) 的描述，然后转换成另一个数字字符串。
前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221
第一项是数字 1
描述前一项，这个数是 1 即 “ 一 个 1 ”，记作 "11"
描述前一项，这个数是 11 即 “ 二 个 1 ” ，记作 "21"
描述前一项，这个数是 21 即 “ 一 个 2 + 一 个 1 ” ，记作 "1211"
描述前一项，这个数是 1211 即 “ 一 个 1 + 一 个 2 + 二 个 1 ” ，记作 "111221"
*/
/* 尾递归 */
char *countHelper(char *s, int n)
{
    if (n == 1)
        return s;
    else
    {
        //求下一个数
        int count;
        char ch[10000];
        char *p = ch;
        //一直读数
        while (*s!='\0')
        {
            count = 1;
            //如果一直是同一个数
            while (*s==*(s+1))
            {
                count++;
                s++;
            }
            //下一个数更新
            *p++ = (char)(count+'0');
            *p++ = *s++;
        }
        return countHelper(ch, n - 1);
    }
}

char *countAndSay(int n)
{
    return countHelper("1", n);
}

/*
556. 下一个更大元素 III
给定一个32位正整数 n，你需要找到最小的32位整数，其与 n 中存在的位数完全相同，并且其值大于n。如果不存在这样的32位整数，则返回-1。

示例 1:

输入: 12
输出: 21
示例 2:

输入: 21
输出: -1
*/
void Quick_sort(int *p, int left, int right){//快速排序--降序--递归版
	if(left < right){
		int l = left;
		int r = right;
		int key = p[l];
		while(l < r){//l == r 相遇时跳出
			while(l < r && p[r] < key){//从右往左找大于/等于key的数
				--r;
			}
			p[l] = p[r];
			while(l < r && p[l] >= key){//从左往右找小于key的数
				++l;
			}
			p[r] = p[l];
		}
		p[l] = key;
		Quick_sort(p, left, l - 1);//递归调用
		Quick_sort(p, r + 1, right);
    }
}

int nextGreaterElement(int n){
    const int over = 2147483647;//2^(31)-1
    int res = 0;
    int flag = -1;//反转点
    int stack[32];//顺序栈
    int top = -1;
    for (; n != 0; n /= 10){
        stack[++top] = n % 10;//按低位->高位依次入栈
    }
    for (int i = 0; i < top; ++i){
        if (stack[i+1] < stack[i]){//寻找是否存在反转点
            flag = i+1;//反转点
            break;
        }
    }
    if (flag != -1){//有反转点
        for (int i = 0; i < flag; ++i){//遍历反转点之前的低位
            if (stack[i] > stack[flag]){//找到一位大于反转点的最小的数字
                int tmp = stack[flag];//两者交换
                stack[flag] = stack[i];
                stack[i] = tmp;
                break;
            }
        }
        Quick_sort(stack, 0, flag-1);//将反转点之前的低位->反转点高位按降序排列,组成最小的数字
        for (; top > -1; --top){//全部出栈组成新的数
            if ( res > over/10 || (res == over/10 && stack[top] > 7) ){//数值溢出
                return -1;//不存在这样的32位整数
            }
            res = stack[top] + res*10;
        }
    }
    else {//无反转点，该数低位->高位是升序的，不存在有符合题意的数
        res = -1;
    }
    return res;
}

/*
385. 迷你语法分析器
给定一个用字符串表示的整数的嵌套列表，实现一个解析它的语法分析器。

列表中的每个元素只可能是整数或整数嵌套列表

提示：你可以假定这些字符串都是格式良好的：

字符串非空
字符串不包含空格
字符串只包含数字0-9、[、-、,、]


示例 1：

给定 s = "324",

你应该返回一个 NestedInteger 对象，其中只包含整数值 324。
*/
/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Initializes an empty nested list and return a reference to the nested integer.
 * struct NestedInteger *NestedIntegerInit();
 *
 * // Return true if this NestedInteger holds a single integer, rather than a nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Set this NestedInteger to hold a single integer.
 * void NestedIntegerSetInteger(struct NestedInteger *ni, int value);
 *
 * // Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 * void NestedIntegerAdd(struct NestedInteger *ni, struct NestedInteger *elem);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 */


// find number and return next char pointer
char *GetNum(char *s, int *num)
{
    *num = 0;
    int neg = 1;
    if (*s == '-') {
        neg = -1;
        ++s;
    }
    while (*s >= '0' && *s <= '9') {
        *num = *num * 10 + *s++ - '0';
    }
    *num *= neg;
    return s;
}

// find the corresponding ']' and return next char pointer, s starts with '['
char *FindBracket(char *s) {
    ++s;
    for (int i = 1; i > 0; ++s) {
        if (*s == '[')
            ++i;
        else if (*s == ']')
            --i;
    }
    return s;
}

struct NestedInteger *deserialize(char *s) {
    if (*s != '[') {
        int n;
        GetNum(s, &n);
        struct NestedInteger *nestInt = NestedIntegerInit();
        NestedIntegerSetInteger(nestInt, n);
        return nestInt;
    }
    int bracket = 1;
    ++s;
    struct NestedInteger *ret = NestedIntegerInit();
    while (*s != ']') {
        if (*s == ',') {
            ++s;
        } else if (*s == '-' || (*s >= '0' && *s <= '9')) {
            int n;
            s = GetNum(s, &n);
            struct NestedInteger *nestInt = NestedIntegerInit();
            NestedIntegerSetInteger(nestInt, n);
            NestedIntegerAdd(ret, nestInt);
        } else {
            struct NestedInteger *nestInt = deserialize(s);
            NestedIntegerAdd(ret, nestInt);
            s = FindBracket(s);
        }
    }
    return ret;
}
