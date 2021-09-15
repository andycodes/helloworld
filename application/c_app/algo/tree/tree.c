struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* ǰ����� - ��->��->��*/
void preorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	printf("%d ", root->val);
	preorder_bstree(root->left);
	preorder_bstree(root->right);
}

/*������� - ��->��->��*/
void inorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	inorder_bstree(root->left);
	printf("%d ", root->val);
	inorder_bstree(root->right);
}

/*������� - ��->��->��*/
void postorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	postorder_bstree(root->left);
	postorder_bstree(root->right);
	printf("%d ", root->val);
}

int maxDepth(struct TreeNode* root)
{
	if(root == NULL)
		return 0;

	int leftDepth = maxDepth(root->left) + 1;
	int rightDepth = maxDepth(root->right) + 1;

	return fmax(leftDepth, rightDepth);
}

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

int longestUnivaluePath(struct TreeNode* root)
{
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


bool isSymmetric(struct TreeNode* root)
{
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


/*
������ 04.08. �׸���ͬ����
�Ѷ��е�7
��Ʋ�ʵ��һ���㷨���ҳ���������ĳ�����ڵ�ĵ�һ����ͬ
���ȡ����ý������Ľڵ�洢����������ݽṹ�С�ע�⣺
�ⲻһ���Ƕ�����������
���磬�������¶�����: root = [3,5,1,6,2,0,8,null,null,7,4]
    3
   / \
  5   1
 / \ / \
6  2 0  8
  / \
 7   4
ʾ�� 1:
����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
����: 3
����: �ڵ� 5 �ͽڵ� 1 ��������������ǽڵ� 3��

*/
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
// �����˻�û�ҵ������� null
// ����ҵ��� p �� q��������
	if (root == NULL || p == root || q == root)
		return root;
//��left��¼���������в���p��q��������ҵ�������֮һ���̽������ң��Ҳ���Ϊnull.
	struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
//��right��¼���������в���p��q��������ҵ�������֮һ���̽������ң����Ҳ���Ϊnull.
	struct TreeNode* right = lowestCommonAncestor(root->right, p, q);
//���leftΪ�գ�˵���������ڵ���cur�����������ϣ�����ֻ��Ҫ�������������ҵĽ������
	if (left == NULL) {
		return right;
	}

	if (right == NULL) {
		return left;
	}
//���left��right����Ϊ�գ�˵���������ڵ�һ����cur����������һ����cur���������ϣ�
        // ���Ƿֱ����� root Ϊ�������������У����� root �������ǵ������������
	return root;
}


/*
654. ��������
����һ�������ظ�Ԫ�ص��������顣
һ���Դ����鹹�������������������£�
�������ĸ��������е����Ԫ�ء�
��������ͨ�����������ֵ��߲��ֹ����������������
��������ͨ�����������ֵ�ұ߲��ֹ����������������
ͨ�����������鹹�������������������������ĸ��ڵ㡣
*/
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize)
{
	if (numsSize <= 0)
		return NULL;

	struct TreeNode*root = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
	int maxidx = 0;
	for (int i = 0; i < numsSize; i++)
		if (nums[i] > nums[maxidx])
			maxidx = i;

	root->val = nums[maxidx];
	root->left = constructMaximumBinaryTree(nums, maxidx);
	root->right = constructMaximumBinaryTree(nums + maxidx + 1, numsSize - maxidx - 1);
	return root;
}


/*
114. ������չ��Ϊ����
����һ����������ԭ�ؽ���չ��Ϊһ��������



���磬����������

    1
   / \
  2   5
 / \   \
3   4   6
����չ��Ϊ��

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int num;

void flatten(struct TreeNode* root) {
    num = 0;
    struct TreeNode** l = (struct TreeNode**)malloc(0);
    preorderTraversal(root, &l);
    for (int i = 1; i < num; i++) {
        struct TreeNode *prev = l[i - 1], *curr = l[i];
        prev->left = NULL;
        prev->right = curr;
    }
    free(l);
}

void preorderTraversal(struct TreeNode* root, struct TreeNode*** l) {
    if (root != NULL) {
        num++;
        (*l) = (struct TreeNode**)realloc((*l), sizeof(struct TreeNode*) * num);
        (*l)[num - 1] = root;
        preorderTraversal(root->left, l);
        preorderTraversal(root->right, l);
    }
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void flatten(struct TreeNode* root)
{
    while (root != NULL) {
        //������Ϊ null��ֱ�ӿ�����һ���ڵ�
        if (root->left == NULL) {
            root = root->right;
        } else {
            // �����������ұߵĽڵ�
            struct TreeNode* pre = root->left;
            while (pre->right != NULL) {
                pre = pre->right;
            }
            //��ԭ�����������ӵ������������ұ߽ڵ�
            pre->right = root->right;
            // �����������뵽�������ĵط�
            root->right = root->left;
            root->left = NULL;
            // ������һ���ڵ�
            root = root->right;
        }
    }
}


/*
105. ��ǰ��������������й��������
����һ������ǰ�������������������������

ע��:
����Լ�������û���ظ���Ԫ�ء�

���磬����

ǰ����� preorder = [3,9,20,15,7]
������� inorder = [9,3,15,20,7]
�������µĶ�������

    3
   / \
  9  20
    /  \
   15   7
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/*
������ǰ�������˳��Ϊ���ȱ������ڵ㣻���ݹ�ر��������������ݹ�ر�
�������������������������˳��Ϊ���ȵݹ�ر��������������������ڵ㣻
���ݹ�ر�����������
��������һ�������ԣ�ǰ���������ʽ����[ ���ڵ�, [��������ǰ��������],
[��������ǰ��������] ]�����ڵ�����ǰ������еĵ�һ���ڵ㡣�������������
ʽ����[ [������������������], ���ڵ�, [������������������] ]
ǰ��������ص��ǣ� ���ڵ� ʼ�ճ���������ĵ�һλ������������� ���ڵ� ����
��������м�λ�á���������������������飬�������ǾͿ���ƴ�� ���ڵ㣬
������ 1��
*/

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
	if ((preorderSize == 0) || (inorderSize == 0)) {
		return NULL;
	}

	struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	root->val = *preorder;// ǰ������еĵ�һ���ڵ���Ǹ��ڵ�
	root->left = NULL;
	root->right = NULL;

	int posion = 0;// ����������ж�λ���ڵ�
	for (int i = 0; i < preorderSize; i++) {
		if (*preorder == inorder[i]) {
			posion = i;
			break;
		}
	}

	root->left = buildTree(preorder + 1, posion, inorder, posion);
	root->right = buildTree(preorder + posion + 1, inorderSize - posion - 1, inorder + posion + 1, inorderSize - posion - 1);
	return root;
}

/*
106. �����������������й��������
����һ��������������������������������

ע��:
����Լ�������û���ظ���Ԫ�ء�

���磬����

������� inorder = [9,3,15,20,7]
������� postorder = [9,15,7,20,3]
�������µĶ�������

    3
   / \
  9  20
    /  \
   15   7
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */



struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    if(postorderSize == 0 || inorderSize == 0)return NULL;      //Ҷ�ӽ�����������Ϊ��

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize-1];                     //�����ֵΪ����������һλ

    int left;
    for(left=0;left<inorderSize;left++){
        if(inorder[left] == root->val)break;                    //�ҵ������б��еĸ���㣬������Ϊ������������
    }
    int right = inorderSize - left - 1;                         //����������������

    root->left = buildTree(inorder,left,postorder,left);        //�ݹ鹹����������
    root->right = buildTree(inorder+left+1,right,postorder+left,right);

    return root;
}


