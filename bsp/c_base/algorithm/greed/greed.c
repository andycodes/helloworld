
/*
Interval Scheduling 区间调度问题

1) 排序(很多场景)
2) 迭代

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
1029. 两地调度
我们这样来看这个问题，
公司首先将这 2N 个人全都安排飞往 B 市，
再选出 N 个人改变它们的行程，让他们飞往 A 市。
如果选择改变一个人的行程，
那么公司将会额外付出 price_A - price_B 的费用，
这个费用可正可负。


因此最优的方案是，选出 price_A - price_B 最小的 N 个人，
让他们飞往 A 市，其余人飞往 B 市。
算法按照 price_A - price_B 从小到大排序；
将前 N 个人飞往 A 市，其余人飞往 B 市，
并计算出总费用。
*/

struct obj{
    int a;
    int b;
    int diff;
};


int cmp_struct( const void *a , const void *b){
	struct obj *c = (struct obj *)a;
	struct obj *d = (struct obj *)b;

	return c->diff - d->diff;
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize){
        int i;
        struct obj ob[costsSize];
        int sum = 0;

        for(i = 0; i < costsSize; i++){
                ob[i].a = costs[i][0];
                ob[i].b = costs[i][1];
                ob[i].diff = ob[i].a - ob[i].b;
        }

	qsort(ob, costsSize, sizeof(struct obj), cmp_struct);
        for (i = 0;i<costsSize/2;i++){
            sum += ob[i].a;
        }

        for (i = costsSize/2;i<costsSize;i++){
            sum += ob[i].b;
        }

        return sum;
}


/*
121. 买卖股票的最佳时机
给定一个数组，
它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票），
设计一个算法来计算你所能获取的最大利润。

注意你不能在买入股票前卖出股票。
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，
在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。


解题思路： 股票买卖策略：
单独交易日：设今天价格 p1、明天价格 p2，则今天买入、
明天卖出可赚取金额 p2-p1（负值代表亏损）。
连续上涨交易日： 设此上涨交易日股票价格分别为
p1,p2,.....pn，则第一天买最后一天卖收益最大，�
pn-p1；等价于每天都买卖，�
pn-p1=(p2-p1)+(p3-p2)+(p4-p3)+....+(pn-P(n-1))。
连续下降交易日： 则不买卖收益最大，即不会亏钱。
算法流程：  遍历整个股票交易日价格列表 price，
策略是所有上涨交易日都买卖（赚到所有利润），
所有下降交易日都不买卖（永不亏钱）。
设 tmp 为第 i-1 日买入与第 i 日卖出赚取的利润，
即 tmp = prices[i] - prices[i - 1] ； 当该天利润为正 tmp > 0，
则将利润加入总利润 profit；当利润为 00 或为负，
则直接跳过； 遍历完成后，返回总利润 profit。

*/
int maxProfit(int* prices, int pricesSize){
        int profit = 0;
        for (int i = 1; i <pricesSize; i++) {
            int tmp = prices[i] - prices[i - 1];
            if (tmp > 0) profit += tmp;
        }
        return profit;
}


/*
1221. 分割平衡字符串
在一个「平衡字符串」中，'L' 和 'R' 字符的数量是相同的。

给出一个平衡字符串 s，
请你将它分割成尽可能多的平衡字符串。

返回可以通过分割得到的平衡字符串的最大数量。

问题分析：分割平衡串，得到尽可能多的平衡串。
这是一个适用贪心算法的问题，
在适当的位置截断源串得到平衡子串，
截断后前后子串的计数不互相影响（无后效性），
且所有局部最优相加即为整体的最优解。
解决思路：

设置一个'L'与'R'的差值计数器diffCount，
设置一个平衡子串计数器count；
顺序遍历源串字符，遇L则diffCount+1，遇到R则diffCount-1；
每遍历一个字符检查一次diffCount是否为0，若为0则count+1
*/

int balancedStringSplit(char * s) {
	int diffCnt = 0;
	int count = 0;

	if (s == NULL)
		return 0;

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'L')
			diffCnt++;
		else
			diffCnt--;

		if (diffCnt == 0)
			count++;
	}

	return count;
}


/*
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。
但是，每个孩子最多只能给一块饼干。对每个孩子 i ，
都有一个胃口值 gi ，这是能让孩子们满足胃口的饼干
的最小尺寸；并且每块饼干 j ，都有一个尺寸 sj 。
如果 sj >= gi ，
我们可以将这个饼干 j 分配给孩子 i ，
这个孩子会得到满足。
你的目标是尽可能满足越多数量的孩子，
并输出这个最大数值。

注意：

你可以假设胃口值为正。
一个小朋友最多只能拥有一块饼干。

示例 1:

输入: [1,2,3], [1,1]

输出: 1

解释:
你有三个孩子和两块小饼干，
3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，
由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。
示例 2:

输入: [1,2], [1,2,3]

输出: 2

*/

int cmp_int ( const void *a , const void *b){
        return *(int *)a - *(int *)b;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){

	int ig = 0;
	int is = 0;
	int out = 0;

	qsort(g,gSize,sizeof(int),cmp_int);
	qsort(s,sSize,sizeof(int),cmp_int);

	while((ig < gSize) && (is < sSize)) {
		if (g[ig] <= s[is]) {
			out++;
			ig++;
			is++;
		}else {
			is++;
		}
	}

	return out;
}

/*
给定一个整数数组 A，我们只能用以下方法修
改该数组：我们选择某个个索引 i 并将 A[i] 替换为 -A[i]，
然后总共重复这个过程 K 次。
（我们可以多次选择同一个索引 i。）

以这种方式修改数组后，返回数组可能的最大和。

*/

/*第一种：每次取反前，将数组排序，
取反最小值，速度最慢*/
int largestSumAfterKNegations(int* A, int ASize, int K){
	int sum = 0;
	int tmp;

	if (A == NULL || ASize <= 0)
		return 0;

	for (int i = 0; i < K; i++) {
		qsort(A,ASize,sizeof(int),cmp_int);
		A[0] = -A[0];
	}

	for (int i = 0; i < ASize; i++) {
		sum += A[i];
	}

	return sum;
}

/*
对K做分析，分3种情况：
1，k小于负数的个数：直接将最小的负数取反
2，k多于负数个数，但是多出来的部分是偶数：
所有负数取反后，直接返回和
3，多出负数的部分是奇数：
将非负数数字排序，把最小数字取反，返回和
*/

#define m_sum()\
	for (int i = 0; i < ASize; i++) {\
		sum += A[i];\
	}\

int largestSumAfterKNegations(int* A, int ASize, int K){
	int tmp;
	int sum = 0;
	int i = 0;

	if (A == NULL || ASize <= 0)
		return 0;

	qsort(A,ASize,sizeof(int),cmp_int);

	if (A[K -1] <= 0) {
		for (; i < K;i++) {
			A[i] = -A[i];
		}

		m_sum();
		return sum;
	}

	for (i = 0; i < K && A[i] < 0; i++) {
			A[i] = -A[i];
	}

	if ((K -i)%2 == 0) {
		m_sum();
		return sum;
	}

	qsort(A,ASize,sizeof(int),cmp_int);
	A[0] = -A[0];

	m_sum();
	return sum;
}


/*
870. 优势洗牌
给定两个大小相等的数组 A 和 B，A 相对于
B 的优势可以用满足 A[i] > B[i] 的索引 i 的数目来描述。

返回 A 的任意排列，使其相对于 B 的优势最大化。



示例 1：

输入：A = [2,7,11,15], B = [1,10,4,11]
输出：[2,11,7,15]

*/
struct obj {
	int data;
	int index;
};

int cmp_struct( const void *a , const void *b){
	struct obj *c = (struct obj *)a;
	struct obj *d = (struct obj *)b;

	return c->data- d->data;
}

int* advantageCount(int* A, int ASize, int* B, int BSize, int* returnSize){
    int l = 0;
    int r = ASize - 1;
	struct obj *ao = (struct obj *)malloc(sizeof(struct obj) * ASize);
	struct obj *bo = (struct obj *)malloc(sizeof(struct obj) * BSize);
	int *ret = (int *)malloc(sizeof(int) * ASize);

	for (int i = 0; i < ASize; i++) {
		ao[i].data = A[i];
		ao[i].index = i;

		bo[i].data = B[i];
		bo[i].index = i;
	}

	qsort(ao, ASize, sizeof(struct obj), cmp_struct);
	qsort(bo, ASize, sizeof(struct obj), cmp_struct);
    	int j = BSize - 1;
	for (int i = 0; i < ASize; i++) {
		if (ao[i].data > bo[l].data) {
			ret[bo[l].index] = ao[i].data;
            		l++;
		} else {
			ret[bo[r].index] = ao[i].data;
            		r--;
		}
	}

	*returnSize = ASize;
	return ret;
}

/*
1282. 用户分组
有 n 位用户参加活动，他们的 ID 从 0 到 n - 1，每位用户都 恰好 属于某一用户组。给你一个长度为 n 的数组 groupSizes，其中包含每位用户所处的用户组的大小，请你返回用户分组情况（存在的用户组以及每个组中用户的 ID）。

你可以任何顺序返回解决方案，ID 的顺序也不受限制。此外，题目给出的数据保证至少存在一种解决方案。



示例 1：

输入：groupSizes = [3,3,3,3,3,1,3]
输出：[[5],[0,1,2],[3,4,6]]
解释：
其他可能的解决方案有 [[2,1,6],[5],[0,4,3]] 和 [[5],[0,6,2],[4,3,1]]。


方法一：哈希映射
对于两个用户 x 和 y，如果 groupSize[x] != groupSize[y]，它们用户组的大小不同，那么它们一定不在同一个用户组中。因此我们可以首先对所有的用户进行一次【粗分组】，用一个哈希映射（HashMap）来存储所有的用户。哈希映射中键值对为 (gsize, users)，其中 gsize 表示用户组的大小，users 表示满足用户组大小为 gsize，即 groupSize[x] == gsize 的所有用户。这样以来，我们就把所有用户组大小相同的用户都暂时放在了同一个组中。

在进行了【粗分组】后，我们可以将每个键值对 (gsize, users) 中的 users 进行【细分组】。由于题目保证了给出的数据至少存在一种方案，因此我们的【细分组】可以变得很简单：只要每次从 users 中取出 gsize 个用户，把它们放在一个组中就可以了。在进行完所有的【细分组】后，我们就得到了一种满足条件的分组方案。

*/
struct bigcase {
	int cnt;
	int idx[1024];
};

int** groupThePeople(int* groupSizes, int groupSizesSize,
	int* returnSize, int** returnColumnSizes) {
	int ** res = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;

	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	struct bigcase array[groupSizesSize + 1];
	memset(array, 0, sizeof(array));

	for (int i = 0; i < groupSizesSize; i++) {
		int curSize = groupSizes[i];
		array[curSize].idx[array[curSize].cnt++] = i;
	}

	for (int i = 0; i < groupSizesSize + 1; i++) {
		int k = 0;
		while(array[i].cnt - k * i > 0) {
			res[*returnSize] = (int *)calloc(i, sizeof(int));
			for(int j = 0; j < i ; j++) {
				res[*returnSize][j] = array[i].idx[j + k * i];
			}
			(*returnColumnSizes)[*returnSize] = i;
			(*returnSize)++;
			k++;
		}
	}

	return res;
}

/*
1094. 拼车
难度中等22
假设你是一位顺风车司机，车上最初有 capacity 个空座位可以用来载客。由于道路的限制，车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向，你可以将其想象为一个向量）。
这儿有一份行程计划表 trips[][]，其中 trips[i] = [num_passengers, start_location, end_location] 包含了你的第 i 次行程信息：
"	必须接送的乘客数量；
"	乘客的上车地点；
"	以及乘客的下车地点。
这些给出的地点位置是从你的 初始 出发位置向前行驶到这些地点所需的距离（它们一定在你的行驶方向上）。
请你根据给出的行程计划表和车子的座位数，来判断你的车是否可以顺利完成接送所用乘客的任务（当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false）。

示例 1：
输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false
示例 2：
输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true

*/

/*
离散特点
本题意思清晰。 （详见NOIP2012D2T2 借教室）
简单看成给一个全0数组， 每一次给3个参数a, b, ca,b,c. 即意味着在[b, c)[b,c)区间每个数都加上aa. 最后问最大值是否超过capacitycapacity.

解法0: 暴力
针对每一个需求， 在区间[b, c)[b,c)每一个值都加上aa， 最后扫描一遍数组则可以得到最大值， 与capacitycapacity比较即可. 鉴于这道题数据范围很小， 可以通过。
时间复杂度: O(nm)O(nm)
空间复杂度: O(m)O(m)
其中nn为拼车需求数， mm为路的长度。

解法1： 线段树
典型区间加，区间最大值问题。 用线段树即可。

时间复杂度: O(mlogm)O(mlogm)
空间复杂度: O(mlogm)O(mlogm)

解法2： 差分数组

给出一个数组arrayarray， 则其差分数组diffdiff定义为

diff=
{
array[i] & (i = 0)
array[i] - array[i-1] & ( i > 0)
}




举个例子, a = [1,3,6,10,15]a=[1,3,6,10,15]时， 其差分数组为[1,2,3,4,5][1,2,3,4,5].

那么针对这道题， 我们针对原数组连续一段加上a的时候， 若直接在原数组操作， 则需要c-bc?b次， 而在差分数组上则只需要2次。 这样即可减少修改次数以降低时间复杂度。
举个例子， a = [0,0,0,0,0,0]a=[0,0,0,0,0,0], 若给出(a, b, c) = (3, 2, 5)(a,b,c)=(3,2,5), 则原数组变为[0,0,3,3,3,0][0,0,3,3,3,0], 差分数组变为[0,0,3,0,0,-3][0,0,3,0,0,?3]仅修改两个值。

由差分数组得到原数组时， 只需要逆向变化即可。

时间复杂度: O(m)O(m)
空间复杂度: O(m)O(m)

*/

#define MAX_POSITION  1001
bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity)
{
    int route[MAX_POSITION] = {0};
    int maxCap = 0;
    // 遍历所有的旅途，将所有的路途信息写入到route中，route元素大小是乘客的数量
    for (int i = 0; i < tripsSize; i++) {
        // 终点不需要增加权重，因为终点是下车，但是起点需要增加权重
        for (int j = trips[i][1]; j < trips[i][2]; j++) {
            route[j] += trips[i][0];
            if (maxCap < route[j]) {
                maxCap = route[j];
            }
        }
    }

    return maxCap > capacity ? false : true;
}

/*
由于终点都是先下后上的所以需要终点人就下车，起点和终点前一个点都在车上，在a[3]到a[6-1]都需要+2，全部行程加完后，然后判断数组有没有出现超过座位的数字就行，
时间复杂度O(n)，是不是简单到爆又容易理解！！！

*/
bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
	int map[1024] = {{0}};

	for (int i = 0; i < tripsSize; i++) {
		for (int j = trips[i][1]; j < trips[i][2];j++) {
			map[j] += trips[i][0];
		}
	}

	for (int i = 0; i < 1024; i++) {
		if(map[i] > capacity)
			return false;
	}

	return true;
}

/*
本题直接解答比较复杂，可以采用统计学的方法进行加加减减操作，可以很容易解答本题。
因为 0 <= trips[i][1] < trips[i][2] <= 1000，可以开一个大小为 1001 的数组 cnt 来代表每个地点的人数。
遍历 trips，在上车点加上对应人数，在下车点减去对应人数。
最终数组 cnt 每个位置的前缀和就是对应地点上的乘客数量，判断是否满足条件就比较简单了。


相对前一站的人数变化
直接创建数组缓存每个车站的人数变动，检索时判断和值是否超限即可

*/
bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
	int map[1024] = {{0}};

	for (int i = 0; i < tripsSize; i++) {
		map[trips[i][1]] += trips[i][0];
		map[trips[i][2]] -= trips[i][0];
	}

	int curStateTotal = 0;
	for (int i = 0; i < 1024; i++) {
		curStateTotal += map[i];
		if(curStateTotal > capacity)
			return false;
	}

	return true;
}

