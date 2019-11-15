#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


/*
[
[2,1,1],
[1,1,0],
[0,1,1]
]
*/

struct queue_load{
	int num;
	int deep;
};

struct queue_blk{
	int count;
	struct queue_load load[0];
};

struct queue_blk * create_array_queue(int sz)
{
	struct queue_blk * queue;

	queue = (struct queue_blk * )malloc(sizeof(struct queue_blk) + sz*sizeof(struct queue_load));
	if(queue == NULL) {
		printf(" malloc error!");
		return  NULL;
	}

	queue->count = 0;

	return queue;
}


void destroy_array_queue(struct queue_blk * queue)
{
	if (queue) {
		free((void*)queue);
		queue = NULL;
	}
}


void push(struct queue_blk * queue,struct queue_load load)
{
	queue->load[queue->count++] = load;
}


struct queue_load  front(struct queue_blk * queue)
{
	return  queue->load[0];
}


// ���ز�ɾ�������п�ͷԪ�ء�
struct queue_load pop(struct queue_blk * queue)
{
	int i = 0;

	struct queue_load head = queue->load[0];

	queue->count--;
	while (i++<queue->count)
		queue->load[i-1] = queue->load[i];

	return head;
}


// ���ء����С��Ĵ�С
int size(struct queue_blk * queue)
{
	return queue->count;
}

// ���ء����С��Ƿ�Ϊ��
int is_empty(struct queue_blk * queue)
{
	return queue->count==0;
}



/*
�ڸ����������У�ÿ����Ԫ���������������ֵ֮һ��

ֵ 0 ����յ�Ԫ��
ֵ 1 �����������ӣ�
ֵ 2 �����õ����ӡ�
ÿ���ӣ��κ��븯�õ����ӣ��� 4 ���������ϣ����ڵ��������Ӷ��ḯ�á�

����ֱ����Ԫ����û����������Ϊֹ�����뾭������С����������������ܣ����� -1��

�����������������
˼·

ÿһ�֣����ý����ÿһ�����������ӵ��������ڵ����������ϡ�һ��ʼ�����õ����ӵ����Ϊ 0��ÿһ�ָ��û�Ӹ������Ӵ�Ⱦ��֮�������������ϣ�����������Щ�µĸ������ӵ����Ϊ�Լ���� +1��������֪������������֮���������ֵ�Ƕ��١�

�㷨

���ǿ�����һ�����������������ģ��һ���̡���Ϊ��������ѡ��ȥʹ�����ֵ��С�ģ���֮ǰδʹ�ù��ģ���������ȥ�����������ӣ���˱�֤ÿһ�����Ӹ���ʱ����ȱ��Ҳ����С�ġ�

���ǻ�Ӧ�ü������״̬�£��Ƿ����������ӡ�

*/
int orangesRotting(int** grid, int gridSize, int* gridColSize){
		int ans = 0;
		int dr[] = { -1,0,1,0 };
		int dc[] = { 0,-1,0,1 };
		int row = gridSize, col = gridColSize[0];

		struct queue_blk *queue = create_array_queue(row*col);

		for(int r=0;r<row;r++)
			for(int c=0;c<col;c++)
				if (grid[r][c] == 2){
					struct queue_load load;
					load.deep = 0;
					load.num = r*col + c;
					push(queue,load);
				}

		while (!is_empty(queue)) {
			struct queue_load curr = pop(queue);
			int r = curr.num / col, c = curr.num % col;
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];
				if (0 <= nr && nr < row && 0 <= nc && nc < col && grid[nr][nc] == 1) {
					grid[nr][nc] = 2;
					struct queue_load load;
					load.num = nr * col + nc;
					load.deep = curr.deep + 1;
					push(queue,load);
					ans = curr.deep + 1;
				}
			}
		}

		for(int r=0;r<row;r++)
			for(int c=0;c<col;c++)
				if (grid[r][c] == 1){
					return -1;
				}

		return ans;
}





