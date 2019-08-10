//C语言中的深拷贝和浅拷贝
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct _student{
    char name[30];
    char *title;
    int age;
}Student;


void main(){
    Student s1;
    Student s2;
    s1.age = 12;
    strcpy(s1.name, "fan");
    s1.title = (char *)malloc(sizeof(char)* 30);
    strcpy(s1.title, "sai");


    s2 = s1;


    printf("s1  age=%d,s1 name=%s,s1 title=%s\n", s1.age, s1.name, s1.title);
    printf("s1  age=%d,s2 name=%s,s2 title=%s\n", s2.age, s2.name, s2.title);


    printf("s1 addr %x\n", s1.name);
    printf("s2 addr %x\n", s2.name);
    printf("s1 addr %x\n", s1.title);
    printf("s2 addr %x\n", s2.title);
    printf("s1 addr %x\n", &s1.age);
    printf("s2 addr %x\n", &s2.age);
    //这说明s1和s2中成员char *title;只是浅拷贝，两个指针指向同一块堆内存，
    //当释放free(s1.title);时，s2.title指向的内存空间也释放了，所以再次释放会报错
    if (s1.title != NULL)
    {
        free(s1.title);
    }
    //错误代码
    /*if (s2.title != NULL)
    {
        free(s2.title);
    }*/

/*
    //要想实现深拷贝，那么必须给s2.title也分配一段内存空间，
    //然后通过strcpy()将s2.title指向的字符串复制到s2.title指向的内存空间内
    由此证明，结构体之间的赋值（s2 = s1;），
    是进行了结构体内部所有数据的拷贝,
    //如上s1.name的地址s2.name的地址不同，
    说明是把s1.name中的数据复制到了s2.name中
*/
}