#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*��������*/
/*
������ö�̬�滮��˼·�����ѽ����
�Ƚ��ѵ��Ǻ���������÷��η���⣬
�������䲻�����Žⷨ�������Ȳ��г���
��̬�滮�������ȶ�������б�����
��ǰ������������к�Ϊ sum�����Ϊ ans
��� sum > 0����˵�� sum �Խ��������Ч����
�� sum ���������ϵ�ǰ��������
��� sum <= 0����˵�� sum �Խ��������Ч����
��Ҫ�������� sum ֱ�Ӹ���Ϊ��ǰ��������
ÿ�αȽ� sum �� ans�Ĵ�С�������ֵ��Ϊans��
�����������ؽ��
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
��̬�滮����dp[i]��ʾ��i��β����������к͡�
��ʼֵ dp[0] = nums[0]��Ȼ��ӵڶ�������ʼ����

if ��ǰ������ǰһ��������кʹ��ڵ�ǰ����
�򽫵�ǰ���ӵ����к��У�nums[i] + dp[i-1] > nums[i]��
�� dp[i] = nums[i] + dp[i-1];
else �Ե�ǰ����β��������кͼ�Ϊ��ǰ������
dp[i] = nums[i]
Ȼ���ж��Ե�ǰ����β��������к���
�����������к�
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

/*
����һ���������� nums ���ҳ�һ�������г˻��������������У����������ٰ���һ��������

ʾ�� 1:

����: [2,3,-2,4]
���: 6
����: ������ [2,3] �����˻� 6��
ʾ�� 2:

����: [-2,0,-1]
���: 0
����: �������Ϊ 2, ��Ϊ [-2,-1] ���������顣
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
