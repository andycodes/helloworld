#include <stdio.h>
#include <stdlib.h>


struct MinHeap;
typedef struct MinHeap * MinPriorityQueue;
typedef int ElementType;


/* ±ê¼Ç½Úµã£¬ÀàËÆÓÚÁ´±íÖÐµÄ±íÍ·½Úµã
 * ¸ÃÖµ±ØÐëÐ¡ÓÚËùÓÐ×îÐ¡¶ÑÖÐµÄÔªËØ£¬ÉèÆäÖµÎª-1
 */
#define SentinelElement -1

/*
 * Ê¹ÓÃÊý×éÊµÏÖ¶Ñ
 *
 * capacity Êý×éµÄ×î´óÈÝÁ¿
 * size     Êý×éµÄ³¤¶È
 * elements ¶ÑÖÐµÄÔªËØ´æ·ÅµÄÊý×é
 */
struct MinHeap
{
    int capacity;
    int size;
    ElementType *elements; // ¶ÑµÄÔªËØ¸öÊýÎªsize£¬Êµ¼ÊÉÏÓÃÀ´´æ´¢µÄÊý×éµÄ³¤¶ÈÎªsize + 1£¬»¹°üÀ¨Ò»¸ösentinelÔªËØ
};

void
PQueueNULLWarning()
{
    printf("Warning: Minimum Priority Queue is NULL");
}

void
outOfSpaceFatalError()
{
    printf("Fatal Error: Out of space");
    abort();
}

MinPriorityQueue
initialize(int maxElements)
{
    MinPriorityQueue pqueue;

    if (maxElements <= 0)
    {
        printf("Fail to initialize: maxElements <= 0");
        return NULL;
    }

    pqueue = malloc(sizeof(struct MinHeap));
    if (pqueue == NULL)
        outOfSpaceFatalError();

    // Êý×éµÄµÚ0¸öÔªËØÊÇ¸ösentinel±ê¼Ç½Úµã£¬¼ÆÈëÊý×éÈÝÁ¿ÖÐ£¬µ«²»¼ÆÈëcapcaity»òsizeÖÐ
    pqueue->size = 0;
    pqueue->capacity = maxElements;
    pqueue->elements = malloc(sizeof(ElementType) * (pqueue->capacity + 1));
    if (pqueue->elements == NULL)
        outOfSpaceFatalError();
    else
        pqueue->elements[0] = SentinelElement;

    return pqueue;
}

void
destroy(MinPriorityQueue pqueue)
{
    if (pqueue != NULL)
    {
        // ÔÚGNU99±ê×¼ÖÐ£¬free(NULL)Ê²Ã´¶¼²»×öÖ±½Ó·µ»Ø£¬ËùÒÔ²»ÓÃÅÐ¶Ïpqueue->elementsÊÇ·ñÎªNULL
        free(pqueue->elements);
        free(pqueue);
    }
}

void
makeEmpty(MinPriorityQueue pqueue)
{
    if (pqueue != NULL)
        pqueue->size = 0;
    else
        PQueueNULLWarning();
}

/*
 * ²åÈëÊ±£¬¶ÑÖÐµÄÔªËØÖ´ÐÐÏÂÂË²Ù×÷
 * É¾³ýÊ±£¬¶ÑÖÐµÄÔªËØÖ´ÐÐÉÏÂË²Ù×÷
 */

/*
 * ²åÈëµÄÊ±¼ä¸´ÔÓ¶ÈÎªO(log N)£¬NÎª×îÐ¡¶ÑÖÐµÄÔªËØ¸öÊý
 * Êµ¼ÊÉÏ£¬ÆäÆ½¾ùÖ´ÐÐÊ±¼äÎªO(1)
 */
void
insert(ElementType x, MinPriorityQueue pqueue)
{
    if (pqueue == NULL)
        PQueueNULLWarning();

    if (isFull(pqueue))
    {
        printf("Fail to insert: Priority Queue is Full");
        return;
    }
    else
    {
        int i;

        // sentinel elementÔÚÕâÀï×÷Îªelements[0]±»±È½Ï£¬ÊÇÑ­»·µÄÖÕÖ¹Ìõ¼þ
        for (i = ++pqueue->size; x < pqueue->elements[i / 2]; i /= 2)
            pqueue->elements[i] = pqueue->elements[i / 2]; // ÏÂÂË²Ù×÷
        pqueue->elements[i] = x;
    }
}

/*
 * É¾³ý²Ù×÷µÄÆ½¾ùÊ±¼äÎªO(log N)
 */
ElementType
deleteMin(MinPriorityQueue pqueue)
{
    if (pqueue == NULL)
    {
        PQueueNULLWarning();
        return SentinelElement;
    }

    if (isEmpty(pqueue))
    {
        printf("Fail to delete: Priority Queue is Empty");
        return SentinelElement;
    }

    int i, child;
    ElementType minElement, lastElement;

    // ×¢Òâ¶ÔÄ³¸ö½Úµã½øÐÐÉÏÂË²Ù×÷Ê±£¬ÒªÅÐ¶Ï¸Ã½ÚµãÊÇÓÐÁ½¸ö¶ù×Ó»¹ÊÇÒ»¸ö¶ù×Ó
    minElement = pqueue->elements[1];
    lastElement = pqueue->elements[pqueue->size--];
    for (i = 1; i * 2 <= pqueue->size; i = child)
    {
        child = i * 2;

        // ½ÚµãiÖ»ÓÐÒ»¸ö¶ù×ÓÊ±±ØÓÐi * 2 = pqueue->size
        if (child < pqueue->size && pqueue->elements[child] > pqueue->elements[child + 1])
            child++;

        if (lastElement < pqueue->elements[child])
            break;
        else
            pqueue->elements[i] = pqueue->elements[child]; // ÉÏÂË²Ù×÷
    }
    pqueue->elements[i] = lastElement;

    return minElement; // ·µ»Ø±»É¾³ýµÄÔªËØ
}

/*
 * Ö´ÐÐÊ±¼ä£ºO(1)
 */
ElementType
findMin(MinPriorityQueue pqueue)
{
    if (pqueue == NULL)
    {
        PQueueNULLWarning();
        return SentinelElement;
    }
    else
        return pqueue->elements[1];
}

int
isEmpty(MinPriorityQueue pqueue)
{
    if (pqueue == NULL)
    {
        PQueueNULLWarning();
        return -1;
    }
    else
        return (pqueue->size == 0);
}

int
isFull(MinPriorityQueue pqueue)
{
    if (pqueue == NULL)
    {
        PQueueNULLWarning();
        return -1;
    }
    else
        return (pqueue->size == pqueue->capacity);
}

void
percolateDown(int *arr, int len, int i)
{
    int child;
    int n = len - 1;
    ElementType tmp;

    for (tmp = arr[i]; i * 2 < n; i = child)
    {
        child = i * 2;
        if (child < n && arr[child] > arr[child + 1])
            child++;

        if (tmp > arr[child])
            arr[i] = arr[child];
        else
            break;
    }
    arr[i] = tmp;
}

MinPriorityQueue
buildHeap_percolate(int *arr, int n)
{
    if (arr == NULL)
    {
        printf("Error: Array is NULL");
        return NULL;
    }

    MinPriorityQueue pqueue;
    pqueue = malloc(sizeof(struct MinHeap));

    if (pqueue == NULL)
        outOfSpaceFatalError();
    ElementType *elements = malloc(sizeof(ElementType) * (n + 1));
    if (elements == NULL)
        outOfSpaceFatalError();

    int i;
    for (i = 1; i <= n; i++)
        elements[i] = arr[i - 1];
    elements[0] = SentinelElement;

    for (i = n / 2; i > 0; i--)
        percolateDown(elements, n + 1, i);

    pqueue->elements = elements;
    pqueue->size = n;
    pqueue->capacity = n * 2;

    return pqueue;
}

/*
 * Í¨¹ýn´Î²åÈëÔªËØ½¨Á¢¶Ñ£¬ÓÉÓÚÃ¿´Î²åÈëµÄÆ½¾ùÖ´ÐÐÊ±¼äÎªO(1)£¬ËùÒÔ½¨¶ÑÆ½¾ùÊ±¼äÎªO(N)
 */
MinPriorityQueue
buildHeap_insert(int *arr, int n)
{
    MinPriorityQueue pqueue;

    if (arr == NULL)
    {
        printf("Array is NULL, fail to build heap");
        return NULL;
    }

    pqueue = initialize(n * 2);
    for (int i = 0; i < n; i++)
        insert(arr[i], pqueue);

    return pqueue;
}

void
printMinPriorityQueue(MinPriorityQueue pqueue)
{
    if (pqueue == NULL)
    {
        PQueueNULLWarning();
        return;
    }

    if (pqueue->elements == NULL)
    {
        printf("Fail to print: Elements of priority queue is NULL");
        return;
    }

    if (isEmpty(pqueue))
    {
        printf("Empty Prioirty Queue\n");
        return;
    }

    printf("Priority Queue\n");
    for (int i = 1; i <= pqueue->size; i++)
        printf("Element[%d] = %d\n", i, pqueue->elements[i]);
    printf("\n");
}


void
buildHeapTest()
{
    int a[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    MinPriorityQueue pqueue_ins = buildHeap_insert(a, 9);
    MinPriorityQueue pqueue_per = buildHeap_percolate(a, 9);
    printMinPriorityQueue(pqueue_ins);
    printMinPriorityQueue(pqueue_per);
}

int main(int argc, const char * argv[])
{
    buildHeapTest();

    return 0;
}
