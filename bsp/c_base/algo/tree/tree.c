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
617
Input:
	Tree 1                     Tree 2
          1                         2
         / \                       / \
        3   2                     1   3
       /                           \   \
      5                             4   7
Output:
Merged tree:
	     3
	    / \
	   4   5
	  / \   \
	 5   4   7
*/
/*
AB������ ͬ���ݹ� ��B����A������A�ݹ����:
���A��ǰ�ڵ�Ϊ�� ����B�ĵ�ǰ�ڵ�
���B��ǰ�ڵ�Ϊ�� ����A�ĵ�ǰ�ڵ�
(������Ѿ���������������)
AB��������ǰ�ڵ㶼Ϊ�� ����null
����Ϊ�� ��B��val �ӵ�A��val�� ���ص�ǰ�ڵ�
*/
struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2)
{
        //�սڵ�ֱ�ӷ���
        if(t1 == NULL) return t2;
        if(t2 == NULL) return t1;

        //���ڵ�Ȩֵ���
        t1->val += t2->val;

        //�����ҽڵ�ݹ�
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);

        //���ظ��ڵ�
        return t1;
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

/*
687. �ֵͬ·��
����һ�����������ҵ����·����
���·���е�ÿ���ڵ������ֵͬ��
����·�����Ծ���Ҳ���Բ��������ڵ㡣

ע�⣺�����ڵ�֮���·������������
֮��ı�����ʾ��

ʾ�� 1:

����:

              5
             / \
            4   5
           / \   \
          1   1   5
���:

2
ʾ�� 2:

����:

              1
             / \
            4   5
           / \   \
          4   4   5
���:

2

*/

int result = 0;
int dfs(struct TreeNode* root)
{
	int left, right;

	if (root == NULL)
		return 0;

	left = dfs(root->left);
	right = dfs(root->right);
	if (root->left != NULL && root->left->val == root->val && root->right != NULL && root->right->val == root->val) {
		result = MAX(result, left + right + 2);
		return MAX(left + 1, right + 1);
	} else if (root->left != NULL && root->left->val == root->val) {
		result = MAX(result, left + 1);
		return left + 1;
	} else if (root->right != NULL && root->right->val == root->val) {
		result = MAX(result, right + 1);
		return right + 1;
	} else {
		return 0;
	}
}

int longestUnivaluePath(struct TreeNode* root){
    result = 0;
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;

    dfs(root);
    return result;
}

/*
Ҷ�����Ƶ���
�뿼��һ�Ŷ����������е�Ҷ�ӣ�
��ЩҶ�ӵ�ֵ�������ҵ�˳�������γ�һ�� Ҷֵ���� ��

*/

void  dfs(struct TreeNode* root ,int *array, int *cnt)
{
	int left,right;
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL){
		array[*cnt] = root->val;
		 (*cnt)++;
	}


	dfs(root->left,array,cnt);
	dfs(root->right,array,cnt);
}


bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2){
	int ret =0;
	int array1[100] = {0};
	int cnt1 = 0;
	int array2[100] = {0};
	int cnt2 = 0;

	dfs(root1,array1,&cnt1);
	dfs(root2,array2,&cnt2);

	ret = memcmp(array1,array2,sizeof(array1));
	if (ret == 0)
		return true;
	else
		return false;
}


/*
����һ����������������Ƿ��Ǿ���ԳƵġ�

���磬������ [1,2,2,3,4,4,3] �ǶԳƵġ�

    1
   / \
  2   2
 / \ / \
3  4 4  3

*/
bool isMirror(struct TreeNode* t1,struct TreeNode* t2)
{
	if (t1 == NULL && t2 == NULL) return true;

	if (t1 == NULL || t2 == NULL) return false;

	return (t1->val == t2->val) && isMirror(t1->right, t2->left) && isMirror(t1->left, t2->right);
}


bool isSymmetric(struct TreeNode* root){
	return isMirror(root, root);
}

/*
110. ƽ�������
����һ�����������ж����Ƿ��Ǹ߶�ƽ��Ķ�������
�����У�һ�ø߶�ƽ�����������Ϊ��
һ��������ÿ���ڵ� ���������������ĸ߶Ȳ�ľ���ֵ������1��
ʾ�� 1:

���������� [3,9,20,null,null,15,7]

    3
   / \
  9  20
    /  \
   15   7
���� true ��

ʾ�� 2:

���������� [1,2,2,3,3,null,null,4,4]

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
���� false ��



�ӵ���������ǰ��Ϸ���
�Զ�������������ȱ���DFS���ݹ�����У�
��ֹ��������DFSԽ��Ҷ�ӽڵ�ʱ�����ظ߶�0��
����ֵ��
�ӵ�������������ÿ���ڵ�rootΪ���ڵ������
���߶�(�������������ĸ߶�ֵ��1max(left,right) + 1)��
�����Ƿ�����һ�� ��/�������߶Ȳ� �� 1 �����ʱ��
�����������ƽ����������-1��
�����ֲ���ƽ����ʱ��
����ĸ߶ȼ��㶼û�������ˣ�
���һ·����-1���������������㡣
�������Ƕ�����һ������DFS��ʱ�临�Ӷ�Ϊ O(N)��

*/
int  dfs(struct TreeNode* root)
{
	if (root == NULL)
		return 0;

	int left = dfs(root->left);
	if (left == -1)
		return -1;

	int right = dfs(root->right);
	if (right == -1)
		return -1;

	return abs(left -right) < 2 ? max(left,right) +1 : -1;
}

bool  isBalanced(struct TreeNode* root){
	return dfs(root) != -1;
}


