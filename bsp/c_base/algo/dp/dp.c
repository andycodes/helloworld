#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
����1:�����ӽṹ;ÿ���׶ε�״̬��ֵ����ͨ��ǰ��׶ε�״̬��ֵ�Ƶ�������,����.
����2:�޺�Ч��;ÿ���׶ε�״ֵ̬һ��ȷ��֮��,�ǲ��ܺ���׶�״ֵ̬��Ӱ���,����.
����3:�ظ�������;�ӵݹ�ⷨ�о��ܿ��������ظ�������ļ���,����.

*/

/*
����:
��ά����ǰ׺��:
sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
*/

/************ǰ׺����*******************/


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
363. �������򲻳��� K �������ֵ��
����һ���ǿն�ά���� matrix ��һ������ k���ҵ���������ڲ������� k �������κ͡�

ʾ��:

����: matrix = [[1,0,1],[0,-2,3]], k = 2
���: 2
����: �������� [[0, 1], [-2, 3]] ����ֵ���� 2���� 2 �ǲ����� k ��������֣�k = 2����
˵����

�����ڵľ����������������� 0��
�������Զ�����������㽫��ν���أ�

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


/*
1220. ͳ��Ԫ����ĸ���е���Ŀ
����һ������ n�������æͳ��һ�����ǿ��԰����������γɶ��ٸ�����Ϊ n ���ַ�����

�ַ����е�ÿ���ַ���Ӧ����СдԪ����ĸ��'a', 'e', 'i', 'o', 'u'��
ÿ��Ԫ�� 'a' ���涼ֻ�ܸ��� 'e'
ÿ��Ԫ�� 'e' ����ֻ�ܸ��� 'a' ������ 'i'
ÿ��Ԫ�� 'i' ���� ���� �ٸ�����һ�� 'i'
ÿ��Ԫ�� 'o' ����ֻ�ܸ��� 'i' ������ 'u'
ÿ��Ԫ�� 'u' ����ֻ�ܸ��� 'a'
���ڴ𰸿��ܻ�ܴ��������㷵�� ģ 10^9 + 7 ֮��Ľ����



ʾ�� 1��

���룺n = 1
�����5
���ͣ����п��ܵ��ַ����ֱ��ǣ�"a", "e", "i" , "o" �� "u"��
ʾ�� 2��

���룺n = 2
�����10
���ͣ����п��ܵ��ַ����ֱ��ǣ�"ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" �� "ua"��


���Ƿ���ÿһ�����������һ����ĸ�� ֻ��ǰһ���ַ��йء� ���üӷ�ԭ���� ����ֱ���Ƴ���

������f(i, char)f(i,char)����ʾǰii���ַ���charchar��β�ͺϷ��ַ���������

���ɹ�����Եõ���
f(i, 'a') = f(i - 1, 'e') + f(i - 1, 'i') + f(i -1, 'u')
�������ơ�

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
������47. ���������ֵ
�Ѷ��е�9
��һ�� m*n �����̵�ÿһ�񶼷���һ�����ÿ�����ﶼ��һ���ļ�ֵ����ֵ���� 0��������Դ����̵����Ͻǿ�ʼ�ø�����������ÿ�����һ��������ƶ�һ��ֱ���������̵����½ǡ�����һ�����̼������������ļ�ֵ���������������õ����ټ�ֵ�����

ʾ�� 1:
����:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
���: 12
����: ·�� 1��3��5��2��1 �����õ�����ֵ������

*/


int maxValueParmCheck(int** grid, int gridSize, int* gridColSize)
{
	if (grid == NULL || gridColSize <= 0 || gridColSize == NULL)
		return -1;
	return 0;
}

/*
����ⷨ����

class Solution:
    def maxValue(self, grid: List[List[int]]) -> int:
        m,n=len(grid),len(grid[0])
        if not m or not n: return 0
        for i in range(m):
            for j in range(n):
                grid[i][j] += max(i>0 and grid[i - 1][j], j>0 and grid[i][j - 1])
        return grid[-1][-1]


״̬ת��
dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
��ʼֵ
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
�ռ��Ż���ֻ�õ���dp[i][j - 1]��dp[i - 1][j]������ѹ����һά����

dp[i][j - 1]����dp[j - 1]
dp[i - 1][j]��û����ǰ��dp[j]
ע�⴦���߽确

(j > 0? dp[j - 1] : 0)���߲�ͨ�ĵط���0�Ϳ����ˣ�
����������dp[j]������
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
62. ��ͬ·��
�Ѷ��е�439�ղط����л�ΪӢ�Ĺ�ע����
һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ"Start" ����
������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ"Finish"����
���ܹ��ж�������ͬ��·����

���磬��ͼ��һ��7 x 3 �������ж��ٿ��ܵ�·����
˵����m �� n ��ֵ�������� 100��
ʾ�� 1:
����: m = 3, n = 2
���: 3
����:
�����Ͻǿ�ʼ���ܹ��� 3 ��·�����Ե������½ǡ�
1. ���� -> ���� -> ����
2. ���� -> ���� -> ����
3. ���� -> ���� -> ����

*/

/*
˼·�������Ҷ�ѧ���ݹ�,��֪���ݹ����ظ����������,��������д�ĵݹ�������m��n�Ƚϴ��ʱ��,
ͬ���ᳬ������ʱ�䡣�����ǿ��Լ�һ������¼,���Ѿ���������Ľ����������,
�´���Ҫ����ͬ���ĵݹ�ʱ,ֱ�Ӵӱ���¼��ȡ��ʹ��

*/
int cycle(int i,int j)
{
	if(i == 0 || j == 0) return 1;
	return cycle(i-1,j)+cycle(i,j-1);
}


int uniquePaths(int m, int n)
{
	return cycle(m-1,n-1);
}

int[][] dp = new int[100][100];
 int uniquePaths(int m, int n) {
    return cycle(m-1,n-1);
}
 int cycle(int i,int j){
    if(i == 0 || j == 0) return 1;
    if(dp[i][j] != 0) return dp[i][j];
    dp[i][j] = cycle(i-1,j)+cycle(i,j-1);
    return dp[i][j];
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
	���ѭ����һ��(�ڲ�ѭ����һȦ)��ʱ��
	��ʾ��һ�е�i�е��ܿ�����
	���ѭ��������(�ڲ�ѭ������Ȧ)��ʱ��
	��ʾ�ڶ��е�i�е��ܿ�����

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
};

/*�������*/
int uniquePaths(int m, int n) {
    int N = n + m - 2;
    int k = m - 1;
    long res = 1;
    for (int i = 1; i <= k; i++)
        res = res * (N - k + i) / i;
    return (int) res;
}

/*
63. ��ͬ·�� II
�Ѷ��е�234
һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ"Start" ����
������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ"Finish"����
���ڿ������������ϰ����ô�����Ͻǵ����½ǽ����ж�������ͬ��·����

�����е��ϰ���Ϳ�λ�÷ֱ��� 1 �� 0 ����ʾ��
˵����m �� n ��ֵ�������� 100��
ʾ�� 1:
����:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
���: 2
����:
3x3 ��������м���һ���ϰ��
�����Ͻǵ����½�һ���� 2 ����ͬ��·����
1. ���� -> ���� -> ���� -> ����
2. ���� -> ���� -> ���� -> ����

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
LCS��ģ��
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
dp[i][j]��ʾ��str1�ĵ�i��Ϊ��β��str2�ĵ�j��Ϊ��β
*/
/*
712. �����ַ�������СASCIIɾ����
�Ѷ��е�93
���������ַ���s1, s2���ҵ�ʹ�����ַ����������ɾ���ַ���ASCIIֵ����С�͡�
ʾ�� 1:
����: s1 = "sea", s2 = "eat"
���: 231
����: �� "sea" ��ɾ�� "s" ���� "s" ��ֵ(115)�����ܺ͡�
�� "eat" ��ɾ�� "t" ���� 116 �����ܺ͡�
����ʱ�������ַ�����ȣ�115 + 116 = 231 ���Ƿ�����������С�͡�

*/

/*
������Ѱ��һ����ͬ�����У�
���ַ���s1��s2ɾ��Ϊ��������ʱ��ɾ��
��ASCII�ۺ���С���ȼ�����һ���ַ���s1
��s2��ASCII���ܺ����Ĺ�ͬ�����С�
��Ϊs1��s2���ܺ͹̶�������ͬ�����е�
�ܺ����ʱ��ɾ����Ϊ�������еĴ��۱�Ȼ
��С��
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
