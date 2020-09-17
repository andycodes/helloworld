struct TreeNode* bst_push(struct TreeNode* root, int val)
{
	struct TreeNode* y = NULL;
	struct TreeNode* cur = root;

	while(cur != NULL) {
		y = cur;
		if (val < cur->val)
			cur = cur->left;
		else
			cur = cur->right;
	}

	struct TreeNode* node = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
	node->val = val;
	if (y == NULL)
		cur = node;
	else if (node->val < y->val)
		y->left = node;
	else
		y->right = node;

	return cur;
}

struct TreeNode* bst_del(struct TreeNode* root, int val)
{
	if (root == NULL) {
		return root;
	}

	if (val > root->val) {
		root->right = bst_del(root->right, val);
		return root;
	}

	 if (val < root->val ) {
		 root->left = bst_del(root->left, val);
	 	return root;
	 }

	if (root->left == NULL) {
		struct TreeNode* tmp = root->right;
		root->right = NULL;
		return tmp;
	}

	if(root->right == NULL) {
		struct TreeNode* tmp = root->left;
		root->left = NULL;
		return tmp;
	}

/*
����ýڵ��������������Ϊ�գ��򽫸ýڵ��������е�
��СԪ�������Ԫ��
*/	struct TreeNode* tmp = root->right;
	while(tmp->left)
		tmp = tmp->left;// // �ҵ�����������Сֵ����root->val����
	swap(root->val, tmp->val);

	root->right = bst_del(root->right, val);// ���ڽ�����������ɾ��key
	return root;
}


void bst_destroy(struct TreeNode* root)
{
	if (root==NULL)
		return ;

	if (root->left != NULL)
		bst_destroy(root->left);
	if (root->right != NULL)
		bst_destroy(root->right);

	free(root);
}

/*
426. ������������ת��Ϊ�����˫������
��һ�� ���������� �͵�ת��Ϊһ�� �������˫��ѭ������ ��

����˫��ѭ���б�����Խ����Һ���ָ����Ϊ˫��ѭ�������ǰ���ͺ��ָ�룬��һ���ڵ��ǰ�������һ���ڵ㣬���һ���ڵ�ĺ���ǵ�һ���ڵ㡣

�ر�أ�����ϣ������ �͵� ���ת����������ת������Ժ����нڵ����ָ����Ҫָ��ǰ�������нڵ����ָ����Ҫָ���̡�����Ҫ������������СԪ�ص�ָ�롣



ʾ�� 1��

���룺root = [4,2,5,1,3]
*/

/*
// Definition for a Node.
struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};
*/
  // the smallest (first) and the largest (last) nodes
 struct Node* first = NULL;
 struct Node* last = NULL;

  void helper(struct Node* node) {
    if (node) {
      // left
      helper(node->left);
      // node
      if (last) {
        // link the previous node (last)
        // with the current one (node)
        last->right = node;
        node->left = last;
      }
      else {
        // keep the smallest node
        // to close DLL later on
        first = node;
      }
      last = node;
      // right
      helper(node->right);
    }
  	}
struct Node* treeToDoublyList(struct Node *root)
{
first = NULL;
last = NULL;

	if (!root) return NULL;

    helper(root);
    // close DLL
    last->right = first;
    first->left = last;
    return first;
}