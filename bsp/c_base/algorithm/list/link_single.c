#include <stdio.h>
#include <stdlib.h>


typedef struct Link{
    int  elem;
    struct Link *next;
}link;


link * initLink(){
    link * p=(link*)malloc(sizeof(link));//����һ��ͷ���
    link * temp=p;//����һ��ָ��ָ��ͷ��㣬���ڱ�������
    //��������
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
    link * temp=p;//������ʱ���temp
    //�����ҵ�Ҫ����λ�õ���һ�����
    for (int i=1; i<add; i++) {
        if (temp==NULL) {
            printf("����λ����Ч\n");
            return p;
        }
        temp=temp->next;
    }
    //����������c
    link * c=(link*)malloc(sizeof(link));
    c->elem=elem;
    //�������в�����
    c->next=temp->next;
    temp->next=c;
    return  p;
}

/*
ɾ�����ĺ�����p�����������add����ɾ���ڵ��λ��
*/
link * delElem(link * p,int add){
    link * temp=p;
    //��������ɾ��������һ�����
    for (int i=1; i<add; i++) {
        temp=temp->next;
    }
    link * del=temp->next;//��������һ��ָ��ָ��ɾ����㣬�Է���ʧ
    temp->next=temp->next->next;//ɾ��ĳ�����ķ������Ǹ���ǰһ������ָ����
    free(del);//�ֶ��ͷŸý�㣬��ֹ�ڴ�й©
    return p;
}


//����ɾ���ڵ�Ϊβ�ڵ�
void delete_node(link * head,link *p_cur_node)
{
    if(p_cur_node != NULL)
    {
        if(p_cur_node->next != NULL)
        {//������ɾ���ڵ�Ϊβ�ڵ�
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
    temp=temp->next;//tampָ����Ԫ���
    //tempָ��ɾ�����
    for (int i=1; i<add; i++) {
        temp=temp->next;
    }
    temp->elem=newElem;
    return p;
}
void display(link *p){
    link* temp=p;//��tempָ������ָ��ͷ���
    //ֻҪtempָ��ָ��Ľ���next����Null����ִ�������䡣
    while (temp->next) {
        temp=temp->next;
        printf("%d",temp->elem);
    }
    printf("\n");
}


