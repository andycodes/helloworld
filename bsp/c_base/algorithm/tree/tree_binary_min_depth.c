/*
����һ�����������ҳ�����С��ȡ�
����������С���Ϊ���ڵ㵽���Ҷ�ӽڵ�ľ��롣

����ʵ�ַ�����

һ�־��Ǽ�������������������ȵ�ʱ��
�ж��Ƿ����0���������0��˵�������������ڣ�
��ȸ�ֵΪ���ֵ��
*/

int minDepth(TreeNode *root) {
        if(root == NULL)
            return false;
        if(root->left == NULL && root->right == NULL)
            return 1;

        int leftDepth = minDepth(root->left);
        if(leftDepth == 0)
            leftDepth = INT_MAX;

        int rightDepth = minDepth(root->right);
        if(rightDepth == 0)
            rightDepth = INT_MAX;

        return leftDepth < rightDepth ? (leftDepth + 1) : (rightDepth + 1);
    }

/*
�ڶ��־����ж����������������Ƿ�Ϊ�գ�
��������Ϊ�գ��򷵻�����������ȣ�
��֮��������������ȣ��������Ϊ�գ�
�򷵻�����������������ȵ���Сֵ��
*/

int minDepth(TreeNode *root) {
        if(root == nullptr)
            return 0;

        //�ж����������������Ƿ�Ϊ��
        //��������Ϊ�գ��򷵻�����������ȣ���֮���������������
        if(root->left == nullptr)
            return minDepth(root->right) + 1;
        if(root->right == nullptr)
            return  minDepth(root->left) + 1;

        //�������Ϊ�գ��򷵻�����������������ȵ���Сֵ
        int leftDepth = minDepth(root->left) + 1;
        int rightDepth = minDepth(root->right) + 1;

        return leftDepth < rightDepth ? leftDepth: rightDepth;
    }