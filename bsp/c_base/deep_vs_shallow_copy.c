//C�����е������ǳ����
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
    //��˵��s1��s2�г�Աchar *title;ֻ��ǳ����������ָ��ָ��ͬһ����ڴ棬
    //���ͷ�free(s1.title);ʱ��s2.titleָ����ڴ�ռ�Ҳ�ͷ��ˣ������ٴ��ͷŻᱨ��
    if (s1.title != NULL)
    {
        free(s1.title);
    }
    //�������
    /*if (s2.title != NULL)
    {
        free(s2.title);
    }*/

/*
    //Ҫ��ʵ���������ô�����s2.titleҲ����һ���ڴ�ռ䣬
    //Ȼ��ͨ��strcpy()��s2.titleָ����ַ������Ƶ�s2.titleָ����ڴ�ռ���
    �ɴ�֤�����ṹ��֮��ĸ�ֵ��s2 = s1;����
    �ǽ����˽ṹ���ڲ��������ݵĿ���,
    //����s1.name�ĵ�ַs2.name�ĵ�ַ��ͬ��
    ˵���ǰ�s1.name�е����ݸ��Ƶ���s2.name��
*/
}