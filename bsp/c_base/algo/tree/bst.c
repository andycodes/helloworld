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
如果该节点的左右子树都不为空，则将该节点右子树中的
最小元素替代该元素
*/	struct TreeNode* tmp = root->right;
	while(tmp->left)
		tmp = tmp->left;// // 找到右子树中最小值，与root->val交换
	swap(root->val, tmp->val);

	root->right = bst_del(root->right, val);// 再在交换过的树中删除key
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

