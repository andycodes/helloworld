#include "stdio.h"
#include "stdlib.h"

typedef int ElementType;
struct HeapStruct {
    //指向一个数组
    ElementType *Element;
    //堆当前元素的个数
    int size;
    //堆的最大容量
    int capacity;
};
typedef struct HeapStruct *MaxHeap;


int maxIndex(int left, int right, MaxHeap heap);

MaxHeap  initHeap(int *arr, int size,  int maxCapacity) {
	MaxHeap heap = (MaxHeap)malloc(sizeof(struct HeapStruct ));
	heap->capacity = maxCapacity;
	heap->Element = (ElementType *)malloc(sizeof(ElementType) * (maxCapacity+1));
	heap->size = size;
	//第一个位置不存任何数据,交换结点时可以作为中间变量
	heap->Element[0] = 0;
	//构建完全二叉树
	for (int i = 0; i < size; i++) {
		heap->Element[i+1] = arr[i];
	}

    //寻找最后一个结点的父结点,作为初始值
    for (int pIndex = heap->size / 2; pIndex >= 1; pIndex--) {
        int tmp = pIndex;
/*表示该结点有孩子结点-->当该结点时叶子结点时,循环结束*/
        while ((tmp<<1) <= heap->size) {
            //寻找这个结点的最大子结点
            int maxChildIndex = 0;
            if ((tmp<<1) + 1 > heap->size) { //没有右孩子,则左孩子就是最大子结点
                maxChildIndex = (tmp<<1);
            } else {//从左右孩子中寻找最大子结点
                maxChildIndex = maxIndex(tmp<<1,  (tmp<<1) + 1, heap);
            }
            //比较最大子结点和当前父结点,
            //如果父结点的值小于最大子结点的值,则交换两个结点
            if (heap->Element[tmp] < heap->Element[maxChildIndex]) {
                //交换两个结点
                heap->Element[0] = heap->Element[tmp];
                heap->Element[tmp] = heap->Element[maxChildIndex];
                heap->Element[maxChildIndex] = heap->Element[0];
                heap->Element[0] = 0;
                tmp = maxChildIndex;
            } else {
                break;//当该结点不需要在交换时,结束向下查找
            }
        }
    }

	return heap;
}

int maxIndex(int left, int right, MaxHeap heap) {
    return heap->Element[left] > heap->Element[right] ? left : right;
}


/*
最大堆中插入一个结点
原理:现在堆的最后增加一个结点,然后沿这堆树上升.
*/
void maxHeapInsert(ElementType e, MaxHeap heap) {
    //检查是否到达了堆的最大容量
    if (heap->capacity == heap->size) {
        return ;
    }

    heap->size++;
    heap->Element[heap->size] = e;
    for (int sIndex = heap->size; sIndex > 1;) {
        //寻找这个结点的父结点
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
最大堆中删除一个元素
原理:将堆的最后的结点提到根结点，
然后删除最大值，然后再把新的根结点向下进行调整,
直到找到其符合的的位置.
*/
void maxHeapPopE(MaxHeap heap, ElementType *e) {
    if (heap->size == 0) {
        return;
    }
    *e = heap->Element[1];
    heap->Element[1] = heap->Element[heap->size];
    heap->size--;
    int pIndex = 1;
    while (pIndex <<1 <= heap->size) { //有子结点
        int maxChild = 0;
        if ((pIndex << 1) + 1 > heap->size) { //没有右孩子
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