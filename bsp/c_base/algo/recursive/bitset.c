
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

	for (int i = 0; i < (1 << numsSize); i++) {  i 为 遍历子集所有状态
		for (int j = 0; j < numsSize; j++) {//遍历子集状态的二进制的每一位
			if ((i & (1 << j)) != 0) { //为真，选取原始对象中的成员
					A[j]
			}
		}

	}

*/


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
当 i = 0; 时，i 的所有位都为 0 ，表示的情况是： arr 中的单词都不
选择。
当 i = (1 << 5) - 1 时，i 的前 5 位都为 1，表示的情况是：arr中的单词
都选择。
那所有选择情况就可以这样枚举：
for (int i = 0; i < (1 << 5); i++) {
    // 得到的每个 i 都可以表示一种选择情况
}
对于 i 表示的情况，怎么知道某个单词 word 的选取状态？
word 在 arr 中的索引 j 就表示它在 i 的第几位，使用 i & (1 << j) 就知道
word 的选取状态。
当 i & (1 << j) 为 1 时，表示 word 的状态为选择；
当 i & (1 << j) 为 0 时，表示 word 的状态为不选。
同时，这里使用位掩码来表示字符串中 26 个英文小写字母的
出现情况。在代码中用 int m; 中的 26 位，来表示 26 个英文的出
现状态。
*/

bool isUnique(char * str, int *bitmap)
{
	int i = 0;
	while(str[i] != '\0') {
		if (*bitmap & (1 << (str[i] - 'a'))) {
			return false;
		}

		*bitmap |= (1 << (str[i] - 'a'));
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
		int bitmap = 0;
		for (int j = 0; j < arrSize; j++) {
			if ((i & (1 << j)) && isUnique(arr[j], &bitmap)) {
				sum += strlen(arr[j]);
			}
		}
		ans = fmax(ans, sum);
	}

	return ans;
}

/*
401. 二进制手表
二进制手表顶部有 4 个 LED 代表小时（0-11），
底部的 6 个 LED 代表分钟（0-59）。
每个 LED 代表一个 0 或 1，最低位在右侧。
例如，上面的二进制手表读取 "3:25"。
给定一个非负整数 n 代表当前 LED 亮着的数量，
返回所有可能的时间。
案例:
输入: n = 1
返回: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
*/
char ** readBinaryWatch(int num, int* returnSize)
{
	char **res = (char **)calloc(1024, sizeof(char *));
	*returnSize = 0;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 60; j++) {
			if (hammingWeight(i) + hammingWeight(j) == num) {
				res[*returnSize] = (char *)calloc(6, sizeof(char));
				sprintf(res[*returnSize], "%d%02d", i, j);
				(*returnSize)++;
			}
		}
	}

	return res;
}


