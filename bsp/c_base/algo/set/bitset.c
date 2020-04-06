/*
���ǿ��԰�ǰ����㷨�����Ż���
���ǲ��ټ�����ֵ�ÿһ��λ��
���ǲ��ϰ��������һ�� 11 ��ת��
���Ѵ𰸼�һ�������ֱ�� 00 ��ʱ��ż��
���Ǿ�֪����û�� 11 ��λ�ˣ���ʱ���ش𰸡�
����ؼ����뷨�Ƕ����������� nn ���� nn �� n - 1n?1 �������㣬
������һ�� 11 ��λ��� 00 ��Ϊʲô������ nn �� n - 1n?1 ��
�����Ʊ�ʾ��

�ڶ����Ʊ�ʾ�У����� nn �����λ�� 11 ���Ƕ�Ӧ n - 1n?1 �е� 00 ��
��ˣ��� nn �� n - 1n?1 �����������ܰ� nn �����λ�� 11 ��� 00 ��
����������λ���䡣ʹ�����С���ɣ������÷ǳ��򵥡�


ͳ��һ��λ�����з�0λ����������ѧ�ϳ�����
��Hanmming Weight������������
*/

int hammingWeight(unsigned int n)
{
    int sum = 0;
    while (n != 0) {
        sum++;
        n &= (n - 1);
    }
    return sum;
}



/*
������ö��:�����Ӽ�
����N��Ԫ�صļ��ϵ�һ���Ӽ��ĸ���Ϊ 2^n

	for (int i = 0; i < (1 << numsSize); i++) {�����Ӽ�����״̬
		for (int j = 0; j < numsSize; j++) {//�����Ӽ�״̬�Ķ����Ƶ�ÿһλ
			if ((i & (1 << j)) != 0) { //Ϊ�棬ѡȡԭʼ�����еĳ�Ա

			}
		}

	}

*/

/*
������ 08.04. �ݼ�
�Ѷ��е�3
�ݼ�����дһ�ַ���������ĳ���ϵ������Ӽ��������в���
���ظ���Ԫ�ء�
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


/*
1239. �����ַ�������󳤶�
�Ѷ��е�34
����һ���ַ������� arr���ַ��� s �ǽ� arr ĳһ�������ַ���
�������õ��ַ�������� s �е�ÿһ���ַ���ֻ���ֹ�һ�Σ�
��ô������һ�����н⡣
�뷵�����п��н� s ������ȡ�

ʾ�� 1��
���룺arr = ["un","iq","ue"]
�����4
���ͣ����п��ܵĴ�������� "","un","iq","ue","uniq" �� "ique"��
��󳤶�Ϊ 4��
ʾ�� 2��
���룺arr = ["cha","r","act","ers"]
�����6
���ͣ����ܵĽ���� "chaers" �� "acters"��
ʾ�� 3��
���룺arr = ["abcdefghijklmnopqrstuvwxyz"]
�����26

*/

/*
˼·����
����ÿ�������޷Ǿ����������ѡ���ⲻѡ��

���� arr �е�ÿ����������һ��������λ����ʾ����
Ϊ 1 ��ʾѡ��������ʣ�Ϊ 0 ��ʾ��ѡ��������ʡ�

��Ŀ���� 1 <= arr.length <= 16����һ�� int(38λ)���㹻��ʾ arr �е�
���е��ʡ�

���� arr ���� 5 �����ʣ����� int i; ��ö�ٶ� arr ������ѡ�������

�� i = 0; ʱ��i ������λ��Ϊ 0 ����ʾ������ǣ� arr �еĵ��ʶ���ѡ��

�� i = (1 << 5) - 1 ʱ��i ��ǰ 5 λ��Ϊ 1����ʾ������ǣ�arr�еĵ��ʶ�ѡ��

������ѡ������Ϳ�������ö�٣�

for (int i = 0; i < (1 << 5); i++) {
    // �õ���ÿ�� i �����Ա�ʾһ��ѡ�����
}
���� i ��ʾ���������ô֪��ĳ������ word ��ѡȡ״̬��

word �� arr �е����� j �ͱ�ʾ���� i �ĵڼ�λ��ʹ�� i & (1 << j) ��֪�� word ��ѡȡ״̬��

�� i & (1 << j) Ϊ 1 ʱ����ʾ word ��״̬Ϊѡ��
�� i & (1 << j) Ϊ 0 ʱ����ʾ word ��״̬Ϊ��ѡ��
ͬʱ������ʹ��λ��������ʾ�ַ����� 26 ��Ӣ��Сд��ĸ�ĳ���������ڴ������� int m; �е� 26 λ������ʾ 26 ��Ӣ�ĵĳ���״̬��

*/
bool isUnique(char * str, int *bit)
{
	int i = 0;
	while(str[i] != '\0') {
		if (*bit & (1 << (str[i] - 'a'))) {
			return false;
		}

		*bit |= (1 << (str[i] - 'a'));
		i++;
	}

	return true;
}

int maxLength(char ** arr, int arrSize)
{
	if (arr == NULL || arrSize <= 0) {
		return 0;
	}

	if (arr != NULL && arrSize == 1) {
		return strlen(arr[0]);
	}

	int ans = 0;
	for (int i = 0; i < (1 << arrSize); i++) {
		int sum = 0;
		int bit = 0;
		for (int j = 0; j < arrSize; j++) {
			if ((i & (1 << j)) && isUnique(arr[j], &bit)) {
				sum += strlen(arr[j]);
			}
		}
		ans = fmax(ans, sum);
	}

	return ans;
}

/*
77. ���
�Ѷ��е�238
������������ n �� k������ 1 ... n �����п��ܵ� k ��������ϡ�
ʾ��:
����: n = 4, k = 2
���:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes)
{
	if (k > n || n < 1) {
		return NULL;
	}

	int **res = (int **)calloc(1 << n, sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1 << n, sizeof(int));

	for (int i = 0; i < (1 << n); i++) {
		if(hammingWeight(i) == k) {
			res[*returnSize] = (int *)calloc(1 << n, sizeof(int));
			for (int j = 0; j < n; j++) {
				if (((i & (1 << j)) != 0)) {
					res[*returnSize][(*returnColumnSizes)[*returnSize]] = j + 1;
					((*returnColumnSizes)[*returnSize])++;
				}
			}

			(*returnSize)++;
		}
	}

	return res;
}




