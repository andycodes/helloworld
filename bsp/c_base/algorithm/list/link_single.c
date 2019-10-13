#include <stdio.h>
#include <stdlib.h>


typedef struct Link{
    int  elem;
    struct Link *next;
}link;


link * initLink(){
    link * p=(link*)malloc(sizeof(link));//创建一个头结点
    link * temp=p;//声明一个指针指向头结点，用于遍历链表
    //生成链表
    for (int i=1; i<5; i++) {
        link *a=(link*)malloc(sizeof(link));
        a->elem=i;
        a->next=NULL;
        temp->next=a;
        temp=temp->next;
    }
    return p;
}
link * insertElem(link * p,int elem,int add){
    link * temp=p;//创建临时结点temp
    //首先找到要插入位置的上一个结点
    for (int i=1; i<add; i++) {
        if (temp==NULL) {
            printf("插入位置无效\n");
            return p;
        }
        temp=temp->next;
    }
    //创建插入结点c
    link * c=(link*)malloc(sizeof(link));
    c->elem=elem;
    //向链表中插入结点
    c->next=temp->next;
    temp->next=c;
    return  p;
}

/*
删除结点的函数，p代表操作链表，add代表删除节点的位置
*/
link * delElem(link * p,int add){
    link * temp=p;
    //遍历到被删除结点的上一个结点
    for (int i=1; i<add; i++) {
        temp=temp->next;
    }
    link * del=temp->next;//单独设置一个指针指向被删除结点，以防丢失
    temp->next=temp->next->next;//删除某个结点的方法就是更改前一个结点的指针域
    free(del);//手动释放该结点，防止内存泄漏
    return p;
}


//考虑删除节点为尾节点
void delete_node(link * head,link *p_cur_node)
{
    if(p_cur_node != NULL)
    {
        if(p_cur_node->next != NULL)
        {//不考虑删除节点为尾节点
            link * pTemp = p_cur_node->next;
            p_cur_node->elem = pTemp->elem;
            p_cur_node->next = pTemp->next;
            free(pTemp);
        }
        else
        {
            link * temp = head;
            while(temp != NULL)
            {
                if(temp->next == p_cur_node)
                {
                    free(p_cur_node);
                    temp->next = NULL;
                }
                temp = temp->next;
            }
        }
    }
}


link *delete_node1(link *head,int key)
{
	link *node1=head;
	link *node2=NULL;
	if (head==NULL)
	{
		return NULL;
	}
	else
	{
		if (node1->elem==key)
		{
			head=head->next;
			free(node1);
			return head;
		}
		else
		{
			while (node1!=NULL)
			{
				node2=node1;
				node2=node2->next;
				if (node2->elem==key)
				{
					node1->next=node2->next;
					free(node2);
					break;
				}
				node1=node1->next;
			}
			return head;
		}
    }
}

int selectElem(link * p,int elem){
    link * t=p;
    int i=1;
    while (t->next) {
        t=t->next;
        if (t->elem==elem) {
            return i;
        }
        i++;
    }
    return -1;
}
link *amendElem(link * p,int add,int newElem){
    link * temp=p;
    temp=temp->next;//tamp指向首元结点
    //temp指向被删除结点
    for (int i=1; i<add; i++) {
        temp=temp->next;
    }
    temp->elem=newElem;
    return p;
}
void display(link *p){
    link* temp=p;//将temp指针重新指向头结点
    //只要temp指针指向的结点的next不是Null，就执行输出语句。
    while (temp->next) {
        temp=temp->next;
        printf("%d",temp->elem);
    }
    printf("\n");
}


