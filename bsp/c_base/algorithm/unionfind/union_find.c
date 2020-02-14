/*并查集（Disjoint set或者Union-find set）是一种树型
的数据结构，常用于处理一些不相交集合（Disjoint Sets）
的合并及查询问题。
2、  基本操作

并查集是一种非常简单的数据结构，
它主要涉及两个基本操作，分别为：

A． 合并两个不相交集合

B． 判断两个元素是否属于同一个集合

本操作可转换为寻找两个元素的最久远祖先是否相同。可以采用递归实现。

合并（Union）：把两个不相交的集合合并为一个集合。
查询（Find）：查询两个元素是否在同一个集合中。
*/

#define MAX 1024

int father[MAX];   /* father[x]表示x的父节点 */
int rank[MAX];     /* rank[x]表示x的秩 */

inline void uf_init(int n)
{
    for (int i = 0; i < n; ++i) {
	//父节点为自己
        father[i] = i;
	//秩为0
	rank[i] = 0;
    }

}


/* 查找x元素所在的集合,回溯时压缩路径 */
int uf_find(int x)
{
    if (x != father[x])
    {
        rank[father[x]] += rank[x];
        //递归，以找到最久远祖先
        //回溯时压缩路径：路径上的所有子孙节
        //点都指向最久远祖先
        father[x] = uf_find(father[x]);
    }
    return father[x];
}


/*
   按秩合并x和y所在的集合
   下面的那个if else结构不是绝对的，具体根据情况变化
   但是，宗旨是不变的即，按秩合并，实时更新秩。
*/
void uf_union(int x, int y)
{
    x = uf_find(x);  //找到最久远祖先
    y = uf_find(y);
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


inline void uf_union(int i, int j)
{
    int x = uf_find(i), y = uf_find(j);    //先找到两个根节点
    if (rank[x] <= rank[y])
        father[x] = y;
    else
        father[y] = x;
    if (rank[x] == rank[y] && x!=y)
        rank[y]++;                   //如果深度相同且根节点不同，则新的根节点的深度+1
}
