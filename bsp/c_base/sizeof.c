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
程序的输出结果为：
1:100
2:4
3：1   //相当于a[100]这个数所占的字节大小，也就是一个char字节占得大小
当数组作为函数的参数进行传递时，该数组自动退化为同类型的指针。不论数组a的容量是多少，sizeof(a)始终等于sizeof(char  *)
*/

