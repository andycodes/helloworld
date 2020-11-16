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
每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]
由于奇数+偶数 = 奇数
2* [奇数或偶数] = 偶数
因此，首先奇偶数分开，分成两部分，
那么这两部分就满足这个条件，奇数部分为X，偶数部分为Y
*/
void exec(int* arr, int size, int* tmp1, int* tmp2)
{
    int i;
    int j = 0;
    int k = 0;

    // 如果数组长度小于等于2 则无需处理
    if (size <= 2) {
        return;
    }

    // 处理数组，把数字1 3 5 7 放在前面，把2 4 6 8...放在后面
	//不停把偶数序号数往后半部分放
    for (i = 0; i < size; i++) {
        if (i % 2 == 0) {
            tmp1[j++] = arr[i];
        } else {
            tmp2[k++] = arr[i];
        }
    }

    memcpy(arr, tmp1, j * sizeof(int));
    memcpy(arr + j, tmp2, k * sizeof(int));

    // 对前面的1 3 5 7...重复该处理过程
    exec(arr, j, tmp1, tmp2);

    // 对后面的2 4 6 8...重复该处理过程
    exec(arr + j, k, tmp1, tmp2);
}

int* beautifulArray(int N, int* returnSize)
{
    int* arr;
    int* tmp1;
    int* tmp2;
    int i;


    *returnSize = N;

    // 返回的数组
    arr = (int*)malloc(sizeof(int) * N);

    // 两个临时数组用于存放临时数据
    tmp1 = (int*)malloc(sizeof(int) * N);
    tmp2 = (int*)malloc(sizeof(int) * N);

    for (i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    exec(arr, N, tmp1, tmp2);

    free(tmp1);
    free(tmp2);

    return arr;
}

/*
395. 至少有K个重复字符的最长子串
难度中等152
找到给定字符串（由小写字符组成）中的最长子串 T ， 要求
T 中的每一字符出现次数都不少于 k 。输出 T 的长度。
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
解题思路：递归拆分子串，分治。先统计出每个字符出现的
频次，维护一对双指针，从首尾开始统计，从首尾往中间排
除，如果出现次数小于k则不可能出现在最终子串中，排除并
挪动指针，然后得到临时子串，依次从头遍历，一旦发现出
现频次小于k的字符，以该字符为分割线，分别递归求其最大
值返回。
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
