
/*
1109. 航班预订统计
这里有 n 个航班，它们分别从 1 到 n 进行编号。
我们这儿有一份航班预订表，
表中第 i 条预订记录 bookings[i] = [i, j, k] 意味着我们在从 i 到 j 的
每个航班上预订了 k 个座位。
请你返回一个长度为 n 的数组 answer，
按航班编号顺序返回每个航班上预订的座位数。
示例：

输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
输出：[10,55,45,25,25]


设a[i]表示第i个航班预订的座位数。
定义一个差分数组diff[]，
diff[i]表示第i个航班与第i-1个航班预订座位的差，
即diff[i] = a[i] - a[i - 1]。
这样，我们每次扫描到[i, j, k]，
就只需要将diff[i]增加k，diff[j + 1]减少k即可。
最后，计算a[i] = a[i - 1] + diff[i]，返回a即可。
*/
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize,
int n, int* returnSize){
	int *diff = malloc(20001 * sizeof(int));
	memset((void*)diff,0,20001*sizeof(int));

	for(int i = 0; i < bookingsSize; i++){
		diff[bookings[i][0]-1] += bookings[i][2]; //等差开始加上等差值
		diff[bookings[i][1]]   -= bookings[i][2]; //等差结束 减掉等差值
	}

	for(int i = 1; i < n; i++) {
		diff[i] += diff[i -1];//推导原始值
	}

	*returnSize = n;
	return diff;
}

/*
1343. 大小为 K 且平均值大于等于阈值的子数组数目
给你一个整数数组 arr 和两个整数 k 和 threshold 。

请你返回长度为 k 且平均值大于等于 threshold 的子数组数目。



示例 1：

输入：arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
输出：3
解释：子数组 [2,5,5],[5,5,5] 和 [5,5,8] 的平均值分别为 4，5 和 6 。其他长度为 3 的子数组的平均值都小于 4 （threshold 的值)。
*/
int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
    int preSum[arrSize + 1];
    memset(preSum,0,sizeof(int) * (arrSize + 1));
    preSum[0] = arr[0];
    for (int i = 1; i <= arrSize; i++) {
        preSum[i] += arr[i - 1] + preSum[i - 1];
    }
    int retNum = 0;
    for(int i = k ; i <= arrSize; i++) {
        int sum = preSum[i] - preSum[i - k];
        if(sum / k >= threshold) {
            retNum++;
        }
    }
    return retNum;
}

/*
974. 和可被 K 整除的子数组
难度中等170
给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。

示例：
输入：A = [4,5,0,-2,-3,1], K = 5
输出：7
解释：
有 7 个子数组满足其元素之和可被 K = 5 整除：
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

*/
int subarraysDivByK(int* A, int ASize, int K){
    int hash[K];
    memset(hash,0,sizeof(hash));
    for(int i=1;i<ASize;i++)//前缀和
    {
        A[i]=A[i-1]+A[i];
    }
    for(int i=0;i<ASize;i++)//余数为键的哈希表
    {
       hash[(A[i]%K+K)%K]++;//消除负数
    }
    int sum=0;
    for(int i=0;i<K;i++)//统计相同余数满足要求的数目
    {
        sum+=hash[i]*(hash[i]-1)/2;
    }
    return sum+hash[0];//加上单个满足余数为零的数目
}

int subarraysDivByK(int* A, int ASize, int K)
{
        int map[K];
		memset(map, 0, sizeof(map));
		map[0] = 1;

        int PreSum=0;
        int Count=0;
        for(int i=0;i<ASize;i++){
            PreSum=PreSum+A[i];//当前项的前缀和 = 上一项的前缀和 + 当前项
            int remain=PreSum%K;//当前项前缀和%K的结果

            //%K结果为负数的情况需要考虑
            if(remain<0) remain=remain+K;

            if(map[remain]){
                Count+=map[remain];//余数remain之前存在，则和现在的当前项可以有map[remain]种组合可能
                map[remain]++;//余数remain之前出现的次数需要更新
            }
            else{
                map[remain]=1;//余数remain之前不存在
            }
        }

        return Count;

}

int subarraysDivByK(int* A, int ASize, int K){
    if (K == 0 || ASize == 0) {
        return 0;
    }
    int ans=0;
    int *presum=(int*)malloc(sizeof(int)*(ASize+1));
    presum[0]=0;
    for(int i=0;i<ASize;i++){
        presum[i+1]=presum[i]+A[i];
    }
    int *arr=(int*)malloc(sizeof(int)*K);
    memset(arr,0,K*sizeof(int));
    for(int i=0;i<ASize+1;i++){
        arr[(presum[i]%K +K)%K]++;
    }
    int count=0;
    for(int i=0;i<K;i++){
        count+=(arr[i]*(arr[i]-1))/2;

    }
    return count;
}

int subarraysDivByK(int* A, int ASize, int K){
    if (K == 0 || ASize == 0 || A == NULL) {
        return 0;
    }

    int *map = (int *)calloc(K, sizeof(int));
    map[0] = 1;
    int sum = 0;
    int count = 0;

    for (int i = 0; i < ASize; i++) {
        sum += A[i];
        int key = (sum % K + K) % K;
        count += map[key];
        map[key]++;
    }

    free(map);
    return count;
}

/*
42. 接雨水
难度困难1499
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。
示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6

*/
int trap(int* height, int heightSize)
{
    int ans = 0;
    int size = heightSize;
    for (int i = 1; i < size - 1; i++) {
        int max_left = 0, max_right = 0;
        for (int j = i; j >= 0; j--) { //Search the left part for max bar size
            max_left = fmax(max_left, height[j]);
        }
        for (int j = i; j < size; j++) { //Search the right part for max bar size
            max_right = fmax(max_right, height[j]);
        }
        ans += fmin(max_left, max_right) - height[i];
    }
    return ans;
}

int trap(int* height, int heightSize)
{
	if(height == NULL || heightSize <= 0)
		return 0;
	int ans = 0;
	int size = heightSize;
	int left_max[size];
	int right_max[size];
    left_max[0] = height[0];
    for (int i = 1; i < size; i++) {
        left_max[i] = fmax(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = fmax(height[i], right_max[i + 1]);
    }
    for (int i = 1; i < size - 1; i++) {
        ans += fmin(left_max[i], right_max[i]) - height[i];
    }
    return ans;

}

int trap(int* height, int heightSize)
{
	if (height == NULL || heightSize <= 0)
		return 0;

	int ans = 0, current = 0;
	int stackSize = fmax(heightSize, 1024);
	int stack[stackSize];
	int top = -1;

	while (current < heightSize) {
		while (top > -1 && height[current] > height[stack[top]]) {
			int low = stack[top--];
			if (top < 0)
				break;
			int distance = current - stack[top] - 1;
			int bounded_height = fmin(height[current], height[stack[top]]) - height[low];
			ans += distance * bounded_height;
		}

		stack[++top] = current++;
	}

	return ans;
}

int trap(int* height, int heightSize)
{
    int left = 0, right = heightSize - 1;
    int ans = 0;
    int left_max = 0, right_max = 0;

    while (left < right) {
        if (height[left] < height[right]) {
		if (height[left] >= left_max)
			left_max = height[left];
		else
			ans += (left_max - height[left]);

            ++left;
        } else {
            if (height[right] >= right_max) {
			right_max = height[right];
		} else
			ans += (right_max - height[right]);

            --right;
        }
    }

    return ans;
}

/*前序和prefixSum  (连续子和)
任意区间数组和均可以使用前缀和来优化
子数组A(i,j]的和为sum[j] - sum[i]
第i个元素的前缀和 = 前i-1个元素之和。
首元素没有前缀，规定为0。
*/

/*
560. 和为K的子数组
给定一个整数数组和一个整数 k，你需要找到该数组中和为
k 的连续的子数组的个数。

示例 1 :

输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
说明 :

数组的长度为 [1, 20,000]。
数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。
通过次数25,598提交次数57,201
*/
int subarraySum(int* nums, int numsSize, int k)
{
	int cnt = 0;
	int prefixSum[numsSize + 1];
	prefixSum[0] = 0;
	for (int i = 1; i <= numsSize; i++) {
		prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
	}

	for (int start = 0; start < numsSize; start++) {
		for (int end = start + 1; end <= numsSize; end++) {
			if (prefixSum[end] - prefixSum[start] == k)
				cnt++;
		}
	}

	return cnt;
}


/*
1423. 可获得的最大点数
几张卡牌 排成一行，每张卡牌都有一个对应的点数。
点数由整数数组 cardPoints 给出。

每次行动，你可以从行的开头或者末尾拿一张卡牌，
最终你必须正好拿 k 张卡牌。

你的点数就是你拿到手中的所有卡牌的点数之和。

给你一个整数数组 cardPoints 和整数 k，请你返回可以获得的
最大点数。



示例 1：

输入：cardPoints = [1,2,3,4,5,6,1], k = 3
输出：12
解释：第一次行动，不管拿哪张牌，你的点数总是 1 。
但是，先拿最右边的卡牌将会最大化你的可获得点数。
最优策略是拿右边的三张牌，最终点数为 1 + 6 + 5 = 12 。
示例 2：

输入：cardPoints = [2,2,2], k = 2
输出：4
解释：无论你拿起哪两张卡牌，可获得的点数总是 4 。
示例 3：

输入：cardPoints = [9,7,7,9,7,7,9], k = 7
输出：55
解释：你必须拿起所有卡牌，可以获得的点数为所有卡牌的点数之和。
示例 4：

输入：cardPoints = [1,1000,1], k = 1
输出：1
解释：你无法拿到中间那张卡牌，所以可以获得的最大点数
为 1 。
示例 5：

输入：cardPoints = [1,79,80,1,1,1,200,1], k = 3
输出：202
*/
int maxScore(int* cardPoints, int cardPointsSize, int k)
{
	int prefixSum[cardPointsSize + 1];
	prefixSum[0] = 0;
	for (int i = 0; i < cardPointsSize; i++) {
		prefixSum[i + 1] = prefixSum[i] + cardPoints[i];
	}

	int max = -1;
	for (int i = 0; i <=  k; i++) {
		max = fmax(max, prefixSum[i] + prefixSum[cardPointsSize] - prefixSum[cardPointsSize - k + i]);
	}

	return max;
}

/*
按题中意思取左取右得最大值，反过来就是求中间连续
子数组得和最小,由于要取 k 张牌，
所以反过来就是在中间找连续的长度为 len(carPoints)-k 的
子数组使其和最小，滑窗将移动 k 次，
不断更新滑窗能得到和的最小值，
最后用输入数组的和减去这个最小值就是结果。
第一排各自代表 index，
第二行代表对应位置的数值,用的是题中第一个范例。
*/
int maxScore(int* cardPoints, int cardPointsSize, int k)
{
	int prefixSum[cardPointsSize + 1];
	prefixSum[0] = 0;
	for (int i = 0; i < cardPointsSize; i++) {
		prefixSum[i + 1] = prefixSum[i] + cardPoints[i];
	}

	int ans = 0x3f3f3f3f;
	int t = cardPointsSize - k;
	for (int j = t;  j <= cardPointsSize; j++) {
		ans = fmin(ans, prefixSum[j] - prefixSum[j - t]);
	}

	return prefixSum[cardPointsSize] - ans;
}