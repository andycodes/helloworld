/*
353. ̰����
�������һ�� ̰������Ϸ������Ϸ������һ�� ��Ļ�ߴ� =
��� x �߶� ����Ļ�����С�����㲻��Ϥ�����Ϸ������ ��
������ �������档
���ʱ���������Ͻǵ� (0, 0) λ�ã����峤��Ϊ 1 ����λ��
�㽫�ᱻ����һ�� (��, ��) ��ʽ��ʳ��λ�����С����߳Ե�ʳ
��ʱ�����ӵĳ��Ȼ����� 1 ����λ���÷�Ҳ�� +1��
ʳ�ﲻ��ͬʱ���֣��ᰴ�б��˳����һ��ʾ����Ļ�ϡ�
�ȷ�������һ��ʳ�ﱻ�߳Ե��󣬵ڶ���ʳ��Ż���֡�
��һ��ʳ������Ļ�ϳ���ʱ��������֤���ܳ����ڱ�������
ռ�ݵĸ����
����ÿ�� move() ����������Ҫ���ص�ǰ�÷ֻ� -1����ʾ������
�������ǽ��ײ����ζ��Ϸ��������
ʾ����

���� width = 3, height = 2, ʳ������Ϊ food = [[1,2],[0,1]]��
Snake snake = new Snake(width, height, food);
��ʼʱ���ߵ�λ���� (0,0) �ҵ�һ��ʳ���� (1,2)��
|S| | |
| | |F|
snake.move("R"); -> �������� 0
| |S| |
| | |F|
snake.move("D"); -> �������� 0
| | | |
| |S|F|
snake.move("R"); -> �������� 1 (�߳Ե��˵�һ��ʳ�
ͬʱ�ڶ���ʳ�������λ�� (0,1))
| |F| |
| |S|S|
snake.move("U"); -> �������� 1
| |F|S|
| | |S|
snake.move("L"); -> �������� 2 (�߳Ե��˵ڶ���ʳ��)
| |S|S|
| | |S|
snake.move("U"); -> �������� -1 (����߽���ײ����Ϸ����)

struct queue_load{
	int x;
	int y;
};
*/

typedef struct {
	int queue[10240];
	int head;
	int rear;
	int width;
	int height;
	int** food;
	int foodSize;
	int* foodColSize;
	int foodCnt;
} SnakeGame;

SnakeGame* snakeGameCreate(int width, int height, int** food, int foodSize, int* foodColSize)
{
	SnakeGame* sg = malloc(sizeof(SnakeGame));
	sg->width = width;
	sg->height = height;
	sg->food = food;
	sg->foodSize = foodSize;
	sg->foodColSize = foodColSize;
	sg->foodCnt = 0;

	sg->queue[sg->rear++] = 0;
	return sg;
}

bool isFood(SnakeGame* obj,int x, int y)
{
	if (obj->foodCnt < obj->foodSize) {
		if (x == obj->food[obj->foodCnt][0] && y == obj->food[obj->foodCnt][1]) {
			obj->foodCnt++;
			return true;
		}
	}

	return false;
}


int snakeGameMove(SnakeGame* obj, char * direction)
{
	int last = obj->queue[obj->rear - 1];
	int nx = last /obj->width;
	int ny = last % obj->width;
	switch(*direction) {
		case 'U': {
				nx -= 1;
		}break;
		case 'L': {
				ny -= 1;
		}break;
		case 'R': {
				ny += 1;
		}break;
		case 'D': {
				nx += 1;
		}break;
		default:break;
	}

	if (nx < 0 || nx >= obj->height || ny < 0 || ny >= obj->width) {
		return -1;
	}

	if(!isFood(obj,nx,ny)) {
		obj->head++;
	}

	for (int i = obj->head; i < obj->rear; i++) {
		if (nx == obj->queue[i] / obj->width && ny == obj->queue[i] % obj->width) {
			return -1;
		}
	}

	obj->queue[obj->rear++] = nx * obj->width + ny;
	return obj->rear - obj->head - 1;
}

void snakeGameFree(SnakeGame* obj)
{
	free(obj);
	obj == NULL;
}


/*
604. ����ѹ���ַ���
�Ѷȼ�17
����һ��ѹ���ַ��������һ�����ݽṹ����֧����������
������ next �� hasNext��
������ѹ���ַ�����ʽΪ��ÿ����ĸ�������һ����������
���������ʾ����ĸ�ڽ�ѹ����ַ������������ֵĴ�����
next() - ���ѹ���ַ�����Ȼ����ĸδ����ѹ���򷵻���һ����
ĸ�����򷵻�һ���ո�
hasNext() - �ж��Ƿ�����ĸ��Ȼû����ѹ��
ע�⣺
��ǵý�������� StringIterator �� ��ʼ�� ����Ϊ��̬���������
���ڶ�����������в��ᱻ�Զ���ա�����ϸ������� ���� ��
ʾ����
StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");

iterator.next(); // ���� 'L'
iterator.next(); // ���� 'e'
iterator.next(); // ���� 'e'
iterator.next(); // ���� 't'
iterator.next(); // ���� 'C'
iterator.next(); // ���� 'o'
iterator.next(); // ���� 'd'
iterator.hasNext(); // ���� true
iterator.next(); // ���� 'e'
iterator.hasNext(); // ���� false
iterator.next(); // ���� ' '

*/
typedef struct {
	int head;
	int rear;
	int *queue;
} StringIterator;

//"L1e2t1C1o1d1e1"
StringIterator* stringIteratorCreate(char * compressedString)
{
	StringIterator* obj = (StringIterator*)calloc(1, sizeof(StringIterator));
	obj->queue = (int *)calloc(strlen(compressedString) * 10, sizeof(int));

	int i = 0;
	int num = 0;
	while(compressedString[i] != '\0') {
		if (isalpha(compressedString[i])) {
			if (num != 0) {
				obj->queue[obj->rear++] = num;
				num = 0;
			}

			obj->queue[obj->rear++] = compressedString[i];
		} else if (isdigit(compressedString[i])) {
			num = num * 10 + compressedString[i] - '0';
		}

		i++;
	}

	if (num != 0)
		obj->queue[obj->rear++] = num;
	return obj;
}
//"L1e2t1C1o1d1e1"
char stringIteratorNext(StringIterator* obj)
{
	if (obj->head == obj->rear)
		return ' ';

	int top = obj->queue[obj->head];
	obj->queue[obj->head + 1]--;
	if (obj->queue[obj->head + 1] <= 0) {
		obj->head += 2;
	}

	return top;
}

bool stringIteratorHasNext(StringIterator* obj) {
	return obj->head != obj->rear;
}

void stringIteratorFree(StringIterator* obj) {
	free(obj->queue);
	free(obj);
	obj = NULL;
}


/*
��ָ Offer 59 - II. ���е����ֵ. ���е����ֵ
�붨��һ�����в�ʵ�ֺ��� max_value �õ�����������ֵ��
Ҫ����max_value��push_back �� pop_front ��ʱ�临�Ӷȶ���O(1)��
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
����ά��һ�������Ķ���queue������push_back, pop_front ֱ�Ӳ�����
�����м��ɡ�
�������������O(1)O(1) ʱ�� ʵ��max_value? ���ǵ��뷨��ά��һ
���ݼ���˫�˶���deque��
ÿ��queue����е�ʱ������dequeҲ����У������֮ǰ����
�����β�ı���ӵ�Ԫ��С��Ԫ�ء�
һ�仰��˵�����ǵ�Ŀ
�ľ���ά�� deque���ֵݼ����ʲ���
ÿ��queue pop��ʱ�����ǵ�deque��һ��ҲҪ�����С����ҽ���
deque�Ķ���Ԫ�غ�queue����Ԫ��һ��ʱ�����ǲ���Ҫִ��
deque�ĳ����еĲ���
����max_value����ֻ��Ҫ����deque�Ķ���Ԫ�ؼ��ɣ���������
����ʵ����$O(1)$ ʱ�� ʵ��max_value

˫�˶��л���
*/
typedef struct {
	int head;
	int rear;
	int mhead;
	int mrear;
	int* queue;
	int* maxqueue;
} MaxQueue;


MaxQueue* maxQueueCreate() {
	MaxQueue* obj = (MaxQueue*)calloc(1, sizeof(MaxQueue));
	obj->queue = (int *)calloc(100000, sizeof(int));
	obj->maxqueue = (int *)calloc(10000, sizeof(int));
	return obj;
}

int maxQueueMax_value(MaxQueue* obj) {
	if (obj->mhead == obj->mrear) {
		return -1;
	}

	return obj->maxqueue[obj->mhead];
}

void maxQueuePush_back(MaxQueue* obj, int value)
{
	obj->queue[obj->rear++] = value;
	while(obj->mrear != obj->mhead && value > obj->maxqueue[obj->mrear - 1]) {
		obj->mrear--;
	}

	obj->maxqueue[obj->mrear++] = value;
}

int maxQueuePop_front(MaxQueue* obj) {
	if (obj->head == obj->rear) {
		return -1;
	}

	int pop = obj->queue[obj->head++];
	if (pop == obj->maxqueue[obj->mhead]) {
		obj->mhead++;
	}

	return pop;
}

