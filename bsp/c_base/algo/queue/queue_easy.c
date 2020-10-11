
#define MAX 100
/*queue*/
int queue[MAX];     // 辅组队列
int visited[MAX];   // 顶点访问标记
int head = 0;
int rear = 0;

 // 入队列(rear 指向队尾没有数据的地方)
queue[rear++] = data;

data = queue[head++];  // 出队列

#define empty(head, rear)	head == rear

/*statck*/
int stack[MAX];
int top = -1;

stack[++top] = data; // push

while(top >= 0) {
	e = stack[top--]; // pop
}

empty:  top == -1
not empty: top >= 0

/*inQueue*/
int iqueue[MAX];
int iqRear = 0;
int iqHead = 0;
void iqueue_push(int newData)
{
/*
	更新上升队列，向前挤掉大于该值的数据
*/
	while(iqRear > iqHead && newData < iqueue[iqRear - 1) {
			iqRear--;
	}

	iqueue[iqRear++] = newData;
}

int minid = iqueue[iqHead];

void iqueue_pop()
{
	if (left == iqueue[iqHead]) {
		iqHead++;
	}
}

/*dQueue*/
int dqueue[MAX];
int dqRear = 0;
int dqHead = 0;
void dqueue_push(int newData)
{
/*
更新下降队列,向前挤掉小于该值的数据
*/
	while(dqRear > dqHead && newData >= dqueue[dqRear - 1]) {
			dqRear--;
	}

	dqueue[dqRear++] = newData;
}

int maxid = dqueue[iqHead];

void iqueue_pop()
{
	if (left == dqueue[dqHead]) {
		dqHead++;
	}
}

dstack_push()
{
	int stack[nums2Size];//idx
	int top = -1;
	for(int i = 0; i < nums2Size; i++) {
		while (top >= 0 && nums2[i] > nums2[stack[top]]) {
			nums2NextBig[stack[top]] = nums2[i];
			top--;
		}

		stack[++top] = i;
	}
}