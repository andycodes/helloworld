

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
1065
字符串的索引对
给出 字符串 text 和 字符串列表 words, 返回所有的索引对 [i, j]
使得在索引对范围内的子字符串 text[i]...text[j]（包括 i 和 j）
属于字符串列表 words。
示例 1:
输入: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
输出: [[3,7],[9,13],[10,17]]
示例 2:
输入: text = "ababa", words = ["aba","ab"]
输出: [[0,1],[0,2],[2,3],[2,4]]
解释:
注意，返回的配对可以有交叉，比如，"aba" 既在 [0,2] 中也
在 [2,4] 中

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

int** indexPairs(char * text, char ** words, int wordsSize,
	int* returnSize, int** returnColumnSizes)
{
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
12. 整数转罗马数字
难度中等326
罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，
即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
通常情况下，罗马数字中小的数字在大的数字的右边。
但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字
5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。
同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下
六种情况：
"	I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
"	X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
"	C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个整数，将其转为罗马数字。
输入确保在 1 到 3999 的范围内。
示例 1:
输入: 3
输出: "III"
示例 2:
输入: 4
输出: "IV"
示例 3:
输入: 9
输出: "IX"
示例 4:
输入: 58
输出: "LVIII"
解释: L = 50, V = 5, III = 3.
示例 5:
输入: 1994
输出: "MCMXCIV"
解释: M = 1000, CM = 900, XC = 90, IV = 4.

*/

struct Map {
	int num;
	char *lm;
};

char * intToRoman(int num)
{
	struct Map map[13];
	map[0].num = 1;
	map[0].lm = "I";
	map[1].num = 4;
	map[1].lm = "IV";
	map[2].num = 5;
	map[2].lm = "V";
	map[3].num = 9;
	map[3].lm = "IX";
	map[4].num = 10;
	map[4].lm = "X";
	map[5].num = 40;
	map[5].lm = "XL";
	map[6].num = 50;
	map[6].lm = "L";
	map[7].num = 90;
	map[7].lm = "XC";
	map[8].num = 100;
	map[8].lm = "C";
	map[9].num = 400;
	map[9].lm = "CD";
	map[10].num = 500;
	map[10].lm = "D";
	map[11].num = 900;
	map[11].lm = "CM";
	map[12].num = 1000;
	map[12].lm = "M";

	char *ret = (char *)calloc(1024, sizeof(char));
	for (int i = 0; i < 13; i++) {
		int cur = num / map[12 - i].num;
		while(cur--) {
			strcat(ret, map[12 - i].lm);
		}

		num %=  map[12 - i].num;
	}

	return ret;
}

/*
443. 压缩字符串
难度简单119
给定一组字符，使用原地算法将其压缩。
压缩后的长度必须始终小于或等于原数组长度。
数组的每个元素应该是长度为1 的字符（不是 int 整数类型）。
在完成原地修改输入数组后，返回数组的新长度。

进阶：
你能否仅使用O(1) 空间解决问题？

示例 1：
输入：
["a","a","b","b","c","c","c"]

输出：
返回 6 ，输入数组的前 6 个字符应该是：["a","2","b","2","c","3"]

说明：
"aa" 被 "a2" 替代。"bb" 被 "b2" 替代。"ccc" 被 "c3" 替代。

*/
int compress(char* chars, int charsSize){
    int write = 0;
    char buf[1000];
    for(int read=0, anchor=0;read<charsSize;anchor=read)
    {
        while(read<charsSize&&chars[read]==chars[anchor])
            read++;
        chars[write++] = chars[anchor];
        if(read-anchor==1)
            continue;
        sprintf(buf,"%d",read-anchor);
        for(int i=0;i<strlen(buf);i++)
            chars[write++] = buf[i];
    }
    return write;
}

/*
271. 字符串的编码与解码
请你设计一个算法，可以将一个 字符串列表 编码成为一个 字符串。这个编码后的字符串是可以通过网络进行高效传送的，并且可以在接收端被解码回原来的字符串列表。

1 号机（发送方）有如下函数：

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
2 号机（接收方）有如下函数：

vector<string> decode(string s) {
  //... your code
  return strs;
}
1 号机（发送方）执行：

string encoded_string = encode(strs);
2 号机（接收方）执行：

vector<string> strs2 = decode(encoded_string);
此时，2 号机（接收方）的 strs2 需要和 1 号机（发送方）的 strs 相同。

请你来实现这个 encode 和 decode 方法。

注意：

因为字符串可能会包含 256 个合法 ascii 字符中的任何字符，所以您的算法必须要能够处理任何可能会出现的字符。
请勿使用 “类成员”、“全局变量” 或 “静态变量” 来存储这些状态，您的编码和解码算法应该是非状态依赖的。
请不要依赖任何方法库，例如 eval 又或者是 serialize 之类的方法。本题的宗旨是需要您自己实现 “编码” 和 “解码” 算法。
*/

/** Encodes a list of strings to a single string */
char* encode(char** strs, int strsSize) {
	char *out = (char *)calloc(102400, sizeof(char));
	for (int i = 0; i < strsSize; i++) {
		sprintf(out + strlen(out), "%08d%s", strlen(strs[i]), strs[i]);
	}
    //printf("[e]%s\n",out);
	return out;
}

/**
 * Decodes a single string to a list of strings.
 *
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//00000005Hello00000005World
char** decode(char* s, int* returnSize) {
	char *p = s;
	*returnSize = 0;
	char **out = (char **)calloc(1024, sizeof(char*));
	while(*p != '\0') {
		int len;
		char str[16];
		memset(str, 0, sizeof(str));
		strncpy(str, p, 8);//没有结束符
		len = atoi(str);
		out[*returnSize] = (char *)calloc(len + 1, sizeof(char));
		strncpy(out[*returnSize], p + 8, len);
		p += len + 8;
		(*returnSize)++;
	}

	return out;
}

// Your functions will be called as such:
// char* s = encode(strs, strsSize);
// decode(s, &returnSize);

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
给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。给定的字符串只含有小写英文字母，并且长度不超过10000。
示例 1:
输入: "abab"

输出: True

解释: 可由子字符串 "ab" 重复两次构成。
示例 2:
输入: "aba"

输出: False

*/

bool repeatedSubstringPattern(char * s){
    int len = strlen(s);
    char * c = (char *) malloc(sizeof(char) * (len * 2));
    memcpy(c, s + 1, len);
    strncat(c, s, len - 1);
    bool ret = strstr(c, s);
    free(c);
    return ret;
}

/*
1023. 驼峰式匹配
难度中等17
如果我们可以将小写字母插入模式串 pattern 得到待查询项 query，那么待查询项与给定模式串匹配。（我们可以在任何位置插入每个字符，也可以插入 0 个字符。）
给定待查询列表 queries，和模式串 pattern，返回由布尔值组成的答案列表 answer。只有在待查项 queries[i] 与模式串 pattern 匹配时， answer[i] 才为 true，否则为 false。

示例 1：
输入：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
输出：[true,false,true,true,false]
示例：
"FooBar" 可以这样生成："F" + "oo" + "B" + "ar"。
"FootBall" 可以这样生成："F" + "oot" + "B" + "all".
"FrameBuffer" 可以这样生成："F" + "rame" + "B" + "uffer".
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool isMatch(const char* query, const char* pattern){
    while (*pattern != 0) {
        if (*query == *pattern) {
            query++;
            pattern++;
        } else {
            if (isupper(*query) || *query == 0)
                return false;
            query++;
        }
    }
    while (*query != 0) {
        if (isupper(*query))
            return false;
        query++;
    }
    return true;
}

bool* camelMatch(char ** queries, int queriesSize, char * pattern, int* returnSize){
    bool* matches = (bool*)calloc(sizeof(bool), queriesSize);
    for(int i = 0; i < queriesSize; i++){
        if (isMatch(queries[i], pattern))
            matches[i] = true;
    }
    *returnSize = queriesSize;
    return matches;
}

/*
67. 二进制求和
难度简单453
给你两个二进制字符串，返回它们的和（用二进制表示）。
输入为 非空 字符串且只包含数字 1 和 0。

示例 1:
输入: a = "11", b = "1"
输出: "100"
示例 2:
输入: a = "1010", b = "1011"
输

*/
char * addBinary(char * a, char * b)
{
	int alen = strlen(a);
	int blen = strlen(b);
	int rlen = fmax(alen, blen) + 2;

	char *res = (char *)calloc(rlen, sizeof(char));
	char *aptr = a + alen - 1;
	char *bptr = b + blen - 1;
	char *rptr = res + rlen - 2;
	char high = 0;
	while (aptr >= a && bptr >= b) {
		char ia = *aptr - '0';
		char ib = *bptr - '0';
		char sum = ia + ib + high;
		*rptr = sum % 2 + '0';
		high = sum / 2;
		aptr--;
		bptr--;
		rptr--;
	}

	if (aptr < a) {
		while(bptr >= b) {
			char ib = *bptr - '0';
			char sum = ib + high;
			*rptr = sum % 2 + '0';
			high = sum / 2;
			bptr--;
			rptr--;
		}
	} else if (bptr < b) {
		while(aptr >= a) {
			char ia = *aptr - '0';
			char sum = ia + high;
			*rptr = sum % 2 + '0';
			high = sum / 2;
			aptr--;
			rptr--;
		}
	}

	if (high) {
		*rptr = high + '0';
	}

	while(*res == 0) {
		res++;
	}

	return res;
}

char * addBinary(char * a, char * b)
{
	int alen = strlen(a);
	int blen = strlen(b);
	int rlen = fmax(alen, blen) + 2;

	char *res = (char *)calloc(rlen, sizeof(char));
	char *aptr = a + alen - 1;
	char *bptr = b + blen - 1;
	char *rptr = res + rlen - 2;
	char high = 0;

	while (rptr > res) {
		char ia = aptr >= a ? *aptr - '0' : 0;
		char ib = bptr >= b ? *bptr - '0' : 0;
		char sum = ia + ib + high;
		*rptr = sum % 2 + '0';
		high = sum / 2;
		aptr--;
		bptr--;
		rptr--;
	}

	if (high) {
		*rptr = '1';
	}

	while(*res == 0) {
		res++;
	}

	return res;
}

void reserve(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char t = s[i];
        s[i] = s[len - i - 1], s[len - i - 1] = t;
    }
}

char* addBinary(char* a, char* b) {
    reserve(a);
    reserve(b);

    int len_a = strlen(a), len_b = strlen(b);
    int n = fmax(len_a, len_b), carry = 0, len = 0;
    char* ans = (char*)malloc(sizeof(char) * (n + 2));
    for (int i = 0; i < n; ++i) {
        carry += i < len_a ? (a[i] == '1') : 0;
        carry += i < len_b ? (b[i] == '1') : 0;
        ans[len++] = carry % 2 + '0';
        carry /= 2;
    }

    if (carry) {
        ans[len++] = '1';
    }
    ans[len] = '\0';
    reserve(ans);

    return ans;
}

/*
415. 字符串相加
难度简单248
给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。

提示：
1.	num1 和num2 的长度都小于 5100
2.	num1 和num2 都只包含数字 0-9
3.	num1 和num2 都不包含任何前导零
4.	你不能使用任何內建 BigInteger 库， 也不能直接将输入的字符串转换为整数形式
出: "10101"


*/

#define swap(a,b) ((a) ^= (b), (b) ^= (a) ,(a) ^= (b))
void strrevSelf_pos(char *s, int begin, int end)
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

void strrevSelf(char *s)
{
	strrevSelf_pos(s, 0, strlen(s) - 1);
}

char * addStrings(char * num1, char * num2)
{
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int lenr = fmax(len1, len2);
	char *res = (char *)calloc(lenr + 2, sizeof(char));

	strrevSelf(num1);
	strrevSelf(num2);
	int pos = 0;
	int i = 0;
	for (; i < lenr; i++) {
		int sum = 0;
		sum += pos;
		sum += i >= len1 ? 0 : num1[i] - '0';
		sum += i >= len2 ? 0 : num2[i] - '0';

		res[i] = sum % 10 + '0';
		pos = sum / 10;
	}

	 if (pos != 0) {
		res[i] = pos + '0';
		pos = 0;
	 }

	strrevSelf(res);
	return res;
}

char* addStrings(char* num1, char* num2) {
    int i = strlen(num1) - 1, j = strlen(num2) - 1, add = 0;
    char* ans = (char*)malloc(sizeof(char) * (fmax(i, j) + 3));
    int len = 0;
    while (i >= 0 || j >= 0 || add != 0) {
        int x = i >= 0 ? num1[i] - '0' : 0;
        int y = j >= 0 ? num2[j] - '0' : 0;
        int result = x + y + add;
        ans[len++] = '0' + result % 10;
        add = result / 10;
        i--, j--;
    }
    // 计算完以后的答案需要翻转过来
    for (int i = 0; 2 * i < len; i++) {
        int t = ans[i];
        ans[i] = ans[len - i - 1], ans[len - i - 1] = t;
    }
    ans[len++] = 0;
    return ans;
}

/*
214. 最短回文串
难度困难176
给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。
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
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a)  ((a) >= 0 ? (a) : -(a))
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