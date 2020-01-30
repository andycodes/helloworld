/*
BFSģ��

�����жϣ��߽��жϣ�����Ҫ����жϣ�

��������

�ڶ����м����һ������������Ԫ��

while(���в�Ϊ��) {
    ȡ������ͷ��Ԫ��
    ����
    ����ͷ��Ԫ�أ����������ٴμ�������������Ԫ��
}

*/
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
	int size;
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
	queue->size = sz;

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
	if (queue->count > queue->size) {
		printf("[%s] push count[%d] too big\n", __func__, queue->count);
		queue->count = queue->count % queue->size;
		return;
	}
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



struct queue_load{
	int row;
	int col;
};
/*tile see dfs floodFill*/
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc,
	int newColor, int* returnSize, int** returnColumnSizes)
{
	*returnSize = imageSize;
	*returnColumnSizes = malloc(sizeof(int) * imageSize);

	for (int i = 0; i < imageSize; i++) {
		(*returnColumnSizes)[i] = imageColSize[i];
	}

	if (newColor == image[sr][sc])
		return image;

	int directions[4][2] = {
		{1,0},
		{-1,0},
		{0,1},
		{0,-1}
	};
	int originalcolor = image[sr][sc];

	struct queue_blk * queue = create_array_queue(50);

	struct queue_load start;
	start.row = sr;
	start.col = sc;

	push(queue,start);

	while(!is_empty(queue)) {
		struct queue_load cur = pop(queue);
		image[cur.row][cur.col] = newColor;

		for(int i = 0; i < 4; i++) {
			int new_i = cur.row + directions[i][0];
			int new_j = cur.col + directions[i][1];
			if ((0 <= new_i) && (new_i < imageSize)  && (0 <= new_j) &&
				(new_j < imageColSize[0]) && image[new_i][new_j] == originalcolor) {
				start.row = new_i;
				start.col = new_j;
				push(queue,start);
			}
		}
	}

	return image;
}


/*
����һ���� '1'��½�أ��� '0'��ˮ����ɵĵĶ�ά���񣬼��㵺���������һ������ˮ��Χ����������ͨ��ˮƽ�����ֱ���������ڵ�½�����Ӷ��ɵġ�����Լ���������ĸ��߾���ˮ��Χ��

ʾ�� 1:

����:
11110
11010
11000
00000

���: 1

struct queue_load{
	int x;
	int y;
};
*/
int numIslands(char** grid, int gridSize, int* gridColSize){
	int num = 0;

	if(grid == NULL  || gridSize == 0 || gridColSize == NULL)
		return num;

	int visited[gridSize][*gridColSize];
	memset((void*)visited,0,sizeof(visited));



	struct queue_blk *qe = create_array_queue(gridSize*(* gridColSize));


	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

	for(int i = 0; i < gridSize; i++) {
		for (int j = 0; j < *gridColSize;j++) {
			if (grid[i][j] == '1') {
				if ((visited[i][j]) == 0) {
					visited[i][j] = 1;
					num++;
				}

				struct queue_load load;
				load.x = i;
				load.y = j;
				push(qe,load);

				while(!is_empty(qe)) {
					struct queue_load get = pop(qe);

					for(int k = 0; k < 4; k++) {
						int nX = get.x + d[k][0];
						int nY = get.y + d[k][1];
						if (nX >=0 && nX < gridSize && nY >=0 && nY < *gridColSize){
							if (grid[nX][nY] == '1' && visited[nX][nY] == 0) {
								visited[nX][nY] = 1;
								struct queue_load load;
								load.x = nX;
								load.y = nY;
								push(qe, load);
							}
						}
					}
				}
			}
		}
	}

	return num;
}

/*
529. ɨ����Ϸ
������һ������ɨ����Ϸ��

����һ��������Ϸ��Ķ�ά�ַ����� 'M' ����һ��δ�ڳ��ĵ��ף�'E' ����һ��δ�ڳ��Ŀշ��飬'B' ����û�����ڣ��ϣ��£����ң�������4���Խ��ߣ����׵����ڳ��Ŀհ׷��飬���֣�'1' �� '8'����ʾ�ж��ٵ�����������ڳ��ķ������ڣ�'X' ���ʾһ�����ڳ��ĵ��ס�

���ڸ���������δ�ڳ��ķ����У�'M'����'E'������һ�����λ�ã��к������������������¹��򣬷�����Ӧλ�ñ�������Ӧ����壺

���һ�����ף�'M'�����ڳ�����Ϸ�ͽ�����- ������Ϊ 'X'��
���һ��û�����ڵ��׵Ŀշ��飨'E'�����ڳ����޸���Ϊ��'B'�����������к������ڵķ��鶼Ӧ�ñ��ݹ�ؽ�¶��
���һ��������һ���������ڵĿշ��飨'E'�����ڳ����޸���Ϊ���֣�'1'��'8'������ʾ���ڵ��׵�������
����ڴ˴ε���У����޸��෽��ɱ���¶���򷵻���塣


ʾ�� 1��

����:

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

*/

const int dir[8][2] = {{0,1}, {1,0}, {0,-1}, {-1,0},
                 	      {1,1}, {-1,-1},{-1,1},{1,-1}
                 	     };


struct queue_load{
	int x;
	int y;
};

struct queue_blk{
	int count;
	int size;
	struct queue_load load[0];
};

struct queue_blk * array_queue_init(int sz)
{
	struct queue_blk * queue;

	queue = (struct queue_blk * )malloc(sizeof(struct queue_blk) + sz*sizeof(struct queue_load));
	if(queue == NULL) {
		printf(" malloc error!");
		return  NULL;
	}

	queue->count = 0;
	queue->size = sz;

	return queue;
}

void array_queue_exit(struct queue_blk * queue)
{
	if (queue) {
		free((void*)queue);
		queue = NULL;
	}
}

void array_queue_push(struct queue_blk * queue,
	struct queue_load load)
{
	queue->load[queue->count++] = load;
	if (queue->count > queue->size) {
		printf("[%s] push count[%d] too big\n", __func__, queue->count);
		queue->count = queue->count % queue->size;
		return;
	}
}


struct queue_load array_queue_pop(struct queue_blk * queue)
{
	int i = 0;

	struct queue_load head = queue->load[0];

	queue->count--;
	while (i++<queue->count)
		queue->load[i-1] = queue->load[i];

	return head;
}


int array_queue_is_empty(struct queue_blk * queue)
{
	return queue->count==0;
}


void  pushNeighborsInQueue(struct queue_blk * queue,
	int x, int y,  char **res, int boardSize, int* boardColSize)
{
	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardColSize[nx]) {
			if (res[nx][ny] == 'E') {
				struct queue_load load;
				load.x = nx;
				load.y = ny;
				array_queue_push(queue, load);
			}
		}
	}
}


int  NeighborsHavenumsM(int x, int y,  char **res, int boardSize, int* boardColSize)
{
	int Mcnt = 0;

	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardColSize[nx]) {
			if (res[nx][ny] == 'M')
				Mcnt++;
		}
	}

	return Mcnt;
}


char** updateBoard(char** board, int boardSize, int* boardColSize,
int* click, int clickSize, int* returnSize, int** returnColumnSizes){

	char **res = (char **)calloc(boardSize, sizeof(char *));
	for (int i = 0; i < boardSize; i++) {
	        res[i] = (char *)calloc(boardColSize[i], sizeof(char));
	}

	*returnColumnSizes = calloc(boardSize, sizeof(int *));

	for (int i = 0; i < boardSize; i++){
	        for (int j = 0; j < boardColSize[i]; j++) {
	            res[i][j] = board[i][j];
	        }

		(*returnColumnSizes)[i] = boardColSize[i];
	}

	*returnSize = boardSize;

	struct queue_blk * queue = array_queue_init(boardSize * boardColSize[0]);
	int x = click[0];
	int y = click[1];

	if (res[x][y] == 'M') {
	    res[x][y] = 'X';
	} else if (res[x][y] == 'E') {
		struct queue_load load;
		load.x = x;
		load.y = y;
		array_queue_push(queue, load);

		while(!array_queue_is_empty(queue)) {
			struct queue_load out = array_queue_pop(queue);
			int nums = NeighborsHavenumsM(out.x, out.y, res, boardSize, boardColSize);
			if (nums > 0) {
				res[out.x][out.y] = '0' + nums;
			} else {
				res[out.x][out.y] = 'B';
				pushNeighborsInQueue(queue, out.x, out.y, res, boardSize, boardColSize);
			}
		}
	}

	array_queue_exit(queue);
	return res;
}

/*
207. �γ̱�
�������ܹ��� n �ſ���Ҫѡ����Ϊ 0 �� n-1��

��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡� ���磬��Ҫѧϰ�γ� 0 ������Ҫ����ɿγ� 1 ��������һ��ƥ������ʾ����: [0,1]

�����γ������Լ����ǵ��Ⱦ��������ж��Ƿ����������пγ̵�ѧϰ��

ʾ�� 1:

����: 2, [[1,0]]
���: true
����: �ܹ��� 2 �ſγ̡�ѧϰ�γ� 1 ֮ǰ������Ҫ��ɿγ� 0���������ǿ��ܵġ�



1���ڿ�ʼ����ǰ��ɨ���Ӧ�Ĵ洢�ռ䣨ʹ���ڽӱ��������Ϊ 00 �Ľ�������С�

2��ֻҪ���зǿգ��ʹӶ���ȡ�����Ϊ 00 �Ľ�㣬�������������������У����ҽ�������������ڽӽ�㣨��ָ��Ľ�㣩����ȼ� 11���ڼ� 11 �Ժ����������� 11 �Ľ������Ϊ 00 ���ͼ�����ӡ�

3��������Ϊ�յ�ʱ�򣬼�������еĶ�������Ƿ�Ϳγ�����ȼ��ɡ�

Ҳ������DFS �ж��Ƿ���ڻ�

*/
bool canFinish(int numCourses, int** prerequisites,
int prerequisitesSize, int* prerequisitesColSize){

	/*ĳ�ε���ȿ������Ϊ�ÿ�ͬʱ�ж��ٸ�ǰ�ÿ�*/
	int *inDegree = (int *)calloc(numCourses, sizeof(int));
	for (int i = 0; i < prerequisitesSize; i++) {
		inDegree[prerequisites[i][0]]++;
	}

	struct aqueue_blk * queue =  aqueue_init(numCourses);

	for (int i = 0; i < numCourses; i++) {
		if (inDegree[i] == 0) {
			struct aqueue_load load;
			load.data = i;
			aqueue_push(queue, load);
		}
	}
/*
	for_aqueue_entry(queue) {
		printf("%d ",queue->load[i].data);
	}
*/
	int cnt = 0;
	while(!aqueue_is_empty(queue)) {
		struct aqueue_load out = aqueue_pop(queue);
		cnt++;
		for (int i = 0 ; i < prerequisitesSize; i++) {
			if (prerequisites[i][1] == out.data) {
				int x = prerequisites[i][0];
				inDegree[x]--;
				if (inDegree[x] == 0) {
					struct aqueue_load load;
					load.data = x;
					aqueue_push(queue, load);
				}
			}
		}
	}

	return cnt == numCourses;
}
