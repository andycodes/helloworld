
 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

/*
һ�����ǵ�ֵ�ģ����ҽ������ڵ���ӽڵ����ڵ�����Ҳ��
��ֵ�ģ�ͬʱ���ڵ��ֵ���ӽڵ��ֵ��ͬ��
���ǿ���ʹ�õݹ�ʵ������жϵĹ��̡�
left_correct ��ʾ��ǰ�ڵ����������ȷ�ģ�
Ҳ����˵���������ڵ������ǵ�ֵ�ģ�
���ҵ�ǰ�ڵ��ֵ�������ӵ�ֵ��
right_correct �Ե�ǰ�ڵ���Һ��ӱ�ʾͬ�������顣
�ݹ鴦��֮�󣬵����ڵ�����������Զ�Ϊ���ʱ��
���ǾͿ����ж���Ŷ������ǵ�ֵ�ġ�
*/


bool isUnivalTree(struct TreeNode* root){
    bool left_correct = (root->left == NULL ||
            (root->val == root->left->val && isUnivalTree(root->left)));
    bool right_correct = (root->right == NULL ||
            (root->val == root->right->val && isUnivalTree(root->right)));

    return left_correct && right_correct;
}
