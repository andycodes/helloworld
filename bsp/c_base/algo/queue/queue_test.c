#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


/*
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
604. 迭代压缩字符串
难度简单17
对于一个压缩字符串，设计一个数据结构，它支持如下两种操作： next 和 hasNext。
给定的压缩字符串格式为：每个字母后面紧跟一个正整数，这个整数表示该字母在解压后的字符串里连续出现的次数。
next() - 如果压缩字符串仍然有字母未被解压，则返回下一个字母，否则返回一个空格。
hasNext() - 判断是否还有字母仍然没被解压。
注意：
请记得将你的类在 StringIterator 中 初始化 ，因为静态变量或类变量在多组测试数据中不会被自动清空。更多细节请访问 这里 。
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