/*并查集（Disjoint set或者Union-find set）是一种树型
它主要涉及两个基本操作，分别为：
合并（Union）：把两个不相交的集合合并为一个集合。
查询（Find）：查询两个元素是否在同一个集合中。
(寻找两个元素的最久远祖先是否相同)

Q:
1)	计算最后有多少个不相交的集合
2)	需要多少条边可以成为连通图(即计算有多少个 parent[i] == i;)

*/
#ifndef UNION_FIND_H
#define UNION_FIND_H
#define UF_MAX 1024
struct UnionFind {
	int root[UF_MAX];
	int rank[UF_MAX];
};

void uf_init(struct UnionFind *uf)
{
	memset(uf, 0, sizeof(int) * UF_MAX);
	for (int i = 0; i < UF_MAX; i++) {
		uf->root[i] = i;
	}
}

/*find root of the node*/
int uf_findRoot(struct UnionFind* obj, int x)
{
    if (x != obj->root[x]) {//x有root
        obj->rank[obj->root[x]] += obj->rank[x];
        obj->root[x] = uf_findRoot(obj, obj->root[x]);
    }

/*最终找到祖宗为自己的家伙*/
    return obj->root[x];
}


/* if in one union*/
bool uf_isOneUnion(struct UnionFind* obj, int x, int y)
{
	 return uf_findRoot(obj, x) == uf_findRoot(obj, y);
}

#if 1
void uf_union(struct UnionFind* obj, int sun0, int sun1)
{
	int root0 = uf_findRoot(obj, sun0);
	int root1 = uf_findRoot(obj, sun1);
	if (root0 == root1)
		return;

	if (obj->rank[root0] > obj->rank[root1]) {
		obj->root[root1] = root0;
		obj->rank[root0] += obj->rank[root1];
	} else {
		if (obj->rank[root0] == obj->rank[root1]) {
			obj->rank[root1]++;
		}
		obj->root[root0] = root1;
	}
}
#else
void uf_union(struct UnionFind* obj, int i, int j)
{
    int x = uf_findRoot(obj, i), y = uf_findRoot(obj, j);
    if (obj->rank[x] <= obj->rank[y])
        obj->root[x] = y;
    else
        obj->root[y] = x;

    if (obj->rank[x] == obj->rank[y] && x!=y)
        obj->rank[y]++;
}
#endif

#endif

