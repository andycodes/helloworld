#include<stdio.h>
#define MAX 8

void insert(int *a,int n)
{
    int i,j,key;
    for(i=1;i<n;i++)//������Ҫ�����Ԫ��
    {
        key=a[i]; //keyΪҪ�����Ԫ��
        for(j=i;j>0 && a[j-1]>key;j--) //����Ҫ�����λ��,ѭ������,���ҵ�����λ��
        {
            a[j] = a[j-1]; //�ƶ�Ԫ�ص�λ��.��Ҫ����Ԫ��ʹ��
        }
        a[j] = key; //������Ҫ�����Ԫ��
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

