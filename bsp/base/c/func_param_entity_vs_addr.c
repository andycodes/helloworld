#include <stdio.h>
#include <stdlib.h>

//����һ��Student�ṹ
struct Student
{
    char name[30];
    float fScore[3];
}student={"dire",98.5,89.0,93.5}; //��ʼ���ṹ�����

void Display(struct Student su) //�β�Ϊͬ���͵Ľṹ��(Student�ṹ)
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
/*���ַ�ʽΪ�������ݲ�������ͨ�ı�����Ϊʵ����һ����,��ֵ����*/
/*
��ANSI C��׼�������ýṹ���������������������崫�͡�
�������ִ���Ҫ��ȫ����Ա������ͣ�
�ر��ǳ�ԱΪ����ʱ����ʹ���͵�ʱ��Ϳռ俪���ܴ�
���صؽ����˳����Ч�ʡ������õİ취����ʹ��ָ�룬
����ָ������������������д��͡���ʱ��ʵ�δ���
�βε�ֻ�ǵ�ַ���Ӷ�������ʱ��Ϳռ�Ŀ�����
*/
	Display(student);
	Display1(&student);

    return 0;
 }