#include <iostream>
#include <stack>
#include <queue>
/** ��������*/
typedef int tree_node_elem_t;
/*
*@struct
*@brief ���������
*/
struct binary_tree_node_t {
	binary_tree_node_t *left; /* ����*/
	binary_tree_node_t *right; /* �Һ���*/
	tree_node_elem_t elem; /* ��������*/
};


/**
* @brief ����������ݹ�.
* @param[in] root �����
* @param[in] visit ��������Ԫ�صĺ���ָ��
* @return ��
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
* @brief ����������ݹ�.
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
* @brief ����������ݹ�.
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
* @brief ����������ǵݹ�.
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
* @brief ����������ǵݹ�.
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
* @brief ����������ǵݹ�.
*/
void post_order(
const binary_tree_node_t *root,
int (*visit)(const binary_tree_node_t*))
{
	/* p�����ڷ��ʵĽ�㣬q���ոշ��ʹ��Ľ��*/
	const binary_tree_node_t *p, *q;
	stack<const binary_tree_node_t *> s;
	p = root;
	do {
		while(p != nullptr) { /* ��������*/
			s.push(p);
			p = p->left;
		}
		q = nullptr;
		while(!s.empty()) {
			p = s.top();
			s.pop();
			/* �Һ��Ӳ����ڻ��ѱ����ʣ�����֮*/
			if(p->right == q) {
				visit(p);
				q = p; /* ����շ��ʹ��Ľ��*/
			} else {
				/* ��ǰ��㲻�ܷ��ʣ���ڶ��ν�ջ*/
				s.push(p);
				/* �ȴ���������*/
				p = p->right;
				break;
			}
		}
	} while(!s.empty());
}


/**
* @brief ��α�����Ҳ��BFS.
**
���������һģһ����Ψһ�Ĳ�ͬ��ջ�����˶���
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
		/* ������һ����Һ�������ν*/
		if(p->left != nullptr) q.push(p->left);
		if(p->right != nullptr) q.push(p->right);
	}
}