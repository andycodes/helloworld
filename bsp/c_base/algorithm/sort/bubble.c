#include <iostream>

using namespace std;

/*Bubble  ð������*/
/*�㷨˼���������

��Ҫ�����һ�����У��Ե�ǰ��δ�ź���ķ�Χ�ڵ�ȫ����������
���¶����ڵ����������ν��бȽϺ͵������ýϴ�������³�����
С������ð������ÿ�������ڵ����ȽϺ������ǵ�����������Ҫ
���෴ʱ���ͽ����ǻ�����

������һ�ָĽ���ð���㷨������¼��ÿһ��ɨ�������³�����
λ��k���������Լ������ѭ��ɨ��Ĵ�����

ð���������ȶ��ġ��㷨ʱ�临�Ӷ�O(n2)--[n��ƽ��]
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



