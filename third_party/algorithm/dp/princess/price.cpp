#include "save_princess.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum DIRECTION
{
	D_UP = 0,
	D_DOWN,
	D_LEFT,
	D_RIGHT,
	D_SIZE
};

enum ROOM_TYPE
{
	TYPE_ROAD,
	TYPE_WINDOW,
	TYPE_PRINCE,
	TYPE_PRINCESS,
};

struct room_info
{
	int row;
	int col;
	enum ROOM_TYPE type;
	int pass_by;
	struct room_info* child[D_SIZE];
};

/*
 * 返回指向孩子的指针,孩子为墙则返回NULL
 * M*N 的迷宫，max_row = M - 1, max_col = N - 1
 */
static struct room_info* get_child(struct room_info* maze, int max_row, int max_col,
					   struct room_info* cur_room, enum DIRECTION direct)
{
	int row = 0;
	int col = 0;
	int idx = 0;
	struct room_info* child = NULL;

	if (NULL == maze || NULL == cur_room)
		return NULL;

	row = cur_room->row;
	col = cur_room->col;

	switch (direct) {
	case D_UP:
		if (row <= 0)
			return NULL;
		row--;
	break;
	case D_DOWN:
		if (row >= max_row)
			return NULL;
		row++;
	break;
	case D_LEFT:
		if (col <= 0)
			return NULL;
		col--;
	break;
	case D_RIGHT:
		if (col >= max_col)
			return NULL;
		col++;
	break;
	default:break;
	}

	idx = row * (max_col + 1) + col;
	child = maze + idx;
	if (TYPE_WINDOW == child->type)
		return NULL;
	else
		return child;
}

/* 成功返回指向S的指针， 失败返回NULL*/
static struct room_info* init_maze(struct room_info* maze, int M, int N, char* maze_data)
{
	int row = 0;
	int col = 0;
	struct room_info* prince = NULL;

	/* 第一遍识别墙等,确定坐标 */
	for (row = 0; row < M; row++)
	{
		for (col = 0; col < N; col++)
		{
			int idx = row * N + col;
			char c = *(maze_data + idx);

			memset(maze + idx, 0, sizeof(struct room_info));
			maze[idx].row = row;
			maze[idx].col = col;

			switch (c)
			{
			case '.':
				maze[idx].type = TYPE_ROAD;
				break;
			case '*':
				maze[idx].type = TYPE_WINDOW;
				break;
			case 'S':
				prince = maze + idx;
				maze[idx].type = TYPE_PRINCE;
				break;
			case 'P':
				maze[idx].type = TYPE_PRINCESS;
				break;
			default:
				return NULL;
			}
		}
	}

	/*第二遍建立图*/
	for (row = 0; row < M; row++) {
		for (col = 0; col < N; col++) {
			int idx = row * N + col;
			for (int i = D_UP; i < D_SIZE; i = i+1)
				maze[idx].child[i]	= get_child(maze, M - 1, N - 1, maze + idx, (enum DIRECTION)i);
		}
	}

	return prince;
}

struct node_info
{
	int level;
	struct room_info* room;
	struct node_info* parent;
	struct node_info* next;
};

static void queue_push(struct node_info* queue,
						struct room_info* room,
						int cur_level,
						struct node_info* parent)
{
	struct node_info* new_node = NULL;
	if (NULL == room)
		return;

	new_node = (struct node_info*) new struct node_info;
	memset(new_node, 0, sizeof(struct node_info));

	new_node->level = cur_level + 1;
	new_node->parent = parent;
	new_node->room = room;

	while (queue != NULL) {
		if (NULL == queue->next) {
			queue->next = new_node;
			break;
		}

		queue = queue->next;
	}
}

static void queue_release(struct node_info* queue)
{
	struct node_info* tmp = NULL;
	while (queue != NULL) {
		tmp = queue->next;
		delete queue;
		queue = tmp;
	}
}

/* 找到princess返回需要的步数
 * 找不到或者出错返回-1
 */
static int find_princess(struct room_info* maze, struct room_info* prince)
{
	struct node_info* queue =  NULL;
	struct node_info* cur_step =  NULL;

	queue = (struct node_info*)new struct node_info;
	if (NULL == queue)
		return -1;

	memset(queue, 0, sizeof(struct node_info));
	queue->parent = NULL;
	queue->level = 0;
	queue->room = prince;

	cur_step = queue;
	while (cur_step != NULL) {
		struct room_info* cur_room = cur_step->room;
		if (NULL == cur_room) {
			fprintf(stderr, "IT CAN NOT HAPPEN!\n");
			break;
		}

		if (TYPE_PRINCESS == cur_room->type) {
			struct node_info* tmp = cur_step;
			/* we find princess :) */
			fprintf(stdout, "\nThe way back to prince... \n");
			while (tmp != NULL) {
				fprintf(stdout, "(%d, %d) ", tmp->room->row, tmp->room->col);
				tmp = tmp->parent;
			}
			fprintf(stdout, "\n");

			queue_release(queue);
			return cur_step->level;
		}else if (TYPE_ROAD == cur_room->type || TYPE_PRINCE == cur_room->type) {
			struct room_info* tmp = NULL;
			if (1 == cur_room->pass_by) {
				cur_step = cur_step->next;
				continue;
			}

			cur_room->pass_by = 1;
			/* 把孩子们丢到队列后面 */
			for (int i = D_UP; i < D_SIZE; i++)
				queue_push(queue, cur_room->child[i], cur_step->level, cur_step);
		}else {
			fprintf(stderr, "Wired!\n");
		}

		cur_step = cur_step->next;
	}

	queue_release(queue);
	return -1;
}

int save_princess(int M, int N, char* maze_data, int time)
{
	struct room_info* maze = NULL;
	struct room_info* prince = NULL;
	int time_need = 0;

	if (M <= 1 || N <= 1 || NULL == maze_data || 0 == time)
		return 0;

	maze = (struct room_info*)malloc(M * N * sizeof(struct room_info));
	if (NULL == maze)
		return 0;

	prince = init_maze(maze, M, N, maze_data);
	if (NULL == prince) {
		free(maze);
		return 0;
	}

	time_need = find_princess(maze, prince);
	free(maze);

	if (-1 == time_need)
		return 0;
	else if (time_need > time)
		return 0;
	else
		return 1;
}