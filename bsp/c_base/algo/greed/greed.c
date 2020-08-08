
/*
Interval Scheduling 区间调度问题

1) 排序(很多场景)
2) 迭代

*/

/*
1029. 两地调度
难度简单122
公司计划面试 2N 人。第 i 人飞往 A 市的费用为 costs[i][0]，
飞往 B 市的费用为 costs[i][1]。
返回将每个人都飞到某座城市的最低费用，要求每个城市都
有 N 人抵达。
示例：
输入：[[10,20],[30,200],[400,50],[30,20]]
输出：110
解释：
第一个人去 A 市，费用为 10。
第二个人去 A 市，费用为 30。
第三个人去 B 市，费用为 50。
第四个人去 B 市，费用为 20。

最低总费用为 10 + 30 + 50 + 20 = 110，每个城市都有一半的人在面试。

*/
/*按照每个职员两个地方的费用差值排序*/
int cmp_doublePoint(const void *a, const void *b)
{
	int ** aa =  (int **)a;
	int ** bb = (int **)b;

	return (aa[0][0] - aa[0][1]) - (bb[0][0] - bb[0][1]);
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize)
{
	qsort(costs, costsSize, sizeof(costs[0]), cmp_doublePoint);
	int sum = 0;

	for (int i = 0; i < costsSize / 2 ; i++) {
		sum += costs[i][0];
	}

	for (int i = costsSize / 2; i < costsSize; i++) {
		sum += costs[i][1];
	}

	return sum;
}

/*
121. 买卖股票的最佳时机
难度简单1126
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
注意：你不能在买入股票前卖出股票。
示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/
/*
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
int maxProfit(int* prices, int pricesSize)
{
	int profit = 0;
	for (int i = 1; i <pricesSize; i++) {
		int tmp = prices[i] - prices[i - 1];
		if (tmp > 0)
			profit += tmp;
	}

	return profit;
}
int maxProfit(int* prices, int pricesSize)
{
	int minprice = INT_MAX;
	int maxprofix = 0;

	for (int i = 0; i < pricesSize; i++) {
		maxprofix = fmax(maxprofix, prices[i] - minprice);
		minprice = fmin(minprice, prices[i]);
	}

	return maxprofix;
}

/*
1221. 分割平衡字符串
难度简单60
在一个「平衡字符串」中，'L' 和 'R' 字符的数量是相同的。
给出一个平衡字符串 s，请你将它分割成尽可能多的平衡字符串。
返回可以通过分割得到的平衡字符串的最大数量。
示例 1：
输入：s = "RLRRLLRLRL"
输出：4
解释：s 可以分割为 "RL", "RRLL", "RL", "RL", 每个子字符串中都包含相同数量的 'L' 和 'R'。
示例 2：
输入：s = "RLLLLRRRLR"
输出：3
解释：s 可以分割为 "RL", "LLLRRR", "LR", 每个子字符串中都包含相同数量的 'L' 和 'R
*/
/*
解决思路：
设置一个'L'与'R'的差值计数器diffCount，
设置一个平衡子串计数器count；
顺序遍历源串字符，遇L则diffCount+1，遇到R则diffCount-1；
每遍历一个字符检查一次diffCount是否为0，若为0则count+1
*/
int balancedStringSplit(char * s)
{
	int diffCnt = 0;
	int count = 0;

	if (s == NULL)
		return 0;

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'L')
			diffCnt++;
		else
			diffCnt--;

/*
RLRRLL diffCnt = 0
RL diffCnt = 0
RRLL diffCnt = 0
*/
		if (diffCnt == 0)
			count++;
	}

	return count;
}

/*
455. 分发饼干
难度简单187
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。对每个孩子 i ，都有一个胃口值 gi ，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j ，都有一个尺寸 sj 。如果 sj >= gi ，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。
注意：
你可以假设胃口值为正。
一个小朋友最多只能拥有一块饼干。
示例 1:
输入: [1,2,3], [1,1]

输出: 1

解释:
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。
示例 2:
输入: [1,2], [1,2,3]

输出: 2

解释:
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.
 '。
*/
int findContentChildren(int* g, int gSize, int* s, int sSize)
{
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
1005. K 次取反后最大化的数组和
难度简单52
给定一个整数数组 A，我们只能用以下方法修改该数组：我们选择某个索引 i 并将 A[i] 替换为 -A[i]，然后总共重复这个过程 K 次。（我们可以多次选择同一个索引 i。）
以这种方式修改数组后，返回数组可能的最大和。
示例 1：
输入：A = [4,2,3], K = 1
输出：5
解释：选择索引 (1,) ，然后 A 变为 [4,-2,3]。
示例 2：
输入：A = [3,-1,0,2], K = 3
输出：6
解释：选择索引 (1, 2, 2) ，然后 A 变为 [3,1,0,2]。
*/

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

int largestSumAfterKNegations(int* A, int ASize, int K)
{
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
			ret[bo[l].index] = ao[i].data; // 如果A数组的值大于B数组的值则把A[i]的值赋给list数组中的B数组的索引。
            		l++;
		} else {
			ret[bo[r].index] = ao[i].data;// 如果是小于等于则把A[i]的值放在list数组中B数组最大的索引位置。
            		r--;
		}
	}

	*returnSize = ASize;
	return ret;
}

/*
1282. 用户分组
有 n 位用户参加活动，他们的 ID 从 0 到 n - 1，每位用户都 恰好
属于某一用户组。给你一个长度为 n 的数组 groupSizes，其中包含
每位用户所处的用户组的大小，请你返回用户分组情况（存在
的用户组以及每个组中用户的 ID）。
你可以任何顺序返回解决方案，ID 的顺序也不受限制。此外，
题目给出的数据保证至少存在一种解决方案。
示例 1：
输入：groupSizes = [3,3,3,3,3,1,3]
输出：[[5],[0,1,2],[3,4,6]]
解释：
其他可能的解决方案有 [[2,1,6],[5],[0,4,3]] 和 [[5],[0,6,2],[4,3,1]]。
*/
/*
方法一：哈希映射
对于两个用户 x 和 y，如果 groupSize[x] != groupSize[y]，它们用户组的
大小不同，那么它们一定不在同一个用户组中。因此我们可
以首先对所有的用户进行一次【粗分组】，用一个哈希映射（
HashMap）来存储所有的用户。哈希映射中键值对为 (gsize, users)，
其中 gsize 表示用户组的大小，users 表示满足用户组大小为 gsize，
即 groupSize[x] == gsize 的所有用户。这样以来，我们就把所有用户
组大小相同的用户都暂时放在了同一个组中。

在进行了【粗分组】后，我们可以将每个键值对 (gsize, users) 中
的 users 进行【细分组】。由于题目保证了给出的数据至少存
在一种方案，因此我们的【细分组】可以变得很简单：只要
每次从 users 中取出 gsize 个用户，把它们放在一个组中就可以了。
在进行完所有的【细分组】后，我们就得到了一种满足条件
的分组方案。
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
假设你是一位顺风车司机，车上最初有 capacity 个空座位可以用
来载客。由于道路的限制，车 只能 向一个方向行驶（也就是
说，不允许掉头或改变方向，你可以将其想象为一个向量）。
这儿有一份行程计划表 trips[][]，其中 trips[i] = [num_passengers, start_location,
end_location] 包含了你的第 i 次行程信息：
"	必须接送的乘客数量；
"	乘客的上车地点；
"	以及乘客的下车地点。
这些给出的地点位置是从你的 初始 出发位置向前行驶到这些
地点所需的距离（它们一定在你的行驶方向上）。
请你根据给出的行程计划表和车子的座位数，来判断你的车
是否可以顺利完成接送所用乘客的任务（当且仅当你可以在
所有给定的行程中接送所有乘客时，返回 true，否则请返回 false）。
示例 1：
输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false
示例 2：
输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true

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

/*
991. 坏了的计算器
难度中等57
在显示着数字的坏计算器上，我们可以执行以下两种操作：
"	双倍（Double）：将显示屏上的数字乘 2；
"	递减（Decrement）：将显示屏上的数字减 1 。
最初，计算器显示数字 X。
返回显示数字 Y 所需的最小操作数。
示例 1：
输入：X = 2, Y = 3
输出：2
解释：先进行双倍运算，然后再进行递减运算 {2 -> 4 -> 3}.

*/
/*
灵感来自示例，首先由于计算器只能双倍或递减，XY又都为整数，因此，当X > Y时，只能递减X-Y次达到目的。当X = Y ，无需操作，可以和上一个条件一起判断。
当Y > X时，如果Y是一个奇数，那么得到它的最后一步必然是递减。如果Y是一个偶数，如果得到它的最后一步是递减，那么倒数第二步也应该是递减，但Y是一个大于X的数，因此X变成Y时一定经过了双倍，那么与其双倍后进行递减，不如先递减再双倍，花费的步数应该会更少，至少能持平。
那么问题就变成了递归问题。当Y > X时且Y是奇数时，将它加一变成偶数，并且总步数等于1 + brokenCalc(X,(Y+1))，当Y是偶数时，总步数等于1 + brokenCalc(X,Y/2)。

*/
int brokenCalc(int X, int Y)
{
	if (Y <= X)
		return X - Y;
	if (Y % 2 == 0) {
		return 1 + brokenCalc(X , Y /2);
	} else
		return 1 + brokenCalc(X , Y + 1);
}

/*
946. 验证栈序列 see stack
方法一： 贪心
思路
所有的元素一定是按顺序 push 进去的，重要的是怎么 pop 出来？
假设当前栈顶元素值为 2，同时对应的 popped 序列中下一个要
pop 的值也为 2，那就必须立刻把这个值 pop 出来。因为之后的
push 都会让栈顶元素变成不同于 2 的其他值，这样再 pop 出来
的数 popped 序列就不对应了。
算法
将 pushed 队列中的每个数都 push 到栈中，同时检查这个数是不
是 popped 序列中下一个要 pop 的值，如果是就把它 pop 出来。
最后，检查不是所有的该 pop 出来的值都是 pop 出来了。
*/
bool validateStackSequences(int* pushed, int pushedSize,
	int* popped, int poppedSize)
{
	if (pushed == NULL || popped == NULL) {
		return false;
	}

	struct astack *stack = astack_init(pushedSize);
	int j = 0;
	for (int i = 0; i < pushedSize; i++) {
		struct astack_load load;
		load.data = pushed[i];
		astack_push(stack, load);

		while(!astack_empty(stack) && j < pushedSize) {
			struct astack_load load = astack_top(stack);
			if (load.data == popped[j]) {
				astack_pop(stack);
				j++;
			} else {
				break;
			}
		}
	}

	return j == pushedSize;
}

/*
55. 跳跃游戏
难度中等761
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个位置。
示例 1:
输入: [2,3,1,1,4]
输出: true
解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置
1 跳 3 步到达最后一个位置。
示例 2:
输入: [3,2,1,0,4]
输出: false
解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最
大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。
*/
bool canJump(int* nums, int numsSize)
{
	int rightmost = 0;

	for (int i = 0; i < numsSize; ++i) {
		if (i <= rightmost) {
			rightmost = fmax(rightmost, i + nums[i]);
			if (rightmost >= numsSize - 1) {
				return true;
			}
		}
	}

	return false;
}

/*
45. 跳跃游戏 II
难度困难649
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。
示例:
输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
*/

/*
我们的目标是到达数组的最后一个位置，因此我们可以考虑最后一步跳跃前所在的位置，该位置通过跳跃能够到达最后一个位置。如果有多个位置通过跳跃都能够到达最后一个位置，那么我们应该如何进行选择呢？直观上来看，我们可以「贪心」地选择距离最后一个位置最远的那个位置，也就是对应下标最小的那个位置。因此，我们可以从左到右遍历数组，选择第一个满足要求的位置。找到最后一步跳跃前所在的位置之后，我们继续贪心地寻找倒数第二步跳跃前所在的位置，以此类推，直到找到数组的开始位置。作者：LeetCode-Solution链接：https://leetcode-cn.com/problems/jump-game-ii/solution/tiao-yue-you-xi-ii-by-leetcode-solution/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int jump(int* nums, int numsSize)
{
	int position = numsSize - 1;
	int steps = 0;
	while (position > 0) {
		for (int i = 0; i < position; i++) {
			if (i + nums[i] >= position) {
				position = i;
				steps++;
				break;
			}
		}
	}
	return steps;
}

