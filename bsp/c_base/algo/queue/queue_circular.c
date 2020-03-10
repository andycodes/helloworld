typedef struct {
    unsigned int head;
    unsigned int tail;
    unsigned int cap;
    int values[0];
} MyCircularQueue;

/** Initialize your data structure here. Set the size of the queue to be k. */

bool myCircularQueueIsEmpty(MyCircularQueue* obj);
bool myCircularQueueIsFull(MyCircularQueue* obj);

MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue *obj = (MyCircularQueue*)calloc(1, sizeof(MyCircularQueue) + k * sizeof(int));
    obj->head = 0;
    obj->tail = k;
    obj->cap = k;
    return obj;
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj)) return false;
    obj->values[(obj->head++) % obj->cap] = value;
    return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return false;
    obj->tail ++;
    return true;
}

/** Get the front item from the queue. */
int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return -1;
    return obj->values[(obj->tail) % obj->cap];
}

/** Get the last item from the queue. */
int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return -1;
    return obj->values[(obj->head-1) % obj->cap];
}

/** Checks whether the circular queue is empty or not. */
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return ((unsigned int)(obj->tail - obj->head) == obj->cap);
}

/** Checks whether the circular queue is full or not. */
bool myCircularQueueIsFull(MyCircularQueue* obj) {
  return (obj->head == obj->tail);
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj);
}


/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);

 * bool param_2 = myCircularQueueDeQueue(obj);

 * int param_3 = myCircularQueueFront(obj);

 * int param_4 = myCircularQueueRear(obj);

 * bool param_5 = myCircularQueueIsEmpty(obj);

 * bool param_6 = myCircularQueueIsFull(obj);

 * myCircularQueueFree(obj);
*/