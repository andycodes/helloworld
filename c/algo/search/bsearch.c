/*
	left = min
	right = max;
*/
int lower_bound(int *nums, int numsSize, int target)
{
	 int left = 0;
	 int right = numsSize - 1;//˼��
//��������[left, right)��Ϊ�գ��˳���ʱ��left = right
	while(left < right) {
		int mid = left + (right - left >> 1);

		if (nums[mid] < target) {//�ϸ���Ŀ��target�����ų�
			left = mid + 1;//[mid + 1, right]
		} else {
			right = mid;
		}
	}

	return left;//right Ҳ�� ��Ϊ[left, right)Ϊ�յ�ʱ�������غ�
}



/*bseach�÷�:
void *bsearch(const void *key, const void *base, size_t nelem, size_t width,
int(*fcmp)(const void *, const *));
������
key�ǲ���Ԫ�صĵ�ַ
������qsortһ��
*/


/*
������ 10.09. ����������
����M��N����ÿһ�С�ÿһ�ж����������У�
���д�����ҳ�ĳԪ�ء�
ʾ��:
���о��� matrix ���£�

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
���� target = 5������ true��
���� target = 20������ false��
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
153. Ѱ����ת���������е���Сֵ
�Ѷ��е�208
���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת��
( ���磬���� [0,1,2,4,5,6,7] ���ܱ�Ϊ [4,5,6,7,0,1,2] )��
���ҳ�������С��Ԫ�ء�
����Լ��������в������ظ�Ԫ�ء�
ʾ�� 1:
����: [3,4,5,1,2]
���: 1

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
315. �����Ҳ�С�ڵ�ǰԪ�صĸ���
�Ѷ�����409
����һ���������� nums����Ҫ�󷵻�һ�������� counts������
counts �и����ʣ� counts[i] ��ֵ��  nums[i] �Ҳ�С�� nums[i] ��Ԫ�ص���
����
ʾ����
���룺nums = [5,2,6,1]
�����[2,1,1,0]
���ͣ�
5 ���Ҳ��� 2 ����С��Ԫ�� (2 �� 1)
2 ���Ҳ���� 1 ����С��Ԫ�� (1)
6 ���Ҳ��� 1 ����С��Ԫ�� (1)
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
	���룺nums = [5,2,6,1]
	�����[2,1,1,0]
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
		// �����������Ԫ��
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

	/* ���valС�ڵ���root->val��˵��val����������е�ֵ��
	����g_smallCnt�����£�ֻ��Ҫ����С�ڸýڵ�val�Ľڵ���� */
	if (root->val >= val) {
		root->smallCnt++;
		root->left = AddNode(root->left, val);
	/* ���val����root->val��˵��root�ڵ��Լ�root���������ڵ㶼��
	С��val�ģ�+1�Ǳ�ʾroot�ڵ㱾�� */
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
410. �ָ���������ֵ
�Ѷ�����318
����һ���Ǹ����������һ������ m������Ҫ���������ֳ�
m ���ǿյ����������顣���һ���㷨ʹ���� m �����������
�͵����ֵ��С��
ע��:
���鳤�� n ������������:
"	1 �� n �� 1000
"	1 �� m �� min(50, n)
ʾ��:
����:
nums = [7,2,5,10,8]
m = 2
���:
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
719. �ҳ��� k С�ľ����
����һ���������飬������������֮��ĵ� k ����С���롣һ�� (A, B) �ľ��뱻����Ϊ A �� B ֮��ľ��Բ�ֵ��

ʾ�� 1:

���룺
nums = [1,3,1]
k = 1
�����0
���ͣ�
�����������£�
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
��˵� 1 ����С����������� (1,1)������֮��ľ���Ϊ 0��
*/

/*
���ڵ� k С�ľ���һ���� [0, W = max(nums) - min(nums)] �У���������������Ͻ��ж��֡�
���ڵ�ǰ���ֵ�λ�� guess��ͳ�ƾ���С�ڵ��� guess �ľ�������������������� k ��
��ϵ������������½硣
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
81. ������ת�������� II
���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת��

( ���磬���� [0,0,1,2,2,5,6] ���ܱ�Ϊ [2,5,6,0,0,1,2] )��

��дһ���������жϸ�����Ŀ��ֵ�Ƿ�����������С������ڷ��� true�����򷵻� false��

ʾ�� 1:

����: nums = [2,5,6,0,0,1,2], target = 0
���: true
ʾ�� 2:

����: nums = [2,5,6,0,0,1,2], target = 3
���: false
*/

/*
����˼·�����ַ����ң�������ֵ������ֵ�Ƚ�
1�����nums[mid] > nums[right]��˵��mid����ǵ�������
1��target���������������ڣ���right = mid - 1;
2������left = mid + 1;
2�����nums[mid] < nums[right]��˵��mid�Ҳ��ǵ�������
1��target�����Ҳ���������ڣ���left = mid + 1;
2������right = mid - 1;
3�����nums[mid] = nums[right]������ȷ�ϵ��������λ�ã��������ƶ��Ҳ�ָ��
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
34. �����������в���Ԫ�صĵ�һ�������һ��λ��
����һ�������������е��������� nums����һ��Ŀ��ֵ target���ҳ�����Ŀ��ֵ�������еĿ�ʼλ�úͽ���λ�á�

����㷨ʱ�临�Ӷȱ����� O(log n) ����

��������в�����Ŀ��ֵ������ [-1, -1]��

ʾ�� 1:

����: nums = [5,7,7,8,8,10], target = 8
���: [3,4]
ʾ�� 2:

����: nums = [5,7,7,8,8,10], target = 6
���: [-1,-1]
*/

int findFirstPosition(int* nums, int numsSize, int target) {
        int left = 0;
        int right = numsSize - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                // �� ������ֱ�ӷ��أ�Ӧ�ü���������ң��� [left, mid - 1] ��������
                right = mid - 1;
            } else if (nums[mid] < target) {
                // Ӧ�ü������ұ��ң��� [mid + 1, right] ��������
                left = mid + 1;
            } else {
                // ��ʱ nums[mid] > target��Ӧ�ü���������ң��� [left, mid - 1] ��������
                right = mid - 1;
            }
        }

        // ��ʱ left �� right ��λ�ù�ϵ�� [right, left]��ע������� �٣���ʱ left ���ǵ� 1 ��Ԫ�س��ֵ�λ��
        // ��˻���Ҫ�ر���һ���ж�
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
                // ֻ�����ﲻһ����������ֱ�ӷ��أ�Ӧ�ü������ұ��ң��� [mid + 1, right] ��������
                left = mid + 1;
            } else if (nums[mid] < target) {
                // Ӧ�ü������ұ��ң��� [mid + 1, right] ��������
                left = mid + 1;
            } else {
                // ��ʱ nums[mid] > target��Ӧ�ü���������ң��� [left, mid - 1] ��������
                right = mid - 1;
            }
        }
        // ���� findFirstPosition �������Է����Ƿ��ҵ����������赥�������ж�
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
        // ����� 1 �γ��ֵ�λ�ö��Ҳ������϶���������� 1 �γ��ֵ�λ��
        if (firstPosition == -1) {
            return res;
        }
        int lastPosition = findLastPosition(nums, numsSize, target);
	res[0] = firstPosition;
	res[1] = lastPosition;

	return res;
}