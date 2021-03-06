#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
特性1:最优子结构;每个阶段的状态或值都是通过前面阶段的状态或值推导出来的,满足.
特性2:无后效性;每个阶段的状态值一旦确定之后,是不受后面阶段状态值所影响的,满足.
特性3:重复子问题;从递归解法中就能看出来有重复子问题的计算,满足.

*/

/*
定理:
二维矩阵前缀和:
sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
*/

/************前缀处理*******************/


/*最大子序和*/
/*
动态规划的是首先对数组进行遍历，
当前最大连续子序列和为 sum，结果为 ans
如果 sum > 0，则说明 sum 对结果有增益效果，
则 sum 保留并加上当前遍历数字
如果 sum <= 0，则说明 sum 对结果无增益效果，
需要舍弃，则 sum 直接更新为当前遍历数字
每次比较 sum 和 ans的大小，将最大值置为ans，
遍历结束返回结果
时间复杂度：O(n)O(n)
*/

int maxSubArray(int* nums, int numsSize)
{
    int ans = nums[0];
    int sum = 0;
    int i;

    for (i = 0; i < numsSize; i++ ) {
        if (sum > 0)
            sum += nums[i];
        else
            sum = nums[i];

	ans = fmax(ans, sum);
    }

    return ans;
}


/*
动态规划，用dp[i]表示以i结尾的最大子序列和。
初始值 dp[0] = nums[0]，然后从第二个数开始遍历

if 当前数加上前一个最大序列和大于当前数，
则将当前数加到序列和中，nums[i] + dp[i-1] > nums[i]，
	则 dp[i] = nums[i] + dp[i-1];
else 以当前数结尾的最大序列和即为当前数本身
	dp[i] = nums[i]
然后判断以当前数结尾的最大序列和是
否大于最大序列和
*/
int maxSubArray(int* nums, int numsSize)
{
    int size = numsSize;
    int max = nums[0];
    int dp[size];
    dp[0] = nums[0];

    for (int i = 1; i < size; ++i) {
        if (dp[i-1] >= 0) {
            dp[i] = nums[i] + dp[i-1];
        } else {
            dp[i] = nums[i];
        }

	max = fmax(max, dp[i]);
    }
    return max;
}


/*
优化空间
因为以当前数结尾的最大序列和仅与
前一个序列和相关，所以可以用一个变量保存
*/
int maxSubArray(int* nums, int numsSize)
{
	int size = numsSize;
	int max = nums[0];
	int pre = nums[0];

	for (int i = 1; i < size; ++i) {
		if (pre >= 0) {
			pre = nums[i] + pre;
		} else {
			pre = nums[i];
		}

		max = fmax(max, pre);
	}
	return max;
}

int maxSubArray(int* nums, int numsSize)
{
	int size = numsSize;
	int max = nums[0];
	int pre = nums[0];

	for (int i = 1; i < size; ++i) {
		pre = fmax(nums[i] + pre, nums[i]);
		max = fmax(max, pre);
	}
	return max;
}


/*
152. 乘积最大子序列
给定一个整数数组 nums ，找出一个序列中乘积最大
的连续子序列（该序列至少包含一个数）。

示例 1:

输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
示例 2:

输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
*/
int maxProduct(int* nums, int numsSize){
	const int N=numsSize;

    int d[numsSize];
    int e[numsSize];

    d[0]=nums[0];
    e[0]=nums[0];

    int ans = nums[0];
    for(int i=1;i<N;++i){
        d[i]=fmax(nums[i],fmax(nums[i]*d[i-1],nums[i]*e[i-1]));
        e[i]=fmin(nums[i],fmin(nums[i]*d[i-1],nums[i]*e[i-1]));
        ans = fmax(ans,fmax(d[i],e[i]));
    }
    return ans;
}


/*
1292. 元素和小于等于阈值的正方形的最大边长
给你一个大小为 m x n 的矩阵 mat 和一个整数阈值 threshold。

请你返回元素总和小于或等于阈值的正方形区域的最大边长；
如果没有这样的正方形区域，则返回 0 。


示例 1：

输入：mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
输出：2
解释：总和小于 4 的正方形的最大边长为 2，如图所示。

*/
int maxSideLength(int** mat, int matSize,
	int* matColSize, int threshold) {
	int colSize = matColSize[0];
	int dp[matSize + 1][colSize + 1];

	for (int i = 1; i <= matSize; i++) {
		for (int j = 1; j <= colSize; j++) {
			dp[i][j] = mat[i - 1][j - 1] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
		}
	}

	int ans = 0;
	for (int k = 1; k <= fmin(matSize, colSize); k++) {
		for (int i = 1; i <= matSize; i++) {
			for (int j = 1; j <= colSize; j++) {
				if (i - k < 0 || j - k < 0) {
					continue;
				}
				int tmp = dp[i][j] - dp[i - k][j] - dp[i][j - k] + dp[i - k][j - k];
				if (tmp <= threshold) {
					ans = (int)fmax(ans, k);
				}
			}
		}
	}

    	return ans;
}

/*
363. 矩形区域不超过 K 的最大数值和
给定一个非空二维矩阵 matrix 和一个整数 k，找到这个矩阵内部不大于 k 的最大矩形和。

示例:

输入: matrix = [[1,0,1],[0,-2,3]], k = 2
输出: 2
解释: 矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）。
说明：

矩阵内的矩形区域面积必须大于 0。
如果行数远大于列数，你将如何解答呢？

*/
int maxSumSubmatrix(int** matrix, int matrixSize, int* matrixColSize, int k){

	int m = matrixSize;
	int n = matrixColSize[0];
	int dp[m + 1][n + 1];
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + matrix[i-1][j-1];
		}
	}

	int res = INT_MIN;
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=n;j++) {
		    for(int k=1;k<=i;k++) {
		        for(int t=1;t<=j;t++) {
		            int tmp=dp[i][j]-dp[k-1][j]-dp[i][t-1]+dp[k-1][t-1];
		            if(tmp<=k) {
		                res= fmax(res,tmp);
		            }
		        }
		    }
		}
	}

	return res;
}



/*
编写一个程序，找出第 n 个丑数。

丑数就是只包含质因数 2, 3, 5 的正整数。

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:

1 是丑数。
n 不超过1690。

*/
/*
动态规划(三指针)
所有的丑数都可以拆成之前的两个已知丑数相乘，那么就要找出这两个数来
暴力的找法就是：每次尝试之前所有的相乘组合，取出值最小的那个，时间复杂度爆炸
优化思路：

并不用每次都尝试所有组合，我们需要过滤掉不可能的组合
已知2，3，5与已有丑数相乘时，数值增长速度是不一样的
我们每次从三组新丑数中，挑选大于已知末尾丑数的最小值，来作为新的丑数
乘3或者乘5的新丑数，如果某次未被选中放入数轴，那么肯定有某一刻会被放进去
所以使用三个游标来确定已被放入数轴的新丑数最小值，每次仅需要对比这三个游标与2，3，5乘积即可


第一步，先提出自底部向上的方案---无论题目怎么变换，动态规划都是要老老实实一步步遍历数据
    在遍历数据方面，是正常的动态规划，从头遍历到尾
    这道题的核心难点在于当前的值跟前几步，而不是前一步有关。
    最简单的思路，寻找第k个，之前的k-1个数分别跟2,3,5相乘，然后找到比k-1大，且最小的数。
    如何优化？减少存储和计算次数？

*/
int nthUglyNumber(int n){
	int dp[n];
	memset(dp,0,sizeof(dp));

	int i2 = 0;
	int i3 = 0;
	int i5 = 0;
	dp[0] = 1;

	for (int i = 1; i < n; i++) {
		int a = dp[i2] * 2;
		int b = dp[i3] * 3;
		int c = dp[i5] * 5;
		int min = MIN3(a , b, c);
		if (min == a)
			i2++;
		if (min == b)// 不用else 比如6是2和3的倍数，i2 i3同时移动避免重复打入
			i3++;
		if (min == c)
			i5++;

		dp[i] = min;
	}

	return dp[n - 1];
}


/*
1220. 统计元音字母序列的数目
给你一个整数 n，请你帮忙统计一下我们可以按下述规则形成多少个长度为 n 的字符串：

字符串中的每个字符都应当是小写元音字母（'a', 'e', 'i', 'o', 'u'）
每个元音 'a' 后面都只能跟着 'e'
每个元音 'e' 后面只能跟着 'a' 或者是 'i'
每个元音 'i' 后面 不能 再跟着另一个 'i'
每个元音 'o' 后面只能跟着 'i' 或者是 'u'
每个元音 'u' 后面只能跟着 'a'
由于答案可能会很大，所以请你返回 模 10^9 + 7 之后的结果。



示例 1：

输入：n = 1
输出：5
解释：所有可能的字符串分别是："a", "e", "i" , "o" 和 "u"。
示例 2：

输入：n = 2
输出：10
解释：所有可能的字符串分别是："ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" 和 "ua"。


我们发现每一个序列往后加一个字母， 只和前一个字符有关。 利用加法原理， 可以直接推出。

我们用f(i, char)f(i,char)来表示前ii个字符以charchar结尾和合法字符串数量。

则由规则可以得到。
f(i, 'a') = f(i - 1, 'e') + f(i - 1, 'i') + f(i -1, 'u')
其余类推。

*/

int countVowelPermutation(int n){
	int a,e,i,o,u;

	if (n == 1)
		return 5;

	a = e = i = o = u = 1;

	const int mod = 1e9 + 7;

	for (int j = 2; j <= n; j++) {
		int aa, ee, ii, oo, uu;

		aa = ((e + i) % mod + u) % mod;
		ee = (a + i) % mod;
		ii = (e + o)  % mod;
		oo = i;
		uu = (i + o) % mod;

		a = aa, e = ee, i = ii, o = oo, u = uu;
		 //printf("%d %d %d %d %d\n",a,e,i,o,u);
	}
	return ((long long) a + e + i + o + u) % mod;
}

/*
面试题47. 礼物的最大价值
难度中等9
在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

示例 1:
输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物

*/


int maxValueParmCheck(int** grid, int gridSize, int* gridColSize)
{
	if (grid == NULL || gridColSize <= 0 || gridColSize == NULL)
		return -1;
	return 0;
}

/*
常规解法代码

class Solution:
    def maxValue(self, grid: List[List[int]]) -> int:
        m,n=len(grid),len(grid[0])
        if not m or not n: return 0
        for i in range(m):
            for j in range(n):
                grid[i][j] += max(i>0 and grid[i - 1][j], j>0 and grid[i][j - 1])
        return grid[-1][-1]


状态转移
dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
初始值
dp[0][0] = grid[0][0];
dp[i][0] = grid[i][0] + dp[i - 1][0];
dp[0][j] = dp[0][j - 1] + grid[0][j];
*/
int maxValue(int** grid, int gridSize, int* gridColSize){
	if (maxValueParmCheck(grid, gridSize, gridColSize) == -1)
		return 0;

	int m = gridSize;
	int n = gridColSize[0];
	int dp[m][n];
	memset(dp, 0, sizeof(dp));

	dp[0][0] = grid[0][0];
	for (int i = 1; i < m; i++) {//first col
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}
	for (int j = 1; j < n; j++) {//first row
		dp[0][j] = dp[0][j - 1] + grid[0][j];
	}
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1])  + grid[i][j];
		}
	}

	return dp[gridSize - 1][gridColSize[gridSize - 1] - 1];
}

/*

Best Answer
空间优化，只用到了dp[i][j - 1]和dp[i - 1][j]，可以压缩成一维数组

dp[i][j - 1]就是dp[j - 1]
dp[i - 1][j]是没更新前的dp[j]
注意处理边界‘

(j > 0? dp[j - 1] : 0)，走不通的地方填0就可以了，
这样就能用dp[j]来计算
*/
int maxValue(int** grid, int gridSize, int* gridColSize){
	if (maxValueParmCheck(grid, gridSize, gridColSize) == -1)
		return 0;

	int row = gridSize;
	int col = gridColSize[0];
	//int dp[row][col];
    	int dp[col];
	memset(dp, 0, sizeof(dp));

        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                dp[j] = fmax(dp[j], (j > 0? dp[j - 1] : 0)) + grid[i][j];
            }
        }
        return dp[col - 1];
}

/*
62. 不同路径
难度中等439收藏分享切换为英文关注反馈
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标
记为"Start" ）。机器人每次只能向下或者向右移动一步。
机器人试图达到网格的右下角（在下图中标记为"Finish"）。
问总共有多少条不同的路径？

例如，上图是一个7 x 3 的网格。有多少可能的路径？
说明：m 和 n 的值均不超过 100。
示例 1:
输入: m = 3, n = 2
输出: 3
解释:
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向右 -> 向下
2. 向右 -> 向下 -> 向右
3. 向下 -> 向右 -> 向右

*/

/*
思路：如果大家都学过递归,就知道递归有重复计算的问题,
我们上面写的递归在遇到m和n比较大的时候,
同样会超过限制时间。那我们可以加一个备忘录,把已经计算
出来的结果保存起来,
下次需要计算同样的递归时,直接从备忘录中取出使用
*/
int recursive(int i,int j)
{
	if(i == 0 || j == 0)
		return 1;

	return recursive(i-1, j) + recursive(i, j - 1);
}

int uniquePaths(int m, int n)
{
	return recursive(m-1, n-1);
}


int dp[100][100];
int recursive(int i, int j)
{
	if(i == 0 || j == 0)
		return 1;

	if(dp[i][j] != 0)
		return dp[i][j];

	dp[i][j] = recursive(i - 1, j) + recursive(i, j - 1);
	return dp[i][j];
}

int uniquePaths(int m, int n)
{
	return recursive(m-1, n-1);
}


/*
dp[i][j] = dp[i - 1][j]+ dp[i][j - 1] ;
*/

int uniquePaths(int m, int n){
	int dp[m][n];
	memset(dp, 0, sizeof(dp));

	dp[0][0] = 1;
	for (int i = 1; i < m; i++) {//first col
		dp[i][0] = 1;
	}

	for (int j = 1; j < n; j++) {//first row
		dp[0][j] = 1;
	}
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = dp[i - 1][j]+ dp[i][j - 1] ;
		}
	}

	return dp[m- 1][n - 1];
}

/*
	外层循环走一次(内层循环走一圈)的时候，
	表示第一行第i列的总可能性
	外层循环走两次(内层循环走两圈)的时候，
	表示第二行第i列的总可能性

*/
int uniquePaths(int m, int n)
{
	int dp[n];

	for(int i = 0; i < n; i++) {
		dp[i] = 1;
	}

	for(int i = 1; i < m; i++) {
		for(int j = 1; j < n; j++) {
			dp[j] = dp[j] + dp[j - 1];
		}
	}

	return dp[n - 1];
}

/*排列组合*/
int uniquePaths(int m, int n)
{
	int N = n + m - 2;
	int k = m - 1;
	long res = 1;

	for (int i = 1; i <= k; i++)
		res = res * (N - k + i) / i;
	return (int) res;
}

/*
63. 不同路径 II
难度中等234
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为"Start" ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格
的右下角（在下图中标记为"Finish"）。
现在考虑网格中有障碍物。那么从左上角到右下角将会有
多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。
说明：m 和 n 的值均不超过 100。
示例 1:
输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: 2
解释:
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右

*/
int uniquePathsWithObstacles(
int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize)
{
	int m = obstacleGridSize;
	int n = obstacleGridColSize[0];
	int dp[n];
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (obstacleGrid[i][j] == 1) {
				dp[j] = 0;
			} else if (j > 0) {
				dp[j] += dp[j - 1];
			}
		}
	}

	return dp[n -1];
}

/*
bfs  279
*/
int numSquares(int n)
{
	int dp[n + 1];
	dp[0] = 0;

	for (int i = 1; i <= n; i++) {
		dp[i] = i;
		for (int j = 1; j * j <= i; j++) {
			dp[i] = fmin(dp[i], dp[i - j * j] + 1);
		}
	}

	return dp[n];
}

/*
91. 解码方法
难度中等363
一条包含字母 A-Z 的消息通过以下方式进行了编码：
'A' -> 1
'B' -> 2
...
'Z' -> 26
给定一个只包含数字的非空字符串，请计算解码方法的总数。
示例 1:
输入: "12"
输出: 2
解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。

*/
/*
首先要根据当前的字符是否为 0 进行判断
s 为字符串 s， f(i) 代表 到 s[i] 一共有多少种解码方式

if s[i] == '0'
if s[i-1] == '1' || s[i-1] =='2' --> f(i) == f(i-2)
也就是说最后两位只能合并解码为 10 或者 20，
例如 1212120 那么此时解的数量与 12121 相同
（只是解中增加了一个 20 的对应字母， 解总数量未增加）
else --> return 0
字符串非法， 也就是 0 只能出现在 1 或者 2 的后面，
其它情况都是无解的如： 1212130， 30 无法对应任何字符，
直接 return 0
if s[i] != '0'
if s[i-1] == '1' || (s[i-1] == '2' && s[i] >= '1' && s[i] <= '6') --> f(i) == f(i - 1) + f(i - 2)
也就是最后两位在 10~26 之间如 1212121， 可以翻译成 12121 + 21，
或者 121212 + 1
else --> f(i) == f(i - 1)
也就是最后两位不在 10~26 之间如 1212132 那只能翻译成 121213 + 2

此题和爬楼梯是同一个类型的问题，难点在于其添加了许多限制条件，只要避开限制条件就可以完美解题了

每次递进，可以选取一个数也可以选取两个数：

s[i] != '0'
如果 s[i-1]s[i] <= 26, 则 dp[i] = dp[i-1] + dp[i-2]
如果 s[i-1]s[i] > 26, 则 dp[i] = dp[i-1], 这是因为 s[i-1]s[i] 组成的两位数无法翻译
s[i] == '0'
如果 s[i-1]s[i] <= 26, 则 dp[i] = dp[i-2], 这是因为 s[i] 无法翻译
还有一些情景直接使得整个序列无法被翻译：
相邻的两个 '0'
以 '0' 结尾的大于 26 的数字
去除这些限制条件，此题就是爬楼梯的问题了，一次可以爬一步，也可以爬两步，问有多少中方式到达终点。

*/
int numDecodings(char * s)
{
	if (s[0] == '0')
		return 0;
	int slen = strlen(s);
	int dp[slen + 1];
	for (int i = 0; i < slen + 1; i++) {
		dp[i] = 1;
	}

	for (int i = 1; i < slen; i++) {
		if (s[i] == '0') {
			if (s[i - 1] == '1' || s[i - 1] == '2') {
				dp[i + 1] = dp[i - 1];
			} else
				return 0;
		} else {
			 if (s[i-1] == '1' || (s[i-1] == '2' && s[i] >= '1' && s[i] <= '6')) {
				dp[i + 1] = dp[i - 1] + dp[i];
			 } else {
				dp[i + 1] = dp[i];
			 }
		}
	}

	return dp[slen];
}

/*
213. 打家劫舍 II
难度中等255
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
示例 1:
输入: [2,3,2]
输出: 3
解释: 你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
示例 2:
输入: [1,2,3,1]
输出: 4
解释: 你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。

*/
#define MAX(a,b) ((a)>(b)?(a):(b))
int rob(int* nums, int numsSize){
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];
    //分两种情况dp，a为偷第1间，b为不偷第1间
    int i, a[numsSize], b[numsSize];
    a[0] = nums[0];
    a[1] = nums[0];
    b[0] = 0;
    b[1] = nums[1];
    for(i = 2; i < numsSize; i++) {
        a[i] = MAX(a[i-1], a[i-2] + nums[i]);
        b[i] = MAX(b[i-1], b[i-2] + nums[i]);
    }
    return MAX(a[numsSize-2], b[numsSize-1]);
}
/*
740. 删除与获得点数
难度中等147
给定一个整数数组 nums ，你可以对它进行一些操作。
每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除每个等于 nums[i] - 1 或 nums[i] + 1 的元素。
开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
示例 1:
输入: nums = [3, 4, 2]
输出: 6
解释:
删除 4 来获得 4 个点数，因此 3 也被删除。
之后，删除 2 来获得 2 个点数。总共获得 6 个点数。
示例 2:
输入: nums = [2, 2, 3, 3, 3, 4]
输出: 9
解释:
删除 3 来获得 3 个点数，接着要删除两个 2 和 4 。
之后，再次删除 3 获得 3 个点数，再次删除 3 获得 3 个点数。
总共获得 9 个点数。

*/
/*
想不到打家劫舍的同志，先读懂题目，先读懂题目，先读懂题目！！！！！ 是删除所有的nums[i] - 1和nums[i]+1。

第一、是删除所有，是删除所有，是删除所有！

第二、是nums[i] -1和nums[i]+1两个都删除，是nums[i] -1和nums[i]+1两个都删除，是nums[i] -1和nums[i]+1两个都删除。 重要的事情我说了9遍。。。。

这里小偷偷的钱不再是nums[i]，而是所有的nums[i]， 也就是nums[i]乘以nums[i]出现的次数。 如果你选择偷nums[i]，那么nums数组中所有的nums[i]你都要选择偷，为什么是所有的nums[i]，因为所有nums[i]+-1的数都被你给干掉了，不允许再选择nums[i]+-1这样的家庭去偷了，所以其他的nums[i]不存在不去偷。所以一旦你偷了nums[i]家的财产，就要偷所有的nums[i]，也就是nums[i]乘以count(nums[i])这么多的钱小偷全部要偷去！！！

所以这里的转移方程相比于打家劫舍里的转移方程，只是把打家劫舍里的正在偷的这个家庭的财产nums[i] 改为 偷财产和这个家庭相等的所有家庭的所有财产！！！此贼够大胆，够贪心，够勇敢！

相比于打家劫舍，这里的nums[i]是打家劫舍里面数组的索引，这里的nums[i]乘次nums[i]出现的次数，也就是所有的nums[i]总和 等同于打家劫舍里数组的值

转移方程为 dp[i] =Math.max(dp[i-1], dp[i-2] + nums[i] * count(nums[i]) ) 这里面i的最大值就是nums数组的最大值，因为nums[i]相当于索引

所以这里相比于打家劫舍里的小偷，这里的小偷已经不再是小偷了，而是江洋大盗了！！！！

*/
int deleteAndEarn(int* nums, int numsSize){
        int count[10001];
	memset(count, 0, sizeof(count));
        int maxNum = 0;
        for (int i = 0; i < numsSize; i++) {
            maxNum = fmax(nums[i], maxNum);
            ++count[nums[i]];
        }

        int dp[10001];
	memset(dp, 0, sizeof(dp));
        dp[1] = count[1];

        for (int i=2; i<=maxNum; ++i) {
            dp[i] = fmax(dp[i-1], dp[i-2]+count[i]*i);
        }

        return dp[maxNum];
}

/*
983. 最低票价
难度中等213
在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行。在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出。每一项是一个从 1 到 365 的整数。
火车票有三种不同的销售方式：
"	一张为期一天的通行证售价为 costs[0] 美元；
"	一张为期七天的通行证售价为 costs[1] 美元；
"	一张为期三十天的通行证售价为 costs[2] 美元。
通行证允许数天无限制的旅行。 例如，如果我们在第 2 天获得一张为期 7 天的通行证，那么我们可以连着旅行 7 天：第 2 天、第 3 天、第 4 天、第 5 天、第 6 天、第 7 天和第 8 天。
返回你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费。

示例 1：
输入：days = [1,4,6,7,8,20], costs = [2,7,15]
输出：11
解释：
例如，这里有一种购买通行证的方法，可以让你完成你的旅行计划：
在第 1 天，你花了 costs[0] = $2 买了一张为期 1 天的通行证，它将在第 1 天生效。
在第 3 天，你花了 costs[1] = $7 买了一张为期 7 天的通行证，它将在第 3, 4, ..., 9 天生效。
在第 20 天，你花了 costs[0] = $2 买了一张为期 1 天的通行证，它将在第 20 天生效。
你总共花了 $11，并完成了你计划的每一天旅行。

*/
/*
在第i天的时候，如果有出行计划，需要比较的三种方案为：

dp[i-1]+cost[0];
dp[i-7]+cost[1];
dp[i-30]+cost[2];
当中括号内数值为负的时候dp取值为0.
如果没有出行计划，则直接由dp[i]=dp[i-1];

*/

int mincostTickets(int* days, int daysSize, int* costs, int costsSize)
{
	int last = days[daysSize - 1];

	int dp[last + 1];
	memset(dp, 0, sizeof(dp));
	int idx = 0;

	for (int i = 1; i <= last; i++) {
		if (i == days[idx]) {
			int cost = INT_MAX;
			int oneDayAgo = i -1;
			int sevenDaysAgo = i - 7 > 0 ? i - 7 : 0;
			int thirtyDaysAgo = i - 30 > 0 ? i - 30 : 0;

			cost = fmin(dp[oneDayAgo] + costs[0], cost);
			cost = fmin(dp[sevenDaysAgo] + costs[1], cost);
			cost = fmin(dp[thirtyDaysAgo] + costs[2], cost);

			dp[i] = cost;
			idx++;
		} else {
			dp[i] = dp[i - 1];
		}
	}

	return dp[last];
}

/*
子串一定是连续的
子序列是原对象删除部分成员不改变顺序留下来的部分

 "pwwkew"
 子串"pww"
 子序列"pkw"
*/


/*
LCS的模板
int longestCommonSubsequence(string text1, string text2)
{
    int LCS[text1.size() + 1][text2.size() + 1];
    memset(LCS,0, sizeof(LCS));

    for (int i = 1; i <= text1.size(); ++i)
        for (int j = 1; j <= text2.size(); ++j)
        {
            if(text1[i - 1] == text2[j - 1])
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            else
                LCS[i][j] = max(LCS[i - 1][j],LCS[i][j - 1]);
        }
    return LCS[text1.size()][text2.size()];
}
dp[i][j]表示以str1的第i项为结尾，str2的第j项为结尾
*/
int longestCommonSubsequence(char * text1, char * text2)
{
    if (text1 == NULL)
        return text2;

    if (text2 == NULL)
        return text1;

	int len1 = strlen(text1);
	int len2 = strlen(text2);

	int dp[len1 + 1][len2 + 1];
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if(text1[i - 1] == text2[j - 1]) {
				dp[i][j] = dp[i -1][j -1] + 1;
			} else {
				dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return dp[len1][len2];
}

/*
583. 两个字符串的删除操作
难度中等96
给定两个单词 word1 和 word2，
找到使得 word1 和 word2 相同所需的最小步数，
每步可以删除任意一个字符串中的一个字符。

示例：
输入: "sea", "eat"
输出: 2
解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"

*/
int minDistance(char * word1, char * word2)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);

	int dp[len1 + 1][len2 + 1];
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (word1[i -1] == word2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return len1 + len2 - 2 * dp[len1][len2];
}


/*
718. 最长重复子数组
难度中等159
给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。
示例 1:
输入:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
输出: 3
解释:
长度最长的公共子数组是 [3, 2, 1]。
*/
int findLength(int* A, int ASize, int* B, int BSize)
{
	if (A == NULL || ASize <= 0)
		return 0;

	if (B == NULL || BSize <= 0)
		return 0;

	int dp[ASize + 1][BSize + 1];
	memset(dp, 0, sizeof(dp));

	int ret = 0;

	for (int i = 1; i <= ASize; i++) {
		for (int j = 1; j <= BSize; j++) {
			if (A[i - 1] == B[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
				ret = fmax(ret, dp[i][j]);
			}
		}
	}

	return ret;
}

/*
sliding_windows
5. 最长回文子串
*/
char * longestPalindrome(char * s)
{
	if (s == NULL || strlen(s) < 1)
	return "";

	int length = strlen(s);
	bool dp[length][length];
	int maxlen = 0;
	char *ret = "";

	for (int len = 1; len <= length; len++) {
		for (int  left = 0; left < length; left++) {
			int right = left + len - 1;
			if (right >= length)
				break;

			dp[left][right] = (len == 1 || len == 2 || dp[left + 1][right - 1]) && s[left] == s[right];
			if (dp[left][right] && len > maxlen) {
				maxlen = len;
				ret = strdup(s + left);
				ret[len] = '\0';
			}
		}
	}

	return ret;
}

/*
712. 两个字符串的最小ASCII删除和
难度中等93
给定两个字符串s1, s2，找到使两个字符串相等所需删除
字符的ASCII值的最小和。
示例 1:
输入: s1 = "sea", s2 = "eat"
输出: 231
解释: 在 "sea" 中删除 "s" 并将 "s" 的值(115)加入总和。
在 "eat" 中删除 "t" 并将 116 加入总和。
结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。

*/

/*
题意是寻找一个共同子序列，
将字符串s1和s2删除为该子序列时所删除
的ASCII综合最小。等价于求一个字符串s1
和s2的ASCII码总和最大的共同子序列。
因为s1和s2的总和固定，当共同子序列的
总和最大时，删除成为该子序列的代价必然
最小。
*/
int minimumDeleteSum(char * s1, char * s2){
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    int dp[len1 + 1][len2 + 1];
    memset(dp,0, sizeof(dp));

    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= len2; ++j)
        {
            if(s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + s1[i - 1];
            else
                dp[i][j] = fmax(dp[i - 1][j],dp[i][j - 1]);
        }

    int sum = 0;
    for (int i = 0; i < len1; ++i)
        sum += s1[i];
    for (int i = 0; i < len2; ++i)
        sum += s2[i];
    return sum - 2 * dp[len1][len2];

}

/*
1483. 树节点的第 K 个祖先
难度困难35
给你一棵树，树上有 n 个节点，按从 0 到 n-1 编号。树以父节点数组的形式给出，其中 parent[i] 是节点 i 的父节点。树的根节点是编号为 0 的节点。
请你设计并实现 getKthAncestor(int node, int k) 函数，函数返回节点 node 的第 k 个祖先节点。如果不存在这样的祖先节点，返回 -1 。
树节点的第 k 个祖先节点是从该节点到根节点路径上的第 k 个节点。

*/
typedef struct {

} TreeAncestor;

    int dp[50010][20];//dp[i][j]表示 对于i节点来说,它的第2^j个祖先是某个节点
                                      //dp[i][j] = dp[dp[i][j - 1]][j - 1] 相当于 我要到第2 ^ j 个祖先，我先到2 ^ (j - 1)个祖先
                                      //再到祖先的2 ^ (j - 1)个祖先，举个例子，我要到dp[i][3] 先跳到dp[i][2] 再在dp[i][2]的基础上再
                                      //跳 2 ^ 2 ，一共跳了8步,和 2 ^ 3 次方一样


TreeAncestor* treeAncestorCreate(int n, int* parent, int parentSize) {
        for(int i = 0 ;i < n ;i++){
            for(int j = 0 ;j < 20 ;j++){
                dp[i][j] = -1;
            }
        }

        for(int i = 0 ;i < parentSize ;i++){
            dp[i][0] = parent[i];
        }
        for(int i = 0 ; i < n ;i++){
            for(int j = 1 ;j < 20 ;j++){
                if(dp[i][j - 1] != -1)
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }

	return NULL;
}

int treeAncestorGetKthAncestor(TreeAncestor* obj, int node, int k) {
        int j = 0;
        while(k > 0){
            if(k % 2 != 0){
                node = dp[node][j];
            }
            if(node == -1) return node;
            j++;
            k = k >> 1;
        }
        return node;
}

void treeAncestorFree(TreeAncestor* obj) {

}

/*
1186. 删除一次得到子数组最大和
难度中等46
给你一个整数数组，返回它的某个 非空 子数组（连续元素）在执行一次可选的删除操作后，所能得到的最大元素总和。
换句话说，你可以从原数组中选出一个子数组，并可以决定要不要从中删除一个元素（只能删一次哦），（删除后）子数组中至少应当有一个元素，然后该子数组（剩下）的元素总和是所有子数组之中最大的。
注意，删除一个元素后，子数组 不能为空。
请看示例：
示例 1：
输入：arr = [1,-2,0,3]
输出：4
解释：我们可以选出 [1, -2, 0, 3]，然后删掉 -2，这样得到 [1, 0, 3]，和最大。

*/
int maximumSum(int* arr, int arrSize)
{
        int N = arrSize;

        // 边界条件，直接判断返回
        if (N == 1) {
            return arr[0];
        }

        int dp1[N]; // dp1[i]代表以arr[i]为结尾的最大连续子数组和
        int dp2[N]; // dp2[i]代表以arr[i]为结尾的并且删除了一个元素（可能是arr[i]自己）后最大的连续子数组和

        dp1[0] = arr[0];
        for (int i = 1; i < N; i++) {
            dp1[i] = fmax(arr[i], dp1[i - 1] + arr[i]);
        }

        #if 0
        for (int i = 0; i < N; i++) {
            cout << "dp1[" << i << "] = " << dp1[i] << endl;
        }
        #endif


        dp2[0] = arr[0];
        dp2[1] = fmax(arr[0], arr[1]);  // 因为删除元素后不能为空，所以以arr[1]为结尾的只有一种情况即arr[0] arr[1]，要么删除arr[0]，要么删除arr[1]

        for (int i = 2; i < N; i++) {
            dp2[i] = fmax(dp1[i - 1], dp2[i - 1] + arr[i]);
        }

        #if 0
        cout << "========================" << endl;
        for (int i = 0; i < N; i++) {
            cout << "dp2[" << i << "] = " << dp2[i] << endl;
        }
        #endif


        int retCnt = INT_MIN;

        // 遍历以arr[i]为结尾，并且删除和不删除元素的情况，找出最大值！
        for (int i = 0; i < N; i++) {
            retCnt = fmax(dp1[i], retCnt);
            retCnt = fmax(retCnt, dp2[i]);
        }

        return retCnt;
}

/*
300
stack
*/
int lengthOfLIS(int* nums, int numsSize)
{
	if (nums == NULL || numsSize <= 0) {
		return 0;
	}

	int dp[numsSize];
	dp[0] = 1;

	int max = 1;

        for (int i = 0; i < numsSize; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = fmax(dp[i], dp[j] + 1);
                }
            }
		max = fmax(max, dp[i]);
        }

	return max;
}

/*
面试题 16.16. 部分排序
给定一个整数数组，编写一个函数，找出索引m和n，只要将
索引区间[m,n]的元素排好序，整个数组就是有序的。注意：
n-m尽量最小，也就是说，找出符合条件的最短序列。
函数返回值为[m,n]，若不存在这样的m和n（例如整个数组是有
序的），请返回[-1,-1]。

示例：

输入： [1,2,4,7,10,11,7,12,6,7,16,18,19]
输出： [3,9]
提示：

0 <= len(array) <= 1000000
*/

/*
array中某个数字在排序前后位置不变，必须满足两个条件：
1. 前面没有比自己小的数字；
2.后面没有比自己打的数字。
定义dp保存上面表述的信息， dp[i]=true表示array[i]在排序前后位置
不变，dp[i]=false，表示在排序前后array[i]位置发生变化。
从前向后扫描数组，不断更新扫描到的最大值，既可以判断
当前array[i]之前是否存在比自己小的数字，如果存在则dp[i]置为
false;
从后向前扫描数组，不断更新扫描到的最小值，既可以判断
当前array[i]之后是否存在比自己小的数字，如果存在则dp[i]置为
false;
找到dp[i]为false的最小和最大的i，即为要返回的数据
*/

int* subSort(int* array, int arraySize, int* returnSize){
     int *ret = (int *)calloc(2, sizeof(int));
     ret[0] = -1;
    ret[1] = -1;
    *returnSize = 2;
    if (arraySize <= 0 || arraySize == NULL ) {
        return ret;
    }

    int dp[arraySize];
    memset(dp, 0, sizeof(dp));
    int maxval = array[0];
    for (int i = 0; i < arraySize; i++) {
        if (array[i] < maxval) {
            dp[i] = 1;
        } else {
            maxval = array[i];
        }
    }

    int minval = array[arraySize - 1];
    int rmax = -1;
    int rmin = arraySize;
    for(int i = arraySize - 1; i >= 0; i--) {
        if (array[i] > minval) {
            dp[i] = 1;
        } else {
            minval = array[i];
        }

        if(dp[i] == 1) {
                rmax = fmax(rmax, i);
                rmin = fmin(rmin, i);
        }
    }

    if (rmax != -1) {
        ret[0] = rmin;
        ret[1] = rmax;
    }

    return ret;
}

/*
DP  see dfs
dp[i][j] = fmin(dp[i - 1][j], dp[i][j - 1]) + dp[i][j];
*/
int minPathSum(int** grid, int gridSize, int* gridColSize) {
	if (grid == NULL || gridSize < 1 || gridColSize == NULL)
		return 0;

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			if (i == 0 && j == 0)
				continue;
			else if (i == 0)
				grid[i][j] += grid[i][j - 1];
			else if (j == 0)
				grid[i][j] += grid[i - 1][j];
			else
				grid[i][j] += fmin(grid[i][j - 1], grid[i - 1][j]);
		}
	}

	return grid[gridSize - 1][gridColSize[0] - 1];
}


/*
174. 地下城游戏
一些恶魔抓住了公主（P）并将她关在了地下城的右下角。
地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士
（K）最初被安置在左上角的房间里，他必须穿过地下城
并通过对抗恶魔来拯救公主。
骑士的初始健康点数为一个正整数。如果他的健康点数
在某一时刻降至 0 或以下，他会立即死亡。
有些房间由恶魔守卫，因此骑士在进入这些房间时会失
去健康点数（若房间里的值为负整数，则表示骑士将损失
健康点数）；其他房间要么是空的（房间里的值为 0），要
么包含增加骑士健康点数的魔法球（若
房间里的值为正整数，则表示骑士将增加健康点数）。
为了尽快到达公主，骑士决定每次只向右或向下移动一步。
编写一个函数来计算确保骑士能够拯救到公主所需的最低
初始健康点数。
例如，考虑到如下布局的地下城，如果骑士遵循最佳路径
右 -> 右 -> 下 -> 下，则骑士的初始健康点数至少为 7。
*/
int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize)
{
    if (dungeon == NULL || dungeonSize == 0 || *dungeonColSize == 0) {
        return 0;
    }
    int row = dungeonSize;
    int col = *dungeonColSize;
   int dp[row][col];
    // 设置最后一个值。
  	dp[row - 1][col -1] = fmax(0, -dungeon[row - 1][col - 1]);

    // 设置最后一列的值
  	for (int i = row - 2; i >= 0; --i) {
        int needMin = dp[i + 1][col - 1] - dungeon[i][col - 1];
        dp[i][col -1] = fmax(0, needMin);
    }

    // 设置最后一行的值
  	for (int i = col - 2; i >= 0; --i) {
        int needMin = dp[row - 1][i + 1] - dungeon[row - 1][i];
        dp[row - 1][i] = fmax(0, needMin);
    }

    for (int i = row - 2; i >= 0; --i) {
        for (int j = col - 2; j >= 0; --j) {
			// 从右边和下边选择一个最小值，然后减去当前的 dungeon 值
            int needMin = fmin(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
            dp[i][j] = fmax(0, needMin);
        }
    }
    return dp[0][0] + 1;


}

/*97. 交错字符串*/
/*
动态规划
状态定义
令dp[i][j]为字符子串s1[0, i),s2[0, j)能否组成s3[0, i+j)。
ps: s1[0, i) = s1.substring(0, i),不包含i。

对于字符串的状态dp[i]来说，通常要考虑所有子串的长度[0, n]，因此定义dp[n+1],n是字符串s的长度，同理二维也一样。

状态转移
对于dp[i][j]该状态来说，要想组成s3[0,i+j)，其s3[0, i+j)最后一个字符s3[i+j-1]要么来自s1[i-1], 要么来自s2[j-1],因此，状态转移：

若s1[i-1]==s3[i+j-1]：
dp[i][j] = dp[i-1][j],i > 0
dp[i][j]=dp[i?1][j],i>0

若s2[j-1]==s3[i+j-1]：
dp[i][j] = dp[i][j-1],j >0
dp[i][j]=dp[i][j?1],j>0

状态初始化：dp[0][0] = true，表示两个空字符串能够组成一个空字符串。

*/
bool isInterleave(char* s1, char* s2, char* s3) {
    int n = strlen(s1), m = strlen(s2), t = strlen(s3);

    int f[n + 1][m + 1];
    memset(f, 0, sizeof(f));

    if (n + m != t) {
        return false;
    }

    f[0][0] = true;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int p = i + j - 1;
            if (i > 0) {
                f[i][j] |= (f[i - 1][j] && s1[i - 1] == s3[p]);
            }
            if (j > 0) {
                f[i][j] |= (f[i][j - 1] && s2[j - 1] == s3[p]);
            }
        }
    }

    return f[n][m];
}

/*
546. 移除盒子
给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。
你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k*k 个积分。
当你将所有盒子都去掉之后，求你能获得的最大积分和。



示例：

输入：boxes = [1,3,2,2,2,3,4,3,1]
输出：23
解释：
[1, 3, 2, 2, 2, 3, 4, 3, 1]
----> [1, 3, 3, 4, 3, 1] (3*3=9 分)
----> [1, 3, 3, 3, 1] (1*1=1 分)
----> [1, 1] (3*3=9 分)
----> [] (2*2=4 分)
*/
int dp[100][100][100];

int calculatePoints(int* boxes, int l, int r, int k) {
    if (l > r) return 0;
    if (dp[l][r][k] != 0) return dp[l][r][k];
    while (r > l && boxes[r] == boxes[r - 1]) {
        r--;
        k++;
    }
    dp[l][r][k] = calculatePoints(boxes, l, r - 1, 0) + (k + 1) * (k + 1);
    for (int i = l; i < r; i++) {
        if (boxes[i] == boxes[r]) {
            dp[l][r][k] = fmax(dp[l][r][k], calculatePoints(boxes, l, i, k + 1) + calculatePoints(boxes, i + 1, r - 1, 0));
        }
    }
    return dp[l][r][k];
}

int removeBoxes(int* boxes, int boxesSize) {
    memset(dp, 0, sizeof dp);
    return calculatePoints(boxes, 0, boxesSize - 1, 0);
}


/*
664. 奇怪的打印机
有台奇怪的打印机有以下两个特殊要求：

打印机每次只能打印同一个字符序列。
每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。
给定一个只包含小写英文字母的字符串，你的任务是计算这个打印机打印它需要的最少次数。

示例 1:

输入: "aaabbb"
输出: 2
解释: 首先打印 "aaa" 然后打印 "bbb"。
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAX_LEN 101

#define MMAX(a, b)        ((a) > (b)? (a) : (b))
#define MMIN(a, b)        ((a) < (b)? (a) : (b))

int dp[MAX_LEN][MAX_LEN];

//【算法思路】分组dp。经典的分组dp模型，重点解决的问题，是切割后左半部分的处理方法。
//          dp[i][j]表示从s[i]到s[j]的打印次数，dp[i][j]可以由k属于i~j中的所有s[i] == s[k]的k点分解
//          表明s[i]和s[k]由一次打印完成
// 1.范围从小到大
// 2.当s[i] == s[k]将问题分解为两部分，分别解决两侧的问题
// 3.处理切割出的两部分，dp[i][k] = dp[i][k-1]（子问题）；dp[k+1][j]已经求出（子问题）
int strangePrinter(char * s){
    int slen = strlen(s);
    if(slen == 0) {
        return 0;
    }

    for(int i = 0; i < slen; i++) {
        for(int j = 0; j < slen; j++) {
            dp[i][j] = 0;
        }
    }

    for(int gap = 0; gap < slen; gap++) {
        for(int i = 0; i + gap < slen; i++) {
            int j = i + gap;

            if(gap == 0) {
                dp[i][j] = 1;
                continue;
            }

            int tmin = INT_MAX;

            for(int k = i; k <= j; k++) {
                if(k == i) {
                    tmin = MMIN(tmin, 1 + dp[i + 1][j]);
                } else if(s[i] == s[k] && k == j) {
                    tmin = MMIN(tmin, dp[i][j - 1]);
                } else if(s[i] == s[k]){
                    tmin = MMIN(tmin, dp[i][k - 1] + dp[k + 1][j]);
                }
            }

            dp[i][j] = tmin;
        }
    }
/*
    for(int i = 0; i < slen; i++) {
        for(int j = 0; j < slen; j++) {
            printf("[%d,%d]%d    ", i, j, dp[i][j]);
        }
        printf("\n");
    }
*/
    return dp[0][slen - 1];
}

/*
689. 三个无重叠子数组的最大和
给定数组 nums 由正整数组成，找到三个互不重叠的子数组的最大和。

每个子数组的长度为k，我们要使这3*k个项的和最大化。

返回每个区间起始索引的列表（索引从 0 开始）。如果有多个结果，返回字典序最小的一个。

示例:

输入: [1,2,1,2,6,7,5,1], 2
输出: [0, 3, 5]
解释: 子数组 [1, 2], [2, 6], [7, 5] 对应的起始索引为 [0, 3, 5]。
我们也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX 20001
int dp[3][MAX][3];
int maxSum[3][MAX];

void init(int* nums, int numsSize, int k, int* returnSize)
{
    memset(dp, 0, sizeof(dp));
    memset(maxSum, 0, sizeof(maxSum));

    dp[0][k - 1][0] = 0;
    maxSum[0][k - 1] = 0;
    for (int i = 0; i < k; i++) {
        maxSum[0][k - 1] += nums[i];
    }
    dp[1][2 * k - 1][0] = 0;
    dp[1][2 * k - 1][1] = k;
    maxSum[1][2 * k - 1] = 0;
    for (int i = 0; i < 2 * k; i++) {
        maxSum[1][2 * k - 1] += nums[i];
    }
    dp[2][3 * k - 1][0] = 0;
    dp[2][3 * k - 1][1] = k;
    dp[2][3 * k - 1][2] = 2 * k;
    maxSum[2][3 * k - 1] = 0;
    for (int i = 0; i < 3 * k; i++) {
        maxSum[2][3 * k - 1] += nums[i];
    }
}

int check(int* nums, int numsSize, int k, int* returnSize)
{
    if (returnSize == NULL) {
        return -1;
    }
    if (nums == NULL || numsSize < 0 || k < 0 || k > numsSize / 3) {
        *returnSize = 0;
        return -1;
    }
    return 0;
}

int* maxSumOfThreeSubarrays(int* nums, int numsSize, int k, int* returnSize)
{
    if (check(nums, numsSize, k, returnSize) != 0) {
        return NULL;
    }

    init(nums, numsSize, k, returnSize);

    for (int i = 0; i < 3; i++) {
        for (int j = (i + 1) * k; j < numsSize; j++) {
            int sum = 0;
            // 计算包含当前数字的k个数字的和，子数组，必定连续
            for (int r = 0; r < k; r++) {
                sum += nums[j - r];
            }
            // 多于一组的时候需要降维累加
            if (i > 0) {
                sum += maxSum[i - 1][j - k];
            }
            if (sum <= maxSum[i][j - 1]) {
                // 最大的子数组不含当前数字
                for (int s = 0; s <= i; s++) {
                    dp[i][j][s] = dp[i][j - 1][s];
                }
                maxSum[i][j] = maxSum[i][j - 1];
            } else {
                int s;
                // 当前数字新增后，大于之前的最大情况
                for (s = 0; s < i; s++) {
                    dp[i][j][s] = dp[i - 1][j - k][s];
                }
                dp[i][j][s] = j - k + 1;
                maxSum[i][j] = sum;
            }
        }
    }
    *returnSize = 3;
    return dp[2][numsSize - 1];
}

/*
面试题 17.13. 恢复空格
哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，并且大写也弄成了小写。像句子"I reset the computer. It still didn’t boot!"已经变成了"iresetthecomputeritstilldidntboot"。在处理标点符号和大小写之前，你得先把它断成词语。当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。假设文章用sentence表示，设计一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。

注意：本题相对原题稍作改动，只需返回未识别的字符数



示例：

输入：
dictionary = ["looked","just","like","her","brother"]
sentence = "jesslookedjustliketimherbrother"
输出： 7
解释： 断句后为"jess looked
*/