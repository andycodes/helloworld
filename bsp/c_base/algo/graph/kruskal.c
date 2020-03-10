#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


#include <stdio.h>
#include <string.h>
#define MAXN 11  //������������ֵ
#define MAXM 20  //�ߵĸ��������ֵ

struct edge  //��
{
    int u, v, w; //�ߵĶ��㡢Ȩֵ
}edges[MAXM]; //�ߵ�����

int parent[MAXN];  //parent[i]Ϊ���� i ���ڼ��϶�Ӧ�����еĸ����
int n, m;  //����������ߵĸ���
int i, j;  //ѭ������

void UFset( )  //��ʼ��
{
    for( i=1; i<=n; i++ )
        parent[i] = -1;
}

int Find( int x ) //���Ҳ����ؽڵ� x �������ϵĸ����
{
    int s; //����λ��
    for( s=x; parent[s]>=0; s=parent[s] );
    while( s!=x ) //�Ż������Dѹ��·����ʹ�����Ĳ��Ҳ������١�
    {
        int tmp = parent[x];
        parent[x] = s;
        x = tmp;
    }
    return s;
}


//��������ͬ���ϵ�Ԫ�ؽ��кϲ���
//ʹ����������������Ԫ�ض���ͨ
void Union( int R1, int R2 )
{
    int r1 = Find(R1), r2 = Find(R2); //r1 Ϊ R1 �ĸ���㣬r2 Ϊ R2 �ĸ����
    int tmp = parent[r1] + parent[r2]; //�������Ͻ�����֮��(����)
    //��� R2 ������������ > R1 ������������
    //(ע�� parent[r1]�Ǹ���)
    if( parent[r1] > parent[r2] ) //�Ż������D�D��Ȩ����
    {
        parent[r1] = r2;
        parent[r2] = tmp;
    }
    else
    {
        parent[r2] = r1;
        parent[r1] = tmp;
    }
}


int cmp( const void * a, const void * b ) //ʵ�ִ�С��������ıȽϺ���
{
    return ((struct edge *)a)->w <= ((struct edge *)b)->w;
}

void Kruskal( )
{
    int sumweight = 0;  //��������Ȩֵ
    int num = 0;  //��ѡ�õıߵ���Ŀ
    int u, v;  //ѡ�ñߵ���������
    UFset( ); //��ʼ�� parent[]����
    for( i=0; i<m; i++ )
    {
        u = edges[i].u; v = edges[i].v;
        if( Find(u) != Find(v) )
        {
            printf( "%d %d %d\n", u, v, edges[i].w );
            sumweight += edges[i].w; num++;
            Union( u, v );
        }
        if( num>=n-1 ) break;
    }
    printf( "weight of MST is %d\n", sumweight );
}


int main( )
{
    int u, v, w; //�ߵ������յ㼰Ȩֵ
    scanf( "%d%d", &n, &m ); //����������ߵĸ���
    for( int i=0; i<m; i++ )
    {
	    scanf( "%d%d%d", &u, &v, &w ); //����ߵ������յ�
	    edges[i].u = u; edges[i].v = v; edges[i].w = w;
    }
    qsort(&edges,n,sizeof(edges[0]),cmp);
    Kruskal();
    return 0;
}

