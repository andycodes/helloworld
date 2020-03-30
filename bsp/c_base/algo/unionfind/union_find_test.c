/*
684. 冗余连接
难度中等82
在本问题中, 树指的是一个连通且无环的无向图。
输入一个图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。
结果图是一个以边组成的二维数组。每一个边的元素是一对[u, v] ，满足 u < v，表示连接顶点u 和v的无向图的边。
返回一条可以删去的边，使得结果图是一个有着N个节点的树。如果有多个答案，则返回二维数组中最后出现的边。答案边 [u, v] 应满足相同的格式 u < v。
示例 1：
输入: [[1,2], [1,3], [2,3]]
输出: [2,3]
解释: 给定的无向图为:
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
遍历所有的边edges，将连通的结点放入同一个集合，
形成一个联通分量GG。
在遍历的过程中，
如果边(a, b)(a,b)的两个结点aa, bb已经属于同一联通分量，
则(a, b)(a,b)就是该联通分量的冗余边。

如前面所述，我们可以遍历每一条边，
而遍历到该条边时我们如果查询这条边
左右两个顶点所在到树之根节点相同，
即代表两个顶点在同一棵树，
故该条边为当前情况「不必要的边」。

如果那一条边是必要的，
那代表两个顶点代表着两颗不同的树，
此时我们将他们合并为同一棵。

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
1319. 连通网络的操作次数
难度中等15
用以太网线缆将 n 台计算机连接成一个网络，计算机的编号从 0 到 n-1。线缆用 connections 表示，其中 connections[i] = [a, b] 连接了计算机 a 和 b。
网络中的任何一台计算机都可以通过网络直接或者间接访问同一个网络中其他任意一台计算机。
给你这个计算机网络的初始布线 connections，你可以拔开任意两台直连计算机之间的线缆，并用它连接一对未直连的计算机。请你计算并返回使所有计算机都连通所需的最少操作次数。如果不可能，则返回 -1 。

示例 1：

输入：n = 4, connections = [[0,1],[0,2],[1,2]]
输出：1
解释：拔下计算机 1 和 2 之间的线缆，并将它插到计算机 1 和 3 上。
示例 2：

输入：n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
输出：2
示例 3：
输入：n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
输出：-1
解释：线缆数量不足。
示例 4：
输入：n = 5, connections = [[0,1],[0,2],[3,4],[2,3]]
输出：0

*/

/*
1)当计算机的数量为 m 时，我们至少需要 m - 1 根线缆才能将它们进行连接

因此如果数组 connections 的长度小于 n - 1，我们可以直接返回 -1

比较 n - 1 和 len(connections)：

如果前者大于后者，那么一定无解，返回 -1；

如果前者小于等于后者，那么我们统计出图中的连通分量数 k，返回 k - 1。

统计图中连通分量数的方法有很多，我们介绍深度优先搜索和并查集两种方法。

*/
int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
	if (n <= 0 || connections == NULL || connectionsSize <= 0 || connectionsColSize == NULL)
		return 0;

	uf_init(n);

	int cnt = 0;// 多余的线缆数量
	int part = n;//连通分量
	for (int i = 0; i < connectionsSize; i++) {
		int x = connections[i][0];
		int y = connections[i][1];
		// 两个点已经连通，不需要这个线缆
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
面试题 17.07. 婴儿名字
难度中等0
每年，政府都会公布一万个最常见的婴儿名字和它们出现
的频率，也就是同名婴儿的数量。有些名字有多种拼法，
例如，John 和 Jon 本质上是相同的名字，但被当成了两个名字
公布出来。给定两个列表，一个是名字及对应的频率，
另一个是本质相同的名字对。设计一个算法打印出每个
真实名字的实际频率。注意，如果 John 和 Jon 是相同的，
并且 Jon 和 Johnny 相同，则 John 与 Johnny 也相同，即它们有传递
和对称性。
在结果列表中，选择字典序最小的名字作为真实名字。
示例：
输入：
names = ["John(15)","Jon(12)","Chris(13)","Kris(4)","Christopher(19)"],
synonyms = ["(Jon,John)","(John,Johnny)","(Chris,Kris)","(Chris,Christopher)"]
输出：["John(27)","Chris(36)"]

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
1202. 交换字符串中的元素
给你一个字符串 s，以及该字符串中的一些「索引对」数组 pairs，其中 pairs[i] = [a, b] 表示字符串中的两个索引（编号从 0 开始）。

你可以 任意多次交换 在 pairs 中任意一对索引处的字符。

返回在经过若干次交换后，s 可以变成的按字典序最小的字符串。



示例 1:

输入：s = "dcab", pairs = [[0,3],[1,2]]
输出："bacd"
解释：
交换 s[0] 和 s[3], s = "bcad"
交换 s[1] 和 s[2], s = "bacd"
示例 2：

输入：s = "dcab", pairs = [[0,3],[1,2],[0,2]]
输出："abcd"
解释：
交换 s[0] 和 s[3], s = "bcad"
交换 s[0] 和 s[2], s = "acbd"
交换 s[1] 和 s[2], s = "abcd"
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


