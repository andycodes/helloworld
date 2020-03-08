/**
���ȶ���---�����(��С��)
��С�ѣ������ļ�ֵ�����жѽ���ֵ����С�ߣ�
��ÿ������ֵ�����亢�ӵ�ֵС��
����һ����ȫ������,�������ǿ�
���н���ֵ���ǲ������亢�ӽ���ֵ
ÿһ����������Ҳ��һ����

��С�ѵ��ŵ��������Ķ�̬��ά���ԡ�

��ǰʵ���Ǵ����ظ���

 */

#include <stdio.h>
#include <stdlib.h>

typedef long int HEAP_DTYPE;

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )


typedef struct minHeap{
	long int cnt;
	long int size;
	HEAP_DTYPE heap[0];
}minHeap;


int minHeapGetIndex(minHeap *H, HEAP_DTYPE data)
{
	long int i=0;

	for(i=0; i<H->cnt; i++)
		if (data==H->heap[i])
			return i;

	return -1;
}


int minHeapisEmpty(minHeap *H)
{
	return H->cnt == 0;
}


long int minHeapGetSize(minHeap *H)
{
	return H->cnt;
}


/*
 * ��С�ѵ����µ����㷨
 *
 * ע������ʵ�ֵĶ��У�
 ��N���ڵ��
 ���ӵ�����ֵ��(2N+1)��
 �Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
 *     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void minheap_filterdown(minHeap *H, long int start, long int end)
{
	long int curNode = start;
	long int left = 2*curNode + 1;
	HEAP_DTYPE tmp = H->heap[curNode];

	while(left <= end) {
		// "left"�����ӣ�"left+1"���Һ���
		if(left < end && H->heap[left] > H->heap[left+1])
			left++;		// ������������ѡ���С�ߣ���H->heap[left+1]

		if(tmp <= H->heap[left])
			break;		//��������
		else {
			H->heap[curNode] = H->heap[left];
			curNode = left;
			left = 2*left + 1;
		}
	}

	H->heap[curNode] = tmp;
}


/*
 * ɾ����С���е�data
 */
int minheap_remove(minHeap *H, long int data)
{
	long int index;
	if(H->cnt == 0)
		return  -1;

	index = minHeapGetIndex(H, data);
	if (index== -1)
		return -1;

	H->heap[index] = H->heap[--H->cnt];		// �����Ԫ���
	// ��index��λ�ÿ�ʼ�������µ���Ϊ��С��
	minheap_filterdown(H, index, H->cnt-1);

	return 0;
}


long int minHeapPop(minHeap *H)
{
	HEAP_DTYPE min;

	if(minHeapisEmpty(H))
		return 0;

	min = H->heap[0];
	minheap_remove(H, min);
	return min;
}


/*
 * ��С�ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
 *
 * ����˵����
 *     start -- ���ϵ��ڵ����ʼλ��
 (һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void filter_up(minHeap *H, long int start)
{
	long int curNode = start;
	long int root = (curNode - 1)/2;		// ��(parent)����λ��
	HEAP_DTYPE tmp = H->heap[curNode];

	while(curNode > 0) {
		if(H->heap[root] <= tmp)
			break;
		else {
			H->heap[curNode] = H->heap[root];
			curNode = root;
			root = (root-1)/2;
		}
	}

	H->heap[curNode] = tmp;
}


int minHeapPush(minHeap *H, long int data)
{
	if(H->cnt >= H->size) {
		printf("heap is full\n");
		return -1;
	}

	H->heap[H->cnt] = data;// ��"����"���ڱ�β
	filter_up(H, H->cnt);
	H->cnt++;

	return 0;
}


/*
 * ��ӡ�����
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
 */
void minheap_print(minHeap *H)
{
	long int i;
	for (i=0; i<H->cnt; i++)
		printf("%ld ", H->heap[i]);
}


minHeap * minheap_init(long int size) {
	minHeap * H = (minHeap *)malloc(sizeof(minHeap) + sizeof(long int) * size);
	H->cnt = 0;
	H->size = size;
	return H;
}


int main(void)
{
	minHeap *H = minheap_init(1024);

	HEAP_DTYPE a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	long int i, len=LENGTH(a);

	printf("== minHeapPush: ");
	for(i=0; i<len; i++) {
		printf("%ld ", a[i]);
		minHeapPush(H, a[i]);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(H);

	i=15;
	minHeapPush(H, i);
	printf("\n== minHeapPush: %ld", i);
	printf("\n== minheap_print: \n10 15 30 50 20 70 40 80 60 90:\n");
	minheap_print(H);

	i=10;
	minheap_remove(H, i);
	printf("\n== minheap_remove: %ld", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(H);
	printf("\n");

	printf("\n minHeapPop test:\n");
	while(!minHeapisEmpty(H)) {
		printf(" %ld ", minHeapPop(H));
	}

	printf("\n");

	return 0;
}

