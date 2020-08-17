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

    bool circularArrayLoop(int* nums, int numsSize) {
	if (nums == NULL || numsSize <= 1)
		return false;

	int n=numsSize;
        bool visited[n];
	memset(visited, 0, sizeof(visited));
        for(int slow=0;slow<n;slow++)
        {
            if(visited[slow])
				continue;

            visited[slow]=true;
			int map[5000 *2];
			memset(map, 0, sizeof(map));
            while(true)
            {
                int fast=((slow+nums[slow])%n+n)%n;
                if(fast==slow||nums[fast]*nums[slow]<0)
                	break;
		   if (map[fast] != 0)
					return true;
		map[slow] = 1;
		visited[fast]=true;

		slow=fast;
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

/*
713. 乘积小于K的子数组
难度中等135
给定一个正整数数组 nums。
找出该数组内乘积小于 k 的连续的子数组的个数。
示例 1:
输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8个乘积小于100的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
说明:
"	0 < nums.length <= 50000
"	0 < nums[i] < 1000
"	0 <= k < 10^6

*/
int numSubarrayProductLessThanK(int* nums, int numsSize, int k)
{
        if (k <= 1) return 0;
        int prod = 1, ans = 0, left = 0;
        for (int right = 0; right < numsSize; right++) {
            prod *= nums[right];
            while (prod >= k) prod /= nums[left++];
            ans += right - left + 1;
        }
        return ans;
}

/*
76. 最小覆盖子串
难度困难695
给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字符的最小子串。

示例：
输入：S = "ADOBECODEBANC", T = "ABC"
输出："BANC"

*/
char * minWindow(char * s, char * t){
    if (s == NULL || t == NULL) {
        return NULL;
    }

    int len = (int)strlen(s);
    int lent = (int)strlen(t);

    char *out = (char *)malloc(len + 1);
    if (out == NULL) {
        return NULL;
    }

    int outLen = 0;
    memset(out, 0, len + 1);
    if (len < lent || lent == 0) {
        return out;
    }

    int map[128] = {0};
    int mapt[128] = {0};
    int cnt = 0;
    /* 1. 初始窗口是短串长度， 先遍历一遍 得到长串中能匹配到短串的字符个数 */
    for (int i = 0; i < lent; i++) {
        mapt[t[i]]++;
        map[s[i]]++;
    }
    for (int i = 0; i < 128; i++) {
        if (mapt[i] > 0) {
            /* 临界点，只要 <= 短串 就是有效计数, 再大就是多余的了 */
            cnt += (map[i] >= mapt[i]? mapt[i] : map[i]);
        }
    }

    /* 2. 当计数等于短串长度就是满足条件了 */
    if (cnt == lent) {
        outLen = lent;
        memcpy(out, s, outLen);
        return out;
    }

    /* 3. 滑动窗口 */
    int l = 0;
    int r = lent;
    for (; r < len; r++) {
        if (mapt[s[r]] == 0) {
            continue;
        }

        map[s[r]]++;
        if (map[s[r]] <= mapt[s[r]]) {
            /* 临界点，只要 <= 短串 就是有效计数, 再大就是多余的了 */
            cnt++;
        }

        if (cnt == lent) {
            /* 从左侧开始校验 找到临界点（map[s[l]] == mapt[s[l]]）删除多余数据 */
            while (mapt[s[l]] == 0 || map[s[l]] > mapt[s[l]]) {
                map[s[l++]]--;
            }

            int cpLen = r - l + 1;
            if (outLen == 0 ||  cpLen < outLen) {
                memset(out, 0, len + 1);
                memcpy(out, s + l, cpLen);
                outLen = cpLen;
            }

            /* 临界点 */
            cnt--;
            map[s[l++]]--;
        }
    }

    return out;
}

#define MAX_HASH_LEN 128
char * minWindow(char * s, char * t){
    int slen = strlen(s);
    int tlen = strlen(t);
    if (slen == 0 || tlen == 0 || slen < tlen) {
        return "";
    }
    int shash[MAX_HASH_LEN] = {0};
    int thash[MAX_HASH_LEN] = {0};
    int i;
    int left = 0, right = 0;
    int matchCnt = 0;
    int minLen = slen + 1; // 小细节 保证s和t有一个字符也能处理
    int minLeft = 0;
    int minRight = 0;
    int index = 0;
    char *res = (char*)malloc(sizeof(char) * (slen + 1));
    memset(res, 0, (slen + 1));

    for (i = 0; i < tlen; i++) {
        thash[t[i]]++;
    }

    while (right < slen) {
        char c = s[right];
        right++;
        // 更新数据 t匹配不到，right往右+1
        if (thash[c] == 0) {
            continue;
        }

        // 匹配到了，s匹配项比t小 matchCnt++
        // s匹配项比t大，说明此item重复，不需要再算进来
        // 代码块1
        if (shash[c] < thash[c]) {
            matchCnt++;
        }
        shash[c]++;

        while (matchCnt == tlen) {
            if (right - left < minLen) {
                // 更新记录
                minLeft = left;
                minRight = right;
                minLen = right - left;
            }

            char d = s[left];
            left++;
            // 更新数据
            // thash[d] == 0 标识left所指元素非关键
            if (thash[d] == 0) {
                continue;
            }

            // shash肯定是有值的，需要减1
            shash[d]--;
            // 与代码块1 对称着写就行
            // 若果深究原理，如果s和t是匹配的，s匹配项不多于t，那么随着left的向右，matchCnt需要减1
            if (shash[d] < thash[d]) {
                matchCnt--;
            }

        }
    }

    s[minRight] = '\0';
    return &s[minLeft];
}

/*
632. 最小区间
难度困难230
你有 k 个升序排列的整数列表。找到一个最小区间，使得 k 个列表中的每个列表至少有一个数包含在其中。
我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小。

示例：
输入：[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
输出：[20,24]
解释：
列表 1：[4, 10, 15, 24, 26]，24 在区间 [20,24] 中。
列表 2：[0, 9, 12, 20]，20 在区间 [20,24] 中。
列表 3：[5, 18, 22, 30]，22 在区间 [20,24] 中。
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define RETURN_SIZE 2
 #define MAX_NUM 3500
typedef struct tagInfo {
    int value;
    int index;
} Info;
int cmpFun(const void *a, const void *b)
{
    Info *temp1 = (Info *)a;
    Info *temp2 = (Info *)b;
    if (temp1->value > temp2->value) {
        return 1;
    } else if (temp1->value < temp2->value) {
        return -1;
    } else {
        return 0;
    }
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
void updateIndex(int begin, int end, int *resBegin, int *resEnd, Info *allNum)
{
    if ((*resBegin == -1) ||
        (allNum[end].value - allNum[begin].value < allNum[*resEnd].value - allNum[*resBegin].value) ||
        (allNum[end].value - allNum[begin].value == allNum[*resEnd].value - allNum[*resBegin].value &&
         begin < *resBegin)) {
        *resBegin = begin;
        *resEnd = end;
        return;
    }
}
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize){
    int numall = 0;
    for (int i = 0; i < numsSize; i++) {
        numall += numsColSize[i];
    }
    Info *allNum = NULL;
    allNum = (Info *) malloc(sizeof(Info) * numall);
    if (allNum == NULL) {
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsColSize[i]; j++) {
            allNum[index].value = nums[i][j];
            allNum[index].index = i;
            index++;
        }
    }
    int kCount[MAX_NUM] = { 0 };
    qsort(allNum, numall, sizeof(Info), cmpFun);
    int begin = 0;
    int end = 0;
    int resBegin = -1;
    int resEnd = -1;
    while (end < numall) {
        kCount[allNum[end++].index]++;
        while (isCover(kCount, numsSize)) {
            updateIndex(begin, (end - 1), &resBegin, &resEnd, allNum);
            kCount[allNum[begin++].index]--;
        }
    }
    int *res = (int *)malloc(sizeof(int) * RETURN_SIZE);
    res[0] = allNum[resBegin].value;
    res[1] = allNum[resEnd].value;
    free(allNum);
    *returnSize = RETURN_SIZE;
    return res;
}