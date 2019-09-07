#include<stdio.h>
#define MAX 8

void insert(int *a,int n)
{
    int i,j,key;
    for(i=1;i<n;i++)//控制需要插入的元素
    {
        key=a[i]; //key为要插入的元素
        for(j=i;j>0 && a[j-1]>key;j--) //查找要插入的位置,循环结束,则找到插入位置
        {
            a[j] = a[j-1]; //移动元素的位置.供要插入元素使用
        }
        a[j] = key; //插入需要插入的元素
    }
}


int main(void)
{
    int a[MAX]={8,7,6,5,4,3,2,1};
    int i;

    insert(a,MAX);
    printf("after:\n");
    for(i=0;i<8;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}

