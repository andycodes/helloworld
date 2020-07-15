#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


/*
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
	struct queue_blk * queue;
	int width;
	int height;
	int** food;
	int foodSize;
	int* foodColSize;
	int foodCnt;
} SnakeGame;

/** Initialize your data structure here.
        @param width - screen width
        @param height - screen height
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
SnakeGame* snakeGameCreate(int width, int height, int** food, int foodSize, int* foodColSize)
{
	SnakeGame* sg = malloc(sizeof(SnakeGame));
	sg->queue = create_array_queue(width * height);
	sg->width = width;
	sg->height = height;
	sg->food = food;
	sg->foodSize = foodSize;
	sg->foodColSize = foodColSize;
	sg->foodCnt = 0;

	struct queue_load newLoc;
	newLoc.x = 0;
	newLoc.y = 0;
	push(sg->queue, newLoc);

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


/** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
        @return The game's score after the move. Return -1 if game over.
        Game over when snake crosses the screen boundary or bites its body. */
int snakeGameMove(SnakeGame* obj, char * direction)
{
	struct queue_load next;
	next = back(obj->queue);

	switch(*direction) {
		case 'U': {
				next.x -= 1;
		}break;
		case 'L': {
				next.y -= 1;
		}break;
		case 'R': {
				next.y += 1;
		}break;
		case 'D': {
				next.x += 1;
		}break;
		default:break;
	}

	if (next.x < 0 || next.x >= obj->height || next.y < 0 || next.y >= obj->width) {
		return -1;
	}

	if(!isFood(obj,next.x,next.y)) {
		(void)pop(obj->queue);
	}

	for_queue_entry(obj->queue) {
		if (next.x == obj->queue->load[i].x && next.y == obj->queue->load[i].y) {
			return -1;
		}
	}

	push(obj->queue, next);
	return size(obj->queue) - 1;

}

void snakeGameFree(SnakeGame* obj) {
	destroy_array_queue(obj->queue);
	free(obj);
	obj == NULL;
}
/*
604. ����ѹ���ַ���
�Ѷȼ�17
����һ��ѹ���ַ��������һ�����ݽṹ����֧���������ֲ����� next �� hasNext��
������ѹ���ַ�����ʽΪ��ÿ����ĸ�������һ�������������������ʾ����ĸ�ڽ�ѹ����ַ������������ֵĴ�����
next() - ���ѹ���ַ�����Ȼ����ĸδ����ѹ���򷵻���һ����ĸ�����򷵻�һ���ո�
hasNext() - �ж��Ƿ�����ĸ��Ȼû����ѹ��
ע�⣺
��ǵý�������� StringIterator �� ��ʼ�� ����Ϊ��̬������������ڶ�����������в��ᱻ�Զ���ա�����ϸ������� ���� ��
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
StringIterator* stringIteratorCreate(char * compressedString) {
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

	//for (int i = 0; i < obj->rear; i += 2) {
	//	printf("[c]%c %d\n", obj->queue[i], obj->queue[i + 1]);
	//}

	return obj;
}
//"L1e2t1C1o1d1e1"
char stringIteratorNext(StringIterator* obj) {
	if (obj->head == obj->rear)
		return ' ';

	int top = obj->queue[obj->head];
	obj->queue[obj->head + 1]--;
	//printf("[s]%c %d\n", top, obj->queue[obj->head + 1]);
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

/**
 * Your StringIterator struct will be instantiated and called as such:
 * StringIterator* obj = stringIteratorCreate(compressedString);
 * char param_1 = stringIteratorNext(obj);

 * bool param_2 = stringIteratorHasNext(obj);

 * stringIteratorFree(obj);
*/