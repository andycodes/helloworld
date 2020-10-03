/*
��³˹�����㷨
��С������
�ӱߵ��ӽ�

����:unionFind
�����б��������ȫ������heap
*/

struct Edge{
    int cost;
    int start;
    int end;
};

struct Edge edges[N];


/*
1584. �������е����С����
����һ��points ���飬��ʾ 2D ƽ���ϵ�һЩ�㣬���� points[i] = [xi, yi] ��
���ӵ� [xi, yi] �͵� [xj, yj] �ķ���Ϊ����֮��� �����پ��� ��
|xi - xj| + |yi - yj| ������ |val| ��ʾ val �ľ���ֵ��
���㷵�ؽ����е����ӵ���С�ܷ��á�ֻ����������֮�� ��
�ҽ��� һ����·��ʱ������Ϊ���е㶼�����ӡ�
ʾ�� 1��
���룺points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
�����20
���ͣ�
���ǿ��԰�����ͼ��ʾ�������е�õ���С�ܷ��ã�
�ܷ���Ϊ 20 ��
ע�⵽����������֮��ֻ��Ψһһ��·�����ൽ�
*/
struct Edge{
    int start;
    int end;
    int w;
};

int cmp_struct(const void *a, const void *b)
{
	struct Edge* aa = (struct Edge*)a;
	struct Edge* bb = (struct Edge*)b;
	return aa->w - bb->w;
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize)
{
	int res = 0;
	int start, end, w;

	if (pointsSize < 2) {
		return 0;
	}

	int edgeSize = (pointsSize * (pointsSize - 1))/2;
	struct Edge edges[edgeSize];
	int size = 0;
	for(int i = 0; i < pointsSize; i++){
		for(int j = i + 1; j < pointsSize; j++){
			edges[size].start = i;
			edges[size].end = j;
			edges[size++].w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
		}
	}

	qsort(edges, edgeSize, sizeof(edges[0]), cmp_struct);

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, pointsSize);

	int pos = 0;
	while(uf->sideCnt > 1){
		start = edges[pos].start;
		end = edges[pos].end;
		w = edges[pos].w;

		if (!uf_isOneUnion(uf, start, end)) {
			uf_union(uf, start, end);
			res += w;
		}

		pos++;
	}

	return res;
}

