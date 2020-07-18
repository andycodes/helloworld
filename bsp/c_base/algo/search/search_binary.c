/*
/*
[lb, ub]
int lb = 0, ub = size;
while (ub - lb > 1) {
	int mid = (lb + ub) / 2;
	if (check mid) {//根据nums[mid]来判断搜索左半部分还是右半部分
		lb = mid;
	} else {
		ub = mid;
	}
}

return nums[lb] >= target ? lb : ub;

二维

int lb = 0; ub = row * col;

while (ub - lb > 1) {
	int mid = (lb + ub) / 2;
	int i = mid / width;
	int j = mid % width;
	if (matrix[i][j] <= target) {//根据nums[mid]来判断搜索左半部分还是右半部分
		lb = mid;
	} else {
		ub = mid;
	}
}

return matrix[lb / width][lb % width] == target;
*/
*/

/** 数组元素的类型*/
typedef int elem_t;
/**
* @brief 有序顺序表的折半查找算法.
**
@param[in] a 存放数据元素的数组，已排好序
* @param[in] n 数组的元素个数
* @param[in] x 要查找的元素
* @return 如果找到x，则返回其下标。如果找
* 不到x 且x 小于array 中的一个或多个元素，则为一个负数，该负数是大
* 于x 的第一个元素的索引的按位求补。如果找不到x 且x 大于array 中的
* 任何元素，则为一个负数，该负数是（最后一个元素的索引加1）的按位求补。
*/
int binary_search(const elem_t a[], const int n, const elem_t x) {
    int left = 0, right = n -1, mid;
    while(left <= right) {
        mid = left + (right - left) / 2;
        if(x > a[mid]) {
            left = mid + 1;
        } else if(x < a[mid]) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -(left+1);
}


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


int test_binary_find_recur()
{
    int a[]={1,2,3,4,5,6,7,8,9,10};
    printf("%d\n",binary_find_recur(a,10,0,10));
}


/*bseach用法:
void *bsearch(const void *key, const void *base,
size_t nelem, size_t width, int(*fcmp)(const void *, const *));
参数：
key指向所要查找的元素.
第一个找的关键字。
第二个：要查找的数组。
第三个：指定数组中元素的数目。
第四个：每个元素的长度（以字符为单位）。
第五个：指向比较函数的指针.
*/
#define LEN 5
void arr_init(int num[], int len)
{
	int i;

	srand(time(NULL));
	for(i = 0; i < len; i++){
		num[i] = rand()%50;
	}

}

void arr_print(int num[], int len)
{
	int i;

	for(i = 0; i < len; i++){
		printf("%d ", num[i]);
	}
	printf("\n");

}


void test_bsearch(void)
{
	int num[LEN];
	int fd;
	int *find_num;

	arr_init(num, LEN);
	arr_print(num, LEN);
	qsort(num, LEN, sizeof(int), cmp_int);
	arr_print(num, LEN);
	printf("enter search num:\n");
	scanf("%d", &fd);
	find_num = bsearch(&fd, num, LEN, sizeof(int), cmp_int);
	(find_num == NULL) ? printf("no find\n") : printf("find the num %d\n", fd);
}

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
性质，从左下角开始按列枚举，具体可参考代码。

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
	while (l < r) {
		int mid = (l + r) >> 1;
		if (getLowerCnt(matrix, row, col, mid) < k) { // 落在区间[l, mid]中数小于k，说明第k小的数一定大于mid
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	return l;
}

int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k){
    struct HeapSort *heap = heapsort_init(k, PRIORITY_QUEUE_MAX);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
                if (heapsort_full(heap)) {
                    if (matrix[i][j] < heapsort_top_key(heap))                      {
                        heapsort_pop(heap);
                        struct heapEntry node;
                        node.key = matrix[i][j];
                        heapsort_push(heap, node);
                    }
                } else {
                        struct heapEntry node;
                        node.key = matrix[i][j];
                        heapsort_push(heap, node);
                }

        }
    }

    return heapsort_top_key(heap);
}

/*
面试题 10.09. 排序矩阵查找
给定M×N矩阵，每一行、每一列都按升序排列，请编写代码找出某元素。

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

通过次数3,044提交次数6,782
*/

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    // int i = matrixRowSize - 1, j = 0;
    int i = 0, j = matrixColSize-1;

    while(j>=0 && i<matrixRowSize) {
        if(matrix[i][j] > target) j--;
        else if(matrix[i][j] < target) i++;
        else return true;
    }
    return false;

}

/*
1198. 找出所有行中最小公共元素
难度中等8
给你一个矩阵 mat，其中每一行的元素都已经按 递增 顺序排好了。请你帮忙找出在所有这些行中 最小的公共元素。
如果矩阵中没有这样的公共元素，就请返回 -1。

示例：
输入：mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
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

int cmp_int ( const void *a , const void *b)
{
        return *(int *)a - *(int *)b;
}

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
给定一个升序整数数组，写一个函数搜索 nums 中数字 target。如果 target 存在，返回它的下标，否则返回 -1。注意，这个数组的大小是未知的。你只可以通过 ArrayReader 接口访问这个数组，ArrayReader.get(k) 返回数组中第 k 个元素（下标从 0 开始）。
你可以认为数组中所有的整数都小于 10000。如果你访问数组越界，ArrayReader.get 会返回 2147483647。

样例 1：
输入: array = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 存在在 nums 中，下标为 4

*/
int search(struct ArrayReader* reader, int target) {
	if (getElement(reader, 0) == target)
		return 0;

    // search boundaries
    int left = 0, right = 1;
    while (getElement(reader, right) < target) {
      left = right;
      right <<= 1;
    }

    // binary search
    int pivot, num;
    while (left <= right) {
      pivot = left + ((right - left) >> 1);
      num = getElement(reader, pivot);

      if (num == target) return pivot;
      if (num > target) right = pivot - 1;
      else left = pivot + 1;
    }

    // there is no target element
    return -1;
}

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/**
 * *********************************************************************
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * int getElement(ArrayReader *, int index);
 */

#define MAX_LEN     10000

//【算法思路】二分。超范围情况下的二分模型，需要判断ll和ll-1
int search(struct ArrayReader* reader, int target) {
    int ll = 0, rr = 10000;

    while(ll < rr) {
        int mid = (ll + rr) / 2;

        int tmp = getElement(reader, mid);

        if(tmp == INT_MAX) {
            rr = mid;

            continue;
        }

        if(tmp > target) {
            rr = mid;
        } else {
            ll = mid + 1;
        }
    }

    int ret = getElement(reader, ll) == target? ll : (getElement(reader, ll - 1) == target? ll - 1 : -1);

    return ret;
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
	int min = INT_MAX;

	for (int i = 0; i < numsSize; i++) {
		min = fmin(nums[i], min);
	}

	return min;
}

int findMin(int* nums, int numsSize){
    int left=0;
    int right=numsSize-1;
    while(right>left)
    {
        int mid=left+(right-left)/2;
        if(nums[mid]>nums[right])
            left=mid+1;
        else
            right=mid;
    }
    return nums[left];
}

/*
300. 最长上升子序列
难度中等812
给定一个无序的整数数组，找到其中最长上升子序列的长度。
示例:
输入: [10,9,2,5,3,7,101,18]
输出: 4
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
说明:
"	可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
"	你算法的时间复杂度应该为 O(n2) 。
进阶:

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

int lengthOfLIS(int* nums, int numsSize){
    if(numsSize==0)
    return 0;
    int stack[numsSize],i=0,top=0,j;
    stack[top++]=nums[0];
    for(i=1;i<numsSize;i++)
        {
            if(nums[i]>stack[top-1])//大于栈顶元素，入栈
            stack[top++]=nums[i];
            else
            {//小于栈顶元素
                for(j=0;j<top;j++)
                if(nums[i]<=stack[j])
                {
                    stack[j]=nums[i];
                    break;
                }
            }
        }
    return top;
}

int lengthOfLIS(int* nums, int numsSize){
    if(numsSize==0)
    return 0;
    int stack[numsSize],i=0,top=0,j;
    int low,high,mid;
    stack[top++]=nums[0];
    for(i=1;i<numsSize;i++)
        {
            if(nums[i]>stack[top-1])//大于栈顶元素，入栈
            stack[top++]=nums[i];
            else
            {//小于栈顶元素
                low=0;
                high=top-1;
                while(high>=low)
                {
                    mid=(low+high)/2;
                    if(stack[mid]>=nums[i])
                    high=mid-1;
                    else
                    low=mid+1;
                }
                stack[high+1]=nums[i];
            }
        }
    return top;
}

/*
436. 寻找右区间
难度中等41
给定一组区间，对于每一个区间 i，检查是否存在一个区间 j，它的起始点大于或等于区间 i 的终点，这可以称为 j 在 i 的"右侧"。
对于任何区间，你需要存储的满足条件的区间 j 的最小索引，这意味着区间 j 有最小的起始点可以使其成为"右侧"区间。如果区间 j 不存在，则将区间 i 存储为 -1。最后，你需要输出一个值为存储的区间值的数组。
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
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

int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize){
    *returnSize = 0;
    if (intervalsSize == 0) {
        return NULL;
    }
    int* retArray = (int*)malloc(sizeof(int) * intervalsSize);
    int** intervalsTmp = (int**)malloc(sizeof(int*) * intervalsSize);
    for (int i = 0; i < intervalsSize; i++) {
        intervalsTmp[i] = (int*)malloc(sizeof(int) * (*intervalsColSize));
        // 起始点坐标
        intervalsTmp[i][0] = intervals[i][0];
        // 原始数组中的位置
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