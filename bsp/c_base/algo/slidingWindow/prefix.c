/*
prefix
子数组和
前序和prefixSum  (连续子和)
任意区间数组和均可以使用前缀和来优化
子数组A(i,j]的和为sum[j] - sum[i]
第i个元素的前缀和 = 前i-1个元素之和。
首元素没有前缀，规定为0

int prefix[arrSize + 1];
prefix[0] = 0;
for (int i = 1; i <= arrSize; i++) {
	prefix[i] = prefix[i - 1] + arr[i - 1];
}

*/

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

/*
暴力超时
整除:
(prefix[j] - prefix[i]) % K == 0
等价
prefix[j] %k == prefix[i] % k
 map[i] * (map[i] - 1) / 2;
*/

int subarraysDivByK(int* A, int ASize, int K)
{
	int prefix[ASize + 1];
	prefix[0] = 0;
	for (int i = 1; i <= ASize; i++) {
		prefix[i] = prefix[i - 1] + A[i - 1];
	}

	int cnt = 0;
	for (int i = 0; i < ASize; i++) {
		for (int j = i + 1; j <= ASize; j++) {
			if ((prefix[j] - prefix[i]) % K == 0) {
				cnt++;
			}
		}
	}

	return cnt;
}

int subarraysDivByK(int* A, int ASize, int K)
{
	if (K == 0 || ASize == 0) {
		return 0;
	}

	int prefix[ASize+1];
	prefix[0]=0;
	for(int i = 1; i <= ASize; i++) {
		prefix[i] = prefix[i - 1]+A[i - 1];
	}

	int map[K];
	memset(map,0,K*sizeof(int));
	for(int i = 0;i<ASize+1;i++){
		map[(prefix[i]%K +K)%K]++;
	}

	int count=0;
	for(int i=0;i<K;i++){
		count+=(map[i]*(map[i]-1))/2;
	}
	return count;
}


/*
42. 接雨水
难度困难1499
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按
此排列的柱子，下雨之后能接多少雨水。

上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，
可以接 6 个单位的雨水（蓝色部分表示雨水）。
感谢 Marcos 贡献此图。
示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/
int trap(int* height, int heightSize)
{
	if (height == NULL ||heightSize <= 0)
		return 0;

	int right[heightSize];

	//right max
	right[heightSize - 1] = height[heightSize - 1];
	for (int i = heightSize - 2; i >= 0; i--) {
		right[i] = fmax(right[i + 1], height[i + 1]); //right max
	}

	int sum = 0;
	int leftmax = height[0];
	for (int i = 1; i < heightSize; i++) {
		leftmax = fmax(leftmax, height[i - 1]);
		int min = fmin(leftmax, right[i]);
		sum += min > height[i] ? min - height[i] : 0;
	}

	return sum;
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



