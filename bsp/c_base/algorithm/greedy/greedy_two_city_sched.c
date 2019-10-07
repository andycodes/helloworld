#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
������������������⣬��˾���Ƚ��� 2N ����ȫ�����ŷ��� B �У�
��ѡ�� N ���˸ı����ǵ��г̣������Ƿ��� A �С�
���ѡ��ı�һ���˵��г̣���ô��˾������⸶�� price_A - price_B �ķ��ã�
������ÿ����ɸ���


������ŵķ����ǣ�ѡ�� price_A - price_B ��С�� N ���ˣ�
�����Ƿ��� A �У������˷��� B �С�
�㷨���� price_A - price_B ��С��������
��ǰ N ���˷��� A �У������˷��� B �У�
��������ܷ��á�
*/

struct obj{
    int a;
    int b;
    int diff;
};

void bubble_sort(struct obj  *data,int size)
{
    for (int i=size;i>0;i--)
    {
        for (int j=0;j<(i-1);j++)
            {
                if (data[j].diff >data[j+1].diff)
                    {
                        struct obj  tmp;
                        tmp=data[j];
                        data[j]=data[j+1];
                        data[j+1]=tmp;
                    }
            }
       }
}



int twoCitySchedCost(int costs[][2], int costsSize, int* costsColSize){
        int i;
        struct obj ob[100];
        int sum = 0;

        for(i = 0; i < costsSize; i++){
                ob[i].a = costs[i][0];
                ob[i].b = costs[i][1];
                ob[i].diff = ob[i].a - ob[i].b;
        }

        bubble_sort(ob,costsSize);

        for (i = 0;i<costsSize/2;i++){
            sum += ob[i].a;
        }

        for (i = costsSize/2;i<costsSize;i++){
            sum += ob[i].b;
        }

        return sum;
}


int main()
{
    int a[][2] = {{259,770},{448,54},{926,667},{184,139},{840,118},{577,469}};
    int b;
    printf("%d\n",twoCitySchedCost(a,6,&b));
    return 0;
}

