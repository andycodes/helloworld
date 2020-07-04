
#define MAX 100

int head = 0;
int rear = 0;
int queue[MAX];     // 辅组队列
int visited[MAX];   // 顶点访问标记
//memset(visited, 0, sizeof(visited));

 // 入队列(rear 指向队尾没有数据的地方)
queue[rear++] = data;

data = queue[head++];  // 出队列

#define empty(head, rear)	head == rear

////////////////////////
top = 0;
char stack[MAX];
memset(stack, 0, sizeof(stack));
top++;
// 运算子入栈
if (top < sizeof(stack)) {
top++;
stack[top] = op;
}

//printf("%c", stack[top]);
		top--;
/////////////////////////////
const int MAXN = 64; // 栈的最大长度
int stack[MAXN];
int top = -1;
stack[++top] = e; // push
while(top >= 0) {
		e = stack[top--]; // pop
		printf("%X", e);
}
