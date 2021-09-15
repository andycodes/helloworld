
/*
1391. ����������Ƿ������Ч·��
����һ�� m x n ������ grid���������ÿ����Ԫ������һ���ֵ���
grid[i][j] �Ľֵ������ǣ�
1 ��ʾ������Ԫ����ҵ�Ԫ��Ľֵ���
2 ��ʾ�����ϵ�Ԫ����µ�Ԫ��Ľֵ���
3 ��ʾ������Ԫ����µ�Ԫ��Ľֵ���
4 ��ʾ�����ҵ�Ԫ����µ�Ԫ��Ľֵ���
5 ��ʾ������Ԫ����ϵ�Ԫ��Ľֵ���
6 ��ʾ�����ҵ�Ԫ����ϵ�Ԫ��Ľֵ���
*/
/*
     0
     ^
     |
3 <-- --> 1
     |
     v
     2

������ŵĺô���ʲô�أ����Է��֣�ֻ������Щ����£�
�������ڵĵ�Ԫ�����������
���ĳһ����Ԫ���е� 00 ��������ô���Ϸ��ĵ�Ԫ�����
�е� 22 ������
���ĳһ����Ԫ���е� 11 ��������ô���Ҳ�ĵ�Ԫ���
���е� 33 ������
���ĳһ����Ԫ���е� 22 ��������ô���·��ĵ�Ԫ�����
�е� 00 ������
���ĳһ����Ԫ���е� 33 ��������ô�����ĵ�Ԫ�����
�е� 11 ������
������ʲô���ɣ�
���ĳһ����Ԫ���е� ii ��������ô���ڵ� ii ���������ڵ�
��Ԫ������е� (i + 2) \% 4(i+2)%4 ������
��ˣ����Ǳ����������񣬶������е�ÿһ����Ԫ�� (x, y)(x,y)��
����ö�������ĸ����ڵĵ�Ԫ�񣬶��ڵ� ii ����������ڵ�Ԫ
������ (x, y)(x,y) �������ҽ��� (x, y)(x,y) ��Ӧ�Ķ��������ĵ� ii λ
�����ڵ�Ԫ���Ӧ�Ķ��������ĵ� (i + 2) % 4 λ��Ϊ 11��
�ڱ�������֮�������ж����ϽǺ����½��ڲ��鼯���Ƿ�
����ͬһ���ϼ��ɡ�
*/

int patterns[7] = {0, 0b1010, 0b0101, 0b1100, 0b0110, 0b1001, 0b0011};
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dimenMap(int x, int y, int colSize)
{
	return x * colSize+ y;
}

void hander(struct UnionFind* uf, int** grid, int row, int col, int x, int y)
{
        for (int i = 0; i < 4; ++i) {// 4 bit �ĸ�����
	    	if ((patterns[grid[x][y]] & (1 << i)) == 0)
				continue;//�Լ���ͨ

		//each set bit
		int nx = x + dirs[i][0];
		int ny = y + dirs[i][1];
		if (nx >= 0 && nx < row && ny >= 0 && ny < col &&
			(patterns[grid[nx][ny]] & (1 << ((i + 2) % 4)))) {
			uf_union(uf, dimenMap(x, y, col), dimenMap(nx, ny, col));
		}
        }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = gridColSize[0];

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, row * col);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                hander(uf, grid, row, col, i, j);
            }
        }

	return uf_isOneUnion(uf, dimenMap(0, 0, col), dimenMap(row - 1, col - 1, col));
}


/*
1102. �÷���ߵ�·��
BFS
*/
typedef struct {
    int x;
    int y;
    int value;
} Node;

int NodeCmp (const void *p1, const void *p2)
{
    return (((Node *)p2)->value - ((Node*)p1)->value);
}

int maximumMinimumPath(int** A, int ASize, int* AColSize)
{
	int matrixSize = ASize * (*AColSize);
	int visited[matrixSize];
	Node nodeSet[matrixSize];//matrixSize������
	memset(visited, 0, sizeof(visited));
	memset(nodeSet,0,sizeof(nodeSet));

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, matrixSize);
	int count = 0;
	for (int i = 0; i < ASize; i++) {
		for (int j = 0; j < (*AColSize); j++) {
			nodeSet[count].x = i;
			nodeSet[count].y = j;
			nodeSet[count].value = A[i][j];
			count++;
		}
	}

	qsort(nodeSet, matrixSize, sizeof(Node), NodeCmp);

	count = 0;
	int ans = fmin(A[0][0], A[ASize - 1][*AColSize - 1]);
	int direction[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
	while (!uf_isOneUnion(uf, 0, matrixSize - 1)) {
		int x = nodeSet[count].x;
		int y = nodeSet[count].y;
		int index = x * (*AColSize) + y;
		visited[index] = 1;
		ans = fmin(ans, nodeSet[count].value);
		for (int i = 0; i < 4; i++) {
			int nx, ny;
			nx = x + direction[i][0];
			ny = y + direction[i][1];
			int indexNew = nx * (*AColSize) + ny;
			if (nx < ASize && nx > -1 && ny < (*AColSize) && ny > -1 && visited[indexNew] == 1) {
				uf_union(uf, index, indexNew);
			}
		}
		count++;
	}
	return ans;
}

/*
959. ��б�ܻ�������
�Ѷ��е�73
���� 1 x 1 ������ɵ� N x N ���� grid �У�ÿ�� 1 x 1 ������ /��\ ���
�񹹳ɡ���Щ�ַ��Ὣ���黮��ΪһЩ���ߵ�����
����ע�⣬��б���ַ���ת��ģ���� \ �� "\\" ��ʾ������
�����������Ŀ��

ʾ�� 1��
���룺
[
  " /",
  "/ "
]
�����2
���ͣ�2x2 �������£�

*/
/*
*0*
1*2
*3*
*/
int regionsBySlashes(char ** grid, int gridSize)
{
        int N = gridSize;

	struct UnionFind duf;
	struct UnionFind* uf = &duf;

	int ufSize = 4 * N * N;
	uf_init(uf, ufSize);
        for (int r = 0; r < N; ++r) //row������
            for (int c = 0; c < N; ++c) { //col������  ����for����grid��ÿ���ַ�
                int root = 4 * (r * N + c);
                char val = grid[r][c]; //�ַ�

                if (val != '\\') {    //���Ϊ '/'����' '����ϣ�0��1������2��3��.
                    uf_union(uf, root + 0, root + 1);
                    uf_union(uf, root + 2, root + 3);
                }

                if (val != '/') {    //���Ϊ '\\'����' '����ϣ�0��2������1��3��
                    uf_union(uf, root + 0, root + 2);
                    uf_union(uf, root + 1, root + 3);
                }
// ����������һ�У������¹鲢 ��3 �鲢���е�0      0
                if (r + 1 < N)
                    uf_union(uf, root + 3, (root + 4 * N) + 0);                //     1    2    1    2
//������ǵ�һ�У������Ϲ鲢��0�鲢���е�3           3
                if (r - 1 >= 0)
                    uf_union(uf, root + 0, (root - 4 * N) + 3);                  //      0        0
                                                                           //       1   2    1    2
//����������һ�У������ҹ鲢��2�鲢���ڵ�1            3         3
		if (c + 1 < N)
                    uf_union(uf, root + 2, (root + 4) + 1);
//������ǵ�һ�У�������鲢��1�鲢���ڵ�2
                if (c - 1 >= 0)
                    uf_union(uf, root + 1, (root - 4) + 2);
            }

        int ans = 0;
        for (int x = 0; x < 4 * N * N; ++x) {
            if (uf_findRoot(uf, x) == x)
                ans++;
        }

        return ans;
    }

/*
685. �������� II
�ڱ������У��и���ָ������������������ͼ������ֻ��һ
�����ڵ㣬���������ڵ㶼�Ǹø��ڵ�ĺ�̡�ÿһ���ڵ�
ֻ��һ�����ڵ㣬���˸��ڵ�û�и��ڵ㡣
����һ������ͼ����ͼ��һ������N���ڵ� (�ڵ�ֵ���ظ�1, 2,
..., N) ������һ�����ӵı߹��ɡ����ӵıߵ��������������
1��N�м䣬�������ӵı߲����������Ѵ��ڵıߡ�
���ͼ��һ���Ա���ɵĶ�ά���顣 ÿһ���� ��Ԫ����һ
�� [u, v]�����Ա�ʾ����ͼ�����Ӷ��� u �Ͷ��� v �ıߣ�����
u �� v ��һ�����ڵ㡣
����һ����ɾ���ıߣ�ʹ��ʣ�µ�ͼ����N���ڵ���и�����
���ж���𰸣������������ڸ�����ά����Ĵ𰸡�
ʾ�� 1:
����: [[1,2], [1,3], [2,3]]
���: [2,3]
����: ����������ͼ����:
  1
 / \
v   v
2-->3
*/

/*
��ͳ�Ƹ������ȣ���1�α������С��2�ĵ㣬����ɻ�����������⣬����������Ϊ2�ĵ㣬�򷵻ص�ǰ�ɻ��ĵ㣻��2�α�����ȴ���2�ĵ㣬����ɻ�����������⣬���ص�ǰ�ɻ��ĵ㣬��Ϊ��ȴ���1�ĵ�ֻ������1�������ߣ�ajoy���ӣ�https://leetcode-cn.com/problems/redundant-connection-ii/solution/685rong-yu-lian-jie-ii-by-ajoy/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int Find(int uNums[], int q)
{
    while (uNums[q] != q) {
        uNums[q] = uNums[uNums[q]];
        q = uNums[q];
    }
    return q;
}

void Union(int uNums[], int p, int q)
{
    uNums[Find(uNums, p)] = Find(uNums, q);
}

int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    int uNums[edgesSize + 1];
    for (int i = 0; i < edgesSize + 1; i++) {
        uNums[i] = i;
    }
    *returnSize = 2;
    int indegree[edgesSize + 1];
    memset(indegree, 0, (edgesSize + 1) * sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        indegree[edges[i][1]]++;
    }
    for (int i = 0; i < edgesSize; i++) {
        if (indegree[edges[i][1]] <= 1) {
            if (Find(uNums, edges[i][0]) == Find(uNums, edges[i][1])) {
                return edges[i];
            }
            Union(uNums, edges[i][0], edges[i][1]);
        }
    }
    for (int i = 0; i < edgesSize; i++) {
        if (indegree[edges[i][1]] > 1) {
            if (Find(uNums, edges[i][0]) == Find(uNums, edges[i][1])) {
                return edges[i];
            }
            Union(uNums, edges[i][0], edges[i][1]);
        }
    }
    return NULL;
}

/*
924. �������ٶ�������Ĵ���
�ڽڵ������У�ֻ�е� graph[i][j] = 1 ʱ��ÿ���ڵ� i �ܹ�ֱ�����ӵ���һ���ڵ� j��

һЩ�ڵ� initial ��������������Ⱦ��ֻҪ�����ڵ�ֱ�����ӣ�����������һ���ڵ��ܵ���������ĸ�Ⱦ����ô�����ڵ㶼�������������Ⱦ�����ֶ�������Ĵ�����������ֱ��û�и���Ľڵ���Ա����ַ�ʽ��Ⱦ��

���� M(initial) ���ڶ������ֹͣ����֮�����������и�Ⱦ������������սڵ�����

���ǿ��Դӳ�ʼ�б���ɾ��һ���ڵ㡣����Ƴ���һ�ڵ㽫��С�� M(initial)�� �򷵻ظýڵ㡣����ж���ڵ������������ͷ���������С�Ľڵ㡣

��ע�⣬���ĳ���ڵ��Ѵ��ܸ�Ⱦ�ڵ���б� initial ��ɾ�������Ժ������Ȼ���������������ܵ���Ⱦ��
*/
/*
������ĿҪ����ٶ�������Ĵ������������˼��Ҫ�󽫸ýڵ�ɾ��֮�󣬲��ܸ�Ⱦ�����������ࡣ�򵥵�˼����һ�£�����ýڵ���ͨ�Ľڵ�����Խ�࣬��ô�ýڵ�ɾ��֮���Ȼ��Ӱ��Ľڵ�����ࡣ�������ʼ��һ��˼·�����Ҹо����˼·�����ָ����ļ�����������˳��ͨ�������ֻ��������⣬ͨ�����鼯�������ܹ����ٵĸ㶨�����Ƿ����ύ��û��ͨ����ȷʵ�Ե������������Ѷ�(����)�������Ŀ��ֻ�Ǽ򵥵���ĳ���ڵ���ͨ�Ľڵ���໹���У�Ϊʲô�أ���Ϊ�����ͨ�Ľڵ��У��ж���ڴ�ȾԴ�У����Ǽ�ʱ�ҵ�����һ������ɾ����Ҳ���ܼ����������Ⱦ�Ľڵ���������ΪֻҪ����ͨ�ģ���ô����һ����ɾ����Ҳ�ᱻ������ͨ�ڵ�Ĵ�ȾԴ��Ⱦ����˲��ܼ򵥵�ֱ��ɾ����ͨ�ڵ����Ľڵ㣬���еķ���������ͳ�ƴ�ȾԴ�ڵ�����ͬһ����ͨ��(����)�еĽڵ�����������ͨ���еĽڵ�������1����ýڵ㲻��ɾ�����������ͨ���еĽڵ�������1����ôɾ������ͨ��Ľڵ���ܼ��ٱ���Ⱦ�Ľڵ㡣���ܸ�Ⱦ�Ľڵ�������࣬��ô�����ҵ���ͨ���и�ȾԴֻ��1�������ӽڵ������Ǹ���ȾԴ�������յĴ𰸡��ۺ������ķ�������ͨ�����µķ��������1�����ȸ��ݵ�ǰ�����Ӿ��󣬿��ٵĴ���һ�����鼯����Ҫͳ��Ȩ�أ���Ҫ��ͳ�ƺϲ��ĸ�������ͬʱ�����ܵ���С�������ϲ���2��������Ҫ�������С�ĸ�ȾԴ����˰����������и�ȾԴ��3�����ݸ�ȾԴ�ڵ��б������ͨ��ĸ�Ⱦ�ڵ������4�����ݸ�ȾԴ��������1���ҵ�Ȩ�����ģ�������С�ĸ�ȾԴ���ø�ȾԴ����Ҫɾ���Ľڵ㡣���ߣ�gpking���ӣ�https://leetcode-cn.com/problems/minimize-malware-spread/solution/jian-shao-e-yi-ruan-jian-de-chuan-bo-bing-cha-ji-d/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/

/*
����˼�������ͨ��ͼ����ͳ�Ƹ�����ͼ�а�����Ⱦ�ڵ������һ����Ⱦ�ڵ�����Ը�Ⱦ������ͼ���������һ����ͼ�ж���һ����Ⱦ�ڵ㣬��ô��ʹȥ��һ����Ҳ��������ܸ�Ⱦ�ڵ�����ѡ����ͼ�нڵ���࣬��ֻ��һ����Ⱦ�ڵ�Ľ�����ߣ�chaoooooo���ӣ�https://leetcode-cn.com/problems/minimize-malware-spread/solution/cyu-yan-bing-cha-ji-by-chaoooooo/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/


#define MAXPOINTS 301
typedef struct {
    int parent[MAXPOINTS];
    int weight[MAXPOINTS];
    int max;
    int cnt;
} UF_t;

UF_t g_uf;

UF_t *UFInit(int max)
{
    memset(&g_uf, 0, sizeof(UF_t));

    g_uf.max = max;
    g_uf.cnt = max;
    for (int i = 0; i < max; ++i) {
        g_uf.parent[i] = i;
        g_uf.weight[i] = 1;
    }

    return &g_uf;
}

int UFFind(UF_t *uf, int id)
{
    int son = id;

    while (id != uf->parent[id]) {
        id = uf->parent[id];
    }

    while (son != id) { // ·��ѹ��
        int tmp = uf->parent[son];
        uf->parent[son] = id;
        son = tmp;
    }

    return id;
}

void UFUnion(UF_t *uf, int id1, int id2)
{
    int id1Root = UFFind(uf, id1);
    int id2Root = UFFind(uf, id2);

    if (id1Root == id2Root) {
        return;
    }

    if (id1Root < id2Root) {
        uf->parent[id2Root] = id1Root;
        uf->weight[id1Root] += uf->weight[id2Root]; // ������ڵ��Ȩ��
    } else {
        uf->parent[id1Root] = id2Root;
        uf->weight[id2Root] += uf->weight[id1Root];
    }

    uf->cnt--;
}

int UFCount(UF_t *uf)
{
    return uf->cnt;
}

int UFWeight(UF_t *uf, int id)
{
    int root = UFFind(uf, id);
    return uf->weight[root];
}

int UFSize(UF_t *uf)
{
    return uf->max;
}

int CheckParam(int **graph, int graphSize, int *graphColSize, int *initial, int initialSize)
{
    if (graph == NULL || graphSize <= 0 || graphColSize == NULL || initial == NULL || initialSize <= 0) {
        return -1;
    }

    if (graphColSize[0] <= 0) {
        return -1;
    }

    return 0;
}

UF_t * BuildUF(int **graph, int graphSize, int *graphColSize)
{
    UF_t *uf = UFInit(graphSize);

    for (int i = 0; i < graphSize; ++i) {
        for (int j = i + 1; j < graphSize; ++j) {
            if (graph[i][j] == 1) {
                UFUnion(uf, i, j); // �ϲ���ͨ��
            }
        }
    }

    return uf;
}

int InitCmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int Search(UF_t *uf, int *initial, int initialSize)
{
    if (UFCount(uf) == 1) {
        return initial[0];
    }

    int count[MAXPOINTS] = {0};
    for (int i = 0; i < initialSize; ++i) {
        int rootId = UFFind(uf, initial[i]);
        count[rootId]++; // ������ͨ��ͳ�Ƹ�ȾԴ
    }

    int weight = -1;
    int index = -1;
    for (int i = 0; i < UFSize(uf); ++i) {
        if (count[i] == 1) { // ��ȾԴֻ��1������ͨ��
            int w = UFWeight(uf, i);
            if (w > weight) { // �ҵ�Ȩ�أ���ͨ�ڵ㣩������ͨ��
                weight = w;
                index = i;
            }
        }
    }

    if (index != -1) { // �ҵ���ͨ��
        for (int i = 0; i < initialSize; ++i) {
            int rootId = UFFind(uf, initial[i]);
            if (rootId == index) { // �ٴӸ�ȾԴ�ڵ����ҵ�������ͨ��Ľڵ㣬Ȼ�󷵻ظ�ȾԴ�������ɡ�
                return initial[i];
            }
        }
    }

    return initial[0]; // ����Ҳ�������Ҫ�����ͨ����ôɾ���κ�һ���ڵ㶼�޷�������⣬��������С��������
}

int minMalwareSpread(int **graph, int graphSize, int *graphColSize, int *initial, int initialSize)
{
    if (CheckParam(graph, graphSize, graphColSize, initial, initialSize)) {
        return -1;
    }

    if (initialSize == 1) {
        return initial[0]; // ֻ��һ���ڵ�ֱ�ӷ��ؼ��ɣ������Ƿ����á�
    }

    UF_t * uf = BuildUF(graph, graphSize, graphColSize);
    qsort(initial, initialSize, sizeof(int), InitCmp);
    return Search(uf, initial, initialSize);
}


