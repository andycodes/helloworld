
#define MAX 100

int head = 0;
int rear = 0;
int queue[MAX];     // �������
int visited[MAX];   // ������ʱ��
//memset(visited, 0, sizeof(visited));

 // �����(rear ָ���βû�����ݵĵط�)
queue[rear++] = data;

data = queue[head++];  // ������

#define empty(head, rear)	head == rear

////////////////////////
top = 0;
char stack[MAX];
memset(stack, 0, sizeof(stack));
top++;
// ��������ջ
if (top < sizeof(stack)) {
top++;
stack[top] = op;
}

//printf("%c", stack[top]);
		top--;
/////////////////////////////
const int MAXN = 64; // ջ����󳤶�
int stack[MAXN];
int top = -1;
stack[++top] = e; // push
while(top >= 0) {
		e = stack[top--]; // pop
		printf("%X", e);
}
