#include <stdio.h>
#include <string.h>

#include "macro.h"


#define ALREADY_DEFINED_MACRO	(1)



struct student
{
	char gender;
	int id;
	int age;
	char name[20];
};


void testcase_offset(void)
{
	int gender_offset, id_offset, age_offset, name_offset;

	gender_offset = offsetof(struct student, gender);
	id_offset = offsetof(struct student, id);
	age_offset = offsetof(struct student, age);
	name_offset = offsetof(struct student, name);

	printf("gender_offset = %d\n", gender_offset);
	printf("id_offset = %d\n", id_offset);
	printf("age_offset = %d\n", age_offset);
	printf("name_offset = %d\n", name_offset);
}


void testcase_container_of(void)
{
	struct student stu;
	struct student *pstu;

	stu.gender = '1';
	stu.id = 9527;
	stu.age = 24;
	strcpy(stu.name, "zhouxingxing");

	// 根据"id地址" 获取 "结构体的地址"。
	pstu = container_of(&stu.id, struct student, id);

	// 根据获取到的结构体student的地址，访问其它成员
	printf("gender= %c\n", pstu->gender);
	printf("age= %d\n", pstu->age);
	printf("name= %s\n", pstu->name);
}




int main()
{
	int create_1m(int) = 0;
	printf("LINK_MULTIPLE [%s]\n",mkstr(a));


/*UNDEFINED_MACRO 没有定义，但是在#if不会编译报错*/
#if (UNDEFINED_MACRO != ALREADY_DEFINED_MACRO)
	printf("UNDEFINED_MACRO:Compiling does not report errors\n ");
#endif



	testcase_offset();
	testcase_container_of();

	return 0;
}



