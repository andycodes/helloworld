/*
prefix
子数组和
前序和prefixSum  (连续子和)
任意区间数组和均可以使用前缀和来优化
子数组A(i,j]的和为sum[j] - sum[i]
第i个元素的前缀和 = 前i-1个元素之和。
首元素没有前缀，规定为0

int prefix[arrSize + 1];
prefix[0] = 0;
for (int i = 1; i <= arrSize; i++) {
	prefix[i] = prefix[i - 1] + arr[i - 1];
}

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
1109. 航班预订统计
这里有 n 个航班，它们分别从 1 到 n 进行编号。
我们这儿有一份航班预订表，
表中第 i 条预订记录 bookings[i] = [i, j, k] 意味着我们在从 i 到 j 的
每个航班上预订了 k 个座位。
请你返回一个长度为 n 的数组 answer，
按航班编号顺序返回每个航班上预订的座位数。
示例：

输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
输出：[10,55,45,25,25]


设a[i]表示第i个航班预订的座位数。
定义一个差分数组diff[]，
diff[i]表示第i个航班与第i-1个航班预订座位的差，
即diff[i] = a[i] - a[i - 1]。
这样，我们每次扫描到[i, j, k]，
就只需要将diff[i]增加k，diff[j + 1]减少k即可。
最后，计算a[i] = a[i - 1] + diff[i]，返回a即可。
*/
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize,
int n, int* returnSize){
	int *diff = malloc(20001 * sizeof(int));
	memset((void*)diff,0,20001*sizeof(int));

	for(int i = 0; i < bookingsSize; i++){
		//等差开始加上等差值
		diff[bookings[i][0]-1] += bookings[i][2];
		diff[bookings[i][1]]   -= bookings[i][2]; //等差结束 减掉等差值
	}

	for(int i = 1; i < n; i++) {
		diff[i] += diff[i -1];//推导原始值
	}

	*returnSize = n;
	return diff;
}


/*
974. 和可被 K 整除的子数组
难度中等170
给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。

示例：
输入：A = [4,5,0,-2,-3,1], K = 5
输出：7
解释：
有 7 个子数组满足其元素之和可被 K = 5 整除：
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

*/

/*
暴力超时
整除:
(prefix[j] - prefix[i]) % K == 0
等价
prefix[j] %k == prefix[i] % k
 map[i] * (map[i] - 1) / 2;
*/

int subarraysDivByK(int* A, int ASize, int K)
{
	int prefix[ASize + 1];
	prefix[0] = 0;
	for (int i = 1; i <= ASize; i++) {
		prefix[i] = prefix[i - 1] + A[i - 1];
	}

	int cnt = 0;
	for (int i = 0; i < ASize; i++) {
		for (int j = i + 1; j <= ASize; j++) {
			if ((prefix[j] - prefix[i]) % K == 0) {
				cnt++;
			}
		}
	}

	return cnt;
}

int subarraysDivByK(int* A, int ASize, int K)
{
	if (K == 0 || ASize == 0) {
		return 0;
	}

	int prefix[ASize+1];
	prefix[0]=0;
	for(int i = 1; i <= ASize; i++) {
		prefix[i] = prefix[i - 1]+A[i - 1];
	}

	int map[K];
	memset(map,0,K*sizeof(int));
	for(int i = 0;i<ASize+1;i++){
		map[(prefix[i]%K +K)%K]++;
	}

	int count=0;
	for(int i=0;i<K;i++){
		count+=(map[i]*(map[i]-1))/2;
	}
	return count;
}


/*
42. 接雨水
难度困难1499
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按
此排列的柱子，下雨之后能接多少雨水。

上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，
可以接 6 个单位的雨水（蓝色部分表示雨水）。
感谢 Marcos 贡献此图。
示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/

int trap(int* height, int heightSize)
{
	int ans = 0;
	for (int i = 1; i < heightSize - 1; i++) {
		int max_left = 0, max_right = 0;
		for (int j = i; j >= 0; j--) { //Search the left part for max bar heightSize
			max_left = fmax(max_left, height[j]);
		}
		for (int j = i; j < heightSize; j++) { //Search the right part for max bar heightSize
			max_right = fmax(max_right, height[j]);
		}
		ans += fmin(max_left, max_right) - height[i];
	}
	return ans;
}

int trap(int* height, int heightSize)
{
	if(height == NULL || heightSize <= 0)
		return 0;
	int ans = 0;
	int left_max[heightSize];
	int right_max[heightSize];

	left_max[0] = height[0];
	for (int i = 1; i < heightSize; i++) {
		left_max[i] = fmax(height[i], left_max[i - 1]);
	}

	right_max[heightSize - 1] = height[heightSize - 1];
	for (int i = heightSize - 2; i >= 0; i--) {
		right_max[i] = fmax(height[i], right_max[i + 1]);
	}

	for (int i = 1; i < heightSize - 1; i++) {
		ans += fmin(left_max[i], right_max[i]) - height[i];
	}
	return ans;
}

int trap(int* height, int heightSize)
{
	int left = 0, right = heightSize - 1;
	int ans = 0;
	int left_max = 0, right_max = 0;

	while (left < right) {
		if (height[left] < height[right]) {
			if (height[left] >= left_max)
				left_max = height[left];
			else
				ans += (left_max - height[left]);

			++left;
		} else {
			if (height[right] >= right_max) {
				right_max = height[right];
			} else
				ans += (right_max - height[right]);

			--right;
		}
	}

	return ans;
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
	for (int i = 1; i < cardPointsSize + 1; i++) {
		prefixSum[i] = prefixSum[i - 1] + cardPoints[i - 1];
	}

	int ans = INT_MAX;
	int t = cardPointsSize - k;
	for (int j = t;  j <= cardPointsSize; j++) {
		ans = fmin(ans, prefixSum[j] - prefixSum[j - t]);
	}

	return prefixSum[cardPointsSize] - ans;
}

/*
525. 连续数组
给定一个二进制数组, 找到含有相同数量的 0 和 1 的最长连续子数组（的长度）。



示例 1:

输入: [0,1]
输出: 2
说明: [0, 1] 是具有相同数量0和1的最长连续子数组。
示例 2:

输入: [0,1,0]
输出: 2
说明: [0, 1] (或 [1, 0]) 是具有相同数量0和1的最长连续子数组。
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MMAX(a, b)        ((a) > (b)? (a) : (b))
#define MMIN(a, b)        ((a) < (b)? (a) : (b))

typedef struct _hash_st {
    int key;
    int sid;
    int eid;
    UT_hash_handle hh;
}hash_st;

//【算法思路】积分+hash。经典的01问题，将0转化为-1。
// 问题转换为最长子序列和为0,使用hash表求解
int findMaxLength(int* nums, int numsSize){
    if(numsSize <= 1) {
        return 0;
    }

    hash_st *head = NULL;
    int max = 0;

    //0 -> -1 && 积分 && 填入hash
    int sum = 0;
    for(int i = 0; i < numsSize; i++) {
        //0转-1并积分
        sum += nums[i] == 0? -1 : 1;

        if(sum == 0) {
            //当sum为0则直接为结果
            max = MMAX(max, i + 1);
        } else {
            int key = sum;

            hash_st *tmph;
            HASH_FIND(hh, head, &key, sizeof(key), tmph);
            if(tmph == NULL) {
                tmph = (hash_st *)calloc(1, sizeof(hash_st));
                tmph->key = key;
                tmph->sid = i;

                HASH_ADD_KEYPTR(hh, head, &tmph->key, sizeof(tmph->key), tmph);
            }

            tmph->eid = i;
            max = MMAX(max, i - tmph->sid);
        }
    }

    return max;
}


