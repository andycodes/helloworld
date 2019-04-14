/**
 * C: ????????"???(Matrix Undirected Graph)"
 *
 * @author skywang
 * @date 2014/04/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

typedef struct _graph
{
	char vexs[MAX];
	int vexnum;
	int edgnum;
	int matrix[MAX][MAX];
}Graph, *PGraph;

/*
 * ??ch?matrix??????
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
 * ????????
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
 * ???(????)
 */
Graph* create_graph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    Graph* pG;

    // ??"???"?"??"
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

    // ???"???"?"??"
    pG->vexnum = v;
    pG->edgnum = e;
    // ???"??"
    for (i = 0; i < pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i] = read_char();
    }

    // ???"?"
    for (i = 0; i < pG->edgnum; i++)
    {
        // ?????????????
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

    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    pG->vexnum = vlen;
    pG->edgnum = elen;
    for (i = 0; i < pG->vexnum; i++)
    {
        pG->vexs[i] = vexs[i];
    }

    for (i = 0; i < pG->edgnum; i++)
    {
        p1 = get_position(*pG, edges[i][0]);
        p2 = get_position(*pG, edges[i][1]);

        pG->matrix[p1][p2] = 1;
        pG->matrix[p2][p1] = 1;
    }

    return pG;
}

static int first_vertex(Graph G, int v)
{
    int i;

    if (v<0 || v>(G.vexnum-1))
        return -1;

    for (i = 0; i < G.vexnum; i++)
        if (G.matrix[v][i] == 1)
            return i;

    return -1;
}

/*
 * ????v???w???????????,?????-1
 */
static int next_vertix(Graph G, int v, int w)
{
    int i;

    if (v<0 || v>(G.vexnum-1) || w<0 || w>(G.vexnum-1))
        return -1;

    for (i = w + 1; i < G.vexnum; i++)
        if (G.matrix[v][i] == 1)
            return i;

    return -1;
}

static void DFS(Graph G, int i, int *visited)
{
    int w;

    visited[i] = 1;
    printf("%c ", G.vexs[i]);
    for (w = first_vertex(G, i); w >= 0; w = next_vertix(G, i, w))
    {
        if (!visited[w])
            DFS(G, w, visited);
    }

}

void DFSTraverse(Graph G)
{
    int i;
    int visited[MAX];


    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("DFS: ");
    for (i = 0; i < G.vexnum; i++) {
        //printf("\n== LOOP(%d)\n", i);
        if (!visited[i])
            DFS(G, i, visited);
    }
    printf("\n");
}

/*
 * ??????(?????????)
 */
void BFS(Graph G)
{
    int head = 0;
    int rear = 0;
    int queue[MAX];     // ????
    int visited[MAX];   // ??????
    int i, j, k;

    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("BFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("%c ", G.vexs[i]);
            queue[rear++] = i;  // ???
        }
        while (head != rear)
        {
            j = queue[head++];  // ???
            for (k = first_vertex(G, j); k >= 0; k = next_vertix(G, j, k)) //k?????????
            {
                if (!visited[k])
                {
                    visited[k] = 1;
                    printf("%c ", G.vexs[k]);
                    queue[rear++] = k;
                }
            }
        }
    }
    printf("\n");
}

/*
 * ???????
 */
void print_graph(Graph G)
{
    int i,j;

    printf("Martix Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
            printf("%d ", G.matrix[i][j]);
        printf("\n");
    }
}

int  main()
{
	Graph* pG;
	pG = create_example_graph();
	print_graph(*pG);
	DFSTraverse(*pG);
	BFS(*pG);
	return 0;
}