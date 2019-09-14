/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* invertTree(struct TreeNode* root){
    if(root==NULL)
			return NULL;
    struct TreeNode * ptmpNode = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(ptmpNode);
    return root;
}

