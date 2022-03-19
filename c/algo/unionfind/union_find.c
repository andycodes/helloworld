/*
连通器个数
*/
#ifndef UNION_FIND_H
#define UNION_FIND_H

struct UnionFind {
	int edgeCnt;
	int *root;
	int *rank;
};

void uf_init(struct UnionFind *uf, size_t size)
{
	uf->edgeCnt = size;
	uf->root = (int *)calloc(size, sizeof(int));
	uf->rank = (int *)calloc(size, sizeof(int));
	memset(uf->rank, 0, sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		uf->root[i] = i;
	}
}

int uf_findRoot(struct UnionFind* uf, int sun)
{
	if (sun == uf->root[sun]) {
		return sun;
	}

        return uf->root[sun] = uf_findRoot(uf, uf->root[sun]);
}

bool uf_isOneUnion(struct UnionFind* uf, int sun0, int sun1)
{
	 return uf_findRoot(uf, sun0) == uf_findRoot(uf, sun1);
}

/*Rank[i]表示以 i 为根节点的集合的层数，即树的高度。
对于两个集合来说，如果两个集合的层数不一样，
我们只需要把层数小的集合的根元素的父亲节点指
向另一个集合的根元素就好了，而且最后合并出
来的集合的层数是不变的。
合并后集合层数唯一会变的情况，就是两个集合的
层数一模一样时。我们可以这样去理解，假设两个
集合都只有一个元素，那么这两个集合的层数
都为一层，层数相同时，此时谁的根节点的父亲
节点指向另一个根节点都无所谓了，
但是这样合并后的集合层数要比原来多了一层。
（原来两个集合都为一层，合并后的集合就变
成两层了）
*/
void uf_union(struct UnionFind* uf, int sun0, int sun1)
{
	int root0 = uf_findRoot(uf, sun0);
	int root1 = uf_findRoot(uf, sun1);
	if (root0 == root1)
		return;

	if (uf->rank[root0] < uf->rank[root1]) {
		uf->root[root0] = root1;
	} else if (uf->rank[root0] > uf->rank[root1]) {
		uf->root[root1] = root0;
	} else {
		uf->root[root0] = root1;
		uf->rank[root1]++;
	}

	uf->edgeCnt--;
	if (uf->edgeCnt == 1) {
		//OK
	}
}

typedef struct {
	char name[MAX];
	int index;
	int count;
	UT_hash_handle hh;
} Hashmap;
void uf_str_union(struct UnionFind* uf, Hashmap *sun0, Hashmap *sun1)
{
	if (sun0 == NULL || sun1 == NULL) {
		return;
	}

	int root1 = uf_findRoot(uf, sun0->index);
	int root2 = uf_findRoot(uf, sun1->index);
	if (root1 == root2) {
		return;
	}
//连接边，字典序小的作为根节点
	if (strcmp(sun0->name, sun1->name) < 0) { 
		uf->root[root2] = root1;
	} else {
		uf->root[root1] = root2;
	}
}

#endif
