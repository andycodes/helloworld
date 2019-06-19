#ifndef JOSEPHLIST_H
#define JOSEPHLIST_H
#include <stdio.h>
typedef struct node *link;
struct node{
        int item;
        link next;
};
link make_node(int item);
void free_node(link p);
void make_joseph_circle(int m);
int joseph_number(int m, int n);
void insert(link p);
void delete_node(link p);
void traverse(void (*visit)(link));
void destroy(void);
#endif