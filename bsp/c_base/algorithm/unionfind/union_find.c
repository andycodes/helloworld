/*���鼯��Disjoint set����Union-find set����һ������
�����ݽṹ�������ڴ���һЩ���ཻ���ϣ�Disjoint Sets��
�ĺϲ�����ѯ���⡣
2��  ��������

���鼯��һ�ַǳ��򵥵����ݽṹ��
����Ҫ�漰���������������ֱ�Ϊ��

A�� �ϲ��������ཻ����

B�� �ж�����Ԫ���Ƿ�����ͬһ������

��������ת��ΪѰ������Ԫ�ص����Զ�����Ƿ���ͬ�����Բ��õݹ�ʵ�֡�

�ϲ���Union�������������ཻ�ļ��Ϻϲ�Ϊһ�����ϡ�
��ѯ��Find������ѯ����Ԫ���Ƿ���ͬһ�������С�


��������ж��ٸ����ཻ�ļ���
������Ҫ�������߿��Գ�Ϊ��ͨͼ
�������ж��ٸ� parent[i] == i;
*/

#define MAX 1024

int father[MAX];   /* father[x]��ʾx�ĸ��ڵ� */
int rank[MAX];     /* rank[x]��ʾx���� */

inline void uf_init(int n)
{
    for (int i = 0; i < n; ++i) {
	//���ڵ�Ϊ�Լ�
        father[i] = i;
	//��Ϊ0
	rank[i] = 0;
    }

}


/* ����xԪ�����ڵļ���,����ʱѹ��·��
�����ҵ�parentָ���Դͷ*/
int uf_find(int x)
{
    if (x != father[x])// x��������ĸ��ף���x���Ǹü��ϵ�����
    {
        rank[father[x]] += rank[x];
        //�ݹ飬���ҵ����Զ����
        //����ʱѹ��·����·���ϵ����������
        //�㶼ָ�����Զ����
        father[x] = uf_find(father[x]);//����x������ֱ���ҵ�����,����˳��·��ѹ��
    }
    return father[x];
}


/*
   ���Ⱥϲ�x��y���ڵļ���
   ������Ǹ�if else�ṹ���Ǿ��Եģ������������仯
   ���ǣ���ּ�ǲ���ļ������Ⱥϲ���ʵʱ�����ȡ�
*/
void uf_union(int x, int y)
{
    x = uf_find(x);  //�ҵ����Զ����
    y = uf_find(y);
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


inline void uf_union(int i, int j)
{
    int x = uf_find(i), y = uf_find(j);    //���ҵ��������ڵ�
    if (rank[x] <= rank[y])
        father[x] = y;
    else
        father[y] = x;
    if (rank[x] == rank[y] && x!=y)
        rank[y]++;                   //��������ͬ�Ҹ��ڵ㲻ͬ�����µĸ��ڵ�����+1
}
