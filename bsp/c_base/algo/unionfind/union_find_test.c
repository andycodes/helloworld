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

	uf_init(MAX);
	for (int i = 0; i < edgesSize; i++) {
		if (uf_isOneUnion(edges[i][0], edges[i][1])) {
			res[0] = edges[i][0];
			res[1] = edges[i][1];
		} else {
			uf_union(edges[i][0], edges[i][1]);
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

	uf_init(n);

	int cnt = 0;// �������������
	int part = n;//��ͨ����
	for (int i = 0; i < connectionsSize; i++) {
		int x = connections[i][0];
		int y = connections[i][1];
		// �������Ѿ���ͨ������Ҫ�������
		if (uf_find(x) == uf_find(y)) {
			cnt++;
		}else {
			uf_union(x, y);
			part--;
		}
	}

	if (connectionsSize < n -1)
		return -1;

	return part - 1;
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


