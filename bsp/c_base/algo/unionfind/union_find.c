/*并查集（Disjoint set或者Union-find set）是一种树型
它主要涉及两个基本操作，分别为：
合并（Union）：把两个不相交的集合合并为一个集合。
查询（Find）：查询两个元素是否在同一个集合中。
(寻找两个元素的最久远祖先是否相同)

Q:
1)	计算最后有多少个不相交的集合
2)	需要多少条边可以成为连通图(即计算有多少个 parent[i] == i;)
*/

struct UnionFind {
	int *father;
	int *rank;
};

struct UnionFind* uf_init(int size)
{
	struct UnionFind* obj = (struct UnionFind*)malloc(sizeof(struct UnionFind));
	obj->father = (int *)calloc(size, sizeof(int));
	obj->rank = (int *)calloc(size, sizeof(int));
	for (int i = 0; i < size; ++i) {
		obj->father[i] = i;//init root is self
		obj->rank[i] = 0;
	}

	return obj;
}


/*find root of the node*/
int uf_findRoot(struct UnionFind* obj, int x)
{
    if (x != obj->father[x]) {//x有father
        obj->rank[obj->father[x]] += obj->rank[x];
        obj->father[x] = uf_findRoot(obj, obj->father[x]);
    }

/*最终找到祖宗为自己的家伙*/
    return obj->father[x];
}


/* if in one union*/
bool uf_isOneUnion(struct UnionFind* obj, int x, int y)
{
	 return uf_findRoot(obj, x) == uf_findRoot(obj, y);
}


void uf_union(struct UnionFind* obj, int i, int j)
{
    int x = uf_findRoot(obj, i), y = uf_findRoot(obj, j);
    if (obj->rank[x] <= obj->rank[y])
        obj->father[x] = y;
    else
        obj->father[y] = x;

    if (obj->rank[x] == obj->rank[y] && x!=y)
        obj->rank[y]++;
}


/*
   按秩合并x和y所在的集合
   下面的那个if else结构不是绝对的，具体根据情况变化
   但是，宗旨是不变的即，按秩合并，实时更新秩。
*/
void uf_union1(int x, int y)
{
    x = uf_findRoot(x);  //找到最久远祖先
    y = uf_findRoot(y);
    if (x == y)
		return;  //两个元素属于同一个集合

//把深度小的集合合并
//到深度大的集合中去
	if (rank[x] > rank[y]) {
		father[y] = x;
		rank[x] += rank[y];  //更新合并后的深度
	} else {
		if (rank[x] == rank[y]) {
			rank[y]++;
		}
		father[x] = y;
	}
}


