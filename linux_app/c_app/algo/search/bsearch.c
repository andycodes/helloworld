/*
	left = min
	right = max;
*/
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



/*bseach用法:
void *bsearch(const void *key, const void *base, size_t nelem, size_t width,
int(*fcmp)(const void *, const *));
参数：
key是查找元素的地址
其他跟qsort一致
*/


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
	int i = 0, j = matrixColSize - 1;

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

		if(nums[mid] > nums[right])
			left = mid + 1;
		else
			right = mid;
	}

	return nums[left];
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
给定一个非负整数数组和一个整数 m，你需要将这个数组分成
m 个非空的连续子数组。设计一个算法使得这 m 个子数组各自
和的最大值最小。
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

int splitArray(int* nums, int numsSize, int m)
{
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

/*
由于第 k 小的距离一定在 [0, W = max(nums) - min(nums)] 中，我们在这个区间上进行二分。
对于当前二分的位置 guess，统计距离小于等于 guess 的距离对数量，并根据它和 k 的
关系调整区间的上下界。
*/
int cmp(int* nums, int numsSize, int diff)
{
            int count = 0, left = 0;
            for (int right = 0; right < numsSize; ++right) {
                while (nums[right] - nums[left] > diff) left++;
                count += right - left;
            }
            //count = number of pairs with distance <= mi
            return count;
}

int smallestDistancePair(int* nums, int numsSize, int k)
{
	qsort(nums, numsSize, sizeof(int), cmp_int);

	int left = 0;
	int right = nums[numsSize - 1] - nums[0];//max diff
	while(left < right) {
		int mid = left + (right - left >> 1);
		int cnt = cmp(nums, numsSize, mid);
		if(cnt >= k) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	return left;
}

/*
81. 搜索旋转排序数组 II
假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2] )。

编写一个函数来判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。

示例 1:

输入: nums = [2,5,6,0,0,1,2], target = 0
输出: true
示例 2:

输入: nums = [2,5,6,0,0,1,2], target = 3
输出: false
*/

/*
解题思路：二分法查找，将给定值与最右值比较
1，如果nums[mid] > nums[right]，说明mid左侧是递增区间
1）target落在左侧递增区间内，则right = mid - 1;
2）否则left = mid + 1;
2，如果nums[mid] < nums[right]，说明mid右侧是递增区间
1）target落在右侧递增区间内，则left = mid + 1;
2）否则right = mid - 1;
3）如果nums[mid] = nums[right]，不能确认递增区间的位置，所以逐步移动右侧指针
*/
#define TRUE 1
#define FALSE 0
bool search(int* nums, int numsSize, int target){
    int left = 0;
    int right = numsSize - 1;
    int mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (nums[mid] == target) {
            return TRUE;
        }

        if (nums[mid] > nums[right]) {
            if ((target >= nums[left]) && (target < nums[mid])) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else if (nums[mid] < nums[right]) {
            if ((target > nums[mid]) && (target <= nums[right])) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            right--;
        }
    }

    return FALSE;
}

/*
34. 在排序数组中查找元素的第一个和最后一个位置
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。

示例 1:

输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]
示例 2:

输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
*/

int findFirstPosition(int* nums, int numsSize, int target) {
        int left = 0;
        int right = numsSize - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                // ① 不可以直接返回，应该继续向左边找，即 [left, mid - 1] 区间里找
                right = mid - 1;
            } else if (nums[mid] < target) {
                // 应该继续向右边找，即 [mid + 1, right] 区间里找
                left = mid + 1;
            } else {
                // 此时 nums[mid] > target，应该继续向左边找，即 [left, mid - 1] 区间里找
                right = mid - 1;
            }
        }

        // 此时 left 和 right 的位置关系是 [right, left]，注意上面的 ①，此时 left 才是第 1 次元素出现的位置
        // 因此还需要特别做一次判断
        if (left != numsSize && nums[left] == target) {
            return left;
        }
        return -1;
    }

    int findLastPosition(int* nums, int numsSize, int target) {
        int left = 0;
        int right = numsSize - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                // 只有这里不一样：不可以直接返回，应该继续向右边找，即 [mid + 1, right] 区间里找
                left = mid + 1;
            } else if (nums[mid] < target) {
                // 应该继续向右边找，即 [mid + 1, right] 区间里找
                left = mid + 1;
            } else {
                // 此时 nums[mid] > target，应该继续向左边找，即 [left, mid - 1] 区间里找
                right = mid - 1;
            }
        }
        // 由于 findFirstPosition 方法可以返回是否找到，这里无需单独再做判断
        return right;
    }


int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;
	res[0] = -1;
	res[1] = -1;

        if (nums == NULL|| numsSize == 0) {
            return res;
        }

        int firstPosition = findFirstPosition(nums, numsSize, target);
        // 如果第 1 次出现的位置都找不到，肯定不存在最后 1 次出现的位置
        if (firstPosition == -1) {
            return res;
        }
        int lastPosition = findLastPosition(nums, numsSize, target);
	res[0] = firstPosition;
	res[1] = lastPosition;

	return res;
}