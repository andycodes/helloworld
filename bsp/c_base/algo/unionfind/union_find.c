/*
��ͨ������
*/
#ifndef UNION_FIND_H
#define UNION_FIND_H

struct UnionFind {
	int cnt;
	int *root;
	int *rank;
};

void uf_init(struct UnionFind *uf, size_t size)
{
	uf->cnt = size;
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

/*Rank[i]��ʾ�� i Ϊ���ڵ�ļ��ϵĲ����������ĸ߶ȡ�*/
/*
��������������˵������������ϵĲ�����һ����
����ֻ��Ҫ�Ѳ���С�ļ��ϵĸ�Ԫ�صĸ��׽ڵ�ָ����һ��
���ϵĸ�Ԫ�ؾͺ��ˣ��������ϲ������ļ��ϵĲ����ǲ���ġ�
�ϲ��󼯺ϲ���Ψһ��������������������ϵĲ���һģһ��ʱ��
���ǿ�������ȥ��⣬�����������϶�ֻ��һ��Ԫ�أ�
��ô���������ϵĲ�����Ϊһ�㣬������ͬʱ��
��ʱ˭�ĸ��ڵ�ĸ��׽ڵ�ָ����һ�����ڵ㶼����ν�ˣ�
���������ϲ���ļ��ϲ���Ҫ��ԭ������һ�㡣
��ԭ���������϶�Ϊһ�㣬�ϲ���ļ��Ͼͱ�������ˣ�
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
}
#endif
