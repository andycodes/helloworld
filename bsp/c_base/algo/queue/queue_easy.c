
#define MAXSIZE 100


/*queue*/
int queue[MAXSIZE];
int head = 0;
int tail = 0;
int visited[MAXSIZE];

 // 入队列(tail 指向队尾没有数据的地方)
queue[tail++] = data;
 // 出队列
data = queue[head++];
#define empty(head, tail)	head == tail

/*statck*/
int stack[MAXSIZE];
int top = -1;
 // push
stack[++top] = data;
// pop
while(top >= 0) {
	out = stack[top--];
}

//stack size : top + 1


empty:  top == -1
not empty: top >= 0


/*维护区间有序数组(递减)*/
void squeue_push(int *dqueue, int dqueueSize, int data)
{
	int i;
	for (i = 0; i < dqueueSize - 1; i++) {
		if (data > dqueue[i]) {
			break;
		}
	}

	for (int j = dqueueSize - 1; j > i; j--) {
		dqueue[j] = dqueue[j - 1];
	}

	dqueue[i] = data;
}
void squeue_del(int *dqueue, int dqueueSize, int del)
{
	int i;
	for (i = 0; i < dqueueSize; i++) {
		if (dqueue[i] == del) {
			break;
		}
	}

	for (int j = i; j < dqueueSize - 1; j++) {
		dqueue[j] = dqueue[j + 1];
	}
}


/*维护区间最小值(不维护区间全部数据)(递增数组)*/
int minqueue[MAXSIZE];
int head = 0;
int tail = 0;
void minqueue_push(int *minqueue, int ndata)
{
	while(tail > head && ndata < minqueue[tail - 1]) {
		tail--;
	}

	minqueue[tail++] = ndata;
}

int minid = minqueue[head];

void iqueue_pop(int *iqueue)
{
	if (obj[left] == minqueue[head]) {
		head++;
	}
}

/*维护区间最大值(不维护区间全部数据)(递减数组)*/
int maxqueue[MAXSIZE];
int tail = 0;
int head = 0;
void maxqueue_push(int ndata)
{
	while(tail > head && ndata >= maxqueue[tail - 1]) {
			tail--;
	}

	maxqueue[tail++] = ndata;
}

int maxid = maxqueue[head];

void maxqueue_pop(void)
{
	if (obj[left] == maxqueue[head]) {
		head++;
	}
}


/*维护区间有序数组(递增)*/
void squeue_push(int *iqueue, int iqueueSize, int data)
{
	int i;
	for (i = 0; i < iqueueSize - 1; i++) {
		if (data < iqueue[i]) {
			break;
		}
	}

	for (int j = iqueueSize - 1; j > i; j--) {
		iqueue[j] = iqueue[j - 1];
	}

	iqueue[i] = data;
}

void squeue_del(int *iqueue, int iqueueSize, int del)
{
	int i;
	for (i = 0; i < iqueueSize; i++) {
		if (iqueue[i] == del) {
			break;
		}
	}

	for (int j = i; j < iqueueSize - 1; j++) {
		iqueue[j] = iqueue[j + 1];
	}
}

