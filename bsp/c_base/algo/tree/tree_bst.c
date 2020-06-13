#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*  Definition for a binary tree node.*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


/*
����һ��������������ͬʱ������С�߽�L?��
���߽�?R��ͨ���޼�������������ʹ������
�ڵ��ֵ��[L, R]�� (R>=L) ���������Ҫ�ı����ĸ��ڵ㣬
���Խ��Ӧ�������޼��õĶ������������µĸ��ڵ㡣

����:
    1
   / \
  0   2

  L = 1
  R = 2

���:
    1
      \
       2


*/

struct TreeNode* trimBST(struct TreeNode* root, int L, int R){
        if (root ==  NULL) return root;
        if (root->val > R) return trimBST(root->left, L, R);
        if (root->val < L) return trimBST(root->right, L, R);

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
}


/*
 ���������������С����

����������������������������顣
��������������� root = [4,2,6,1,3,null,null]��
��������Ľ������ [1, 2, 3, 4, 6]��
��ĿҪ������������С���룬
����Ҫ�������������������
����Ԫ�ز����Сֵ��

*/


int ret = 2147483647;
bool first = true;
int last;//��һ������ֵ
void help(struct TreeNode* root)
{
    if(root)
    {
        //������
        help(root->left);

        //��ǰ��㴦��
        if(!first)
            ret = min(ret, abs(root->val - last));
        else
        {
            first = false;
        }
        last = root->val;

        //������
        help(root->right);
    }
}



int minDiffInBST(struct TreeNode* root){
     ret = 2147483647;
    first = true;
    help(root);
    return ret;
}

/*
����һ���������������������������
ʹ��������ߵĽ�����������ĸ���
����ÿ�����û�����ӽ�㣬ֻ��һ�����ӽ�㡣

ʾ�� ��

���룺[5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

�����[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9

*/
struct TreeNode* increasingBST(struct TreeNode* root){
	if (root == NULL)
		return NULL;

	struct TreeNode* ans = root;

	if (root->right != NULL)
		root->right = increasingBST(root->right);

	if (root->left != NULL){
		ans = increasingBST(root->left);
		struct TreeNode* ans1 = ans;
		while(ans1->right != NULL)
			ans1 = ans1->right;
		ans1->right = root;
		root->left = NULL;
	}

	return ans;
}


/*
��һ�������������е��������飬
ת��Ϊһ�ø߶�ƽ�������������

�����У�һ���߶�ƽ���������ָ
һ��������ÿ���ڵ� ����������������
�߶Ȳ�ľ���ֵ������ 1��

ʾ��:

������������: [-10,-3,0,5,9],

һ�����ܵĴ��ǣ�[0,-3,9,-10,null,5]��
�����Ա�ʾ��������߶�ƽ�������������

      0
     / \
   -3   9
   /   /
 -10  5
*/
struct TreeNode* ToBST(int nums[],int left,int right){
	if(left>right)return NULL;//����Ķ�������Ϊ[left,right]���޷����м����ݹ飬ֱ���˳�
	int mid = (int)(left+right)/2;//������ֵ
	struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
	root->left = ToBST(nums,left,mid-1);//ע��mid-1 ����벿�ֽ��еݹ�
	root->right = ToBST(nums,mid+1,right);//ע��mid+1 ���Ұ벿�ֽ��еݹ�
	return root;
}


struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    return ToBST(nums,0,numsSize-1);
}

/*
����һ��������������
��дһ������ kthSmallest ���������е� k ����С��Ԫ�ء�

˵����
����Լ��� k ������Ч�ģ�1 �� k �� ����������Ԫ�ظ�����

*/
/*�������(������)+��ǰ��ֹ*/
void dfs(struct TreeNode* root, int k, int *cnt, int *ret)
{
    if(root == NULL)
        return;

    dfs(root->left, k, cnt, ret);
    if(++ (*cnt) ==k) {
        *ret = root->val;
        return;
    }
    dfs(root->right, k, cnt, ret);
}

int kthSmallest(struct TreeNode* root, int k){
    int ret = 0;
    int i = 0;
    dfs(root,k, &i,&ret);
    return ret;
}

/*
����һ�����������������е�ĳһ����㣬�����ҳ��ý��������˳���̵Ľڵ㡣

��� p �ĺ����ֵ�� p.val ��Ľ���м�ֵ��С�Ľ�㡣



ʾ�� 1:



����: root = [2,1,3], p = 1
���: 2
����: ���� 1 ��˳������ 2����ע�� p �ͷ���ֵ��Ӧ�� TreeNode ���͡�

*/
/*
�ݹ�ִ������������ڵݹ�����л�ȡx����һ���������ǰֵ��<=x�ģ���ô����BST������ֻ��Ҫ�����������ҡ������ǰֵ>x����ǰֵ�п��ܣ�����������Ҳ�п����и�С�ĵ���Ҳ>x�ģ������ӵݹ��ѡ����ӽ��ģ���С��).
ʱ��O(logN)���ռ�O(logN)����ջ����ȡ�
*/
struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p) {
	if (root == NULL || p == NULL) {
		return NULL;
	}

	//��ǰ����߶�������>p
	if (root->val <= p->val) {
		return inorderSuccessor(root->right, p);
	}

	//root>p
	struct TreeNode* tmp = inorderSuccessor(root->left, p);
	if (tmp != NULL && tmp->val < root->val) {
		return tmp;
	}
	else {
		return root;
	}
}

/*
ѭ��ʵ��
�����ǰֵ��<=x�ģ���ô����BST������ֻ��Ҫ�����������ң�cur=cur.right��
�����ǰֵ>x����ǰֵ�п��ܣ�����������Ҳ�п����и�С�ĵ���Ҳ>x�ġ���ÿ�����������֧ʱ����ǰ����һ����ѡ�㣬��¼�ýڵ��ֵ����ʷ��С�ڵ��ֵ��
ʱ��O(logN)���ռ�O(1��

*/
struct rootNode* inorderSuccessor(struct rootNode* root, struct rootNode* p) {
	if (root == NULL || p == NULL) {
		return NULL;
	}

	struct rootNode* cur = root;
	struct rootNode* res = NULL;

	while (cur != NULL) {
		if (cur->val <= p->val) {
			cur = cur->right;
		} else {
			if (res == NULL || res->val > cur->val) {
				res = cur;
			}
			cur = cur->left;
		}
	}

	return res;
}

/*
98. ��֤����������
����һ�����������ж����Ƿ���һ����Ч�Ķ�����������

����һ��������������������������

�ڵ��������ֻ����С�ڵ�ǰ�ڵ������
�ڵ��������ֻ�������ڵ�ǰ�ڵ������
�������������������������Ҳ�Ƕ�����������
*/
bool dfs(struct TreeNode* root, long low, long high) {
	if (root == NULL)
	return true;

	long num = root->val;
	if (num <= low || num >= high)
		return false;

    return dfs(root->left, low, num) && dfs(root->right, num, high);
}
bool isValidBST(struct TreeNode* root){
    return dfs(root, LONG_MIN, LONG_MAX);
}

/*

��һ�ֽⷨ
�������Ч��BST������ô��List�����ظ�Ԫ��������ġ�

*/
struct TreeNode* pre = NULL;

bool dfs(struct TreeNode* root) {
    if (root == NULL)
		return true;

	if (!dfs(root->left))
		return false;

	if (pre != NULL && pre->val >= root->val)
		return false;

	pre = root;

	return dfs(root->right);
}

bool isValidBST(struct TreeNode* root){
	pre = NULL;
	return dfs(root);
}

/**
���������(Binary Search Tree)��
(��:����������������������)��������һ�ÿ�����
�����Ǿ����������ʵĶ�����:
���������������գ�
�������������н���ֵ��С�����ĸ�����ֵ;
���������������գ�
�������������н���ֵ���������ĸ�����ֵ;
������������Ҳ�ֱ�Ϊ������������
 */

#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

typedef int Type;

typedef struct BSTreeNode{
	Type   key;					// �ؼ���(��ֵ)
	struct BSTreeNode *left;	// ����
	struct BSTreeNode *right;	// �Һ���
	struct BSTreeNode *parent;	// �����
}Node, *BSTree;

/*
 * ǰ�����"������"
 ǰ����� - ��->��->��
 */
void preorder_bstree(BSTree tree)
{
	if(tree != NULL)
	{
		printf("%d ", tree->key);
		preorder_bstree(tree->left);
		preorder_bstree(tree->right);
	}
}

/*
 * �������"������"
 ������� - ��->��->��
 */
void inorder_bstree(BSTree tree)
{
	if(tree != NULL)
	{
		inorder_bstree(tree->left);
		printf("%d ", tree->key);
		inorder_bstree(tree->right);
	}
}

/*
 * �������"������"
 ������� - ��->��->��
 */
void postorder_bstree(BSTree tree)
{
	if(tree != NULL)
	{
		postorder_bstree(tree->left);
		postorder_bstree(tree->right);
		printf("%d ", tree->key);
	}
}

/*
 * (�ݹ�ʵ��)����"������x"�м�ֵΪkey�Ľڵ�
 */
Node* bstree_search(BSTree x, Type key)
{
	if (x==NULL || x->key==key)
		return x;

	if (key < x->key)
		return bstree_search(x->left, key);
	else
		return bstree_search(x->right, key);
}

/*
 * (�ǵݹ�ʵ��)����"������x"�м�ֵΪkey�Ľڵ�
 */
Node* iterative_bstree_search(BSTree x, Type key)
{
	while ((x!=NULL) && (x->key!=key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

/*
 * ������С��㣺����treeΪ�����Ķ���������С��㡣
 */
Node* bstree_minimum(BSTree tree)
{
	if (tree == NULL)
		return NULL;

	while(tree->left != NULL)
		tree = tree->left;
	return tree;
}

/*
 * ��������㣺����treeΪ�����Ķ�����������㡣
 */
Node* bstree_maximum(BSTree tree)
{
	if (tree == NULL)
		return NULL;

	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}

/*
 * �ҽ��(x)�ĺ�̽�㡣��������"������������ֵ���ڸý��"��"��С���"��
 */
Node* bstree_successor(Node *x)
{
	// ���x�����Һ��ӣ���"x�ĺ�̽��"Ϊ "�����Һ���Ϊ������������С���"��
	if (x->right != NULL)
		return bstree_minimum(x->right);

    // ���xû���Һ��ӡ���x���������ֿ��ܣ�
	// (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
	// (02) x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
	Node* y = x->parent;
	while ((y!=NULL) && (x==y->right))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 * �ҽ��(x)��ǰ����㡣��������"������������ֵС�ڸý��"��"�����"��
 */
Node* bstree_predecessor(Node *x)
{
	// ���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ���������������"��
	if (x->left != NULL)
		return bstree_maximum(x->left);

    // ���xû�����ӡ���x���������ֿ��ܣ�
	// (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
	// (01) x��"һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
	Node* y = x->parent;
	while ((y!=NULL) && (x==y->left))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 * ���������ض�������㡣
 *
 * ����˵����
 *     key �Ǽ�ֵ��
 *     parent �Ǹ���㡣
 *     left �����ӡ�
 *     right ���Һ��ӡ�
 */
static Node* create_bstree_node(Type key, Node *parent, Node *left, Node* right)
{
	Node* p;

	if ((p = (Node *)malloc(sizeof(Node))) == NULL)
		return NULL;
	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;

	return p;
}

/*
701. �����������еĲ������
 * �������뵽��������
 */
struct TreeNode* insertIntoBST(struct TreeNode* root, int val)
{
	struct TreeNode* y = NULL;
	struct TreeNode* x = root;

	while(x != NULL) {
		y = x;
		if (val < x->val)
			x = x->left;
		else
			x = x->right;
	}

	struct TreeNode* node = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
	node->val = val;
	if (y == NULL)
		root = node;
	else if (node->val < y->val)
		y->left = node;
	else
		y->right = node;

	return root;
}

/*
 * ɾ�����(z)�������ظ��ڵ�
 *
 * ����˵����
 *     tree �������ĸ����
 *     z ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�
 */
static Node* bstree_delete(BSTree tree, Node *z)
{
	Node *x=NULL;
    Node *y=NULL;

	if ((z->left == NULL) || (z->right == NULL) )
		y = z;
	else
		y = bstree_successor(z);

	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;

	if (x != NULL)
		x->parent = y->parent;

	if (y->parent == NULL)
		tree = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if (y != z)
		z->key = y->key;

	if (y!=NULL)
		free(y);

	return tree;
}

/*
 * ɾ�����(keyΪ�ڵ�ļ�ֵ)�������ظ��ڵ�
 *
 * ����˵����
 *     tree �������ĸ����
 *     z ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�
 */
Node* delete_bstree(BSTree tree, Type key)
{
	Node *z, *node;

	if ((z = bstree_search(tree, key)) != NULL)
		tree = bstree_delete(tree, z);

	return tree;
}

/*
 * ���ٶ�����
 */
void destroy_bstree(BSTree tree)
{
	if (tree==NULL)
		return ;

	if (tree->left != NULL)
		destroy_bstree(tree->left);
	if (tree->right != NULL)
		destroy_bstree(tree->right);

	free(tree);
}

/*
 * ��ӡ"������"
 *
 * tree       -- �������Ľڵ�
 * key        -- �ڵ�ļ�ֵ
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
void print_bstree(BSTree tree, Type key, int direction)
{
	if(tree != NULL)
	{
		if(direction==0)	// tree�Ǹ��ڵ�
			printf("%2d is root\n", tree->key);
		else				// tree�Ƿ�֧�ڵ�
			printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");

		print_bstree(tree->left, tree->key, -1);
		print_bstree(tree->right,tree->key,  1);
	}
}

/*
450. ɾ�������������еĽڵ�
�Ѷ��е�167
����һ�������������ĸ��ڵ� root ��һ��ֵ key��ɾ�������������е� key ��Ӧ�Ľڵ㣬����֤���������������ʲ��䡣���ض������������п��ܱ����£��ĸ��ڵ�����á�
һ����˵��ɾ���ڵ�ɷ�Ϊ�������裺
1.	�����ҵ���Ҫɾ���Ľڵ㣻
2.	����ҵ��ˣ�ɾ������
˵���� Ҫ���㷨ʱ�临�Ӷ�Ϊ O(h)��h Ϊ���ĸ߶ȡ�
ʾ��:
root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

������Ҫɾ���Ľڵ�ֵ�� 3���������������ҵ� 3 ����ڵ㣬Ȼ��ɾ������

һ����ȷ�Ĵ��� [5,4,6,2,null,null,7], ����ͼ��ʾ��

    5
   / \
  4   6
 /     \
2       7

��һ����ȷ���� [5,2,6,null,4,null,7]��

    5
   / \
  2   6
   \   \
    4   7

*/

/*
���Ҫɾ���Ľڵ�ȸ� root ��ֵС�������������ɾ�� key �ڵ㣻
���Ҫɾ���Ľڵ�ȸ� root ��ֵ�������������ɾ�� key �ڵ㣻
�� key �� root ��ֵ��ȵ�ʱ������Ҫɾ���ýڵ㣬�������������ֲ�ͬ�������

���ýڵ� (root �ڵ�) ��������Ϊ��ʱ���Ͽ��ýڵ��������������� (ע�Ᵽ��������)�����ظýڵ��������
���ýڵ��������Ϊ��ʱ���Ͽ����ӣ����ظýڵ��������
�ýڵ�������������Ϊ��ʱ�����ýڵ��������е���С�ڵ������Ԫ��

*/
 #define swap(a,b) ((a) ^= (b), (b) ^= (a) ,(a) ^= (b))

struct TreeNode* deleteNode(struct TreeNode* root, int key){
	if (root == NULL) {
		return root;
	}

	if (key > root->val) {
		  // key �ȸ��������������ɾ�� key �ڵ�
		root->right = deleteNode(root->right, key);
		return root;
	}

	 if (key < root->val ) {
		 // key �ȸ�С�������������ɾ�� key �ڵ�
		 root->left = deleteNode(root->left, key);
	 	return root;
	 }

	/*find key node*/
	/*case1*/
	if (root->left == NULL) {
		// ����ýڵ��������Ϊ�գ����ظýڵ��������
		struct TreeNode* tmp = root->right;
		root->right = NULL;
		return tmp;
	}
	/*case2*/
	if(root->right == NULL) {
		 // ����ýڵ��������Ϊ�գ����ظýڵ��������
		struct TreeNode* tmp = root->left;
		root->left = NULL;
		return tmp;
	}

// ����ýڵ��������������Ϊ�գ��򽫸ýڵ��������е���СԪ�������Ԫ��
	struct TreeNode* tmp = root->right;
	while(tmp->left)
		tmp = tmp->left;// // �ҵ�����������Сֵ����root->val����
	swap(root->val, tmp->val);

	root->right = deleteNode(root->right, key);// ���ڽ�����������ɾ��key
	return root;
}
