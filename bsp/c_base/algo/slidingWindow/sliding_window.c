/*
滑动窗口
一个左指针left，一个右指针right，
窗口扩张：left不变，right++
窗口滑动：left++, right++

子串，子数组问题
*/



/*
面试题59 - II. 队列的最大值
请定义一个队列并实现函数 max_value 得到队列里的最大值，
要求函数max_value、push_back 和 pop_front 的时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1

示例 1：

输入:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出: [null,null,null,2,1,2]
示例 2：

输入:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出: [null,-1,-1]

*/

/*
我们维护一个正常的队列queue，这样push_back, pop_front 直接操作正常队列即可。

问题在于如何在O(1)O(1) 时间 实现max_value? 我们的想法是维护一个递减的双端队列deque。

每次queue入队列的时候，我们deque也入队列，入队列之前我们清除队尾的比入队的元素小的元素。 一句话来说，我们的目的就是维持 deque保持递减性质不变
每次queue pop的时候，我们的deque不一定也要出队列。当且仅当deque的队首元素和queue队首元素一致时候，我们才需要执行deque的出队列的操作
这样max_value我们只需要返回deque的队首元素即可，至此我们终于实现了$O(1)$ 时间 实现max_value

*/
typedef struct {
	struct ListNode *head;
	struct ListNode *mhead;
} MaxQueue;

MaxQueue* maxQueueCreate() {
	MaxQueue * queue = (MaxQueue *)malloc(sizeof(MaxQueue));
	queue->head = slink_init();
	queue->mhead = slink_init();
	return queue;
}

int maxQueueMax_value(MaxQueue* obj) {
	if(slink_empty(obj->mhead))
		return -1;

	return slink_get_first(obj->mhead);
}

void maxQueuePush_back(MaxQueue* obj, int value) {
	slink_push_last(obj->head, value);
	while(!slink_empty(obj->mhead) && value > slink_get_last(obj->mhead)) {
		slink_pop_last(obj->mhead);
	}

	slink_push_last(obj->mhead, value);
}

int maxQueuePop_front(MaxQueue* obj) {
	if (slink_empty(obj->head))
		return -1;
	int ret = slink_pop_first(obj->head);
	if (ret == slink_get_first(obj->mhead)) {
		slink_pop_first(obj->mhead);
	}

	return ret;
}

void maxQueueFree(MaxQueue* obj) {
	free(obj->head);
	free(obj->mhead);
	free(obj);
}

/*
209. 长度最小的子数组
难度中等261
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。如果不存在符合条件的连续子数组，返回 0。
示例:
输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。
进阶:
*/
int minSubArrayLen(int s, int* nums, int numsSize)
{
	int leftidx = 0;
	int rightidx = 0;
	int sum = 0;
	int minlen = 0;
	int minret = INT_MAX;

	if (nums == NULL || numsSize <= 0)
		return 0;

	while(rightidx < numsSize) {
		while(rightidx < numsSize && sum + nums[rightidx] < s) {
			sum += nums[rightidx++];
			minlen++;
		}

		if (rightidx < numsSize) {
			sum += nums[rightidx++];
			minlen++;
		}


		while(sum - nums[leftidx] >= s) {
			sum -= nums[leftidx++];
			minlen--;
		}

		if (sum >= s)
			minret = fmin(minret, minlen);
	}

	return minret == INT_MAX ? 0 : minret;
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
面试题48. 最长不含重复字符的子字符串
难度中等6
请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

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
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

*/

int lengthOfLongestSubstring(char * s)
{
	int left = 0;
	int right = 0;
	int max = 0;

	struct List list;
	queue_init(&list);
	while(s[right] != '\0') {
		while(1) {
			struct DataEntry *entry = ListFindKey(&list, s[right]);
			if (entry != NULL) {
				queue_pop_entry(&list);
				left++;
			} else {
				break;
			}
		}

		queue_push_key(&list, s[right]);
		right++;
		max = fmax(max, right - left);
	}

	return max;
}


/*
1004. 最大连续1的个数 III
难度中等41
给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。
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
给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。
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
建立26个大写字母的映射，用于记录窗口中字符出现的次数，将A存到数组的0号下标的位置
初始窗口指针left，right都为0，移动right，增大窗口，同时更新当前最长重复字符的长度。直到窗口长度过长，即不能通过替换k次形成重复字符时，收缩窗口(此时可以通过k+1次替换满足)，left++。但是这里可以不必更新max_count，因为当我们找到max_count之后，就一定能找到一个长度为d的区间使得max_count + k = d。我们只需要算出这个满足条件的d即可(这里通过right-left+1计算)。
一直更新当前最长重复字符的长度，直到right指针遍历完字符串s

# 用字典保存字母出现的次数，需要替换的字符数目＝窗口字符数目－数量最多的字符数目

用数组记录下当前窗口各个字母的总数和当前窗口中出现次数最多的字母的数量
当：窗口大小 > (最大字母数-k)时扩张移动窗口，否则扩张窗口
当窗口移动到字符串末端后结束，答案为最后窗口的大小

（1）滑动窗口思路，一般大家都能想到；
（2）窗口内所有字符的个数减去最多字符的个数如果小于等于k，即替换后肯定满足条件，我们可以再将滑动窗口的右边界往右移动一下，这是本问题的关键；


假设我们用来替换别的字符的那个字符是c，那么题目可以转变成这样一个问题，在一个window里面，最多有k个不为c的字符，这样才是满足条件的

那么这样的字符c有哪些呢？毫无疑问是set(s)里面的这些字符。

然后我们维护一个window，不断计算不为c的字符的个数counter，如果counter大于n了说明我们怎么替换也不行了，我们就要将start往前挪一格，否则一直挪end。
每次挪完end之后都要记得更新这一轮的最大长度

每个字符c循环后都要更新最终res。

*/
int characterReplacement(char * s, int k){
	int left = 0;
	int right = 0;
	int max = 0;
	int ans = 0;
	int le[26] = {{0}};

	while(right < strlen(s)) {
		int idx = s[right] - 'A';
		le[idx]++;
		max = fmax(max, le[idx]);//当前窗口内的最多字符的个数
		if (right - left + 1 -max > k) {//需要替换的字符个数就是当前窗口的大小减去窗口中数量最多的字符的数量
			le[s[left] - 'A']--;//缩小窗口
			left++;
		}
		ans = fmax(ans, right-left+1);//当窗口内可替换的字符数小于等于k时，我们需要根据该窗口长度来确定是否更新result
		right++;
	}

	return ans;
}
/*
面试题 17.18. 最短超串
难度中等5
假设你有两个数组，一个长一个短，短的元素均不相同。找到长数组中包含短数组所有的元素的最短子数组，其出现顺序无关紧要。
返回最短子数组的左端点和右端点，如有多个满足条件的子数组，返回左端点最小的一个。若不存在，返回空数组。
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

	int left = 0, right = 0, count = 0, minLen= INT_MAX;
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	while(right < bigSize) {
		struct DataEntry *curEntry = hashFindKey(&ht, big[right]);
		if(curEntry != NULL) {
			if (curEntry->value == 0) {
				count++;
			}

			curEntry->value++;
		}

		while(count == smallSize) {
			struct DataEntry *entry;
			entry = hashFindKey(&ht, big[left]);
			if (entry == NULL) {
				left++;
			} else if (entry->value > 1) {
				left++;
				entry->value--;
			} else {//value == 1
				if (minLen > right-left + 1) {
					minLen = right-left + 1;
					res[0] = left;
					res[1] = right;
				}

				entry->value--;
				left++;
				count--;
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
697. 数组的度
难度简单115
给定一个非空且只包含非负数的整数数组 nums,
数组的度的定义是指数组里任一元素出现频数的最大值。
你的任务是找到与 nums 拥有相同大小的度的最短连续子数组，
返回其长度。
示例 1:
输入: [1, 2, 2, 3, 1]
输出: 2
解释:
输入数组的度是2，因为元素1和2的出现频数最大，均为2.
连续子数组里面拥有相同度的有如下所示:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
最短连续子数组[2, 2]的长度为2，所以返回2.
示例 2:
输入: [1,2,2,3,1,4,2]
输出: 6

*/
struct Degree {
	int cnt;
	int start;
	int len;
};

int findShortestSubArray(int* nums, int numsSize)
{
	struct Degree obj[50000];
	memset(obj, 0, sizeof(obj));

	for (int i = 0; i < numsSize; i++) {
		obj[nums[i]].cnt++;
		if (obj[nums[i]].cnt == 1) {
			obj[nums[i]].start = i;
			obj[nums[i]].len = 1;
		} else {
			obj[nums[i]].len = i - obj[nums[i]].start + 1;
		}
	}

	int maxdegree = 0;
	for (int i = 0; i < numsSize; i++) {
		maxdegree = fmax(maxdegree, obj[nums[i]].cnt);
	}

	int minsize = numsSize;
	for (int i = 0; i < numsSize; i++) {
		if (obj[nums[i]].cnt == maxdegree)
			minsize = fmin(minsize, obj[nums[i]].len);
	}

	return minsize;
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
给定一个排序好的数组，两个整数 k 和 x，从数组中找到最靠近 x（两数之差最小）的 k 个数。返回的结果必须要是按升序排好的。如果有两个数与 x 的差值一样，优先选择数值较小的那个数。
示例 1:
输入: [1,2,3,4,5], k=4, x=3
输出: [1,2,3,4]

示例 2:
输入: [1,2,3,4,5], k=4, x=-1
输出: [1,2,3,4]
*/
int g_x;
int cmp_int1(const void* a, const void* b)
{
	int c = *((int *)a);
	int d = *((int *)b);

	if (abs(g_x - c) != abs(g_x - d)) {
		return abs(g_x - c) - abs(g_x - d);
	} else {
		return c - d;
	}
}

int cmp_int ( const void *a , const void *b)
{
        return *(int *)a - *(int *)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
	g_x = x;
	qsort(arr, arrSize, sizeof(arr[0]), cmp_int1);
	qsort(arr, k, sizeof(arr[0]), cmp_int);
	*returnSize = k;
	return arr;
}

/*

方法一：排除法（双指针）
"排除法"的结论：（这个结论对于这道问题来说非常重要，可以说是解题的关键）

如果 x 的值就在长度为 size 区间内（不一定相等），要得到 size - 1 个符合题意的最接近的元素，此时看左右边界：

1、如果左边界与 x 的差值的绝对值较小，删除右边界；
2、如果右边界与 x 的差值的绝对值较小，删除左边界；
3、如果左、右边界与 x 的差值的绝对值相等，删除右边界。

以 arr = [1, 2, 3, 4, 5, 6, 7] , x = 5, k = 3 为例。

思路分析：

1、一个一个删，因为是有序数组，且返回的是连续升序子数组，所以每一次删除的元素一定是位于边界；

2、一共 77 个元素，要保留 33 个元素，因此要删除 44 个元素；

3、因为要删除的元素都位于边界，于是可以使用双指针对撞的方式确定保留区间，即"最优区间"。

*/
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
	int left = 0;
	int right = arrSize - 1;
	int rmnums = arrSize - k;

	while(rmnums > 0) {
		if (x - arr[left] <= arr[right] - x) {
			right--;
		} else {
			left++;
		}

		rmnums--;
	}

	int *ret = (int *)calloc(k, sizeof(int));
	 memcpy(ret, arr + left, sizeof(int) * k);
	*returnSize = k;
	return ret;
}


int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize){
    *returnSize = k;
    int left = 0;
    int right = arrSize - 1;
    while (right - left >= k) {
        if (x * 2 <= arr[right] + arr[left]) {
            --right;
        } else {
            ++left;
        }
    }
    return &arr[left];
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
	int min = INT_MAX;
	int w1Idx = -1;
	int w2Idx = -2;
	for (int i = 0; i < wordsSize; i++) {
		if (strcmp(words[i], word1) == 0) {
			w1Idx = i;
		}

		if (strcmp(words[i], word2) == 0) {
			w2Idx = i;
		}

		if (w1Idx >= 0 && w2Idx >= 0) {
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
int maxArea(int* height, int heightSize){
	if (height == NULL || heightSize <= 0) {
		return 0;
	}

	int area = INT_MIN;
	for(int i = 1; i < heightSize; i++) {
		for (int j = 0; j < i; j++) {
			area = fmax(area, fmin(height[i], height[j]) * (i - j));
		}
	}

	return area;
}
/*
双指针法
最初我们考虑由最外围两条线段构成的区域。
现在，为了使面积最大化，
我们需要考虑更长的两条线段之间的区域。
如果我们试图将指向较长线段的指针向内侧移动，
矩形区域的面积将受限于较短的线段而不会获得任何增加。
但是，在同样的条件下，
移动指向较短线段的指针尽管造成了矩形宽度的减小，
但却可能会有助于面积的增大。因为移动较短线段的
指针会得到一条相对较长的线段，
这可以克服由宽度减小而引起的面积减小。
*/
int maxArea(int* height, int heightSize){
	if (height == NULL || heightSize <= 0) {
		return 0;
	}

	int area = INT_MIN;
	int l = 0, r = heightSize - 1;
        while (l < r) {
            area = fmax(area, fmin(height[l], height[r]) * (r - l));
            if (height[l] < height[r])
                l++;
            else
                r--;
        }
        return area;
}

/*前序和prefixSum  (连续子和)
任意区间数组和均可以使用前缀和来优化
子数组A(i,j]的和为sum[j] - sum[i]
第i个元素的前缀和 = 前i-1个元素之和。
首元素没有前缀，规定为0。
*/

/*
560. 和为K的子数组
给定一个整数数组和一个整数 k，你需要找到该数组中和为
k 的连续的子数组的个数。

示例 1 :

输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
说明 :

数组的长度为 [1, 20,000]。
数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。
通过次数25,598提交次数57,201
*/
int subarraySum(int* nums, int numsSize, int k)
{
	int cnt = 0;
	int prefixSum[numsSize + 1];
	prefixSum[0] = 0;
	for (int i = 1; i <= numsSize; i++) {
		prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
	}

	for (int start = 0; start < numsSize; start++) {
		for (int end = start + 1; end <= numsSize; end++) {
			if (prefixSum[end] - prefixSum[start] == k)
				cnt++;
		}
	}

	return cnt;
}


/*
1423. 可获得的最大点数
几张卡牌 排成一行，每张卡牌都有一个对应的点数。
点数由整数数组 cardPoints 给出。

每次行动，你可以从行的开头或者末尾拿一张卡牌，
最终你必须正好拿 k 张卡牌。

你的点数就是你拿到手中的所有卡牌的点数之和。

给你一个整数数组 cardPoints 和整数 k，请你返回可以获得的
最大点数。



示例 1：

输入：cardPoints = [1,2,3,4,5,6,1], k = 3
输出：12
解释：第一次行动，不管拿哪张牌，你的点数总是 1 。
但是，先拿最右边的卡牌将会最大化你的可获得点数。
最优策略是拿右边的三张牌，最终点数为 1 + 6 + 5 = 12 。
示例 2：

输入：cardPoints = [2,2,2], k = 2
输出：4
解释：无论你拿起哪两张卡牌，可获得的点数总是 4 。
示例 3：

输入：cardPoints = [9,7,7,9,7,7,9], k = 7
输出：55
解释：你必须拿起所有卡牌，可以获得的点数为所有卡牌的点数之和。
示例 4：

输入：cardPoints = [1,1000,1], k = 1
输出：1
解释：你无法拿到中间那张卡牌，所以可以获得的最大点数
为 1 。
示例 5：

输入：cardPoints = [1,79,80,1,1,1,200,1], k = 3
输出：202
*/
int maxScore(int* cardPoints, int cardPointsSize, int k)
{
	int prefixSum[cardPointsSize + 1];
	prefixSum[0] = 0;
	for (int i = 0; i < cardPointsSize; i++) {
		prefixSum[i + 1] = prefixSum[i] + cardPoints[i];
	}

	int max = -1;
	for (int i = 0; i <=  k; i++) {
		max = fmax(max, prefixSum[i] + prefixSum[cardPointsSize] - prefixSum[cardPointsSize - k + i]);
	}

	return max;
}

/*
按题中意思取左取右得最大值，反过来就是求中间连续
子数组得和最小,由于要取 k 张牌，
所以反过来就是在中间找连续的长度为 len(carPoints)-k 的
子数组使其和最小，滑窗将移动 k 次，
不断更新滑窗能得到和的最小值，
最后用输入数组的和减去这个最小值就是结果。
第一排各自代表 index，
第二行代表对应位置的数值,用的是题中第一个范例。
*/
int maxScore(int* cardPoints, int cardPointsSize, int k)
{
	int prefixSum[cardPointsSize + 1];
	prefixSum[0] = 0;
	for (int i = 0; i < cardPointsSize; i++) {
		prefixSum[i + 1] = prefixSum[i] + cardPoints[i];
	}

	int ans = 0x3f3f3f3f;
	int t = cardPointsSize - k;
	for (int j = t;  j <= cardPointsSize; j++) {
		ans = fmin(ans, prefixSum[j] - prefixSum[j - t]);
	}

	return prefixSum[cardPointsSize] - ans;
}

/*
方法一：从中心往两侧延伸【通过】
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
	for (int center = 0; center <= 2 * size -1; center++) {
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
/*中心扩散法。*/
char * longestPalindrome(char * s)
{
	if(strlen(s)==0||strlen(s)==1)
		return s;

	int i,start,left,right,count,len;
	start = len =0;

	for(i = 0; s[i] != '\0'; i += count) {
		count = 1;
		left= i - 1;
		right = i + 1;
		while(s[right] != '\0' && s[i] == s[right]) { //处理重复字符串
			right++;
			count++;
		}

		while(left >= 0 && s[right] != '\0' && s[left] == s[right]) {
			left--;
			right++;
		}

		if(right-left-1>len) {
			start = left+1;
			len = right-left-1;
		}
	}

	s[start + len] = '\0';      // 原地修改返回
	return s + start;
}

