#include<stdio.h>
#include<stdlib.h>
void Warshall(int,int**);
void main()
{
    int i,j,num;
    FILE*p;
    p=fopen("2.txt","r");
    if(p==NULL)
    {
        printf("cannot open 2.txt");
        exit(-1);
    }
    fscanf(p,"%d",&num);
    int **r=(int**)malloc(sizeof(int*)*(num+1));
    for(i=0;i<num+1;i++)
        r[i]=(int*)malloc(sizeof(int)*(num+1));
    for(i=1;i<num+1;i++)
        for(j=1;j<num+1;j++)
            fscanf(p,"%d",&r[i][j]);
    printf("�������Ϊ��%d\n",num);
    printf("�ڽӾ���Ϊ��\n");
    for(i=1;i<num+1;i++)
    {
        for(j=1;j<num+1;j++)
            printf(" %d  ",r[i][j]);
        printf("\n");
    }
    Warshall(num,r);
    printf("���յĴ��ݱհ�Ϊ\n");
    for(i=1;i<num+1;i++)
    {
        for(j=1;j<num+1;j++)
            printf(" %d  ",r[i][j]);
        printf("\n");
    }

}
//����ѭ��ʵ�ֵ�warshall�㷨
//rΪ�ڽӾ����м�洢���ԵĿɴ���ǿɴ�·�������1��ʾ�ɴ0��ʾ���ɴ�
void Warshall(int num,int**r)
{
    int i,j,k;
    int **temp=(int**)malloc(sizeof(int*)*(num+1));
    for(i=0;i<num+1;i++)
        temp[i]=(int*)malloc(sizeof(int)*(num+1));
    for(k=1;k<=num;k++)//����ȡ�õĿ�����Ϊ�м��Ķ���
    {
        for(i=1;i<=num;i++)
        {
            for(j=1;j<=num;j++)
            {
                temp[i][j]=(r[i][j])||(r[i][k]&r[k][j]);
            }
        }
        for(i=1;i<=num;i++)
            for(j=1;j<=num;j++)
                r[i][j]=temp[i][j];
    }

}