/**
 * C: �ڽӾ���ͼ��ʾ��"����ͼ(Matrix Undirected Graph)"
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100

#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

// �ڽӾ���
typedef struct _graph
{
    char vexs[MAX];       // ���㼯��
    int vexnum;           // ������
    int edgnum;           // ����
    int matrix[MAX][MAX]; // �ڽӾ���
}Graph, *PGraph;

/*
 * ����ch��matrix�����е�λ��
 */
static int get_position(Graph g, char ch)
{
    int i;
    for(i=0; i<g.vexnum; i++)
        if(g.vexs[i]==ch)
            return i;
    return -1;
}

/*
 * ��ȡһ�������ַ�
 */
static char read_char()
{
    char ch;

    do {
        ch = getchar();
    } while(!isLetter(ch));

    return ch;
}

/*
 * ����ͼ(�Լ�����)
 */
Graph* create_graph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    Graph* pG;

    // ����"������"��"����"
    printf("input vertex number: ");
    scanf("%d", &v);
    printf("input edge number: ");
    scanf("%d", &e);
    if ( v < 1 || e < 1 || (e > (v * (v-1))))
    {
        printf("input error: invalid parameters!\n");
        return NULL;
    }

    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // ��ʼ��"������"��"����"
    pG->vexnum = v;
    pG->edgnum = e;
    // ��ʼ��"����"
    for (i = 0; i < pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i] = read_char();
    }

    // ��ʼ��"��"
    for (i = 0; i < pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����ͽ�������
        printf("edge(%d):", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        if (p1==-1 || p2==-1)
        {
            printf("input error: invalid edge!\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = 1;
        pG->matrix[p2][p1] = 1;
    }

    return pG;
}

/*
 * ����ͼ(�����ṩ�ľ���)
 */
Graph* create_example_graph()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'C'},
        {'A', 'D'},
        {'A', 'F'},
        {'B', 'C'},
        {'C', 'D'},
        {'E', 'G'},
        {'F', 'G'}};
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    Graph* pG;

    // ����"������"��"����"
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // ��ʼ��"������"��"����"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    // ��ʼ��"����"
    for (i = 0; i < pG->vexnum; i++)
    {
        pG->vexs[i] = vexs[i];
    }

    // ��ʼ��"��"
    for (i = 0; i < pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����ͽ�������
        p1 = get_position(*pG, edges[i][0]);
        p2 = get_position(*pG, edges[i][1]);

        pG->matrix[p1][p2] = 1;
        pG->matrix[p2][p1] = 1;
    }

    return pG;
}

/*
 * ��ӡ�������ͼ
 */
void print_graph(Graph G)
{
    int i,j,k;

    printf("Martix Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
            printf("%d ", G.matrix[i][j]);
        printf("\n");
    }
}

void main()
{
    Graph* pG;

    // �Զ���"ͼ"(����������)
    //pG = create_graph();
    // �������е�"ͼ"
    pG = create_example_graph();
    // ��ӡ�������
    print_graph(*pG);
}
