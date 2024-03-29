/*
sizeof ( x )  
操作符, 操作符, 操作符,  不是函数 ! 

在编译时确定其值,  计算出x在内存中所占字节数. 

 所以, 括号内的赋值和函数, 不会被执行, 编译与执行, 没一分钱联系.
*/

#include <stdio.h>


//  1. sizeof ( 数值 )  
void sizeof_data(void)
{
    char c=8;
    int  i=32;
    printf("%ld ", sizeof(c    ));  // 结果:1, 因为char就是1字节
    printf("%ld ", sizeof(c+i  ));  // 结果:4, i是4字节, 运算时c值被隐式转换成int, 运算值是4字节
    printf("%ld ", sizeof(c=c+i));  // 结果:1, 等同于(c), 编译时, 因为=不被执行, 所以=的右边只是个屁 
}

//  2. sizeof ( 字符 )
void sizeof_char(void)
{
    // 小心, char和'a'在被=动作前, 是两个独立类型, 没关联
    char c = 'a';  
    printf("%ld ", sizeof(c));      // 结果:1, char类型是1字节
    printf("%ld ", sizeof('a'));    // C结果:4，C++结果:1
                                // C99的标准，    'a'是整型字符常量，常量!常量!常量!被看成是int型， 所以占4字节。
                                // ISO C++的标准，'a'是字符字面量  ，被看成是char型，所以占1字节。
}

// 3. sizeof ( 字符串 )
void sizeof_string(void)
{
    printf("%ld ", sizeof("abc")); // 结果:4，双引号会在尾部自动添加转义字符'\0',即数据0X00, 所以是4   
                                // 双引号作用: (1)字符串尾部加0, (2)开辟内存空间, (3)提取地址
}

//4. sizeof ( 数组 )
void sizeof_array(void)
{
    char a[50]="hello";
    printf("%ld ", sizeof(a));      // 结果:50, 返回数组总字节大小
}

/*
5. sizeof ( 指针 )
 sizeof_point,8(64bit) 1
  *p 是 p 指向的内容，*p 的大小是指向内容的大小
*/
void sizeof_point(void)
{
    char *p="hello";
    printf("%s,%zu %zu \n", __func__, sizeof(p), sizeof(*p));     
}

//6. sizeof ( 结构体 )  
// 字节对齐,为快速处理数据,内存是按32位读取写的,而不是一字节一字节地读写
// 结构体的首地址自动对齐至能被对齐字节数大小所整除。
// 结构体每个成员在结构体内的偏移地址都是成员大小的整数倍，否则, 在前方填充byte。
// 结构体的总大小为结构体对齐字节数大小的整数倍

void sizeof_struct(void)
{
struct T1{
    int   a;                  // 成员随意位置
    char  b;
    int   c;
    short d;
}t1;
printf("%ld ", sizeof(t1));   // 结果:16, 4+4+4+4
 
struct T2{
    int   a;                  // 合理安排成员位置
    char  b;
    short d;
    int   c;
}t2;
printf("%ld ", sizeof(t2));     // 结果:12, 4+4+4, 设计结构时，调整成员的位置，可节省存储空间。
}

//7. sizeof ( 函数 )
// 小心, 函数不执行
char Sum(int i, short s)
{return i + s;}

void sizeof_func(void)
{
    printf("%ld ", sizeof(Sum(32, 8)));  // 结果:1, 只会判断返回类型的大小. 函数是不会执行的! 
}

int main(void)
{
    sizeof_data();
    sizeof_char();
    sizeof_string();
    sizeof_array();
    sizeof_point();
    sizeof_struct();
    sizeof_func();
    printf("\n"); 
}