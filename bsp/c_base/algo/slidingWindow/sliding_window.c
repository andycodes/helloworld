/*
区间的问题几个思路供参考：
1、滑动窗口（双指针）
2、前缀和的差
*/

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
	do {
		what
	}

	right++ or continue;

	满足条件，选最优
	left++;
}


for (int right = 0; right < slen; right++) {
		do {
			what
		}
		满足条件选最优
		left++;
}
*/


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
右指针开始右移，扩大窗口，直到窗口内除了出现次数最多
的字符以外的其他字符数量达到k
右指针再移动会超出k时，左指针开始同时移动，此时窗口
按照之前的大小开始滑动；然后，右指针继续移动直到其它
字符的数量再次超出k的限制，左指针又开始同时移动，如此
循环下去直到右指针移动到字符串终点。
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
		maxCnt = fmax(maxCnt, map[s[right] - 'A']);
		if (right - left + 1 > maxCnt + k) {
			map[s[left] - 'A']--;
			left++;
		}
		ans = fmax(ans, right-left+1);
		right++;
	}

	//return ans;
	return strlen(s) - left;
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

struct Hashmap {
	int key;
	int cnt;
	UT_hash_handle hh;
};

int* shortestSeq(int* big, int bigSize, int* small, int smallSize, int* returnSize)
{
	if (big == NULL || small == NULL || bigSize <= 0 || smallSize <= 0 || smallSize > bigSize) {
		*returnSize = 0;
		return NULL;
	}

	struct Hashmap *hashmap = NULL;

	for (int i = 0; i < smallSize; i++) {
		struct Hashmap *node = (struct Hashmap *)calloc(1, sizeof(struct Hashmap));
		node->key = small[i];
		HASH_ADD_INT(hashmap, key, node);
	}

	int left = 0, right = 0, winCnt = 0, minLen= INT_MAX;
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	while(right < bigSize) {
		struct Hashmap *find = NULL;
		HASH_FIND_INT(hashmap, big + right, find);
		if(find != NULL) {
			if (find->cnt == 0) {
				winCnt++;
			}

			find->cnt++;
		}

		while(winCnt == smallSize) {
			struct Hashmap *findleft = NULL;
			HASH_FIND_INT(hashmap, big + left, findleft);
			if (findleft == NULL) {
				left++;
			} else if (findleft->cnt > 1) {
				findleft->cnt--;
				left++;
			} else {//cnt == 1
				if (minLen > right-left + 1) {
					minLen = right-left + 1;
					res[0] = left;
					res[1] = right;
				}

				findleft->cnt--;
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
18. 四数之和
给定一个包含 n 个整数的数组 nums 和一个目标值 target，
判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的
值与 target 相等？找出所有满足条件且不重复的四元组。
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
	}
}

int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize)
{
	int numTotalSize = 0;
	for (int i = 0; i < numsSize; i++) {
		numTotalSize += numsColSize[i];
	}

	Info allNum[numTotalSize];

	int allNumSize = 0;
	for (int i = 0; i < numsSize; i++) {
		for (int j = 0; j < numsColSize[i]; j++) {
			allNum[allNumSize].value = nums[i][j];
			allNum[allNumSize].group = i;
			allNumSize++;
		}
	}

	int kCount[MAX_NUM] = { 0 };
	qsort(allNum, numTotalSize, sizeof(Info), cmpFun);
	int left = 0;
	int right = 0;
	int resBegin = -1;
	int resEnd = -1;
	while (right < numTotalSize) {

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
	for(int i = 1;i < numsSize; i++) {
		if(nums[i] == nums[i-1])
			flag++; //计数
		else
			flag = 0;  //计数器置0

		if(flag >= 2)
			temp++;  //移位距离加1

		nums[i - temp] = nums[i]; //移位
	}

	return numsSize - temp;
}


/*
1176. 健身计划评估
你的好友是一位健身爱好者。前段日子，他给自己制定了一
份健身计划。现在想请你帮他评估一下这份计划是否合理。
他会有一份计划消耗的卡路里表，其中 calories[i] 给出了你的这
位好友在第 i 天需要消耗的卡路里总量。
为了更好地评估这份计划，对于卡路里表中的每一天，你都
需要计算他 「这一天以及之后的连续几天」 （共 k 天）内消
耗的总卡路里 T：
如果 T < lower，那么这份计划相对糟糕，并失去 1 分；
如果 T > upper，那么这份计划相对优秀，并获得 1 分；
否则，这份计划普普通通，分值不做变动。
请返回统计完所有 calories.length 天后得到的总分作为评估结果。
注意：总分可能是负数。
示例 1：
输入：calories = [1,2,3,4,5], k = 1, lower = 3, upper = 3
输出：0
解释：calories[0], calories[1] < lower 而 calories[3], calories[4] > upper, 总分 = 0.
*/
int dietPlanPerformance(int* calories, int caloriesSize, int k, int lower, int upper)
{
	int index = 0;
	int score = 0;
	int sum = 0;

	for (; index < k; index++) {
		sum += calories[index];
	}

	for (; ; index++) {
		if (sum < lower) {
			score--;
		} else if (sum > upper) {
			score++;
		}

		if (index == caloriesSize) {
			break;
		}

		sum += calories[index] - calories[index - k];
	}
	return score;
}


/*
1040. 移动石子直到连续 II
在一个长度无限的数轴上，第 i 颗石子的位置为 stones[i]。如果
一颗石子的位置最小/最大，那么该石子被称作端点石子。
每个回合，你可以将一颗端点石子拿起并移动到一个未占用
的位置，使得该石子不再是一颗端点石子。
值得注意的是，如果石子像 stones = [1,2,5] 这样，你将无法移动
位于位置 5 的端点石子，因为无论将它移动到任何位置（例
如 0 或 3），该石子都仍然会是端点石子。
当你无法进行任何移动时，即，这些石子的位置连续时，游
戏结束。
要使游戏结束，你可以执行的最小和最大移动次数分别是多
少？ 以长度为 2 的数组形式返回答案：
answer = [minimum_moves, maximum_moves] 。
示例 1：
输入：[7,4,9]
输出：[1,2]
解释：
我们可以移动一次，4 -> 8，游戏结束。
或者，我们可以移动两次 9 -> 5，4 -> 6，游戏结束。
*/
/*
举个例子：初始时有 8 颗石子，在数轴上的有石子的刻度为：
4，6，8，9，15，16，19，20最大值求解方法：石子可以放置的
空间，等于左右两端石子之间的未占用位置。在例子中，一
共有 20-4+1-8 个位置。石子覆盖的线段长度是 20-4 个，加上一
个端点的位置即 20-4+1，再减去已经占用的 8 个位置。用公式
表示为：s1=stones[n-1]-stones[0]+1-ns1=stones[n?1]?stones[0]+1?n。但是第一次
移动的左端点或右端点的石子后，这个移动的石子和它相邻
的那颗石子之间的空间，后面就不能被放置了，因为与他相
邻的那个点变为端点，他们之间的位置不可以被放置了。例
如第一步移动了 4，那么 5 这个位置就不可能放置石子了。
所以要计算不能被访问的空间
s2=min(stones[n-1]-stones[n-2]-1, stones[1]-stones[0] -1)s2=min(stones[n?1]?stones[n?2]?1,stones[1]?stones[0]?1)。
最大值为 s1-s2。因为在后面的步骤里，我们都可以做出策
略，让每一轮左右端点的差值只减 1。最小值求解方法：
如果最后游戏结束，那么一定有 nn 个连续坐标摆满了石子。
如果我们要移动最少，必定要找一个石子序列，使得在 nn 大
小连续的坐标内，初始时有最多的石子。设想有个尺子，上
面有 nn 个刻度点，我们用这个尺子在石子从最左边到最右边
移动，每动一次都查看下在尺子范围内有 mm 个石子，那么要
使这个区间填满，就需要移动 n-mn?m 次。只要在尺子外部有石
子，就有策略填满尺子内的。这些次数中最小的就为虽少次
数。但是有一种特例：1，2，3，4，7这种 1-4 是最好的序列，
但是 7 不能移动到端点，只能 1 先移动到 6，然后 7 移动到 5 解
决，这种情况要用 2 步。就是尺子内的石子都是连续的，中
间没空洞，只在边上有空，要用 2 次。
*/
int* numMovesStonesII(int* stones, int stonesSize, int* returnSize)
{
        qsort(stones, stonesSize, sizeof(stones[0]), cmp_int);

        int minMove=stonesSize;

        for(int i=0,j=0;j<stonesSize;++j)
        {
            //当前窗口的大小大于n
            while(stones[j]-stones[i]+1>stonesSize)i++;

            //当前窗口的石子个数
            int already_stone=(j-i+1);

            //前n-1个石子的顺序连续，最后一个石子不连续，需要移动2步。
            //比如3 4 5 6 10，我们不能直接将10变为2，而是将3变为8，然后10变为7来移动
            if (already_stone==stonesSize-1&&stones[j]-stones[i]+1==stonesSize-1)
                minMove=fmin(minMove,2);
            else
                minMove=fmin(minMove,stonesSize-already_stone);

        }

	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;
	res[0] = minMove;
	res[1] = fmax(stones[stonesSize-1]-stones[1]-stonesSize+2, stones[stonesSize-2]-stones[0]-stonesSize+2);

        return res;
}


/*
1100. 长度为 K 的无重复字符子串
给你一个字符串 S，找出所有长度为 K 且不含重复字符的子串，
请你返回全部满足要求的子串的 数目。
示例 1：
输入：S = "havefunonleetcode", K = 5
输出：6
解释：
这里有 6 个满足题意的子串，分别是：
'havef','avefu','vefun','efuno','etcod','tcode'。
*/
int numKLenSubstrNoRepeats(char * S, int K)
{
    // 存储字符出现频数
    int fre[128] = {0};
    // 窗口左右指针
    int left, right;
    left = right = 0;
    // S长度
    int slen = strlen(S);
    // 窗口内不同字符个数
    int count = 0;
    // 当前窗口宽度
    int width = 0;
    // result
    int res = 0;
    while(right < slen) {

        if(width < K) {
			// 一开始先扩展窗口到宽度为K
		if(fre[S[right++]]++ == 0) count++;
		width++;
        }else{
        	// 宽度为K后固定宽度滑动窗口
            if(--fre[S[left++]] == 0) count--;
            if(fre[S[right++]]++ == 0) count++;
        }

        if(count == K) res++;

    }
    return res;
}

/*
978. 最长湍流子数组
当 A 的子数组 A[i], A[i+1], ..., A[j] 满足下列条件时，我们称其为湍流子数组：

若 i <= k < j，当 k 为奇数时， A[k] > A[k+1]，且当 k 为偶数时，A[k] < A[k+1]；
或 若 i <= k < j，当 k 为偶数时，A[k] > A[k+1] ，且当 k 为奇数时， A[k] < A[k+1]。
也就是说，如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组。

返回 A 的最大湍流子数组的长度。



示例 1：

输入：[9,4,2,10,7,8,8,1,9]
输出：5
解释：(A[1] > A[2] < A[3] > A[4] < A[5])
*/
int cmp(int a,int b)
{
	if(a > b) {
		return 1;
	} else if(a < b) {
		return -1;
	} else {
		return 0;
	}
}

int maxTurbulenceSize(int* A, int ASize)
{
	int ans = 1;
	int anchor = 0;

	for(int i = 1; i < ASize; i++) {
		int c = cmp(A[i-1], A[i]);
		if(i == ASize - 1 || c * cmp(A[i], A[i+1]) != -1) {
			if(c != 0) {
				ans = fmax(ans, i - anchor + 1);
			}
			anchor = i;
		}
	}
	return ans;
}

/*
480. 滑动窗口中位数
中位数是有序序列最中间的那个数。如果序列的大小是偶数，则没有最中间的数；此时中位数是最中间的两个数的平均数。

例如：

[2,3,4]，中位数是 3
[2,3]，中位数是 (2 + 3) / 2 = 2.5
给你一个数组 nums，有一个大小为 k 的窗口从最左端滑动到最右端。窗口中有 k 个数，每次窗口向右移动 1 位。你的任务是找出每次窗口移动后得到的新窗口中元素的中位数，并输出由它们组成的数组。



示例：

给出 nums = [1,3,-1,-3,5,3,6,7]，以及 k = 3。
*/

#if 1
void dqueue_push(int *dqueue, int dqueueSize, int data)
{
    int i;
    for (i = 0; i < dqueueSize - 1; i++) {
        if (data > dqueue[i]) {
            break;
        }
    }

    for (int j = dqueueSize - 1; j > i; j--) {
        dqueue[j] = dqueue[j - 1];
    }

    dqueue[i] = data;
}

void dqueue_del(int *dqueue, int dqueueSize, int data)
{
    int i;
    for (i = 0; i < dqueueSize; i++) {
        if (data == dqueue[i]) {
            break;
        }
    }

    for (int j = i; j < dqueueSize - 1; j++) {
        dqueue[j] = dqueue[j + 1];
    }
}
#else

void dqueue_replace(int *dqueue, int dqueueSize, int oldData, int newData)
{
	for (int i = 0; i < dqueueSize; i++) {
		if (dqueue[i] == oldData) {
			dqueue[i] = newData;
			return;
		}
	}
}
#endif

double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
	*returnSize = 0;
    if (nums == NULL || numsSize <= 0) {
        return NULL;
    }

    double *res = (int *)calloc(numsSize, sizeof(double));
	int dqueue[k];
	memcpy(dqueue, nums, sizeof(int) * k);
	qsort(dqueue, k, sizeof(dqueue[0]), cmp_int);
	res[0] = k % 2 == 1 ? dqueue[k / 2] : (dqueue[k / 2] * 0.5 + dqueue[k / 2 - 1] * 0.5);
	(*returnSize) = 1;

	for (int i = 0; i < numsSize - k; i++) {
		dqueue_del(dqueue, k, nums[i]);
		dqueue_push(dqueue, k, nums[i + k]);
		res[*returnSize] = k % 2 ==1 ? dqueue[k / 2] : (dqueue[k / 2] * 0.5 + dqueue[k / 2 - 1] * 0.5);
		(*returnSize)++;
	}

	return res;
}

/*
727. 最小窗口子序列
给定字符串 S and T，找出 S 中最短的（连续）子串 W ，使得 T 是
W 的 子序列 。
如果 S 中没有窗口可以包含 T 中的所有字符，返回空字符串 ""。
如果有不止一个最短长度的窗口，返回开始位置最靠左的那个。
示例 1：
输入：
S = "abcdebdde", T = "bde"
输出："bcde"
解释：
"bcde" 是答案，因为它在相同长度的字符串 "bdde" 出现之前。
"deb" 不是一
*/
char * minWindow(char * S, char * T)
{
	if(S == T)
		return S;
	int start = 0;
	int end = strlen(S) - 1;
	int s = 0,t = 0;
	while(s < strlen(S)){
		if(S[s] == T[t]) {
			t++;
		}

		if(t == strlen(T)) {
			int right = s;
			t--;
			while(t >= 0) {
				if(S[s] == T[t]){
					t--;
				}
				s--;
			}

			s++;
			if(right - s + 1 < end - start + 1){
				start = s;
				end = right;
			}
			t = 0;
		}
		s++;
	}

	if (end - start + 1 == strlen(S))
		return "";

	char *res = (char *)calloc(20000, sizeof(char));
	strncpy(res, S + start, end - start + 1);
	return res;
}


/*
992. K 个不同整数的子数组
给定一个正整数数组 A，如果 A 的某个子数组中不同整数的个数恰好为 K，则称 A 的这个连续、不一定独立的子数组为好子数组。

（例如，[1,2,3,1,2] 中有 3 个不同的整数：1，2，以及 3。）

返回 A 中好子数组的数目。



示例 1：

输入：A = [1,2,1,2,3], K = 2
输出：7
解释：恰好由 2 个不同整数组成的子数组：[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
*/

/*
第一种是求出不同整数个数<=K的子数组数量，再求出不同整
数个数<=K - 1的子数组数量，两者相减。
*/
int subarraysLessThanKDistinct(int* A, int ASize, int K)
{
	int m[ASize + 1];
	memset(m, 0, sizeof(m));
	int left = 0;
	int right = 0;
	int res = 0;
	int count = 0; //不同整数的个数
	while(right < ASize) {
		m[A[right]]++;
		if(m[A[right]] == 1)
			count++;

		while(count > K){
			m[A[left]]--;
			if(!m[A[left]])  count--;
				left++;
		}
/*
每变动一次right，增加的子数组数量为right - left + 1，right不动，
向左数
*/		res += right - left + 1;
		right++;
	}
	return res;
}

int subarraysWithKDistinct(int* A, int ASize, int K)
{
	return subarraysLessThanKDistinct(A, ASize, K) - subarraysLessThanKDistinct(A, ASize, K - 1);
}

/*
1156. 单字符重复子串的最大长度
难度中等34
如果字符串中的所有字符都相同，那么这个字符串是单字符
重复的字符串。
给你一个字符串 text，你只能交换其中两个字符一次或者什么
都不做，然后得到一些单字符重复的子串。返回其中最长的
子串的长度。

示例 1：
输入：text = "ababa"
输出：3
示例 2：
输入：text = "aaabaaa"
输出：6
*/

int maxRepOpt1(char * text)
{
	int len = strlen(text);
	int cnt[26] = {0};//记录各个字符在text中出现的次数

	for(int i = 0; i < len; i++)
		cnt[text[i]-'a']++;

	char cur_c = text[0];//当前单字符
	int curSize = 1;//当前单字符串长度
	int right = 1;//当前遍历到的字符索引
	int ans = 0;

	while(right < len) {
		while(right < len && text[right] == cur_c){
			right++;
			curSize++;
		}
/*
可以把某个位置的cur_c交换到right位置，使单字符串得以延长
*/
		if(curSize < cnt[cur_c-'a']) {
			curSize++;
			int tmp = right + 1;//继续向后延长单字符串
			while(tmp < len && text[tmp] == cur_c){
				curSize++;
				tmp++;
			}
		}
/*
当aaaba这种情况时，前"交换"的a会在继续延长时再次计数，
所以要取min，达到去重的作用
*/		curSize = fmin(curSize, cnt[cur_c-'a']);
		ans = fmax(ans, curSize);
		if(right < len) {//继续记录下一段单字符串
			cur_c = text[right];
			curSize = 1;
			right++;
		}
	}
	return ans;
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
int findShortestSubArray(int* nums, int numsSize)
{
	int map[50000] = {0};
	int winCnt[50000] = {0};
	int max = 0;

 	for (int i = 0; i < numsSize; i++) {
		max = fmax(max, ++map[nums[i]]);
	}

	int left = 0;
	int right = 0;
	int res = numsSize;

	while(right < numsSize) {
		if (++winCnt[nums[right]] != max) {
			right++;
			continue;
		}

		while((left <= right) && (winCnt[nums[right]] == max)) {
			winCnt[nums[left]]--;
			left++;
		}

		res = fmin(res, right - left + 2);
		right++;
	}

	return res;
}

