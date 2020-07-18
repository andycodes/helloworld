/*
684. ��������
�Ѷ��е�82
�ڱ�������, ��ָ����һ����ͨ���޻�������ͼ��
����һ��ͼ����ͼ��һ������N���ڵ� (�ڵ�ֵ���ظ�1, 2, ..., N) ������һ�����ӵı߹��ɡ����ӵıߵ��������������1��N�м䣬�������ӵı߲����������Ѵ��ڵıߡ�
���ͼ��һ���Ա���ɵĶ�ά���顣ÿһ���ߵ�Ԫ����һ��[u, v] ������ u < v����ʾ���Ӷ���u ��v������ͼ�ıߡ�
����һ������ɾȥ�ıߣ�ʹ�ý��ͼ��һ������N���ڵ����������ж���𰸣��򷵻ض�ά�����������ֵıߡ��𰸱� [u, v] Ӧ������ͬ�ĸ�ʽ u < v��
ʾ�� 1��
����: [[1,2], [1,3], [2,3]]
���: [2,3]
����: ����������ͼΪ:
  1
 / \
2 - 3

*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 /**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*
�������еı�edges������ͨ�Ľ�����ͬһ�����ϣ�
�γ�һ����ͨ����GG��
�ڱ����Ĺ����У�
�����(a, b)(a,b)���������aa, bb�Ѿ�����ͬһ��ͨ������
��(a, b)(a,b)���Ǹ���ͨ����������ߡ�

��ǰ�����������ǿ��Ա���ÿһ���ߣ�
��������������ʱ���������ѯ������
���������������ڵ���֮���ڵ���ͬ��
����������������ͬһ������
�ʸ�����Ϊ��ǰ���������Ҫ�ıߡ���

�����һ�����Ǳ�Ҫ�ģ�
�Ǵ�������������������Ų�ͬ������
��ʱ���ǽ����Ǻϲ�Ϊͬһ�á�

*/
int* findRedundantConnection(int** edges, int edgesSize,
int* edgesColSize, int* returnSize){
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf);

	for (int i = 0; i < edgesSize; i++) {
		if (uf_isOneUnion(uf, edges[i][0], edges[i][1])) {
			res[0] = edges[i][0];
			res[1] = edges[i][1];
		} else {
			uf_union(uf, edges[i][0], edges[i][1]);
		}
	}

	return res;
}

/*
1319. ��ͨ����Ĳ�������
�Ѷ��е�15
����̫�����½� n ̨��������ӳ�һ�����磬������ı�Ŵ� 0 �� n-1�������� connections ��ʾ������ connections[i] = [a, b] �����˼���� a �� b��
�����е��κ�һ̨�����������ͨ������ֱ�ӻ��߼�ӷ���ͬһ����������������һ̨�������
����������������ĳ�ʼ���� connections������԰ο�������ֱ̨�������֮������£�����������һ��δֱ���ļ������������㲢����ʹ���м��������ͨ��������ٲ�����������������ܣ��򷵻� -1 ��

ʾ�� 1��

���룺n = 4, connections = [[0,1],[0,2],[1,2]]
�����1
���ͣ����¼���� 1 �� 2 ֮������£��������嵽����� 1 �� 3 �ϡ�
ʾ�� 2��

���룺n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
�����2
ʾ�� 3��
���룺n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
�����-1
���ͣ������������㡣
ʾ�� 4��
���룺n = 5, connections = [[0,1],[0,2],[3,4],[2,3]]
�����0

*/

/*
1)�������������Ϊ m ʱ������������Ҫ m - 1 �����²��ܽ����ǽ�������

���������� connections �ĳ���С�� n - 1�����ǿ���ֱ�ӷ��� -1

�Ƚ� n - 1 �� len(connections)��

���ǰ�ߴ��ں��ߣ���ôһ���޽⣬���� -1��

���ǰ��С�ڵ��ں��ߣ���ô����ͳ�Ƴ�ͼ�е���ͨ������ k������ k - 1��

ͳ��ͼ����ͨ�������ķ����кܶ࣬���ǽ���������������Ͳ��鼯���ַ�����

*/
int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
	if (n <= 0 || connections == NULL || connectionsSize <= 0 || connectionsColSize == NULL)
		return 0;

	struct UnionFind duf;
	struct UnionFind *uf = &duf;

	uf_init(uf, n);

	int cnt = 0;// �������������
	int part = n;//��ͨ����
	for (int i = 0; i < connectionsSize; i++) {
		// �������Ѿ���ͨ������Ҫ�������
		if (uf_isOneUnion(uf, connections[i][0], connections[i][1])) {
			cnt++;
		}else {
			uf_union(uf, connections[i][0], connections[i][1]);
			part--;
		}
	}

	if (connectionsSize < n -1)
		return -1;
	part--;
	return cnt >=  part? part : -1;
}


/*
������ 17.07. Ӥ������
�Ѷ��е�0
ÿ�꣬�������ṫ��һ��������Ӥ�����ֺ����ǳ���
��Ƶ�ʣ�Ҳ����ͬ��Ӥ������������Щ�����ж���ƴ����
���磬John �� Jon ����������ͬ�����֣�������������������
�������������������б�һ�������ּ���Ӧ��Ƶ�ʣ�
��һ���Ǳ�����ͬ�����ֶԡ����һ���㷨��ӡ��ÿ��
��ʵ���ֵ�ʵ��Ƶ�ʡ�ע�⣬��� John �� Jon ����ͬ�ģ�
���� Jon �� Johnny ��ͬ���� John �� Johnny Ҳ��ͬ���������д���
�ͶԳ��ԡ�
�ڽ���б��У�ѡ���ֵ�����С��������Ϊ��ʵ���֡�
ʾ����
���룺
names = ["John(15)","Jon(12)","Chris(13)","Kris(4)","Christopher(19)"],
synonyms = ["(Jon,John)","(John,Johnny)","(Chris,Kris)","(Chris,Christopher)"]
�����["John(27)","Chris(36)"]

*/
#define STR_LEN     50
typedef struct _info_st
{
	char name[STR_LEN];
	char *root;
	int cnt;
}info_st;
char** trulyMostPopular(char** names, int namesSize,
	char** synonyms, int synonymsSize, int* returnSize)
{
	*returnSize = 0;

	if(namesSize == 0) {
		return NULL;
	}

	info_st *info = (info_st *)calloc(namesSize, sizeof(info_st));
	struct HashTable dht;
	struct HashTable *ht = &dht;
	HashInit(ht, namesSize, hashequal_str, hashcode_str);
	for(int i = 0; i < namesSize; i++) {
		char *iterator;
		char *p;
		iterator = strtok_r(names[i], "(", &p);
		strcpy(info[i].name, iterator);

		iterator = strtok_r(NULL, ")", &p);
		info[i].cnt = atoi(iterator);
		info[i].root = info[i].name;

		struct DataEntry cmpEntry;
		cmpEntry.key = info[i].name;
		struct DataEntry *find = hashFind(ht, &cmpEntry);
		if (find == NULL) {
			struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
			entry->key = strdup(info[i].name);
			entry->value = i;//���
			HashAdd(ht, &entry->node);
		}

	}

	printf("\n");

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, namesSize);

	for(int i = 0; i < synonymsSize; i++) {
		int slen = strlen(synonyms[i]);
		char synname[2][STR_LEN];
		memset(synname, 0, sizeof(synname));
		char *iterator;
		char *p;
		iterator = strtok_r(synonyms[i], ",", &p);
		strcpy(synname[0],iterator + 1);
		strcpy(synname[1], p);
		int len = strlen(synname[1]);
		synname[1][len - 1] = '\0';

	        printf("%s; %s ", synname[0], synname[1]);

	        int id[2];
	        for(int j = 0; j < 2; j++) {
			struct DataEntry cmpEntry;
			cmpEntry.key = synname[j];
			struct DataEntry *findptr = hashFind(ht, &cmpEntry);
			id[j] = findptr->value;
	        }

	        printf("%d; %d\n", id[0], id[1]);

		uf_union(uf, id[0], id[1]);
	}

	int rsize = 0;
	for(int i = 0; i < namesSize; i++) {
		int root = uf_findRoot(uf, i);
		if(strcmp(info[i].name, info[root].root) < 0) {
			info[root].root = info[i].name;
		}

		if(i == root) {
			rsize++;
		} else {
			info[root].cnt += info[i].cnt;
		}
	}

	char **ret = (char **)calloc(rsize, sizeof(char *));
	for (int i = 0; i < namesSize; i++) {
		if(i == uf_findRoot(uf, i)) {
			ret[*returnSize] = (char *)calloc(1024, sizeof(char));
			sprintf(ret[*returnSize], "%s(%d)", info[i].root,  info[i].cnt);
			printf("%s ", ret[*returnSize]);
			(*returnSize)++;
		}
	}
	return ret;
}


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
        for (int i = 0; i < 4; ++i) {// 4 bit
	    	if ((patterns[grid[x][y]] & (1 << i)) == 0)
				continue;

		//each set bit
		int sx = x + dirs[i][0];
		int sy = y + dirs[i][1];
		if (sx >= 0 && sx < row && sy >= 0 && sy < col &&
			(patterns[grid[sx][sy]] & (1 << ((i + 2) % 4)))) {
			uf_union(uf, dimenMap(x, y, col), dimenMap(sx, sy, col));
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
1101. �˴���ʶ������ʱ��
�Ѷ��е�7
��һ���罻Ȧ�ӵ��У��� N ���ˡ�ÿ���˶���һ���� 0 ��
N-1 Ψһ�� id ��š�
������һ����־�б� logs������ÿ����¼������һ���Ǹ�����
��ʱ������Լ����������˵Ĳ�ͬ id��logs[i] = [timestamp, id_A, id_B]��
ÿ����־��ʶ�������˳�Ϊ���ѵ�ʱ�䣬�������໥�ģ���
�� A �� B �Ǻ��ѣ���ô B �� A Ҳ�Ǻ��ѡ�
��� A �� B �ĺ��ѣ����� A �� B �ĺ��ѵĺ��ѣ���ô�Ϳ�����
Ϊ A Ҳ�� B ��ʶ��
����Ȧ����������֮�䶼��ʶ������ʱ�䡣����Ҳ�������
ʱ�䣬�ͷ��� -1 ��

ʾ����
���룺logs = [[20190101,0,1],[20190104,3,4],[20190107,2,3],[20190211,1,5],
[20190224,2,4],[20190301,0,3],[20190312,1,2],[20190322,4,5]], N = 6
�����20190301
���ͣ�
��һ�νύ������ timestamp = 20190101��0 �� 1 ��Ϊ���ѣ��罻����Ȧ���� [0,1], [2], [3], [4], [5]��
�ڶ��νύ������ timestamp = 20190104��3 �� 4 ��Ϊ���ѣ��罻����Ȧ���� [0,1], [2], [3,4], [5].
�����νύ������ timestamp = 20190107��2 �� 3 ��Ϊ���ѣ��罻����Ȧ���� [0,1], [2,3,4], [5].
���Ĵνύ������ timestamp = 20190211��1 �� 5 ��Ϊ���ѣ��罻����Ȧ���� [0,1,5], [2,3,4].
����νύ������ timestamp = 20190224��2 �� 4 �Ѿ��Ǻ����ˡ�
�����νύ������ timestamp = 20190301��0 �� 3 ��Ϊ���ѣ���Ҷ�������ʶ�ˡ�

*/
/*
���εĲ��鼯���⡣

�������⣺

1.ȫ����ʶ������ʱ��=������A��ʶ������ʱ�䣬����B����ʶ������ʱ�䣬AB��ʶ������ʱ�䣩�е����ʱ��

2.�������A�ͼ���BΪͬһ���ϣ����¼���log��Ч

3.������ѵ��ǣ���α������ڳٵ�һ��log�ȴٳ�A��B�ϲ�������Ԥ�����������кϲ����������緢��

*/
int uf_union(struct UnionFind* uf, int** logs, int logsSize)
{
	for (int i = 0; i < logsSize; i++) {
		int root0 = uf_findRoot(uf, logs[i][1]);
		int root1 = uf_findRoot(uf, logs[i][2]);
		if (root0 == root1)
			continue;

		int timemax = fmax(fmax(uf->timestamp[root0], uf->timestamp[root1]), logs[i][0]);

		if (uf->rank[root0] < uf->rank[root1]) {
			uf->root[root0] = root1;
			uf->timestamp[root1] = timemax;
		} else if (uf->rank[root0] > uf->rank[root1]) {
			uf->root[root1] = root0;
			uf->timestamp[root0] = timemax;
		} else {
			uf->root[root0] = root1;
			uf->rank[root1]++;
			uf->timestamp[root1] = timemax;
		}
	/*
	N����ֻ��ҪN-1�κϲ�������ʶ�����ˣ�
	�ж�����ΪN=1 ˵��ȫ��ʶ�ˡ�
	*/
		uf->unionCnt--;
		if (uf->unionCnt == 1) {
			return logs[i][0];
		}
	}

	return -1;
}

/*
ȫ����ʶ������ʱ��=��
����A��ʶ������ʱ�䣬
����B����ʶ������ʱ�䣬
AB��ʶ������ʱ�䣩
�е����ʱ��
*/
int earliestAcq(int** logs, int logsSize, int* logsColSize, int N)
{
	struct UnionFind duf;
	struct UnionFind *uf = &duf;

	uf_init(uf, N);
	qsort(logs, logsSize, sizeof(logs[0]), cmp_point);
	return uf_union(uf, logs, logsSize);
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
947. �Ƴ�����ͬ�л�ͬ��ʯͷ
�Ѷ��е�65
���ǽ�ʯͷ�����ڶ�άƽ���е�һЩ����������ϡ�ÿ������������ֻ����һ��ʯͷ��
ÿ�� move ���������Ƴ�һ�������л�������������ʯͷ���ڵ�ʯͷ��
�������һ���㷨�����������ִ�ж��ٴ� move ������

ʾ�� 1��
���룺stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
�����5
ʾ�� 2��
���룺stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
�����3

*/
int removeStones(int** stones, int stonesSize, int* stonesColSize)
{
        int n = stonesSize;
        if(!n) return 0;

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf->root = (int *)calloc(n, sizeof(int));
	uf->rank = (int *)calloc(n, sizeof(int));
	uf->cnt = n;
	uf_init(uf);

        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]){
                        uf_union(uf, i,j);
                    }
            }
        }
        return n -uf->cnt;
}


