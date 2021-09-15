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

/*
98. ��֤����������
*/
bool dfs(struct TreeNode* root, long low, long high)
{
	if (root == NULL)
		return true;

	long num = root->val;
	if (num <= low || num >= high)
		return false;

	return dfs(root->left, low, num) && dfs(root->right, num, high);
}

bool isValidBST(struct TreeNode* root)
{
	return dfs(root, LONG_MIN, LONG_MAX);
}

/*
 * (�ݹ�ʵ��)����"������x"�м�ֵΪkey�Ľڵ�
 */
struct TreeNode* bstree_search(struct TreeNode* root, int val)
{
	if (root==NULL || root->val==val)
		return root;

	if (val < root->val)
		return bstree_search(root->left, val);
	else
		return bstree_search(root->right, val);
}


/*
 * ������С��㣺����treeΪ�����Ķ���������С��㡣
 */
struct TreeNode* bstree_minimum(struct TreeNode* root)
{
	if (root == NULL)
		return NULL;

	while(root->left != NULL)
		root = root->left;
	return root;
}

/*
 * ��������㣺����treeΪ�����Ķ�����������㡣
 */
struct TreeNode* bstree_maximum(struct TreeNode* root)
{
	if (root == NULL)
		return NULL;

	while(root->right != NULL)
		root = root->right;
	return root;
}

/*1382. ��������������ƽ��*/
void func(struct TreeNode* root,int *re,int *returnSize){
    if(root)//������������������õ�һ����������
    {
        func(root->left,re,returnSize);
        re[(*returnSize)++]=root->val;
        func(root->right,re,returnSize);
    }
}
struct TreeNode* createTree(int *nums,int numsSize){
    //����һ���������鴴��ƽ�����������
    if(numsSize==0) return NULL;
    struct TreeNode *node=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val=nums[numsSize/2];
    node->left=createTree(nums,numsSize/2);
    node->right=createTree(&nums[numsSize/2+1],numsSize-1-numsSize/2);
    return node;
}
struct TreeNode* balanceBST(struct TreeNode* root){
    int numsSize=0,nums[10000]={0};
    func(root,nums,&numsSize);
    return createTree(nums,numsSize);
}

