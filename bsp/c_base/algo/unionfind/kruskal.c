struct Node{
    int val;
    int start;
    int end;
}Node;
Node V[N];

 // �����б����򣬼ǵ�iС�ı�Ϊe[i] (1<=i<=m)mΪ�ߵĸ���
 // ��ʼ��MSTΪ��
 // ��ʼ����ͨ������ʹÿ������Գ�Ϊһ����������ͨ����

 for (int i = 0; i < m; i++)
 {
     if (e[i].u��e[i].v����ͬһ��ͨ����)
     {
         // �ѱ�e[i]����ͣӣ�
         // �ϲ�e[i].u��e[i].v���ڵ���ͨ����
     }
 }

/*
1135. ��ͳɱ���ͨ���г���
�Ѷ��е�23
����һ�����Ǹ����л����滮�ߣ���ͼ���� N �����У�
���ǰ��� 1 �� N �Ĵ����š�
����һЩ�����ӵ�ѡ�� conections������ÿ��ѡ�� conections[i] =
[city1, city2, cost] ��ʾ������ city1 �ͳ��� city2 ������Ҫ�ĳɱ���
��������˫��ģ�Ҳ����˵���� city1 �ͳ��� city2 ����Ҳͬ��
��ζ�ų��� city2 �ͳ��� city1 ��������
����ʹ��ÿ�Գ��м䶼���ڽ�����������һ�����ͨ·
�������ܳ���Ϊ 1 �ģ���С�ɱ�������С�ɱ�Ӧ��������
ȫ�����Ӵ��۵��ۺϡ����������֪�����޷���ɸ�����
�������㷵�� -1��

ʾ�� 1��

���룺N = 3, conections = [[1,2,5],[1,3,6],[2,3,1]]
�����6
���ͣ�
ѡ������ 2 ���߶������������г��У����Ǵ���ѡȡ�ɱ���
С�� 2 ����

*/

/*
Ԥ��֪ʶ��С������ͼ����������һ�ú��������еĶ����
�޻���ͨ��ͼ��һ����Ȩͼ����С�������� MST �� ������һ
��Ȩֵ���������бߵ�Ȩֵ֮�ͣ���С����������
���鼯���鼯��һ�����͵����ݽṹ�����ڴ���һЩ����
�����ϵĺϲ�����ѯ���⡣������ʹ������ɭ������ʾ��
����һ��kruskal �㷨˼·�������⣬���ǿ��԰� N �����п���
N �����㣬�����������еĳɱ� cost ���Ƕ�Ӧ��Ȩ�أ���Ҫ
�����������г��е���С�ɱ�������Ȼ������һ����׼��
��С���������������ǽ��ܵ�һ�־����㷨�� kruskal �㷨��
��Ȼ������Ҫ����С�ɱ�����ô���Կ϶��������ͼû��
��������л��Ļ�������ζ�����ɾ��һ����ʹ�óɱ���
С�������㷨���ǻ���������ԣ����ձߵ�Ȩ��˳�򣨴�
С���󣩴������еıߣ����߼��뵽��С�������У�
����ı߲������Ѿ�����ı߹��ɻ���ֱ�����к��� N - 1 ��
��Ϊֹ����Щ�߻���һƬɭ�ֱ��һ���������������ͼ
����С��������
*/

 int minimumCost(int N, int** connections, int connectionsSize, int* connectionsColSize)
{
	qsort(connections, connectionsSize, sizeof(connections[0]), cmp_point);
	int cost = 0;

	struct UnionFind duf;
	struct UnionFind* uf = &duf;
	uf_init(uf, N + 1);
	uf->cnt = N;
	for (int i = 0; i < connectionsSize; i++) {
		if (!uf_isOneUnion(uf, connections[i][0], connections[i][1])) {
			uf_union(uf, connections[i][0], connections[i][1]);
			cost += connections[i][2];
		}
	}

	return uf->cnt == 1 ? cost : -1;
}


/*
1584. �������е����С����
����һ��points ���飬��ʾ 2D ƽ���ϵ�һЩ�㣬���� points[i] = [xi, yi] ��

���ӵ� [xi, yi] �͵� [xj, yj] �ķ���Ϊ����֮��� �����پ��� ��|xi - xj| + |yi - yj| ������ |val| ��ʾ val �ľ���ֵ��

���㷵�ؽ����е����ӵ���С�ܷ��á�ֻ����������֮�� ���ҽ��� һ����·��ʱ������Ϊ���е㶼�����ӡ�



ʾ�� 1��



���룺points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
�����20
���ͣ�

���ǿ��԰�����ͼ��ʾ�������е�õ���С�ܷ��ã��ܷ���Ϊ 20 ��
ע�⵽����������֮��ֻ��Ψһһ��·�����ൽ�
*/
//��¼������ı�ź�Ȩֵ
struct Edge{
    int u;
    int v;
    int w;
};
typedef struct Edge Edge;

//·��ѹ��
int find(int* S, int x){
    if(S[x] < 0)
        return x;
    else
        return S[x] = find(S, S[x]);
}

//���ȹ鲢
void Union(int* S, int root1, int root2){
    if(S[root1] < S[root2])
        S[root2] = root1;
    else{
        if(S[root1] == S[root2])
            S[root1]--;
        S[root2] = root1;
        }
}

//��Ȩֵ���п�������
void quick_sort(Edge* E, int l, int r){
    if(l >= r) return;
    int i = l - 1, j = r + 1, x = E[l + r >> 1].w;
    while(i < j){
        while(E[++i].w < x);
        while(E[--j].w > x);
        if(i < j){
            Edge tmp;
            tmp.u = E[i].u, tmp.v = E[i].v, tmp.w = E[i].w;
            E[i].u = E[j].u, E[i].v = E[j].v, E[i].w = E[j].w;
            E[j].u = tmp.u, E[j].v = tmp.v, E[j].w = tmp.w;
            }
        }
    quick_sort(E, l, j);
    quick_sort(E, j + 1, r);
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    int edges = 0;
    int res = 0;
    int u, v, w;
    int n = pointsSize;
    int* S = (int*)calloc(n, sizeof(int));
    memset(S, -1, sizeof(int) * n);
    Edge* E = (Edge*)calloc((n * (n - 1))/2, sizeof(Edge));
    int size = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            E[size].u = i;
            E[size].v = j;
            E[size++].w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            }
        }
    quick_sort(E, 0, size - 1);
    int pos = 0;
    while(edges != n - 1){
        u = E[pos].u;
        v = E[pos].v;
        w = E[pos].w;
        int root1 = find(S, u);
        int root2 = find(S, v);
        if(root1 != root2){
            edges++;
            res += w;
            Union(S, root1, root2);
            }
        pos++;
        }
    free(S);
    free(E);

    return res;
}

//Prim�㷨

int res;

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    res = 0;
    int n = pointsSize;
    bool collected[n];
    int dist[n];    //dist[i]��ʾi�ŵ㵽�㼯����̾���
    int fee[n][n];  //fee[i][j] ��ʾi��j��������ķ���
    memset(collected, 0, sizeof(collected));

    for(int i = 0; i < n; i++){
        fee[i][i] = 0;
        for(int j = i + 1; j < n; j++)
            fee[i][j] = fee[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        }
    //��0�ŵ㿪ʼ,��ʱ�㼯ֻ��0
    collected[0] = true;
    for(int i = 0; i < n; i++) dist[i] = fee[i][0];

    while(1){
        int v = -1;
        int mindist = INT_MAX;
        for(int i = 0; i < n; i++){
            if(collected[i]) continue;
            if(dist[i] < mindist){
                mindist = dist[i];
                v = i;
                }
            }
        if(v == -1) break;
        res += mindist;
        collected[v] = true;
        dist[v] = 0;
        for(int i = 0; i < n; i++)  //����δ��¼��������¼�㼯����̾���
            if(!collected[i] && dist[i] > fee[v][i])
                dist[i] = fee[v][i];
        }
    return res;
}

/*
1168. ˮ��Դ�����Ż�
������һ���� n �����ӡ�����ϣ��ͨ������ˮ��������ܵ���Ϊ���з��ӹ�ˮ��

����ÿ������ i�����������ֿ�ѡ�Ĺ�ˮ������

һ����ֱ���ڷ����ڽ���ˮ�����ɱ�Ϊ wells[i]��
��һ���Ǵ���һ�ھ�����ܵ���ˮ������ pipes �������ڷ��Ӽ�����ܵ��ĳɱ�������ÿ�� pipes[i] = [house1, house2, cost] �����ùܵ��� house1 �� house2 ������һ��ĳɱ�����Ȼ��������˫��ġ�
�����æ����Ϊ���з��Ӷ���ˮ������ܳɱ���
*/

int minCostToSupplyWater(int n, int* wells, int wellsSize,
int** pipes, int pipesSize, int* pipesColSize)
{
	struct HeapCtrl *hp = heapInit(wellsSize + pipesSize);
	for (int i = 0; i < wellsSize; i++) {
		struct heapEntry node;
		node.start = i + 1;
		node.end = 0;
		node.key = wells[i];
		heapPush(hp, node);
	}

	for (int i = 0; i < pipesSize; i++) {
		struct heapEntry node;
		node.start = pipes[i][0];
		node.end = pipes[i][1];
		node.key = pipes[i][2];
		heapPush(hp, node);
	}

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, n + 1);

	int cost = 0;
	while(!heapEmpty(hp)) {
		struct heapEntry pop = heapPop(hp);
		if (!uf_isOneUnion(uf, pop.start, pop.end)) {
			uf_union(uf, pop.start, pop.end);
			cost += pop.key;
		}
	}

	return cost;
}