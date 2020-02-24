/*并查集（Disjoint set或者Union-find set）是一种树型
它主要涉及两个基本操作，分别为：
合并（Union）：把两个不相交的集合合并为一个集合。
查询（Find）：查询两个元素是否在同一个集合中。
(寻找两个元素的最久远祖先是否相同)

Q:
1)	计算最后有多少个不相交的集合
2)	需要多少条边可以成为连通图(即计算有多少个 parent[i] == i;)
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


/* 查找x元素所在的集合,回溯时压缩路径
就是找到parent指针的源头*/
int uf_find(int x)
{
    if (x != father[x])// x不是自身的父亲，即x不是该集合的祖宗
    {
        rank[father[x]] += rank[x];
        //递归，以找到最久远祖先
        //回溯时压缩路径：路径上的所有子孙节
        //点都指向最久远祖先
        father[x] = uf_find(father[x]);//查找x的祖先直到找到代表,于是顺手路径压缩
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
