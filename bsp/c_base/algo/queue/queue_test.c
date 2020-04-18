#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


/*
�������һ�� ̰������Ϸ������Ϸ������һ�� ��Ļ�ߴ� = ��� x �߶� ����Ļ�����С�����㲻��Ϥ�����Ϸ������ ������� �������档

���ʱ���������Ͻǵ� (0, 0) λ�ã����峤��Ϊ 1 ����λ��

�㽫�ᱻ����һ�� (��, ��) ��ʽ��ʳ��λ�����С����߳Ե�ʳ��ʱ�����ӵĳ��Ȼ����� 1 ����λ���÷�Ҳ�� +1��

ʳ�ﲻ��ͬʱ���֣��ᰴ�б��˳����һ��ʾ����Ļ�ϡ��ȷ�������һ��ʳ�ﱻ�߳Ե��󣬵ڶ���ʳ��Ż���֡�

��һ��ʳ������Ļ�ϳ���ʱ��������֤���ܳ����ڱ�������ռ�ݵĸ����

����ÿ�� move() ����������Ҫ���ص�ǰ�÷ֻ� -1����ʾ�����Լ������ǽ��ײ����ζ��Ϸ��������

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

snake.move("R"); -> �������� 1 (�߳Ե��˵�һ��ʳ�ͬʱ�ڶ���ʳ�������λ�� (0,1))

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

SnakeGame* snakeGameCreate(int width, int height, int** food, int foodSize, int* foodColSize) {
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


bool isFood(SnakeGame* obj,int x, int y) {
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
int snakeGameMove(SnakeGame* obj, char * direction) {

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

