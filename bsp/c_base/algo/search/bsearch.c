/*

while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (Check mid) { // 根据nums[mid]来判断搜索左半部分还是右半部分
        lb = mid;
    } else {
        ub = mid;
    }
}
// 视情况处理最后的lb或者ub，此时ub == lb + 1
return nums[lb] >= target ? lb : ub;

二维

int lb = 0; ub = row * col;

while (ub - lb > 1) {
	int mid = (lb + ub) / 2;
	int i = mid / width;
	int j = mid % width;
	if (matrix[i][j] <= target) {
		lb = mid;
	} else {
		ub = mid;
	}
}

return matrix[lb / width][lb % width] == target;
*/
int binary_find_recur(int a[],int key,int start,int end)
{
	int middle=(start+end)/2;
	if(a[middle]==key)
		return middle;
	if(start==middle)
		return -1;
        if(key<a[middle])
		binary_find_recur(a,key,start,middle);
	else
		binary_find_recur(a,key,middle,end);
}

/*bseach用法:
void *bsearch(const void *key, const void *base, size_t nelem, size_t width,
int(*fcmp)(const void *, const *));
参数：
key指向所要查找的元素.
第一个找的关键字。
第二个：要查找的数组。
第三个：指定数组中元素的数目。
第四个：每个元素的长度（以字符为单位）。
第五个：指向比较函数的指针.
*/

/*
1011. 在 D 天内送达包裹的能力
难度中等75
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。

示例 1：
输入：weights = [1,2,3,4,5,6,7,8,9,10], D = 5
输出：15
解释：
船舶最低载重 15 就能够在 5 天内送达所有包裹，如下所示：
第 1 天：1, 2, 3, 4, 5
第 2 天：6, 7
第 3 天：8
第 4 天：9
第 5 天：10

请注意，货物必须按照给定的顺序装运，因此使用载重能力为 14 的船舶并将包装分成 (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) 是不允许的。

*/
/*
 //1.最低运载能力必然大于等于序列中的最大值；结果落在[max(weights), sum(weights)]        //2.要注意是在D天“内”完成，所以运载能力要尽量小，只要是在D天之内就可以作者：luke-9r链接：https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/solution/c-er-fen-cha-zhao-jian-dan-shi-xian-dai-ma-by-luke/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
对于一艘承载力为K船来说，我们必然会在不超过其承载力的前提下贪心地往上装载货物，这样才能使得运送包裹所花费的时间最短。
如果船在承载力为K的条件下可以完成在D天内送达包裹的任务，那么任何承载力大于K的条件下依然也能完成任务。
我们可以让这个承载力K从max(weights)max(weights)开始（即所有包裹中质量最大包裹的重量，低于这个重量我们不可能完成任务），逐渐增大承载力K，直到K可以让我们在D天内送达包裹。此时K即为我们所要求的最低承载力。
逐渐增大承载力K的方法效率过低，让我们用二分查找的方法来优化它。
*/
bool canShip(int* weights, int weightsSize, int D, int shipCapacity)
{
	int cur = shipCapacity ;
	for(int i = 0; i < weightsSize; i++) {
		if (weights[i] > shipCapacity )
			return false;
		if (cur < weights[i]) {
			cur = shipCapacity ;
			D--;
		}
		cur -= weights[i];
	}
	return D > 0;
}

int shipWithinDays(int* weights, int weightsSize, int D)
{
	int left = 0;
	int right = 0;

	for(int i = 0; i < weightsSize; i++) {
		left = fmax(left, weights[i]);
		right += weights[i];
	}

	while(left < right) {
		int mid = (right + left) / 2;
		if (canShip(weights, weightsSize, D, mid)) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	return left;
}

/*
378. 有序矩阵中第K小的元素
难度中等245
给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，
找到矩阵中第 k 小的元素。
请注意，它是排序后的第 k 小元素，
而不是第 k 个不同的元素。

示例：
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

返回 13。

*/
/*
首先第k大数一定落在[l, r]中，其中l = matrix[0][0], r = matrix[row - 1][col - 1].
我们二分值域[l, r]区间，mid = (l + r) >> 1, 对于mid，我们检查矩阵中
有多少元素小于等于mid，
记个数为cnt，那么有：
1、如果cnt < k, 那么[l, mid]中包含矩阵元素个数一定小于k，那么
第k小元素一定不在[l, mid]
中，必定在[mid + 1, r]中，所以更新l = mid + 1.
2、否则cnt >= k，那么[l, mid]中包含矩阵元素个数就大于等于k，
即第k小元素一定在[l,mid]区间中，
更新r = mid;

至于怎么得矩阵中有多少元素小于等于k，可以利用矩阵本身
性质，从左下角开始按列枚举
综上：
算法时间复杂度为O(n * log(m)), 其中n = max(row, col)，代表矩阵行数
和列数的最大值,
 m代表二分区间的长度，即矩阵最大值和最小值的差。
*/
int getLowerCnt(int **matrix, int row, int col, int mid)
{
    int i = row - 1, j = 0, cnt = 0;
    while (i >= 0 && j < col) {
        if (matrix[i][j] <= mid) {
            cnt = cnt + i + 1;
            j++;
        } else {
            i--;
        }
    }
    return cnt;
}

int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k)
{
	if (matrix == NULL || matrixColSize == NULL || matrixSize == 0)
		return -1;
	int row = matrixSize, col = matrixColSize[0];
	int l = matrix[0][0], r = matrix[row - 1][col - 1];
	while (l < r) {//值域
		int mid = (l + r) >> 1;
		if (getLowerCnt(matrix, row, col, mid) < k) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	return l;
}

/*
面试题 10.09. 排序矩阵查找
给定M×N矩阵，每一行、每一列都按升序排列，
请编写代码找出某元素。

示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。
给定 target = 20，返回 false。
*/

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target)
{
	int i = 0, j = matrixColSize-1;

	while(j >= 0 && i < matrixRowSize) {
		if(matrix[i][j] > target)
			j--;
		else if(matrix[i][j] < target)
			i++;
		else
			return true;
	}

	return false;
}

/*
1198. 找出所有行中最小公共元素
难度中等8
给你一个矩阵 mat，其中每一行的元素都已经按 递增 顺序
排好了。请你帮忙找出在所有这些行中 最小的公共元素。
如果矩阵中没有这样的公共元素，就请返回 -1。

示例：
输入：
mat = [
[1,2,3,4,5],
[2,4,5,8,10],
[3,5,7,9,11],
[1,3,5,7,9]
]
输出：5

*/
int smallestCommonElement(int** mat, int matSize, int* matColSize)
{
	int map[10001];

	memset(map, 0, sizeof(map));
	for (int i = 0; i < matSize; i++) {
		for (int j = 0; j < matColSize[i]; j++) {
			map[mat[i][j]]++;
		}
	}

	for (int i = 0; i < 10001; i++) {
		if (map[i] == matSize)
			return i;
	}

	return -1;
}
/*
mat = [
[1,2,3,4,5],
[2,4,5,8,10],
[3,5,7,9,11],
[1,3,5,7,9]
]
*/
int smallestCommonElement(int** mat, int matSize, int* matColSize)
{
	int map[10001];
	memset(map, 0, sizeof(map));

	int row = matSize;
	int col = matColSize[0];
	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			if (++map[mat[i][j]] == row) {
				return mat[i][j];
			}
		}
	}

	return -1;
}
/*
mat = [
[1,2,3,4,5],
[2,4,5,8,10],
[3,5,7,9,11],
[1,3,5,7,9]
]
*/
int smallestCommonElement(int** mat, int matSize, int* matColSize)
{
	int map[10001];
	memset(map, 0, sizeof(map));

	int fd;
	int row = matSize;
	int col = matColSize[0];
	int *find_num = NULL;

	for (int j = 0; j < col; j++) {
		for (int i = 1; i < row; i++) {
			find_num = bsearch(&mat[0][j], mat[i], col, sizeof(int), cmp_int);
			if (find_num == NULL) {
				break;
			}
		}

		if (find_num != NULL)
			return mat[0][j];
	}

	return -1;
}

/*
702. 搜索长度未知的有序数组
难度中等11
给定一个升序整数数组，写一个函数搜索 nums 中数字 target。
如果 target 存在，返回它的下标，否则返回 -1。注意，这个数
组的大小是未知的。你只可以通过 ArrayReader 接口访问这个数组，
ArrayReader.get(k) 返回数组中第 k 个元素（下标从 0 开始）。
你可以认为数组中所有的整数都小于 10000。如果你访问数组
越界，ArrayReader.get 会返回 2147483647。
样例 1：
输入: array = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 存在在 nums 中，下标为 4
*/
int search(struct ArrayReader* reader, int target)
{
	if (getElement(reader, 0) == target)
		return 0;

	// search boundaries
	int left = 0, right = 1;
	while (getElement(reader, right) < target) {
		left = right;
		right <<= 1;
	}

	// binary search
	int mid, seachValue;
	while (left <= right) {
		mid = (left + right) >> 1;
		seachValue = getElement(reader, mid);

		if (seachValue == target)
			return mid;
		if (seachValue > target)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}

/*
153. 寻找旋转排序数组中的最小值
难度中等208
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
请找出其中最小的元素。
你可以假设数组中不存在重复元素。
示例 1:
输入: [3,4,5,1,2]
输出: 1

*/
int findMin(int* nums, int numsSize)
{
	int left = 0;
	int right = numsSize - 1;

	while(right - left > 1) {
		int mid= (left + right) >> 1;
		if(nums[mid] > nums[right])
			left = mid;
		else
			right = mid;
	}

	return fmin(nums[left], nums[right]);
}


/*
436. 寻找右区间
难度中等41
给定一组区间，对于每一个区间 i，检查是否存在一个区间 j，
它的起始点大于或等于区间 i 的终点，这可以称为 j 在 i
的"右侧"。
对于任何区间，你需要存储的满足条件的区间 j 的最小索引，
这意味着区间 j 有最小的起始点可以使其成为"右侧"区间。
如果区间 j 不存在，则将区间 i 存储为 -1。最后，你需要输出
一个值为存储的区间值的数组。
注意:
1.	你可以假设区间的终点总是大于它的起始点。
2.	你可以假定这些区间都不具有相同的起始点。
示例 1:
输入: [ [1,2] ]
输出: [-1]

解释:集合中只有一个区间，所以输出-1。
示例 2:
输入: [ [3,4], [2,3], [1,2] ]
输出: [-1, 0, 1]

解释:对于[3,4]，没有满足条件的"右侧"区间。
对于[2,3]，区间[3,4]具有最小的"右"起点;
对于[1,2]，区间[2,3]具有最小的"右"起点。
示例 3:
输入: [ [1,4], [2,3], [3,4] ]
输出: [-1, 2, -1]

*/

// 二维数组排序
int MyCmp(const void *pa, const void *pb)
{
    return (*(int**)pa)[0] - (*(int**)pb)[0];
}

int BinarySerach(int **intervalsTmp, int intervalsSize, int left, int right, int target)
{
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        // 正好搜索到目标直接返回
        if (target == intervalsTmp[mid][0]) {
            return intervalsTmp[mid][1];
        } else if (target < intervalsTmp[mid][0]) {
            // 目标小 砍掉右区间right = mid - 1
            right = mid - 1;
        } else if (target > intervalsTmp[mid][0]){
            left = mid + 1;
        }
    }

    // 走到这里 while循环结束的条件只有一个left == right + 1 所以实际left需要减掉1
    // 第一种情况 left元素 大于target 满足条件 直接返回
    // 第二种情况 left元素 小于target 试探下left是否超过 最大边界 不越界直接返回left元素 越界说明找不到比target大的了
    // 其他情况 通通返回-1
    if (intervalsTmp[left - 1][0] >= target) {
        return intervalsTmp[left - 1][1];
    } else if (left < intervalsSize) {
        return intervalsTmp[left][1];
    }

    return -1;
}

int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize,
	int* returnSize)
{
	*returnSize = 0;
	if (intervalsSize == 0) {
		return NULL;
	}

	int* retArray = (int*)malloc(sizeof(int) * intervalsSize);
	int** intervalsTmp = (int**)malloc(sizeof(int*) * intervalsSize);
	for (int i = 0; i < intervalsSize; i++) {
		intervalsTmp[i] = (int*)malloc(sizeof(int) * (*intervalsColSize));
		intervalsTmp[i][0] = intervals[i][0];
		intervalsTmp[i][1] = i;
	}

	qsort(intervalsTmp, intervalsSize, sizeof(int*), MyCmp);

	// 二分查找
	for (int i = 0; i < intervalsSize; i++) {
	retArray[i] = BinarySerach(intervalsTmp, intervalsSize, 0, intervalsSize - 1, intervals[i][1]);
	}
	*returnSize = intervalsSize;
	return retArray;
}

/*
33. 搜索旋转排序数组
难度中等840
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
你可以假设数组中不存在重复的元素。
你的算法时间复杂度必须是 O(log n) 级别。
示例 1:
输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4
示例 2:
输入: nums = [4,5,6,7,0,1,2], target = 3
输出: -1

*/
int search(int* nums, int numsSize, int target)
{
        int l = 0;
        int r = numsSize - 1;
        int mid;
        while (l < r){
            mid = l + (r - l) / 2;
            if ((nums[0]> target) ^ (nums[mid] < nums[0]) ^ (nums[mid] < target))
                l = mid + 1;
            else
                r = mid;
        }
        return l == r && nums[l] == target? l:-1;
}

int search(int* nums, int numsSize, int target)
{
        int left=0,right=numsSize-1,mid;
        while(left<=right){
            mid=left+(right-left)/2;
            if(nums[0]>target){  //目标在右子数组
                if(nums[mid]>=nums[0]) left=mid+1; //中点在左子数组
                else{ //中点在右子数组
                    if(nums[mid]==target) return mid;
                    else if(nums[mid]<target) left=mid+1;
                    else right=mid-1;
                }
            }
            else {//目标在左子数组
                if(nums[mid]<nums[0]) right=mid-1;//中点在右子数组
                else{ //中点在左子数组
                    if(nums[mid]==target) return mid;
                    else if(nums[mid]<target) left=mid+1;
                    else right=mid-1;
                }
            }
        }
        return -1;
}

/*
4. 寻找两个正序数组的中位数
难度困难2980
给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。

示例 1:
nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
示例 2:
nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5

*/
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int m = nums1Size;
    int n = nums2Size;
    int len = m + n;
    int left = -1, right = -1;
    int aStart = 0, bStart = 0;
    for (int i = 0; i <= len / 2; i++) {
        left = right;
        if (aStart < m && (bStart >= n || nums1[aStart] < nums2[bStart])) {
            right = nums1[aStart++];
        } else {
            right = nums2[bStart++];
        }
    }
    if ((len & 1) == 0)
        return (left + right) / 2.0;
    else
        return right;
}

double getNum(int* nums1, int nums1Size, int* nums2, int nums2Size, int k){
        int result[nums1Size + nums2Size];
        int i = 0, j = 0;
        int cur = 0;
        while(i < nums1Size && j <nums2Size && cur <= k){
            if(nums1[i] < nums2[j]) result[cur++] = nums1[i++];
            else result[cur++] = nums2[j++];
        }
        while(i < nums1Size && cur <=k) result[cur++] = nums1[i++];
        while(j < nums2Size && cur <=k) result[cur++] = nums2[j++];
        return result[cur-1];
    }

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
        int length = nums1Size + nums2Size;
        double result = 0;
        //分别进行奇数偶数处理
        if(length % 2 != 0){
            result = getNum(nums1,nums1Size, nums2, nums2Size, length/2);
        }else{
            result = getNum(nums1,nums1Size, nums2, nums2Size, length/2-1)/2 +
				getNum(nums1,nums1Size, nums2, nums2Size, length/2)/2;
        }
        return result;
}

/*
295. 数据流的中位数
难度困难227
中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
例如，
[2,3,4] 的中位数是 3
[2,3] 的中位数是 (2 + 3) / 2 = 2.5
设计一个支持以下两种操作的数据结构：
"	void addNum(int num) - 从数据流中添加一个整数到数据结构中。
"	double findMedian() - 返回目前所有元素的中位数。
示例：
addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2
进阶:
1.	如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
2.	如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？
通过次数19,813
*/
typedef struct {
	int size;
	int array[1024 * 1024];
} MedianFinder;

MedianFinder* medianFinderCreate() {
	return (MedianFinder*)calloc(1, sizeof(MedianFinder));
}

void medianFinderAddNum(MedianFinder* obj, int num) {
	//insert sort
	if (obj->size >= 3) {
		int left = 0;
		int right = obj->size - 1;

		while(left + 1 < right) {
			int mid = (left + right) / 2;
			if (num > obj->array[mid]) {
				left = mid;
			} else {
				right = mid;
			}
		}

		int move;
		if (num > obj->array[right]) {
			move = right + 1;
		} else if (num < obj->array[left]){
			move = left;
		} else {
			move = right;
		}

		for (int i = obj->size; i > move; i--) {
			obj->array[i] = obj->array[i - 1];
		}

		obj->array[move] = num;
		obj->size++;
	} else {
		obj->array[obj->size++] = num;
		qsort(obj->array, obj->size, sizeof(int), cmp_int);
	}
}

double medianFinderFindMedian(MedianFinder* obj) {
	if (obj->size % 2 == 0) {
		return (obj->array[obj->size / 2] + obj->array[obj->size / 2 - 1]) * 0.5;
	} else {
		return obj->array[obj->size / 2];
	}
}

void medianFinderFree(MedianFinder* obj) {
	free(obj);
	obj = NULL;
}

/*
167. 两数之和 II - 输入有序数组
难度简单375
给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。
函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。
说明:
"	返回的下标值（index1 和 index2）不是从零开始的。
"	你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。
示例:
输入: numbers = [2, 7, 11, 15], target = 9
输出: [1,2]
解释: 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。


*/

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;

    for (int i = 0; i < numbersSize; ++i) {
        int low = i + 1, high = numbersSize - 1;
        while (low <= high) {
            int mid = (high - low) / 2 + low;
            if (numbers[mid] == target - numbers[i]) {
                ret[0] = i + 1, ret[1] = mid + 1;
                return ret;
            } else if (numbers[mid] > target - numbers[i]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
    }
    ret[0] = -1, ret[1] = -1;
    return ret;
}

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;

    int low = 0, high = numbersSize - 1;
    while (low < high) {
        int sum = numbers[low] + numbers[high];
        if (sum == target) {
            ret[0] = low + 1, ret[1] = high + 1;
            return ret;
        } else if (sum < target) {
            ++low;
        } else {
            --high;
        }
    }
    ret[0] = -1, ret[1] = -1;
    return ret;
}