/**
 * �����(��С��)
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

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )


#define HeapSize 128
typedef struct minHeap{
	int heap[HeapSize];
	int cnt;
}minHeap;


/*
 * ����data�ڶ�����е�����
 *
 * ����ֵ��
 *     ���� -- ����data�������е�����
 *     ������ -- -1
 */
int get_index(minHeap *H, int data)
{
	int i=0;

	for(i=0; i<H->cnt; i++)
		if (data==H->heap[i])
			return i;

	return -1;
}

/*
 * ��С�ѵ����µ����㷨
 *
 * ע������ʵ�ֵĶ��У�
 ��N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
 *     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void minheap_filterdown(minHeap *H, int start, int end)
{
    int c = start; 	 	// ��ǰ(current)�ڵ��λ��
    int l = 2*c + 1; 	// ��(left)���ӵ�λ��
    int tmp = H->heap[c];	// ��ǰ(current)�ڵ�Ĵ�С

    while(l <= end)
    {
		// "l"�����ӣ�"l+1"���Һ���
        if(l < end && H->heap[l] > H->heap[l+1])
            l++;		// ������������ѡ���С�ߣ���H->heap[l+1]
        if(tmp <= H->heap[l])
            break;		//��������
        else
        {
            H->heap[c] = H->heap[l];
            c = l;
            l = 2*l + 1;
        }
    }
    H->heap[c] = tmp;
}


/*
 * ɾ����С���е�data
 *
 * ����ֵ��
 *      0���ɹ�
 *     -1��ʧ��
 */
int minheap_remove(minHeap *H, int data)
{
	int index;
	// ���"��"�ѿգ��򷵻�-1
	if(H->cnt == 0)
		return -1;

	// ��ȡdata�������е�����
	index = get_index(H, data);
	if (index==-1)
		return -1;

	H->heap[index] = H->heap[--H->cnt];		// �����Ԫ���
	// ��index��λ�ÿ�ʼ�������µ���Ϊ��С��
	minheap_filterdown(H, index, H->cnt-1);

	return 0;
}

int isEmpty(minHeap *H)
{
	return H->cnt == 0;
}


int minHeapGetSize(minHeap *H)
{
	return H->cnt;
}

//С���ѵ�ɾ��
int minHeapPop(minHeap *H) {
	int min;

	if(isEmpty(H))
		return 0;

	min = H->heap[0];
	minheap_remove(H, min);
	return min;
}


/*
 * ��С�ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
 *
 * ע������ʵ�ֵĶ��У�
 ��N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���ϵ��ڵ����ʼλ��
 (һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void filter_up(minHeap *H, int start)
{
    int c = start;			// ��ǰ�ڵ�(current)��λ��
    int p = (c-1)/2;		// ��(parent)����λ��
    int tmp = H->heap[c];		// ��ǰ�ڵ�(current)�Ĵ�С

    while(c > 0)
    {
        if(H->heap[p] <= tmp)
            break;
        else
        {
            H->heap[c] = H->heap[p];
            c = p;
            p = (p-1)/2;
        }
    }
    H->heap[c] = tmp;
}

/*
 * ��data���뵽�������
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
 */
int minHeapPush(minHeap *H, int data)
{
	// ���"��"�������򷵻�
	if(H->cnt >= HeapSize) {
		printf("heap is full\n");
		return -1;
	}

	H->heap[H->cnt] = data;		// ��"����"���ڱ�β
	filter_up(H, H->cnt);			// ���ϵ�����
	H->cnt++;					// �ѵ�ʵ������+1

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
	int i;
	for (i=0; i<H->cnt; i++)
		printf("%d ", H->heap[i]);
}


void minheap_init(minHeap *H) {
	H->cnt = 0;
}


int main(void)
{
	minHeap H;
	minheap_init(&H);

	int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	int i, len=LENGTH(a);

	printf("== minHeapPush: ");
	for(i=0; i<len; i++) {
		printf("%d ", a[i]);
		minHeapPush(&H, a[i]);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(&H);

	i=15;
	minHeapPush(&H, i);
	printf("\n== minHeapPush: %d", i);
	printf("\n== minheap_print: \n10 15 30 50 20 70 40 80 60 90:\n");
	minheap_print(&H);

	i=10;
	minheap_remove(&H, i);
	printf("\n== minheap_remove: %d", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(&H);
	printf("\n");

	printf("\n minHeapPop test:\n");
	while(!isEmpty(&H)) {
		printf(" %d ", minHeapPop(&H));
	}

	printf("\n");

	return 0;
}
