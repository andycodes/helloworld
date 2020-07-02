
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