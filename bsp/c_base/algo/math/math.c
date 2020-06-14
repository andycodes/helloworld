/*判断两个数是否异号*/
int x = -1, y = 2;
bool f = ((x ^ y) < 0); // true

int x = 3, y = 2;
bool f = ((x ^ y) < 0); // false

/*绝对值*/
int abs(int);
/* sqrt() 用来求给定值的平方根 */
double sqrt(double x);
/*pow() 函数用来求 x 的 y 次幂（次方）*/
double pow(double x, double y);

void num(void)
{
	if (isdigit(s[i])) {
		num = num * 10 + s[i] - '0';
	}
}

/*
1010. 总持续时间可被 60 整除的歌曲
在歌曲列表中，第 i 首歌曲的持续时间为 time[i] 秒。
返回其总持续时间（以秒为单位）可被 60 整除的歌曲对的数量。
形式上，我们希望索引的数字  i < j 且有 (time[i] + time[j]) % 60 == 0。
1 <= time[i] <= 500

示例 1：
输入：[30,20,150,100,40]
输出：3
解释：这三对的总持续时间可被 60 整数：
(time[0] = 30, time[2] = 150): 总持续时间 180
(time[1] = 20, time[3] = 100): 总持续时间 120
(time[1] = 20, time[4] = 40): 总持续时间 60

1)首先所有对象%60
2)组合的可能性
*/
int numPairsDivisibleBy60(int* time, int timeSize)
{
	int result = 0;
	int mod[60];

	memset((void*)mod, 0, sizeof(mod));
	for(int i = 0; i < timeSize; i++) {
		mod[time[i] % 60]++;
	}

	for (int i = 1; i < 30; i++) {
		result += mod[i] * mod[60 - i];
	}

	result += (mod[0] * (mod[0] - 1) + mod[30] * (mod[30] - 1)) / 2;

	return result;
}

/*
数学定理:

1)
如果一个数组和大于0
令其作为环形，那么一定可以找到一个起点，
从此起点开始转一圈（遍历），连续和大于零
*/

/*
60. 第k个排列
给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。
按大小顺序列出所有排列情况，并一一标记，
当 n = 3 时, 所有排列如下：
"123"
"132"
"213"
"231"
"312"
"321"
给定 n 和 k，返回第 k 个排列。
说明：
给定 n 的范围是 [1, 9]。
给定 k 的范围是[1,  n!]。
示例 1:
输入: n = 3, k = 3
输出: "213"
*/

/*
例如： n = 6, k = 373
初始化数组 nums = [1, 2, 3, 4, 5, 6];
首先应该明白，以 1 开头的全排列有 5! 个，
以 2 开头的全排列有 5! 个 ……
共 5! * 6 = 6! 个；
故 k = 373 时，
全排列的第一个数字应该是 nums[ k / 5! ] = 4 ;
数组删除 4, 此时 nums = [1, 2, 3, 5, 6]; k %= 5! = 12 ;
接下来就是在 nums 中找第 12 个全排列，重复 1，2 步即可 。
*/

//阶乘(n!)
int factorial(int n)
{
	int num = 1;
	while (n > 0)
		num *= n--;
	return num;
}


void deleteItem(int *nums, int pos, int moveSize)
{
	while (pos < moveSize - 1)
		nums[pos++] = nums[pos + 1];
}

char *getPermutation(int n, int k)
{
	int i, j = 0, nums[n], factor;
	char *res = (char *)calloc(10, sizeof(char));

	for (i = 0; i < n; i++)  //初始化一个 [1,2,3,……,n] 数组
		nums[i] = i + 1;
	for (i = 0, k--; i < n; i++) {  //k要先减去1   给定 k 的范围是[1,  n!]。
		factor = factorial(n - i - 1);
		res[j++] = nums[k  / factor] + '0';
		deleteItem(nums, k / factor, n - i);  //取出一个元素
		k %= factor;
	}
	return res;
}

/*
LCP 03. 机器人大冒险
力扣团队买了一个可编程机器人，
机器人初始位置在原点(0, 0)。小伙伴事先给机器人输入一串指
令command，机器人就会无限循环这条指令的步骤进行移动。
指令有两种：
U: 向y轴正方向移动一格
R: 向x轴正方向移动一格。
不幸的是，在 xy 平面上还有一些障碍物，
他们的坐标用obstacles表示。机器人一旦碰到障碍物就会被损毁。
给定终点坐标(x, y)，返回机器人能否完好地到达终点。
如果能，返回true；否则返回false�
示例 1：

输入：command = "URR", obstacles = [], x = 3, y = 2
输出：true
解释：U(0, 1) -> R(1, 1) -> R(2, 1) -> U(2, 2) -> R(3, 2)。
示例 2：

输入：command = "URR", obstacles = [[2, 2]], x = 3, y = 2
输出：false
解释：机器人在到达终点前会碰到(2, 2)的障碍物。

*/
void lower(int *x, int *y, int d1, int d2)
{
	int p1 = *x /d1;
	int p2 = *y /d2;
	int min = p1 > p2 ? p2 : p1;
	*x = *x - min * d1;
	*y = *y - min * d2;
}

bool isOk(char * command, int x, int y)
{
	int i=0;
	while(x>=0 && y>=0) {
		if(x==0&&y==0)
			return true;
		if(*(command+i)=='U') {
			y--;
		}else  {
			x--;
		}
		i++;
	}

	if(x==0&&y==0)
	return true;
		else
	return false;
}

bool robot(char * command, int** obstacles, int obstaclesSize, int* obstaclesColSize, int x, int y)
{
	int nx = x, ny = y;
	int numU=0,numR=0;

	for(int i=0; i<strlen(command); i++) {
		if(*(command+i)=='U') {
			numU++;
		}else{
			numR++;
		}
	}

	lower(&nx,&ny,numR,numU);
	if(!isOk(command,nx,ny))
		return false;

	for(int i=0; i<obstaclesSize; i++) {
		if(obstacles[i][0]>x||obstacles[i][1]>y)
			continue;
		nx=obstacles[i][0];
		ny=obstacles[i][1];

		lower(&nx,&ny,numR,numU);
		if(isOk(command,nx,ny))
			return false;
	}

	return true;
}

/*
313. 超级丑数
难度中等80
编写一段程序来查找第 n 个超级丑数。
超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。
示例:
输入: n = 12, primes = [2,7,13,19]
输出: 32
解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
说明:
"	1 是任何给定 primes 的超级丑数。
"	 给定 primes 中的数字以升序排列。
"	0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000 。
*/

/*
 * @lc app=leetcode.cn id=313 lang=c
 *
 * [313] 超级丑数
 */

// @lc code=start

//【算法思路】数学。丑数的构造方法。
int nthSuperUglyNumber(int n, int* primes, int primesSize){
    if(n == 1)
    {
        return 1;
    }

    int *res = (int *)calloc(n, sizeof(int));
    int rsize = 0;

    int *pids = (int *)calloc(primesSize, sizeof(int));

    res[rsize++] = 1;

    while(rsize < n)
    {
        // 选择最小的(素数*res[pid])，更新其pid
        int min = INT_MAX;
        int id = 0;

        for(int i = 0; i < primesSize; i++)
        {
            int tmin = primes[i] * res[ pids[i] ];

            if(tmin < min)
            {
                min = tmin;
                id = i;
            }
            // 去除重复
            else if(tmin == min)
            {
                pids[i]++;
            }
        }

        res[rsize++] = min;
        pids[id]++;
    }

    return res[n - 1];
}

/*
1371. 每个元音包含偶数次的最长子字符串
难度中等245
给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。

示例 1：
输入：s = "eleetminicoworoep"
输出：13
解释：最长子字符串是 "leetminicowor" ，它包含 e，i，o 各 2 个，以及 0 个 a，u 。
示例 2：
输入：s = "leetcodeisgreat"
输出：5
解释：最长子字符串是 "leetc" ，其中包含 2 个 e 。
示例 3：
输入：s = "bcbcbc"
输出：6
解释：这个示例中，字符串 "bcbcbc" 本身就是最长的，因为所有的元音 a，e，i，o，u 都出
*/
//00000 ~ 11111 一共2^5，32中状态，0表示出现偶数，1表示出现奇数
int findTheLongestSubstring(char * s)
{
	int n = strlen(s);
	int pos[32] = {-1};
	int status = 0;
	int ans = 0;

	for (int i = 0; i < 32; i++) {
		pos[i] = -1;
	}

	pos[0] = 0;

	for (int i = 0; i < n; i ++) {
            if (s[i] == 'a') {
                status ^= 1<<0;
            } else if (s[i] == 'e') {
                status ^= 1<<1;
            } else if (s[i] == 'i') {
                status ^= 1<<2;
            } else if (s[i] == 'o') {
                status ^= 1<<3;
            } else if (s[i] == 'u') {
                status ^= 1<<4;
            }
            if (pos[status] != -1) {
                ans = fmax(ans, i + 1 - pos[status]);
            } else {
                pos[status] = i + 1;
            }
	}

        return ans;
}

/*
1296. 划分数组为连续数字的集合
难度中等25
给你一个整数数组 nums 和一个正整数 k，请你判断是否可以把这个数组划分成一些由 k 个连续数字组成的集合。
如果可以，请返回 True；否则，返回 False。

示例 1：
输入：nums = [1,2,3,3,4,4,5,6], k = 4
输出：true
解释：数组可以分成 [1,2,3,4] 和 [3,4,5,6]。

*/
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
bool isPossibleDivide(int* nums, int numsSize, int k){
    int min, cnt, j;
    if (numsSize % k != 0) {
        return false;
    }
    qsort(nums, numsSize, sizeof(int), cmp);
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            min = nums[i];
            cnt = 0;
            for (j = i; (j < numsSize) && (cnt < k); j++) {
                if (nums[j] == min){
                    cnt++;
                    min++;
                    nums[j] = 0;
                }
            }
            if (cnt < k) {
                return false;
            }
        }
    }
    return true;
}

/*
442. 数组中重复的数据
难度中等205
给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次。
找到所有出现两次的元素。
你可以不用到任何额外空间并在O(n)时间复杂度内解决这个问题吗？
示例：
输入:
[4,3,2,7,8,2,3,1]

输出:
[2,3]

*/
int const cmp_int(const void *a, const void *b)
{
	return *((int *)a) - *((int *)b);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDuplicates(int* nums, int numsSize, int* returnSize)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	int *res = (int *)calloc(numsSize, sizeof(int));
	*returnSize = 0;
	if (numsSize <= 1)
		return res;

	for(int i = 0; i < numsSize - 1; i++) {
		if (nums[i] == nums[i + 1]) {
			res[*returnSize] = nums[i];
			(*returnSize)++;
			i++;
		}
	}

	return res;
}