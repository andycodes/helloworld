#include "stdio.h"
#include "stdlib.h"


/*
��С�ѣ������ļ�ֵ�����жѽ���ֵ����С�ߣ�
��ÿ������ֵ�����亢�ӵ�ֵС��
����һ����ȫ������,�������ǿ�
���н���ֵ���ǲ������亢�ӽ���ֵ
ÿһ����������Ҳ��һ����
*/

#define HeapSize 128


typedef struct minHeap{
	int heap[HeapSize];    //���С������Ԫ�ص�����
	int n;                  //С���ѵ�ǰԪ�صĸ�������ʼֵΪ0
}minHeap;



/*�Զ����µ����㷨
�������µ������ڵ����Ĺ�����Ҫ����
�ڵ��������������Ϊ��С��
*/
void shifDown(minHeap *H, int m) {
	//m�ǿ�ʼ�����Ľ��,n�ǵ��������ĵ�
	int tmp = H->heap[m];  //j��i������Ů
	for (int j = 2 * m + 1; j <= H->n-1; j=2*j+1) {
		if (j<H->n-1 && H->heap[j] > H->heap[j + 1])
			j++;

		if (tmp <= H->heap[j])
			break;
		else {//��ǰ���ڵ�����ӽڵ�-->����
			tmp = H->heap[m];
			H->heap[m] = H->heap[j];
			H->heap[j] = tmp;
			m = j;
		}
	}
}


//�𲽹���С����
//�������Ǵ��µ��ϣ�������ʱ���Ǵ�������
void createMinHeap(minHeap *H, int arr[], int n) {
	/*init*/
	for ( int i = 0; i < n; i++)
		H->heap[i] = arr[i];
	H->n = n;

	//�Ե�����������С����
	for (int i = (H->n - 2) / 2; i >=0;i--) {
		shifDown(H,i);                       //�ֲ���������ɸѡ
	}
}


/*�Ե����ϵ���С����*/
void shifUp(minHeap *H,int start) {
	int j= start;
	int i = (j - 1) / 2;
	int tmp = H->heap[start];

	while (j>0) {
		if (H->heap[i] <= tmp)
			break;
		else {
			H->heap[j] = H->heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}

	H->heap[j] = tmp;
}


//С���ѵĲ���,���þֲ����¶��ϵõ����㷨
void Insert(minHeap *H,int x) {
	if (H->n == HeapSize) {
		printf("heap is full\n");
	}

	H->heap[H->n] = x;

	shifUp(H, H->n);

	H->n++;
}


//С���ѵ�ɾ��
int Remove(minHeap *H) {
	int min;
	if (!H->n)
		return 0;               //�ѿշ���0
	min = H->heap[0];
	H->heap[0] = H->heap[H->n - 1];
	H->n--;
	 //�Ե�����������С����
	for (int i = (H->n - 2) / 2; i >= 0; i--) {
		shifDown(H, i); //�ֲ���������ɸѡ
	}
	return min;
}


int main() {
	int arr[8] = { 53,17,78,9,45,65,87,23};
	minHeap H;

	createMinHeap(&H,arr, sizeof(arr)/sizeof(int));

	printf("create min heap\n");
	for (int i = 0; i < 8; i++) {
		printf(" %d ",H.heap[i]);
	}

	printf("\n insert 10\n");
	Insert(&H,10);
	for (int i = 0; i < 9; i++) {
		printf(" %d ", H.heap[i]);
	}

	int x;
	x=Remove(&H);
	printf("\n del \n");
	printf("del data is :%d\n",x);
	printf("after del \n");
	for (int i = 0; i < 8; i++) {
		printf(" %d ", H.heap[i]);
	}
	printf(" \n");
	return 0;
 }
