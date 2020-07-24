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
733. ͼ����Ⱦ
see dfs floodFill*/
int** floodFill(int** image, int imageSize, int* imageColSize,
	int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes)
{
	int row = imageSize;
	int col = imageColSize[0];

	*returnSize = imageSize;
	*returnColumnSizes = imageColSize;

	if (newColor == image[sr][sc]) {
		return image;
	}

	int queue[row * col];
	int head = 0;
	int rear = 0;

	queue[rear++] = sr * col + sc;
	int oldColor = image[sr][sc];
	image[sr][sc] = newColor;

	int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int deep = 0;
	while(rear != head) {
		int floorSize = rear - head;
		deep++;

		for (int i = 0; i < floorSize; i++) {
			int pop = queue[head++];
			int pop_x = pop / col;
			int pop_y = pop % col;

			for (int k = 0; k < 4; k++) {
				int nx = pop_x + d[k][0];
				int ny = pop_y + d[k][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (image[nx][ny] != oldColor) {
					continue;
				}

				image[nx][ny] = newColor;
				queue[rear++] = nx * col + ny;
			}
		}
	}

	return image;
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
	grid[x][y] = '0';

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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** updateBoard(char** board, int boardSize, int* boardColSize,
	int* click, int clickSize, int* returnSize, int** returnColumnSizes)
{
	int row = boardSize;
	int col = boardColSize[0];
	int queue[row * col * 1000];
	int head = 0;
	int rear = 0;

	*returnSize = boardSize;
	*returnColumnSizes = boardColSize;
	if (board == NULL || boardSize <= 0 || boardColSize == NULL || click == NULL || clickSize != 2)
		return board;

	queue[rear++] = click[0] * col + click[1];

	int deep = 0;
	int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1}};
	while(head != rear) {
		int floorSize = rear - head;
		deep++;
		for (int i = 0; i < floorSize; i++) {
			int pop = queue[head++];
			int popx = pop / col;
			int popy = pop % col;

			if (board[popx][popy] == 'M') {
				board[popx][popy] = 'X';
				return board;
			}

			int mineCnt = 0;
			for (int k = 0; k < 8; k++) {
				int nx = popx + d[k][0];
				int ny = popy + d[k][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (board[nx][ny] == 'M') {
					mineCnt++;
				}
			}

			if (mineCnt > 0 && board[popx][popy] == 'E') {
				board[popx][popy] = '0' + mineCnt;
			} else if (board[popx][popy] == 'E'){
				board[popx][popy] = 'B';
				for (int k = 0; k < 8; k++) {
					int nx = popx + d[k][0];
					int ny = popy + d[k][1];

					if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
						continue;
					}

					queue[rear++] = nx * col + ny;
				}
			}
		}
	}

	return board;
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
210. �γ̱� II
�Ѷ��е�122
�������ܹ��� n �ſ���Ҫѡ����Ϊ 0 �� n-1��
��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡� ���磬��Ҫѧϰ
�γ� 0 ������Ҫ����ɿγ� 1 ��������һ��ƥ������ʾ����: [0,1]
�����γ������Լ����ǵ��Ⱦ�������������Ϊ��ѧ�����пγ�
�����ŵ�ѧϰ˳��
���ܻ��ж����ȷ��˳����ֻҪ����һ�־Ϳ����ˡ�
���������������пγ̣�����һ�������顣
ʾ�� 1:
����: 2, [[1,0]]
���: [0,1]
����: �ܹ��� 2 �ſγ̡�Ҫѧϰ�γ� 1������Ҫ����ɿγ� 0��
��ˣ���ȷ�Ŀγ�˳��Ϊ [0,1] ��
ʾ�� 2:
����: 4, [[1,0],[2,0],[3,1],[3,2]]
���: [0,1,2,3] or [0,2,1,3]
����: �ܹ��� 4 �ſγ̡�Ҫѧϰ�γ� 3����Ӧ������ɿγ� 1 ��
�γ� 2�����ҿγ� 1 �Ϳγ� 2 ��Ӧ�����ڿγ� 0 ֮��
��ˣ�һ����ȷ�Ŀγ�˳���� [0,1,2,3] ����һ����ȷ�������� [0,2,1,3] ��
˵��:
1.	������Ⱦ��������ɱ�Ե�б��ʾ��ͼ�Σ��������ڽӾ���������μ�ͼ�ı�ʾ����
2.	����Լٶ�������Ⱦ�������û���ظ��ıߡ�
*/
/*
����������ȣ�������ͼ����һ��� v ������ȼ�Ϊ��ǰ����
���������������յ�Ϊ v �ĵıߵ���Ŀ�����ȣ�������ͼ��
��һ��� v ������ȼ�Ϊ��ǰ�������Ϊ v ��ָ����������
�ߵ���Ŀ��ÿ�δ����Ϊ 0 �Ľ�㿪ʼ��������С����Ϊ
0 ����ʾû��ǰ�ý�㡣�������Ϊ 0 �Ľ�㣬��������ָ
��Ľ������ -1 ���ٰ��µ����Ϊ 0 �Ľ�������С����
���ж�������ϣ����Ǻ��ܽ����������˵����Щ����γɻ���
*/
int* findOrder(int numCourses, int** prerequisites,
int prerequisitesSize, int* prerequisitesColSize, int* returnSize)
{
	int inDegree[numCourses];
	memset(inDegree, 0, sizeof(inDegree));
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

	int *res = (int *)calloc(numCourses, sizeof(int));
	*returnSize = 0;
	while(head != rear) {
		int pop = queue[head++];//�ڶ����ж������Ϊ0�Ķ���

		res[*returnSize] = pop;
		(*returnSize)++;

		for (int i = 0; i < prerequisitesSize; i++) {
			if (prerequisites[i][1] == pop) {
				int nextCourse = prerequisites[i][0];
				if(--inDegree[nextCourse] == 0) {
					queue[rear++] = nextCourse;
				}
			}
		}
	}

	if (*returnSize != numCourses) {
		*returnSize = 0;
	}
	return res;
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
