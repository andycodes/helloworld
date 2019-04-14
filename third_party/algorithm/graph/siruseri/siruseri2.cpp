#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <set>
#include <queue>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

using std::set;
using std::pair;
using std::make_pair;
const char fi[] = "atm.in";
const char fo[] = "atm.out";
const int maxN = 500010;
const int SIZE = 0xfffff;
const int MAX = 0x3f3f3f3f;
const int MIN = ~MAX;

struct Edge {int v; Edge *next;};
Edge *edge1[maxN], *edge2[maxN];
bool marked[maxN], bar[maxN], final[maxN];
int q[maxN], money[maxN], dist[maxN];
int cnt[maxN], DFN[maxN], Low[maxN];
int belong[maxN], stack[maxN];
int n, m, S, P, top, Index, Bcnt, ans, f, r;

void init_file()
{
    freopen(fi, "r", stdin);
    freopen(fo, "w", stdout);
    return;
}

inline int getint()
{
	int res = 0; char tmp;
	while (!isdigit(tmp = getchar()));
		do res = (res << 3) + (res << 1) + tmp - '0';
	while (isdigit(tmp = getchar()));
	return res;
}

inline void insert2(int u, int v)
{
    if (u == v) return;
    for (Edge *p = edge2[u]; p; p = p -> next)
        if (p -> v == v) return;
    //重新建图的时候要记得判重，
    //以免重边造成枚举量很大。
    Edge *p = new Edge;
    p -> v = v;
    p -> next = edge2[u];
    edge2[u] = p;
    return;
}

inline void insert1(int u, int v)
{
	Edge *p = new Edge;
	p -> v = v;
	p -> next = edge1[u];
	edge1[u] = p;
	return;
}

void readdata()
{
	n = getint();
	for (m = getint(); m; --m) {
		int u = getint(), v = getint();
		insert1(u, v);
	}

	for (int i = 1; i < n + 1; ++i)
		money[i] = getint();

	S = getint();

	for (P = getint(); P; --P)
		bar[getint()] = 1;
	return;
}

void tarjan(int u)
{
   Low[u] = DFN[u] = ++Index;
   marked[stack[++top] = u] = true;
   for (Edge *p = edge1[u]; p; p = p -> next)
   {
       int v = p -> v;
       if (!DFN[v])
       {
           tarjan(v);
           Low[u] = min(Low[u], Low[v]);
       }
       else if (marked[v])
           Low[u] = min(Low[u], DFN[v]);
   }
   if (Low[u] == DFN[u])
   {
        ++Bcnt;
        int tmp = u;
        do
        {
            marked[tmp = stack[top--]] = 0;
            belong[tmp] = Bcnt;
            final[Bcnt] |= bar[tmp];
            cnt[Bcnt] += money[tmp];
        } while (tmp != u);
    }
    return;
}

inline int Spfa()
{
    memset(marked, 0, sizeof marked);
    memset(dist, ~0x3f, sizeof dist);
    int ans = final[belong[S]]
            ? cnt[belong[S]] : 0;
    //注意起点不是终点的情况。
    top = 0;
    q[r++] = belong[S];
    dist[belong[S]] = cnt[belong[S]];
    marked[belong[S]] = 1;
    while (f < r)
    {
        int u = q[f++];
        marked[u] = 0;
        for (Edge *p = edge2[u]; p; p = p -> next)
        if (dist[u] + cnt[p -> v] > dist[p -> v])
        {
            dist[p -> v] = dist[u] + cnt[p -> v];
            if (final[p -> v])
                ans = max(ans, dist[p -> v]);
            if (!marked[p -> v])
            {
                marked[p -> v] = 1;
                q[r++] = p -> v;
            }
        }
    }
    return ans;
}

void work()
{
	tarjan(S);
	for (int i = 1; i < n + 1; ++i)
		for (Edge *p = edge1[i]; p; p = p -> next)

	if (belong[p -> v] != belong[i])
		insert2(belong[i], belong[p -> v]);

	printf("%d\n", Spfa());
	return;
}

int main()
{
    init_file();
    readdata();
    work();
    return 0;
}

#undef min
#undef max

