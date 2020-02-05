#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/************ǰ׺*******************/


/*��������*/
/*
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
�Ż��ռ�
��Ϊ�Ե�ǰ����β��������кͽ���
ǰһ�����к���أ����Կ�����һ����������
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
152. �˻����������
����һ���������� nums ���ҳ�һ�������г˻����
�����������У����������ٰ���һ��������

ʾ�� 1:

����: [2,3,-2,4]
���: 6
����: ������ [2,3] �����˻� 6��
ʾ�� 2:

����: [-2,0,-1]
���: 0
����: �������Ϊ 2, ��Ϊ [-2,-1] ���������顣
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
1292. Ԫ�غ�С�ڵ�����ֵ�������ε����߳�
����һ����СΪ m x n �ľ��� mat ��һ��������ֵ threshold��

���㷵��Ԫ���ܺ�С�ڻ������ֵ����������������߳���
���û�������������������򷵻� 0 ��


ʾ�� 1��

���룺mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
�����2
���ͣ��ܺ�С�� 4 �������ε����߳�Ϊ 2����ͼ��ʾ��

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
��дһ�������ҳ��� n ��������

��������ֻ���������� 2, 3, 5 ����������

ʾ��:

����: n = 10
���: 12
����: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 ��ǰ 10 ��������
˵��:

1 �ǳ�����
n ������1690��

*/
/*
��̬�滮(��ָ��)
���еĳ��������Բ��֮ǰ��������֪������ˣ���ô��Ҫ�ҳ�����������
�������ҷ����ǣ�ÿ�γ���֮ǰ���е������ϣ�ȡ��ֵ��С���Ǹ���ʱ�临�Ӷȱ�ը
�Ż�˼·��

������ÿ�ζ�����������ϣ�������Ҫ���˵������ܵ����
��֪2��3��5�����г������ʱ����ֵ�����ٶ��ǲ�һ����
����ÿ�δ������³����У���ѡ������֪ĩβ��������Сֵ������Ϊ�µĳ���
��3���߳�5���³��������ĳ��δ��ѡ�з������ᣬ��ô�϶���ĳһ�̻ᱻ�Ž�ȥ
����ʹ�������α���ȷ���ѱ�����������³�����Сֵ��ÿ�ν���Ҫ�Ա��������α���2��3��5�˻�����


��һ����������Եײ����ϵķ���---������Ŀ��ô�任����̬�滮����Ҫ����ʵʵһ������������
    �ڱ������ݷ��棬�������Ķ�̬�滮����ͷ������β
    �����ĺ����ѵ����ڵ�ǰ��ֵ��ǰ������������ǰһ���йء�
    ��򵥵�˼·��Ѱ�ҵ�k����֮ǰ��k-1�����ֱ��2,3,5��ˣ�Ȼ���ҵ���k-1������С������
    ����Ż������ٴ洢�ͼ��������

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
		if (min == b)// ����else ����6��2��3�ı�����i2 i3ͬʱ�ƶ������ظ�����
			i3++;
		if (min == c)
			i5++;

		dp[i] = min;
	}

	return dp[n - 1];
}


