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


#define MIN3(a,b,c) ((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
int minDistance(char * word1, char * word2)
{
	int row = (word1 == NULL) ? 0: strlen(word1);
	int col =  (word2 == NULL) ? 0: strlen(word2);

	row++;
	col++;

    int mat[row][col];                  /* C99 - variable-length array */


    for( int i=0; i<row; ++i ) {        /* ������� */
        for( int j=0; j<col; ++j ) {    /* ������� */
            if( i == 0 ) {
                mat[i][j] = j;          /* ��ʼ����1��Ϊ [ 0 1 2 ... ] */
            }
            else if( j == 0 ) {
                mat[i][j] = i;          /* ��ʼ����1��Ϊ [ 0 1 2 ... ] */
            }
            else {
                int cost = ( word1[i-1] == word2[j-1] ) ? 0 : 1;     /* ��¼word1[i-1]��word2[j-1]�Ƿ���� */
                mat[i][j] = MIN3( mat[i-1][j  ] + 1,           /* ȡ���ߵ���Сֵ */
                                  mat[i  ][j-1] + 1,
                                  mat[i-1][j-1] + cost);
            }
        }
    }

    return mat[row-1][col-1];
}}


int main()
{
	int w[5] = { 0 , 2 , 3 , 4 , 5 };			//��Ʒ�����2��3��4��5
	int v[5] = { 0 , 3 , 4 , 5 , 6 };			//��Ʒ�ļ�ֵ3��4��5��6
	int bagV = 8;					        //������С

        /*
        ��̬�滮��
        dp[ i ][ j ] ��ʾ ����Ե� i ����Ʒ��
        �ұ���ʣ������Ϊ  j ʱ���ܻ�õ�����ֵ */
	int dp[5][9] = { { 0 } };

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= bagV; j++) {
          /* j < w[i] ���������ʱ�򱳰����������Է��µ� i ����Ʒ��
          ֻ��ѡ����m[ i ][ j ] = m[ i-1 ][ j ]*/
			if (j < w[i])
				dp[i][j] = dp[i - 1][j];
            /*
 j>=w[i] ���������ʱ�����������Է��µ� i ����Ʒ��
 ���Ǿ�Ҫ�����������Ʒ�Ƿ��ܻ�ȡ����ļ�ֵ��
 �����ȡ��m[ i ][ j ]=m[ i-1 ][ j-w[ i ] ] + v[ i ]��
 �����m[ i-1 ][ j-w[ i ] ]ָ�ľ��ǿ�����i-1����Ʒ��
 ��������Ϊj-w[i]ʱ������ֵ��
 Ҳ���൱��Ϊ��i����Ʒ�ڳ���w[i]�Ŀռ䡣
 ������ã�m[ i ][ j ] = m[ i-1 ][ j ] , ͬ��1���������û��ǲ��ã�
 ��Ȼ�ǱȽ�������������ּ�ֵ���
            */
			else
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
		}
	}

	//��̬�滮������
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d ",dp[i][j]);
		}
		printf("\n");
	}

	return 0;
}


