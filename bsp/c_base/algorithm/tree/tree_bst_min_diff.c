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

int main()
{}

