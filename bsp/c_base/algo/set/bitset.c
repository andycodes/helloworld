/*
我们可以把前面的算法进行优化。
我们不再检查数字的每一个位，
而是不断把数字最后一个 11 反转，
并把答案加一。当数字变成 00 的时候偶，
我们就知道它没有 11 的位了，此时返回答案。
这里关键的想法是对于任意数字 nn ，将 nn 和 n - 1n?1 做与运算，
会把最后一个 11 的位变成 00 。为什么？考虑 nn 和 n - 1n?1 的
二进制表示。

在二进制表示中，数字 nn 中最低位的 11 总是对应 n - 1n?1 中的 00 。
因此，将 nn 和 n - 1n?1 与运算总是能把 nn 中最低位的 11 变成 00 ，
并保持其他位不变。使用这个小技巧，代码变得非常简单。


统计一个位数组中非0位的数量，数学上称作：
”Hanmming Weight“，汉明重量
*/

int hammingWeight(unsigned int n)
{
    int sum = 0;
    while (n != 0) {
        sum++;
        n &= (n - 1);
    }
    return sum;
}



/*
二进制枚举:所有子集
含有N个元素的集合的一切子集的个数为 2^n

	for (int i = 0; i < (1 << numsSize); i++) {遍历子集所有状态
		for (int j = 0; j < numsSize; j++) {//遍历子集状态的二进制的每一位
			if ((i & (1 << j)) != 0) { //为真，选取原始对象中的成员

			}
		}

	}

*/

/*
面试题 08.04. 幂集
难度中等3
幂集。编写一种方法，返回某集合的所有子集。集合中不包
含重复的元素。
说明：解集不能包含重复的子集。
示例:
 输入： nums = [1,2,3]
 输出：
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

*/

/*
0-(1<<n)的二进制数代表了一个集合的所有子集，
位为1的位对应的索引在其中，位0的不在其中。
*/
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
	int **res = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	for (int i = 0; i < (1 << numsSize); i++) {
		res[*returnSize] = (int *)calloc(numsSize, sizeof(int));
		int col = 0;
		for (int j = 0; j < numsSize; j++) {
			if (i & (1 << j)) {
				res[*returnSize][col++]=  nums[j];
			}
		}

		(*returnColumnSizes)[*returnSize] = col;
		(*returnSize)++;
	}
	return res;
}


/*
1239. 串联字符串的最大长度
难度中等34
给定一个字符串数组 arr，字符串 s 是将 arr 某一子序列字符串
连接所得的字符串，如果 s 中的每一个字符都只出现过一次，
那么它就是一个可行解。
请返回所有可行解 s 中最长长度。

示例 1：
输入：arr = ["un","iq","ue"]
输出：4
解释：所有可能的串联组合是 "","un","iq","ue","uniq" 和 "ique"，
最大长度为 4。
示例 2：
输入：arr = ["cha","r","act","ers"]
输出：6
解释：可能的解答有 "chaers" 和 "acters"。
示例 3：
输入：arr = ["abcdefghijklmnopqrstuvwxyz"]
输出：26

*/

/*
思路分析
对于每个单词无非就两种情况，选或这不选。

对于 arr 中的每个单词我用一个二进制位来表示它，
为 1 表示选择这个单词，为 0 表示不选择这个单词。

题目给出 1 <= arr.length <= 16，那一个 int(38位)就足够表示 arr 中的
所有单词。

例如 arr 中有 5 个单词，我用 int i; 来枚举对 arr 的所有选择情况：

当 i = 0; 时，i 的所有位都为 0 ，表示的情况是： arr 中的单词都不选择。

当 i = (1 << 5) - 1 时，i 的前 5 位都为 1，表示的情况是：arr中的单词都选择。

那所有选择情况就可以这样枚举：

for (int i = 0; i < (1 << 5); i++) {
    // 得到的每个 i 都可以表示一种选择情况
}
对于 i 表示的情况，怎么知道某个单词 word 的选取状态？

word 在 arr 中的索引 j 就表示它在 i 的第几位，使用 i & (1 << j) 就知道 word 的选取状态。

当 i & (1 << j) 为 1 时，表示 word 的状态为选择；
当 i & (1 << j) 为 0 时，表示 word 的状态为不选。
同时，这里使用位掩码来表示字符串中 26 个英文小写字母的出现情况。在代码中用 int m; 中的 26 位，来表示 26 个英文的出现状态。

*/
bool isUnique(char * str, int *bit)
{
	int i = 0;
	while(str[i] != '\0') {
		if (*bit & (1 << (str[i] - 'a'))) {
			return false;
		}

		*bit |= (1 << (str[i] - 'a'));
		i++;
	}

	return true;
}

int maxLength(char ** arr, int arrSize)
{
	if (arr == NULL || arrSize <= 0) {
		return 0;
	}

	if (arr != NULL && arrSize == 1) {
		return strlen(arr[0]);
	}

	int ans = 0;
	for (int i = 0; i < (1 << arrSize); i++) {
		int sum = 0;
		int bit = 0;
		for (int j = 0; j < arrSize; j++) {
			if ((i & (1 << j)) && isUnique(arr[j], &bit)) {
				sum += strlen(arr[j]);
			}
		}
		ans = fmax(ans, sum);
	}

	return ans;
}

/*
77. 组合
难度中等238
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
示例:
输入: n = 4, k = 2
输出:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes)
{
	if (k > n || n < 1) {
		return NULL;
	}

	int **res = (int **)calloc(1 << n, sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1 << n, sizeof(int));

	for (int i = 0; i < (1 << n); i++) {
		if(hammingWeight(i) == k) {
			res[*returnSize] = (int *)calloc(1 << n, sizeof(int));
			for (int j = 0; j < n; j++) {
				if (((i & (1 << j)) != 0)) {
					res[*returnSize][(*returnColumnSizes)[*returnSize]] = j + 1;
					((*returnColumnSizes)[*returnSize])++;
				}
			}

			(*returnSize)++;
		}
	}

	return res;
}




