
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
