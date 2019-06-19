#include <iostream>
#include <stdio.h>
#include <stack>
using namespace std;

struct Edge
{
    int adj_vertex;
    Edge* next;
};

struct Vertex
{
    int vertex;
    Edge* head;
};

struct Graph
{
    Vertex vertices[50];
    int vertex_num;
};

int Visited[50];
int inStack[50];
int DFN[50];
int Low[50];
int time_cnt=0;
stack<int> S;

void Create_Graph(Graph *g)
{
    cout <<"enter the number of vertices:";
    cin >>g->vertex_num;

    for(int i=1;i<=g->vertex_num;++i)
    {
        g->vertices[i].vertex=i;
        g->vertices[i].head=NULL;
    }

    for(int i=1;i<=g->vertex_num;++i)
    {
        cin.clear();
        cout <<"enter vertex "<<i<<"'s edges:";
        int vtx;
        Edge* temp;
        while(cin >>vtx)
        {
            temp=new Edge;
            temp->adj_vertex=vtx;
            temp->next=g->vertices[i].head;
            g->vertices[i].head=temp;
        }
    }
}

void Tarjan(int u,const Graph *g)
{
    ++time_cnt;
    DFN[u]=Low[u]=time_cnt;
    Visited[u]=1;
    S.push(u);
    inStack[u]=1;
    for(Edge* temp=g->vertices[u].head;temp;temp=temp->next)
    {
        int v=temp->adj_vertex;
        if(Visited[v]==0)
        {
            Tarjan(v,g);
            if(Low[u]>Low[v])
                Low[u]=Low[v];
        }
        else if(inStack[v] && Low[u]>DFN[v])
            Low[u]=DFN[v];
    }

    if(DFN[u]==Low[u])
    {
        int vtx;
        cout <<"set is:";
        do
        {
            vtx=S.top();
            S.pop();
            inStack[vtx]=0;
            cout <<vtx<<" ";
        } while (vtx!=u);
    }
}

int main()
{
    Graph* g=new Graph;
    Create_Graph(g);
    for(int i=1;i<=g->vertex_num;++i)
    {
        Visited[i]=0;
        inStack[i]=0;
        DFN[i]=0;
        Low[i]=0;
    }
    for(int i=1;i<=g->vertex_num;++i)
        if(Visited[i]==0)
            Tarjan(i,g);
}