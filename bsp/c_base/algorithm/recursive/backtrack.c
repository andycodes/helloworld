/*
result = []
def backtrack(·��, ѡ���б�):
    if ���㡸����������:
        result.add(��·����)
        return

    for ѡ�� in ��ѡ���б�:
        #��ѡ��
	 ����ѡ���ѡ���б��Ƴ�
	 ��·����.add(ѡ��)
        backtrack(·��, ѡ���б�)
        #����ѡ��
        ��·����.remove(ѡ��)
    	 ����ѡ���ټ���ѡ���б�

*/


/*ȫ����*/
void backtrack(int source[], int start, int end, int *resSize, int **res)
{
	// �ҵ�һ������
	if (start == end) {
		res[*resSize] = (int *)calloc (sizeof(int)*end);
		memcpy(res[*resSize], source, sizeof(int) * end);
		(*resSize)++;
	} else {
		// û������һ�����У��������������һ��Ԫ��
		for (int i = start; i < end; i++) {
			if (start != i) {// ��������
				swap(source[start], source[i]);
			}

			// �ݹ�����ʣ��Ĵ�start+1��end��Ԫ��
			backtrack(source, start + 1, end, resSize, res);

			if (start != i) {// ����ʱ��ԭ
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

