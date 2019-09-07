#include <iostream>

using namespace std;

/*Bubble  冒泡排序*/
/*算法思想简单描述：

在要排序的一组数中，对当前还未排好序的范围内的全部数，自上
而下对相邻的两个数依次进行比较和调整，让较大的数往下沉，较
小的往上冒。即：每当两相邻的数比较后发现它们的排序与排序要
求相反时，就将它们互换。

下面是一种改进的冒泡算法，它记录了每一遍扫描后最后下沉数的
位置k，这样可以减少外层循环扫描的次数。

冒泡排序是稳定的。算法时间复杂度O(n2)--[n的平方]
*/
void bubble_sort(int* data,int size)
{
    for (int i=size;i>0;i--)
    {
        for (int j=0;j<(i-1);j++)
            {
                if (data[j]>data[j+1])
                    {
                        int tmp;
                        tmp=data[j];
                        data[j]=data[j+1];
                        data[j+1]=tmp;
                    }
            }
       }
}

int main()
{
    int a[5] = {5,6,8,3,7};
    
    bubble_sort(a,5);

    for(int i =0;i<5;i++)
    {
      cout<<a[i]<<" ";
    }

    cout<<endl;
}



