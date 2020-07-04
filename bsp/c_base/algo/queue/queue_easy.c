
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
