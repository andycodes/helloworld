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
    printf("顶点个数为：%d\n",num);
    printf("邻接矩阵为：\n");
    for(i=1;i<num+1;i++)
    {
        for(j=1;j<num+1;j++)
            printf(" %d  ",r[i][j]);
        printf("\n");
    }
    Warshall(num,r);
    printf("最终的传递闭包为\n");
    for(i=1;i<num+1;i++)
    {
        for(j=1;j<num+1;j++)
            printf(" %d  ",r[i][j]);
        printf("\n");
    }

}
//三重循环实现的warshall算法
//r为邻接矩阵，中间存储初试的可达与非可达路径情况，1表示可达，0表示不可达
void Warshall(int num,int**r)
{
    int i,j,k;
    int **temp=(int**)malloc(sizeof(int*)*(num+1));
    for(i=0;i<num+1;i++)
        temp[i]=(int*)malloc(sizeof(int)*(num+1));
    for(k=1;k<=num;k++)//依次取得的可以作为中间点的顶点
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