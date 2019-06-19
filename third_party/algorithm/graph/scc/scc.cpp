/*
�����⡿������һȺţ�У�һͷţ��Ϊ��һͷţ�ܻ�ӭ��m�Թ�ϵ��
��ϵʽ���Դ��ݵģ�����a��Ϊb�ܻ�ӭ��b��Ϊc�ܻ�ӭ����ôaҲ��Ϊc�ܻ�ӭ��
������ж���ͷţ�����е�ţ��Ϊ�ܻ�ӭ��

��˼·��������Щ��ϵ�γɵ�ǿ��ͨͼ���ɵ㣬
���γ���һ�����޻�ͼ�����ͼ��ĳ���Ϊ0�ĵ㣨����ֻ��һ����
���Ǳ�����ţ��Ϊ�ܻ�ӭ�ĵ㣬˵���������ԭ����ǿ��ͨͼ��Ҫ
������ǿ��ͨͼ����ܵ�����
*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;

int pre[10002],low[10002],lt_num,c,scc_num[10002],scc,out0[10002],n,adj[10002],num,flag,scc_count[10002];
struct E
{
    int to;
    int next;
} edge[500000];

stack <int >s;

void add(int a,int b)
{
    edge[num].to=b;
    edge[num].next=adj[a];
    adj[a]=num++;
}

void dfs(int u)
{
    int i,v;
    pre[u]=low[u]=c++;
    s.push (u);
    for(i=adj[u]; i!=-1; i=edge[i].next)
    {
        v=edge[i].to;
        if(!pre[v])//!scc_num[v]
        {
            dfs(v);

                low[u]=min(low[u],low[v]);
        }
        else if(!scc_num[v])
            low[u]=min(low[u],pre[v]);
    }
    if(low[u]==pre[u])   //�Ǹ���ͨ������ ��һ����
    {
        scc++;
        while(1)
        {
            int t=s.top ();
            s.pop ();
            scc_num[t]=scc;             //scc_num[t]�ǵ�scc��ǿ��ͨ����;
            scc_count[scc]++;
            if(t==u)
                break;
        }
    }
}

int main()
{
    int a,b,m,i;
    while(~scanf("%d%d",&n,&m))
    {
        memset(adj,-1,sizeof(adj));
        num=0;
        while(m--)
        {
            scanf("%d%d",&a,&b);
            add(a,b);
        }
        c=1;scc=0;
        memset(scc_count,0,sizeof(scc_count));
        memset(pre,0,sizeof(pre));
        for(int i=1;i<=n;i++)
            if(pre[i]==0)
                dfs(i);


        memset(out0,0,sizeof(out0));
        for(int u=1;u<=n;u++)
            for(i=adj[u]; i!=-1; i=edge[i].next)
            {
                int v; v=edge[i].to;
                if(scc_num[u]!=scc_num[v])
                    out0[scc_num[u]]++;
            }

        int ans=0,num=0;
        for(int u=1;u<=scc;u++)
            if(out0[u]==0)
                {
                    num++;
                    ans+=scc_count[u];
                }
                if(num==1)
        printf("%d\n",ans);
        else printf("0\n");
    }
    return 0;
}