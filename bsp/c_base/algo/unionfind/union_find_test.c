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
    int id;
    int cnt;
}info_st;

char** trulyMostPopular(char** names, int namesSize,
char** synonyms, int synonymsSize, int* returnSize)
{
	if(namesSize == 0) {
		*returnSize = 0;
		return NULL;
	}

	info_st *info = (info_st *)calloc(namesSize, sizeof(info_st));
	HashMap * hashmap = hashmap_init(namesSize, 1);
	for(int i = 0; i < namesSize; i++) {
		char *iterator;
		char *p;
		iterator = strtok_r(names[i], "(", &p);
		strcpy(info[i].name, iterator);

		iterator = strtok_r(NULL, ")", &p);
		info[i].cnt = atoi(iterator);

		info[i].root = info[i].name;
		info[i].id = i;

		DataType hashdata;
		hashdata.key = info[i].name;
		hashdata.val = i;
		hashmap_getValue(hashmap, &hashdata);
		if (hashdata.id == -1) {
			hashmap_push(hashmap, hashdata);
		}

		printf("%d: %s, %d   ", info[i].id, info[i].name, info[i].cnt);
	}

	printf("\n");

	struct UnionFind* obj = uf_init(namesSize);

	for(int i = 0; i < synonymsSize; i++) {
	        int slen = strlen(synonyms[i]);
	        char tmps[2][STR_LEN];

		char *iterator;
		char *p;
		iterator = strtok_r(synonyms[i], ",", &p);
		strcpy(tmps[0],iterator + 1);

		strcpy(tmps[1], p);
		int len = strlen(tmps[1]);
		tmps[1][len - 1] = '\0';

	        printf("%s; %s ", tmps[0], tmps[1]);

	        int id[2];
	        bool find = true;
	        for(int j = 0; j < 2; j++) {
			DataType hashdata;
			hashdata.key = tmps[j];
			hashmap_getValue(hashmap, &hashdata);
			if (hashdata.id == -1) {
				find = false;
				break;
			}

			id[j] = hashdata.val;
	        }

	        if(find == false)
	        {
	            continue;
	        }

	        printf("%d; %d\n", id[0], id[1]);

		uf_union(obj, id[0], id[1]);
	}


    	printf("\n");

	int rsize = 0;
	for(int i = 0; i < namesSize; i++) {
		int ff = uf_findRoot(obj, i);
		if(strcmp(info[i].name, info[ff].root) < 0) {
			info[ff].root = info[i].name;
		}

		if(i == ff) {
			rsize++;
			continue;
		} else {
			info[ff].cnt += info[i].cnt;
		}
	}

	char **ret = (char **)calloc(rsize, sizeof(char *));
	int rid = 0;
	for (int i = 0; i < namesSize; i++) {
		if(i == uf_findRoot(obj, i)) {
			ret[rid] = info[i].root;
			char tmp[STR_LEN] = {{'\0'}};
			sprintf(tmp, "(%d)", info[i].cnt);
			strcat(ret[rid], tmp);
			printf("%s    ", ret[rid]);
			rid++;
		}
	}
	*returnSize = rsize;
	return ret;
}

/*
1202. �����ַ����е�Ԫ��
����һ���ַ��� s���Լ����ַ����е�һЩ�������ԡ����� pairs������ pairs[i] = [a, b] ��ʾ�ַ����е�������������Ŵ� 0 ��ʼ����

����� �����ν��� �� pairs ������һ�����������ַ���

�����ھ������ɴν�����s ���Ա�ɵİ��ֵ�����С���ַ�����



ʾ�� 1:

���룺s = "dcab", pairs = [[0,3],[1,2]]
�����"bacd"
���ͣ�
���� s[0] �� s[3], s = "bcad"
���� s[1] �� s[2], s = "bacd"
ʾ�� 2��

���룺s = "dcab", pairs = [[0,3],[1,2],[0,2]]
�����"abcd"
���ͣ�
���� s[0] �� s[3], s = "bcad"
���� s[0] �� s[2], s = "acbd"
���� s[1] �� s[2], s = "abcd"
*/
char arrayblk[10001][10001];
//int colsize[10001];
//int scol[10001];
char * smallestStringWithSwaps(char * s, int** pairs, int pairsSize, int* pairsColSize)
{
	if (s == NULL || pairs == NULL || pairsSize <= 0 || pairsColSize == NULL) {
		return s;
	}

	size_t ufSize = strlen(s);
	struct UnionFind *uf =  uf_init(ufSize);
	for (int i = 0; i < pairsSize; i++) {
		uf_union(uf, pairs[i][0], pairs[i][1]);
	}

	struct HashTable ht;
	int ret = HashInit(&ht, ufSize, hashequal_int, hashcode_int);
	for (int i = 0; i < ufSize; i++) {
		struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		entry->key = uf_findRoot(uf, i);
		entry->value = s[i];
		HashAdd(&ht, &entry->node);
	}

	//hashPrint(&ht);
	memset(arrayblk, 0, sizeof(arrayblk));
	int *colsize = (int *)calloc(10001, sizeof(int));
	//memset(colsize, 0, sizeof(colsize));
	for (int i = 0; i < ht.bktSize; i++) {
	    struct Node *node;
	    LIST_FOR_EACH(node, &ht.bkts[i]) {
		struct DataEntry *getEntry;
		getEntry = NODE_ENTRY(node, struct DataEntry, node);
		arrayblk[i][colsize[i]] = getEntry->value;
		colsize[i]++;
	    }
	}

	for (int i = 0; i < ufSize; i++) {
		qsort(arrayblk[i], colsize[i], sizeof(arrayblk[i][0]), cmp_char);
	}
	int *scol = (int *)calloc(10001, sizeof(int));
	//memset(scol, 0, sizeof(scol));
	int i = 0;
	char *res = strdup(s);
	while(s[i] != '\0') {
		int hashkey = uf_findRoot(uf, i);
		unsigned int bid = hashGetBlkid_int(&ht, hashkey) ;
		int col = scol[bid];
		res[i] = arrayblk[bid][col];
		scol[bid]++;
		i++;
	}

	return res;
}

/*
1391. ����������Ƿ������Ч·��
����һ�� m x n ������ grid���������ÿ����Ԫ������һ���ֵ���grid[i][j] �Ľֵ������ǣ�

1 ��ʾ������Ԫ����ҵ�Ԫ��Ľֵ���
2 ��ʾ�����ϵ�Ԫ����µ�Ԫ��Ľֵ���
3 ��ʾ������Ԫ����µ�Ԫ��Ľֵ���
4 ��ʾ�����ҵ�Ԫ����µ�Ԫ��Ľֵ���
5 ��ʾ������Ԫ����ϵ�Ԫ��Ľֵ���
6 ��ʾ�����ҵ�Ԫ����ϵ�Ԫ��Ľֵ���

*/

int patterns[7] = {0, 0b1010, 0b0101, 0b1100, 0b0110, 0b1001, 0b0011};
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dimenMap(int x, int y, int colSize)
{
	return x * colSize+ y;
}

void hander(struct UnionFind* uf, int** grid, int row, int col, int x, int y)
{
            int pattern = patterns[grid[x][y]];
            for (int i = 0; i < 4; ++i) {
                if (pattern & (1 << i)) {
                    int sx = x + dirs[i][0];
                    int sy = y + dirs[i][1];
                    if (sx >= 0 && sx < row && sy >= 0 && sy < col && (patterns[grid[sx][sy]] & (1 << ((i + 2) % 4)))) {
                        uf_union(uf, dimenMap(x, y, col), dimenMap(sx, sy, col));
                    }
                }
            }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = gridColSize[0];

	struct UnionFind* uf = uf_init(row * col);

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
��һ���罻Ȧ�ӵ��У��� N ���ˡ�ÿ���˶���һ���� 0 �� N-1 Ψһ�� id ��š�
������һ����־�б� logs������ÿ����¼������һ���Ǹ�������ʱ������Լ����������˵Ĳ�ͬ id��logs[i] = [timestamp, id_A, id_B]��
ÿ����־��ʶ�������˳�Ϊ���ѵ�ʱ�䣬�������໥�ģ���� A �� B �Ǻ��ѣ���ô B �� A Ҳ�Ǻ��ѡ�
��� A �� B �ĺ��ѣ����� A �� B �ĺ��ѵĺ��ѣ���ô�Ϳ�����Ϊ A Ҳ�� B ��ʶ��
����Ȧ����������֮�䶼��ʶ������ʱ�䡣����Ҳ�������ʱ�䣬�ͷ��� -1 ��

ʾ����
���룺logs = [[20190101,0,1],[20190104,3,4],[20190107,2,3],[20190211,1,5],[20190224,2,4],[20190301,0,3],[20190312,1,2],[20190322,4,5]], N = 6
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
int find(int *fa, int x) {
    if(fa[x] == x) {
        return fa[x];
    }

    fa[x] = find(fa, fa[x]);
    return fa[x];
}

void join(int *fa, int x, int y) {
    int xx = find(fa, x);
    int yy = find(fa, y);

    if(xx == yy) {
        return;
    }

    if(xx < yy) {
        fa[yy] = xx;
    } else {
        fa[xx] = yy;
    }
}

int compare(const void *a, const void *b) {
    return (*(int **)a)[0] - (*(int **)b)[0];
}

//���㷨˼·������+���鼯��ȫ����ʶ������ʱ��=������A��ʶ������ʱ�䣬����B����ʶ������ʱ�䣬AB��ʶ������ʱ�䣩�е����ʱ��
int earliestAcq(int** logs, int logsSize, int* logsColSize, int N)
{
    int *fa  = (int *)calloc(N, sizeof(int));
    int *times  = (int *)calloc(N, sizeof(int));

    for(int i = 0; i < N; i++) {
        fa[i] = i;
        times[i] = -1;
    }

    //����󣬴�ʹ���Ϻϲ���ʱ�価�緢�����������кϲ���������Ϊ�Ѿ���һ���������Ա�����
    qsort(logs, logsSize, sizeof(int *), compare);

	int cnt = N;
    for(int i = 0; i < logsSize; i++) {
        int x = logs[i][1];
        int y = logs[i][2];

        int xx = find(fa, x);
        int yy = find(fa, y);

        if(xx == yy) {
            continue;
        }

        int timex = times[xx];
        int timey = times[yy];
        int timexy = logs[i][0];

        int time = fmax(timex, fmax(timey, timexy));

        //ʵ��join�Ĺ��ܶ���ֱ�ӵ��ýӿ�
        if(xx < yy) {
            fa[yy] = xx;
            times[xx] = time;
        } else {
            fa[xx] = yy;
            times[yy] = time;
        }
// N����ֻ��ҪN-1�κϲ�������ʶ�����ˣ��ж�����ΪN=1 ˵��ȫ��ʶ�ˡ�
	cnt--;
	if (cnt == 1) {
		return logs[i][0];
	}
    }

	return -1;
}

/*
1135. ��ͳɱ���ͨ���г���
�Ѷ��е�23
����һ�����Ǹ����л����滮�ߣ���ͼ���� N �����У����ǰ��� 1 �� N �Ĵ����š�
����һЩ�����ӵ�ѡ�� conections������ÿ��ѡ�� conections[i] = [city1, city2, cost] ��ʾ������ city1 �ͳ��� city2 ������Ҫ�ĳɱ�����������˫��ģ�Ҳ����˵���� city1 �ͳ��� city2 ����Ҳͬ����ζ�ų��� city2 �ͳ��� city1 ��������
����ʹ��ÿ�Գ��м䶼���ڽ�����������һ�����ͨ·�������ܳ���Ϊ 1 �ģ���С�ɱ�������С�ɱ�Ӧ��������ȫ�����Ӵ��۵��ۺϡ����������֪�����޷���ɸ������������㷵�� -1��

ʾ�� 1��

���룺N = 3, conections = [[1,2,5],[1,3,6],[2,3,1]]
�����6
���ͣ�
ѡ������ 2 ���߶������������г��У����Ǵ���ѡȡ�ɱ���С�� 2 ����

*/

/*
Ԥ��֪ʶ��С������ͼ����������һ�ú��������еĶ�����޻���ͨ��ͼ��һ����Ȩͼ����С�������� MST �� ������һ��Ȩֵ���������бߵ�Ȩֵ֮�ͣ���С�������������鼯���鼯��һ�����͵����ݽṹ�����ڴ���һЩ���ཻ���ϵĺϲ�����ѯ���⡣������ʹ������ɭ������ʾ������һ��kruskal �㷨˼·�������⣬���ǿ��԰� N �����п��� N �����㣬�����������еĳɱ� cost ���Ƕ�Ӧ��Ȩ�أ���Ҫ�����������г��е���С�ɱ�������Ȼ������һ����׼����С���������������ǽ��ܵ�һ�־����㷨�� kruskal �㷨����Ȼ������Ҫ����С�ɱ�����ô���Կ϶��������ͼû�л�������л��Ļ�������ζ�����ɾ��һ����ʹ�óɱ���С�������㷨���ǻ���������ԣ����ձߵ�Ȩ��˳�򣨴�С���󣩴������еıߣ����߼��뵽��С�������У�����ı߲������Ѿ�����ı߹��ɻ���ֱ�����к��� N - 1 ����Ϊֹ����Щ�߻���һƬɭ�ֱ��һ���������������ͼ����С�����������ߣ�LeetCode-Solution���ӣ�https://leetcode-cn.com/problems/connecting-cities-with-minimum-cost/solution/zui-di-cheng-ben-lian-tong-suo-you-cheng-shi-by-le/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
int minimumCost(int N, int** connections, int connectionsSize, int* connectionsColSize)
{
	qsort(connections, connectionsSize, sizeof(connections[0]), cmp_point);
	int cost = 0;

	struct UnionFind* uf = uf_init(N + 1);
	for (int i = 0; i < connectionsSize; i++) {
		if (!uf_isOneUnion(uf, connections[i][0], connections[i][1])) {
			uf_union(uf, connections[i][0], connections[i][1]);
			cost += connections[i][2];
		}
	}

	int rooCnt = 0;
	for (int i = 1; i <= N; i++) {
		if (uf->father[i] == i) {
			if (++rooCnt > 1) {
				return -1;
			}
		}
	}

	return cost;
}

/*
1102. �÷���ߵ�·��
BFS
*/

#define min(a,b) (a) < (b) ? (a) : (b)
int direction[2][4] = {{1,-1,0,0},{0,0,1,-1}};
typedef struct {
    int x;
    int y;
    int value;
} Node;

int NodeCmp (const void *p1, const void *p2)
{
    return (((Node *)p2)->value - ((Node*)p1)->value);
}

int FindRoot (int root, int *parent) {
    int son,tmp;
    son = root;
    while (root != parent[root]) {
        root = parent[root];
    }
    while (son != root) {
        tmp = parent[son];
        parent[son] = root;
        son = tmp;
    }
    return root;
}

void Union(int x, int y, int *parent)
{
    int rootX, rootY;
    rootX = FindRoot(x, parent);
    rootY = FindRoot(y, parent);
    if (rootX == rootY) {
        return;
    } else if (rootX < rootY) {        //��Ϊ�ṹ������������������Žϴ��ֵ������
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
    }
}
int maximumMinimumPath(int** A, int ASize, int* AColSize){
    int matrixSize = ASize * (*AColSize);
    int trace[matrixSize];
    int parent[matrixSize];
    Node nodeArray[matrixSize];
    memset(trace, 0, sizeof(trace));
    memset(parent, 0, sizeof(parent));
    memset(nodeArray,0,sizeof(nodeArray));
    int count = 0;
    for (int i = 0; i < ASize; i++) {
        for (int j = 0; j < (*AColSize); j++) {
            parent[count] = i * (*AColSize) + j;
            nodeArray[count].x = i;
            nodeArray[count].y = j;
            nodeArray[count].value = A[i][j];
            count++;
        }
    }
    qsort(nodeArray, matrixSize, sizeof(Node), NodeCmp);
    count = 0;
    int ans = min(A[0][0], A[ASize - 1][*AColSize - 1]);
    while (FindRoot(0, parent) != FindRoot(matrixSize - 1, parent)) {
        int x = nodeArray[count].x;
        int y = nodeArray[count].y;
        int index = x * (*AColSize) + y;
        trace[index] = 1;                          //��Ǹõ㱻���뵱ǰ·����
        ans = min(ans, nodeArray[count].value);
        for (int i = 0; i < 4; i++)
        {
            int nx, ny;
            nx = x + direction[0][i];
            ny = y + direction[1][i];
            int indexNew = nx * (*AColSize) + ny;
            if (nx < ASize && nx > -1 && ny < (*AColSize) && ny > -1 && trace[indexNew] == 1) {
                Union(index, indexNew, parent);
            }
        }
        count++;
    }
    return ans;
}
