/*
647. 回文子串
难度中等374
给定一个字符串，你的任务是计算这个字符串中有多少个回
文子串。
具有不同开始位置或结束位置的子串，即使是由相同的字符
组成，也会被视作不同的子串。

示例 1：
输入："abc"
输出：3
解释：三个回文子串: "a", "b", "c"
*/

/*
从中心往两侧延伸【通过】
思路
在长度为 N 的字符串中，可能的回文串中心位置有 2N-1 个：
字母，或两个字母中间。
从每一个回文串中心开始统计回文串数量。
回文区间 [a, b] 表示 S[a], S[a+1], ..., S[b] 是回文串，
根据回文串定义可知 [a+1, b-1] 也是回文区间。
算法
对于每个可能的回文串中心位置，
尽可能扩大它的回文区间 [left, right]。
当 left >= 0 and right < N and S[left] == S[right] 时，
扩大区间。此时回文区间表示的回文串为 S[left], S[left+1], ..., S[right]。

*/
int countSubstrings(char * s)
{
	int size = strlen(s);
	int ans = 0;
	for (int center = 0; center < 2 * size -1; center++) {
		int left = center / 2;
		int right = left + center % 2;
		while(left >= 0 && right < size && s[left] == s[right]) {
			ans++;
			left--;
			right++;
		}
	}

	return ans;
}

/*
5. 最长回文子串
给定一个字符串 s，找到 s 中最长的回文子串。
你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"
*/
char * longestPalindrome(char * s)
{
	int slen = strlen(s);
	if (s == NULL || slen <= 1) {
		return s;
	}

	int max = 1;
	int save[2] = {0};
	for (int centor = 0; centor < 2 * slen - 1; centor++) {
		int left = centor / 2;
		int right = left + centor % 2;

		while(left >= 0 && right < slen && s[left] == s[right]) {
			if (right - left + 1 > max) {
				save[0] = left;
				save[1] = right;
				max = right - left + 1 ;
			}

			left--;
			right++;
		}
	}

	s[save[1]  + 1] = '\0';
	return s + save[0];
}


/*
457. 环形数组循环
给定一个含有正整数和负整数的环形数组 nums。 如果某个索
引中的数 k 为正数，则向前移动 k 个索引。相反，如果是负
数 (-k)，则向后移动 k 个索引。因为数组是环形的，所以可以
假设最后一个元素的下一个元素是第一个元素，而第一个元
素的前一个元素是最后一个元素。

确定 nums 中是否存在循环（或周期）。循环必须在相同的索
引处开始和结束并且循环长度 > 1。此外，一个循环中的所有
运动都必须沿着同一方向进行。换句话说，一个循环中不能
同时包括向前的运动和向后的运动。


示例 1：

输入：[2,-1,1,2,2]
输出：true
解释：存在循环，按索引 0 -> 2 -> 3 -> 0 。循环长度为 3
*/
/*
首先我们需要一个 visited 数组，来记录访问过的数字然后
我们遍历原数组，如果当前数字已经访问过了，直接跳过，
否则就以当前位置坐标为起始点开始查找，进行 while 循环，
计算下一个位置（计算方法是当前位置坐标加上对应的数字，
由于是循环数组，所以结果可能会超出数组的长度，所以我
们要对数组长度取余。当然上面的数字也可能是负数，加完
以后可能也是负数，所以在取余之前还得再补上一个n，使其
变为正数，但是 若这个负数远大于n的话，取余之前只加上一
个n，可能是不够的，所以正确的方法是应该先对n取余，再
加上n。为了同时把正数的情况也包含进来，最终我们的处理
方法是先对n取余，再加上n，再对n取余，这样不管正数还是
负数，大小如何，都可以成功的旋转跳跃了。）此时我们判
断，如果 fast 和 slow 相等，说明此时是一个数字的循环，不符
合题意，再有就是检查二者的方向，数字是正数表示 forward，
若是负数表示 backward，在一个 loop 中必须同正或同负，我们只
要让二者相乘，如果结果是负数的话，说明方向不同，直接
break 掉。此时如果 fast 已经有映射了，说明我们找到了合法的
loop，返回 true，否则建立一个这样的映射，将 fast 位置在 visited
数组中标记 true，继续循环。
*/
bool circularArrayLoop(int* nums, int numsSize)
{
	if (nums == NULL || numsSize <= 1)
		return false;

	bool visited[numsSize];
	memset(visited, 0, sizeof(visited));

	for(int slow = 0; slow < numsSize; slow++) {
		if(visited[slow])
			continue;

		visited[slow] = true;
		int map[5001];
		memset(map, 0, sizeof(map));
		while(true) {
			int fast = ((slow+nums[slow])%numsSize+numsSize)%numsSize;
			if(fast == slow||nums[fast]*nums[slow] < 0)
				break;
			if (map[fast] != 0)
				return true;
			map[slow] = 1;
			visited[fast] = true;
			slow = fast;
		}
	}

	return false;
}

