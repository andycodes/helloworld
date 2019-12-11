#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*最大子序和*/
/*
这道题用动态规划的思路并不难解决，
比较难的是后文提出的用分治法求解，
但由于其不是最优解法，所以先不列出来
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

int maxSubArray(int* nums, int numsSize){
    int ans = nums[0];
    int sum = 0;
    int i;

    for (i = 0; i < numsSize;i++ ){
        if (sum > 0)
            sum += nums[i];
        else
            sum = nums[i];

        ans = ans > sum ? ans:sum;
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
int maxSubArray(int* nums, int numsSize){
    int size = numsSize;
    int max = nums[0];
    int dp[size];
    dp[0] = nums[0];
    for (int i = 1; i < size; ++i) {
        if (nums[i] + dp[i-1] >= nums[i]) {
            dp[i] = nums[i] + dp[i-1];
        } else {
            dp[i] = nums[i];
        }
        if (dp[i] > max) {
            max = dp[i];
        }
    }
    return max;
}

/*
优化空间
因为以当前数结尾的最大序列和仅与前一个序列和相关，所以可以用一个变量保存
*/

int maxSubArray(int* nums, int numsSize){
    int size = numsSize;
    int max = nums[0];
   int pre = nums[0];
    for (int i = 1; i < size; ++i) {
        if (nums[i] + pre >= nums[i]) {
            pre = nums[i] + pre;
        } else {
            pre = nums[i];
        }
        if (pre > max) {
            max = pre;
        }
    }
    return max;
}

/*
给定一个整数数组 nums ，找出一个序列中乘积最大的连续子序列（该序列至少包含一个数）。

示例 1:

输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
示例 2:

输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
*/

#define math_max(a, b) ((a) > (b) ? (a) : (b))
#define match_min(a, b) ((a) < (b) ? (a) : (b))
#define INT_MAX		((int)(~0U >> 1))
#define INT_MIN		(-INT_MAX - 1)
int maxProduct(int* nums, int numsSize){
        const int N=numsSize;

	int d[numsSize];
	int e[numsSize];

	d[0]=nums[0];
        e[0]=nums[0];

        int ans=INT_MIN;
        ans=math_max(ans,math_max(d[0],e[0]));
        for(int i=1;i<N;++i){
            d[i]=math_max(nums[i],math_max(nums[i]*d[i-1],nums[i]*e[i-1]));
            e[i]=match_min(nums[i],match_min(nums[i]*d[i-1],nums[i]*e[i-1]));
            ans = math_max(ans,math_max(d[i],e[i]));
        }
        return ans;
}


#define MIN3(a,b,c) ((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
int minDistance(char * word1, char * word2)
{
	int row = (word1 == NULL) ? 0: strlen(word1);
	int col =  (word2 == NULL) ? 0: strlen(word2);

	row++;
	col++;

    int mat[row][col];                  /* C99 - variable-length array */


    for( int i=0; i<row; ++i ) {        /* 数组的行 */
        for( int j=0; j<col; ++j ) {    /* 数组的列 */
            if( i == 0 ) {
                mat[i][j] = j;          /* 初始化第1行为 [ 0 1 2 ... ] */
            }
            else if( j == 0 ) {
                mat[i][j] = i;          /* 初始化第1列为 [ 0 1 2 ... ] */
            }
            else {
                int cost = ( word1[i-1] == word2[j-1] ) ? 0 : 1;     /* 记录word1[i-1]与word2[j-1]是否相等 */
                mat[i][j] = MIN3( mat[i-1][j  ] + 1,           /* 取三者的最小值 */
                                  mat[i  ][j-1] + 1,
                                  mat[i-1][j-1] + cost);
            }
        }
    }

    return mat[row-1][col-1];
}}


int main()
{
	int w[5] = { 0 , 2 , 3 , 4 , 5 };			//商品的体积2、3、4、5
	int v[5] = { 0 , 3 , 4 , 5 , 6 };			//商品的价值3、4、5、6
	int bagV = 8;					        //背包大小

        /*
        动态规划表
        dp[ i ][ j ] 表示 在面对第 i 件物品，
        且背包剩余容量为  j 时所能获得的最大价值 */
	int dp[5][9] = { { 0 } };

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= bagV; j++) {
          /* j < w[i] 的情况，这时候背包容量不足以放下第 i 件物品，
          只能选择不拿m[ i ][ j ] = m[ i-1 ][ j ]*/
			if (j < w[i])
				dp[i][j] = dp[i - 1][j];
            /*
 j>=w[i] 的情况，这时背包容量可以放下第 i 件物品，
 我们就要考虑拿这件物品是否能获取更大的价值。
 如果拿取，m[ i ][ j ]=m[ i-1 ][ j-w[ i ] ] + v[ i ]。
 这里的m[ i-1 ][ j-w[ i ] ]指的就是考虑了i-1件物品，
 背包容量为j-w[i]时的最大价值，
 也是相当于为第i件物品腾出了w[i]的空间。
 如果不拿，m[ i ][ j ] = m[ i-1 ][ j ] , 同（1）究竟是拿还是不拿，
 自然是比较这两种情况那种价值最大。
            */
			else
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
		}
	}

	//动态规划表的输出
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d ",dp[i][j]);
		}
		printf("\n");
	}

	return 0;
}


