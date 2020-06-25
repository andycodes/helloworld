#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** ����Ԫ�ص�����*/
typedef int elem_t;
/**
* @brief ����˳�����۰�����㷨.
**
@param[in] a �������Ԫ�ص����飬���ź���
* @param[in] n �����Ԫ�ظ���
* @param[in] x Ҫ���ҵ�Ԫ��
* @return ����ҵ�x���򷵻����±ꡣ�����
* ����x ��x С��array �е�һ������Ԫ�أ���Ϊһ���������ø����Ǵ�
* ��x �ĵ�һ��Ԫ�ص������İ�λ�󲹡�����Ҳ���x ��x ����array �е�
* �κ�Ԫ�أ���Ϊһ���������ø����ǣ����һ��Ԫ�ص�������1���İ�λ�󲹡�
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


/*bseach�÷�:
void *bsearch(const void *key, const void *base,
size_t nelem, size_t width, int(*fcmp)(const void *, const *));
������
keyָ����Ҫ���ҵ�Ԫ��.
��һ���ҵĹؼ��֡�
�ڶ�����Ҫ���ҵ����顣
��������ָ��������Ԫ�ص���Ŀ��
���ĸ���ÿ��Ԫ�صĳ��ȣ����ַ�Ϊ��λ����
�������ָ��ȽϺ�����ָ��.
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
1011. �� D �����ʹ����������
�Ѷ��е�75
���ʹ��ϵİ��������� D ���ڴ�һ���ۿ����͵���һ���ۿڡ�
���ʹ��ϵĵ� i ������������Ϊ weights[i]��ÿһ�죬���Ƕ��ᰴ����������˳�������ʹ���װ�ذ���������װ�ص��������ᳬ�������������������
�������� D ���ڽ����ʹ��ϵ����а����ʹ�Ĵ����������������

ʾ�� 1��
���룺weights = [1,2,3,4,5,6,7,8,9,10], D = 5
�����15
���ͣ�
����������� 15 ���ܹ��� 5 �����ʹ����а�����������ʾ��
�� 1 �죺1, 2, 3, 4, 5
�� 2 �죺6, 7
�� 3 �죺8
�� 4 �죺9
�� 5 �죺10

��ע�⣬������밴�ո�����˳��װ�ˣ����ʹ����������Ϊ 14 �Ĵ���������װ�ֳ� (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) �ǲ�����ġ�

*/
/*
 //1.�������������Ȼ���ڵ��������е����ֵ���������[max(weights), sum(weights)]        //2.Ҫע������D�조�ڡ���ɣ�������������Ҫ����С��ֻҪ����D��֮�ھͿ������ߣ�luke-9r���ӣ�https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/solution/c-er-fen-cha-zhao-jian-dan-shi-xian-dai-ma-by-luke/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
����һ�ҳ�����ΪK����˵�����Ǳ�Ȼ���ڲ��������������ǰ����̰�ĵ�����װ�ػ����������ʹ�����Ͱ��������ѵ�ʱ����̡�
������ڳ�����ΪK�������¿��������D�����ʹ������������ô�κγ���������K����������ȻҲ���������
���ǿ��������������K��max(weights)max(weights)��ʼ�������а�������������������������������������ǲ�����������񣩣������������K��ֱ��K������������D�����ʹ��������ʱK��Ϊ������Ҫ�����ͳ�������
�����������K�ķ���Ч�ʹ��ͣ��������ö��ֲ��ҵķ������Ż�����


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
378. ��������е�KС��Ԫ��
�Ѷ��е�245
����һ�� n x n ��������ÿ�к�ÿ��Ԫ�ؾ�����������
�ҵ������е� k С��Ԫ�ء�
��ע�⣬���������ĵ� k СԪ�أ�
�����ǵ� k ����ͬ��Ԫ�ء�

ʾ����
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

���� 13��

*/
/*
���ȵ�k����һ������[l, r]�У�����l = matrix[0][0], r = matrix[row - 1][col - 1].
���Ƕ���ֵ��[l, r]���䣬mid = (l + r) >> 1, ����mid�����Ǽ�������
�ж���Ԫ��С�ڵ���mid��
�Ǹ���Ϊcnt����ô�У�
1�����cnt < k, ��ô[l, mid]�а�������Ԫ�ظ���һ��С��k����ô
��kСԪ��һ������[l, mid]
�У��ض���[mid + 1, r]�У����Ը���l = mid + 1.
2������cnt >= k����ô[l, mid]�а�������Ԫ�ظ����ʹ��ڵ���k��
����kСԪ��һ����[l,mid]�����У�
����r = mid;

������ô�þ������ж���Ԫ��С�ڵ���k���������þ�����
���ʣ������½ǿ�ʼ����ö�٣�����ɲο����롣

���ϣ�
�㷨ʱ�临�Ӷ�ΪO(n * log(m)), ����n = max(row, col)�������������
�����������ֵ,
 m�����������ĳ��ȣ����������ֵ����Сֵ�Ĳ
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
		if (getLowerCnt(matrix, row, col, mid) < k) { // ��������[l, mid]����С��k��˵����kС����һ������mid
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
������ 10.09. ����������
����M��N����ÿһ�С�ÿһ�ж����������У����д�����ҳ�ĳԪ�ء�

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

ͨ������3,044�ύ����6,782
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


