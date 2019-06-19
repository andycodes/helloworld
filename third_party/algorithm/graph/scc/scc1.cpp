/*
/*
���� �� http://acm.hust.edu.cn/vjudge/problem/viewProblem.action?id=30726

���� �� ����ͼG����һ�����ĵ㼯��ʹ�õ㼯�����������ڵ�u��v��
���� Ҫôu���Ե���v��Ҫôv���Ե���u������u��v�����໥���




����ǿ��ͨ�����һ��DAG����Ϊÿ��ǿ��ͨ����ҪôѡҪô��ѡ��
��DAG�ϵ��· ���ν�ͼ ����2�ֲ�ͬ�ķ�����Ҳ�ֱ����˼��仨����
DP��ֱ�ӵ���DP




vector��ͼ�ͼ��仯������

*/
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <cmath>
#include <map>
#define lson o<<1,l,m
#define rson o<<1|1,m+1,r
#define mem(a) memset(a,0,sizeof(a))
typedef long long ll;
const int N = 1005;
const int M = 50005;
const ll mod = 1000000007;

using namespace std;

int n, m, T;
int he[N];

struct C {
    int ne, to;
} e[M];

void add(int id, int x, int y) {
    e[id].to = y;
    e[id].ne = he[x];
    he[x] = id;
}

int pre[N], low[N], scc[N], dfs_clock, scc_cnt;
stack <int> S;

void dfs(int u) {

    pre[u] = low[u] = ++ dfs_clock;
    S.push(u);
    for(int i = he[u]; i != -1; i = e[i].ne) {

        int v = e[i].to;
        if(pre[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(scc[v] == 0) {
            low[u] = min(low[u], pre[v]);
        }

    }

    if(low[u] == pre[u]) {
        scc_cnt ++;
        while(1) {
            int x = S.top(); S.pop();
            scc[x] = scc_cnt;
            if(x == u) break;
        }
    }

}

void find_scc() {
    mem(scc);
    mem(pre);
    dfs_clock = scc_cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(pre[i] == 0) dfs(i);
    }
}

int dp[N], vis[N], w[N];
vector <int> G[N];

int DP(int u) {
    int& ans = dp[u];
    if(vis[u] == 1) return ans;
    vis[u] = 1;
    ans = w[u];
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
				ans = max(ans, DP(v) + w[u]);
    }
    return ans;
}

int main() {

    cin >> T;
    while(T--) {

        cin >> n >> m;
        memset(he, -1, sizeof(he));

        for(int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            add(i, x, y);
        }

        find_scc();
        mem(w);
        for(int i = 1; i <= n; i++) {
            int x = scc[i];
            w[x]++;
      	}

				for(int i = 1; i <= scc_cnt; i++) {
					G[i].clear();
				}

        int id = 1;
        for(int u = 1; u <= n; u++) {
            for(int i = he[u]; i != -1; i = e[i].ne) {
                int v = e[i].to;
                if(scc[v] != scc[u]) {
                    G[scc[u]].push_back(scc[v]);
                }
            }
        }

        memset(vis, 0, sizeof(vis));
        int ans = 0;
        for(int i = 1; i <= scc_cnt; i++) {
        	ans = max(ans, DP(i));
				}

        printf("%d\n", ans);

    }

    return 0;
}