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

/*
426. 将二叉搜索树转化为排序的双向链表
将一个 二叉搜索树 就地转化为一个 已排序的双向循环链表 。

对于双向循环列表，你可以将左右孩子指针作为双向循环链表的前驱和后继指针，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。

特别地，我们希望可以 就地 完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中最小元素的指针。



示例 1：

输入：root = [4,2,5,1,3]
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