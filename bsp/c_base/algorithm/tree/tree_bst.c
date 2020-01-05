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

struct TreeNode* trimBST(struct TreeNode* root, int L, int R){
        if (root ==  NULL) return root;
        if (root->val > R) return trimBST(root->left, L, R);
        if (root->val < L) return trimBST(root->right, L, R);

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
}


/*
 二叉搜索树结点最小距离

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
void help(struct TreeNode* root)
{
    if(root)
    {
        //左子树
        help(root->left);

        //当前结点处理
        if(!first)
            ret = min(ret, abs(root->val - last));
        else
        {
            first = false;
        }
        last = root->val;

        //右子树
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

