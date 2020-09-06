/*
353. 贪吃蛇
请你设计一个 贪吃蛇游戏，该游戏将会在一个 屏幕尺寸 =
宽度 x 高度 的屏幕上运行。如果你不熟悉这个游戏，可以 点
击这里 在线试玩。
起初时，蛇在左上角的 (0, 0) 位置，身体长度为 1 个单位。
你将会被给出一个 (行, 列) 形式的食物位置序列。当蛇吃到食
物时，身子的长度会增加 1 个单位，得分也会 +1。
食物不会同时出现，会按列表的顺序逐一显示在屏幕上。
比方讲，第一个食物被蛇吃掉后，第二个食物才会出现。
当一个食物在屏幕上出现时，它被保证不能出现在被蛇身体
占据的格子里。
对于每个 move() 操作，你需要返回当前得分或 -1（表示蛇与自
己身体或墙相撞，意味游戏结束）。
示例：

给定 width = 3, height = 2, 食物序列为 food = [[1,2],[0,1]]。
Snake snake = new Snake(width, height, food);
初始时，蛇的位置在 (0,0) 且第一个食物在 (1,2)。
|S| | |
| | |F|
snake.move("R"); -> 函数返回 0
| |S| |
| | |F|
snake.move("D"); -> 函数返回 0
| | | |
| |S|F|
snake.move("R"); -> 函数返回 1 (蛇吃掉了第一个食物，
同时第二个食物出现在位置 (0,1))
| |F| |
| |S|S|
snake.move("U"); -> 函数返回 1
| |F|S|
| | |S|
snake.move("L"); -> 函数返回 2 (蛇吃掉了第二个食物)
| |S|S|
| | |S|
snake.move("U"); -> 函数返回 -1 (蛇与边界相撞，游戏结束)

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
604. 迭代压缩字符串
难度简单17
对于一个压缩字符串，设计一个数据结构，它支持如下两种
操作： next 和 hasNext。
给定的压缩字符串格式为：每个字母后面紧跟一个正整数，
这个整数表示该字母在解压后的字符串里连续出现的次数。
next() - 如果压缩字符串仍然有字母未被解压，则返回下一个字
母，否则返回一个空格。
hasNext() - 判断是否还有字母仍然没被解压。
注意：
请记得将你的类在 StringIterator 中 初始化 ，因为静态变量或类变
量在多组测试数据中不会被自动清空。更多细节请访问 这里 。
示例：
StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");

iterator.next(); // 返回 'L'
iterator.next(); // 返回 'e'
iterator.next(); // 返回 'e'
iterator.next(); // 返回 't'
iterator.next(); // 返回 'C'
iterator.next(); // 返回 'o'
iterator.next(); // 返回 'd'
iterator.hasNext(); // 返回 true
iterator.next(); // 返回 'e'
iterator.hasNext(); // 返回 false
iterator.next(); // 返回 ' '

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
剑指 Offer 59 - II. 队列的最大值. 队列的最大值
请定义一个队列并实现函数 max_value 得到队列里的最大值，
要求函数max_value、push_back 和 pop_front 的时间复杂度都是O(1)。
若队列为空，pop_front 和 max_value 需要返回 -1
示例 1：
输入:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出: [null,null,null,2,1,2]
示例 2：
输入:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出: [null,-1,-1]
*/

/*
我们维护一个正常的队列queue，这样push_back, pop_front 直接操作正
常队列即可。
问题在于如何在O(1)O(1) 时间 实现max_value? 我们的想法是维护一
个递减的双端队列deque。
每次queue入队列的时候，我们deque也入队列，入队列之前我们
清除队尾的比入队的元素小的元素。
一句话来说，我们的目
的就是维持 deque保持递减性质不变
每次queue pop的时候，我们的deque不一定也要出队列。当且仅当
deque的队首元素和queue队首元素一致时候，我们才需要执行
deque的出队列的操作
这样max_value我们只需要返回deque的队首元素即可，至此我们
终于实现了$O(1)$ 时间 实现max_value

双端队列划窗
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

