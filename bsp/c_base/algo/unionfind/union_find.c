/*���鼯��Disjoint set����Union-find set����һ������
����Ҫ�漰���������������ֱ�Ϊ��
�ϲ���Union�������������ཻ�ļ��Ϻϲ�Ϊһ�����ϡ�
��ѯ��Find������ѯ����Ԫ���Ƿ���ͬһ�������С�
(Ѱ������Ԫ�ص����Զ�����Ƿ���ͬ)

Q:
1)	��������ж��ٸ����ཻ�ļ���
2)	��Ҫ�������߿��Գ�Ϊ��ͨͼ(�������ж��ٸ� parent[i] == i;)
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
   ���Ⱥϲ�x��y���ڵļ���
   ������Ǹ�if else�ṹ���Ǿ��Եģ������������仯
   ���ǣ���ּ�ǲ���ļ������Ⱥϲ���ʵʱ�����ȡ�
*/
void uf_union1(int x, int y)
{
    x = uf_findRoot(x);  //�ҵ����Զ����
    y = uf_findRoot(y);
    if (x == y)
		return;  //����Ԫ������ͬһ������

//�����С�ļ��Ϻϲ�
//����ȴ�ļ�����ȥ
	if (rank[x] > rank[y]) {
		father[y] = x;
		rank[x] += rank[y];  //���ºϲ�������
	} else {
		if (rank[x] == rank[y]) {
			rank[y]++;
		}
		father[x] = y;
	}
}


