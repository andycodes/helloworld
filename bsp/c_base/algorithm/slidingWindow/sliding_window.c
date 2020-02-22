
/*
面试题59 - II. 队列的最大值
请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1

示例 1：

输入:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出: [null,null,null,2,1,2]
示例 2：

输入:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出: [null,-1,-1]

*/

/*
我们维护一个正常的队列queue，这样push_back, pop_front 直接操作正常队列即可。

问题在于如何在O(1)O(1) 时间 实现max_value? 我们的想法是维护一个递减的双端队列deque。

每次queue入队列的时候，我们deque也入队列，入队列之前我们清除队尾的比入队的元素小的元素。 一句话来说，我们的目的就是维持 deque保持递减性质不变
每次queue pop的时候，我们的deque不一定也要出队列。当且仅当deque的队首元素和queue队首元素一致时候，我们才需要执行deque的出队列的操作
这样max_value我们只需要返回deque的队首元素即可，至此我们终于实现了$O(1)$ 时间 实现max_value

*/
typedef struct {
	struct ListNode *head;
	struct ListNode *mhead;
} MaxQueue;

MaxQueue* maxQueueCreate() {
	MaxQueue * queue = (MaxQueue *)malloc(sizeof(MaxQueue));
	queue->head = slink_init();
	queue->mhead = slink_init();
	return queue;
}

int maxQueueMax_value(MaxQueue* obj) {
	if(slink_empty(obj->mhead))
		return -1;

	return slink_get_first(obj->mhead);
}

void maxQueuePush_back(MaxQueue* obj, int value) {
	slink_push_last(obj->head, value);
	while(!slink_empty(obj->mhead) && value > slink_get_last(obj->mhead)) {
		slink_pop_last(obj->mhead);
	}

	slink_push_last(obj->mhead, value);
}

int maxQueuePop_front(MaxQueue* obj) {
	if (slink_empty(obj->head))
		return -1;
	int ret = slink_pop_first(obj->head);
	if (ret == slink_get_first(obj->mhead)) {
		slink_pop_first(obj->mhead);
	}

	return ret;
}

void maxQueueFree(MaxQueue* obj) {
	free(obj->head);
	free(obj->mhead);
	free(obj);
}

