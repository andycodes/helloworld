/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/*
给定一个二叉树，找出其最大深度。
二叉树的深度为根节点到最远叶子节点的距离。

如果二叉树为空，则深度为0
如果不为空，分别求左子树的深度和右子树的深度，
取最大的再加1。
*/

int maxDepth(struct TreeNode* root){
    if(root == NULL)
        return 0;

    //分别计算左子树和右子树的深度
    int leftDepth = maxDepth(root->left) + 1;
    int rightDepth = maxDepth(root->right) + 1;

    return leftDepth > rightDepth ? leftDepth: rightDepth;
}

