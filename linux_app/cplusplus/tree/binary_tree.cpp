#include <iostream>
#include <stack>
#include <queue>
/** 结点的数据*/
typedef int tree_node_elem_t;
/*
*@struct
*@brief 二叉树结点
*/
struct binary_tree_node_t {
	binary_tree_node_t *left; /* 左孩子*/
	binary_tree_node_t *right; /* 右孩子*/
	tree_node_elem_t elem; /* 结点的数据*/
};


/**
* @brief 先序遍历，递归.
* @param[in] root 根结点
* @param[in] visit 访问数据元素的函数指针
* @return 无
*/
void pre_order_r(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*))
{
	if (root == nullptr) return;
	visit(root);
	pre_order_r(root->left, visit);
	pre_order_r(root->right, visit);
}


/**
* @brief 中序遍历，递归.
*/
void in_order_r(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*)) {
	if(root == nullptr) return;
	in_order_r(root->left, visit);
	visit(root);
	in_order_r(root->right, visit);
}


/**
* @brief 后序遍历，递归.
*/
void post_order_r(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*))
{
	if(root == nullptr) return;
	post_order_r(root->left, visit);
	post_order_r(root->right, visit);
	visit(root);
}


/**
* @brief 先序遍历，非递归.
*/
void pre_order(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*))
{
	const binary_tree_node_t *p;
	stack<const binary_tree_node_t *> s;
	p = root;
	if(p != nullptr) s.push(p);
	while(!s.empty()) {
		p = s.top();
		s.pop();
		visit(p);
		if(p->right != nullptr) s.push(p->right);
		if(p->left != nullptr) s.push(p->left);
	}
}


/**
* @brief 中序遍历，非递归.
*/
void in_order(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*))
{
	const binary_tree_node_t *p;
	stack<const binary_tree_node_t *> s;
	p = root;
	while(!s.empty() || p!=nullptr) {
		if(p != nullptr) {
			s.push(p);
			p = p->left;
		} else {
			p = s.top();
			s.pop();
			visit(p);
			p = p->right;
		}
	}
}


/**
* @brief 后序遍历，非递归.
*/
void post_order(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*))
{
	/* p，正在访问的结点，q，刚刚访问过的结点*/
	const binary_tree_node_t *p, *q;
	stack<const binary_tree_node_t *> s;
	p = root;
	do {
		while(p != nullptr) { /* 往左下走*/
			s.push(p);
			p = p->left;
		}
		q = nullptr;
		while(!s.empty()) {
			p = s.top();
			s.pop();
			/* 右孩子不存在或已被访问，访问之*/
			if(p->right == q) {
				visit(p);
				q = p; /* 保存刚访问过的结点*/
			} else {
				/* 当前结点不能访问，需第二次进栈*/
				s.push(p);
				/* 先处理右子树*/
				p = p->right;
				break;
			}
		}
	} while(!s.empty());
}


/**
* @brief 层次遍历，也即BFS.
**
跟先序遍历一模一样，唯一的不同是栈换成了队列
*/
void level_order(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*))
{
	const binary_tree_node_t *p;
	queue<const binary_tree_node_t *> q;
	p = root;
	if(p != nullptr) q.push(p);
	while(!q.empty()) {
		p = q.front();
		q.pop();
		visit(p);
		/* 先左后右或先右后左无所谓*/
		if(p->left != nullptr) q.push(p->left);
		if(p->right != nullptr) q.push(p->right);
	}
}