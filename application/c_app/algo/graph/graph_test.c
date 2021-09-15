
struct Node{
    int val;
    int start;
    int end;
}Node;
Node V[N];


/*
1129. 颜色交替的最短路径
在一个有向图中，节点分别标记为 0, 1, ..., n-1。这个图中的每条边不是红色就是蓝色，且存在自环或平行边。

red_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的红色有向边。类似地，blue_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的蓝色有向边。

返回长度为 n 的数组 answer，其中 answer[X] 是从节点 0 到节点 X 的最短路径的长度，且路径上红色边和蓝色边交替出现。如果不存在这样的路径，那么 answer[x] = -1。



示例 1：

输入：n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
输出：[0,1,-1]
示例 2：

输入：n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
输出：[0,1,-1]
示例 3：

输入：n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
输出：[0,-1,-1]
示例 4：

输入：n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
输出：[0,1,2]
示例 5：

输入：n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
输出：[0,1,1]
*/

#define MAX_N 101
void InitGragh(char gragh[MAX_N][MAX_N][2], int **red_edges, int red_edgesSize, int **blue_edges, int blue_edgesSize)
{
    for (int i = 0; i < red_edgesSize; i++) {
        if (gragh[red_edges[i][0]][red_edges[i][1]][0] == 0) {
            gragh[red_edges[i][0]][red_edges[i][1]][0] = 'R';
        } else {
            gragh[red_edges[i][0]][red_edges[i][1]][1] = 'R';
        }
    }
    for (int i = 0; i < blue_edgesSize; i++) {
        if (gragh[blue_edges[i][0]][blue_edges[i][1]][0] == 0) {
            gragh[blue_edges[i][0]][blue_edges[i][1]][0] = 'B';
        } else {
            gragh[blue_edges[i][0]][blue_edges[i][1]][1] = 'B';
        }
    }
}

int* shortestAlternatingPaths(int n, int **red_edges, int red_edgesSize, int* red_edgesColSize, int **blue_edges, int blue_edgesSize, int* blue_edgesColSize, int* returnSize)
{
	char gragh[MAX_N][MAX_N][2] = {0};
	int *ans = (int*)malloc(n * sizeof(int));
	for (int i = 1; i < n; i++) {
		ans[i] = INT_MAX;
	}

	struct List list;
	struct List *queue = &list;
	queue_init(queue);

	struct DataEntry  *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
	entry->n = 0;
	entry->color = -1;
	ListAddTail(queue, &entry->node);


	InitGragh(gragh, red_edges, red_edgesSize, blue_edges, blue_edgesSize);
	int step = 0;
	while (!queue_empty(queue)) {
        step++;
        int len = queue_size(queue);
        while (len--) {
		struct DataEntry *cur = queue_pop_entry(queue);
		for (int i = 0; i < n; i++) { //邻接表
                char nextColor = -1;
                if (gragh[cur->n][i][0] != 0) {
                    nextColor = gragh[cur->n][i][0];
                    if (nextColor != cur->color) {
			struct DataEntry  *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
			entry->n = i;
			entry->color = nextColor;
			ListAddTail(queue, &entry->node);
			gragh[cur->n][i][0] = 0;
			ans[i] = ans[i] < step ? ans[i] : step;
                    }
                }

                if (gragh[cur->n][i][1] != 0) {
                    nextColor = gragh[cur->n][i][1];
                    if (nextColor != -1 && cur->color != nextColor) {
			struct DataEntry  *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
			entry->n = i;
			entry->color = nextColor;
			ListAddTail(queue, &entry->node);
			gragh[cur->n][i][1] = 0;
			ans[i] = ans[i] < step ? ans[i] : step;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (ans[i] == INT_MAX) {
            ans[i] = -1;
        }
    }

	ans[0] = 0;
	*returnSize = n;
	return ans;
}

/*
310. 最小高度树
难度中等169
对于一个具有树特征的无向图，我们可选择任何一个节点作为根。图因此可以成为树，在所有可能的树中，具有最小高度的树被称为最小高度树。给出这样的一个图，写出一个函数找到所有的最小高度树并返回他们的根节点。
格式
该图包含 n 个节点，标记为 0 到 n - 1。给定数字 n 和一个无向边 edges 列表（每一个边都是一对标签）。
你可以假设没有重复的边会出现在 edges 中。由于所有的边都是无向边， [0, 1]和 [1, 0] 是相同的，因此不会同时出现在 edges 里。
示例 1:
输入: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3

*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMinHeightTrees(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    int* pQueue = (int*)malloc(n * sizeof(int)); // 队列
    memset(pQueue, 0, n * sizeof(int));
    int front = -1; // 队头下标
    int rear = -1; // 队尾下标
    int curr = 0; // 当前队头元素
    int lenghOfQue = 0; // 队长

    if (1 == n && 0 == edgesSize)
    {
        *returnSize = 1;
        return pQueue;
    }

    int* pIndegree = (int*)malloc(n * sizeof(int)); // 入度数组
    memset(pIndegree, 0, n * sizeof(int)); // 入度初始为0

    int** ppGraph = (int**)malloc(n * sizeof(int*)); // 二维数组邻接表
    int* pColOfGraph = (int*)malloc(n * sizeof(int)); // 每个结点相邻结点个数
    memset(pColOfGraph, 0, n * sizeof(int));
    int row = 0;
    int col = 0;
    for (row = 0; row <= n - 1; row++)
    {
        ppGraph[row] = (int*)malloc(n * sizeof(int*));
    }

    for (row = 0; row <= edgesSize - 1; row++) // 初始化邻接表：图 入度 相邻点
    {
        ppGraph[edges[row][1]][pIndegree[edges[row][1]]++] = edges[row][0];
        ppGraph[edges[row][0]][pIndegree[edges[row][0]]++] = edges[row][1];
        pColOfGraph[edges[row][1]]++;
        pColOfGraph[edges[row][0]]++;
    }

    for (row = 0; row <= n - 1; row++) // 入度为1的结点进队
    {
        if (1 == pIndegree[row])
        {
            pQueue[++rear] = row;
        }
    }

    while (2 < n) // 结果只能是1或者2，证明略
    {
        lenghOfQue = rear - front; // 队长
        n -= lenghOfQue; // 更新结点个数

        while (lenghOfQue--)
        {
            curr = pQueue[++front]; // peek & pop

            for (col = 0; col <= pColOfGraph[curr] - 1; col++)
            {
                --pIndegree[curr];
                --pIndegree[ppGraph[curr][col]];

                if (1 == pIndegree[ppGraph[curr][col]])
                {
                    pQueue[++rear] = ppGraph[curr][col]; // push
                }
            }
        }
    }

    *returnSize = rear - front;
    return pQueue + front + 1;
}