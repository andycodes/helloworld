
/*
������59 - II. ���е����ֵ
�붨��һ�����в�ʵ�ֺ��� max_value �õ�����������ֵ��Ҫ����max_value��push_back �� pop_front ��ʱ�临�Ӷȶ���O(1)��

������Ϊ�գ�pop_front �� max_value ��Ҫ���� -1

ʾ�� 1��

����:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
���: [null,null,null,2,1,2]
ʾ�� 2��

����:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
���: [null,-1,-1]

*/

/*
����ά��һ�������Ķ���queue������push_back, pop_front ֱ�Ӳ����������м��ɡ�

�������������O(1)O(1) ʱ�� ʵ��max_value? ���ǵ��뷨��ά��һ���ݼ���˫�˶���deque��

ÿ��queue����е�ʱ������dequeҲ����У������֮ǰ���������β�ı���ӵ�Ԫ��С��Ԫ�ء� һ�仰��˵�����ǵ�Ŀ�ľ���ά�� deque���ֵݼ����ʲ���
ÿ��queue pop��ʱ�����ǵ�deque��һ��ҲҪ�����С����ҽ���deque�Ķ���Ԫ�غ�queue����Ԫ��һ��ʱ�����ǲ���Ҫִ��deque�ĳ����еĲ���
����max_value����ֻ��Ҫ����deque�Ķ���Ԫ�ؼ��ɣ�������������ʵ����$O(1)$ ʱ�� ʵ��max_value

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

