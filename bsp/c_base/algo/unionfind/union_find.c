/*并查集（Disjoint set或者Union-find set）是一种树型
它主要涉及两个基本操作，分别为：
合并（Union）：把两个不相交的集合合并为一个集合。
查询（Find）：查询两个元素是否在同一个集合中。
(寻找两个元素的最久远祖先是否相同)

Q:
1)	计算最后有多少个不相交的集合
2)	需要多少条边可以成为连通图(即计算有多少个 parent[i] == i;)

[root1][root1][sun3][sun4][root1]
*/
#ifndef UNION_FIND_H
#define UNION_FIND_H

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

#if 0
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
#else
void uf_union(struct UnionFind* obj, int x, int y)
{
	x = uf_findRoot(obj, x);
	y = uf_findRoot(obj, y);
	if (x == y)
		return;

	if (obj->rank[x] > obj->rank[y]) {
		obj->father[y] = x;
		obj->rank[x] += obj->rank[y];
	} else {
		if (obj->rank[x] == obj->rank[y]) {
			obj->rank[y]++;
		}
		obj->father[x] = y;
	}
}
#endif
#endif

