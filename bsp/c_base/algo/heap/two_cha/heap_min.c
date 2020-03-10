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


int minHeapGetIndex(minHeap *mh, HEAP_DTYPE data)
{
	long int i=0;

	for(i=0; i<mh->cnt; i++)
		if (data==mh->heap[i])
			return i;

	return -1;
}


bool minHeapisEmpty(minHeap *mh)
{
	return mh->cnt == 0;
}

bool minHeapisFull(minHeap *mh)
{
	printf("heap is full\n");
	return mh->cnt == mh->size;
}


long int minHeapGetSize(minHeap *mh)
{
	return mh->cnt;
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
static void minheap_filterdown(minHeap *mh, long int start, long int end)
{
	long int curNode = start;
	long int left = 2*curNode + 1;
	HEAP_DTYPE tmp = mh->heap[curNode];

	while(left <= end) {
		// "left"�����ӣ�"left+1"���Һ���
		if(left < end && mh->heap[left] > mh->heap[left+1])
			left++;		// ������������ѡ���С�ߣ���mh->heap[left+1]

		if(tmp <= mh->heap[left])
			break;		//��������
		else {
			mh->heap[curNode] = mh->heap[left];
			curNode = left;
			left = 2*left + 1;
		}
	}

	mh->heap[curNode] = tmp;
}


/*
 * ɾ����С���е�data
 */
int minheap_remove(minHeap *mh, long int data)
{
	long int index;
	if(mh->cnt == 0)
		return  -1;

	index = minHeapGetIndex(mh, data);
	if (index== -1)
		return -1;

	mh->heap[index] = mh->heap[--mh->cnt];		// �����Ԫ���
	// ��index��λ�ÿ�ʼ�������µ���Ϊ��С��
	minheap_filterdown(mh, index, mh->cnt-1);

	return 0;
}


long int minHeapPop(minHeap *mh)
{
	HEAP_DTYPE min;

	if(minHeapisEmpty(mh))
		return 0;

	min = mh->heap[0];
	minheap_remove(mh, min);
	return min;
}


/*
 * ��С�ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
 *
 * ����˵����
 *     start -- ���ϵ��ڵ����ʼλ��
 (һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void filter_up(minHeap *mh, long int start)
{
	long int curNode = start;
	long int root = (curNode - 1)/2;		// ��(parent)����λ��
	HEAP_DTYPE tmp = mh->heap[curNode];

	while(curNode > 0) {
		if(mh->heap[root] <= tmp)
			break;
		else {
			mh->heap[curNode] = mh->heap[root];
			curNode = root;
			root = (root-1)/2;
		}
	}

	mh->heap[curNode] = tmp;
}

/*
�������һ��ʹ�õĲ��Խ������ˣ�percolate up����
��Ԫ���ڶ�������ֱ���ҳ���ȷ��λ��
�����ΪH,�������Ԫ��ΪX,������size+1��λ�ý���һ����Ѩ��
Ȼ��Ƚ�X�Ϳ�Ѩ�ĸ��׵Ĵ�С��
�ѡ���ĸ��ס����������Դ��ƽ���
����X�ŵ����ʵ�λ�ã���
*/
int minHeapPush(minHeap *mh, long int data)
{
	if(minHeapisFull(mh)) {
		return -1;
	}

	mh->heap[mh->cnt] = data;// ��"����"���ڱ�β
	filter_up(mh, mh->cnt);
	mh->cnt++;

	return 0;
}


/*
 * ��ӡ�����
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
 */
void minheap_print(minHeap *mh)
{
	long int i;
	for (i=0; i<mh->cnt; i++)
		printf("%ld ", mh->heap[i]);
}


minHeap * minheap_init(long int size)
{
	minHeap * mh = (minHeap *)malloc(sizeof(minHeap) + sizeof(HEAP_DTYPE) * size);
	mh->cnt = 0;
	mh->size = size;
	return mh;
}


void minheap_exit(minHeap * mh)
{
	free(mh);
	mh = NULL;
}

int main(void)
{
	minHeap *mh = minheap_init(1024);

	HEAP_DTYPE a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	long int i, len=LENGTH(a);

	printf("== minHeapPush: ");
	for(i=0; i<len; i++) {
		printf("%ld ", a[i]);
		minHeapPush(mh, a[i]);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(mh);

	i=15;
	minHeapPush(mh, i);
	printf("\n== minHeapPush: %ld", i);
	printf("\n== minheap_print: \n10 15 30 50 20 70 40 80 60 90:\n");
	minheap_print(mh);

	i=10;
	minheap_remove(H, i);
	printf("\n== minheap_remove: %ld", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(mh);
	printf("\n");

	printf("\n minHeapPop test:\n");
	while(!minHeapisEmpty(mh)) {
		printf(" %ld ", minHeapPop(mh));
	}

	printf("\n");

	return 0;
}

