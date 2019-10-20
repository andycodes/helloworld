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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
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
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };


#define min(a, b) ((a) < (b) ? (a) : (b))
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
给定一个树，按中序遍历重新排列树，使树中最左边的结点现在是树的根，并且每个结点没有左子结点，只有一个右子结点。

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


