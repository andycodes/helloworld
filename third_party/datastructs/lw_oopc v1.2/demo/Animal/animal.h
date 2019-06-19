#ifndef ANIMAL_H_INCLUDED_
#define ANIMAL_H_INCLUDED_

#include "lw_oopc.h"

INTERFACE(IMoveable)
{
    void (*move)(IMoveable* t);     // Move��Ϊ
};

ABS_CLASS(Animal)
{
    char name[128];     // ������ǳ�(����С��128���ַ�)
    int age;            // ���������

    void (*setName)(Animal* t, const char* name);   // ���ö�����ǳ�
    void (*setAge)(Animal* t, int age);             // ���ö�������� 
    void (*sayHello)(Animal* t);                    // ������к�
    void (*eat)(Animal* t);                         // ���ﶼ��ԣ����󷽷���������ʵ�֣�
    void (*breathe)(Animal* t);                     // ���ﶼ����������󷽷���������ʵ�֣�
    void (*init)(Animal* t, const char* name, int age); // ��ʼ���ǳƺ�����
};

CLASS(Fish)
{
    EXTENDS(Animal);        // �̳�Animal������
    IMPLEMENTS(IMoveable);  // ʵ��IMoveable�ӿ�

    void (*init)(Fish* t, const char* name, int age);
};

CLASS(Dog)
{
    EXTENDS(Animal);        // �̳�Animal������
    IMPLEMENTS(IMoveable);  // ʵ��IMoveable�ӿ�


    void(*init)(Dog* t, const char* name, int age);
};

CLASS(Car)
{
    IMPLEMENTS(IMoveable);  // ʵ��IMoveable�ӿڣ����Ӳ��Ƕ��������Move��
};

#endif