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
һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б�
��Ϊ"Start" ����������ÿ��ֻ�����»��������ƶ�һ����
��������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ"Finish"����
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
˼·�������Ҷ�ѧ���ݹ�,��֪���ݹ����ظ����������,
��������д�ĵݹ�������m��n�Ƚϴ��ʱ��,
ͬ���ᳬ������ʱ�䡣�����ǿ��Լ�һ������¼,���Ѿ�����
�����Ľ����������,
�´���Ҫ����ͬ���ĵݹ�ʱ,ֱ�Ӵӱ���¼��ȡ��ʹ��
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
}

/*�������*/
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
63. ��ͬ·�� II
�Ѷ��е�234
һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ"Start" ����
������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ����
�����½ǣ�����ͼ�б��Ϊ"Finish"����
���ڿ������������ϰ����ô�����Ͻǵ����½ǽ�����
��������ͬ��·����

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
91. ���뷽��
�Ѷ��е�363
һ��������ĸ A-Z ����Ϣͨ�����·�ʽ�����˱��룺
'A' -> 1
'B' -> 2
...
'Z' -> 26
����һ��ֻ�������ֵķǿ��ַ������������뷽����������
ʾ�� 1:
����: "12"
���: 2
����: �����Խ���Ϊ "AB"��1 2������ "L"��12����

*/
/*
����Ҫ���ݵ�ǰ���ַ��Ƿ�Ϊ 0 �����ж�
s Ϊ�ַ��� s�� f(i) ���� �� s[i] һ���ж����ֽ��뷽ʽ

if s[i] == '0'
if s[i-1] == '1' || s[i-1] =='2' --> f(i) == f(i-2)
Ҳ����˵�����λֻ�ܺϲ�����Ϊ 10 ���� 20��
���� 1212120 ��ô��ʱ��������� 12121 ��ͬ
��ֻ�ǽ���������һ�� 20 �Ķ�Ӧ��ĸ�� ��������δ���ӣ�
else --> return 0
�ַ����Ƿ��� Ҳ���� 0 ֻ�ܳ����� 1 ���� 2 �ĺ��棬
������������޽���磺 1212130�� 30 �޷���Ӧ�κ��ַ���
ֱ�� return 0
if s[i] != '0'
if s[i-1] == '1' || (s[i-1] == '2' && s[i] >= '1' && s[i] <= '6') --> f(i) == f(i - 1) + f(i - 2)
Ҳ���������λ�� 10~26 ֮���� 1212121�� ���Է���� 12121 + 21��
���� 121212 + 1
else --> f(i) == f(i - 1)
Ҳ���������λ���� 10~26 ֮���� 1212132 ��ֻ�ܷ���� 121213 + 2

�������¥����ͬһ�����͵����⣬�ѵ���������������������������ֻҪ�ܿ����������Ϳ�������������

ÿ�εݽ�������ѡȡһ����Ҳ����ѡȡ��������

s[i] != '0'
��� s[i-1]s[i] <= 26, �� dp[i] = dp[i-1] + dp[i-2]
��� s[i-1]s[i] > 26, �� dp[i] = dp[i-1], ������Ϊ s[i-1]s[i] ��ɵ���λ���޷�����
s[i] == '0'
��� s[i-1]s[i] <= 26, �� dp[i] = dp[i-2], ������Ϊ s[i] �޷�����
����һЩ�龰ֱ��ʹ�����������޷������룺
���ڵ����� '0'
�� '0' ��β�Ĵ��� 26 ������
ȥ����Щ�������������������¥�ݵ������ˣ�һ�ο�����һ����Ҳ���������������ж����з�ʽ�����յ㡣

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
213. ��ҽ��� II
�Ѷ��е�255
����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݣ�ÿ�䷿�ڶ�����һ�����ֽ�����ط����еķ��ݶ�Χ��һȦ������ζ�ŵ�һ�����ݺ����һ�������ǽ����ŵġ�ͬʱ�����ڵķ���װ���໥��ͨ�ķ���ϵͳ������������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ�������
����һ������ÿ�����ݴ�Ž��ķǸ��������飬�������ڲ���������װ�õ�����£��ܹ�͵�Ե�����߽�
ʾ�� 1:
����: [2,3,2]
���: 3
����: �㲻����͵�� 1 �ŷ��ݣ���� = 2����Ȼ��͵�� 3 �ŷ��ݣ���� = 2��, ��Ϊ���������ڵġ�
ʾ�� 2:
����: [1,2,3,1]
���: 4
����: �������͵�� 1 �ŷ��ݣ���� = 1����Ȼ��͵�� 3 �ŷ��ݣ���� = 3����
     ͵�Ե�����߽�� = 1 + 3 = 4 ��

*/
#define MAX(a,b) ((a)>(b)?(a):(b))
int rob(int* nums, int numsSize){
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];
    //���������dp��aΪ͵��1�䣬bΪ��͵��1��
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
740. ɾ�����õ���
�Ѷ��е�147
����һ���������� nums ������Զ�������һЩ������
ÿ�β����У�ѡ������һ�� nums[i] ��ɾ��������� nums[i] �ĵ�����֮�������ɾ��ÿ������ nums[i] - 1 �� nums[i] + 1 ��Ԫ�ء�
��ʼ��ӵ�� 0 ����������������ͨ����Щ������õ���������
ʾ�� 1:
����: nums = [3, 4, 2]
���: 6
����:
ɾ�� 4 ����� 4 ����������� 3 Ҳ��ɾ����
֮��ɾ�� 2 ����� 2 ���������ܹ���� 6 ��������
ʾ�� 2:
����: nums = [2, 2, 3, 3, 3, 4]
���: 9
����:
ɾ�� 3 ����� 3 ������������Ҫɾ������ 2 �� 4 ��
֮���ٴ�ɾ�� 3 ��� 3 ���������ٴ�ɾ�� 3 ��� 3 ��������
�ܹ���� 9 ��������

*/
/*
�벻����ҽ����ͬ־���ȶ�����Ŀ���ȶ�����Ŀ���ȶ�����Ŀ���������� ��ɾ�����е�nums[i] - 1��nums[i]+1��

��һ����ɾ�����У���ɾ�����У���ɾ�����У�

�ڶ�����nums[i] -1��nums[i]+1������ɾ������nums[i] -1��nums[i]+1������ɾ������nums[i] -1��nums[i]+1������ɾ���� ��Ҫ��������˵��9�顣������

����С͵͵��Ǯ������nums[i]���������е�nums[i]�� Ҳ����nums[i]����nums[i]���ֵĴ����� �����ѡ��͵nums[i]����ônums���������е�nums[i]�㶼Ҫѡ��͵��Ϊʲô�����е�nums[i]����Ϊ����nums[i]+-1������������ɵ��ˣ���������ѡ��nums[i]+-1�����ļ�ͥȥ͵�ˣ�����������nums[i]�����ڲ�ȥ͵������һ����͵��nums[i]�ҵĲƲ�����Ҫ͵���е�nums[i]��Ҳ����nums[i]����count(nums[i])��ô���ǮС͵ȫ��Ҫ͵ȥ������

���������ת�Ʒ�������ڴ�ҽ������ת�Ʒ��̣�ֻ�ǰѴ�ҽ����������͵�������ͥ�ĲƲ�nums[i] ��Ϊ ͵�Ʋ��������ͥ��ȵ����м�ͥ�����вƲ��������������󵨣���̰�ģ����¸ң�

����ڴ�ҽ��ᣬ�����nums[i]�Ǵ�ҽ�����������������������nums[i]�˴�nums[i]���ֵĴ�����Ҳ�������е�nums[i]�ܺ� ��ͬ�ڴ�ҽ����������ֵ

ת�Ʒ���Ϊ dp[i] =Math.max(dp[i-1], dp[i-2] + nums[i] * count(nums[i]) ) ������i�����ֵ����nums��������ֵ����Ϊnums[i]�൱������

������������ڴ�ҽ������С͵�������С͵�Ѿ�������С͵�ˣ����ǽ������ˣ�������

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
983. ���Ʊ��
�Ѷ��е�213
��һ�������к��ܻ�ӭ�Ĺ��ȣ�����ǰһ��ƻ���һЩ�����С��ڽ�������һ�����Ҫ���е����ӽ���һ����Ϊ days �����������ÿһ����һ���� 1 �� 365 ��������
��Ʊ�����ֲ�ͬ�����۷�ʽ��
"	һ��Ϊ��һ���ͨ��֤�ۼ�Ϊ costs[0] ��Ԫ��
"	һ��Ϊ�������ͨ��֤�ۼ�Ϊ costs[1] ��Ԫ��
"	һ��Ϊ����ʮ���ͨ��֤�ۼ�Ϊ costs[2] ��Ԫ��
ͨ��֤�������������Ƶ����С� ���磬��������ڵ� 2 ����һ��Ϊ�� 7 ���ͨ��֤����ô���ǿ����������� 7 �죺�� 2 �졢�� 3 �졢�� 4 �졢�� 5 �졢�� 6 �졢�� 7 ��͵� 8 �졣
��������Ҫ����ڸ������б� days ���г���ÿһ�����������Ҫ��������ѡ�

ʾ�� 1��
���룺days = [1,4,6,7,8,20], costs = [2,7,15]
�����11
���ͣ�
���磬������һ�ֹ���ͨ��֤�ķ����������������������мƻ���
�ڵ� 1 �죬�㻨�� costs[0] = $2 ����һ��Ϊ�� 1 ���ͨ��֤�������ڵ� 1 ����Ч��
�ڵ� 3 �죬�㻨�� costs[1] = $7 ����һ��Ϊ�� 7 ���ͨ��֤�������ڵ� 3, 4, ..., 9 ����Ч��
�ڵ� 20 �죬�㻨�� costs[0] = $2 ����һ��Ϊ�� 1 ���ͨ��֤�������ڵ� 20 ����Ч��
���ܹ����� $11�����������ƻ���ÿһ�����С�

*/
/*
�ڵ�i���ʱ������г��мƻ�����Ҫ�Ƚϵ����ַ���Ϊ��

dp[i-1]+cost[0];
dp[i-7]+cost[1];
dp[i-30]+cost[2];
������������ֵΪ����ʱ��dpȡֵΪ0.
���û�г��мƻ�����ֱ����dp[i]=dp[i-1];

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
�Ӵ�һ����������
��������ԭ����ɾ�����ֳ�Ա���ı�˳���������Ĳ���

 "pwwkew"
 �Ӵ�"pww"
 ������"pkw"
*/


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
583. �����ַ�����ɾ������
�Ѷ��е�96
������������ word1 �� word2��
�ҵ�ʹ�� word1 �� word2 ��ͬ�������С������
ÿ������ɾ������һ���ַ����е�һ���ַ���

ʾ����
����: "sea", "eat"
���: 2
����: ��һ����"sea"��Ϊ"ea"���ڶ�����"eat"��Ϊ"ea"

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
718. ��ظ�������
�Ѷ��е�159
�������������� A �� B ���������������й����ġ��������������ĳ��ȡ�
ʾ�� 1:
����:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
���: 3
����:
������Ĺ����������� [3, 2, 1]��
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
5. ������Ӵ�
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
712. �����ַ�������СASCIIɾ����
�Ѷ��е�93
���������ַ���s1, s2���ҵ�ʹ�����ַ����������ɾ��
�ַ���ASCIIֵ����С�͡�
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

/*
1483. ���ڵ�ĵ� K ������
�Ѷ�����35
����һ������������ n ���ڵ㣬���� 0 �� n-1 ��š����Ը��ڵ��������ʽ���������� parent[i] �ǽڵ� i �ĸ��ڵ㡣���ĸ��ڵ��Ǳ��Ϊ 0 �Ľڵ㡣
������Ʋ�ʵ�� getKthAncestor(int node, int k) �������������ؽڵ� node �ĵ� k �����Ƚڵ㡣������������������Ƚڵ㣬���� -1 ��
���ڵ�ĵ� k �����Ƚڵ��ǴӸýڵ㵽���ڵ�·���ϵĵ� k ���ڵ㡣

*/
typedef struct {

} TreeAncestor;

    int dp[50010][20];//dp[i][j]��ʾ ����i�ڵ���˵,���ĵ�2^j��������ĳ���ڵ�
                                      //dp[i][j] = dp[dp[i][j - 1]][j - 1] �൱�� ��Ҫ����2 ^ j �����ȣ����ȵ�2 ^ (j - 1)������
                                      //�ٵ����ȵ�2 ^ (j - 1)�����ȣ��ٸ����ӣ���Ҫ��dp[i][3] ������dp[i][2] ����dp[i][2]�Ļ�������
                                      //�� 2 ^ 2 ��һ������8��,�� 2 ^ 3 �η�һ��


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
1186. ɾ��һ�εõ�����������
�Ѷ��е�46
����һ���������飬��������ĳ�� �ǿ� �����飨����Ԫ�أ���ִ��һ�ο�ѡ��ɾ�����������ܵõ������Ԫ���ܺ͡�
���仰˵������Դ�ԭ������ѡ��һ�������飬�����Ծ���Ҫ��Ҫ����ɾ��һ��Ԫ�أ�ֻ��ɾһ��Ŷ������ɾ����������������Ӧ����һ��Ԫ�أ�Ȼ��������飨ʣ�£���Ԫ���ܺ�������������֮�����ġ�
ע�⣬ɾ��һ��Ԫ�غ������� ����Ϊ�ա�
�뿴ʾ����
ʾ�� 1��
���룺arr = [1,-2,0,3]
�����4
���ͣ����ǿ���ѡ�� [1, -2, 0, 3]��Ȼ��ɾ�� -2�������õ� [1, 0, 3]�������

*/
int maximumSum(int* arr, int arrSize)
{
        int N = arrSize;

        // �߽�������ֱ���жϷ���
        if (N == 1) {
            return arr[0];
        }

        int dp1[N]; // dp1[i]������arr[i]Ϊ��β����������������
        int dp2[N]; // dp2[i]������arr[i]Ϊ��β�Ĳ���ɾ����һ��Ԫ�أ�������arr[i]�Լ��������������������

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
        dp2[1] = fmax(arr[0], arr[1]);  // ��Ϊɾ��Ԫ�غ���Ϊ�գ�������arr[1]Ϊ��β��ֻ��һ�������arr[0] arr[1]��Ҫôɾ��arr[0]��Ҫôɾ��arr[1]

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

        // ������arr[i]Ϊ��β������ɾ���Ͳ�ɾ��Ԫ�ص�������ҳ����ֵ��
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
������ 16.16. ��������
����һ���������飬��дһ���������ҳ�����m��n��ֻҪ��
��������[m,n]��Ԫ���ź������������������ġ�ע�⣺
n-m������С��Ҳ����˵���ҳ�����������������С�
��������ֵΪ[m,n]����������������m��n������������������
��ģ����뷵��[-1,-1]��

ʾ����

���룺 [1,2,4,7,10,11,7,12,6,7,16,18,19]
����� [3,9]
��ʾ��

0 <= len(array) <= 1000000
*/

/*
array��ĳ������������ǰ��λ�ò��䣬������������������
1. ǰ��û�б��Լ�С�����֣�
2.����û�б��Լ�������֡�
����dp���������������Ϣ�� dp[i]=true��ʾarray[i]������ǰ��λ��
���䣬dp[i]=false����ʾ������ǰ��array[i]λ�÷����仯��
��ǰ���ɨ�����飬���ϸ���ɨ�赽�����ֵ���ȿ����ж�
��ǰarray[i]֮ǰ�Ƿ���ڱ��Լ�С�����֣����������dp[i]��Ϊ
false;
�Ӻ���ǰɨ�����飬���ϸ���ɨ�赽����Сֵ���ȿ����ж�
��ǰarray[i]֮���Ƿ���ڱ��Լ�С�����֣����������dp[i]��Ϊ
false;
�ҵ�dp[i]Ϊfalse����С������i����ΪҪ���ص�����
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
174. ���³���Ϸ
һЩ��ħץס�˹�����P�������������˵��³ǵ����½ǡ�
���³����� M x N ��������ɵĶ�ά��������Ӣ�µ���ʿ
��K����������������Ͻǵķ���������봩�����³�
��ͨ���Կ���ħ�����ȹ�����
��ʿ�ĳ�ʼ��������Ϊһ����������������Ľ�������
��ĳһʱ�̽��� 0 �����£���������������
��Щ�����ɶ�ħ�����������ʿ�ڽ�����Щ����ʱ��ʧ
ȥ�������������������ֵΪ�����������ʾ��ʿ����ʧ
��������������������Ҫô�ǿյģ��������ֵΪ 0����Ҫ
ô����������ʿ����������ħ������
�������ֵΪ�����������ʾ��ʿ�����ӽ�����������
Ϊ�˾��쵽�﹫������ʿ����ÿ��ֻ���һ������ƶ�һ����
��дһ������������ȷ����ʿ�ܹ����ȵ�������������
��ʼ����������
���磬���ǵ����²��ֵĵ��³ǣ������ʿ��ѭ���·��
�� -> �� -> �� -> �£�����ʿ�ĳ�ʼ������������Ϊ 7��
*/
int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize)
{
    if (dungeon == NULL || dungeonSize == 0 || *dungeonColSize == 0) {
        return 0;
    }
    int row = dungeonSize;
    int col = *dungeonColSize;
   int dp[row][col];
    // �������һ��ֵ��
  	dp[row - 1][col -1] = fmax(0, -dungeon[row - 1][col - 1]);

    // �������һ�е�ֵ
  	for (int i = row - 2; i >= 0; --i) {
        int needMin = dp[i + 1][col - 1] - dungeon[i][col - 1];
        dp[i][col -1] = fmax(0, needMin);
    }

    // �������һ�е�ֵ
  	for (int i = col - 2; i >= 0; --i) {
        int needMin = dp[row - 1][i + 1] - dungeon[row - 1][i];
        dp[row - 1][i] = fmax(0, needMin);
    }

    for (int i = row - 2; i >= 0; --i) {
        for (int j = col - 2; j >= 0; --j) {
			// ���ұߺ��±�ѡ��һ����Сֵ��Ȼ���ȥ��ǰ�� dungeon ֵ
            int needMin = fmin(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
            dp[i][j] = fmax(0, needMin);
        }
    }
    return dp[0][0] + 1;


}

/*97. �����ַ���*/
/*
��̬�滮
״̬����
��dp[i][j]Ϊ�ַ��Ӵ�s1[0, i),s2[0, j)�ܷ����s3[0, i+j)��
ps: s1[0, i) = s1.substring(0, i),������i��

�����ַ�����״̬dp[i]��˵��ͨ��Ҫ���������Ӵ��ĳ���[0, n]����˶���dp[n+1],n���ַ���s�ĳ��ȣ�ͬ����άҲһ����

״̬ת��
����dp[i][j]��״̬��˵��Ҫ�����s3[0,i+j)����s3[0, i+j)���һ���ַ�s3[i+j-1]Ҫô����s1[i-1], Ҫô����s2[j-1],��ˣ�״̬ת�ƣ�

��s1[i-1]==s3[i+j-1]��
dp[i][j] = dp[i-1][j],i > 0
dp[i][j]=dp[i?1][j],i>0

��s2[j-1]==s3[i+j-1]��
dp[i][j] = dp[i][j-1],j >0
dp[i][j]=dp[i][j?1],j>0

״̬��ʼ����dp[0][0] = true����ʾ�������ַ����ܹ����һ�����ַ�����

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
546. �Ƴ�����
����һЩ��ͬ��ɫ�ĺ��ӣ����ӵ���ɫ�����ֱ�ʾ������ͬ�����ֱ�ʾ��ͬ����ɫ��
�㽫���������ֲ���ȥȥ�����ӣ�ֱ�����еĺ��Ӷ�ȥ��Ϊֹ��ÿһ��������Ƴ�������ͬ��ɫ������ k �����ӣ�k >= 1��������һ��֮���㽫�õ� k*k �����֡�
���㽫���к��Ӷ�ȥ��֮�������ܻ�õ������ֺ͡�



ʾ����

���룺boxes = [1,3,2,2,2,3,4,3,1]
�����23
���ͣ�
[1, 3, 2, 2, 2, 3, 4, 3, 1]
----> [1, 3, 3, 4, 3, 1] (3*3=9 ��)
----> [1, 3, 3, 3, 1] (1*1=1 ��)
----> [1, 1] (3*3=9 ��)
----> [] (2*2=4 ��)
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
664. ��ֵĴ�ӡ��
��̨��ֵĴ�ӡ����������������Ҫ��

��ӡ��ÿ��ֻ�ܴ�ӡͬһ���ַ����С�
ÿ�ο�����������ʼ�ͽ���λ�ô�ӡ���ַ������һḲ�ǵ�ԭ�����е��ַ���
����һ��ֻ����СдӢ����ĸ���ַ�������������Ǽ��������ӡ����ӡ����Ҫ�����ٴ�����

ʾ�� 1:

����: "aaabbb"
���: 2
����: ���ȴ�ӡ "aaa" Ȼ���ӡ "bbb"��
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

//���㷨˼·������dp������ķ���dpģ�ͣ��ص��������⣬���и����벿�ֵĴ���������
//          dp[i][j]��ʾ��s[i]��s[j]�Ĵ�ӡ������dp[i][j]������k����i~j�е�����s[i] == s[k]��k��ֽ�
//          ����s[i]��s[k]��һ�δ�ӡ���
// 1.��Χ��С����
// 2.��s[i] == s[k]������ֽ�Ϊ�����֣��ֱ������������
// 3.�����и���������֣�dp[i][k] = dp[i][k-1]�������⣩��dp[k+1][j]�Ѿ�����������⣩
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
689. �������ص������������
�������� nums ����������ɣ��ҵ����������ص�������������͡�

ÿ��������ĳ���Ϊk������Ҫʹ��3*k����ĺ���󻯡�

����ÿ��������ʼ�������б��������� 0 ��ʼ��������ж������������ֵ�����С��һ����

ʾ��:

����: [1,2,1,2,6,7,5,1], 2
���: [0, 3, 5]
����: ������ [1, 2], [2, 6], [7, 5] ��Ӧ����ʼ����Ϊ [0, 3, 5]��
����Ҳ����ȡ [2, 1], ���ǽ�� [1, 3, 5] ���ֵ����ϸ���
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
            // ���������ǰ���ֵ�k�����ֵĺͣ������飬�ض�����
            for (int r = 0; r < k; r++) {
                sum += nums[j - r];
            }
            // ����һ���ʱ����Ҫ��ά�ۼ�
            if (i > 0) {
                sum += maxSum[i - 1][j - k];
            }
            if (sum <= maxSum[i][j - 1]) {
                // ���������鲻����ǰ����
                for (int s = 0; s <= i; s++) {
                    dp[i][j][s] = dp[i][j - 1][s];
                }
                maxSum[i][j] = maxSum[i][j - 1];
            } else {
                int s;
                // ��ǰ���������󣬴���֮ǰ��������
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
������ 17.13. �ָ��ո�
Ŷ�������㲻С�İ�һ����ƪ�����еĿո񡢱�㶼ɾ���ˣ����Ҵ�дҲŪ����Сд�������"I reset the computer. It still didn��t boot!"�Ѿ������"iresetthecomputeritstilldidntboot"���ڴ��������źʹ�Сд֮ǰ������Ȱ����ϳɴ����Ȼ�ˣ�����һ�����Ĵʵ�dictionary����������Щ��û�ڴʵ������������sentence��ʾ�����һ���㷨�������¶Ͽ���Ҫ��δʶ����ַ����٣�����δʶ����ַ�����

ע�⣺�������ԭ�������Ķ���ֻ�践��δʶ����ַ���



ʾ����

���룺
dictionary = ["looked","just","like","her","brother"]
sentence = "jesslookedjustliketimherbrother"
����� 7
���ͣ� �Ͼ��Ϊ"jess looked
*/