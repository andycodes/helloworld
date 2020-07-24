
struct Node{
    int val;
    int start;
    int end;
}Node;
Node V[N];


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

/*
310. ��С�߶���
�Ѷ��е�169
����һ������������������ͼ�����ǿ�ѡ���κ�һ���ڵ���Ϊ����ͼ��˿��Գ�Ϊ���������п��ܵ����У�������С�߶ȵ�������Ϊ��С�߶���������������һ��ͼ��д��һ�������ҵ����е���С�߶������������ǵĸ��ڵ㡣
��ʽ
��ͼ���� n ���ڵ㣬���Ϊ 0 �� n - 1���������� n ��һ������� edges �б�ÿһ���߶���һ�Ա�ǩ����
����Լ���û���ظ��ı߻������ edges �С��������еı߶�������ߣ� [0, 1]�� [1, 0] ����ͬ�ģ���˲���ͬʱ������ edges �
ʾ�� 1:
����: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

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
    int* pQueue = (int*)malloc(n * sizeof(int)); // ����
    memset(pQueue, 0, n * sizeof(int));
    int front = -1; // ��ͷ�±�
    int rear = -1; // ��β�±�
    int curr = 0; // ��ǰ��ͷԪ��
    int lenghOfQue = 0; // �ӳ�

    if (1 == n && 0 == edgesSize)
    {
        *returnSize = 1;
        return pQueue;
    }

    int* pIndegree = (int*)malloc(n * sizeof(int)); // �������
    memset(pIndegree, 0, n * sizeof(int)); // ��ȳ�ʼΪ0

    int** ppGraph = (int**)malloc(n * sizeof(int*)); // ��ά�����ڽӱ�
    int* pColOfGraph = (int*)malloc(n * sizeof(int)); // ÿ��������ڽ�����
    memset(pColOfGraph, 0, n * sizeof(int));
    int row = 0;
    int col = 0;
    for (row = 0; row <= n - 1; row++)
    {
        ppGraph[row] = (int*)malloc(n * sizeof(int*));
    }

    for (row = 0; row <= edgesSize - 1; row++) // ��ʼ���ڽӱ�ͼ ��� ���ڵ�
    {
        ppGraph[edges[row][1]][pIndegree[edges[row][1]]++] = edges[row][0];
        ppGraph[edges[row][0]][pIndegree[edges[row][0]]++] = edges[row][1];
        pColOfGraph[edges[row][1]]++;
        pColOfGraph[edges[row][0]]++;
    }

    for (row = 0; row <= n - 1; row++) // ���Ϊ1�Ľ�����
    {
        if (1 == pIndegree[row])
        {
            pQueue[++rear] = row;
        }
    }

    while (2 < n) // ���ֻ����1����2��֤����
    {
        lenghOfQue = rear - front; // �ӳ�
        n -= lenghOfQue; // ���½�����

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