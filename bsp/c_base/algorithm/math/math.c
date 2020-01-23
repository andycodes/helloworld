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

/*
这里有 n 个航班，它们分别从 1 到 n 进行编号。

我们这儿有一份航班预订表，表中第 i 条预订记录 bookings[i] = [i, j, k] 意味着我们在从 i 到 j 的每个航班上预订了 k 个座位。

请你返回一个长度为 n 的数组 answer，按航班编号顺序返回每个航班上预订的座位数。



示例：

输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
输出：[10,55,45,25,25]


设a[i]表示第i个航班预订的座位数。

定义一个差分数组tag[]，tag[i]表示第i个航班与第i-1个航班预订座位的差，即tag[i] = a[i] - a[i - 1]。

这样，我们每次扫描到[i, j, k]，就只需要将tag[i]增加k，tag[j + 1]减少k即可。

最后，计算a[i] = a[i - 1] + tag[i]，返回a即可。

*/
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize){
	int *diff = malloc(20001 * sizeof(int));
	memset((void*)diff,0,20001*sizeof(int));

	for(int i = 0; i < bookingsSize; i++){
		diff[bookings[i][0]-1] += bookings[i][2];
		diff[bookings[i][1]]   -= bookings[i][2];
	}

	for(int i = 1; i < n; i++) {
		diff[i] += diff[i -1];
	}

	*returnSize = n;
	return diff;
}

/*
1010. 总持续时间可被 60 整除的歌曲
在歌曲列表中，第 i 首歌曲的持续时间为 time[i] 秒。

返回其总持续时间（以秒为单位）可被 60 整除的歌曲对的数量。形式上，我们希望索引的数字  i < j 且有 (time[i] + time[j]) % 60 == 0。



示例 1：

输入：[30,20,150,100,40]
输出：3
解释：这三对的总持续时间可被 60 整数：
(time[0] = 30, time[2] = 150): 总持续时间 180
(time[1] = 20, time[3] = 100): 总持续时间 120
(time[1] = 20, time[4] = 40): 总持续时间 60

*/

int numPairsDivisibleBy60(int* time, int timeSize){
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

