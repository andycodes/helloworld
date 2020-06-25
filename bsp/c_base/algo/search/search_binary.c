#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


