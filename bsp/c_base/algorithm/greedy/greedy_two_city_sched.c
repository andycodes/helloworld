#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
我们这样来看这个问题，公司首先将这 2N 个人全都安排飞往 B 市，
再选出 N 个人改变它们的行程，让他们飞往 A 市。
如果选择改变一个人的行程，那么公司将会额外付出 price_A - price_B 的费用，
这个费用可正可负。


因此最优的方案是，选出 price_A - price_B 最小的 N 个人，
让他们飞往 A 市，其余人飞往 B 市。
算法按照 price_A - price_B 从小到大排序；
将前 N 个人飞往 A 市，其余人飞往 B 市，
并计算出总费用。
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

