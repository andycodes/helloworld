/**
 * C: �ڽӱ��ʾ��"����ͼ(List Undirected Graph)"
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

// �ڽӱ��б��Ӧ������Ķ���
typedef struct _ENode
{
    int ivex;                   // �ñ���ָ��Ķ����λ��
    struct _ENode *next_edge;   // ָ����һ������ָ��
}ENode, *PENode;

// �ڽӱ��б�Ķ���
typedef struct _VNode
{
    char data;              // ������Ϣ
    ENode *first_edge;      // ָ���һ�������ö���Ļ�
}VNode;

// �ڽӱ�
typedef struct _LGraph
{
    int vexnum;             // ͼ�Ķ������Ŀ
    int edgnum;             // ͼ�ıߵ���Ŀ
    VNode vexs[MAX];
}LGraph;


/*
 * ����ch��matrix�����е�λ��
 */
static int get_position(LGraph g, char ch)
{
    int i;
    for(i=0; i<g.vexnum; i++)
        if(g.vexs[i].data==ch)
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
 * ��node���ӵ�list��ĩβ
 */
static void link_last(ENode *list, ENode *node)
{
    ENode *p = list;

    while(p->next_edge)
        p = p->next_edge;
    p->next_edge = node;
}

/*
 * �����ڽӱ��Ӧ��ͼ(�Լ�����)
 */
LGraph* create_lgraph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    ENode *node1, *node2;
    LGraph* pG;

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

    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // ��ʼ��"������"��"����"
    pG->vexnum = v;
    pG->edgnum = e;
    // ��ʼ��"�ڽӱ�"�Ķ���
    for(i=0; i<pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i].data = read_char();
        pG->vexs[i].first_edge = NULL;
    }

    // ��ʼ��"�ڽӱ�"�ı�
    for(i=0; i<pG->vexnum; i++)
    {
        // ��ȡ�ߵ���ʼ����ͽ�������
        printf("edge(%d): ", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        // ��ʼ��node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        // ��node1���ӵ�"p1���������ĩβ"
        if(pG->vexs[p1].first_edge == NULL)
          pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
        // ��ʼ��node2
        node2 = (ENode*)malloc(sizeof(ENode));
        node2->ivex = p1;
        // ��node2���ӵ�"p2���������ĩβ"
        if(pG->vexs[p2].first_edge == NULL)
          pG->vexs[p2].first_edge = node2;
        else
            link_last(pG->vexs[p2].first_edge, node2);
    }

    return pG;
}

/*
 * �����ڽӱ��Ӧ��ͼ(�����ṩ������)
 */
LGraph* create_example_lgraph()
{
    char c1, c2;
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
    ENode *node1, *node2;
    LGraph* pG;


    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // ��ʼ��"������"��"����"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    // ��ʼ��"�ڽӱ�"�Ķ���
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].data = vexs[i];
        pG->vexs[i].first_edge = NULL;
    }

    // ��ʼ��"�ڽӱ�"�ı�
    for(i=0; i<pG->vexnum; i++)
    {
        // ��ȡ�ߵ���ʼ����ͽ�������
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        // ��ʼ��node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        // ��node1���ӵ�"p1���������ĩβ"
        if(pG->vexs[p1].first_edge == NULL)
          pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
        // ��ʼ��node2
        node2 = (ENode*)malloc(sizeof(ENode));
        node2->ivex = p1;
        // ��node2���ӵ�"p2���������ĩβ"
        if(pG->vexs[p2].first_edge == NULL)
          pG->vexs[p2].first_edge = node2;
        else
            link_last(pG->vexs[p2].first_edge, node2);
    }

    return pG;
}

/*
 * ��ӡ�ڽӱ�ͼ
 */
void print_lgraph(LGraph G)
{
    int i,j,k;
    ENode *node;

    printf("List Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%d(%c): ", i, G.vexs[i].data);
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            printf("%d(%c) ", node->ivex, G.vexs[node->ivex].data);
            node = node->next_edge;
        }
        printf("\n");
    }
}

void main()
{
    LGraph* pG;

    // �Զ���"ͼ"(�Լ���������)
    //pG = create_lgraph();
    // �������е�"ͼ"
    pG = create_example_lgraph();

    // ��ӡͼ
    print_lgraph(*pG);
}
