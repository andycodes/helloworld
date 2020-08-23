/**
 * 桶排序：
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * 桶排序
 *
 * 参数说明：
 *     a -- 待排序数组
 *     n -- 数组a的长度
 *     bucketSize -- 数组a中最大值的范围
 */
void bucket_sort(int a[], int n, int bucketSize)
{
	int i, j;

	if (a==NULL || n<1 || bucketSize<1)
		return ;

	int buckets[bucketSize];
	memset(buckets, 0, bucketSize*sizeof(int));

	// 1. 计数
	for(i = 0; i < n; i++)
		buckets[a[i]]++;

	// 2. 排序:自然序
	for (i = 0, j = 0; i < bucketSize; i++)
		while( (buckets[i]--) >0 )//重复数字
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

	bucket_sort(a, ilen, 10); // 桶排序

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}

