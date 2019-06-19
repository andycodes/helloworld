#include <stdlib.h>
#include "josephlist.h"
static link head = NULL;
static link tail = NULL;

link make_node(int item)
{
    link p = new node;
    p->item=item;
    p->next=NULL;
    return p;
}

void free_node(link p)
{
   if(p!=NULL)
      free(p);
}

void insert(link p)
{
    if(head == NULL && tail ==NULL){  
        head = p;
        tail = p;
        p->next=head;

    }else{
        tail->next = p;
        tail = p;
        tail->next = head;
    }

}


void delete_node(link p)
{
    link pre;
    if(head==tail&&head==p) {
        head = NULL;
        tail = NULL;
        return;
    }else if(head==tail&&head!=p) {
        printf("impossible\n");
        return;
    }else if(p==head){
        head = head->next;
        tail ->next = head; // IMPORTANT O(∩_∩)O
        return;    
    }   

    for(pre=head;pre;pre=pre->next) {
        if(pre->next == p) {
              pre->next = p->next;
              if(p==tail)  
                  tail=pre;            
              return;
        }
    }
}

void traverse(void (*visit)(link))
{
    link p;

    for(p=head;p!=tail;p=p->next)
        visit(p);
    visit(tail);
}

void destroy(void)
{
    link p= head;
    link q= head; 
    while(p!=tail) {
        q = p;/*temp point*/
        p = p->next;   
        free_node(q);
    }
    if(tail!=NULL)
        free_node(tail);
    head = NULL;
    tail = NULL;
    return;
}

void make_joseph_circle(int m)
{
    if(head!=NULL)
        destroy();
    for(int i=1;i<=m;i++){
        link p =  make_node(i);
        insert(p);
    }
    return;
}

/*链表实现Josephus约瑟夫环问题如下，
输出每轮杀掉的人的编号，并且输出
最后剩下的一名幸运者。*/
int joseph_number(int m, int n)
{
    make_joseph_circle(m);
    link p=head;
    link temp_next=p;
    int count=1;

        while(count<m) {
                for(int i=0;i<n-1;i++) {
                p = p->next;
                }
                printf("%d\t%d\n",count,p->item);
                temp_next = p->next;
                delete_node(p);
                free_node(p);
                p = temp_next;
                count++;
        }

    printf("LUCKY Joseph:%d\n\n",p->item);

    int result = p->item;
    if(p!=NULL)
        free_node(p);
    head=NULL;
    tail=NULL;
    return result;
 
}