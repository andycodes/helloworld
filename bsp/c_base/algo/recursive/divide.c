#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

/**
241. 为运算表达式设计优先级
给定一个含有数字和运算符的字符串，
为表达式添加括号，改变其运算优先级以求出不同
的结果。你需要给出所有可能的组合的结果。
有效的运算符号包含 +, - 以及 * 。

示例 1:

输入: "2-1-1"
输出: [0, 2]
解释:
((2-1)-1) = 0
(2-(1-1)) = 2

*/
int GetNum(char* input, int begin, int end)
{
	int i;
	int num = 0;

	for (i = begin; i <= end; i++) {
		num = num * 10 + input[i] - '0';
	}

	return num;
}


int* CalNum(char* input, int begin, int end, int*returnSize)
{
	int i;
	int m, n;
	int* res = NULL;
	int* leftOut = NULL;
	int* rightOut = NULL;
	int leftNumSize = 0;
	int rightNumSize = 0;
	bool isdigit = true;
	int result = 0;

	res = (int*)malloc(sizeof(int) * 2000);
	*returnSize = 0;

	for (i = begin; i <= end; i++) {
		if (ispunct(input[i])) {
			leftOut = CalNum(input, begin, i - 1, &leftNumSize);
			rightOut = CalNum(input, i + 1, end, &rightNumSize);

			for (m = 0; m < leftNumSize; m++) {
				for (n = 0; n < rightNumSize; n++) {
					switch (input[i]) {
						case '+':
						result = leftOut[m] + rightOut[n];
						break;
						case '-':
						result = leftOut[m] - rightOut[n];
						break;
						case '*':
						result = leftOut[m] * rightOut[n];
						break;
						default:
						break;
					}

					res[*returnSize] = result;
					(*returnSize)++;
				}
			}

			free(leftOut);
			free(rightOut);
			leftOut = NULL;
			rightOut = NULL;

			isdigit = false;
		}
	}

	if (isdigit) {//字符串没有符号位；都是数字
		res[*returnSize] = GetNum(input, begin, end);
		(*returnSize)++;
	}
	return res;
}

int* diffWaysToCompute(char* input, int* returnSize)
{
	*returnSize = 0;
	return CalNum(input, 0, strlen(input) - 1, returnSize);
}


/*
932. 漂亮数组
对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，
使得：
对于每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]。
那么数组 A 是漂亮数组。
给定 N，返回任意漂亮数组 A（保证存在一个）。
示例 1：
输入：4
输出：[2,1,4,3]

*/
/*
漂亮数组有以下的性质:

（1）A是一个漂亮数组，
如果对A中所有元素添加一个常数，
那么Ａ还是一个漂亮数组。

（2）A是一个漂亮数组，
如果对A中所有元素乘以一个常数，
那么A还是一个漂亮数组。

（3）A是一个漂亮数组，如果删除一些A中所有元素，
那么A还是一个漂亮数组。

（4) A是一个奇数构成的漂亮数组，
B是一个偶数构成的漂亮数组，那么A+B也是一个漂亮数组
比如:{1,5,3,7}+{2,6,4,8}={1,5,3,7,2,6,4,8}也是一个漂亮数组。

所以我们假设一个{1-m}的数组是漂亮数组，
可以通过下面的方式构造漂亮数组{1-2m}:

对{1-m}中所有的数乘以2-1，
构成一个奇数漂亮数组A。如{1,3,2,4},可以得到{1,5,3,7}
对{1-m}中所有的数乘以2,
构成一个偶数漂亮数组B,如{1,3,2,4}, 可以得到{2,6,4,8}
A+B构成了{1-2m}的漂亮数组。{1,5,3,7}+{2,6,4,8}={1,5,3,7,2,6,4,8}
从中删除不要的数字即可。

首先明确一下，如果一个数组X是漂亮数组
"	那么2X(每个元素乘以2)，也是漂亮数组
"	那么2X-1(每个元素乘以2，减一)，也是漂亮数组

满足下面条件的为漂亮数组：

每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]
由于奇数+偶数 = 奇数
2* [奇数或偶数] = 偶数
因此，首先奇偶数分开，分成两部分，
那么这两部分就满足这个条件，奇数部分为X，偶数部分为Y
然后对X进行拆分，将X的所有位向右移动一位，然后拆分奇偶
对Y进行拆分，将Y的所有位向右移动一位，然后拆分奇偶s
*/

int* GetBeautifulArray(int num, int** saveArray, int* size)
{
    int* outArray = NULL;
    int* leftArray = NULL;
    int* rightArray = NULL;
    int leftSize = 0;
    int rightSize = 0;
    int i;

    if (saveArray[num] != NULL) {
        *size = num;
        return saveArray[num];
    }

    if (num == 1) {
        outArray = (int*)malloc(sizeof(int));
        outArray[0] = 1;
        *size = 1;
        saveArray[num] = outArray;
        return outArray;
    }

    leftArray = GetBeautifulArray((num + 1) / 2, saveArray, &leftSize);
    rightArray = GetBeautifulArray(num / 2, saveArray, &rightSize);

    *size = leftSize + rightSize;
    outArray = (int*)malloc(sizeof(int) * (*size));
    for (i = 0; i < leftSize; i++) {
        outArray[i] = leftArray[i] * 2 - 1;
    }
    for (i = 0; i < rightSize; i++) {
        outArray[i + leftSize] = rightArray[i] * 2;
    }

    saveArray[num] = outArray;

    return outArray;
}


/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int* beautifulArray(int N, int* returnSize)
{
    int* outArray = NULL;
    int i;
    int** saveArray = (int**)malloc(sizeof(int*) * (N + 1));

    (void)memset(saveArray, 0, sizeof(int*) * (N + 1));
    outArray = GetBeautifulArray(N, saveArray, returnSize);
    for (i = 0; i < N; i++) {
        if (saveArray[i] != NULL) {
            free(saveArray[i]);
        }
    }
    free(saveArray);
    return outArray;
}

/*
50. Pow(x, n)
难度中等390收藏分享切换为英文关注反馈
实现 pow(x, n) ，即计算 x 的 n 次幂函数。
示例 1:
输入: 2.00000, 10
输出: 1024.00000
示例 2:
输入: 2.10000, 3
输出: 9.26100
示例 3:
输入: 2.00000, -2
输出: 0.25000
解释: 2-2 = 1/22 = 1/4 = 0.25

*/
double dfs(double x, long long N)
{
	if (n == 0) {
		return 1.0;
	}

	double y = dfs(x, N / 2);

	return N % 2 == 0 ? y * y : y * y * x;
}

double traverse(double x, long long N)
{
        double ans = 1.0;
        // 贡献的初始值为 x
        double x_contribute = x;
        // 在对 N 进行二进制拆分的同时计算答案
        while (N > 0) {
            if (N % 2 == 1) {
                // 如果 N 二进制表示的最低位为 1，那么需要计入贡献
                ans *= x_contribute;
            }
            // 将贡献不断地平方
            x_contribute *= x_contribute;
            // 舍弃 N 二进制表示的最低位，这样我们每次只要判断最低位即可
            N /= 2;
        }
        return ans;
}

double myPow(double x, int n)
{
	long long N = n;
	return N >= 0 ? traverse(x, N) : 1.0 / traverse(x, -N);
}

/*
395. 至少有K个重复字符的最长子串
难度中等152
找到给定字符串（由小写字符组成）中的最长子串 T ， 要求 T 中的每一字符出现次数都不少于 k 。输出 T 的长度。
示例 1:
输入:
s = "aaabb", k = 3

输出:
3

最长子串为 "aaa" ，其中 'a' 重复了 3 次。
示例 2:
输入:
s = "ababbc", k = 2

输出:
5

最长子串为 "ababb" ，其中 'a' 重复了 2 次， 'b' 重复了 3 次。

*/
/*
解题思路：递归拆分子串，分治。先统计出每个字符出现的频次，维护一对双指针，从首尾开始统计，从首尾往中间排除，如果出现次数小于k则不可能出现在最终子串中，排除并挪动指针，然后得到临时子串，依次从头遍历，一旦发现出现频次小于k的字符，以该字符为分割线，分别递归求其最大值返回。
*/

int divide(char *s, int k, int left, int right)
{
	if (right - left + 1 < k)
		return 0;

	int mapcnt[26];
	memset(mapcnt, 0, sizeof(mapcnt));

	for (int i = left; i <= right; i++) {
		mapcnt[s[i] - 'a']++;
	}

	while(right - left + 1 >= k && mapcnt[s[left] - 'a'] < k) {
		left++;
	}

	while(right - left + 1 >= k && mapcnt[s[right] - 'a'] < k) {
		right--;
	}

	if (right - left + 1 < k)
		return 0;

	for (int i = left; i <= right; i++) {
		if (mapcnt[s[i] - 'a'] < k) {
			return fmax(divide(s, k, left, i - 1), divide(s, k, i + 1, right));
		}
	}

	return right - left + 1;
}

int longestSubstring(char * s, int k)
{
	int slen = strlen(s);

	if (slen == 0 || k > slen)
		return 0;

	if (k < 2)
		return slen;

	return divide(s, k, 0, slen - 1);
}
