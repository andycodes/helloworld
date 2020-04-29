/*
1129. ��ɫ��������·��
��һ������ͼ�У��ڵ�ֱ���Ϊ 0, 1, ..., n-1�����ͼ�е�ÿ���߲��Ǻ�ɫ������ɫ���Ҵ����Ի���ƽ�бߡ�

red_edges �е�ÿһ�� [i, j] �Ա�ʾ�ӽڵ� i ���ڵ� j �ĺ�ɫ����ߡ����Ƶأ�blue_edges �е�ÿһ�� [i, j] �Ա�ʾ�ӽڵ� i ���ڵ� j ����ɫ����ߡ�

���س���Ϊ n ������ answer������ answer[X] �Ǵӽڵ� 0 ���ڵ� X �����·���ĳ��ȣ���·���Ϻ�ɫ�ߺ���ɫ�߽�����֡����������������·������ô answer[x] = -1��



ʾ�� 1��

���룺n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
�����[0,1,-1]
ʾ�� 2��

���룺n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
�����[0,1,-1]
ʾ�� 3��

���룺n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
�����[0,-1,-1]
ʾ�� 4��

���룺n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
�����[0,1,2]
ʾ�� 5��

���룺n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
�����[0,1,1]
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
		for (int i = 0; i < n; i++) { //�ڽӱ�
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

