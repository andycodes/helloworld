
#define MAX 100
/*queue*/
int queue[MAX];     // �������
int visited[MAX];   // ������ʱ��
int head = 0;
int rear = 0;

 // �����(rear ָ���βû�����ݵĵط�)
queue[rear++] = data;

data = queue[head++];  // ������

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
	�����������У���ǰ�������ڸ�ֵ������
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
�����½�����,��ǰ����С�ڸ�ֵ������
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