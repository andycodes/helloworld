
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