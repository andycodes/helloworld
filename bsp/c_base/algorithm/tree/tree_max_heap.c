#include "stdio.h"
#include "stdlib.h"

typedef int ElementType;
struct HeapStruct {
    //ָ��һ������
    ElementType *Element;
    //�ѵ�ǰԪ�صĸ���
    int size;
    //�ѵ��������
    int capacity;
};
typedef struct HeapStruct *MaxHeap;


int maxIndex(int left, int right, MaxHeap heap);

MaxHeap  initHeap(int *arr, int size,  int maxCapacity) {
	MaxHeap heap = (MaxHeap)malloc(sizeof(struct HeapStruct ));
	heap->capacity = maxCapacity;
	heap->Element = (ElementType *)malloc(sizeof(ElementType) * (maxCapacity+1));
	heap->size = size;
	//��һ��λ�ò����κ�����,�������ʱ������Ϊ�м����
	heap->Element[0] = 0;
	//������ȫ������
	for (int i = 0; i < size; i++) {
		heap->Element[i+1] = arr[i];
	}

    //Ѱ�����һ�����ĸ����,��Ϊ��ʼֵ
    for (int pIndex = heap->size / 2; pIndex >= 1; pIndex--) {
        int tmp = pIndex;
/*��ʾ�ý���к��ӽ��-->���ý��ʱҶ�ӽ��ʱ,ѭ������*/
        while ((tmp<<1) <= heap->size) {
            //Ѱ�������������ӽ��
            int maxChildIndex = 0;
            if ((tmp<<1) + 1 > heap->size) { //û���Һ���,�����Ӿ�������ӽ��
                maxChildIndex = (tmp<<1);
            } else {//�����Һ�����Ѱ������ӽ��
                maxChildIndex = maxIndex(tmp<<1,  (tmp<<1) + 1, heap);
            }
            //�Ƚ�����ӽ��͵�ǰ�����,
            //���������ֵС������ӽ���ֵ,�򽻻��������
            if (heap->Element[tmp] < heap->Element[maxChildIndex]) {
                //�����������
                heap->Element[0] = heap->Element[tmp];
                heap->Element[tmp] = heap->Element[maxChildIndex];
                heap->Element[maxChildIndex] = heap->Element[0];
                heap->Element[0] = 0;
                tmp = maxChildIndex;
            } else {
                break;//���ý�㲻��Ҫ�ڽ���ʱ,�������²���
            }
        }
    }

	return heap;
}

int maxIndex(int left, int right, MaxHeap heap) {
    return heap->Element[left] > heap->Element[right] ? left : right;
}


/*
�����в���һ�����
ԭ��:���ڶѵ��������һ�����,Ȼ�������������.
*/
void maxHeapInsert(ElementType e, MaxHeap heap) {
    //����Ƿ񵽴��˶ѵ��������
    if (heap->capacity == heap->size) {
        return ;
    }

    heap->size++;
    heap->Element[heap->size] = e;
    for (int sIndex = heap->size; sIndex > 1;) {
        //Ѱ��������ĸ����
        int pIndex = sIndex / 2;
        if (heap->Element[pIndex] < heap->Element[sIndex]) {
            heap->Element[0] = heap->Element[pIndex];
            heap->Element[pIndex] = heap->Element[sIndex];
            heap->Element[sIndex] = heap->Element[0];
            heap->Element[0] = 0;
            sIndex = pIndex;
        } else {
            break;
        }
    }
}

/*
������ɾ��һ��Ԫ��
ԭ��:���ѵ����Ľ���ᵽ����㣬
Ȼ��ɾ�����ֵ��Ȼ���ٰ��µĸ�������½��е���,
ֱ���ҵ�����ϵĵ�λ��.
*/
void maxHeapPopE(MaxHeap heap, ElementType *e) {
    if (heap->size == 0) {
        return;
    }
    *e = heap->Element[1];
    heap->Element[1] = heap->Element[heap->size];
    heap->size--;
    int pIndex = 1;
    while (pIndex <<1 <= heap->size) { //���ӽ��
        int maxChild = 0;
        if ((pIndex << 1) + 1 > heap->size) { //û���Һ���
            maxChild = pIndex << 1;
        } else {
            maxChild = maxIndex(pIndex << 1, (pIndex << 1) + 1, heap);
        }
        if (heap->Element[pIndex] < heap->Element[maxChild]) {
            heap->Element[0] = heap->Element[pIndex];
            heap->Element[pIndex] = heap->Element[maxChild];
            heap->Element[maxChild] = heap->Element[0];
            heap->Element[0] = 0;
            pIndex = maxChild;
        } else {
            break;
        }
    }
}


int main() {
	int arr[] = { 5, 1, 13, 3, 16, 7, 10, 14, 6, 9 };

	MaxHeap heap = initHeap(arr, sizeof(arr) /sizeof(int), 20);

	maxHeapInsert(18, heap);
	printf("insert 18\n");
	for (int i = 1; i <= heap->size; i++) {
		printf("%d ",heap->Element[i]);
	}

	ElementType e;
	maxHeapPopE(heap, &e);
	printf("\npop e = %d\n",e);
	for (int i = 1; i <= heap->size; i++) {
		printf("%d ",heap->Element[i]);
	}

	printf("\n");

	return 0;
}