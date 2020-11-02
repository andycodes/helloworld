struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
����һ�����������ҳ��������ȡ�
�����������Ϊ���ڵ㵽��ԶҶ�ӽڵ�ľ��롣
���������Ϊ�գ������Ϊ0
�����Ϊ�գ��ֱ�������������Ⱥ�����������ȣ�
ȡ�����ټ�1��
*/
int maxDepth(struct TreeNode* root)
{
    if(root == NULL)
        return 0;

    int leftDepth = maxDepth(root->left) + 1;
    int rightDepth = maxDepth(root->right) + 1;

    return fmax(leftDepth, rightDepth);
}

/*
�ж����������������Ƿ�Ϊ�գ�
��������Ϊ�գ��򷵻�����������ȣ�
��֮��������������ȣ��������Ϊ�գ�
�򷵻�����������������ȵ���Сֵ��
*/
int minDepth(struct TreeNode *root)
{
        if(root == NULL)
            return 0;

        if(root->left == NULL)
            return minDepth(root->right) + 1;
        if(root->right == NULL)
            return  minDepth(root->left) + 1;

        int leftDepth = minDepth(root->left) + 1;
        int rightDepth = minDepth(root->right) + 1;
        return fmin(leftDepth, rightDepth);
}


/*
226. ��ת������
     4
   /   \
  2     7
 / \   / \
1   3 6   9
to

     4
   /   \
  7     2
 / \   / \
9   6 3   1
*/
struct TreeNode* invertTree(struct TreeNode* root)
{
	if(root == NULL)
		return NULL;

	struct TreeNode * ptmpNode = root->left;
	root->left = invertTree(root->right);
	root->right = invertTree(ptmpNode);
	return root;
}


