
/*
Interval Scheduling �����������

1) ����(�ܶೡ��)
2) ����

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
1029. ���ص���
������������������⣬
��˾���Ƚ��� 2N ����ȫ�����ŷ��� B �У�
��ѡ�� N ���˸ı����ǵ��г̣������Ƿ��� A �С�
���ѡ��ı�һ���˵��г̣�
��ô��˾������⸶�� price_A - price_B �ķ��ã�
������ÿ����ɸ���


������ŵķ����ǣ�ѡ�� price_A - price_B ��С�� N ���ˣ�
�����Ƿ��� A �У������˷��� B �С�
�㷨���� price_A - price_B ��С��������
��ǰ N ���˷��� A �У������˷��� B �У�
��������ܷ��á�
*/

struct obj{
    int a;
    int b;
    int diff;
};


int cmp_struct( const void *a , const void *b){
	struct obj *c = (struct obj *)a;
	struct obj *d = (struct obj *)b;

	return c->diff - d->diff;
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize){
        int i;
        struct obj ob[costsSize];
        int sum = 0;

        for(i = 0; i < costsSize; i++){
                ob[i].a = costs[i][0];
                ob[i].b = costs[i][1];
                ob[i].diff = ob[i].a - ob[i].b;
        }

	qsort(ob, costsSize, sizeof(struct obj), cmp_struct);
        for (i = 0;i<costsSize/2;i++){
            sum += ob[i].a;
        }

        for (i = costsSize/2;i<costsSize;i++){
            sum += ob[i].b;
        }

        return sum;
}


/*
121. ������Ʊ�����ʱ��
����һ�����飬
���ĵ� i ��Ԫ����һ֧������Ʊ�� i ��ļ۸�

��������ֻ�������һ�ʽ��ף������������һ֧��Ʊ����
���һ���㷨�����������ܻ�ȡ���������

ע���㲻���������Ʊǰ������Ʊ��
����: [7,1,5,3,6,4]
���: 5
����: �ڵ� 2 �죨��Ʊ�۸� = 1����ʱ�����룬
�ڵ� 5 �죨��Ʊ�۸� = 6����ʱ��������������� = 6-1 = 5 ��
     ע���������� 7-1 = 6, ��Ϊ�����۸���Ҫ��������۸�


����˼·�� ��Ʊ�������ԣ�
���������գ������۸� p1������۸� p2����������롢
����������׬ȡ��� p2-p1����ֵ������𣩡�
�������ǽ����գ� ������ǽ����չ�Ʊ�۸�ֱ�Ϊ
p1,p2,.....pn�����һ�������һ����������󣬼
pn-p1���ȼ���ÿ�춼�������
pn-p1=(p2-p1)+(p3-p2)+(p4-p3)+....+(pn-P(n-1))��
�����½������գ� ������������󣬼������Ǯ��
�㷨���̣�  ����������Ʊ�����ռ۸��б� price��
�������������ǽ����ն�������׬���������󣩣�
�����½������ն���������������Ǯ����
�� tmp Ϊ�� i-1 ��������� i ������׬ȡ������
�� tmp = prices[i] - prices[i - 1] �� ����������Ϊ�� tmp > 0��
��������������� profit��������Ϊ 00 ��Ϊ����
��ֱ�������� ������ɺ󣬷��������� profit��

*/
int maxProfit(int* prices, int pricesSize){
        int profit = 0;
        for (int i = 1; i <pricesSize; i++) {
            int tmp = prices[i] - prices[i - 1];
            if (tmp > 0) profit += tmp;
        }
        return profit;
}


/*
1221. �ָ�ƽ���ַ���
��һ����ƽ���ַ������У�'L' �� 'R' �ַ�����������ͬ�ġ�

����һ��ƽ���ַ��� s��
���㽫���ָ�ɾ����ܶ��ƽ���ַ�����

���ؿ���ͨ���ָ�õ���ƽ���ַ��������������

����������ָ�ƽ�⴮���õ������ܶ��ƽ�⴮��
����һ������̰���㷨�����⣬
���ʵ���λ�ýض�Դ���õ�ƽ���Ӵ���
�ضϺ�ǰ���Ӵ��ļ���������Ӱ�죨�޺�Ч�ԣ���
�����оֲ�������Ӽ�Ϊ��������Ž⡣
���˼·��

����һ��'L'��'R'�Ĳ�ֵ������diffCount��
����һ��ƽ���Ӵ�������count��
˳�����Դ���ַ�����L��diffCount+1������R��diffCount-1��
ÿ����һ���ַ����һ��diffCount�Ƿ�Ϊ0����Ϊ0��count+1
*/

int balancedStringSplit(char * s) {
	int diffCnt = 0;
	int count = 0;

	if (s == NULL)
		return 0;

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'L')
			diffCnt++;
		else
			diffCnt--;

		if (diffCnt == 0)
			count++;
	}

	return count;
}


/*
��������һλ�ܰ��ļҳ�����Ҫ����ĺ�����һЩС���ɡ�
���ǣ�ÿ���������ֻ�ܸ�һ����ɡ���ÿ������ i ��
����һ��θ��ֵ gi ���������ú���������θ�ڵı���
����С�ߴ磻����ÿ����� j ������һ���ߴ� sj ��
��� sj >= gi ��
���ǿ��Խ�������� j ��������� i ��
������ӻ�õ����㡣
���Ŀ���Ǿ���������Խ�������ĺ��ӣ�
�������������ֵ��

ע�⣺

����Լ���θ��ֵΪ����
һ��С�������ֻ��ӵ��һ����ɡ�

ʾ�� 1:

����: [1,2,3], [1,1]

���: 1

����:
�����������Ӻ�����С���ɣ�
3�����ӵ�θ��ֵ�ֱ��ǣ�1,2,3��
��Ȼ��������С���ɣ�
�������ǵĳߴ綼��1����ֻ����θ��ֵ��1�ĺ������㡣
������Ӧ�����1��
ʾ�� 2:

����: [1,2], [1,2,3]

���: 2

*/

int cmp_int ( const void *a , const void *b){
        return *(int *)a - *(int *)b;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){

	int ig = 0;
	int is = 0;
	int out = 0;

	qsort(g,gSize,sizeof(int),cmp_int);
	qsort(s,sSize,sizeof(int),cmp_int);

	while((ig < gSize) && (is < sSize)) {
		if (g[ig] <= s[is]) {
			out++;
			ig++;
			is++;
		}else {
			is++;
		}
	}

	return out;
}

/*
����һ���������� A������ֻ�������·�����
�ĸ����飺����ѡ��ĳ�������� i ���� A[i] �滻Ϊ -A[i]��
Ȼ���ܹ��ظ�������� K �Ρ�
�����ǿ��Զ��ѡ��ͬһ������ i����

�����ַ�ʽ�޸�����󣬷���������ܵ����͡�

*/
int cmp_int ( const void *a , const void *b){
        return *(int *)a - *(int *)b;
}

/*��һ�֣�ÿ��ȡ��ǰ������������
ȡ����Сֵ���ٶ�����*/
int largestSumAfterKNegations(int* A, int ASize, int K){
	int sum = 0;
	int tmp;

	if (A == NULL || ASize <= 0)
		return 0;

	for (int i = 0; i < K; i++) {
		qsort(A,ASize,sizeof(int),cmp_int);
		A[0] = -A[0];
	}

	for (int i = 0; i < ASize; i++) {
		sum += A[i];
	}

	return sum;
}

/*
��K����������3�������
1��kС�ڸ����ĸ�����ֱ�ӽ���С�ĸ���ȡ��
2��k���ڸ������������Ƕ�����Ĳ�����ż����
���и���ȡ����ֱ�ӷ��غ�
3����������Ĳ�����������
���Ǹ����������򣬰���С����ȡ�������غ�
*/

#define m_sum()\
	for (int i = 0; i < ASize; i++) {\
		sum += A[i];\
	}\

int largestSumAfterKNegations(int* A, int ASize, int K){
	int tmp;
	int sum = 0;
	int i = 0;

	if (A == NULL || ASize <= 0)
		return 0;

	qsort(A,ASize,sizeof(int),cmp_int);

	if (A[K -1] <= 0) {
		for (; i < K;i++) {
			A[i] = -A[i];
		}

		m_sum();
		return sum;
	}

	for (i = 0; i < K && A[i] < 0; i++) {
			A[i] = -A[i];
	}

	if ((K -i)%2 == 0) {
		m_sum();
		return sum;
	}

	qsort(A,ASize,sizeof(int),cmp_int);
	A[0] = -A[0];

	m_sum();
	return sum;
}


/*
870. ����ϴ��
����������С��ȵ����� A �� B��A �����
B �����ƿ��������� A[i] > B[i] ������ i ����Ŀ��������

���� A ���������У�ʹ������� B ��������󻯡�



ʾ�� 1��

���룺A = [2,7,11,15], B = [1,10,4,11]
�����[2,11,7,15]

*/
struct obj {
	int data;
	int index;
};

int cmp_struct( const void *a , const void *b){
	struct obj *c = (struct obj *)a;
	struct obj *d = (struct obj *)b;

	return c->data- d->data;
}

int* advantageCount(int* A, int ASize, int* B, int BSize, int* returnSize){
    int l = 0;
    int r = ASize - 1;
	struct obj *ao = (struct obj *)malloc(sizeof(struct obj) * ASize);
	struct obj *bo = (struct obj *)malloc(sizeof(struct obj) * BSize);
	int *ret = (int *)malloc(sizeof(int) * ASize);

	for (int i = 0; i < ASize; i++) {
		ao[i].data = A[i];
		ao[i].index = i;

		bo[i].data = B[i];
		bo[i].index = i;
	}

	qsort(ao, ASize, sizeof(struct obj), cmp_struct);
	qsort(bo, ASize, sizeof(struct obj), cmp_struct);
    	int j = BSize - 1;
	for (int i = 0; i < ASize; i++) {
		if (ao[i].data > bo[l].data) {
			ret[bo[l].index] = ao[i].data;
            		l++;
		} else {
			ret[bo[r].index] = ao[i].data;
            		r--;
		}
	}

	*returnSize = ASize;
	return ret;
}

/*
1282. �û�����
�� n λ�û��μӻ�����ǵ� ID �� 0 �� n - 1��ÿλ�û��� ǡ�� ����ĳһ�û��顣����һ������Ϊ n ������ groupSizes�����а���ÿλ�û��������û���Ĵ�С�����㷵���û�������������ڵ��û����Լ�ÿ�������û��� ID����

������κ�˳�򷵻ؽ��������ID ��˳��Ҳ�������ơ����⣬��Ŀ���������ݱ�֤���ٴ���һ�ֽ��������



ʾ�� 1��

���룺groupSizes = [3,3,3,3,3,1,3]
�����[[5],[0,1,2],[3,4,6]]
���ͣ�
�������ܵĽ�������� [[2,1,6],[5],[0,4,3]] �� [[5],[0,6,2],[4,3,1]]��


����һ����ϣӳ��
���������û� x �� y����� groupSize[x] != groupSize[y]�������û���Ĵ�С��ͬ����ô����һ������ͬһ���û����С�������ǿ������ȶ����е��û�����һ�Ρ��ַ��顿����һ����ϣӳ�䣨HashMap�����洢���е��û�����ϣӳ���м�ֵ��Ϊ (gsize, users)������ gsize ��ʾ�û���Ĵ�С��users ��ʾ�����û����СΪ gsize���� groupSize[x] == gsize �������û����������������ǾͰ������û����С��ͬ���û�����ʱ������ͬһ�����С�

�ڽ����ˡ��ַ��顿�����ǿ��Խ�ÿ����ֵ�� (gsize, users) �е� users ���С�ϸ���顿��������Ŀ��֤�˸������������ٴ���һ�ַ�����������ǵġ�ϸ���顿���Ա�úܼ򵥣�ֻҪÿ�δ� users ��ȡ�� gsize ���û��������Ƿ���һ�����оͿ����ˡ��ڽ��������еġ�ϸ���顿�����Ǿ͵õ���һ�����������ķ��鷽����

*/
struct bigcase {
	int cnt;
	int idx[1024];
};

int** groupThePeople(int* groupSizes, int groupSizesSize,
	int* returnSize, int** returnColumnSizes) {
	int ** res = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;

	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	struct bigcase array[groupSizesSize + 1];
	memset(array, 0, sizeof(array));

	for (int i = 0; i < groupSizesSize; i++) {
		int curSize = groupSizes[i];
		array[curSize].idx[array[curSize].cnt++] = i;
	}

	for (int i = 0; i < groupSizesSize + 1; i++) {
		int k = 0;
		while(array[i].cnt - k * i > 0) {
			res[*returnSize] = (int *)calloc(i, sizeof(int));
			for(int j = 0; j < i ; j++) {
				res[*returnSize][j] = array[i].idx[j + k * i];
			}
			(*returnColumnSizes)[*returnSize] = i;
			(*returnSize)++;
			k++;
		}
	}

	return res;
}
