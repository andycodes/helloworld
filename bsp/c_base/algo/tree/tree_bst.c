/*
在二叉搜索树中：
1.若任意结点的左子树不空，则左子树上所有结点的值均
不大于它的根结点的值。
2. 若任意结点的右子树不空，则右子树上所有结点的
值均不小于它的根结点的值。
3.任意结点的左、右子树也分别为二叉搜索树。
*/

/*  Definition for a binary tree node.*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


/*
669. 修剪二叉搜索树
给定一个二叉搜索树，同时给定最小边界L?和
最大边界?R。通过修剪二叉搜索树，使得所有
节点的值在[L, R]中 (R>=L) 。你可能需要改变树的根节点，
所以结果应当返回修剪好的二叉搜索树的新的根节点。
输入:
    1
   / \
  0   2

  L = 1
  R = 2

输出:
    1
      \
       2
*/
struct TreeNode* trimBST(struct TreeNode* root, int L, int R)
{
        if (root ==  NULL)
			return root;
        if (root->val > R)
			return trimBST(root->left, L, R);
        if (root->val < L)
			return trimBST(root->right, L, R);

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
}


/*
783. 二叉搜索树节点最小距离
二叉搜索树的中序遍历是升序数组。
比如对于样例输入 root = [4,2,6,1,3,null,null]，
中序遍历的结果就是 [1, 2, 3, 4, 6]。
题目要求两个结点的最小距离，
就是要求中序遍历数组里相邻
两个元素差的最小值。
*/

int ret = 2147483647;
bool first = true;
int last;//上一个结点的值
void dfs(struct TreeNode* root)
{
	if (root == NULL)
		return;

	dfs(root->left);

	//当前结点处理
	if(!first)
		ret = min(ret, abs(root->val - last));
	else {
		first = false;
	}

	last = root->val;

	dfs(root->right);
}

int minDiffInBST(struct TreeNode* root)
{
	ret = 2147483647;
	first = true;
	dfs(root);
	return ret;
}

/*
给定一个树，按中序遍历重新排列树，
使树中最左边的结点现在是树的根，
并且每个结点没有左子结点，只有一个右子结点。

示例 ：

输入：[5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

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
将一个按照升序排列的有序数组，
转换为一棵高度平衡二叉搜索树。

本题中，一个高度平衡二叉树是指
一个二叉树每个节点 的左右两个子树的
高度差的绝对值不超过 1。

示例:

给定有序数组: [-10,-3,0,5,9],

一个可能的答案是：[0,-3,9,-10,null,5]，
它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5
*/
struct TreeNode* ToBST(int nums[],int left,int right){
	if(left>right)return NULL;//定义的二分区间为[left,right]，无法进行继续递归，直接退出
	int mid = (int)(left+right)/2;//二分中值
	struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
	root->left = ToBST(nums,left,mid-1);//注意mid-1 对左半部分进行递归
	root->right = ToBST(nums,mid+1,right);//注意mid+1 对右半部分进行递归
	return root;
}


struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    return ToBST(nums,0,numsSize-1);
}

/*
给定一个二叉搜索树，
编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。

说明：
你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。

*/
/*中序遍历(生成器)+提前终止*/
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
给你一个二叉搜索树和其中的某一个结点，请你找出该结点在树中顺序后继的节点。

结点 p 的后继是值比 p.val 大的结点中键值最小的结点。



示例 1:



输入: root = [2,1,3], p = 1
输出: 2
解析: 这里 1 的顺序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。

*/
/*
递归执行中序遍历，在递归过程中获取x的下一个。如果当前值是<=x的，那么根据BST的特性只需要在右子树中找。如果当前值>x，则当前值有可能，它的左子树也有可能有更小的但是也>x的，对左子递归后，选择更接近的（更小的).
时间O(logN)，空间O(logN)调用栈的深度。
*/
struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p) {
	if (root == NULL || p == NULL) {
		return NULL;
	}

	//当前和左边都不可能>p
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
循环实现
如果当前值是<=x的，那么根据BST的特性只需要在右子树中找：cur=cur.right。
如果当前值>x，则当前值有可能，它的左子树也有可能有更小的但是也>x的。则每次走入这个分支时，当前点是一个候选点，记录该节点的值和历史最小节点的值。
时间O(logN)，空间O(1）

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
98. 验证二叉搜索树
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
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

另一种解法
如果是有效的BST树，那么该List是无重复元素且升序的。

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
二叉查找树(Binary Search Tree)，
(又:二叉搜索树，二叉排序树)它或者是一棵空树，
或者是具有下列性质的二叉树:
若它的左子树不空，
则左子树上所有结点的值均小于它的根结点的值;
若它的右子树不空，
则右子树上所有结点的值均大于它的根结点的值;
它的左、右子树也分别为二叉排序树。
 */

#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

typedef int Type;

typedef struct BSTreeNode{
	Type   key;					// 关键字(键值)
	struct BSTreeNode *left;	// 左孩子
	struct BSTreeNode *right;	// 右孩子
	struct BSTreeNode *parent;	// 父结点
}Node, *BSTree;

/*
 * 前序遍历"二叉树"
 前序遍历 - 根->左->右
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
 * 中序遍历"二叉树"
 中序遍历 - 左->根->右
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
 * 后序遍历"二叉树"
 后序遍历 - 左->右->根
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
 * (递归实现)查找"二叉树x"中键值为key的节点
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
 * (非递归实现)查找"二叉树x"中键值为key的节点
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
 * 查找最小结点：返回tree为根结点的二叉树的最小结点。
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
 * 查找最大结点：返回tree为根结点的二叉树的最大结点。
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
 * 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
 */
Node* bstree_successor(Node *x)
{
	// 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
	if (x->right != NULL)
		return bstree_minimum(x->right);

    // 如果x没有右孩子。则x有以下两种可能：
	// (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
	// (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
	Node* y = x->parent;
	while ((y!=NULL) && (x==y->right))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 * 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
 */
Node* bstree_predecessor(Node *x)
{
	// 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
	if (x->left != NULL)
		return bstree_maximum(x->left);

    // 如果x没有左孩子。则x有以下两种可能：
	// (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
	// (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
	Node* y = x->parent;
	while ((y!=NULL) && (x==y->left))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
 * 创建并返回二叉树结点。
 *
 * 参数说明：
 *     key 是键值。
 *     parent 是父结点。
 *     left 是左孩子。
 *     right 是右孩子。
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
701. 二叉搜索树中的插入操作
 * 将结点插入到二叉树中
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
 * 删除结点(z)，并返回根节点
 *
 * 参数说明：
 *     tree 二叉树的根结点
 *     z 删除的结点
 * 返回值：
 *     根节点
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
 * 删除结点(key为节点的键值)，并返回根节点
 *
 * 参数说明：
 *     tree 二叉树的根结点
 *     z 删除的结点
 * 返回值：
 *     根节点
 */
Node* delete_bstree(BSTree tree, Type key)
{
	Node *z, *node;

	if ((z = bstree_search(tree, key)) != NULL)
		tree = bstree_delete(tree, z);

	return tree;
}

/*
 * 销毁二叉树
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
 * 打印"二叉树"
 *
 * tree       -- 二叉树的节点
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
void print_bstree(BSTree tree, Type key, int direction)
{
	if(tree != NULL)
	{
		if(direction==0)	// tree是根节点
			printf("%2d is root\n", tree->key);
		else				// tree是分支节点
			printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");

		print_bstree(tree->left, tree->key, -1);
		print_bstree(tree->right,tree->key,  1);
	}
}

/*
450. 删除二叉搜索树中的节点
难度中等167
给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。
一般来说，删除节点可分为两个步骤：
1.	首先找到需要删除的节点；
2.	如果找到了，删除它。
说明： 要求算法时间复杂度为 O(h)，h 为树的高度。
示例:
root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。

一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示。

    5
   / \
  4   6
 /     \
2       7

另一个正确答案是 [5,2,6,null,4,null,7]。

    5
   / \
  2   6
   \   \
    4   7

*/

/*
如果要删除的节点比根 root 的值小，则从左子树中删除 key 节点；
如果要删除的节点比根 root 的值大，则从右子树中删除 key 节点；
当 key 和 root 的值相等的时候，则需要删除该节点，这其中又有三种不同的情况：

当该节点 (root 节点) 的左子树为空时，断开该节点与右子树的连接 (注意保存右子树)，返回该节点的右子树
当该节点的右子树为空时，断开连接，返回该节点的左子树
该节点左右子树都不为空时，将该节点右子树中的最小节点替代该元素

*/
 #define swap(a,b) ((a) ^= (b), (b) ^= (a) ,(a) ^= (b))

struct TreeNode* deleteNode(struct TreeNode* root, int key){
	if (root == NULL) {
		return root;
	}

	if (key > root->val) {
		  // key 比根大，则从右子树中删除 key 节点
		root->right = deleteNode(root->right, key);
		return root;
	}

	 if (key < root->val ) {
		 // key 比根小，则从左子树中删除 key 节点
		 root->left = deleteNode(root->left, key);
	 	return root;
	 }

	/*find key node*/
	/*case1*/
	if (root->left == NULL) {
		// 如果该节点的左子树为空，返回该节点的右子树
		struct TreeNode* tmp = root->right;
		root->right = NULL;
		return tmp;
	}
	/*case2*/
	if(root->right == NULL) {
		 // 如果该节点的右子树为空，返回该节点的左子树
		struct TreeNode* tmp = root->left;
		root->left = NULL;
		return tmp;
	}

// 如果该节点的左右子树都不为空，则将该节点右子树中的最小元素替代该元素
	struct TreeNode* tmp = root->right;
	while(tmp->left)
		tmp = tmp->left;// // 找到右子树中最小值，与root->val交换
	swap(root->val, tmp->val);

	root->right = deleteNode(root->right, key);// 再在交换过的树中删除key
	return root;
}

 /*
270. 最接近的二叉搜索树值
难度简单31
给定一个不为空的二叉搜索树和一个目标值 target，请在该二叉搜索树中找到最接近目标值 target 的数值。
注意：
"	给定的目标值 target 是一个浮点数
"	题目保证在该二叉搜索树中只会存在一个最接近目标值的数
示例：
输入: root = [4,2,5,1,3]，目标值 target = 3.714286

    4
   / \
  2   5
 / \
1   3

输出: 4

 */
int closestValue(struct TreeNode* root, double target)
{
        int l = root->val, r = root->val;
        while(root){
            if(target < root->val){
                r = root->val;
                root = root->left;
            }else if(target > root->val){
                l = root->val;
                root = root->right;
            }else
                return root->val;
        }
        return fabs(target - l) < fabs(r - target) ? l:r;
}

 int closestValue(struct TreeNode* root, double target)
{
	int val;
	int closest = root->val;

	while(root != NULL) {
		val = root->val;
		closest = fabs(val - target) < fabs(closest - target) ? val : closest;
		root = target < root->val ? root->left : root->right;
	}

	return closest;
}

/*
109. 有序链表转换二叉搜索树
难度中等277
给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
示例:
给定的有序链表： [-10, -3, 0, 5, 9],

一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5

*/

struct ListNode* preMid(struct ListNode *head){       //找链表中间结点的前一个结点
    struct ListNode* slow=head,*fast=head,*preslow=head;
    while(fast!=NULL&&fast->next!=NULL)
    {
        preslow=slow;
        slow=slow->next;
        fast=fast->next->next;
    }
    return preslow;
}
struct TreeNode* newTreeNode(int x){
    struct TreeNode* root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val=x;
    root->left=root->right=NULL;
    return root;
}
struct TreeNode* sortedListToBST(struct ListNode* head){
    if(head==NULL) return NULL;                             //递归的终止条件:链表中只有0或1个元素
    if(head->next==NULL) return newTreeNode(head->val);
    struct ListNode* premid=preMid(head);
    struct ListNode* mid=premid->next;
    premid->next=NULL;              //断开链表 分为前后两部分
    struct TreeNode* root=newTreeNode(mid->val);
    root->left=sortedListToBST(head);
    root->right=sortedListToBST(mid->next);
    return root;
}

/*
面试题 17.12. BiNode
二叉树数据结构TreeNode可用来表示单向链表（其中left置空，right为下一个链表节点）。实现一个方法，把二叉搜索树转换为单向链表，要求依然符合二叉搜索树的性质，转换操作应是原址的，也就是在原始的二叉搜索树上直接修改。

返回转换后的单向链表的头节点。

注意：本题相对原题稍作改动



示例：

输入： [4,2,5,1,3,null,6,0]
输出： [0,null,1,null,2,null,3,null,4,null,5,null,6]
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode *cur;
    void inOrder(struct TreeNode* node)
    {
        if(node==NULL)  return ;
        inOrder(node->left);
        node->left=NULL;    //将该节点的左孩子设为NULL
        cur->right=node;    //将该节点赋给上一个节点的右孩子
        cur=node;           //更新cur
        inOrder(node->right);
    }
struct TreeNode* convertBiNode(struct TreeNode* root)
{
    struct TreeNode *ans = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
        cur = ans;
        inOrder(root);
        return ans->right;
}

/*
1038. 从二叉搜索树到更大和树
给出二叉 搜索 树的根节点，该二叉树的节点值各不相同，修改二叉树，使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int sum = 0;
struct TreeNode* backingInOrder(struct TreeNode* root)
{
        if(root != NULL){
            backingInOrder(root->right);
            sum = sum + root->val;
            root->val = sum;
            backingInOrder(root->left);
        }
        return root;
}

struct TreeNode* bstToGst(struct TreeNode* root)
{
	sum = 0;
	return backingInOrder(root);
}

/*
1382. 将二叉搜索树变平衡
给你一棵二叉搜索树，请你返回一棵 平衡后 的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。

如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 1 ，我们就称这棵二叉搜索树是 平衡的 。

如果有多种构造方法，请你返回任意一种。


*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void func(struct TreeNode* root,int *re,int *returnSize){
    if(root)//中序遍历二叉搜索树得到一个递增数组
    {
        func(root->left,re,returnSize);
        re[(*returnSize)++]=root->val;
        func(root->right,re,returnSize);
    }
}
struct TreeNode* createTree(int *nums,int numsSize){
    //利用一个递增数组创建平衡二叉搜索树
    if(numsSize==0) return NULL;
    struct TreeNode *node=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val=nums[numsSize/2];
    node->left=createTree(nums,numsSize/2);
    node->right=createTree(&nums[numsSize/2+1],numsSize-1-numsSize/2);
    return node;
}
struct TreeNode* balanceBST(struct TreeNode* root){
    int numsSize=0,nums[10000]={0};
    func(root,nums,&numsSize);
    return createTree(nums,numsSize);
}


/*
1373. 二叉搜索子树的最大键值和
给你一棵以 root 为根的 二叉树 ，请你返回 任意 二叉搜索子树的最大键值和。

二叉搜索树的定义如下：

任意节点的左子树中的键值都 小于 此节点的键值。
任意节点的右子树中的键值都 大于 此节点的键值。
任意节点的左子树和右子树都是二叉搜索树。

*/
 int result = 0;
struct Result{
    bool isBST;
    int sum;
    int minLeft;
    int maxLeft;
};

     struct Result* isBST(struct TreeNode *root){
        if(root == NULL){
            return NULL;
        }

	struct Result *res = (struct Result *)calloc(1, sizeof(struct Result));
        res->isBST = true;
        res->sum = root->val;
        res->maxLeft = root->val;
        res->minLeft = root->val;
        if(root->left == NULL && root->right == NULL){
            res->sum = root->val;
            res->isBST = true;
            res->minLeft = root->val;
            res->maxLeft = root->val;
            result = fmax(result,res->sum);
            return res;
        }else{
            struct Result* leftRes = isBST(root->left);
            struct Result* rightRes = isBST(root->right);
            if(leftRes!=NULL){
                res->isBST = res->isBST&&leftRes->isBST&&(root->val>leftRes->maxLeft);
                res->sum += leftRes->sum;
                res->maxLeft = fmax(leftRes->maxLeft,res->maxLeft);
                res->minLeft = fmin(leftRes->minLeft,res->minLeft);
            }
            if(rightRes != NULL){
                res->isBST = res->isBST&&rightRes->isBST&&(root->val<rightRes->minLeft);
                res->sum += rightRes->sum;
                res->maxLeft = fmax(rightRes->maxLeft,res->maxLeft);
                res->minLeft = fmin(rightRes->minLeft,res->minLeft);
            }
            if(res->isBST){
                result = fmax(result,res->sum);
            }
            return res;
        }
    }

int maxSumBST(struct TreeNode* root){
	result = 0;
		isBST(root);
        return result;
}