/*         BFS

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


1)�������һ���8������
2)�໥��������������ȳ���
	���ǰ������
	���Ⱥ�������
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


/*
200. ��������
�Ѷ��е�647
����һ���� '1'��½�أ��� '0'��ˮ����ɵĵĶ�ά����
������������е����������
�������Ǳ�ˮ��Χ������ÿ������ֻ����ˮƽ�������ֱ����
�����ڵ�½�������γɡ�
���⣬����Լ��������������߾���ˮ��Χ��

ʾ�� 1:
����:
[
['1','1','1','1','0'],
['1','1','0','1','0'],
['1','1','0','0','0'],
['0','0','0','0','0']
]
���: 1
*/
void bfs(char** grid, int row, int col, int x, int y)
{
	int queue[row * col];
	int head = 0;
	int rear = 0;

	queue[rear++] = x * col + y;
	grid[x][y] = '0'; /*���޸ĺ����queue���������*/

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	int deep = 0;
	while(head != rear) {
		int floorSize = rear - head;
		deep++;

		for (int i = 0; i < floorSize; i++) {
			int pop = queue[head++];
			int popx = pop / col;
			int popy = pop % col;

			for (int k = 0; k < 4; k++) {
				int nx = popx + d[k][0];
				int ny = popy + d[k][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (grid[nx][ny] != '1') {
					continue;
				}

				grid[nx][ny] = '0';
				queue[rear++] = nx * col +ny;
			}
		}
	}
}

int numIslands(char** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = gridColSize[0];

	if (grid == NULL || gridSize <= 0 || gridColSize == NULL)
		return 0;

	int num = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == '1') {
				num++;
				bfs(grid, row, col, i, j);
			}
		}
	}

	return num;
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
	int inDegree[numCourses];
	memset(inDegree, 0, sizeof(inDegree));//!!!
	for (int i = 0; i < prerequisitesSize; i++) {
		inDegree[prerequisites[i][0]]++;
	}

	int queue[numCourses];
	int head = 0;
	int rear = 0;

	for (int i = 0; i < numCourses; i++) {
		if (inDegree[i] == 0) {
			queue[rear++] = i;
		}
	}

	int cnt = 0;
	while(head != rear) {
		int floorSize = rear - head;
		for (int k = 0; k < floorSize; k++) {
			int pop = queue[head++];
			cnt++;
			for (int i = 0 ; i < prerequisitesSize; i++) {
				if (prerequisites[i][1] == pop) {
					int x = prerequisites[i][0];
					inDegree[x]--;
					if (inDegree[x] == 0) {
						queue[rear++] = x;
					}
				}
			}
		}
	}

	return cnt == numCourses;
}

/*
279. ��ȫƽ����
���������� n���ҵ����ɸ���ȫƽ���������� 1, 4, 9, 16, ...��
ʹ�����ǵĺ͵��� n������Ҫ����ɺ͵���ȫƽ�����ĸ���
���١�

ʾ�� 1:

����: n = 12
���: 3
����: 12 = 4 + 4 + 4.
ʾ�� 2:

����: n = 13
���: 2
����: 13 = 4 + 9.
*/
int numSquares(int n)
{
	int queue[1024 * 1024 * 10];
	int head = 0;
	int rear = 0;

	queue[rear++] = n;
	int deep = 0;

	while(head != rear) {
		deep++;

		// ÿһ��Ĺ�ȱ���
		int floorSize = rear - head;
		for (int i = 0; i < floorSize; i++) {
			int top = queue[head++];
			for (int j = 1; j <= sqrt(top); j++) {
				int target = top - pow(j, 2);
				// ˵���ѵ����ƽ����
				if (target < 0)
					break;
				/* �����ǹ�ȱ��������Ե�������0ʱ��
				�϶������·��*/
				if (target == 0)
					return deep;

				queue[rear++] = target;
			}
		}
	}

	return -1;
}


/*
752. ��ת����
�Ѷ��е�106
����һ�������ĸ�Բ�β��ֵ�ת������ÿ�����ֶ���10������
�� '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' ��ÿ�����ֿ���������ת��
����� '9' ��Ϊ  '0'��'0' ��Ϊ '9' ��ÿ����ת��ֻ����תһ�����ֵ�
һλ���֡�
���ĳ�ʼ����Ϊ '0000' ��һ�������ĸ����ֵ����ֵ��ַ�����
�б� deadends ������һ���������֣�һ�����ֵ����ֺ��б����
�κ�һ��Ԫ����ͬ����������ᱻ�����������޷��ٱ���ת��
�ַ��� target ������Խ��������֣�����Ҫ������С����ת������
���������β��ܽ��������� -1��
ʾ�� 1:
���룺deadends = ["0201","0101","0102","1212","2002"], target = "0202"
�����6
���ͣ�
���ܵ��ƶ�����Ϊ "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"��
ע�� "0000" -> "0001" -> "0002" -> "0102" -> "0202" �����������ǲ��ܽ����ģ�
��Ϊ�������� "0102" ʱ������ͻᱻ������
*/
/*
���ǿ��Խ� 0000 �� 9999 �� 10000 ״̬����ͼ�ϵ� 10000 ���ڵ㣬
�����ڵ�֮�����һ���ߣ����ҽ����������ڵ��Ӧ��״̬
ֻ�� 1 λ��ͬ���Ҳ�ͬ����λ��� 1������ 0 �� 9 Ҳ��� 1 ���������
�����������ڵ���������� deadends �С���ô���յĴ𰸼�Ϊ 0000
�� target �����·����

�����ù�������������ҵ����·������ 0000 ��ʼ������
����ÿһ��״̬����������չ����� 8 ��״̬��
�������ĵ� i = 0, 1, 2, 3 λ���� 1 ����� 1������Щ״̬��û������
�����Ҳ��� deadends �е�״̬ȫ�����뵽�����У�
����������������ע�� 0000 �����п���Ҳ�� deadends �С�

*/
#define VISITED_OFFSET 10000
int openLock(char ** deadends, int deadendsSize, char * target)
{
	int i,j,k, ret, floorSize, deep = -1;
	char start[] = "0000";

	if (strcmp(start, target) == 0)
		return 0;

	int targetint = atoi(target);

	int queue[10000];
	int head = 0;
	int rear = 0;
	int visited[20000];
	memset(visited, 0, sizeof(visited));

    	for (i = 0; i < deadendsSize; i++) {
		int deadint = atoi(deadends[i]);
		visited[deadint + VISITED_OFFSET] = 1;
	}

	int startint = atoi(start);
	if (visited[startint + VISITED_OFFSET] == 1)
		return -1;

	queue[rear++] = startint;
	visited[startint + VISITED_OFFSET] = 1;

    	while(head != rear) {
	        ++deep;
	        floorSize = rear - head;
	        for (k = 0; k < floorSize; k++) {
			int pop = queue[head++];
	                if (pop == targetint) {
				return deep;
	                }

	            	for (i = 0; i < 4; i++) {//�ĸ�λ��
				for (j = -1; j < 2; j += 2) {// 2������
					char newstr[6];
					sprintf(newstr, "%04d", pop);
					newstr[i] = (newstr[i] - '0' + j + 10)%10 + '0';
					int newobj = atoi(newstr);
					if (visited[newobj + VISITED_OFFSET] == 1) {
						continue;
					}

					queue[rear++] = newobj;
					visited[newobj + VISITED_OFFSET] = 1;
				}
			}
		}
	}

	return -1;
}

/*
1102. �÷���ߵ�·��
�Ѷ��е�33
����һ�� R �� C �е��������� A�������ϵ�·���� [0,0] ��ʼ��
�� [R-1,C-1] ������
·�����ĸ����������ϡ��¡����ң�չ����
��һ���ѷ��ʵ�Ԫ���ƶ�����һ���ڵ�δ���ʵ�Ԫ��
·���ĵ÷��Ǹ�·���ϵ� ��С ֵ�����磬·�� 8 ��  4 ��  5 ��  9
��ֵΪ 4 ��
�ҳ�����·���е÷� ��� ������·���������� �÷֡�

ʾ�� 1��

���룺[[5,4,5],[1,2,6],[7,4,6]]
�����4
���ͣ�
�÷���ߵ�·���û�ɫͻ����ʾ��

*/

/*
����ֱ��ÿ��ȡ·���е����ֵ������һ��·����
��Ҫ�������ȶ��У��ѵ�ǰ�������ߵ�·������ֵ�Ӵ�С
�ź��򣬲�������֦��������ܻ��޽⣻ÿ�ζ��ߵ�ǰ·��
�е����ֵ��������ߵ��յ�ʱ����Ȼ��������·���з�ֵ
�����ֵ�����ؽ�����ɣ�ÿ��ȡ����ǰ���ʱ��Ҫ����һ
�µ�ǰ�Ľ����������������
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

/*
317. �뽨��������ľ���
�Ѷ�����29
���Ǹ����ز������̣���Ҫѡ��һƬ�յ� ��һ����¥��������ⶰ��¥������һ�������ܱ���ʩ���ȽϷ���ĵط���ͨ�����У���ϣ�������������� ��̵ľ���� �ڵִ��ܱ�ȫ���Ľ�����������������ѵ�ѡַ���ܱ�ȫ��������� ��̾���͡�

��ʾ��
��ֻ��ͨ�����ϡ��¡������ĸ��������ƶ���
����һ���� 0��1 �� 2 ��ɵĶ�ά�������У�
"	0 �������������ͨ����ѡ����Ŀյ�
"	1 �������޷�ͨ�еĽ�����
"	2 �������޷�ͨ�е��ϰ���

ʾ����
���룺[[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
�����7
������
�������������� (0,0)��(0,4) �� (2,2) �Լ�һ��λ�� (0,2) ���ϰ��
�����ܾ���֮�� 3+3+1=7 ���ţ�����λ�� (1,2) �Ƿ���Ҫ������ŵص㣬�ʷ���7��
*/
#define QUEUE_LEN (10000)
int MinDist(int sum, int res){
    if(sum < res){
        return sum;
    }
    return res;
}
int shortestDistance(int** grid, int gridSize, int* gridColSize){
    int sum[gridSize][*gridColSize];
    memset(sum, 0, gridSize * (*gridColSize) * sizeof(int));
    int dist[gridSize][*gridColSize];
    memset(dist, 0, gridSize * (*gridColSize) * sizeof(int));
    int queue[QUEUE_LEN][2];
    memset(queue, 0, QUEUE_LEN * 2 * sizeof(int));
    int dirlist[][2] = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };
    int head = 0;
    int tail = 0;
    int res = INT_MAX;

    int val = 0;
    for(int i  = 0; i < gridSize; i++){
        for(int j = 0; j < *gridColSize; j++){
            if(grid[i][j] == 1){
                queue[tail][0] = i;
                queue[tail][1] = j;
                tail++;
               // printf("pos is [%d, %d]", i, j);
                res = INT_MAX;
                while(head != tail){
                    int a = queue[head][0];
                    int b = queue[head][1];
                    head++;
                    for(int k = 0; k < 4; k++){
                        int x = a + dirlist[k][0];
                        int y = b + dirlist[k][1];
                        if(x >= 0 && x < gridSize && y >= 0 && y < *gridColSize && grid[x][y] == val){
                            --grid[x][y];
                            dist[x][y] = dist[a][b] + 1;
                            sum[x][y] += dist[x][y];// todo
                            res = MinDist(sum[x][y], res);
                            queue[tail][0] = x;
                            queue[tail][1] = y;
                            tail++;
                        }
                    }
                }
                val--;
                if(res == INT_MAX){
                    return -1;
                }
            }
        }
    }
    return res;
}

/*
490. �Թ�
�Ѷ��е�43
�ɿյغ�ǽ��ɵ��Թ�����һ��������������������ĸ������������������ǽ��ǰ����ֹͣ����������ͣ��ʱ������ѡ����һ������
���������ʼλ�ã�Ŀ�ĵغ��Թ����ж����ܷ���Ŀ�ĵ�ͣ�¡�
�Թ���һ��0��1�Ķ�ά�����ʾ�� 1��ʾǽ�ڣ�0��ʾ�յء�����Լٶ��Թ��ı�Ե����ǽ�ڡ���ʼλ�ú�Ŀ�ĵص�����ͨ���кź��кŸ�����

ʾ�� 1:
���� 1: �Թ������¶�ά�����ʾ

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

���� 2: ��ʼλ������ (rowStart, colStart) = (0, 4)
���� 3: Ŀ�ĵ����� (rowDest, colDest) = (4, 4)

���: true

*/
bool hasPath(int** maze, int mazeSize, int* mazeColSize, int* start, int startSize,
int* destination, int destinationSize)
{
	int row = mazeSize;
	int col = *mazeColSize;

	int visited[row][col];
	memset(visited, 0, sizeof(visited));

        int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
	int queueSize = fmax(1024, row * col);
	int queue[queueSize];
	memset(queue, 0, sizeof(queue));
	int head = 0;
	int rear = 0;
        queue[rear++] = start[0] * col + start[1];
        visited[start[0]][start[1]] = true;
        while (head != rear) {
		int top = queue[head++];
		int s[2];
		s[0] = top / col;
		s[1] = top % col;

            if (s[0] == destination[0] && s[1] == destination[1])
                return true;
            for (int i = 0; i < 4; i++) {
                int x = s[0] + dirs[i][0];
                int y = s[1] + dirs[i][1];
                while (x >= 0 && y >= 0 && x < row && y < col && maze[x][y] == 0) {
                    x += dirs[i][0];
                    y += dirs[i][1];
                }

			x -= dirs[i][0];
			y -= dirs[i][1];

                if (visited[x][y] == 0) {
			queue[rear++] = x * col + y;
                    visited[x][y] = 1;
                }
            }
        }
        return false;
}

/*
505. �Թ� II
�Ѷ��е�32
�ɿյغ�ǽ��ɵ��Թ�����һ��������������������ĸ������������������ǽ��ǰ����ֹͣ����������ͣ��ʱ������ѡ����һ������
���������ʼλ�ã�Ŀ�ĵغ��Թ����ҳ�����ͣ��Ŀ�ĵص���̾��롣����Ķ����������ʼλ�ã�����������Ŀ�ĵأ������������Ŀյظ�����������޷�ͣ��Ŀ�ĵأ����� -1��
�Թ���һ��0��1�Ķ�ά�����ʾ�� 1��ʾǽ�ڣ�0��ʾ�յء�����Լٶ��Թ��ı�Ե����ǽ�ڡ���ʼλ�ú�Ŀ�ĵص�����ͨ���кź��кŸ�����

ʾ�� 1:
���� 1: �Թ������¶�ά�����ʾ

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

���� 2: ��ʼλ������ (rowStart, colStart) = (0, 4)
���� 3: Ŀ�ĵ����� (rowDest, colDest) = (4, 4)

���: 12

����: һ�����·�� : left -> down -> left -> down -> right -> down -> right��
             �ܾ���Ϊ 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12��

*/
int shortestDistance(int** maze, int mazeSize, int* mazeColSize,
int* start, int startSize, int* destination, int destinationSize){
	int row = mazeSize;
	int col = *mazeColSize;

	int distance[row][col];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			distance[i][j] = INT_MAX;
		}
	}

	int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
	int queueSize = fmax(1024, row * col);
	int queue[queueSize];
	memset(queue, 0, sizeof(queue));
	int head = 0;
	int rear = 0;
	queue[rear++] = start[0] * col + start[1];
	distance[start[0]][start[1]] = 0;

        while (head != rear) {
		int top = queue[head++];
		int s[2];
		s[0] = top / col;
		s[1] = top % col;
            for (int i = 0; i < 4; i++) {
                int x = s[0] + dirs[i][0];
                int y = s[1] + dirs[i][1];
			int count = 0;
                while (x >= 0 && y >= 0 && x < row && y < col && maze[x][y] == 0) {
                    x += dirs[i][0];
                    y += dirs[i][1];
			count++;
                }

			x -= dirs[i][0];
			y -= dirs[i][1];

			if (distance[s[0]][s[1]] + count < distance[x][y]) {
				distance[x][y] = distance[s[0]][s[1]] + count;
				queue[rear++] = x * col + y;
			}
            }
        }

        return distance[destination[0]][destination[1]] == INT_MAX ? -1 : distance[destination[0]][destination[1]];
}

/*
22. ��������dfs
bfs  left right Ϊ����������0 */
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
1293. �����е����·��
�Ѷ�����63
����һ�� m * n ����������ÿ����Ԫ���� 0���գ����� 1���ϰ����ÿһ�������������ڿհ׵�Ԫ�����ϡ��¡������ƶ���
����� ��� �������� k ���ϰ�����ҳ������Ͻ� (0, 0) �����½� (m-1, n-1) �����·����������ͨ����·������Ĳ���������Ҳ���������·�����򷵻� -1��

ʾ�� 1��
���룺
grid =
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]],
k = 1
�����6
���ͣ�
�������κ��ϰ������·���� 10��
����λ�� (3,2) �����ϰ������·���� 6 ����·���� (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).

*/
/*
1 ���ϰ���k ��Ϊ���ɾ������ٸ��ϰ�
2 ʹ�ö�λ����visit ��Ϊ�ܷ�
�������ж�������
-1 ��δ����
������·���Ӹõ���� �����پ������ϰ�����
����1��A·������õ�ʱ �������پ���3���ϰ�
B·������õ�ʱ �������پ���1���ϰ�����ΪB·������A·����
���ܼ������
����2��A·������õ�ʱ �������پ���3���ϰ�B·����
��õ�ʱ �������پ���3���ϰ�����ΪB·����A·���޲��
���ؼ������ps��3ά����Ҳ�������˼3 C����ʹ������ʵ�ֶ���
ͨ�����Ż�����ִ��ʱ�䣨ȱ�� ����ϳ���ps�����ʹ��ѭ����
�еĻ� ���г������ֻ��Ҫ 39394
*/
int shortestPath(int** grid, int gridSize, int* gridColSize, int k)
{
	int row = gridSize;
	int col = *gridColSize;
	int queue[100000][2];//0---xy , 1 --k
	int head = 0;
	int rear = 0;
	queue[rear][0] = 0;
	queue[rear++][1] = k;
	int deep = -1;
	int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int visited[row][col];
	memset(visited, -1, sizeof(visited));

	while(head != rear) {
		int floorSize = rear - head;
		deep++;
		for (int i = 0; i < floorSize; i++) {
			int cx = queue[head][0] / col;
			int cy = queue[head][0] % col;
			int ck = queue[head++][1];

			if (cx == row -1 && cy == col -1) {
				return deep;
			}

			for (int i = 0; i < 4; i++) {
				int nx = cx + d[i][0];
				int ny = cy + d[i][1];
				int nk = ck;

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (ck - grid[nx][ny] > visited[nx][ny]) {
					queue[rear][0] = nx * col + ny;
					queue[rear++][1] = ck - grid[nx][ny];
					visited[nx][ny] = ck - grid[nx][ny];
				}
			}
		}
	}

	return -1;
}

/*
407. ����ˮ II
�Ѷ�����214
����һ�� m x n �ľ������е�ֵ��Ϊ�Ǹ������������ά�߶�ͼÿ����Ԫ�ĸ߶ȣ������ͼ����״����ܽӶ����������ˮ��

ʾ����
�������� 3x6 �ĸ߶�ͼ:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

���� 4 ��
*/
/*
Given the following 3x6 height map:
[
[1,4,3,1,3,2],
[3,2,1,3,2,4],
[2,3,3,2,3,1]
]
*/

/*
Q<x,y,h>�����ȼ����У�
����ͼ��������Ϊ��һ���߽磬����Q��
�ܴ�ˮ�� = 0;
while(Q����){
    <x,y,h> = Q�����Ѷ�;
    for(<nx,ny> in <x,y>����������){
        if(<nx,ny> ��ͼ�� �� �ڱ߽��ڲ�){
            �ܴ�ˮ�� += max(0, h - <nx,ny>�ĸ߶�);
            �±߽�λ��<nx,ny, max(h,<nx,ny>�ĸ߶�)>��Q;
        }
    }
}
*/
/*
����"��һ��Ԫ��"�������е�����Ϊ 0 �Ļ���
�򸸽ڵ���ӽڵ��λ�ù�ϵ���£�
(01) ����Ϊi�����ӵ������� (2*i+1);
(02) ����Ϊi�����ӵ������� (2*i+2);
(03) ����Ϊi�ĸ����������� floor((i-1)/2);

����ѵĺ�����"��ӽڵ�"��"ɾ���ڵ�"

��KСԪ�� ----���ջ
*/
#define PRIORITY_QUEUE_MIN
struct heapEntry {
	int x;
	int y;
	int key;
};

struct HeapCtrl{
	int size;
	int cap;
	void (*rmdown)(struct HeapCtrl *, int , int);
	void (*pushup)(struct HeapCtrl *, int);
	struct heapEntry node[0];
};

#ifdef PRIORITY_QUEUE_MAX
void maxheapPushup(struct HeapCtrl *hp, int start)
{
	int child = start; // ��ǰ�ڵ�(current)��λ��
	int p = (child - 1) / 2;// ��(parent)����λ��
	struct heapEntry cur = hp->node[child];// ��ǰ�ڵ�(current)�Ĵ�С

	while(child > 0) {
		if(hp->node[p].key >= cur.key) {
			break;
		} else {
			hp->node[child] = hp->node[p];
			child = p;
			p = (child - 1) / 2;
		}
	}

	hp->node[child] = cur;
}

void maxheapRmdown(struct HeapCtrl *hp, int start, int end)
{
	int p = start;
	int lchild = 2*p + 1;
	struct heapEntry cur = hp->node[p];

	while(lchild <= end) {
		if(lchild < end && hp->node[lchild].key < hp->node[lchild+1].key)
			lchild++;// ������������ѡ��ϴ��ߣ���m_heap[l+1]

		if(cur.key >= hp->node[lchild].key) {
			break;//��������
		} else {
			hp->node[p] = hp->node[lchild];
			p = lchild;
			lchild = 2*p + 1;
		}
	}

	hp->node[p] = cur;
}
#endif

#ifdef PRIORITY_QUEUE_MIN
void minheapPushup(struct HeapCtrl *hp, int start)
{
	int child = start;
	int p = (child - 1) / 2;
	struct heapEntry cur = hp->node[child];

	while(child > 0) {
		if (hp->node[p].key <= cur.key) {
			break;
		} else {
			hp->node[child] = hp->node[p];
			child = p;
			p = (child - 1) / 2;
		}
	}

	hp->node[child] = cur;
}

void minheapRmdown(struct HeapCtrl *hp, int start, int end)
{
	int p = start;
	int lchild = 2*p + 1;
	struct heapEntry cur = hp->node[p];

	while(lchild <= end) {
		if(lchild < end && hp->node[lchild].key > hp->node[lchild+1].key)
			lchild++;// ������������ѡ���С�ߣ���m_heap[l+1]

		if(cur.key <= hp->node[lchild].key)
			break;//��������
		else {
			hp->node[p] = hp->node[lchild];
			p = lchild;
			lchild = 2*lchild + 1;
		}
	}

	hp->node[p] = cur;
}
#endif

int heapGetIdx(struct HeapCtrl *hp, int key)
{
	for(int i = 0; i < hp->size; i++) {
		if (key == hp->node[i].key) {
			return i;
		}
	}

	return -1;
}

bool heapEmpty(struct HeapCtrl *hp)
{
	return hp->size == 0;
}

bool heapFull(struct HeapCtrl *hp)
{
	return hp->size == hp->cap;
}

int heapSize(struct HeapCtrl *hp)
{
	return hp->size;
}

int heapRm(struct HeapCtrl *hp, int data)
{
	int index;
	if(hp->size == 0)
		return  -1;

	index = heapGetIdx(hp, data);
	if (index== -1) {
		return -1;
	}

	hp->node[index] = hp->node[--hp->size];// �����Ԫ���
	// ��indexλ�ÿ�ʼ�������µ���Ϊ����
	hp->rmdown(hp, index, hp->size -1);
	return 0;
}

struct heapEntry heapPop(struct HeapCtrl *hp)
{
	struct heapEntry top;

	top = hp->node[0];
	heapRm(hp, top.key);
	return top;
}

int heapPush(struct HeapCtrl *hp, struct heapEntry node)
{
	if(heapFull(hp)) {
		return -1;
	}

	hp->node[hp->size] = node;
	hp->pushup(hp, hp->size);
	hp->size++;

	return 0;
}

struct HeapCtrl *heapInit(int cap)
{
	struct HeapCtrl * hp = (struct HeapCtrl *)calloc(1, sizeof(struct HeapCtrl) + sizeof(struct heapEntry) * cap);
	hp->cap = cap;
	hp->rmdown = minheapRmdown;//minheapRmdown
	hp->pushup = minheapPushup;
	return hp;
}

    int dirR[4] = {-1, 0, 1, 0};
    int dirC[4] = {0, 1, 0, -1};


int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize)
{
	int row = heightMapSize;
	int col = *heightMapColSize;

	if (row == 0 || col ==0) return 0;

        //priority_queue<Node> q; // ���ȶ���ά�������߽�
	int hpSzie = fmax(1024, row * col);
	struct HeapCtrl *hp = heapInit(hpSzie);
		// �Ƿ���ʵ����Ƿ���Χǽ���
       // vector<vector<int>> visited(row , vector<int>(col, 0));
	int visited[row][col];
	memset(visited, 0, sizeof(visited));
        // �߽����
        for (int i =0; i< col; i++){
            //q.push({0, i, heightMap[0][i]});
            //q.push({row-1, i, heightMap[row-1][i]});
		struct heapEntry node;
		node.x = 0;
		node.y = i;
		node.key = heightMap[0][i];
		heapPush(hp,node);
		node.x = row - 1;
		node.y = i;
		node.key = heightMap[row-1][i];
		heapPush(hp,node);

            visited[0][i] = visited[row-1][i] = 1;
        }
        for (int i = 1; i< row -1; i++){
            //q.push({i, 0, heightMap[i][0]});
           // q.push({i, col -1, heightMap[i][col-1]});

		struct heapEntry node;
		node.x = i;
		node.y = 0;
		node.key = heightMap[i][0];
		heapPush(hp,node);
		node.x = i;
		node.y = col - 1;
		node.key = heightMap[i][col-1];
		heapPush(hp,node);
              visited[i][0] = visited[i][col-1] = 1;
        }
        int ans = 0;

        while (!heapEmpty(hp)){
            struct heapEntry top = heapPop(hp);

            for (int d = 0; d< 4; d++){
                int r = dirR[d] + top.x;
                int c = dirC[d] + top.y;
                if (r <0 || r >=row || c < 0|| c >= col) continue;
                if (visited[r][c]) continue;
                visited[r][c] = 1;
                if (heightMap[r][c] < top.key){
                    ans += (top.key - heightMap[r][c]);
                }
                //q.push({r, c, max(top.key, heightMap[r][c])});
			struct heapEntry node;
			node.x = r;
			node.y = c;
			node.key = fmax(top.key, heightMap[r][c]);
			heapPush(hp,node);
            }
        }
        return ans;
}

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int** updateMatrix(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes)
{
        int row = matrixSize;
	int col = *matrixColSize;
	int **dist = (int **)calloc(row, sizeof(int *));
	for (int i = 0; i < row; i++) {
		dist[i] = (int *)calloc(col, sizeof(int));
	}

	int visited[row][col];
	memset(visited, 0, sizeof(visited));
	   int queue[10001];
		memset(queue, 0, sizeof(queue));
	   int head = 0;
	   int rear = 0;
        // �����е� 0 ��ӽ���ʼ������
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == 0) {
			queue[rear++] = i * col + j;
                    visited[i][j] = 1;
                }
            }
        }

        // �����������
        while (head != rear) {
             int top = queue[head++];
		  int i = top / col;
		  int j = top % col;
            for (int d = 0; d < 4; ++d) {
                int ni = i + dir[d][0];
                int nj = j + dir[d][1];
                if (ni >= 0 && ni < row && nj >= 0 && nj < col && !visited[ni][nj]) {
                    dist[ni][nj] = dist[i][j] + 1;
				queue[rear++] = ni * col + nj;
                    visited[ni][nj] = 1;
                }
            }
        }

	*returnSize = matrixSize;
	*returnColumnSizes = matrixColSize;
    return dist;
}

/*
Tree �� BFS ��Դ BFS
ͼ �� BFS ��Դ BFS
*/

int** updateMatrix(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes)
{
    int m = matrixSize, n = *matrixColSize;


    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        matrix[i][j] = matrix[i][j] == 0 ? 0 : 10000;
      }
    }

    // �����Ͻǿ�ʼ
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (i - 1 >= 0) {
          matrix[i][j] = fmin(matrix[i][j], matrix[i - 1][j] + 1);
        }
        if (j - 1 >= 0) {
          matrix[i][j] = fmin(matrix[i][j], matrix[i][j - 1] + 1);
        }
      }
    }
    // �����½ǿ�ʼ
    for (int i = m - 1; i >= 0; i--) {
      for (int j = n - 1; j >= 0; j--) {
        if (i + 1 < m) {
          matrix[i][j] = fmin(matrix[i][j], matrix[i + 1][j] + 1);
        }
        if (j + 1 < n) {
          matrix[i][j] = fmin(matrix[i][j], matrix[i][j + 1] + 1);
        }
      }
    }

	*returnColumnSizes = matrixColSize;
	*returnSize = matrixSize;
    return matrix;
}

/*
1162. ��ͼ����
�Ѷ��е�134
������������һ�ݴ�СΪ N x N �ġ���ͼ�������� grid�������ÿ�������򡹣���Ԫ�񣩶��� 0 �� 1 ��Ǻ��ˡ����� 0 ������1 ����½�أ������ҳ�һ������������������������������½������ľ��������ġ�
��������˵�ľ����ǡ������پ��롹�� Manhattan Distance����(x0, y0) �� (x1, y1) ����������֮��ľ����� |x0 - x1| + |y0 - y1| ��
������ǵĵ�ͼ��ֻ��½�ػ��ߺ����뷵�� -1��

ʾ�� 1��

���룺[[1,0,1],[0,0,0],[1,0,1]]
�����2
���ͣ�
�������� (1, 1) ������½������֮��ľ��붼�ﵽ���������Ϊ 2��

*/
/*
[
[1,0,1],
[0,0,0],
[1,0,1]
]
0 --sea
1---land
������ǵĵ�ͼ��ֻ��½�ػ��ߺ����뷵�� -1��
*/
int maxDistance(int** grid, int gridSize, int* gridColSize)
{
	int queue[100 * 1000];
	int rear = 0;
	int head = 0;
	int row = gridSize;
	int col = *gridColSize;

	int cnt = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 1) {
				queue[rear++] = i * col + j;
				cnt++;
			}
		}
	}

	if (cnt == 0 || cnt == row * col)
		return -1;

	int deep = -1;
	int dir[][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
	while(rear != head) {
		deep++;
		int floorSize = rear - head;
		for (int i = 0; i < floorSize; i++) {
			int top = queue[head++];
			int cx = top / col;
			int cy = top % col;

			for (int j = 0; j < 4; j ++) {
				int nx = cx + dir[j][0];
				int ny = cy + dir[j][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (grid[nx][ny] != 0)
					continue;

				grid[nx][ny] = 1;
				queue[rear++] = nx * col + ny;
			}
		}
	}

	return deep;
}

/*
��Ȼ�ⲻ��һ������Դ�����·���⣨SSSP����������ѧϰ�������·�㷨�У���� SSSP ����ķ����� Dijkstra �㷨�� SPFA�㷨���������������֮������·һ��ʹ�� Floyd �㷨���������������Ӧ��ʹ�� Floyd �㷨��Ҫ����������⣬������Ҫ����һ������ʹ�� Floyd �㷨��ʱ�临�Ӷȡ�����֪��������ͼ�������·�����ߣ�LeetCode-Solution���ӣ�https://leetcode-cn.com/problems/as-far-from-land-as-possible/solution/di-tu-fen-xi-by-leetcode-solution/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
int maxDistance(int** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = *gridColSize;
	int d[row][col];
	int visited[row][col];
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                d[i][j] = INT_MAX;
		visited[i][j] = 0;
            }
        }

	int queue[100 * 1000];
	int head = 0;
	int rear = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j]) {
                    d[i][j] = 0;
                    //q.push({i, j});
			queue[rear++] = i * col + j;
                    visited[i][j] = 1;
                }
            }
        }

	int dir[][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
        while (head != rear) {
            int f = queue[head++];
		int cx = f / col;
		int cy = f % col;
			visited[cx][cy] = 0;
            for (int i = 0; i < 4; ++i) {
                int nx = cx + dir[i][0], ny = cy + dir[i][1];
                if (!(nx >= 0 && nx <= row - 1 && ny >= 0 && ny <= col - 1)) continue;
                if (d[nx][ny] > d[cx][cy] + 1) {
                    d[nx][ny] = d[cx][cy] + 1;
                    if (!visited[nx][ny]) {
                        queue[rear++] = nx * col + ny;
                        visited[nx][ny] = 1;
                    }
                }
            }
        }

        int ans = -1;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (!grid[i][j]) ans = fmax(ans, d[i][j]);
            }
        }

        return (ans == INT_MAX) ? -1 : ans;
}


/*
DFS
301
*/
#define MAX_QUEUE_SIZE 10000
#define MAX_WORD_SIZE  50
#define LEFT_P '('
#define RIGHT_P ')'

struct Queue {
    char** parentheses;
    int head;
    int rear;
};
typedef struct Queue Queue_t;

void InitQueue(Queue_t* que)
{
    que->parentheses = (char**)calloc(MAX_QUEUE_SIZE, sizeof(char*));
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        que->parentheses[i] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
    }
    que->head = que->rear = 0;
}

void DeInitQueue(Queue_t* que)
{
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        free(que->parentheses[i]);
    }
    free(que->parentheses);
}

bool IsEmpty(Queue_t* que)
{
    return que->head == que->rear;
}

void EnQueue(Queue_t* que, char* strParentheses)
{
    strcpy(que->parentheses[que->rear], strParentheses);
    que->rear = (que->rear + 1) % MAX_QUEUE_SIZE;
}

void DeQueue(Queue_t* que, char** strParentheses)
{
    if (que->head >= que->rear) {
        return;
    }

    // strcpy(strParentheses, que->parentheses[que->head]);
    *strParentheses =  que->parentheses[que->head];
    que->head = (que->head + 1) % MAX_QUEUE_SIZE;
}

int GetQueueSize(Queue_t* que)
{
    return que->rear - que->head;
}

bool IsStringValid(char* pString, int* delta)
{
    int leftCount = 0;
    int rightCount = 0;
    bool flag = true;
    for (int i = 0; i < strlen(pString); i++) {
        if (pString[i] == LEFT_P) {
            leftCount++;
        } else if (pString[i] == RIGHT_P) {
            rightCount++;
        }
        if (leftCount < rightCount) {
            flag = false;
        }
    }
    *delta = leftCount - rightCount;
    if (flag && *delta == 0) {
        return true;
    } else {
        return false;
    }
}

bool IsInQueue(char* pString, Queue_t* que)
{
    for (int i = que->head; i < que->rear; i++) {
        if (strcmp(pString, que->parentheses[i]) == 0) {
            return true;
        }
    }
    return false;
}

void RemoveChar(char* pString, int index)
{
    int len = strlen(pString);
    if (index < 0 || index >= len) {
        return;
    }

    for (int i = index; i < len - 1; i++) {
        pString[i] = pString[i + 1];
    }
    pString[len - 1] = '\0';
}

void BFS(Queue_t* quePtr, char** rst, int* returnSize)
{
    char* tmpStr = NULL;
    bool flag = false;
    int delta = 0;

    while (!IsEmpty(quePtr)) {
        int curSize = GetQueueSize(quePtr);
        for (int i = 0; i < curSize; i++) {
            // termination is result ok
            DeQueue(quePtr, &tmpStr);
            // process
            if (IsStringValid(tmpStr, &delta)) {
                rst[*returnSize] = (char*)calloc(strlen(tmpStr) + 1, sizeof(char));
                strcpy(rst[*returnSize], tmpStr);
                *returnSize = *returnSize + 1;
                flag = true;
            }

            // drill down and enqueue
            if (!flag) { // if find result this round
                for (int k = 0; k < strlen(tmpStr); k++) {
                    if (tmpStr[k] != LEFT_P && tmpStr[k] != RIGHT_P) {
                        continue;
                    }

                    if (tmpStr[k] == LEFT_P && delta < 0) {
                        continue;
                    }

                    if (tmpStr[k] == RIGHT_P && delta > 0) {
                        continue;
                    }

                    char* tmpStr2 = (char*)calloc(strlen(tmpStr) + 1, sizeof(char));
                    strcpy(tmpStr2, tmpStr);
                    RemoveChar(tmpStr2, k);
                    if (!IsInQueue(tmpStr2, quePtr)) {
                        EnQueue(quePtr, tmpStr2);
                    } else {
                        free(tmpStr2);
                    }
                }
            }
        }
        if (flag) {
            return;
        }
    }
    return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeInvalidParentheses(char* s, int* returnSize)
{
    Queue_t que;
    InitQueue(&que);
    EnQueue(&que, s);
    char** rst = (char**)calloc(MAX_QUEUE_SIZE, sizeof(char*));
    *returnSize = 0;

    BFS(&que, rst, returnSize);
    return rst;
}


/*
127. ���ʽ���
�����������ʣ�beginWord �� endWord����һ���ֵ䣬�ҵ��� beginWord �� endWord �����ת�����еĳ��ȡ�ת������ѭ���¹���

ÿ��ת��ֻ�ܸı�һ����ĸ��
ת�������е��м䵥�ʱ������ֵ��еĵ��ʡ�
˵��:

���������������ת�����У����� 0��
���е��ʾ�����ͬ�ĳ��ȡ�
���е���ֻ��Сд��ĸ��ɡ�
�ֵ��в������ظ��ĵ��ʡ�
����Լ��� beginWord �� endWord �Ƿǿյģ��Ҷ��߲���ͬ��
ʾ�� 1:

����:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

���: 5

����: һ�����ת�������� "hit" -> "hot" -> "dot" -> "dog" -> "cog",
     �������ĳ��� 5��
*/

#define MAX_QUEUE_SIZE 10000

int isValidString(char *popString, char *dicString);

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
    if ((beginWord == NULL) || (strlen(beginWord) <= 0) || (endWord == NULL) || (strlen(endWord) <= 0) || (wordList == NULL) || (wordListSize <= 0)) {
        return 0;
    }

    char *queue[MAX_QUEUE_SIZE];
    int front = 0;
    int rear = 0;
    int *pVisit = (int *)malloc(sizeof(int) * wordListSize);
    memset(pVisit, 0, sizeof(int) * wordListSize);

    queue[rear] = beginWord;
    rear++;
    int step = 0;

    while (front != rear) {
        step++;
        int gap = rear - front;
        if (gap < 0) {
            gap = front - rear + 1;
        }

        for (int k = 0; k < gap; k++) {
            char *pop = queue[front];
            front = (front + 1) % MAX_QUEUE_SIZE;

            if (strcmp(pop, endWord) == 0) {
                free(pVisit);
                return step;
            }

            for (int i = 0; i < wordListSize; i++) {
                if ((pVisit[i] == 0) && (isValidString(pop, wordList[i]))) {
                    queue[rear] = wordList[i];
                    rear = (rear + 1) % MAX_QUEUE_SIZE;
                    pVisit[i] = 1;
                }
            }
        }
    }
    free(pVisit);
    return 0;
}

int isValidString(char *popString, char *dicString)
{
    int diffNum = 0;
    int len = strlen(popString);
    for (int i = 0; i < len; i++) {
        if (popString[i] != dicString[i]) {
            diffNum++;
        }

        if (diffNum > 1) {
            return 0;;
        }
    }
    return 1;
}

#define MAX_QUEUE_LEN 100000

int isSequ(char* a, char* b){
    int len = strlen(a);
    int count = 0;
    for(int i = 0; i < len; i++){
        if(a[i] != b[i])
            count++;
    }
    if(count == 1)
        return true;
    else
        return false;

}

int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize)
{
    char* queueList[MAX_QUEUE_LEN] = {0};       //����һ���ܴ�����飬������������
    int head = 0;                               //��Ҫ��βָ����
    int tail = 0;

    for(int i = 0; i < wordListSize; i++){
        if(strcmp(endWord, wordList[i]) == 0){  //�ַ������п���ƥ���
            break;
        }
        if(i == wordListSize-1) return 0;       //�ַ���������û��ƥ��ģ�return 0
    }
    int* mark = (int*)malloc(wordListSize*sizeof(int)); //��Ҫ��ʶ����ַ����Ƿ��Ѿ��������ˣ�������ѭ��
    memset(mark, 0, wordListSize * sizeof(int));

    queueList[tail++] = beginWord;              //��ʼ����ʼ�ַ�������У�βָ��+1
    int step = 1;
    while(head != tail){                        //���в�Ϊ�գ�����δ����
        int scop = tail-head;                   //�����������ǰ��һ���ж��ٸ�
        for(int i = 0; i < scop; i++){
            char *temp = queueList[head++];
            if(strcmp(temp, endWord) == 0){     //�൱�ڳ����У��ж��Ƿ���ϡ���ָ��++
                free(mark);
                return step;
            }
            for(int j = 0; j < wordListSize; j++){  //�൱��������һ�㣬���Ƿ���ڿ��Ա仯��
                if(mark[j] == 0 && isSequ(temp, wordList[j])){
                    mark[j] = 1;
                    queueList[tail++] = wordList[j];
                }
            }
        }
        step++;
    }
    free(mark);
    return 0;
}

