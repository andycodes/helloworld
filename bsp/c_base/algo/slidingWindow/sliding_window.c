/*
子串，子数组问题

1) 处理
	right
	sum += nums[right++];
2)right++
	指向未处理的单元


滑动窗口一个左指针left，一个右指针right，
两种窗口滑动方式：
while(right < slen) {
	do---
	right++ or continue;

	满足条件，选最优
	left++;
}


for (int right = 0; right < slen; right++) {
		do--
		满足条件选最优
		left++;
}


*/


/*
209. 长度最小的子数组
难度中等261
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组
中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。
如果不存在符合条件的连续子数组，返回 0。
示例:
输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。
进阶:
*/
int minSubArrayLen(int s, int* nums, int numsSize)
{
	int left = 0;
	int right = 0;
	int sum = 0;
	int res = INT_MAX;

	for (int i = 0; i < numsSize; i++) {
		sum += nums[i];
	}

	if (sum < s) {
		return 0;
	}

	sum = 0;
	while(right < numsSize) {
		sum += nums[right++];
		if (sum < s) {
			continue;
		}

		while(sum - nums[left] >= s) {
			sum -= nums[left++];
		}

		res = fmin(res, right - left);
	}

	return res;
}


int minSubArrayLen(int s, int* nums, int numsSize)
{
	int leftidx = 0;
	int sum = 0;
	int minret = INT_MAX;

	for (int i = 0; i < numsSize; i++) {
		sum += nums[i];
		while(sum >= s) {
			minret = fmin(minret, i + 1 - leftidx);
			sum -= nums[leftidx++];
		}
	}

	return minret == INT_MAX ? 0 : minret;
}


/*
3. 无重复字符的最长子串
难度中等6
请从字符串中找出一个最长的不包含重复字符的子字符串，
计算该最长子字符串的长度。

示例 1:
输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，
"pwke" 是一个子序列，不是子串。

*/
int lengthOfLongestSubstring(char* s)
{
	int left = 0;
	int right = 0;
	int slen = strlen(s);

	if (s == NULL) {
		return 0;
	}

	int map[128] = {0};
	int ret = 0;
	while(right < slen) {
		if (map[s[right]] == 0) {
			map[s[right++]] = 1;
			ret = fmax(ret, right - left);
			continue;
		}

		map[s[left++]]--;
	}

	return ret;
}


/*
1004. 最大连续1的个数 III
难度中等41
给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从
0 变成 1 。
返回仅包含 1 的最长（连续）子数组的长度。
示例 1：
输入：A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释：
[1,1,1,0,0,1,1,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 6。
*/
int longestOnes(int* A, int ASize, int K)
{
	int left = 0;
	int right = 0;
	int res = 0;

	while(right < ASize) {
		if (A[right] == 1) {
			right++;
			res = fmax(res, right - left);
			continue;
		}

		if (A[right] == 0 && K > 0) {
			right++;
			K--;
			res = fmax(res, right - left);
			continue;
		}

		if(A[left++] == 0) {
			K++;
		}
	}

	return res;
}

int longestOnes(int* A, int ASize, int K)
{
	//cnt用来统计窗口中0的个数
	int left=0,right=0, cnt=0,res=0,size=ASize;
	while(right < size) {
		cnt += (A[right] == 0);
		while (cnt > K) {////当窗口内0的个数大于K时，需要缩小窗口
			cnt -= (A[left] == 0);
			left++;
		}
		////窗口内0的个数小于等于k时，也就是可以该窗口内的0都可以替换，根据该窗口长度来确定是否更新res
		res = fmax(res, right-left+1);
		right++;
	}

	return res;
}

/*
424. 替换后的最长重复字符
难度中等73
给你一个仅由大写英文字母组成的字符串，你可以将任意位
置上的字符替换成另外的字符，总共可最多替换 k 次。在执行
上述操作后，找到包含重复字母的最长子串的长度。
注意:
字符串长度 和 k 不会超过 104。
示例 1:
输入:
s = "ABAB", k = 2

输出:
4

解释:
用两个'A'替换为两个'B',反之亦然。

*/
/*
然后我们维护一个window，不断计算不为c的字符的个数counter，
如果counter大于n了说明我们怎么替换也不行了，我们就要将start
往前挪一格，否则一直挪end。
每次挪完end之后都要记得更新这一轮的最大长度
每个字符c循环后都要更新最终res。
*/
int characterReplacement(char * s, int k)
{
	int left = 0;
	int right = 0;
	int maxCnt = 0;
	int ans = 0;
	int map[26] = {0};

	while(right < strlen(s)) {
		map[s[right] - 'A']++;
		maxCnt = fmax(maxCnt, map[s[right] - 'A']);//当前窗口内的最多字符的个数
/*
需要替换的字符个数就是当前窗口的大小减去窗口中数量最
多的字符的数量
*/
		if (right - left + 1 -maxCnt > k) {
			map[s[left] - 'A']--;//缩小窗口
			left++;
		}
/*
当窗口内可替换的字符数小于等于k时，我们需要根据该窗口
长度来确定是否更新result
*/
		ans = fmax(ans, right-left+1);
		right++;
	}

	return ans;
}

/*
面试题 17.18. 最短超串
难度中等5
假设你有两个数组，一个长一个短，短的元素均不相同。找
到长数组中包含短数组所有的元素的最短子数组，其出现顺
序无关紧要。
返回最短子数组的左端点和右端点，如有多个满足条件的子
数组，返回左端点最小的一个。若不存在，返回空数组。
示例 1:
输入:
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
输出: [7,10]
示例 2:
输入:
big = [1,2,3]
small = [4]
输出: []
*/
int* shortestSeq(int* big, int bigSize, int* small, int smallSize, int* returnSize)
{
	if (big == NULL || small == NULL || bigSize <= 0 || smallSize <= 0 || smallSize > bigSize) {
		*returnSize = 0;
		return NULL;
	}

	struct HashTable ht;
	int ret = HashInit(&ht, smallSize, hashequal_int, hashcode_int);

	for (int i = 0; i < smallSize; i++) {
		hashPushKey(&ht, small[i]);
	}

	int left = 0, right = 0, winCnt = 0, minLen= INT_MAX;
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	while(right < bigSize) {
		struct DataEntry *curEntry = hashFindKey(&ht, big[right]);
		if(curEntry != NULL) {
			if (curEntry->value == 0) {
				winCnt++;
			}

			curEntry->value++;
		}

		while(winCnt == smallSize) {
			struct DataEntry *entry = hashFindKey(&ht, big[left]);
			if (entry == NULL) {
				left++;
			} else if (entry->value > 1) {
				entry->value--;
				left++;
			} else {//value == 1
				if (minLen > right-left + 1) {
					minLen = right-left + 1;
					res[0] = left;
					res[1] = right;
				}

				entry->value--;
				left++;
				winCnt--;
			}
		}

		right++;
	}

	if (minLen == INT_MAX) {
		*returnSize = 0;
		return NULL;
	}

	return res;
}


/*
给定一个字符串 s ，找出 至多 包含两个
不同字符的最长子串 t 。

示例 1:

输入: "eceba"
输出: 3
解释: t 是 "ece"，长度为3。
示例 2:

输入: "ccaabbb"
输出: 5
解释: t 是 "aabbb"，长度为5。

*/
int lengthOfLongestSubstringTwoDistinct(char * s)
{
	int sSize = strlen(s);
	if (sSize <= 2)
		return sSize;

	int left = 0;
	int max = 0;

	while( left + max < sSize) {
		int tempLeft = left;

		while(left < sSize && s[left] == s[tempLeft]) {
			left++;
		}

		int right = left;
		int tempRight = right;

		while(right < sSize && (s[right] == s[tempRight] || s[right] == s[tempLeft] )) {
			right++;
		}

		max = max > (right - tempLeft) ? max :(right - tempLeft);
		left = tempRight;
	}

	return max;
}

/*
658. 找到 K 个最接近的元素
难度中等84
给定一个排序好的数组，两个整数 k 和 x，从数组中找到最靠
近 x（两数之差最小）的 k 个数。返回的结果必须要是按升序
排好的。如果有两个数与 x 的差值一样，优先选择数值较小
的那个数。
示例 1:
输入: [1,2,3,4,5], k=4, x=3
输出: [1,2,3,4]

示例 2:
输入: [1,2,3,4,5], k=4, x=-1
输出: [1,2,3,4]
*/
int gX;
int cmp_int1(const void *a, const void *b)
{
	int aa = *((int *)a);
	int bb = *((int *)b);

	if (abs(aa - gX) == abs(bb - gX)) {
		return aa - bb;
	}

	return abs(aa - gX) > abs(bb - gX);
}

int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
	gX = x;
	*returnSize = k;
	qsort(arr, arrSize, sizeof(arr[0]), cmp_int1);
	qsort(arr, k, sizeof(arr[0]), cmp_int);
	return arr;
}

/*
排除法（双指针）
如果 x 的值就在长度为 size 区间内（不一定相等），要得到
size - 1 个符合题意的最接近的元素，此时看左右边界：
1、如果左边界与 x 的差值的绝对值较小，删除右边界；
2、如果右边界与 x 的差值的绝对值较小，删除左边界；
3、如果左、右边界与 x 的差值的绝对值相等，删除右边界。
*/
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
	int left = 0;
	int right = arrSize - 1;
	*returnSize = k;

	while(right - left >= k) {
		if (x - arr[left] <= arr[right] - x) {// 2 *x <= arr[left] + arr[right]
			right--;
		} else {
			left++;
		}
	}

	return arr + left;
}


/*
面试题 17.11. 单词距离
难度中等2
有个内含单词的超大文本文件，给定任意两个单词，找出在这个文件中这两个单词的最短距离(相隔单词数)。如果寻找过程在这个文件中会重复多次，而每次寻找的单词不同，你能对此优化吗?
示例：
输入：words = ["I","am","a","student","from","a","university","in","a","city"], word1 = "a", word2 = "student"
输出：1

*/
int findClosest(char** words, int wordsSize, char* word1, char* word2)
{
	int min = wordsSize;
	int w1Idx = wordsSize;
	int w2Idx = wordsSize;
	for (int i = 0; i < wordsSize; i++) {
		if (strcmp(words[i], word1) == 0) {
			w1Idx = i;
		}

		if (strcmp(words[i], word2) == 0) {
			w2Idx = i;
		}

		if (w1Idx != wordsSize && w2Idx != wordsSize) {
			min = fmin(min, abs(w1Idx - w2Idx));
		}

	}

	return min;
}

/*
see hashmap
*/
struct it{
	int num;
	int idx;
};

int cmp_struct(const int *a, const int *b)
{
	struct it * c = (struct it *)a;
	struct it * d = (struct it *)b;
	return c->num - d->num;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	int* res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	struct it obj[numsSize];
	for (int i = 0; i < numsSize; i++) {
		obj[i].num = nums[i];
		obj[i].idx = i;
	}

	qsort(obj, numsSize, sizeof(obj[0]), cmp_struct);
	int left = 0;
	int right = numsSize -1;
	int sum;
	while(1) {
		sum = obj[left].num + obj[right].num;
		if (sum > target) {
			right--;
		}else if(sum < target) {
			left++;
		}else {
			break;
		}
	}

	res[0] = obj[left].idx;
	res[1] = obj[right].idx;
	return res;
}

/*
18. 四数之和
给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：

答案中不可以包含重复的四元组。

示例：

给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/


int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){

	int **ret = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	for (int a = 0; a < numsSize - 3; a++) {
		if(a > 0 && nums[a] == nums[a - 1])
			continue;

		if(nums[a]+nums[a+1]+nums[a+2]+nums[a+3]>target) break;
		if(nums[a]+nums[numsSize-3]+nums[numsSize-2]+nums[numsSize-1]<target) continue;
		for (int b = a + 1; b < numsSize - 2; b++) {
			if(nums[a]+nums[b]+nums[b+1]+nums[b+2]>target) break;
			 if(nums[a]+nums[b]+nums[numsSize-2]+nums[numsSize-1]<target) continue;
			if(b > a + 1 && nums[b] == nums[b -1])
				continue;

			int c = b + 1;
			int d = numsSize - 1;

			while(c < d) {
				int sum = nums[a] + nums[b] + nums[c] + nums[d];
				if (sum < target) {
					c++;
				} else if (sum > target) {
					d--;
				} else {
					ret[*returnSize] = (int *)calloc(4, sizeof(int));
					ret[*returnSize][0] = nums[a];
					ret[*returnSize][1] = nums[b];
					ret[*returnSize][2] = nums[c];
					ret[*returnSize][3] = nums[d];
					(*returnColumnSizes)[*returnSize] = 4;
					(*returnSize)++;
					while(c<d&&nums[c+1]==nums[c])
	        				    c++;
	        			while(c<d&&nums[d-1]==nums[d])
	        				    d--;

					c++;
					d--;
				}
			}
		}
	}

	return ret;
}

/*
11. 盛最多水的容器
给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中
的一个点 (i, ai) 。在坐标内画 n 条垂直线，
垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，
使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器，且 n 的值至少为 2。

*/
int maxArea(int* height, int heightSize)
{
	int left  = 0;
	int right = heightSize - 1;

	int max = 0;
	while (left < right) {
		int cur = (right - left) * (fmin(height[left], height[right]));
		max = fmax(max, cur);
		if (height[left] > height[right]) {
			right--;
		} else {
			left++;
		}
	}

	return max;
}

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
1456. 定长子串中元音的最大数目
给你字符串 s 和整数 k 。

请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。

英文中的 元音字母 为（a, e, i, o, u）。



示例 1：

输入：s = "abciiidef", k = 3
输出：3
解释：子字符串 "iii" 包含 3 个元音字母。
*/
int is_vowel(char c)
{
	const char vowel[] = {'a', 'e', 'i', 'o', 'u'};

	int i = 0;
	while(i < 5) {
		if (c == vowel[i]) {
			return 1;
		}

		i++;
	}

	return 0;
}

int maxVowels(char * s, int k)
{
	int cnt = 0;
	int res = 0;

	for (int right = 0; right < strlen(s); right++) {
		cnt += is_vowel(s[right]);

		if (right >= k) {
			cnt -= is_vowel(s[right - k]);
		}

		res = fmax(res, cnt);
	}

	return res;
}

//a, e, i, o, u
bool isYuan(char c)
{
	int d[] = {'a', 'e', 'i', 'o', 'u'};
	for (int i = 0; i < 5; i++) {
		if (c == d[i]) {
			return true;
		}
	}

	return false;
}

int maxVowels(char * s, int k)
{
	int left = 0;
	int right = 0;
	int slen = strlen(s);
	int winCnt = 0;
	int max = 0;

	while(right < slen) {
		if (isYuan(s[right])) {
			winCnt++;
		}

		if (right - left + 1 < k) {
			right++;
			continue;
		}

		max = fmax(max, winCnt);

		if (isYuan(s[left])) {
			winCnt--;
		}
		left++;
		right++;
	}

	return max;
}

/*
457. 环形数组循环
给定一个含有正整数和负整数的环形数组 nums。 如果某个索引中的数 k 为正数，则向前移动 k 个索引。相反，如果是负数 (-k)，则向后移动 k 个索引。因为数组是环形的，所以可以假设最后一个元素的下一个元素是第一个元素，而第一个元素的前一个元素是最后一个元素。

确定 nums 中是否存在循环（或周期）。循环必须在相同的索引处开始和结束并且循环长度 > 1。此外，一个循环中的所有运动都必须沿着同一方向进行。换句话说，一个循环中不能同时包括向前的运动和向后的运动。


示例 1：

输入：[2,-1,1,2,2]
输出：true
解释：存在循环，按索引 0 -> 2 -> 3 -> 0 。循环长度为 3
*/
/*
首先首先我们需要一个 visited 数组，来记录访问过的数字然后我们遍历原数组，如果当前数字已经访问过了，直接跳过，否则就以当前位置坐标为起始点开始查找，进行 while 循环，计算下一个位置（计算方法是当前位置坐标加上对应的数字，由于是循环数组，所以结果可能会超出数组的长度，所以我们要对数组长度取余。当然上面的数字也可能是负数，加完以后可能也是负数，所以在取余之前还得再补上一个n，使其变为正数，但是 若这个负数远大于n的话，取余之前只加上一个n，可能是不够的，所以正确的方法是应该先对n取余，再加上n。为了同时把正数的情况也包含进来，最终我们的处理方法是先对n取余，再加上n，再对n取余，这样不管正数还是负数，大小如何，都可以成功的旋转跳跃了。）此时我们判断，如果 fast 和 slow 相等，说明此时是一个数字的循环，不符合题意，再有就是检查二者的方向，数字是正数表示 forward，若是负数表示 backward，在一个 loop 中必须同正或同负，我们只要让二者相乘，如果结果是负数的话，说明方向不同，直接 break 掉。此时如果 fast 已经有映射了，说明我们找到了合法的 loop，返回 true，否则建立一个这样的映射，将 fast 位置在 visited 数组中标记 true，继续循环。
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


/*
567. 字符串的排列
难度中等140
给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。
换句话说，第一个字符串的排列之一是第二个字符串的子串。
示例1:
输入: s1 = "ab" s2 = "eidbaooo"
输出: True
解释: s2 包含 s1 的排列之一 ("ba").

示例2:
输入: s1= "ab" s2 = "eidboaoo"
输出: False

*/
bool checkInclusion(char * s1, char * s2){
        int mp[26] = {0};
	for (int i = 0; i < strlen(s1); i++) {
		mp[s1[i] - 'a']++;
	}

        int l = 0, r = 0;
        while (r < strlen(s2)){
            char c = s2[r++];
            mp[c - 'a']--; // 入窗
            while (l < r && mp[c - 'a'] < 0){ // 出窗
                mp[s2[l++] - 'a'] ++;
            }
            if (r - l == strlen(s1)) return true;
        }
        return false;
}

bool checkMap(int *map1, int *map2)
{
	for (int i = 0; i < 26; i++) {
		if (map1[i] != map2[i]) {
			return false;
		}
	}

	return true;
}

bool checkInclusion(char * s1, char * s2)
{
	int map[26] = {0};
	int i = 0;
	int s1len = strlen(s1);

	while(i < s1len) {
		map[s1[i++] - 'a']++;
	}

	int map2[26] = {0};
	int left = 0;
	int right = 0;
	int s2len = strlen(s2);

	while(right < s2len) {

        map2[s2[right] - 'a']++;

		if (right - left + 1 < s1len) {
			right++;
			continue;
		}

		bool check = checkMap(map, map2);
		if (check == true) {
			return true;
		}

		map2[s2[left] - 'a']--;
		left++;
		right++;
	}

	return false;
}


/*
713. 乘积小于K的子数组
难度中等135
给定一个正整数数组 nums。
找出该数组内乘积小于 k 的连续的子数组的个数。
示例 1:
输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8个乘积小于100的子数组分别为:
[10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
说明:
"	0 < nums.length <= 50000
"	0 < nums[i] < 1000
"	0 <= k < 10^6

*/
int numSubarrayProductLessThanK(int* nums, int numsSize, int k)
{
        if (k <= 1)
			return 0;

        int prod = 1, ans = 0, left = 0;
        for (int right = 0; right < numsSize; right++) {
            prod *= nums[right];
            while (prod >= k) {
				prod /= nums[left++];
            }
/*右指针每增加一位，以右指针为首增加子数组，
[5,2]加6，增加[6]、[2,6]、[5,2,6]，个数即为R - L+ 1*/
            ans += right - left + 1;
        }
        return ans;
}

/*
76. 最小覆盖子串
难度困难695
给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以
在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字
符的最小子串。

示例：
输入：S = "ADOBECODEBANC", T = "ABC"
输出："BANC"

*/
#define MAX_HASH_LEN 128
char * minWindow(char * s, char * t)
{
	int slen = strlen(s);
	int tlen = strlen(t);
	if (slen == 0 || tlen == 0 || slen < tlen) {
		return "";
	}

	int maps[MAX_HASH_LEN] = {0};
	int mapt[MAX_HASH_LEN] = {0};
	int i;
	int left = 0, right = 0;
	int matchSize = 0;
	int minLen = slen + 1; // 小细节 保证s和t有一个字符也能处理
	int minLeft = 0;
	int minRight = 0;
	int index = 0;

	for (i = 0; i < tlen; i++) {
		mapt[t[i]]++;
	}

	while (right < slen) {
		char c = s[right];
		right++;
		// 更新数据 t匹配不到，right往右+1
		if (mapt[c] == 0) {
			continue;
		}

		if (maps[c] < mapt[c]) {
			matchSize++;  /*计数小于t字符串内累计数才有效*/
		}

		maps[c]++;

		while (matchSize == tlen) {/*包含 T 所有字符 开始算最小*/
			if (right - left < minLen) {
				// 更新记录
				minLeft = left;
				minRight = right;
				minLen = right - left;
			}

			char d = s[left];
			left++;
			// 更新数据
			// mapt[d] == 0 标识left所指元素非关键
			if (mapt[d] == 0) {
				continue;
			}

			maps[d]--;
			if (maps[d] < mapt[d]) {
				matchSize--;
			}
		}
	}

	s[minRight] = '\0';
	return &s[minLeft];
}


/*
632. 最小区间
难度困难230
你有 k 个升序排列的整数列表。找到一个最小区间，使得 k 个
列表中的每个列表至少有一个数包含在其中。
我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小。

示例：
输入：[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
输出：[20,24]
解释：
列表 1：[4, 10, 15, 24, 26]，24 在区间 [20,24] 中。
列表 2：[0, 9, 12, 20]，20 在区间 [20,24] 中。
列表 3：[5, 18, 22, 30]，22 在区间 [20,24] 中。
*/
#define RETURN_SIZE 2
#define MAX_NUM 3500
typedef struct tagInfo {
	int value;
	int group;
} Info;

int cmpFun(const void *a, const void *b)
{
	Info *temp1 = (Info *)a;
	Info *temp2 = (Info *)b;

	return temp1->value > temp2->value;
}

int isCover(int *kCount, int k)
{
	for (int i = 0; i < k; i++) {
		if (kCount[i] == 0) {
			return 0;
		}
	}
	return 1;
}
void updateIndex(int left, int right, int *resBegin, int *resEnd, Info *allNum)
{
	if ((*resBegin == -1) ||
	(allNum[right].value - allNum[left].value < allNum[*resEnd].value - allNum[*resBegin].value) ||
	(allNum[right].value - allNum[left].value == allNum[*resEnd].value - allNum[*resBegin].value &&
	left < *resBegin)) {
		*resBegin = left;
		*resEnd = right;
		return;
	}
}

int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize)
{
	int numall = 0;
	for (int i = 0; i < numsSize; i++) {
		numall += numsColSize[i];
	}

	Info allNum[numall];

	int allNumSize = 0;
	for (int i = 0; i < numsSize; i++) {
		for (int j = 0; j < numsColSize[i]; j++) {
			allNum[allNumSize].value = nums[i][j];
			allNum[allNumSize].group = i;
			allNumSize++;
		}
	}

	int kCount[MAX_NUM] = { 0 };
	qsort(allNum, numall, sizeof(Info), cmpFun);
	int left = 0;
	int right = 0;
	int resBegin = -1;
	int resEnd = -1;
	while (right < numall) {

		kCount[allNum[right].group]++;

		while (isCover(kCount, numsSize)) {//满足求最小
			updateIndex(left, right, &resBegin, &resEnd, allNum);
			kCount[allNum[left++].group]--;
		}

		right++;
	}

	int *res = (int *)malloc(sizeof(int) * RETURN_SIZE);
	res[0] = allNum[resBegin].value;
	res[1] = allNum[resEnd].value;
	*returnSize = RETURN_SIZE;
	return res;
}


/*
80. 删除排序数组中的重复项 II
难度中等271收藏分享切换为英文关注反馈
给定一个排序数组，你需要在原地删除重复出现的元素，
使得每个元素最多出现两次，返回移除后数组的新长度。
不要使用额外的数组空间，你必须在原地修改输入数组并在
使用 O(1) 额外空间的条件下完成。
示例 1:
给定 nums = [1,1,1,2,2,3],
函数应返回新长度 length = 5, 并且原数组的前五个元素被修改
为 1, 1, 2, 2, 3 。
你不需要考虑数组中超出新长度后面的元素。
*/
//动态调整移位距离
int removeDuplicates(int* nums, int numsSize)
{
    int flag = 0, temp = 0;
    for(int i=1;i<numsSize;i++){
        if(nums[i] == nums[i-1])
			flag++; //计数
        else
			flag = 0;  //计数器置0
        if(flag>=2)
			temp++;  //移位距离加1

        nums[i-temp] = nums[i]; //移位
    }
    return numsSize - temp;
}

