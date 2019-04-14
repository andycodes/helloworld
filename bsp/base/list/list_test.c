#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct mylist {
	int num;
	struct list_head list;
} mylist_t;


static LIST_HEAD(list1);


struct student{
	char name[20];
	char sex;
}stu={"zhangsan",'m'};


int main(int argc, char *argv[])
{
	mylist_t *node1;
	mylist_t *node2;
	mylist_t *pos;
	mylist_t *tmp;
	int cnt = 0;

	node1 = (mylist_t *)malloc(sizeof(mylist_t));
	node1->num = 1;
	list_add(&node1->list, &list1);

	node2 = (mylist_t *)malloc(sizeof(mylist_t));
	node2->num = 2;
	list_add(&node2->list, &list1);

	printf("list_empty is [%d]\n",list_empty(&list1));

	list_for_each_entry_safe(pos,tmp,&list1,list)
	{
		if (pos->num == 1 || pos->num == 2)
		{
			printf("pos->num[%d]\n",pos->num);
			list_del(&pos->list);
		}
	}

	printf("list_empty is [%d]\n",list_empty(&list1));

    return 0;
}


