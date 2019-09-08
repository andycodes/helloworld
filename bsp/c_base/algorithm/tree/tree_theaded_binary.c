/** @file threaded_binary_tree.c
* @brief ����������.
*/
#include <stddef.h> /* for NULL */
#include <stdio.h>
/* ������ݵ�����. */
typedef int elem_t;
/**
*@struct
*@brief �������������.
*/
typedef struct tbt_node_t {
	int ltag; /** 1 ��ʾ��������0 ��ʾ�Ǻ���*/
	int rtag; /** 1 ��ʾ��������0 ��ʾ�Ǻ���*/
	struct tbt_node_t *left; /** ����*/
	struct tbt_node_t *right; /** �Һ���*/
	elem_t elem; /** �������ŵ�����*/
}tbt_node_t;
/* �ڲ�����*/
static void in_thread(tbt_node_t *p, tbt_node_t **pre);
static tbt_node_t *first(tbt_node_t *p);
static tbt_node_t *next(const tbt_node_t *p);
/**
* @brief ������������������.
* @param[in] root ����
* @return ��
*/
void create_in_thread(tbt_node_t *root) {
	/* ǰ�����ָ��*/
	tbt_node_t *pre=NULL;
	if(root != NULL) { /* �ǿն�������������*/
	/* �������������������*/
	in_thread(root, &pre);
	/* �����������һ�����*/
	pre->right = NULL;
	pre->rtag = 1;
	}
}
/**
* @brief ������������������ִ���������.
* @param[in] root ����
* @param[in] visit ���ʽ������ݵĺ���
* @return ��
*/
void in_order(tbt_node_t *root, int(*visit)(tbt_node_t*)) {
tbt_node_t *p;
for(p = first(root); p != NULL; p = next(p)) {
visit(p);
}
}
/*
* @brief ������������������������.
* @param[in] p ��ǰҪ����Ľ��
* @param[inout] pre ��ǰ����ǰ�����
* @return ��
*/
static void in_thread(tbt_node_t *p, tbt_node_t **pre) {
	if(p != NULL) {
		in_thread(p->left, pre); /* ������������*/
		if(p->left == NULL) { /* ������Ϊ�գ�����ǰ��*/
		p->left = *pre;
		p->ltag = 1;
		}
		/* ����ǰ�����ĺ������*/
		if((*pre) != NULL &&
		(*pre)->right == NULL) {
		(*pre)->right = p;
		(*pre)->rtag = 1;
		}
		*pre = p; /* ����ǰ��*/
		in_thread(p->right, pre); /* ������������*/
	}
}
/*
* @brief Ѱ�������������������µĵ�һ�����.
* @param[in] p �����������е�����һ�����
* @return �������������ĵ�һ�����
*/
static tbt_node_t *first(tbt_node_t *p) {
	if(p == NULL) return NULL;
	while(p->ltag == 0) {
	p = p->left; /* �����½�㣬��һ����Ҷ���*/
	}
	return p;
}
/*
* @brief ������������������ĳ���ĺ��.
* @param[in] p ĳ���
* @return p �ĺ��
*/
static tbt_node_t *next(const tbt_node_t *p) {
	if(p->rtag == 0) {
	return first(p->right);
	} else {
	return p->right;
	}
}