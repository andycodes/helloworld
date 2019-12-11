/*ͼ��������ȱ���*/
#include <stdlib.h>
#include <stdio.h>

#define VERTEX_NUM 9 /*ʵ��8���㣬λ��0��ʹ��*/


struct node                       /* ͼ����ṹ����     */
{
   int vertex;                    /* ����������Ϣ       */
   struct node *nextnode;         /* ָ��һ�����ָ��   */
};
typedef struct node *graph;       /* ͼ�εĽṹ����̬   */
struct node head[VERTEX_NUM];              /* ͼ�ζ�������       */

/* To determine whether a vertex has been visited, if you have visited, no longer visit*/
int visited[VERTEX_NUM];

/********************�������е���Ϣ�����ڽӱ�********************/
/*each starting point to build list
The list maintains the edge starting from the starting point*/
void creategraph(int node[ ][2],int num)/*numָ����ͼ�ı���*/
{
	graph newnode;                 /*ָ���½ڵ��ָ�붨��*/
	graph ptr;
	int from;                      /* �ߵ����          */
	int to;                        /* �ߵ��յ�          */
	int i;

	/* ��ȡ������Ϣ�������ڽӱ�*/
	for ( i = 0; i < num; i++ ) {
		from = node[i][0];         /*    ���ߵ����            */
		to = node[i][1];           /*   ���ߵ��յ�             */

		/* �����¶��� */
		newnode = (graph)malloc(sizeof(struct node));
		newnode->vertex = to;        /*next vertex id, dfs use it*/
		newnode->nextnode = NULL;    /* �趨ָ���ֵ       */
		ptr = &(head[from]);         /* ����λ��           */
		while (ptr->nextnode != NULL ) /* ����������β   */
			ptr = ptr->nextnode;     /* ��һ������         */
		ptr->nextnode = newnode;    /* ����ڵ�        */
	}
}

/**********************  ͼ�����������Ѱ��********************/
/*Loop through head lists*/
void dfs(int current)
{
	graph ptr;
	visited[current] = 1;          /* ��¼�ѱ�����       */
	printf("vertex[%d]\n",current);   /* �����������ֵ     */
	ptr = head[current].nextnode;  /* ����λ��           */
	while ( ptr != NULL ) {
		/*Make sure that each vertex is accessed only once*/
		if (visited[ptr->vertex] == 0)
			dfs(ptr->vertex);              /* �ݻر������� */
		ptr = ptr->nextnode;              /* ��һ������   */
	}
}

/****************************** ������******************************/
int main()
{
	graph ptr;
	 /* ��������     */
	int node[ ][2] = {
		{1, 2}, {2, 1},
		{1, 3}, {3, 1},
		{1, 4}, {4, 1},
		{2, 5}, {5, 2},
		{2, 6}, {6, 2},
		{3, 7}, {7, 3},
		{4, 7}, {4, 4},
		{5, 8}, {8, 5},
		{6, 7}, {7, 6},
		{7, 8}, {8, 7}
	};


	int i;
	//clrscr();
	for ( i = 1; i < VERTEX_NUM; i++ )      /*   ���������ʼ��  */
	{
		head[i].vertex = i;         /*    �趨����ֵ      */
		head[i].nextnode = NULL;    /*       ָ��Ϊ��     */
		visited[i] = 0;             /* �趨������ʼ��־   */
	}
	creategraph(node,sizeof(node)/(2*sizeof(int)));          /*    �����ڽӱ�      */
	printf("Content of the gragh's ADlist is:\n");
	for ( i = 1; i <VERTEX_NUM; i++ ) {
		printf("vertex%d ->",head[i].vertex); /* ����ֵ    */
		ptr = head[i].nextnode;             /* ����λ��   */
		while ( ptr != NULL ){     /* ����������β       */
			printf(" %d ",ptr->vertex);  /* ӡ����������   */
			ptr = ptr->nextnode;         /* ��һ������     */
		}
		printf("\n");               /*   ����             */
	}
	printf("\nThe end of the dfs are:\n");

	dfs(1);/*Starting from vertex 1*/
	printf("\n");                  /* ����               */
	puts(" Press any key to quit...");
}

