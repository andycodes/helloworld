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

/*
312. 戳气球
有 n 个气球，编号为0 到 n-1，每个气球上都标有一个数字，这些数字存在数组 nums 中。

现在要求你戳破所有的气球。如果你戳破气球 i ，就可以获得 nums[left] * nums[i] * nums[right] 个硬币。 这里的 left 和 right 代表和 i 相邻的两个气球的序号。注意当你戳破了气球 i 后，气球 left 和气球 right 就变成了相邻的气球。

求所能获得硬币的最大数量。

说明:

你可以假设 nums[-1] = nums[n] = 1，但注意它们不是真实存在的所以并不能被戳破。
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
示例:

输入: [3,1,5,8]
输出: 167
解释: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
     coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/
int rec[502][502];
int val[502];
int solve(int left, int right) {
    if (left >= right - 1) {
        return 0;
    }
    if (rec[left][right] != -1) {
        return rec[left][right];
    }
    for (int i = left + 1; i < right; i++) {
        int sum = val[left] * val[i] * val[right];
        sum += solve(left, i) + solve(i, right);
        rec[left][right] = fmax(rec[left][right], sum);
    }
    return rec[left][right];
}

int maxCoins(int* nums, int numsSize) {
    memset(rec, -1, sizeof(rec));
    val[0] = val[numsSize + 1] = 1;
    for (int i = 1; i <= numsSize; i++) {
        val[i] = nums[i - 1];
    }

    return solve(0, numsSize + 1);
}

/*
327. 区间和的个数
给定一个整数数组 nums，返回区间和在 [lower, upper] 之间的个数，包含 lower 和 upper。
区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)。

说明:
最直观的算法复杂度是 O(n2) ，请在此基础上优化你的算法。

示例:

输入: nums = [-2,5,-1], lower = -2, upper = 2,
输出: 3
解释: 3个区间分别是: [0,0], [2,2], [0,2]，它们表示的和分别为: -2, -1, 2。
*/

int countRangeSum(int* nums, int numsSize, int lower, int upper){
    long sum;
    int count;
    int i, j;
    if (numsSize == 1) {
        if ((nums[0] >= lower) && (nums[0] <= upper)) { return 1; }
        if ((nums[0] < lower) || (nums[0] > upper)) { return 0; }
    }

    count = 0;
    for (i = 0; i < numsSize; i++) {
        sum = 0;
        for (j = i; j < numsSize; j++) {
            sum += nums[j];
            if ((sum >= lower) && (sum <= upper)) {
                count++;
            }
        }
    }
    return count;
}

int countRangeSumRecursive(long long* sum, int lower, int upper, int left, int right) {
    if (left == right) {
        return 0;
    } else {
        int mid = (left + right) / 2;
        int n1 = countRangeSumRecursive(sum, lower, upper, left, mid);
        int n2 = countRangeSumRecursive(sum, lower, upper, mid + 1, right);
        int ret = n1 + n2;

        // 首先统计下标对的数量
        int i = left;
        int l = mid + 1;
        int r = mid + 1;
        while (i <= mid) {
            while (l <= right && sum[l] - sum[i] < lower) l++;
            while (r <= right && sum[r] - sum[i] <= upper) r++;
            ret += (r - l);
            i++;
        }

        // 随后合并两个排序数组
        int sorted[right - left + 1];
        memset(sorted, 0, sizeof(sorted));
        int p1 = left, p2 = mid + 1;
        int p = 0;
        while (p1 <= mid || p2 <= right) {
            if (p1 > mid) {
                sorted[p++] = sum[p2++];
            } else if (p2 > right) {
                sorted[p++] = sum[p1++];
            } else {
                if (sum[p1] < sum[p2]) {
                    sorted[p++] = sum[p1++];
                } else {
                    sorted[p++] = sum[p2++];
                }
            }
        }
        for (int i = 0; i < right - left + 1; i++) {
            sum[left + i] = sorted[i];
        }
        return ret;
    }
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long long s = 0;
    long long sum[numsSize + 1];
    sum[0] = 0;
    for (int i = 1; i <= numsSize; i++) {
        sum[i] = sum[i - 1] + nums[i - 1];
    }
    return countRangeSumRecursive(sum, lower, upper, 0, numsSize);
}

