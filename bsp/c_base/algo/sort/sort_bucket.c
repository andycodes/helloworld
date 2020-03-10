/**
 * Ͱ����C ����
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * Ͱ����
 *
 * ����˵����
 *     a -- ����������
 *     n -- ����a�ĳ���
 *     max -- ����a�����ֵ�ķ�Χ
 */
void bucket_sort(int a[], int n, int max)
{
	int i, j;
    int *buckets;

    if (a==NULL || n<1 || max<1)
        return ;

    // ����һ������Ϊmax������buckets�����ҽ�buckets�е��������ݶ���ʼ��Ϊ0��
    if ((buckets=(int *)malloc(max*sizeof(int)))==NULL)
        return ;
    memset(buckets, 0, max*sizeof(int));

	// 1. ����
    for(i = 0; i < n; i++)
        buckets[a[i]]++;

	// 2. ����
	for (i = 0, j = 0; i < max; i++)
		while( (buckets[i]--) >0 )
			a[j++] = i;

	free(buckets);
}

void main()
{
	int i;
	int a[] = {8,2,3,4,3,6,6,3,9};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	bucket_sort(a, ilen, 10); // Ͱ����

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
