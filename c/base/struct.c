#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief The Student struct
 * 定义 结构体 数据类型 , 同时为该结构体类型声明 别名
 * 可以直接使用 别名 结构体变量名 声明结构体类型变量
 * 不需要在前面添加 struct 关键字
 */
typedef struct Student
{
    char name[5];
    int age;
    int id;
}Student;


/**
 * @brief main
 * @return
 */
int main()
{
    // 声明结构体变量 , 同时进行初始化操作
    Student s1 = {"Tom", 18, 1};

    // 声明结构体变量 , 不进行初始化
    Student s2;

    // 将结构体变量 s1 赋值给 结构体变量 s2
    s2 = s1;

    // 打印 s2 结构体的值
    printf("name = %s, age = %d, id = %d\n", s2.name, s2.age, s2.id);
    // 打印两个结构体变量的地址值 , 上述赋值不是地址赋值 , 而是实际的值之间进行的赋值
    printf("s1 address = %d, s2 address = %d\n", &s1, &s2);

    // 由上面的 s2 打印结果可知 , 将 s1 结构体变量赋值给 s2 结构体变量
    // 会为 s2 的每个 结构体成员 进行赋值
    // 将 s1 结构体的 成员 取出 并赋值给 s2 结构体 的 相应成员

    return 0;
}