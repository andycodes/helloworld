/*
result = []
def backtrack(路径, 选择列表):
    if 满足「结束条件」:
        result.add(「路径」)
        return

    for 选择 in 「选择列表」:
        #做选择
	 将该选择从选择列表移除
	 「路径」.add(选择)
        backtrack(路径, 选择列表)
        #撤销选择
        「路径」.remove(选择)
    	 将该选择再加入选择列表

*/


/*全排列*/
void backtrack(int source[], int start, int end, int *resSize, int **res)
{
	// 找到一个排列
	if (start == end) {
		res[*resSize] = (int *)calloc (sizeof(int)*end);
		memcpy(res[*resSize], source, sizeof(int) * end);
		(*resSize)++;
	} else {
		// 没有找完一个排列，则继续往下找下一个元素
		for (int i = start; i < end; i++) {
			if (start != i) {// 两两交换
				swap(source[start], source[i]);
			}

			// 递归排列剩余的从start+1到end的元素
			backtrack(source, start + 1, end, resSize, res);

			if (start != i) {// 回溯时还原
				swap(source[start], source[i]);
			}
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be calloc ed, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
	int **res = (int **)calloc (17000 * sizeof(int *));
	int resSize = 0;

	backtrack(nums, 0, numsSize, &resSize, res);

	*returnSize = resSize;
	*returnColumnSizes = (int *)calloc (sizeof(int) * 17000);
	for (int i = 0; i < resSize; i++) {
		(*returnColumnSizes)[i] = numsSize;
	}

	return res;
}

