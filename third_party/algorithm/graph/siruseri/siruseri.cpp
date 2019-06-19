#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <map>

const long maxn = 500010;
const long MOD = 500010;
typedef long long ll;
long n;/*N ��ʾ·�ڵĸ���*/
long m;/*M��ʾ��·����*/
long S;long P;
long money[maxn];
long bar[maxn];
long DFN[maxn];
long LOW[maxn];
bool InStack[maxn];
long Stack[maxn];
long top  = 0;
long TIME = 0;
long Bcnt = 0;
long Belong[maxn];
long size[maxn];
long que[MOD];
bool vis[maxn];
long dist[maxn];
std::map<ll,bool> connected;
#define POS(a,b) (((ll)a-1)*(ll)m+(ll)b-1ll)
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

struct node
{
	long index;
	node* next;
};
node* head[maxn];
node* head2[maxn];

void insert(long a,long b)
{
	node* tmp = new node;
	tmp->index = b;
	tmp->next = head[a];
	head[a] = tmp;
}

void init()
{
    scanf("%ld%ld",&n,&m);

/*��i+1 �е�����������ʾ��i ����·�������յ��·�ڱ��*/
	for (long i=1;i<m+1;i++) {
		long a;long b;
		scanf("%ld%ld",&a,&b);
		insert(a,b);
	}

/*������ N �У�ÿ��һ����������˳���ʾÿ��·�ڴ���ATM���е�Ǯ��*/
	for (long i=1;i<n+1;i++)
		scanf("%ld",money+i);

/*������һ�а����������� S��P��S��ʾ�����ĵ�
��ţ�Ҳ���ǳ�����·�ڡ�P��ʾ�ư���Ŀ*/
	scanf("%ld%ld",&S,&P);

/*��������һ������ P����������ʾ
P���оưɵ�·�ڵı�š� */
	for (long i=1;i<P+1;i++)
		scanf("%ld",bar+i);
}

void tarjan(long u)
{
    DFN[u] = LOW[u] = ++TIME;
    InStack[u] = true;
    Stack[++top] = u;
    for (node* next=head[u];next;next=next->next)
    {
        long v = next->index;
        if (!DFN[v])
        {
            tarjan(v);
            LOW[u] = MIN(LOW[u],LOW[v]);
        }
        else if(InStack[v])
        {
            LOW[u] = MIN(LOW[u],DFN[v]);
        }
    }
    if (DFN[u] == LOW[u])
    {
        ++Bcnt;
        long v;
        do
        {
            v = Stack[top--];
            InStack[v]= false;
            Belong[v] = Bcnt;
            size[Bcnt]+=money[v];
        }while(v != u);
    }
}

void SPFA()
{
   long l = 0;
    long r = 0;
    que[++r] = Belong[S];
    while (l != r)
    {
        l = (l+1) % MOD;
        long u = que[l];
        vis[u] = false;
        for (node* vv=head2[u];vv;vv=vv->next)
        {
            long v = vv->index;
            if (dist[v]<dist[u]+size[v])
            {
                dist[v]=dist[u]+size[v];
                if (!vis[v])
                {
                    vis[v] = true;
                    r = (r+1) % MOD;
                    que[r] = v;
                }
            }
        }
    }
}

void insert2(long a,long b)
{
    node* tmp = new node;
    tmp->index = b;
    tmp->next = head2[a];
    head2[a] = tmp;
}

void rebuild()
{
    for (long u=1;u<n+1;u++)
    {
        for (node* vv=head[u];vv;vv=vv->next)
        {
            long v = vv->index;
            long B1 = Belong[u];
            long B2 = Belong[v];
            if (B1 != B2 && !connected[POS(B1,B2)])
            {
                connected[POS(B1,B2)] = true;
                insert2(B1,B2);
            }
        }
    }
}

int main()
{
	freopen("atm.in","r",stdin);
	freopen("atm.out","w",stdout);
	init();
	for (long i=1;i<n+1;i++)
		if (!DFN[i])
			tarjan(i);

	rebuild();
	SPFA();
	long ans = 0;
	for (long i=1;i<P+1;i++)
	{
	ans = MAX(ans,dist[Belong[bar[i]]]+size[Belong[S]]);
	}
	printf("%ld",ans);
	return 0;
}
