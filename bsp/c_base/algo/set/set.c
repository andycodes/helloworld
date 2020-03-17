/*
面试题 08.04. 幂集
难度中等3
幂集。编写一种方法，返回某集合的所有子集。集合中不包含重复的元素。
说明：解集不能包含重复的子集。
示例:
 输入： nums = [1,2,3]
 输出：
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

*/

/*
0-(1<<n)的二进制数代表了一个集合的所有子集，
位为1的位对应的索引在其中，位0的不在其中。
*/
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
	int **res = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	for (int i = 0; i < (1 << numsSize); i++) {
		res[*returnSize] = (int *)calloc(numsSize, sizeof(int));
		int col = 0;
		for (int j = 0; j < numsSize; j++) {
			if (i & (1 << j)) {
				res[*returnSize][col++]=  nums[j];
			}
		}

		(*returnColumnSizes)[*returnSize] = col;
		(*returnSize)++;
	}
	return res;
}

