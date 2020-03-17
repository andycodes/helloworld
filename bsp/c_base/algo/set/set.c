/*
������ 08.04. �ݼ�
�Ѷ��е�3
�ݼ�����дһ�ַ���������ĳ���ϵ������Ӽ��������в������ظ���Ԫ�ء�
˵�����⼯���ܰ����ظ����Ӽ���
ʾ��:
 ���룺 nums = [1,2,3]
 �����
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
0-(1<<n)�Ķ�������������һ�����ϵ������Ӽ���
λΪ1��λ��Ӧ�����������У�λ0�Ĳ������С�
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

