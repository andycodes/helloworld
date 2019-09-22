#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*��������*/
/*
������ö�̬�滮��˼·�����ѽ�����Ƚ��ѵ��Ǻ���������÷��η���⣬�������䲻�����Žⷨ�������Ȳ��г���
��̬�滮�������ȶ�������б�������ǰ������������к�Ϊ sum�����Ϊ ans
��� sum > 0����˵�� sum �Խ��������Ч������ sum ���������ϵ�ǰ��������
��� sum <= 0����˵�� sum �Խ��������Ч������Ҫ�������� sum ֱ�Ӹ���Ϊ��ǰ��������
ÿ�αȽ� sum �� ans�Ĵ�С�������ֵ��Ϊans�������������ؽ��
ʱ�临�Ӷȣ�O(n)O(n)
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
��̬�滮����dp[i]��ʾ��i��β����������к͡���ʼֵ dp[0] = nums[0]��Ȼ��ӵڶ�������ʼ����

if ��ǰ������ǰһ��������кʹ��ڵ�ǰ�����򽫵�ǰ���ӵ����к��У�nums[i] + dp[i-1] > nums[i]���� dp[i] = nums[i] + dp[i-1];
else �Ե�ǰ����β��������кͼ�Ϊ��ǰ������ dp[i] = nums[i]
Ȼ���ж��Ե�ǰ����β��������к��Ƿ����������к�
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
�Ż��ռ�
��Ϊ�Ե�ǰ����β��������кͽ���ǰһ�����к���أ����Կ�����һ����������
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
