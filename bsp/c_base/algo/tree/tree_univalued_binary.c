
 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

/*
一颗树是单值的，当且仅当根节点的子节点所在的子树也是
单值的，同时根节点的值与子节点的值相同。
我们可以使用递归实现这个判断的过程。
left_correct 表示当前节点的左孩子是正确的，
也就是说：左孩子所在的子树是单值的，
并且当前节点的值等于左孩子的值。
right_correct 对当前节点的右孩子表示同样的事情。
递归处理之后，当根节点的这两种属性都为真的时候，
我们就可以判定这颗二叉树是单值的。
*/


bool isUnivalTree(struct TreeNode* root){
    bool left_correct = (root->left == NULL ||
            (root->val == root->left->val && isUnivalTree(root->left)));
    bool right_correct = (root->right == NULL ||
            (root->val == root->right->val && isUnivalTree(root->right)));

    return left_correct && right_correct;
}
