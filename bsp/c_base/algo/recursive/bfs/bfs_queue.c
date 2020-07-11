/*

BFS


while queue �ǿ�:
	node = queue.pop()
    for node ���������ڽ�� m:
        if m δ���ʹ�:
            queue.push(m)


�����·��!!!!!!

depth = 0 # ��¼�������ڼ���
while queue �ǿ�:
    depth++
    n = queue �е�Ԫ�ظ���
    ѭ�� n ��:
        node = queue.pop()
        for node ���������ڽ�� m:
            if m δ���ʹ�:
                queue.push(m)

*/


/*
994. ���õ�����
�ڸ����������У�ÿ����Ԫ���������������ֵ֮һ��

ֵ 0 ����յ�Ԫ��
ֵ 1 �����������ӣ�
ֵ 2 �����õ����ӡ�
ÿ���ӣ��κ��븯�õ����ӣ��� 4 ���������ϣ����ڵ��������Ӷ��ḯ�á�

����ֱ����Ԫ����û����������Ϊֹ�����뾭������С����������������ܣ����� -1��

�����������������
˼·

ÿһ�֣����ý����ÿһ�����������ӵ��������ڵ���������
�ϡ�һ��ʼ�����õ����ӵ����Ϊ 0��
ÿһ�ָ��û�Ӹ������Ӵ�Ⱦ��֮�������������ϣ�
����������Щ�µĸ������ӵ����Ϊ�Լ���� +1��
������֪������������֮���������ֵ�Ƕ��١�

�㷨

���ǿ�����һ�����������������ģ��һ���̡�
��Ϊ��������ѡ��ȥʹ�����ֵ��С�ģ���֮ǰδʹ�ù��ģ�
��������ȥ�����������ӣ�
��˱�֤ÿһ�����Ӹ���ʱ����ȱ��Ҳ����С�ġ�

���ǻ�Ӧ�ü������״̬�£��Ƿ����������ӡ�

*/
int orangesRotting(int** grid, int gridSize, int* gridColSize)
{
    if (grid == NULL || gridSize == 0 || gridColSize == NULL || gridColSize[0] == 0) {
        return 0;
    }

	int row = gridSize;
	int col = gridColSize[0];

	int queue[row * col];
	int head = 0;
	int rear = 0;

    // bfs
    int count = 0;// count ��ʾ�������ӵ�����
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 2) {
		 queue[rear++] = i * col + j;//�����������
            } else if (grid[i][j] == 1) {
                count++;
            }
        }
    }

    int deep = 0;// round ��ʾ���õ����������߷�����
    while (count > 0 && head != rear) {
	deep++;
	int floorSize = rear - head;

	for (int i = 0; i < floorSize; i++) {
		int pop = queue[head++];// һ����������
		int pop_x = pop / col;
		int pop_y = pop % col;

		int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	        for (int k = 0; k < 4; k++) {
	            int dx = pop_x + dir[k][0];
	            int dy = pop_y + dir[k][1];
	            if (dx < 0 || dx >= row || dy < 0 || dy >= col) {
	                continue;
	            }

	            if (grid[dx][dy] != 1) {
	                continue;
	            }

			grid[dx][dy] = 2;
			count--;
			queue[rear++] = dx * col + dy;//�����������
	        }
	}
    }

    return (count > 0) ? -1: deep;
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

����һ��������Ϸ��Ķ�ά�ַ�����
'M' ����һ��δ�ڳ��ĵ��ף�
'E' ����һ��δ�ڳ��Ŀշ��飬
'B' ����û�����ڣ��ϣ��£����ң�������4���Խ��ߣ�
���׵����ڳ��Ŀհ׷��飬
���֣�'1' �� '8'����ʾ�ж��ٵ�����������ڳ��ķ������ڣ�
'X' ���ʾһ�����ڳ��ĵ��ס�

���ڸ���������δ�ڳ��ķ����У�'M'����'E'����
��һ�����λ�ã��к�����������
�������¹��򣬷�����Ӧλ�ñ�������Ӧ����壺

���һ�����ף�'M'�����ڳ�����Ϸ�ͽ�����- ������Ϊ 'X'��
���һ��û�����ڵ��׵Ŀշ��飨'E'�����ڳ����޸���Ϊ��'B'����
�������к������ڵķ��鶼Ӧ�ñ��ݹ�ؽ�¶��
���һ��������һ���������ڵĿշ��飨'E'�����ڳ���
�޸���Ϊ���֣�'1'��'8'������ʾ���ڵ��׵�������
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
				aqueue_push_last(queue, load);
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

	struct queue_blk * queue = aqueue_init(boardSize * boardColSize[0]);
	int x = click[0];
	int y = click[1];

	if (res[x][y] == 'M') {
	    res[x][y] = 'X';
	} else if (res[x][y] == 'E') {
		struct queue_load load;
		load.x = x;
		load.y = y;
		aqueue_push_last(queue, load);

		while(!aqueue_empty(queue)) {
			struct queue_load out = aqueue_pop_first(queue);
			int nums = NeighborsHavenumsM(out.x, out.y, res, boardSize, boardColSize);
			if (nums > 0) {
				res[out.x][out.y] = '0' + nums;
			} else {
				res[out.x][out.y] = 'B';
				pushNeighborsInQueue(queue, out.x, out.y, res, boardSize, boardColSize);
			}
		}
	}

	aqueue_exit(queue);
	return res;
}

/*
207. �γ̱�
�������ܹ��� n �ſ���Ҫѡ����Ϊ 0 �� n-1��

��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡� ���磬��Ҫѧϰ
�γ� 0 ������Ҫ����ɿγ� 1 ��������һ��ƥ������ʾ��
��: [0,1]

�����γ������Լ����ǵ��Ⱦ��������ж��Ƿ�����������
�γ̵�ѧϰ��

ʾ�� 1:

����: 2, [[1,0]]
���: true
����: �ܹ��� 2 �ſγ̡�ѧϰ�γ� 1 ֮ǰ��
����Ҫ��ɿγ� 0���������ǿ��ܵġ�



1���ڿ�ʼ����ǰ��ɨ���Ӧ�Ĵ洢�ռ䣨ʹ���ڽӱ���
�����Ϊ 00 �Ľ�������С�

2��ֻҪ���зǿգ��ʹӶ���ȡ�����Ϊ 00 �Ľ�㣬
�������������������У����ҽ�������������ڽӽ�
�㣨��ָ��Ľ�㣩����ȼ� 11���ڼ� 11 �Ժ���������
�� 11 �Ľ������Ϊ 00 ���ͼ�����ӡ�

3��������Ϊ�յ�ʱ�򣬼�������еĶ�������Ƿ��
�γ�����ȼ��ɡ�

Ҳ������DFS �ж��Ƿ���ڻ�

*/
bool canFinish(int numCourses, int** prerequisites,
int prerequisitesSize, int* prerequisitesColSize)
{
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
			aqueue_push_last(queue, load);
		}
	}
/*
	for_aqueue_entry(queue) {
		printf("%d ",queue->load[i].data);
	}
*/
	int cnt = 0;
	while(!aqueue_empty(queue)) {
		struct aqueue_load out = aqueue_pop_first(queue);
		cnt++;
		for (int i = 0 ; i < prerequisitesSize; i++) {
			if (prerequisites[i][1] == out.data) {
				int x = prerequisites[i][0];
				inDegree[x]--;
				if (inDegree[x] == 0) {
					struct aqueue_load load;
					load.data = x;
					aqueue_push_last(queue, load);
				}
			}
		}
	}

	return cnt == numCourses;
}

/*
210. �γ̱� II
�Ѷ��е�122
�������ܹ��� n �ſ���Ҫѡ����Ϊ 0 �� n-1��
��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡� ���磬��Ҫѧϰ�γ� 0 ������Ҫ����ɿγ� 1 ��������һ��ƥ������ʾ����: [0,1]
�����γ������Լ����ǵ��Ⱦ�������������Ϊ��ѧ�����пγ������ŵ�ѧϰ˳��
���ܻ��ж����ȷ��˳����ֻҪ����һ�־Ϳ����ˡ����������������пγ̣�����һ�������顣
ʾ�� 1:
����: 2, [[1,0]]
���: [0,1]
����: �ܹ��� 2 �ſγ̡�Ҫѧϰ�γ� 1������Ҫ����ɿγ� 0����ˣ���ȷ�Ŀγ�˳��Ϊ [0,1] ��
ʾ�� 2:
����: 4, [[1,0],[2,0],[3,1],[3,2]]
���: [0,1,2,3] or [0,2,1,3]
����: �ܹ��� 4 �ſγ̡�Ҫѧϰ�γ� 3����Ӧ������ɿγ� 1 �Ϳγ� 2�����ҿγ� 1 �Ϳγ� 2 ��Ӧ�����ڿγ� 0 ֮��
     ��ˣ�һ����ȷ�Ŀγ�˳���� [0,1,2,3] ����һ����ȷ�������� [0,2,1,3] ��
˵��:
1.	������Ⱦ��������ɱ�Ե�б��ʾ��ͼ�Σ��������ڽӾ���������μ�ͼ�ı�ʾ����
2.	����Լٶ�������Ⱦ�������û���ظ��ıߡ�
��ʾ:
1.	��������൱�ڲ���һ��ѭ���Ƿ����������ͼ�С��������ѭ�����򲻴�������������˲�����ѡȡ���пγ̽���ѧϰ��
2.	ͨ�� DFS ������������ - һ������Coursera�ľ�����Ƶ�̳̣�21���ӣ���������������Ļ������
3.	��������Ҳ����ͨ�� BFS ��ɡ�
1.	nums1��nums2 �������С��������1000��

*/


/*
����������ȣ�������ͼ����һ��� v ������ȼ�Ϊ��ǰ���д��������������յ�Ϊ v �ĵıߵ���Ŀ�����ȣ�������ͼ����һ��� v ������ȼ�Ϊ��ǰ�������Ϊ v ��ָ���������ıߵ���Ŀ��ÿ�δ����Ϊ 0 �Ľ�㿪ʼ��������С����Ϊ 0 ����ʾû��ǰ�ý�㡣�������Ϊ 0 �Ľ�㣬��������ָ��Ľ������ -1 ���ٰ��µ����Ϊ 0 �Ľ�������С�������ж�������ϣ����Ǻ��ܽ����������˵����Щ����γɻ���
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize,
	int* prerequisitesColSize, int* returnSize)
{
	int inDegree[numCourses];
	memset(inDegree, 0, sizeof(inDegree));

	int matrix[numCourses][numCourses];
	int matrixCnt[numCourses];
	memset(matrix, 0, sizeof(matrix));
	memset(matrixCnt, 0, sizeof(matrixCnt));

	for (int i = 0; i < prerequisitesSize; i++) {
		//printf("%d", prerequisites[i][0]);
		inDegree[prerequisites[i][0]]++;
		int cnt = matrixCnt[prerequisites[i][1]];//out degree
		matrix[prerequisites[i][1]][cnt] = prerequisites[i][0];
		matrixCnt[prerequisites[i][1]]++;
	}

	struct List list;
	queue_init(&list);
	for (int i = 0; i < numCourses; i++) {
		if (inDegree[i] == 0) {
			queue_push_key(&list, i);
		}
	}

	int *ret = calloc(numCourses, sizeof(int));
	int retSize = 0;
	while(!queue_empty(&list)) {
		struct Node *popNode = queue_pop(&list);
		struct DataEntry *entry;
		entry = NODE_ENTRY(popNode, struct DataEntry, node);
		ret[retSize++] = entry->key;
		for(int i = 0; i < matrixCnt[entry->key]; i++) {
			int idx = matrix[entry->key][i];
			if (--inDegree[idx] == 0) {
				queue_push_key(&list, idx);
			}
		}
	}

	//printf("%d\n",retSize);
	*returnSize = retSize;
	if (retSize != numCourses)
		*returnSize = 0;
	return ret;
}

/*
22. ��������
�Ѷ��е�955
���� n �����������ŵĶ������������һ�������������ܹ��������п��ܵĲ��� ��Ч�� ������ϡ�

ʾ����
���룺n = 3
�����[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]

*/
char** generateParenthesis(int n, int* returnSize)
{
	*returnSize = 0;
	if (n == 0) {
		return NULL;
	}

	char** res = (char**)calloc(1024 * 1024, sizeof(char*));
	struct List list;
	queue_init(&list);

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->left = n;
	entry->right = n;
	memset(entry->data, 0, sizeof(entry->data));
	ListAddTail(&list, &entry->node);

	while(!queue_empty(&list)) {
		struct Node *pop = queue_pop(&list);
		struct DataEntry  *popEntry = NODE_ENTRY(pop, struct DataEntry, node);

		if (popEntry->left == 0 && popEntry->right == 0) {
			res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
			strcpy(res[*returnSize], popEntry->data);
			(*returnSize)++;
		}

		if (popEntry->left > 0) {
			struct DataEntry  *leftentry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
			leftentry->left = popEntry->left - 1;
			leftentry->right = popEntry->right;
			strcpy(leftentry->data, popEntry->data);
			strcat(leftentry->data, "(");
			ListAddTail(&list, &leftentry->node);
		}

		if (popEntry->right > 0 && popEntry->left < popEntry->right) {
			struct DataEntry  *rightentry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
			rightentry->left = popEntry->left;
			rightentry->right = popEntry->right - 1;
			strcpy(rightentry->data, popEntry->data);
			strcat(rightentry->data, ")");
			ListAddTail(&list, &rightentry->node);
		}
	}

	return res;
}

/*
279. ��ȫƽ����
���������� n���ҵ����ɸ���ȫƽ���������� 1, 4, 9, 16, ...��ʹ�����ǵĺ͵��� n������Ҫ����ɺ͵���ȫƽ�����ĸ������١�

ʾ�� 1:

����: n = 12
���: 3
����: 12 = 4 + 4 + 4.
ʾ�� 2:

����: n = 13
���: 2
����: 13 = 4 + 9.
*/
int numSquares(int n){
	struct List queue;
	queue_init(&queue);

	queue_push_key(&queue, n);
	int level = 0;
	while(!queue_empty(&queue)) {
		level++;

		// ÿһ��Ĺ�ȱ���
		int size = queue_size(&queue);
		for (int i = 0; i < size; i++) {
			struct DataEntry *top = queue_pop_entry(&queue);

			for (int j = 1; j <= sqrt(n); j++) {
				int target = top->key - pow(j, 2);
				// ˵���ѵ����ƽ����
				if (target < 0)
					break;
				// �����ǹ�ȱ��������Ե�������0ʱ���϶������·��
				if (target == 0)
					return level;
				queue_push_key(&queue, target);
			}
		}
	}

	return -1;
}

/*
752. ��ת����
�Ѷ��е�106
����һ�������ĸ�Բ�β��ֵ�ת������ÿ�����ֶ���10�����֣� '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' ��ÿ�����ֿ���������ת������� '9' ��Ϊ  '0'��'0' ��Ϊ '9' ��ÿ����ת��ֻ����תһ�����ֵ�һλ���֡�
���ĳ�ʼ����Ϊ '0000' ��һ�������ĸ����ֵ����ֵ��ַ�����
�б� deadends ������һ���������֣�һ�����ֵ����ֺ��б�����κ�һ��Ԫ����ͬ����������ᱻ�����������޷��ٱ���ת��
�ַ��� target ������Խ��������֣�����Ҫ������С����ת���������������β��ܽ��������� -1��

ʾ�� 1:
���룺deadends = ["0201","0101","0102","1212","2002"], target = "0202"
�����6
���ͣ�
���ܵ��ƶ�����Ϊ "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"��
ע�� "0000" -> "0001" -> "0002" -> "0102" -> "0202" �����������ǲ��ܽ����ģ�
��Ϊ�������� "0102" ʱ������ͻᱻ������

*/
/*
���ǿ��Խ� 0000 �� 9999 �� 10000 ״̬����ͼ�ϵ� 10000 ���ڵ㣬�����ڵ�֮�����һ���ߣ����ҽ����������ڵ��Ӧ��״ֻ̬�� 1 λ��ͬ���Ҳ�ͬ����λ��� 1������ 0 �� 9 Ҳ��� 1 ��������������������ڵ���������� deadends �С���ô���յĴ𰸼�Ϊ 0000 �� target �����·����

�����ù�������������ҵ����·������ 0000 ��ʼ����������ÿһ��״̬����������չ����� 8 ��״̬���������ĵ� i = 0, 1, 2, 3 λ���� 1 ����� 1������Щ״̬��û�����������Ҳ��� deadends �е�״̬ȫ�����뵽�����У�����������������ע�� 0000 �����п���Ҳ�� deadends �С�

*/
int openLock(char ** deadends, int deadendsSize, char * target)
{
	int i,j,k, ret, len, steps = -1;
	char start[] = "0000";

	if (strcmp(start, target) == 0)
		return 0;

	struct List dlist;
	struct List *list = &dlist;
	queue_init(list);

	struct HashTable dht;
	struct HashTable *ht = &dht;
	HashInit(ht, 2 << 10, hashequal_str, hashcode_str);

    	for (i = 0; i < deadendsSize; i++) {
		struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		entry->key = deadends[i];
		HashAdd(ht, &entry->node);
	}

	struct DataEntry cmpEntry;
	cmpEntry.key = start;
	struct DataEntry *find = hashFind(ht, &cmpEntry);
	if (find != NULL) {
		return -1;
	}

	struct DataEntry  *entryQueue = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entryQueue->key = start;
	ListAddTail(list, &entryQueue->node);

    	while(!queue_empty(list)) {
        ++steps;
        len = queue_size(list);
        for (k = 0; k < len; k++) {
		struct DataEntry *pop = queue_pop_entry(list);
                if (strcmp(pop->key, target) == 0) {
			//free(pop);
			//HashDeinit(ht, node_free);
			return steps;
                }

		//struct DataEntry *entryhash = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		//entryhash->key = pop->key;
		//HashAdd(ht, &entryhash->node);

            	for (i = 0; i < 4; i++) {
			for (j = -1; j < 2; j += 2) {
				char *newstr = strdup(pop->key);
				newstr[i] = (newstr[i] - '0' + j + 10)%10 + '0';

				struct DataEntry nextEntry;
				nextEntry.key = newstr;
				struct DataEntry *find =  hashFind(ht, &nextEntry);
				if (find != NULL) {
					continue;
				}

				struct DataEntry *entryhash = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
				entryhash->key = newstr;
				HashAdd(ht, &entryhash->node);

				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->key = newstr;
				ListAddTail(list, &entry->node);
			}
		}
	}
	}

	//HashDeinit(ht, node_free);
	return -1;
}

/*
863. �����������о���Ϊ K �Ľ��
����һ�������������и���� root���� һ��Ŀ���� target ����һ������ֵ K ��

���ص�Ŀ���� target ����Ϊ K �����н���ֵ���б� �𰸿������κ�˳�򷵻ء�



ʾ�� 1��

���룺root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
�����[7,4,1]
���ͣ�
������Ϊ��Ŀ���㣨ֵΪ 5������Ϊ 2 �Ľ�㣬
ֵ�ֱ�Ϊ 7��4���Լ� 1
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 /*
����ʹ�� DFS ������������Ϊÿ���ڵ㱣���丸��㣻
ʹ�� BFS �������������������ӡ��Һ��ӡ�����㣩���������� K ��ʱ�������е�ȫ����㼴Ϊ����

ע�⣺

BFS Ҫ�����ѷ��ʽ�㣻
ÿ�ζ�����ǰ������ȫ��Ԫ����������һ����㣻

 */
void dfs(struct List *listFather, struct TreeNode* root, struct TreeNode* father)
{
	if (root == NULL) {
		return;
	}

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->cur = root;
	entry->father = father;
	entry->visited = 0;
	ListAddTail(listFather, &entry->node);

	dfs(listFather, root->left, root);
	dfs(listFather, root->right, root);
}

void setVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			entry->visited = 1;
		}
	}
}

bool checkVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->visited;
		}
	}

	return false;
}

struct TreeNode* getFather(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->father;
		}
	}

	return NULL;
}


int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
	struct List dListFather;
	struct List *listFather = &dListFather;

	ListInit(listFather);
	dfs(listFather, root, NULL); //��¼�����

	struct List dqueue;
	struct List *queue = &dqueue;

	queue_init(queue);

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->cur = target;
	ListAddTail(queue, &entry->node);
	setVisited(listFather, target);

	while(!queue_empty(queue)) {
		if (K-- == 0) {
			*returnSize = 0;
			int *res = (int *)calloc(2048, sizeof(int));
			while(!queue_empty(queue)) {
				struct DataEntry *pop = queue_pop_entry(queue);
				res[*returnSize] = pop->cur->val;
				(*returnSize)++;
			}

			return res;
		}

		int qSize = queue_size(queue);
		for (int i = 0; i < qSize; i++) {
			struct DataEntry *pop = queue_pop_entry(queue);
			if (pop->cur->left && !checkVisited(listFather, pop->cur->left)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->left;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->left);
			}

			if (pop->cur->right && !checkVisited(listFather, pop->cur->right)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->right;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->right);
			}

			struct TreeNode* father = getFather(listFather, pop->cur);
			if (father != NULL && !checkVisited(listFather, father)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = father;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, father);
			}
		}
	}

	return NULL;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define MAXSIZE 510
struct TreeNode** parent_array;
int flag[MAXSIZE];
int count;

void get_parent(struct TreeNode* node, struct TreeNode** parent_array);
void dfs(struct TreeNode* node, int K, int dis, int* res);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
    if (root == NULL || target == NULL || K < 0 || K > 500) {
        *returnSize = 0;
        return NULL;
    }

    // ��������������ڴ�
    parent_array = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAXSIZE);
    memset(parent_array, 0, MAXSIZE * sizeof(struct TreeNode*));
    // flag�����ʼ�������ڱ�Ƿ��ʹ��Ľ��
    memset(flag, 0, MAXSIZE * sizeof(int));
    // �������Ҫ��Ľ��ֵ�Ľ������
    int *res = (int *)malloc(sizeof(int) * MAXSIZE);
    memset(res, -1, MAXSIZE * sizeof(int));

    // �����������ҵ�ÿ�����ĸ���㣬���ý���ֵ��Ϊparent_array����������parent_array�д�Ŷ�Ӧ�����
    get_parent(root, parent_array);

    // DFS����
    count = 0;
    flag[target->val] = 1;
    dfs(target, K, 0, res);

    // ���ؽ��
    *returnSize = count;
    return res;
}

void get_parent(struct TreeNode* node, struct TreeNode** parent_array)
{
    if (node->right != NULL) {
        parent_array[node->right->val] = node;
        get_parent(node->right, parent_array);
    }
    if (node->left != NULL) {
        parent_array[node->left->val] = node;
        get_parent(node->left, parent_array);
    }
}

void dfs(struct TreeNode* node, int K, int dis, int* res)
{
    if (dis == K) {
        res[count] = node->val;
        count++;
        return;
    }

    if (node->left != NULL && flag[node->left->val] != 1) {
        flag[node->left->val] = 1;
        dfs(node->left, K, dis + 1, res);
    }

    if (node->right != NULL && flag[node->right->val] != 1) {
        flag[node->right->val] = 1;
        dfs(node->right, K, dis + 1, res);
    }

    if (parent_array[node->val] != 0 && flag[parent_array[node->val]->val] != 1) {
        flag[parent_array[node->val]->val] = 1;
        dfs(parent_array[node->val], K, dis + 1, res);
    }
}

/*
1102. �÷���ߵ�·��
�Ѷ��е�33
����һ�� R �� C �е��������� A�������ϵ�·���� [0,0] ��ʼ���� [R-1,C-1] ������
·�����ĸ����������ϡ��¡����ң�չ������һ���ѷ��ʵ�Ԫ���ƶ�����һ���ڵ�δ���ʵ�Ԫ��
·���ĵ÷��Ǹ�·���ϵ� ��С ֵ�����磬·�� 8 ��  4 ��  5 ��  9 ��ֵΪ 4 ��
�ҳ�����·���е÷� ��� ������·���������� �÷֡�

ʾ�� 1��

���룺[[5,4,5],[1,2,6],[7,4,6]]
�����4
���ͣ�
�÷���ߵ�·���û�ɫͻ����ʾ��

*/

/*
����ֱ��ÿ��ȡ·���е����ֵ������һ��·������Ҫ�������ȶ��У��ѵ�ǰ�������ߵ�·������ֵ�Ӵ�С�ź��򣬲�������֦��������ܻ��޽⣻ÿ�ζ��ߵ�ǰ·���е����ֵ��������ߵ��յ�ʱ����Ȼ��������·���з�ֵ�����ֵ�����ؽ�����ɣ�ÿ��ȡ����ǰ���ʱ��Ҫ����һ�µ�ǰ�Ľ�������������������ߣ�goodgoodstudy-5���ӣ�https://leetcode-cn.com/problems/path-with-maximum-minimum-value/solution/li-yong-you-xian-dui-lie-bfsqiu-lu-jing-zhong-de-z/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
int maximumMinimumPath(int** A, int ASize, int* AColSize)
{
	int row = ASize;
	int col = AColSize[0];

	struct HeapSort *hp = heapsort_init(col * row, PRIORITY_QUEUE_MAX);
	int visited[row][col];
	memset(visited, 0, sizeof(visited));

	struct heapEntry node;
	node.key = A[0][0];
	node.x = 0;
	node.y = 0;
	heapsort_push(hp, node);
	visited[0][0] = 1;

	int d[4][2] = { { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1 } };
	int res = INT_MAX;
	while(!heapsort_empty(hp)) {
		struct heapEntry pop = heapsort_pop(hp);
		res = fmin(res, pop.key);
		if (pop.x == row -1 && pop.y == col - 1) {
			return res;
		}

		for (int i = 0; i < 4; i++) {
			int x = pop.x + d[i][0];
			int y = pop.y + d[i][1];

			if (x < 0 || x >= row || y < 0 || y >= col) {
				continue;
			}

			if (visited[x][y] == 1) {
				continue;
			}

			struct heapEntry node;
			node.key = A[x][y];
			node.x = x;
			node.y = y;
			heapsort_push(hp, node);
			visited[x][y] = 1;
		}
	}

	return res;
}

