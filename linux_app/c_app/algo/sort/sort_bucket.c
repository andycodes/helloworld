/**
 * Ͱ����
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
 *     bucketSize -- ����a�����ֵ�ķ�Χ
 */
void bucket_sort(int a[], int n, int bucketSize)
{
	int i, j;

	if (a==NULL || n<1 || bucketSize<1)
		return ;

	int buckets[bucketSize];
	memset(buckets, 0, bucketSize*sizeof(int));

	// 1. ����
	for(i = 0; i < n; i++)
		buckets[a[i]]++;

	// 2. ����:��Ȼ��
	for (i = 0, j = 0; i < bucketSize; i++)
		while( (buckets[i]--) >0 )//�ظ�����
			a[j++] = i;
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

