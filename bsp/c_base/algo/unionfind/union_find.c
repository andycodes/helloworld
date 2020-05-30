/*���鼯��Disjoint set����Union-find set����һ������
����Ҫ�漰���������������ֱ�Ϊ��
�ϲ���Union�������������ཻ�ļ��Ϻϲ�Ϊһ�����ϡ�
��ѯ��Find������ѯ����Ԫ���Ƿ���ͬһ�������С�
(Ѱ������Ԫ�ص����Զ�����Ƿ���ͬ)

Q:
1)	��������ж��ٸ����ཻ�ļ���
2)	��Ҫ�������߿��Գ�Ϊ��ͨͼ(�������ж��ٸ� parent[i] == i;)

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
    if (x != obj->father[x]) {//x��father
        obj->rank[obj->father[x]] += obj->rank[x];
        obj->father[x] = uf_findRoot(obj, obj->father[x]);
    }

/*�����ҵ�����Ϊ�Լ��ļһ�*/
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

