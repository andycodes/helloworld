/** @file threaded_binary_tree.c
* @brief 线索二叉树.
*/
#include <stddef.h> /* for NULL */
#include <stdio.h>
/* 结点数据的类型. */
typedef int elem_t;
/**
*@struct
*@brief 线索二叉树结点.
*/
typedef struct tbt_node_t {
	int ltag; /** 1 表示是线索，0 表示是孩子*/
	int rtag; /** 1 表示是线索，0 表示是孩子*/
	struct tbt_node_t *left; /** 左孩子*/
	struct tbt_node_t *right; /** 右孩子*/
	elem_t elem; /** 结点所存放的数据*/
}tbt_node_t;
/* 内部函数*/
static void in_thread(tbt_node_t *p, tbt_node_t **pre);
static tbt_node_t *first(tbt_node_t *p);
static tbt_node_t *next(const tbt_node_t *p);
/**
* @brief 建立中序线索二叉树.
* @param[in] root 树根
* @return 无
*/
void create_in_thread(tbt_node_t *root) {
	/* 前驱结点指针*/
	tbt_node_t *pre=NULL;
	if(root != NULL) { /* 非空二叉树，线索化*/
	/* 中序遍历线索化二叉树*/
	in_thread(root, &pre);
	/* 处理中序最后一个结点*/
	pre->right = NULL;
	pre->rtag = 1;
	}
}
/**
* @brief 在中序线索二叉树上执行中序遍历.
* @param[in] root 树根
* @param[in] visit 访问结点的数据的函数
* @return 无
*/
void in_order(tbt_node_t *root, int(*visit)(tbt_node_t*)) {
tbt_node_t *p;
for(p = first(root); p != NULL; p = next(p)) {
visit(p);
}
}
/*
* @brief 中序线索化二叉树的主过程.
* @param[in] p 当前要处理的结点
* @param[inout] pre 当前结点的前驱结点
* @return 无
*/
static void in_thread(tbt_node_t *p, tbt_node_t **pre) {
	if(p != NULL) {
		in_thread(p->left, pre); /* 线索化左子树*/
		if(p->left == NULL) { /* 左子树为空，建立前驱*/
		p->left = *pre;
		p->ltag = 1;
		}
		/* 建立前驱结点的后继线索*/
		if((*pre) != NULL &&
		(*pre)->right == NULL) {
		(*pre)->right = p;
		(*pre)->rtag = 1;
		}
		*pre = p; /* 更新前驱*/
		in_thread(p->right, pre); /* 线索化右子树*/
	}
}
/*
* @brief 寻找线索二叉树的中序下的第一个结点.
* @param[in] p 线索二叉树中的任意一个结点
* @return 此线索二叉树的第一个结点
*/
static tbt_node_t *first(tbt_node_t *p) {
	if(p == NULL) return NULL;
	while(p->ltag == 0) {
	p = p->left; /* 最左下结点，不一定是叶结点*/
	}
	return p;
}
/*
* @brief 求中序线索二叉树中某结点的后继.
* @param[in] p 某结点
* @return p 的后继
*/
static tbt_node_t *next(const tbt_node_t *p) {
	if(p->rtag == 0) {
	return first(p->right);
	} else {
	return p->right;
	}
}