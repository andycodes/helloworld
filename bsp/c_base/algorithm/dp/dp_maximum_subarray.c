#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*最大子序和*/
/*
这道题用动态规划的思路并不难解决，比较难的是后文提出的用分治法求解，但由于其不是最优解法，所以先不列出来
动态规划的是首先对数组进行遍历，当前最大连续子序列和为 sum，结果为 ans
如果 sum > 0，则说明 sum 对结果有增益效果，则 sum 保留并加上当前遍历数字
如果 sum <= 0，则说明 sum 对结果无增益效果，需要舍弃，则 sum 直接更新为当前遍历数字
每次比较 sum 和 ans的大小，将最大值置为ans，遍历结束返回结果
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
动态规划，用dp[i]表示以i结尾的最大子序列和。初始值 dp[0] = nums[0]，然后从第二个数开始遍历

if 当前数加上前一个最大序列和大于当前数，则将当前数加到序列和中，nums[i] + dp[i-1] > nums[i]，则 dp[i] = nums[i] + dp[i-1];
else 以当前数结尾的最大序列和即为当前数本身 dp[i] = nums[i]
然后判断以当前数结尾的最大序列和是否大于最大序列和
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

int main()
{


}
