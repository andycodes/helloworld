/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int maxDepth(struct TreeNode* root){
    if(root == NULL)
        return 0;

    //分别计算左子树和右子树的深度
    int leftDepth = maxDepth(root->left) + 1;
    int rightDepth = maxDepth(root->right) + 1;

    return leftDepth > rightDepth ? leftDepth: rightDepth;
}

