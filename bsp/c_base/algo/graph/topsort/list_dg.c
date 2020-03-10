/**
 * C: �޻�·����ͼ(Directed Acyclic Graph)����������
 *    ��DAGͼ��ͨ���ڽӱ�ʵ�ֵġ�  
 *
 * @author skywang
 * @date 2014/04/22
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define isLetter(a)     ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)       (sizeof(a)/sizeof(a[0]))

// �ڽӱ��б��Ӧ������Ķ���
typedef struct _ENode
{
    int ivex;                   // �ñ���ָ��Ķ����λ��
    struct _ENode *next_edge;   // ָ����һ������ָ��
}ENode, *PENode;

// �ڽӱ��б�Ķ���
typedef struct _VNode
{
    char data;              // ��������
    ENode *first_edge;      // ָ���һ�������ö���Ļ�
}VNode;

// �ڽӱ�
typedef struct _LGraph
{
    int vexnum;             // ͼ�Ķ������Ŀ
    int edgnum;             // ͼ�ıߵ���Ŀ
    VNode *vexs;            // ͼ�Ķ�������
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
 
    pG = (LGraph*)malloc(sizeof(LGraph));
    assert(pG!=NULL);

    // ��ʼ��"������"��"����"
    pG->vexnum = v;
    pG->edgnum = e;
    pG->vexs = (VNode *)malloc(pG->vexnum * sizeof(VNode));
    assert(pG->vexs != NULL);
    // ��ʼ��"�ڽӱ�"�Ķ���
    for(i=0; i<pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i].data = read_char();
        pG->vexs[i].first_edge = NULL;
    }

    // ��ʼ��"�ڽӱ�"�ı�
    for(i=0; i<pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����ͽ�������
        printf("edge(%d): ", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        // ��ʼ��node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex             = p2;
        // ��node1���ӵ�"p1���������ĩβ"
        if(pG->vexs[p1].first_edge == NULL)
          pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
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
        {'A', 'G'}, 
        {'B', 'A'}, 
        {'B', 'D'}, 
        {'C', 'F'}, 
        {'C', 'G'}, 
        {'D', 'E'}, 
        {'D', 'F'}}; 
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    ENode *node1, *node2;
    LGraph* pG;

    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
    assert(pG != NULL);
    memset(pG, 0, sizeof(LGraph));

    // ��ʼ��"������"��"����"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    pG->vexs = (VNode *)malloc(pG->vexnum * sizeof(VNode));
    assert(pG->vexs != NULL);
    // ��ʼ��"�ڽӱ�"�Ķ���
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].data = vexs[i];
        pG->vexs[i].first_edge = NULL;
    }

    // ��ʼ��"�ڽӱ�"�ı�
    for(i=0; i<pG->edgnum; i++)
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
    }

    return pG;
}

/*
 * ���������������ͼ�ĵݹ�ʵ��
 */
static void DFS(LGraph G, int i, int *visited)
{
    int w;
    ENode *node;

    visited[i] = 1;
    printf("%c ", G.vexs[i].data);
    node = G.vexs[i].first_edge;
    while (node != NULL)
    {
        if (!visited[node->ivex])
            DFS(G, node->ivex, visited);
        node = node->next_edge;
    }
}

/*
 * ���������������ͼ
 */
void DFS_traverse(LGraph G)
{
    int i;
    int *visited;       // ������ʱ��

    visited = (int *)malloc(G.vexnum * sizeof(int));
    assert(visited != NULL);

    // ��ʼ�����ж��㶼û�б�����
    memset(visited, 0, G.vexnum * sizeof(int));

    printf("== DFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
            DFS(G, i, visited);
    }
    printf("\n");

    free(visited);
}

/*
 * ����������������������Ĳ�α�����
 */
void BFS(LGraph G)
{
    int head = 0;
    int rear = 0;
    int *queue;     // �������
    int *visited;   // ������ʱ��
    int i, j, k;
    ENode *node;


    queue   = (int *)malloc(G.vexnum * sizeof(int));
    visited = (int *)malloc(G.vexnum * sizeof(int));
    assert(queue!=NULL && visited!=NULL);

    memset(queue, 0, G.vexnum * sizeof(int));
    memset(visited, 0, G.vexnum * sizeof(int));

    printf("== BFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("%c ", G.vexs[i].data);
            queue[rear++] = i;  // �����
        }
        while (head != rear) 
        {
            j = queue[head++];  // ������
            node = G.vexs[j].first_edge;
            while (node != NULL)
            {
                k = node->ivex;
                if (!visited[k])
                {
                    visited[k] = 1;
                    printf("%c ", G.vexs[k].data);
                    queue[rear++] = k;
                }
                node = node->next_edge;
            }
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}

/*
 * ��������
 *
 * ����˵����
 *     G -- �ڽӱ��ʾ������ͼ
 * ����ֵ��
 *     -1 -- ʧ��(�����ڴ治���ԭ����)
 *      0 -- �ɹ����򣬲�������
 *      1 -- ʧ��(������ͼ���л���)
 */
int topological_sort(LGraph G)
{
    int i,j;
    int index = 0;
    int head = 0;           // �������е�ͷ
    int rear = 0;           // �������е�β
    int *queue;             // �������
    int *ins;               // �������
    char *tops;             // �������������飬��¼ÿ���ڵ����������š�
    int num = G.vexnum;
    ENode *node;

    ins  = (int *)malloc(num*sizeof(int));  // �������
    tops = (char *)malloc(num*sizeof(char));// ��������������
    queue = (int *)malloc(num*sizeof(int)); // ��������
    assert(ins!=NULL && tops!=NULL && queue!=NULL);
    memset(ins, 0, num*sizeof(int));
    memset(tops, 0, num*sizeof(char));
    memset(queue, 0, num*sizeof(int));

    // ͳ��ÿ������������
    for(i = 0; i < num; i++)
    {
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            ins[node->ivex]++;
            node = node->next_edge;
        }
    }

    // ���������Ϊ0�Ķ��������
    for(i = 0; i < num; i ++)
        if(ins[i] == 0)
            queue[rear++] = i;          // �����

    while (head != rear)                // ���зǿ�
    {
        j = queue[head++];              // �����С�j�Ƕ�������
        tops[index++] = G.vexs[j].data; // ���ö�����ӵ�tops�У�tops��������
        node = G.vexs[j].first_edge;    // ��ȡ�Ըö���Ϊ���ĳ��߶���

        // ����"node"�����Ľڵ����ȼ�1��
        // ����1֮�󣬸ýڵ�����Ϊ0���򽫸ýڵ���ӵ������С�
        while(node != NULL)
        {
            // ���ڵ�(���Ϊnode->ivex)����ȼ�1��
            ins[node->ivex]--;
            // ���ڵ�����Ϊ0������"�����"
            if( ins[node->ivex] == 0)
                queue[rear++] = node->ivex;  // �����

            node = node->next_edge;
        }
    }

    if(index != G.vexnum)
    {
        printf("Graph has a cycle\n");
        free(queue);
        free(ins);
        free(tops);
        return 1;
    }

    // ��ӡ����������
    printf("== TopSort: ");
    for(i = 0; i < num; i ++)
        printf("%c ", tops[i]);
    printf("\n");

    free(queue);
    free(ins);
    free(tops);
    return 0;
}

/*
 * ��ӡ�ڽӱ�ͼ
 */
void print_lgraph(LGraph G)
{
    int i;
    ENode *node;

    printf("== List Graph:\n");
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
    print_lgraph(*pG);      // ��ӡͼ
    //DFS_traverse(*pG);    // �����������
    //BFS(*pG);             // �����������
    topological_sort(*pG);  // ��������
}
