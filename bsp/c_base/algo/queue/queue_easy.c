
#define MAX 100
////////////////////////////////////
struct QUEUE
int queue[MAX];     // �������
int visited[MAX];   // ������ʱ��
int head = 0;
int rear = 0;
//memset(visited, 0, sizeof(visited));

 // �����(rear ָ���βû�����ݵĵط�)
queue[rear++] = data;

data = queue[head++];  // ������

#define empty(head, rear)	head == rear

/////////////////////////////
int stack[MAX];
int top = -1;

stack[++top] = data; // push

while(top >= 0) {
	e = stack[top--]; // pop
}

empty:  top == -1
not empty: top >= 0

bool isInQueue(char* stack, int top, char data)
{
	if (top <= -1)
		return false;

	for (int i = 0; i <= top; i++) {
		if (stack[i] == data)
			return true;
	}

	return false;
}