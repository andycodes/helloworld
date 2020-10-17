/*         BFS

BFS ʹ��queue ����heap

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
int dirR[4] = {-1, 0, 1, 0};
int dirC[4] = {0, 1, 0, -1};
int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize)
{
	int row = heightMapSize;
	int col = *heightMapColSize;

	if (row == 0 || col ==0) return 0;

	int hpSzie = fmax(1024, row * col);
	struct HeapCtrl *hp = heapInit(hpSzie);
	// �Ƿ���ʵ����Ƿ���Χǽ���
	int visited[row][col];
	memset(visited, 0, sizeof(visited));

	// �߽����
        for (int i =0; i< col; i++){
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

            for (int d = 0; d< 4; d++) {
		int nx = dirR[d] + top.x;
		int ny = dirC[d] + top.y;
		if (nx <0 || nx >=row || ny < 0|| ny >= col)
			continue;
		if (visited[nx][ny])
			continue;
		visited[nx][ny] = 1;
		if (heightMap[nx][ny] < top.key){
			ans += (top.key - heightMap[nx][ny]);
		}
		struct heapEntry node;
		node.x = nx;
		node.y = ny;
		node.key = fmax(top.key, heightMap[nx][ny]);
		heapPush(hp,node);
            }
        }
        return ans;
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
499. �Թ� III
�ɿյغ�ǽ��ɵ��Թ�����һ������������ϣ�u���£�d����l���ң�r���ĸ������������������ǽ��ǰ����ֹͣ����������ͣ��ʱ������ѡ����һ�������Թ��л���һ�����������˶�������ʱ���ͻ�������

���������ʼλ�ã�Ŀ�ĵغ��Թ����ҳ���������̾�����������·���� ����Ķ����������ʼλ�ã�����������Ŀ�ĵأ������������Ŀյظ�����ͨ��'u', 'd', 'l' �� 'r'�������ƶ����� ���ڿ����ж������·���� ������ֵ�����С��·����������޷����붴�����"impossible"��

�Թ���һ��0��1�Ķ�ά�����ʾ�� 1��ʾǽ�ڣ�0��ʾ�յء�����Լٶ��Թ��ı�Ե����ǽ�ڡ���ʼλ�ú�Ŀ�ĵص�����ͨ���кź��кŸ�����



ʾ��1:

���� 1: �Թ������¶�ά�����ʾ

0 0 0 0 0
1 1 0 0 1
0 0 0 0 0
0 1 0 0 1
0 1 0 0 0
*/
#define MAX_ROW 30
#define MAX_COL 30

typedef struct MazeSearch_t {
    int visited;
    int step;
    char* path;
}MazeSearch;

MazeSearch g_MazeSearch[MAX_ROW][MAX_COL];

void directMove(int** maze, int row, int col, int* hole,
	int curIdx, int *queue, int dir, int *head, int *rear)
{
	int curStep;
	char *curPath;
	int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	char str[4] = {'d', 'u', 'r', 'l'};

	int curRow = curIdx / col;
	int curCol = curIdx % col;
	curStep = g_MazeSearch[curRow][curCol].step;
	curPath = g_MazeSearch[curRow][curCol].path;

	int nextRow = curRow;
	int nextCol = curCol;
	while(((nextRow + dirs[dir][0]) >= 0) && ((nextRow + dirs[dir][0]) < row)
		&& ((nextCol + dirs[dir][1]) >= 0) && ((nextCol + dirs[dir][1]) < col)) {

		if (maze[nextRow + dirs[dir][0]][nextCol + dirs[dir][1]] == 1) // 1��ʾǽ��
			break;

		nextRow += dirs[dir][0];
		nextCol += dirs[dir][1];
		curStep++;

		if ((nextRow == hole[0]) && (nextCol == hole[1])) // ��
			break;

		if (g_MazeSearch[nextRow][nextCol].visited == 1)
			return;
	}

	if (curStep == g_MazeSearch[curRow][curCol].step)
		return;
	if ((g_MazeSearch[hole[0]][hole[1]].step > 0) && (curStep > g_MazeSearch[hole[0]][hole[1]].step))
		return;
	if ((g_MazeSearch[nextRow][nextCol].step > 0) && (curStep > g_MazeSearch[nextRow][nextCol].step))
		return;

	char* newPath = (char*)malloc(sizeof(char) * (strlen(curPath) + 2));
	snprintf(newPath, strlen(curPath) + 2, "%s%c", curPath, str[dir]);

	if ((g_MazeSearch[nextRow][nextCol].step == curStep) &&
		(strcmp(newPath, g_MazeSearch[nextRow][nextCol].path) >= 0)) {
		free(newPath);
		return;
	}

	g_MazeSearch[nextRow][nextCol].step = curStep;
	if (g_MazeSearch[nextRow][nextCol].path != NULL)
		free(g_MazeSearch[nextRow][nextCol].path);
	g_MazeSearch[nextRow][nextCol].path = newPath;

	if ((nextRow == hole[0]) && (nextCol == hole[1]))
		return;

	queue[*rear] = nextRow * col + nextCol;
	(*rear)++;
}

char* findShortestWay(int** maze, int mazeSize, int* colSize, int* ball, int ballSize, int* hole, int holeSize) {
	int row = mazeSize;
	int col = colSize[0];

	memset(g_MazeSearch, 0, sizeof(g_MazeSearch));
	int  queue[row * col];
	int head = 0;
	int rear = 0;

	queue[rear++] = ball[0] * col + ball[1];
	g_MazeSearch[ball[0]][ball[1]].visited = 1;
	g_MazeSearch[ball[0]][ball[1]].path = (char*)malloc(sizeof(char));
	g_MazeSearch[ball[0]][ball[1]].path = "\0";

	while(head != rear) {
		int pop = queue[head++];
		for (int i = 0; i < 4; i++) {
			directMove(maze, row, col, hole, pop, queue, i, &head, &rear);
		}
	}

	if (g_MazeSearch[hole[0]][hole[1]].path == NULL)
		return "impossible";
	return g_MazeSearch[hole[0]][hole[1]].path;
}

/*
1036. ������Թ�
��һ�� 10^6 x 10^6 �������У�ÿ������������Ϊ (x, y)������ 0 <= x, y < 10^6��

���Ǵ�Դ���� source ��ʼ��������ͼ����Ŀ�귽�� target��ÿ���ƶ������Ƕ������ߵ����������ĸ����������ڵķ���ֻҪ�÷����ڸ����ķ����б� blocked �ϡ�

ֻ���ڿ���ͨ��һϵ�е��ƶ�����Ŀ�귽��ʱ�ŷ��� true�����򣬷��� false��



ʾ�� 1��

���룺blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
�����false
���ͣ�
��Դ�����޷�����Ŀ�귽����Ϊ�����޷����������ƶ���
ʾ�� 2��

���룺blocked = [], source = [0,0], target = [999999,999999]
�����true
���ͣ�
��Ϊû�з��񱻷���������һ�����Ե���Ŀ�귽��
*/
struct node {
    int x;
    int y;
};

int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// -1��ʾ����ס�ˣ�2��ʾ�ﵽ��Ŀ�ĵأ�1��ʾ������len�ķ���
int bfs(int* source, int* target, int** blocked , int blockedSize) {
    struct node nn[100000] = {0};
    int cnt = 1;
    nn[0].x = source[0];
    nn[0].y = source[1];
    int ll = 2 * (blockedSize + 2);
    bool visited[ll][ll];
    memset(visited, 0, ll*ll);
    int cur = 0;
    while (cur < cnt) {
        struct node n = nn[cur++];
        int x = n.x;
        int y = n.y;
        int disx = x - source[0] > 0 ? x - source[0] : source[0] - x;
        int disy = y - source[1] > 0 ? y - source[1] : source[1] - y;
        if (disx > blockedSize || disy > blockedSize) return 1;
        if (x == target[0] && y == target[1]) return 2;
        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            if (nx < 0 || nx >= 1000000) continue;
            if (ny < 0 || ny >= 1000000) continue;
            if (visited[nx-source[0]+blockedSize+1][ny-source[1]+blockedSize+1] == 1) continue;
            bool isBlock = false;
            for (int k = 0; k < blockedSize; k++) {
                if (nx == blocked[k][0] && ny == blocked[k][1]) {
                    isBlock = true;
                    break;
                }
            }
            if (isBlock) continue;
            nn[cnt].x = nx;
            nn[cnt].y = ny;
            cnt++;
            visited[nx-source[0]+blockedSize+1][ny-source[1]+blockedSize+1] = 1;
        }
    }
    return -1;
}

bool isEscapePossible(int** blocked, int blockedSize, int* blockedColSize, int* source, int sourceSize, int* target, int targetSize){
    // block�ĳ���Ϊlen����ס���εıߣ��ϰ��������Է�ס�߳�Ϊlen�ľ���
    // ��source��target����ͨ��bfsȥ�ߣ���������˱˴���ɹ��������������������ʼ���������len��Ҳ��ɹ�
    int r = bfs(source, target, blocked, blockedSize);
    if (r == -1) return false;
    if (r == 2) return true;
    r = bfs(target, source, blocked, blockedSize);
    if (r == -1) return false;
    return true;
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
542. 01 ����
����һ���� 0 �� 1 ��ɵľ����ҳ�ÿ��Ԫ�ص������ 0 �ľ��롣

��������Ԫ�ؼ�ľ���Ϊ 1 ��

ʾ�� 1:
����:

0 0 0
0 1 0
0 0 0
*/

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int** updateMatrix(int** matrix, int matrixSize,
	int* matrixColSize, int* returnSize, int** returnColumnSizes)
{
	int row = matrixSize;
	int col = *matrixColSize;
	int **res = (int **)calloc(row, sizeof(int *));
	for (int i = 0; i < row; i++) {
		res[i] = (int *)calloc(col, sizeof(int));
	}

	int visited[row][col];
	memset(visited, 0, sizeof(visited));
	int queue[10001];
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

	while (head != rear) {
		int top = queue[head++];
		int i = top / col;
		int j = top % col;
		for (int d = 0; d < 4; ++d) {
			int nx = i + dir[d][0];
			int ny = j + dir[d][1];
			if (nx >= 0 && nx < row && ny >= 0 && ny < col && !visited[nx][ny]) {
				res[nx][ny] = res[i][j] + 1;
				queue[rear++] = nx * col + ny;
				visited[nx][ny] = 1;
			}
		}
	}

	*returnSize = matrixSize;
	*returnColumnSizes = matrixColSize;
	return res;
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
126. ���ʽ��� II
�����������ʣ�beginWord �� endWord����һ���ֵ� wordList���ҳ����д� beginWord �� endWord �����ת�����С�ת������ѭ���¹���

ÿ��ת��ֻ�ܸı�һ����ĸ��
ת����õ��ĵ��ʱ������ֵ��еĵ��ʡ�
˵��:

���������������ת�����У�����һ�����б�
���е��ʾ�����ͬ�ĳ��ȡ�
���е���ֻ��Сд��ĸ��ɡ�
�ֵ��в������ظ��ĵ��ʡ�
����Լ��� beginWord �� endWord �Ƿǿյģ��Ҷ��߲���ͬ��
ʾ�� 1:

����:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

���:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
ʾ�� 2:

����:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

���: []

����: endWord "cog" �����ֵ��У����Բ����ڷ���Ҫ���ת�����С�
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

//ѧϰһƪ���������ܸߵ�C���룬����ѧϰ����д��һ��

//�μ���https://leetcode-cn.com/problems/word-ladder-ii/solution/lai-ge-cde-ti-jie-xie-de-hen-shang-xin-by-hong-65/

//˼·��
//1�������µ��ֵ�,�� beginword �����ֵ� Ϊ�׵���
//2,��ȡ endWord ���ֵ��е��±�,�Ҳ�����ֱ�ӷ��ؿ�
//3,�����ֵ���ÿ�����ʵ����ڹ�ϵ
//4,BFS���������������ȡ���ת�����в��������ҹ���������ϵ��
//5,DFS��������������ݹ����������ϵ�����ҵ����ת������

#define     MIN(a, b)       ((a) < (b) ? (a) : (b))
#define     MAX(a, b)       ((a) > (b) ? (a) : (b))
#define     INVALID_INDEX   0xffffffff
#define     PRT_SW          0

//��¼ÿ�����ʵ�ת��������Ϣ
typedef struct {
    unsigned int    adjNum;         //�ֵ���ת�����ʵĸ���
    unsigned int*   adjIndex;       //ת���������ֵ��е�����
} WordAdj;

//��¼ÿ�����ʵ�������Ϣ
typedef struct {
    unsigned int    isOk;           //��¼��ǰ�����Ƿ�������
    unsigned int    minLen;         //��¼��ǰ���ʵĲ���
    unsigned int    nextNum;        //��ǰ���ʵ���һ��ת�����ʵ�����
    unsigned int*   nextIndex;      //�洢��ǰ���ʵ���һ��ת������
} WordSearch;

//��¼�����Ϣ
typedef struct outPut {
    char**              str;        //�洢ÿ�����ת������
    struct outPut*      next;       //ָ����һ�����
} OutPutList;

WordAdj*        g_wordAdjInfo       = NULL;         //���ڼ�¼�ֵ���ÿ�����ʵ�ת������
WordSearch*     g_wordSearchInfo    = NULL;         //����BFS������¼�����Ϣ
OutPutList*     g_outPutStr         = NULL;         //���ڼ�¼���ת�����н��
unsigned int    g_outPutStrNum      = 0;            //���ת��������

#if (PRT_SW == 1)
#define     DebugPrt    printf
#else
#define     DebugPrt
#endif

//����һ���ڴ�����
int MallocMem(char*** newWordList, unsigned int totalWordNum){
    unsigned int    i   = 0;

    *newWordList = (char**)malloc(sizeof(char*) * totalWordNum);
    if(NULL == (*newWordList)) return -1;

    g_wordAdjInfo = (WordAdj*)malloc(sizeof(WordAdj) * totalWordNum);
    if(NULL == g_wordAdjInfo) return -1;

    g_wordSearchInfo = (WordSearch*)malloc(sizeof(WordSearch) * totalWordNum);
    if(NULL == g_wordSearchInfo) return -1;

    g_outPutStr = (OutPutList*)malloc(sizeof(OutPutList));
    if(NULL == g_outPutStr) return -1;
    g_outPutStr->next = NULL;

    for(i = 0; i < totalWordNum; i++)
    {
        g_wordAdjInfo[i].adjNum = 0;
        g_wordAdjInfo[i].adjIndex = (unsigned int*)malloc(sizeof(unsigned int) * totalWordNum);
        if(NULL == g_wordAdjInfo[i].adjIndex) return -1;

        g_wordSearchInfo[i].isOk = 0;
        g_wordSearchInfo[i].minLen = INVALID_INDEX;
        g_wordSearchInfo[i].nextNum = 0;
        g_wordSearchInfo[i].nextIndex = (unsigned int*)malloc(sizeof(unsigned int) * totalWordNum);
        if(NULL == g_wordSearchInfo[i].nextIndex) return -1;
    }
    return 0;
}

//���������ڴ��ͷ�
void FreeMem(char** newWordList, unsigned int totalWordNum){
    unsigned int    i       = 0;
    OutPutList*     pTmp    = NULL;
    OutPutList*     pRel    = NULL;

    for(i = 0; i < totalWordNum; i++)
    {
        free(g_wordAdjInfo[i].adjIndex);
        g_wordAdjInfo->adjIndex = NULL;

        free(g_wordSearchInfo[i].nextIndex);
        g_wordSearchInfo->nextIndex = NULL;
    }

    free(newWordList);
    newWordList = NULL;

    free(g_wordAdjInfo);
    g_wordAdjInfo = NULL;

    free(g_wordSearchInfo);
    g_wordSearchInfo = NULL;

    pTmp = g_outPutStr;
    while((NULL != pTmp) && (i < g_outPutStrNum + 1))
    {
        pRel = pTmp;
        pTmp = pTmp->next;
        free(pRel);
        pRel = NULL;
        i += 1;
    }

    free(g_outPutStr);
    g_outPutStr = NULL;
    return;
}

//���������ع��ֵ��б��� beginWord ���ʼ����ֵ�Ϊ�׵���
int RebuildNewWordList(char * beginWord, char ** wordList, int wordListSize, char** newWordList){
    int     i           = 0;
    int     iNum        = 0;

    newWordList[0] = beginWord;
    iNum += 1;
    for(i = 0; i < wordListSize; i++)
    {
        if(0 != strcmp(wordList[i], beginWord))
        {
            newWordList[iNum++] = wordList[i];
        }
    }

    return iNum;
}

//�����ģ���ȡ endWord ���ֵ��е��±꣬endWord �����ֵ����򷵻ؿ��б�
int CheckEndWord(char* endWord, char** wordList, int wordListSize, unsigned int* endWordIndex){
    unsigned int    i   = 0;

    for(i = 0; i < wordListSize; i++)
    {
        if(0 == strcmp(endWord, wordList[i]))
        {
            *endWordIndex = i;
            return 0;
        }
    }
    return -1;
}

//�����壺�ж����������Ƿ����ת��
int CheckIsAdjWord(char* word1, char* word2){
    unsigned int    i           = 0;
    unsigned int    diffNum     = 0;
    unsigned int    len         = strlen(word1);
    while(i < len)
    {
        if(word1[i] != word2[i])
        {
            diffNum += 1;
        }
        i += 1;
        if(diffNum > 1) return -1;
    }
    if(diffNum == 1) return 0;
    return -1;
}

//�������������ֵ������е��ʵ�ת����ϵ g_wordAdjInfo
int CreateWordAdj(char** newWordList, unsigned int totalWordNum){
    unsigned int    i   = 0;
    unsigned int    j   = 0;
    for(i = 0; i < totalWordNum - 1; i++)
    {
        for(j = i + 1; j < totalWordNum; j++)
        {
            if(0 == CheckIsAdjWord(newWordList[i], newWordList[j]))
            {
                g_wordAdjInfo[i].adjIndex[g_wordAdjInfo[i].adjNum++] = j;

                if(0 == i) continue;

                g_wordAdjInfo[j].adjIndex[g_wordAdjInfo[j].adjNum++] = i;
            }
        }
    }
    return 0;
}

//�����ߣ�BFS�����������
//1,ʹ�ö����Ƚ��ȳ�ʵ��BFS��������������ʺϴ�ΧѰ��
//2,����ǰ��Ԫ������ѹ�����
//3,���ö����Ƚ��ȳ�������ȡ����ǰ��ڵ㣬����ǰ�ڵ�������²�ڵ㣬����ѹ�����
//4,ֱ������Ϊ�գ����������нڵ㣬���Բ������Ĳ�α���
//5,������Բ�����ȫ�������������� endWord ���ڵĲ��ɽ���
int BfsSearch(char** newWordList, unsigned int totalWordNum, unsigned int endWordIndex, unsigned int* minLen){
    unsigned int        i           = 0;
    unsigned int        j           = 0;
    unsigned int        adjIndex    = 0;
    unsigned int        currIndex   = 0;
    unsigned int        findFlag    = 0;
    unsigned int        iHead       = 0;
    unsigned int        iTail       = 0;
    unsigned int        iLevelNum   = 0;

    unsigned int*       searchList      = NULL;
    WordAdj*            wordAdjInfo     = g_wordAdjInfo;
    WordSearch*         wordSearchInfo  = g_wordSearchInfo;

    searchList = (unsigned int*)malloc(sizeof(unsigned int) * totalWordNum);
    if(NULL == searchList) return -1;

    //1,���ֵ���Ԫ�� starWord �������
    searchList[iTail++] = 0;
    iLevelNum = 1;

    wordSearchInfo[0].isOk = 1;
    wordSearchInfo[0].minLen = 1;

    while(iHead < iTail)
    {
        iLevelNum = iTail - iHead;
        //2,������ǰ������Ԫ��
        for(i = 0; i < iLevelNum; i++)
        {
            //3,����ǰ������Ԫ�ص��ӽڵ�ѹ�����
            currIndex = searchList[iHead++];
            for(j = 0; j < wordAdjInfo[currIndex].adjNum; j++)
            {
                adjIndex = wordAdjInfo[currIndex].adjIndex[j];
                wordSearchInfo[currIndex].nextIndex[wordSearchInfo[currIndex].nextNum++] = adjIndex;

                if(0 == wordSearchInfo[adjIndex].isOk)
                {
                    wordSearchInfo[adjIndex].isOk = 1;
                    wordSearchInfo[adjIndex].minLen = wordSearchInfo[currIndex].minLen + 1;
                    searchList[iTail++] = adjIndex;
                }
                if(adjIndex == endWordIndex)
                {
                    findFlag = 1;
                }
            }
        }

        if(1 == findFlag)
        {
            //4,������ endWord �㣬���ɽ�������
            free(searchList);
            *minLen = wordSearchInfo[endWordIndex].minLen;
            return 0;
        }
    }

    free(searchList);
    return -1;
}

//�����ˣ���һ�����ת�����н������������ g_outPutStr ��
int PushRetToOutList(char** newWordList, unsigned int* oneList, unsigned int oneListNum){
    unsigned int    i           = 0;
    char**          OutStr      = NULL;
    char*           charstr     = NULL;
    OutPutList*     node        = NULL;

    OutStr = (char**)malloc(sizeof(char*) * oneListNum);
    if(NULL == OutStr) return -1;

    node = (OutPutList*)malloc(sizeof(OutPutList));
    if(NULL == node) return -1;

    for(i = 0; i < oneListNum; i++)
    {
        charstr = (char*)malloc(sizeof(char) * (strlen(newWordList[oneList[i]]) + 1));
        if(NULL == charstr) return -1;
        strcpy(charstr, newWordList[oneList[i]]);
        OutStr[i] = charstr;
    }

    node->str = OutStr;
    node->next = g_outPutStr->next;
    g_outPutStr->next = node;
    g_outPutStrNum += 1;
    return 0;
}

//�����ţ�DFS ������ȱ����㷨
void DfsSearch(char** newWordList, unsigned int endWordIndex, unsigned int* oneList, unsigned int oneListNum, unsigned int minLen){
    unsigned int    i           = 0;
    unsigned int    lastIndex   = 0;
    unsigned int    nextIndex   = 0;
    WordSearch* wordSearchInfo  = g_wordSearchInfo;

    //1,��������һ����ǰ������δ�����С��μ��ɽ���
    if(oneListNum > minLen) return;

    //2,�������������ҵ� endWord �õ�һ����
    lastIndex = oneList[oneListNum - 1];
    if(lastIndex == endWordIndex)
    {
        PushRetToOutList(newWordList, oneList, oneListNum);
        return;
    }

    //3,�ڵ�ǰ�ڵ����Ч�ӽڵ��еݹ鴦��
    for(i = 0; i < wordSearchInfo[lastIndex].nextNum; i++)
    {
        nextIndex = wordSearchInfo[lastIndex].nextIndex[i];
        if((wordSearchInfo[nextIndex].minLen == oneListNum + 1) && (oneListNum < minLen))
        {
            oneList[oneListNum] = nextIndex;
            DfsSearch(newWordList, endWordIndex, oneList, oneListNum + 1, minLen);
        }
    }
    return;
}

//����ʮ��ʹ�� DFS ������ȱ���Ѱ�����ת������
int CalcResultByDfs(char** newWordList, unsigned int endWordIndex, unsigned int minLen){
    unsigned int*   oneList     = NULL;
    unsigned int    oneListNum  = 0;

    oneList = (unsigned int*)malloc(sizeof(unsigned int) * minLen);
    if(NULL == oneList) return -1;

    oneListNum = 1;
    oneList[0] = 0;
    DfsSearch(newWordList, endWordIndex, oneList, oneListNum, minLen);

    free(oneList);
    oneList = NULL;
    return 0;
}

//����ʮһ���������
char*** OutPutHandle(unsigned int minLen, int* returnSize, int** returnColumnSizes){
    unsigned int    i       = 0;
    unsigned int    j       = 0;
    char*** outPutAll       = NULL;
    OutPutList* pTmp        = NULL;

    outPutAll = (char ***)malloc(sizeof(char**) * g_outPutStrNum);
    if(NULL == outPutAll) return NULL;

    *returnSize = g_outPutStrNum;
    *returnColumnSizes = (int*)malloc(sizeof(int) * g_outPutStrNum);
    if(NULL == *returnColumnSizes) return NULL;

    pTmp = g_outPutStr->next;

    for(i = 0; i < g_outPutStrNum; i++)
    {
        (*returnColumnSizes)[i] = minLen;

        if(NULL != pTmp)
        {
            outPutAll[i] = pTmp->str;
            pTmp = pTmp->next;
        }
    }

/*
    for(i = 0; i < g_outPutStrNum; i++)
    {
        DebugPrt("[%d]:", i);
        for(j = 0; j < minLen; j++)
        {
            DebugPrt(" %s", outPutAll[i][j]);
        }
        DebugPrt("\n");
    }
*/
    return outPutAll;
}

//������
char *** findLadders(char * beginWord, char * endWord, char ** wordList, int wordListSize, int* returnSize, int** returnColumnSizes){
    int         mallocColumnSizes       = 0;
    int         totalWordNum            = wordListSize + 1;
    int         endWordIndex            = 0;
    char**      newWordList             = NULL;                 //���ڼ�¼���¼�¼�ֵ�
    char***     outPutAll               = NULL;

    *returnSize = 0;
    g_outPutStrNum = 0;

    //1,��ʼ��
    if(0 != MallocMem(&newWordList, (wordListSize + 1)))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //2�������µ��ֵ�,�� beginword �����ֵ� Ϊ�׵���
    totalWordNum = RebuildNewWordList(beginWord, wordList, wordListSize, newWordList);

    //3,��ȡ endWord ���ֵ��е��±�
    if(0 != CheckEndWord(endWord, newWordList, totalWordNum, &endWordIndex))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //4,�����ֵ��е��ʵ����ڹ�ϵ
    if(0 != CreateWordAdj(newWordList, totalWordNum))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //5,BFS���������������ȡ���ת�����в��� mallocColumnSizes
    if(0 != BfsSearch(newWordList, totalWordNum, endWordIndex, &mallocColumnSizes))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //6,DFS�����������
    if(0 != CalcResultByDfs(newWordList, endWordIndex, mallocColumnSizes))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //7,�������
    outPutAll = OutPutHandle(mallocColumnSizes, returnSize, returnColumnSizes);

    //8,�ͷſռ�
    FreeMem(newWordList, (wordListSize + 1));
    return outPutAll;
}

/*
675. Ϊ�߶����������
�㱻������һ��Ҫ�ٰ�߶�����������ֿ���. ������һ���Ǹ��Ķ�ά�����ʾ�� ����������У�

0 ��ʾ�ϰ����޷�������.
1 ��ʾ�������ߵĵ���.
�� 1 ����� ��ʾһ�������߹������ĸ߶�.
ÿһ�����㶼�������ϡ��¡������ĸ�����֮һ�ƶ�һ����λ�������վ�ĵط���һ��������ô����Ծ����Ƿ�Ҫ��������

�㱻Ҫ�������ĸ߶ȴӵ���߿������е�����ÿ����һ���������ĸ߶ȱ�Ϊ 1 ��

�㽫�ӣ�0��0���㿪ʼ��������Ӧ�÷����㿳����������Ҫ�ߵ���С������ ������޷��������е��������� -1 ��

���Ա�֤���ǣ�û���������ĸ߶�����ͬ�ģ�������������Ҫ����һ������



ʾ�� 1:

����:
[
 [1,2,3],
 [0,0,4],
 [7,6,5]
]
���: 6
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct strPara_ {
    int i;
    int j;
    int value;
}strPara;
#define Q 1000
typedef struct queuePara_ {
    int front;
    int rear;
    strPara que[Q];
}queuePara;
queuePara queue;
void init(queuePara *q)
{
    q->front = 0;
    q->rear = 0;
    memset(q, 0, sizeof(q));
}

int emQueue(queuePara *q, int i, int j)
{
    if ((q->rear + 1 + Q) % Q == q->front) {
        return 0;
    }
    q->que[q->rear].j = j;
    q->que[q->rear].i = i;
    q->rear = (q->rear + 1) % Q;
    return 1;
}
int isEmpty(queuePara *q)
{
    if (q->rear == q->front) {
        return 1;
    }
    return 0;
}

int getSize(queuePara *q)
{
    return (q->rear + Q - q->front) % Q;
}
#define M 100
#define N 100
strPara arr[M*N];
int visit[M][N];
#if 0
int forest[M][N] = {
    {2,3,4},
    {0,0,5},
    {8,7,6}
};
#endif
int compare(const void * a, const void *b)
{
    strPara *aa = (strPara *)a;
    strPara *bb = (strPara *)b;
    return (aa->value - bb->value);
}
int sort (int ** forest,int forestSize, int* forestColSize)
{
    int i, j;
    int k = 0;
    for (i = 0; i < forestSize; i++) {
        for (j = 0 ; j < *forestColSize; j++) {
            if (forest[i][j] == 0) {
                continue;
            }
            arr[k].i = i;
            arr[k].j = j;
            arr[k].value = forest[i][j];
            k++;
        }
    }
    qsort(arr, k, sizeof(strPara), compare);
    return k;
}
int bfs(strPara *start, strPara *target, int **forest,int forestSize, int forestColSize)
{
    int i, j, k;
    int di[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    int cnt = 0;
    queuePara *q = &queue;
    init(q);
    emQueue(q, start->i, start->j);
    memset(visit, 0, sizeof(visit));
    visit[start->i][start->j] = 1;
    while(!isEmpty(q)) {
        k = getSize(q);
        for (i = 0; i < k; i++) {
            int x = q->que[q->front].i;
            int y = q->que[q->front].j;
            q->front = (q->front + 1) % Q;
            if (x == target->i && y == target->j) {
                return cnt;
            }
            for (j = 0; j < 4; j++) {
                int nx = x + di[j][0];
                int ny = y + di[j][1];
                if (nx >=0 && nx < forestSize && ny >=0 && ny < forestColSize &&
                    visit[nx][ny] == 0 && forest[nx][ny] != 0) {
                    emQueue(q, nx, ny);
                    visit[nx][ny] = 1;
                }
            }
        }
        cnt++;
    }
    return -1;
}
int cutOffTree(int **forest,int forestSize, int* forestColSize){
    int i, j, k;
    int cnt = 0;
    int sum = 0;
    if (forest == NULL || forestSize == 0 || *forestColSize == 0 || forest[0][0] == 0) {
        return -1;
    }
    k = sort(forest, forestSize, forestColSize);
    strPara start;
    start.i = 0;
    start.j = 0;
    start.value = forest[0][0];

    for (i = 0; i < k; i++) {
        if (start.i == arr[i].i && start.j == arr[i].j) {
            continue;
        }
        cnt = bfs(&start, &arr[i],forest, forestSize, *forestColSize);
        if (cnt == -1) {
            return -1;
        }
        start.i = arr[i].i;
        start.j = arr[i].j;
        start.value = arr[i].value;
        sum += cnt;
    }
   // printf("%d\n", sum);
    return sum;
}
/*
�Ƚ�ˮ����ɡ��ȱ���һ��ͼ���������ĵ�����ĸ߶ȼ�¼������Ȼ�������ĸ߶�����һ�¡���ô�𰸾��Ǵ����(0,0)����һ��������һ�������ڶ��������ڶ���������������...����̾���֮��ÿ����֮��ľ�����BFS���㼴�ɣ��������������֮���޷����˵���𰸾���NO�����ߣ�7QQQQQQQ���ӣ�https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/solution/bfs-by-7qqqqqqq/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/

/*
909. ������
N x N ������ board �ϣ����� 1 �� N*N �����ָ������ţ���� �����½ǿ�ʼ��ÿһ�н��淽��

���磬һ�� 6 x 6 ��С�����̣�������£�


r �� c �е����̣���ǰ��������ţ����̸��п��ܴ��� ���ߡ� �� �����ӡ������ board[r][c] != -1���Ǹ��߻����ӵ�Ŀ�ĵؽ����� board[r][c]��

��Ҵ������ϵķ��� 1 �����������һ�С���һ�У���ʼ������

ÿһ�غϣ������Ҫ�ӵ�ǰ���� x ��ʼ������������Ҫ��ǰ����

ѡ��Ŀ�귽��ѡ��ӱ�� x+1��x+2��x+3��x+4��x+5������ x+6 �ķ�����ѡ��һ��Ŀ�귽�� s ��Ŀ�귽��ı�� <= N*N��
��ѡ��ģ���������ӵ��龰���������̴�С��Σ����Ŀ�ĵط�ΧҲֻ�ܴ������� [x+1, x+6] ֮�䡣
������ң����Ŀ�귽�� S �������߻����ӣ���ô��һᴫ�͵��߻����ӵ�Ŀ�ĵء�������Ҵ��͵�Ŀ�귽�� S��
ע�⣬�����ÿ�غϵ�ǰ�����������ֻ�������߻�����һ�Σ�����Ŀ�ĵ�����һ���߻����ӵ���㣬��Ҳ��������ƶ���

���شﵽ���� N*N ����������ƶ���������������ܣ��򷵻� -1��



ʾ����

���룺[
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,35,-1,-1,13,-1],
[-1,-1,-1,-1,-1,-1],
[-1,15,-1,-1,-1,-1]]
�����4
���ͣ�
���ȣ��ӷ��� 1 [�� 5 �У��� 0 ��] ��ʼ��
������ƶ������� 2�����������������ƶ��������� 15��
Ȼ��������ƶ������� 17 [�� 3 �У��� 5 ��]�����������ߵ����� 13��
Ȼ��������ƶ������� 14���ұ���ͨ�������ƶ������� 35��
Ȼ��������ƶ������� 36, ��Ϸ������
����֤������Ҫ���� 4 ���ƶ����ܵ���� N*N ���������Դ��� 4��
*/

/*
��������һ�� NxN ��С�Ķ�ά���飬�����½Ǵ�1��ʼ���������ߣ������Ͻǻ������Ͻǵ�����Ϊ NxN���м�ĳЩλ�û������ӣ�����ͬ������һ����ֱ�ӿ��Ե�������һ��λ�á����ھ���ͬ����� Big Rich Man һ������һ�����ӣ�������1��6�ڵ�����һ�����֣������ݳ�һ�ѣ������޸�ң�����ӣ�ÿ�ζ�������1��6����ָ���Ĳ���������С���ü������ٵ����յ� NxN λ�á���ʼ��������ʱ�򣬿�����ֵ����Ϊ��һ����̬�滮 Dynamic Programming ���⣬�������ľ�а취���������⣬û��д��״̬ת�Ʒ��̣�ֻ�����ա�����ʵ������һ�㣬����Сֵ����һ������������������� BFS����ֱ�ӵ�Ӧ�þ������Թ������������У������㵽�յ�����ٲ�����Ҳ�������ڸ�ͨ�õĳ�����ֻҪ�Ǵ���ȷ����״̬ת�Ƶķ�ʽ������Ҳ����ʹ�á������������������Թ����������⣬�����ߵ�1��6�����Ե����������������Ϳ��Կ�����һ���Թ��ˣ�ΨһҪ���⴦��ľ����������ӵ������Ҫ������һ��λ�á�����⻹����һ���ѵ㣬�������ֱ�ź�����Ķ�ά�����ת����������ʼ�����ڶ�ά��������½ǣ�����1���������ж���Ķ�ά����� (0, 0) ���������Ͻǣ���Ҫת��һ�£����о������������������λ��Ƶģ������к���������ʱ���Ǵ�����������ģ�ת����ʱ��Ҫע��һ�¡�

�ѵ�������ᵽ�ˣ����ڿ�ʼд����ɣ���Ȼ�� BFS������Ҫ�ö��� queue ����������ʼʱ������1���룬Ȼ����Ҫһ�� visited ���飬��СΪ nxn+1���� while ѭ���н��в��������ȡ���������֣��ж������� nxn ֱ�ӷ��ؽ�� minStep�������Ҫ����1��6�ڵ���������i���� num+i ������һ��Ҫ�ߵľ��룬��Ҫ����תΪ����Ķ�ά����λ�ã���������ŵ�һ���������Ӻ����У�����ٽ���������������꣬�Ϳ��Կ���λ�����Ƿ������ӣ��еĻ�����Ҫ���������ܵ����λ�ã�û�еĻ������� num+i��������һ��λ�ã��ٿ� visited �е�ֵ�����Ѿ����ʹ���ֱ��������������Ϊ true�����Ҽ������ queue �м��ɣ��� while ѭ���˳��ˣ���ʾ�޷������յ㣬���� -1�������ֱ��תΪ��ά����λ�õ��Ӻ���Ҳ�����ѣ�����Ӧ�����ֱ�ż�1����Ϊ�����Ǵ�1��ʼ�ģ��������еĶ�ά�����Ǵ�0��ʼ�ģ�Ȼ�����n�õ������꣬��nȡ��õ������ꡣ������õ��ĺ������궼��������ȷ�ģ���Ϊǰ��˵�����ֱ�������λ��Ƶģ����к���������ʱ��������Ҫ��תһ�£����� n-1 ��ȥ��ǰ����������Ϊ�����еĶ�ά�������λ�������Ͻǣ�ͬ����Ҫ��תһ���������õ��Ĳ�����ȷ�ĺ������꣬���ؼ��ɣ�
*/

/*
    ���������ֱ��(1,2,3,...,N*N)תΪ��ά����λ��:
    (1)����Ӧ�����ֱ�ż�1����Ϊ�����Ǵ�1��ʼ�ģ��������еĶ�ά�����Ǵ�0��ʼ�ģ�
    (2)Ȼ�����n�õ������꣬��nȡ��õ������ꡣ
    (3)������õ��ĺ������궼��������ȷ�ģ���Ϊǰ��˵�����ֱ�������λ��Ƶģ�
       ���к���������ʱ��������Ҫ��תһ�£����� n-1 ��ȥ��ǰ����
*/
int  getNextBoardValue(int **board,int boardSize,int num)
{
    if(board == NULL)
    {
        return -1;
    }

    int n = boardSize;

    int x = (num - 1)/n;
    int y = (num - 1)%n;

    if(x % 2 != 0)// if x is odd number
    {
        y = (n - 1) - y;//ֻ��xλ��������(����������),y�����Ǵ�����������yҪ��ת
    }

    x = (n - 1) - x;//x�Ǵ��������ߵģ�����Ҫһֱ��ת

    return board[x][y];
}

int snakesAndLadders(int** board, int boardSize, int* boardColSize){
    if(board == NULL || boardSize == 0 || boardColSize == NULL)
    {
        return -1;
    }

    int n = boardSize;
    int c = boardColSize[0];
    int minStep = 0;
    int q[n*n];//create a queue
    int visited[n*n+1];

    memset(q,0,sizeof(q));
    memset(visited,0,sizeof(visited));
    int cur = 0;
    int next = 0;

    int front = 0;
    int rear  = 0;

    /*begin with the left lower corner of the chessboard*/
    q[rear++] = 1;//enqueue
    //visited[n - 1][0] = true;//
    int layerNum = 0;

    while(rear != front)
    {
        //printf("cur = %d\n",cur);


        layerNum = rear - front;

        for(int l = 0;l<layerNum;l++)
        {
            cur = q[front++];//dequeue
            if(cur == n*n)
            {
                return minStep;
            }
            for(int i = 1;i <= 6 && cur + i <= n*n ;i++)
            {
                next = getNextBoardValue(board,boardSize,cur+i);
                if(next == -1)
                {
                    next = cur + i;
                }

                if(visited[next])
                {
                    continue;
                }
                visited[next] = true;
                q[rear++] = next;
            }
        }
        minStep++;

    }
    return -1;
}