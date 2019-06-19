#include <stdio.h>
#include <string.h>

// ��ýṹ��(TYPE)�ı�����Ա(MEMBER)�ڴ˽ṹ���е�ƫ������
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

// ����"�ṹ��(type)����"�е�"���Ա����(member)��ָ��(ptr)"����ȡָ�������ṹ�������ָ��
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

struct student
{
	char gender;
	int id;
	int age;
	char name[20];
};

void main()
{
	struct student stu;
	struct student *pstu;

	stu.gender = '1';
	stu.id = 9527;
	stu.age = 24;
	strcpy(stu.name, "zhouxingxing");

	// ����"id��ַ" ��ȡ "�ṹ��ĵ�ַ"��
	pstu = container_of(&stu.id, struct student, id);

	// ���ݻ�ȡ���Ľṹ��student�ĵ�ַ������������Ա
	printf("gender= %c\n", pstu->gender);
	printf("age= %d\n", pstu->age);
	printf("name= %s\n", pstu->name);
}
