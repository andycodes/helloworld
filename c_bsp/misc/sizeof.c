#include <iostream>
using namespace std;

typedef struct __OBJ__
{
    int a;
    int b;
    int c;
}OBJ;

void theFun(char a[])
{
    cout<< "2: " <<sizeof(a) <<endl;
}
int  main()
{
    char a[100]=" ";
    cout<< "1: "<<sizeof(a) <<endl;
    theFun(a);
    cout<< "3: "<<sizeof(a[100]) <<endl;
    cout<< "4: "<<sizeof(OBJ) <<endl;
    cout<< "5: "<<sizeof( struct __OBJ__) <<endl;
    return   0;
}

/*
�����������Ϊ��
1:100
2:4
3��1   //�൱��a[100]�������ռ���ֽڴ�С��Ҳ����һ��char�ֽ�ռ�ô�С
��������Ϊ�����Ĳ������д���ʱ���������Զ��˻�Ϊͬ���͵�ָ�롣��������a�������Ƕ��٣�sizeof(a)ʼ�յ���sizeof(char  *)
*/

