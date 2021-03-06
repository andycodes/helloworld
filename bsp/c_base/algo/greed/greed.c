
/*
Interval Scheduling 区间调度问题
贪心算法一般用来解决需要 “找到要做某事的最小数量”
或 “找到在某些情况下适合的最大物品数量” 的问题，
且提供的是无序的输入。
1) 排序(很多场景)
2) 迭代

*/

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

/*
406. 根据身高重建队列
难度中等424
假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。
注意：
总人数少于1100人。
示例
输入:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

输出:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int compare(const void *a,const void *b){
    const int* pa = *(const int **)a;
    const int* pb = *(const int **)b;
    return pa[0] == pb[0]?pa[1] - pb[1]:pb[0] - pa[0];
}

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes){
    int **res = NULL;
    res = (int **)malloc(sizeof(int *) * peopleSize);
    int i;
    int pos;
    //for(i = 0;i < peopleSize;i++){
        //res[i] = (int *)malloc(sizeof(int) * 2);
   // }

    qsort(people, peopleSize, sizeof(int *), compare);
    //for(i = 0;i < peopleSize;i++)
        //printf("%d\t%d\n",people[i][0],people[i][1]);
    for(i = 0;i < peopleSize;i++){
        pos = people[i][1];
        //printf("people i1 is %d\n",people[i][1]);
        memmove(&res[pos + 1], &res[pos], (i - pos) *sizeof(int *));
        res[pos] = (int *)malloc(sizeof(int) * 2);
        res[pos][0] = people[i][0];
        res[pos][1] = people[i][1];
    }

    *returnSize = peopleSize;
    *returnColumnSizes = peopleColSize;
    return res;
}

/*
135. 分发糖果
难度困难239
老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。
你需要按照以下要求，帮助老师给这些孩子分发糖果：
"	每个孩子至少分配到 1 个糖果。
"	相邻的孩子中，评分高的孩子必须获得更多的糖果。
那么这样下来，老师至少需要准备多少颗糖果呢？
示例 1:
输入: [1,0,2]
输出: 5
解释: 你可以分别给这三个孩子分发 2、1、2 颗糖果。

*/
int candy(int* ratings, int ratingsSize)
{
        int sum = 0;
        int left2right[ratingsSize];
        int right2left[ratingsSize];
	for (int i = 0; i < ratingsSize; i++) {
		left2right[i] = right2left[i] = 1;
	}

        for (int i = 1; i < ratingsSize; i++) {
            if (ratings[i] > ratings[i - 1]) {
                left2right[i] = left2right[i - 1] + 1;
            }
        }
        for (int i = ratingsSize - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                right2left[i] = right2left[i + 1] + 1;
            }
        }
        for (int i = 0; i < ratingsSize; i++) {
            sum += fmax(left2right[i], right2left[i]);
        }
        return sum;
}

int candy(int* ratings, int ratingsSize)
{
        int candies[ratingsSize];
	for (int i = 0; i < ratingsSize; i++) {
		candies[i] = 1;
	}

        for (int i = 1; i < ratingsSize; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        int sum = candies[ratingsSize - 1];
        for (int i = ratingsSize - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = fmax(candies[i], candies[i + 1] + 1);
            }
            sum += candies[i];
        }
        return sum;
}

/*
452. 用最少数量的箭引爆气球
难度中等162收藏分享切换为英文关注反馈
在二维空间中有许多球形的气球。对于每个气球，提供的输
入是水平方向上，气球直径的开始和结束坐标。由于它是水
平的，所以y坐标并不重要，因此只要知道开始和结束的x坐
标就足够了。开始坐标总是小于结束坐标。平面内最多存
在104个气球。
一支弓箭可以沿着x轴从不同点完全垂直地射出。在坐标x处射
出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，
xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。可以射出的
弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前
进。我们想找到使得所有气球全部被引爆，所需的弓箭的最
小数量。
Example:
输入:
[[10,16], [2,8], [1,6], [7,12]]
输出:
2
解释:
对于该样例，我们可以在x = 6（射爆[2,8],[1,6]两个气球）和 x = 11（
射爆另外两个气球）。
*/
int findMinArrowShots(int** points, int pointsSize, int* pointsColSize)
{
	if (pointsSize == 0)
		return 0;

	qsort(points, pointsSize, sizeof(points[0]), cmp_doublePoint);

	int arrows = 1;
	int curStart, curEnd, lastEnd = points[0][1];
	for (int i = 0; i < pointsSize; i++) {
		curStart = points[i][0];
		curEnd = points[i][1];
		if (lastEnd < curStart) {
			arrows++;
			lastEnd = curEnd;
		}
	}
	return arrows;
}


/*
56. 合并区间
难度中等545
给出一个区间的集合，请合并所有重叠的区间。
示例 1:
输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2:
输入: [[1,4],[4,5]]
输出: [[1,5]]
解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。

*/
int cmp_doublePoint(const void *a, const void *b)
{
	int **aa = (int **)a;
	int **bb = (int **)b;

	if (aa[0][0] == bb[0][0]) {
		return aa[0][1] - bb[0][1];
	} else {
		return aa[0][0] - bb[0][0];
	}
}
//[[1,3],[2,6],[8,10],[15,18]]
//[[1,4],[4,5]]
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
	int* returnSize, int** returnColumnSizes)
{
	if (intervals == NULL || intervalsSize <= 0 || intervalsColSize == NULL) {
		*returnSize = 0;
		return NULL;
	}

	qsort(intervals, intervalsSize, sizeof(intervals[0]), cmp_doublePoint);
	int **res = (int **)calloc(intervalsSize, sizeof(int *));
	*returnColumnSizes = (int *)calloc(intervalsSize, sizeof(int));
	for (int i = 0; i < intervalsSize; i++) {
		res[i] = (int *)calloc(2, sizeof(int));
		(*returnColumnSizes)[i] = 2;
	}

	res[0][0] = intervals[0][0];
	res[0][1] = intervals[0][1];
	*returnSize = 1;
	for (int i = 1; i < intervalsSize; i++) {
		if (intervals[i][0] > res[*returnSize - 1][1]) {
			res[*returnSize][0] = intervals[i][0];
			res[*returnSize][1] = intervals[i][1];
			(*returnSize)++;
		} else {
			res[*returnSize - 1][1] = fmax(res[*returnSize - 1][1] , intervals[i][1]);
		}
	}

	return res;
}

/*
376. 摆动序列
难度中等229收藏分享切换为英文关注反馈
如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。
例如， [1,7,4,9,2,5] 是一个摆动序列，因为差值 (6,-3,5,-7,3) 是正负交替出现的。相反, [1,4,7,2,5] 和 [1,7,4,5,5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。
给定一个整数序列，返回作为摆动序列的最长子序列的长度。 通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。
示例 1:
输入: [1,7,4,9,2,5]
输出: 6
解释: 整个序列均为摆动序列。
示例 2:
输入: [1,17,5,10,13,15,10,5,16,8]
输出: 7
解释: 这个序列包含几个长度为 7 摆动序列，其中一个可为[1,17,10,13,10,16,8]。
示例 3:
输入: [1,2,3,4,5,6,7,8,9]
输出: 2

*/
int calculate(int *nums, int numsSize, int index, bool isUp)
{
        int maxcount = 0;
        for (int i = index + 1; i < numsSize; i++) {
            if ((isUp && nums[i] > nums[index]) || (!isUp && nums[i] < nums[index]))
                maxcount = fmax(maxcount, 1 + calculate(nums, numsSize, i, !isUp));
        }
        return maxcount;
 }

int wiggleMaxLength(int* nums, int numsSize)
{
        if (numsSize < 2)
            return numsSize;
        return 1 + fmax(calculate(nums, numsSize, 0, true), calculate(nums, numsSize, 0, false));
}

int wiggleMaxLength(int* nums, int numsSize)
{
    int down = 1, up = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i - 1])
            up = down + 1;
        else if (nums[i] < nums[i - 1])
            down = up + 1;
    }
    return numsSize == 0 ? 0 : fmax(down, up);
}

/*
738. 单调递增的数字
难度中等65收藏分享切换为英文关注反馈
给定一个非负整数 N，找出小于或等于 N 的最大的整数，同时这个整数需要满足其各个位数上的数字是单调递增。
（当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。）
示例 1:
输入: N = 10
输出: 9
示例 2:
输入: N = 1234
输出: 1234

*/

//贪心算法，遍历数字每一位，当前位的数字比下一位的数字大，则将该位数字减小1，然后之后位的数字全部变为9
int monotoneIncreasingDigits(int N)
{
        char num[1024] = {0};
		sprintf(num, "%d", N);
        int t = strlen(num);
        for(int i=strlen(num)-1;i>=1;i--){
            if(num[i]<num[i-1]){
                t=i;
                num[i-1]--;
            }
        }
        while(t<strlen(num))
            num[t++]='9';

        return atoi(num);
}

//贪心算法，遍历数字每一位，当前位的数字比下一位的数字大，则将该位数字减小1，然后之后位的数字全部变为9
//贪心算法，遍历数字每一位，当前位的数字比下一位的数字大，则将该位数字减小1，然后之后位的数字全部变为9
int monotoneIncreasingDigits(int N)
{
        char s[1024] = {0};
	sprintf(s, "%d", N);
        int p=0;
        for(int i=strlen(s)-1;i>=1;i--)
        {
            if(s[i]<s[i-1])
            {
                p=i;
                s[i-1]--;
                while(p<strlen(s))
                {
                    s[p++]='9';
                }
            }
        }
        return atoi(s);
    }

//贪心算法，遍历数字每一位，当前位的数字比下一位的数字大，则将该位数字减小1，然后之后位的数字全部变为9
//贪心算法，遍历数字每一位，当前位的数字比下一位的数字大，则将该位数字减小1，然后之后位的数字全部变为9
int monotoneIncreasingDigits(int N)
{
        char s[1024] = {0};
	sprintf(s, "%d", N);
        int p=0;
        for(int i=strlen(s)-1;i>=1;i--)
        {
            if(s[i]<s[i-1])
            {
                p=i;
                s[i-1]--;
                while(p<strlen(s))
                {
                    s[p++]='9';
                }
            }
        }
        return atoi(s);
    }

/*
659. 分割数组为连续子序列
给你一个按升序排序的整数数组 num（可能包含重复数字），请你将它们分割成一个或多个子序列，其中每个子序列都由连续整数组成且长度至少为 3 。

如果可以完成上述分割，则返回 true ；否则，返回 false 。



示例 1：

输入: [1,2,3,3,4,5]
输出: True
解释:
你可以分割出这样两个连续子序列 :
1, 2, 3
3, 4, 5
*/
int nc[10000];
int tail[10002];
bool isPossible(int* nums, int numsSize){
    int i, pos;
    int base = 0;
    memset(nc, 0, sizeof(nc));
    memset(tail, 0, sizeof(tail));
    if (nums[0] < 0) {
        base = abs(nums[0]);
    }
    for (i = 0; i < numsSize; i++) {
        pos = base + nums[i];
        nc[pos]++;
    }

    for (i = 0; i < numsSize; i++) {
        pos = base + nums[i];
        if (nc[pos] == 0) {
            continue;
        } else if (pos > 0 && nc[pos] > 0 && tail[pos-1] > 0) {
            nc[pos]--;
            tail[pos-1]--;
            tail[pos]++;
        } else if (nc[pos] > 0 && nc[pos+1] > 0 && nc[pos+2] > 0) {
            nc[pos]--;
            nc[pos+1]--;
            nc[pos+2]--;
            tail[pos+2]++;
        } else {
            return false;
        }
    }
    return true;
}

/*
358. K 距离间隔重排字符串
给你一个非空的字符串 s 和一个整数 k，你要将这个字符串中的字母进行重新排列，使得重排后的字符串中相同字母的位置间隔距离至少为 k。

所有输入的字符串都由小写字母组成，如果找不到距离至少为 k 的重排结果，请返回一个空字符串 ""。

示例 1：

输入: s = "aabbcc", k = 3
输出: "abcabc"
解释: 相同的字母在新的字符串中间隔至少 3 个单位距离。
示例 2:

输入: s = "aaabc", k = 3
输出: ""
解释: 没有办法找到可能的重排结果。
*/
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

typedef struct letterCnt {
    int letterVal;
    int letterCnt;
    int prePos;
}LETTER_CNT;

char findNextChar(LETTER_CNT *letterCnt, int curPos, int k)
{
    char nextChar = 0;
    int i = 0;
    for (; i < 27; i++) {
        if (letterCnt[i].letterCnt == 0) {
            continue;
        }

        if (letterCnt[i].prePos == -1  ||  (curPos - letterCnt[i].prePos) >= k) {
            letterCnt[i].prePos = curPos;
            letterCnt[i].letterCnt -= 1;
            nextChar =  letterCnt[i].letterVal;
            break;
        }
    }

    return nextChar;
}
int compareLetterCnt(const void *elm1, const void *elm2) {
    return ((LETTER_CNT *)elm2)->letterCnt - ((LETTER_CNT *)elm1)->letterCnt;
}

char * rearrangeString(char * s, int k)
{
    LETTER_CNT letterCnt[27] = { 0 };
    int letterPrePos[27] = { 0 };
    int maxDupLetter = 0;

    if (s == NULL) {
        return "";
    }

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        letterCnt[s[i] - 'a'].letterVal = s[i];
        letterCnt[s[i] - 'a'].letterCnt += 1;
        letterCnt[s[i] - 'a'].prePos = -1;
        maxDupLetter = MAX(maxDupLetter, letterCnt[s[i] - 'a'].letterCnt);
    }

    if ((maxDupLetter - 1) * k + 1 > len) {
        return "";
    }

    qsort(letterCnt, 27, sizeof(LETTER_CNT),  compareLetterCnt);

    char *pNewStr = (char *)malloc(len + 1);
    memset(pNewStr, 0, len + 1);
    int i  = 0;
    for (i = 0; i < len; i++) {
        char c  =  findNextChar(letterCnt, i, k);
        qsort(letterCnt, 27, sizeof(LETTER_CNT),  compareLetterCnt); // 取完重新排序一下 保证优先取最多的字符
        if (c == 0) {
            break;
        }
        pNewStr[i] = c;
    }

    if (i != len) {
        free(pNewStr);
        return "";
    }

    return pNewStr;
}

/*
502. IPO
假设 力扣（LeetCode）即将开始其 IPO。为了以更高的价格将股票卖给风险投资公司，力扣 希望在 IPO 之前开展一些项目以增加其资本。 由于资源有限，它只能在 IPO 之前完成最多 k 个不同的项目。帮助 力扣 设计完成最多 k 个不同项目后得到最大总资本的方式。

给定若干个项目。对于每个项目 i，它都有一个纯利润 Pi，并且需要最小的资本 Ci 来启动相应的项目。最初，你有 W 资本。当你完成一个项目时，你将获得纯利润，且利润将被添加到你的总资本中。

总而言之，从给定项目中选择最多 k 个不同项目的列表，以最大化最终资本，并输出最终可获得的最多资本。

示例 1:

输入: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

输出: 4

解释:
由于你的初始资本为 0，你尽可以从 0 号项目开始。
在完成后，你将获得 1 的利润，你的总资本将变为 1。
此时你可以选择开始 1 号或 2 号项目。
由于你最多可以选择两个项目，所以你需要完成 2 号项目以获得最大的资本。
因此，输出最后最大化的资本，为 0 + 1 + 3 = 4。
*/
typedef struct {
	int p; // profit
	int c; // capital
} node_t;

typedef int (*cmp_fn)(const void *,const void *);

int cmpc(const void*a, const void*b)
{ // 对成本cost进行排序，从小到大
	node_t* n1 = (node_t*)a;
	node_t* n2 = (node_t*)b;
	return (n1->c - n2->c);
}

int cmpp(const void*a, const void*b)
{ // 对收益profit进行排序，从小到大，大顶堆
	node_t* n1 = (node_t*)a;
	node_t* n2 = (node_t*)b;
	return (n1->p - n2->p);
}

void swap(node_t *a, node_t *b)
{ // 交换两个元素
    node_t t = *a;
    *a = *b;
    *b = t;
}

bool HeadNodeDown(node_t *a, int n, cmp_fn cmp, int i)
{ // 节点元素i进行下沉
    if (a == NULL || n < 0 || i > n ) {
        return false;
    }
	int dad = i; // 非叶子节点，即父节点的编号
    int k = n / 2 - 1; // 非叶子节点的最大位置
	while (dad <= k) { // 父节点，仍然是非叶子节点
		int son = dad * 2 + 1; // 左子节点的编号
		if (son + 1 < n && cmp(&a[son], &a[son + 1]) < 0) {
		    son = son + 1;  // 右子节点更大，选右边
		}
		if (cmp(&a[son], &a[dad]) <= 0) { // 子节点都比较小
		    break; // 不用再下沉了
		}
		swap(&a[son], &a[dad]);
		dad = son;
	}
    return true;
}

bool HeadNodeUp(node_t *a, int n, cmp_fn cmp, int i)
{ // 节点元素i进行上浮
    if (a == NULL || n < 0 || i > n ) {
        return false;
    }
	int son = i; // 叶子节点，即子节点的编号
	while (son > 0) { // 子节点，仍然是正常节点
		int dad = (son - 1) / 2; // 父节点的编号
		if (cmp(&a[son], &a[dad]) <= 0) { // 子节点比较小
		    break; // 不用再上浮了
		}
		swap(&a[son], &a[dad]);
		son = dad;
	}
    return true;
}

bool HeadNodePush(node_t *a, int *n, cmp_fn cmp, node_t *t)
{ // 在堆中压入一个节点元素，从尾部添加
	if (a == NULL || n == NULL || *n < 0 || t == NULL) {
        return false;
    }
	a[*n] = *t;
    (*n)++;
    HeadNodeUp(a, *n, cmp, *n-1);
    return true;
}

bool HeadNodePop(node_t *a, int *n, cmp_fn cmp, node_t *t)
{ // 在堆中弹出一个节点元素，从顶部弹出
	if (a == NULL || n == NULL || *n < 0 || t == NULL) {
        return false;
    }
    swap(&a[0], &a[*n - 1]);
    *t = a[*n - 1];
    memset(&a[*n - 1], 0, sizeof(node_t));
    (*n)--;
    HeadNodeDown(a, *n, cmp, 0);
    return true;
}

bool HeadCreate(node_t *a, int n, cmp_fn cmp)
{ // 堆的非叶子节点的调整
    if (a == NULL || n < 0) {
        return false;
    }
    int k = n / 2 - 1; // 非叶子节点的最大位置
    for (int i = k; i >= 0; i--) { // 遍历所有非叶子节点
    	HeadNodeDown(a, n, cmp, i); // 逐个判断是否可以下沉
    }
    return true;
}

bool HeapSort(node_t *a, int n)
{ // 堆排序，大顶堆，从小到大
    if (a == NULL || n < 0) {
        return false;
    }
    for (int i = n; i > 0; i--) {
        HeadCreate(a, i, cmpp);
        swap(&a[0], &a[i - 1]);
    }
    return true;
}

int gd(int k, int w, node_t*a, int n)
{ // 贪心greedy算法，每次都选择收益最大的那个
    if (k == 0 || w < 0 || a == NULL || n <= 0) {
        return 0;
    }
    node_t c[n];
    memset(c, 0, sizeof(c));
	qsort(a, n, sizeof(node_t), cmpc);
	for (int ai = 0, ci = 0; k > 0; k--) {
		while (ai < n && a[ai].c <= w) { // 都可选
			HeadNodePush(c, &ci, cmpp, &a[ai]);
			ai++;
		}
		if (ci > 0) { // 还有元素可选
			node_t t; // 临时变量
			HeadNodePop(c, &ci, cmpp, &t);
			w += t.p;
		}
	}
    return w;
}

int findMaximizedCapital(int k, int w, int*p, int pn, int*c, int cn)
{
    if (k == 0 || w < 0 || p == NULL || pn <= 0 || c == NULL || cn <= 0) {
        return 0;
    }
    node_t a[pn];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < pn; i++) {
    	a[i].p = p[i];
    	a[i].c = c[i];
	}
    return gd(k, w, a, pn);
}
