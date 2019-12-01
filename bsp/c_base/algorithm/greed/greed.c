#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
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

void bubble_sort(struct obj  *data,int size)
{
    for (int i=size;i>0;i--)
    {
        for (int j=0;j<(i-1);j++)
            {
                if (data[j].diff >data[j+1].diff)
                    {
                        struct obj  tmp;
                        tmp=data[j];
                        data[j]=data[j+1];
                        data[j+1]=tmp;
                    }
            }
       }
}



int twoCitySchedCost(int costs[][2], int costsSize, int* costsColSize){
        int i;
        struct obj ob[100];
        int sum = 0;

        for(i = 0; i < costsSize; i++){
                ob[i].a = costs[i][0];
                ob[i].b = costs[i][1];
                ob[i].diff = ob[i].a - ob[i].b;
        }

        bubble_sort(ob,costsSize);

        for (i = 0;i<costsSize/2;i++){
            sum += ob[i].a;
        }

        for (i = costsSize/2;i<costsSize;i++){
            sum += ob[i].b;
        }

        return sum;
}


int main()
{
    int a[][2] = {{259,770},{448,54},{926,667},{184,139},{840,118},{577,469}};
    int b;
    printf("%d\n",twoCitySchedCost(a,6,&b));
    return 0;
}


/*
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
��һ����ƽ���ַ������У�'L' �� 'R' �ַ�����������ͬ�ġ�

����һ��ƽ���ַ��� s�����㽫���ָ�ɾ����ܶ��ƽ���ַ�����

���ؿ���ͨ���ָ�õ���ƽ���ַ��������������

����������ָ�ƽ�⴮���õ������ܶ��ƽ�⴮������һ������̰���㷨�����⣬���ʵ���λ�ýض�Դ���õ�ƽ���Ӵ����ضϺ�ǰ���Ӵ��ļ���������Ӱ�죨�޺�Ч�ԣ��������оֲ�������Ӽ�Ϊ��������Ž⡣
���˼·��

����һ��'L'��'R'�Ĳ�ֵ������diffCount������һ��ƽ���Ӵ�������count��
˳�����Դ���ַ�����L��diffCount+1������R��diffCount-1��
ÿ����һ���ַ����һ��diffCount�Ƿ�Ϊ0����Ϊ0��count+1

*/

int balancedStringSplit(char * s){
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
��������һλ�ܰ��ļҳ�����Ҫ����ĺ�����һЩС���ɡ����ǣ�ÿ���������ֻ�ܸ�һ����ɡ���ÿ������ i ������һ��θ��ֵ gi ���������ú���������θ�ڵı��ɵ���С�ߴ磻����ÿ����� j ������һ���ߴ� sj ����� sj >= gi �����ǿ��Խ�������� j ��������� i ��������ӻ�õ����㡣���Ŀ���Ǿ���������Խ�������ĺ��ӣ��������������ֵ��

ע�⣺

����Լ���θ��ֵΪ����
һ��С�������ֻ��ӵ��һ����ɡ�

ʾ�� 1:

����: [1,2,3], [1,1]

���: 1

����:
�����������Ӻ�����С���ɣ�3�����ӵ�θ��ֵ�ֱ��ǣ�1,2,3��
��Ȼ��������С���ɣ��������ǵĳߴ綼��1����ֻ����θ��ֵ��1�ĺ������㡣
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


