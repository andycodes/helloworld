#include <stdio.h>
#include <stdlib.h>

//创建一个Student结构
struct Student
{
    char name[30];
    float fScore[3];
}student={"dire",98.5,89.0,93.5}; //初始化结构体变量

void Display(struct Student su) //形参为同类型的结构体(Student结构)
{
    printf("-----Information------\n");
    printf("Name:%s\n",su.name);
    printf("Chinese:%.2f\n",su.fScore[0]);
    printf("Math:%.2f\n",su.fScore[1]);
    printf("English:%.2f\n",su.fScore[2]);
    printf("Average:%.2f\n",(su.fScore[0]+su.fScore[1],su.fScore[2])/3);
}

void Display1(struct Student *pStruct)
{
    printf("------Information-------\n");
    printf("Name:%s\n",pStruct->name);
    printf("Chinese:%.2f\n",(*pStruct).fScore[0]);
    printf("Math:%.2f\n",(*pStruct).fScore[1]);
    printf("English:%.2f\n",pStruct->fScore[2]);
}

int main ()
{
/*这种方式为函数传递参数与普通的变量作为实参是一样的,是值传递*/
/*
在ANSI C标准中允许用结构变量作函数参数进行整体传送。
但是这种传送要将全部成员逐个传送，
特别是成员为数组时将会使传送的时间和空间开销很大，
严重地降低了程序的效率。因此最好的办法就是使用指针，
即用指针变量作函数参数进行传送。这时由实参传向
形参的只是地址，从而减少了时间和空间的开销。
*/
	Display(student);
	Display1(&student);

    return 0;
 }