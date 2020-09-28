
int lower_bound(int *nums, int numsSize, int target)
{
	 int left = 0;
	 int right = numsSize - 1;//思考
//搜索区间[left, right)不为空，退出的时候left = right
	while(left < right) {
		int mid = left + (right - left >> 1);

		if (nums[mid] < target) {//严格不是目标target，则排除
			left = mid + 1;//[mid + 1, right]
		} else {
			right = mid;
		}
	}

	return left;//right 也行 因为[left, right)为空的时候他们重合
}

/*

二维
int lower_bound(int *nums, int numsSize, int target)
{
	 int left = 0;
	 int right = row * col - 1;//思考
//搜索区间[left, right)不为空，退出的时候left = right
	while(left < right) {
		int mid = left + (right - left >> 1);
		int i = mid / col;
		int j = mid % col;
		if (nums[i][j] < target) {//严格不是目标target，则排除
			left = mid + 1;//[mid + 1, right]
		} else {
			right = mid;
		}
	}

	return left;//right 也行 因为[left, right)为空的时候他们重合
}


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
key是查找元素的地址
其他跟qsort一致
*/

/*
1011. 在 D 天内送达包裹的能力
难度中等75
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按
给出重量的顺序往传送带上装载包裹。我们装载的重量不会
超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载
能力。

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

请注意，货物必须按照给定的顺序装运，因此使用载重能力
为 14 的船舶并将包装分成 (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) 是不允许的。

*/
/*
 //1.最低运载能力必然大于等于序列中的最大值；
 结果落在[max(weights), sum(weights)]
 //2.要注意是在D天“内”完成，所以运载能力要尽量小，只要
 是在D天之内就可以
对于一艘承载力为K船来说，我们必然会在不超过其承载力的
前提下贪心地往上装载货物，这样才能使得运送包裹所花费
的时间最短。
如果船在承载力为K的条件下可以完成在D天内送达包裹的任
务，那么任何承载力大于K的条件下依然也能完成任务。
我们可以让这个承载力K从max(weights)max(weights)开始（即所有包
裹中质量最大包裹的重量，低于这个重量我们不可能完成任
务），逐渐增大承载力K，直到K可以让我们在D天内送达包裹
。此时K即为我们所要求的最低承载力。
逐渐增大承载力K的方法效率过低，让我们用二分查找的方法
来优化它。
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


bool checkWeight(int* weights, int weightsSize, int D, int cap)
{
	int days = 0;
	int prefix = 0;

	for (int i = 0; i < weightsSize; i++) {
		if (weights[i] > cap) {
			return false;
		}

		if (prefix + weights[i]> cap) {
			days++;
			prefix = 0;
		}

		prefix +=  weights[i];
	}

	days = prefix == 0 ? days : days + 1;

	return days <= D;
}


int shipWithinDays(int* weights, int weightsSize, int D)
{
	int max = 0;
	int total = 0;

	for (int i = 0; i < weightsSize; i++) {
		max = fmax(max, weights[i]);
		total += weights[i];
	}

	int left = max;
	int right = total;
	while (left < right) {
		int mid = left + (right - left >> 1);
		if (checkWeight(weights, weightsSize, D, mid) == false) {
			left = mid + 1;
		} else {
			right = mid;
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
1)直接转一维排序

*/
int getLowerCnt(int **matrix, int row, int col, int mid)
{
	int i = row - 1, j = 0, cnt = 0;
	while (i >= 0 && j < col) {
		if (matrix[i][j] <= mid) {
			cnt = cnt + i + 1;/*一列有i + 1的元素*/
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
	int left = matrix[0][0], right = matrix[row - 1][col - 1];
	while (left < right) {
		int mid = left + (right - left >> 1);
		if (getLowerCnt(matrix, row, col, mid) < k) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}

	return left;
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
	while (left < right) {
		mid = left + (right - left >> 1);
		seachValue = getElement(reader, mid);
		if (seachValue == target)
			return mid;

		if (seachValue < target) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}

	return getElement(reader, left) == target ? left : -1;
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

	while(left < right) {
		int mid= left + (right - left >> 1);

		if(nums[mid] > nums[right])//!
			left = mid + 1;
		else
			right = mid;
	}

	return nums[left];
}

/*
33. 搜索旋转排序数组
难度中等840
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
搜索一个给定的目标值，如果数组中存在这个目标值，则返
回它的索引，否则返回 -1 。
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
	int left = 0,right = numsSize-1,mid;
	while(left< right){
		mid = left+(right-left >>1);
		if(nums[0] > target){  //目标在右子数组
			if(nums[mid]>= nums[0])
				left = mid + 1; //中点在左子数组
			else{ //中点在右子数组
				if(nums[mid] == target)
					return mid;
				else if(nums[mid] <target)
					left = mid+1;
				else
					right = mid;
			}
		} else {//目标在左子数组
			if(nums[mid] < nums[0])
				right = mid;//中点在右子数组
			else{ //中点在左子数组
				if(nums[mid] == target)
					return mid;
				else if (nums[mid] < target)
					left = mid+1;
				else
					right = mid;
			}
		}
	}

	return nums[left] == target ? left : -1;
}


int search(int* nums, int numsSize, int target)
{
        int left = 0;
        int right = numsSize - 1;
        int mid;
        while (left < right){
            mid = left + (right - left >> 1);
            if ((nums[0]> target) ^ (nums[mid] < nums[0]) ^ (nums[mid] < target))
                left = mid + 1;
            else
                right = mid;
        }
        return left == right && nums[left] == target ? left:-1;
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
	int len = nums1Size+ nums2Size;
	int left = -1, right = -1;
	int aStart = 0, bStart = 0;

	for (int i = 0; i <= len / 2; i++) {
		left = right;
		if (aStart < nums1Size && (bStart >= nums2Size || nums1[aStart] < nums2[bStart])) {
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

/*
295. 数据流的中位数
难度困难227
中位数是有序列表中间的数。如果列表长度是偶数，中位数
则是中间两个数的平均值。
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
*/
typedef struct {
	int size;
	int array[1024 * 1024];
} MedianFinder;

MedianFinder* medianFinderCreate() {
	return (MedianFinder*)calloc(1, sizeof(MedianFinder));
}

void medianFinderAddNum(MedianFinder* obj, int num)
{
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

double medianFinderFindMedian(MedianFinder* obj)
{
	if (obj->size % 2 == 0) {
		return (obj->array[obj->size / 2] + obj->array[obj->size / 2 - 1]) * 0.5;
	} else {
		return obj->array[obj->size / 2];
	}
}

void medianFinderFree(MedianFinder* obj)
{
	free(obj);
	obj = NULL;
}


/*
315. 计算右侧小于当前元素的个数
难度困难409
给定一个整数数组 nums，按要求返回一个新数组 counts。数组
counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数
量。

示例：
输入：nums = [5,2,6,1]
输出：[2,1,1,0]
解释：
5 的右侧有 2 个更小的元素 (2 和 1)
2 的右侧仅有 1 个更小的元素 (1)
6 的右侧有 1 个更小的元素 (1)

*/

int* countSmaller(int* nums, int numsSize, int* returnSize)
{
	int *res = (int *)calloc(numsSize, sizeof(int));
	*returnSize = numsSize;

	for (int i = 0; i < numsSize - 1; i++) {
		int cnt = 0;
		for (int j = i + 1; j < numsSize; j++) {
			cnt += nums[j] < nums[i] ? 1 : 0;
		}

		res[i] = cnt;
	}

	return res;
}

int* countSmaller(int* nums, int numsSize, int* returnSize)
{
	if (nums == NULL || numsSize <= 0) {
		*returnSize = 0;
		return NULL;
	}

	int *res = (int *)calloc(numsSize, sizeof(int));
	*returnSize = numsSize;

	int sortArr[numsSize];
	int sortSize = 0;
	memset(sortArr, 0, sizeof(sortArr));
	/*
	输入：nums = [5,2,6,1]
	输出：[2,1,1,0]
	*/
	for(int i = numsSize - 1; i >= 0; i--) {
		int left = 0, right = sortSize;
		while(left < right) {
			int mid = left + (right - left >> 1);
			if(nums[i] > sortArr[mid])
				left = mid + 1;
			else
				right = mid;
		}

		res[i] = right;
		// 倒序逐个插入元素
		for (int i = sortSize; i > right; i--) {
			sortArr[i] = sortArr[i - 1];
		}
		sortArr[right] = nums[i];
		sortSize++;
	}

	return res;
}


#include <stdio.h>

struct BstNode {
    int val;
    int smallCnt;
    struct BstNode *left;
    struct BstNode *right;
};

static struct BstNode g_root;

static int g_smallCnt;
static struct BstNode *AddNode(struct BstNode *root, int val)
{
	if (root == NULL) {
		root = (struct BstNode *)calloc(1, sizeof(struct BstNode));
		root->val = val;
		return root;
	}

	/* 如果val小于等于root->val，说明val不会大于已有的值，
	所以g_smallCnt不更新，只需要更新小于该节点val的节点个数 */
	if (root->val >= val) {
		root->smallCnt++;
		root->left = AddNode(root->left, val);
	/* 如果val大于root->val，说明root节点以及root的左子树节点都是
	小于val的，+1是表示root节点本身 */
	} else {
		g_smallCnt += root->smallCnt + 1;
		root->right = AddNode(root->right, val);
	}

	return root;
}

int* countSmaller(int* nums, int numsSize, int* returnSize)
{
    int i;
    int *ans = (int *)calloc(1, sizeof(int) * numsSize);

    if (numsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }

    memset(&g_root, 0, sizeof(g_root));
    g_root.val = nums[numsSize - 1];

    for (i = numsSize - 2; i >= 0; i--) {
        g_smallCnt = 0;
        AddNode(&g_root, nums[i]);
        ans[i] = g_smallCnt;
    }

    *returnSize = numsSize;
    return ans;
}

/*
410. 分割数组的最大值
难度困难318
给定一个非负整数数组和一个整数 m，你需要将这个数组分成 m 个非空的连续子数组。设计一个算法使得这 m 个子数组各自和的最大值最小。
注意:
数组长度 n 满足以下条件:
"	1 ≤ n ≤ 1000
"	1 ≤ m ≤ min(50, n)
示例:
输入:
nums = [7,2,5,10,8]
m = 2

输出:
18

解释:
一共有四种方法将nums分割为2个子数组。
其中最好的方式是将其分为[7,2,5] 和 [10,8]，
因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。


*/

bool check(int* nums, int numsSize, int m, int x) {
    long long sum = 0;
    int cnt = 1;
    for (int i = 0; i < numsSize; i++) {
        if (sum + nums[i] > x) {
            cnt++;
            sum = nums[i];
        } else {
            sum += nums[i];
        }
    }
    return cnt <= m;
}

int splitArray(int* nums, int numsSize, int m) {
    long long left = 0, right = 0;
    for (int i = 0; i < numsSize; i++) {
        right += nums[i];
        if (left < nums[i]) {
            left = nums[i];
        }
    }
    while (left < right) {
        long long mid = (left + right) >> 1;
        if (check(nums, numsSize, m, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

/*
532. 数组中的K-diff数对
难度简单90收藏分享切换为英文关注反馈
给定一个整数数组和一个整数 k, 你需要在数组里找到不同的
k-diff 数对。这里将 k-diff 数对定义为一个整数对 (i, j), 其中 i 和 j 都
是数组中的数字，且两数之差的绝对值是 k.
示例 1:
输入: [3, 1, 4, 1, 5], k = 2
输出: 2
解释: 数组中有两个 2-diff 数对, (1, 3) 和 (3, 5)。
尽管数组中有两个1，但我们只应返回不同的数对的数量。
*/
int findPairs(int* nums, int numsSize, int k)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);
	int cnt = 0;
	for (int i = 0; i < numsSize; i++) {
		if (i != 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		int key = nums[i] + k;
		int *p = (int *)bsearch(&key, nums + i + 1, numsSize - i - 1, sizeof(int), cmp_int);
		if (p != NULL) {

			cnt++;
		}
	}

	return cnt;
}

/*
719. 找出第 k 小的距离对
给定一个整数数组，返回所有数对之间的第 k 个最小距离。一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值。

示例 1:

输入：
nums = [1,3,1]
k = 1
输出：0
解释：
所有数对如下：
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
因此第 1 个最小距离的数对是 (1,1)，它们之间的距离为 0。
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

//双指针加速
int helper(int* nums, int numsSize, int diff) {
    int cnt = 0;

    int ll = 0, rr = 0;
    while(rr < numsSize) {
        if(nums[rr] - nums[ll] <= diff) {
            rr++;
            continue;
        }

        //进行结算
        cnt += rr - ll - 1;
        ll++;
        //printf("hll = %d, hrr = %d, cnt = %d\n", ll, rr, cnt);
    }

    //处理尾部数据
    for(int i = ll; i < numsSize; i++) {
        cnt += numsSize - i - 1;
    }
/*
    for(int i = 0; i < numsSize - 1; i++) {
        for(int j = i + 1; j < numsSize; j++) {
            if(nums[j] - nums[i] <= diff) {
                cnt++;
            } else {
                break;
            }
        }
    }
*/
    //printf("diff = %d, cnt = %d\n", diff, cnt);
    return cnt;
}

//【算法思路】扩展的二分查找。以二分查找为框架，对于二分值如何判定进行扩展。
// 1.计算差值存在范围
// 2.给定差值，查找小于等于差值的对数
// 3.如果该数值大于K，则rr = mid
// 4.否则ll = mid + 1;
int smallestDistancePair(int* nums, int numsSize, int k){
    //找到最大最小值
    qsort(nums, numsSize, sizeof(int), compare);

    int ll = 0, rr = nums[numsSize - 1] - nums[0];
    while(ll < rr) {
        //printf("ll = %d, rr = %d\n", ll, rr);
        int mid = (ll + rr) / 2;

        int cnt = helper(nums, numsSize, mid);

        if(cnt >= k) {
            rr = mid;
        } else {
            ll = mid + 1;
        }
    }

    return ll;
}