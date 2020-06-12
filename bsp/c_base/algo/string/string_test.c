

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

