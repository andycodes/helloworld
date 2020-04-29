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

