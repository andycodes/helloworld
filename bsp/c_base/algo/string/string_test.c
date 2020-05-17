/*
583. 两个字符串的删除操作
难度中等96
给定两个单词 word1 和 word2，
找到使得 word1 和 word2 相同所需的最小步数，
每步可以删除任意一个字符串中的一个字符。

示例：
输入: "sea", "eat"
输出: 2
解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"

*/
int minDistance(char * word1, char * word2)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);

	int dp[len1 + 1][len2 + 1];
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (word1[i -1] == word2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return len1 + len2 - 2 * dp[len1][len2];
}

/*
5. 最长回文子串
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"
*/
/*中心扩散法。*/
char * longestPalindrome(char * s){
    if(strlen(s)==0||strlen(s)==1) return s;
    int i,start,left,right,count,len;
    start = len =0;
    for(i=0;s[i]!='\0';i+=count){
        count = 1;
        left=i-1;
        right = i+1;
        while(s[right]!='\0'&&s[i]==s[right]){ //处理重复字符串
            right++;
            count++;
        }
        while(left>=0 && s[right]!='\0' && s[left] == s[right]){
            left--;
            right++;
        }
        if(right-left-1>len){
            start = left+1;
            len = right-left-1;
        }
    }
    s[start + len] = '\0';      // 原地修改返回
    return s + start;
}

/*dp*/
char * longestPalindrome(char * s)
{
    if (s == NULL || strlen(s) < 1) return "";
	int length = strlen(s);
	bool dp[length][length];
	int maxlen = 0;
	char *ret = "";
	for (int len = 1; len <= length; len++) {
		for (int  start = 0; start < length; start++) {
			int end = start + len - 1;
			if (end >= length)
				break;

			dp[start][end] = (len == 1 || len == 2 || dp[start + 1][end - 1]) && s[start] == s[end];
			if (dp[start][end] && len > maxlen) {
				maxlen = len;
				ret = strdup(s + start);
				ret[len] = '\0';
			}
		}
	}

	return ret;
}

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
    if (s == NULL || strlen(s) < 1) return "";

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


/*
43. 字符串相乘
难度中等329
给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
示例 1:
输入: num1 = "2", num2 = "3"
输出: "6"
示例 2:
输入: num1 = "123", num2 = "456"
输出: "56088"

*/
/*
两数相乘得到的乘积的长度不会超过两个数字的长度之和，若num1长度为length1，num2 长度为lenght2，则 num1 x num2 的长度不会超过 length1 + length2
还有就是乘的时候需要错位的原因，比如6 x 8得到的 48 为啥要跟6 x 9得到的 54 错位相加，因为 8 是十位上的数字，其本身相当于80，所以错开的一位实际上末尾需要补的0
num1 和 num2 中任意位置的两个数字相乘，得到的两位数在最终结果中的位置是确定的，比如 num1 中位置为i的数字乘以 num2 中位置为j的数字，那么得到的两位数字的位置为 i+j 和 i+j+1，这也是由错位相乘引起的
首先开辟两个空间，一个用来存储错位相乘的中间结果，int类型，另外一个作为最终返回的结果，char类型。需要注意的是后一个指针需要比totalLength多一个字符用来在C语言当中指示字符串数组的结束，对于int类型的中间结果初始化为0。

由于要从个位上开始相乘，所以从 num1 和 num2 字符串的尾部开始往前遍历，分别提取出对应位置上的字符，将其转为整型后相乘，将num1[i]与num[j]相乘的结果累加存储在value[i+j+1]当中，注意这里是累加。以上面的 89 x 76 为例，num1[1] x num2[0]的结果 48 是需要与num1[0] x num2[1]的结果 63相加以后一并存储在value[2]当中再进入下一步的处理工序的。

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
// 从数组的尾部开始遍历，将第i位的高位通过/累加到第i-1位，然后通过%求余获得当前位的数字。
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
例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
"	I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
"	X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
"	C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个整数，将其转为罗马数字。输入确保在 1 到 3999 的范围内。
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
712. 两个字符串的最小ASCII删除和
难度中等93
给定两个字符串s1, s2，找到使两个字符串相等所需删除字符的ASCII值的最小和。
示例 1:
输入: s1 = "sea", s2 = "eat"
输出: 231
解释: 在 "sea" 中删除 "s" 并将 "s" 的值(115)加入总和。
在 "eat" 中删除 "t" 并将 116 加入总和。
结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。

*/

/*
题意是寻找一个共同子序列，
将字符串s1和s2删除为该子序列时所删除
的ASCII综合最小。等价于求一个字符串s1
和s2的ASCII码总和最大的共同子序列。
因为s1和s2的总和固定，当共同子序列的
总和最大时，删除成为该子序列的代价必然
最小。
*/
int minimumDeleteSum(char * s1, char * s2){
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    int dp[len1 + 1][len2 + 1];
    memset(dp,0, sizeof(dp));

    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= len2; ++j)
        {
            if(s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + s1[i - 1];
            else
                dp[i][j] = fmax(dp[i - 1][j],dp[i][j - 1]);
        }

    int sum = 0;
    for (int i = 0; i < len1; ++i)
        sum += s1[i];
    for (int i = 0; i < len2; ++i)
        sum += s2[i];
    return sum - 2 * dp[len1][len2];

}


