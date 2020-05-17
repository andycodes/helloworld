
/*
324. 摆动排序 II
给定一个无序的数组 nums，将它重新排列成 nums[0] < nums[1] > nums[2] < nums[3]... 的顺序。

示例 1:

输入: nums = [1, 5, 1, 1, 6, 4]
输出: 一个可能的答案是 [1, 4, 1, 5, 1, 6]

大小数据分2组+小数组降序大数组升序+大小数组互相穿插
*/
void wiggleSort(int* nums, int numsSize){
	if (nums == NULL || numsSize < 2)
		return;

	qsort(nums, numsSize, sizeof(int), cmp_int);

	int big_count = 0, small_count = 0;

	if (numsSize % 2 == 1) {
		big_count = numsSize / 2;
		small_count = numsSize / 2 + 1;
	} else {
		big_count = numsSize / 2;
		small_count = numsSize / 2;
	}

	int big[big_count];
	int small[small_count];

	for (int i = 0; i < small_count; i++) {
		 small[small_count-i-1] = nums[i];
	}

	for(int i = small_count; i < numsSize; i++){
            big[i-small_count] = nums[i];
        }

	int small_index = 0, big_index = big_count-1;
        for(int i=0;i<numsSize;i++){
            if(i % 2 == 0){
                nums[i] = small[small_index];
                small_index++;
            }else{
                nums[i] = big[big_index];
                big_index--;
            }
        }
}

/*
853. 车队
难度中等47
N  辆车沿着一条车道驶向位于 target 英里之外的共同目的地。
每辆车 i 以恒定的速度 speed[i] （英里/小时），从初始位置 position[i] （英里） 沿车道驶向目的地。
一辆车永远不会超过前面的另一辆车，但它可以追上去，并与前车以相同的速度紧接着行驶。
此时，我们会忽略这两辆车之间的距离，也就是说，它们被假定处于相同的位置。
车队 是一些由行驶在相同位置、具有相同速度的车组成的非空集合。注意，一辆车也可以是一个车队。
即便一辆车在目的地才赶上了一个车队，它们仍然会被视作是同一个车队。

会有多少车队到达目的地?

示例：
输入：target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
输出：3
解释：
从 10 和 8 开始的车会组成一个车队，它们在 12 处相遇。
从 0 处开始的车无法追上其它车，所以它自己就是一个车队。
从 5 和 3 开始的车会组成一个车队，它们在 6 处相遇。
请注意，在到达目的地之前没有其它车会遇到这些车队，所以答案是 3。

*/

struct Car {
    int pos;
    int speed;
};

int cmp_struct(const void *a, const void *b)
{
    struct Car *c = (struct Car *)a;
     struct Car *d = (struct Car *)b;

     return c->pos - d->pos;
}

bool isMeet(struct Car  curCar, struct Car  nextCar, int target)
{
        if (curCar.speed <= nextCar.speed) {
            return false;
        }

        double t = (nextCar.pos - curCar.pos) * 1.0 / (curCar.speed - nextCar.speed);
        return curCar.speed * t + curCar.pos <= target;
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize)
{
    if (position == NULL || positionSize <= 0 || speed == NULL || speedSize <= 0) {
        return 0;
    }

    struct Car *car = (struct Car *)calloc(positionSize, sizeof(struct Car *));
    for (int i = 0; i < positionSize; i++) {
        car[i].pos = position[i];
        car[i].speed = speed[i];
    }

    qsort(car, positionSize, sizeof(car[0]), cmp_struct);

    int group = 1;
    struct Car nextCar = car[positionSize - 1];
    for (int i = positionSize - 2; i >= 0; i--) {
        if(!isMeet(car[i], nextCar, target)) {
            group++;
            nextCar = car[i];
        }
    }

    return group;
}

/*
面试题 16.16. 部分排序
给定一个整数数组，编写一个函数，找出索引m和n，只要将索引区间[m,n]的元素排好序，整个数组就是有序的。注意：n-m尽量最小，也就是说，找出符合条件的最短序列。函数返回值为[m,n]，若不存在这样的m和n（例如整个数组是有序的），请返回[-1,-1]。

示例：

输入： [1,2,4,7,10,11,7,12,6,7,16,18,19]
输出： [3,9]
提示：

0 <= len(array) <= 1000000
*/

/*
array中某个数字在排序前后位置不变，必须满足两个条件：
1. 前面没有比自己小的数字；
2.后面没有比自己打的数字。
定义dp保存上面表述的信息， dp[i]=true表示array[i]在排序前后位置不变，dp[i]=false，表示在排序前后array[i]位置发生变化。
从前向后扫描数组，不断更新扫描到的最大值，既可以判断当前array[i]之前是否存在比自己小的数字，如果存在则dp[i]置为false;
从后向前扫描数组，不断更新扫描到的最小值，既可以判断当前array[i]之后是否存在比自己小的数字，如果存在则dp[i]置为false;
找到dp[i]为false的最小和最大的i，即为要返回的数据
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
1366. 通过投票对团队排名
难度中等18
现在有一个特殊的排名系统，依据参赛团队在投票人心中的次序进行排名，每个投票者都需要按从高到低的顺序对参与排名的所有团队进行排位。
排名规则如下：
"	参赛团队的排名次序依照其所获「排位第一」的票的多少决定。如果存在多个团队并列的情况，将继续考虑其「排位第二」的票的数量。以此类推，直到不再存在并列的情况。
"	如果在考虑完所有投票情况后仍然出现并列现象，则根据团队字母的字母顺序进行排名。
给你一个字符串数组 votes 代表全体投票者给出的排位情况，请你根据上述排名规则对所有参赛团队进行排名。
请你返回能表示按排名系统 排序后 的所有团队排名的字符串。

示例 1：
输入：votes = ["ABC","ACB","ABC","ACB","ACB"]
输出："ACB"
解释：A 队获得五票「排位第一」，没有其他队获得「排位第一」，所以 A 队排名第一。
B 队获得两票「排位第二」，三票「排位第三」。
C 队获得三票「排位第二」，两票「排位第三」。
由于 C 队「排位第二」的票数较多，所以 C 队排第二，B 队排第三。
示例 2：
输入：votes = ["WXYZ","XYZW"]
输出："XWYZ"
解释：X 队在并列僵局打破后成为排名第一的团队。X 队和 W 队的「排位第一」票数一样，但是 X 队有一票「排位第二」，而 W 没有获得「排位第二」。
示例 3：
输入：votes = ["ZMNAGUEDSJYLBOPHRQICWFXTVK"]
输出："ZMNAGUEDSJYLBOPHRQICWFXTVK"
解释：只有一个投票者，所以排名完全按照他的意愿。
示例 4：
输入：votes = ["BCA","CAB","CBA","ABC","ACB","BAC"]
输出："ABC"
解释：
A 队获得两票「排位第一」，两票「排位第二」，两票「排位第三」。
B 队获得两票「排位第一」，两票「排位第二」，两票「排位第三」。
C 队获得两票「排位第一」，两票「排位第二」，两票「排位第三」。
完全并列，所以我们需要按照字母升序排名。

*/

struct Sort {
	char c;
	int cnt[26];
	int flag;
};

int cmp_struct(const void *a, const void *b)
{
	struct Sort *c = (struct Sort *)a;
	struct Sort *d = (struct Sort *)b;


	for (int i = 0; i < 26; i++){
		if (c->cnt[i] != d->cnt[i]) {
			return d->cnt[i] - c->cnt[i];
		}
	}

	return c->c - d->c;
}

char * rankTeams(char ** votes, int votesSize)
{
	struct Sort hash[26];
	memset(hash, 0, sizeof(hash));

	for (int i = 0; i < 26; i++) {
		hash[i].c = 'A' + i;
	}

	for(int i = 0; i < votesSize; i++) {
		int j = 0;
		while(votes[i][j] != '\0') {
			hash[votes[i][j] - 'A'].cnt[j]++;
			hash[votes[i][j] - 'A'].flag = 1;
			j++;
		}
	}

	qsort(hash, 26, sizeof(hash[0]), cmp_struct);
	char *ret = (char *)calloc(27, sizeof(char));
	int retCnt = 0;
	for(int i = 0; i < 26; i++) {
		if (hash[i].flag == 1)
			ret[retCnt++] = hash[i].c;
	}

	return ret;
}

/*
面试题45. 把数组排成最小的数
难度中等33
输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

示例 1:
输入: [10,2]
输出: "102"
示例 2:
输入: [3,30,34,5,9]
输出: "3033459"

*/

int cmp_str(const void *a, const void *b)
{
	char e[101] = {{0}};
	char f[101] = {{0}};
	sprintf(e, "%d", *((int *)a));
	sprintf(f, "%d", *((int *)b));

	char c[101] = {{0}};
	char d[101] = {{0}};
	strcat(c, e);
	strcat(c, f);

	strcat(d, f);
	strcat(d, e);

	return strcmp(c, d);
}

char* minNumber(int* nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(int), cmp_str);
	char *ret = (char *)calloc(1024 * 100, sizeof(char));
	for (int i = 0; i < numsSize; i++) {
		char tmpstr[101];
		memset(tmpstr, 0, sizeof(tmpstr));
		sprintf(tmpstr, "%d", nums[i]);
		strcat(ret, tmpstr);
	}

	return ret;
}

/*
31. 下一个排列
难度中等461
实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
必须原地修改，只允许使用额外常数空间。
以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/
/*
1、从后往前遍历，找到第一个nums[i] < nums[i + 1]，的位置i;
2、通过步骤1知道i以后的位置都是单调递减的，因此后后面队列中找到第一个比他大的数，位置为j；
3、交换位置i和位置j上面的两个数；
4、从i+1位置开始，后面的数按照递增排序，最终的结果就是要找到的下一个比当前数大的数；

从右往左找到第 1 个升序排列 a[i]>a[i+1]
在 a[i] 右侧从右至左找到第 1 个大于 a[i] 的数，该数与 a[i] 交换值。(从右至左是因为经过第一步之后从右至左数依次增大，这样可以找到右边比 a[i] 大且接近 a[i] 的数)
交换值后，对 a[i] 右边的值升序排序，保证其顺序值最小。

*/

static int comp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void nextPermutation(int* nums, int numsSize){
    if (NULL == nums || 0 == numsSize)
    {
        return;
    }

    int left = numsSize - 2; // 从倒数第二个开始
    int right;
    int temp = 0;

    while (left >= 0 && nums[left] >= nums[left + 1])
    {
        left--;
    }

    if (-1 == left) // 如果本来就是逆序的
    {
        return qsort(nums, numsSize, sizeof(int), comp);
    }

    for (right = left + 1; right <= numsSize - 1 && nums[left] < nums[right]; right++);

    temp = nums[left];
    nums[left] = nums[right - 1];
    nums[right - 1] = temp;

    qsort(nums + left + 1, numsSize - 1 - left, sizeof(int), comp);
}

/*
539. 最小时间差
给定一个 24 小时制（小时:分钟）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。


示例 1：

输入: ["23:59","00:00"]
输出: 1

备注:

列表中时间数在 2~20000 之间。
*/
int str2min(char * str)
{
	int hour;
	int min;
	sscanf(str, "%d:%d", &hour, &min);
	return hour * 60 + min;
}

int findMinDifference(char ** timePoints, int timePointsSize)
{
	int mins[timePointsSize];
	for (int i = 0; i < timePointsSize; i++) {
		mins[i] = str2min(timePoints[i]);
	}

	qsort(mins, timePointsSize, sizeof(mins[0]), cmp_int);
	int ret = 1440;
	for (int i = 1; i < timePointsSize; i++) {
		ret = fmin(ret, mins[i] - mins[i - 1]);
	}

	ret = fmin(ret, mins[0] + 1440 - mins[timePointsSize - 1]);

	return ret;
}


