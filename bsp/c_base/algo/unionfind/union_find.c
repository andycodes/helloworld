/*���鼯��Disjoint set����Union-find set����һ������
����Ҫ�漰���������������ֱ�Ϊ��
�ϲ���Union�������������ཻ�ļ��Ϻϲ�Ϊһ�����ϡ�
��ѯ��Find������ѯ����Ԫ���Ƿ���ͬһ�������С�
(Ѱ������Ԫ�ص����Զ�����Ƿ���ͬ)

Q:
1)	��������ж��ٸ����ཻ�ļ���
2)	��Ҫ�������߿��Գ�Ϊ��ͨͼ(�������ж��ٸ� parent[i] == i;)

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
    if (x != obj->root[x]) {//x��root
        obj->rank[obj->root[x]] += obj->rank[x];
        obj->root[x] = uf_findRoot(obj, obj->root[x]);
    }

/*�����ҵ�����Ϊ�Լ��ļһ�*/
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

