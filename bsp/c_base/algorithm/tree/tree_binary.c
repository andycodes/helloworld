
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


struct TreeNode* invertTree(struct TreeNode* root){
    if(root==NULL)
			return NULL;
    struct TreeNode * ptmpNode = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(ptmpNode);
    return root;
}

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

    return leftDepth > rightDepth ? leftDepth: rightDepth;
}


/*
����һ�����������ҳ�����С��ȡ�
����������С���Ϊ���ڵ�
�����Ҷ�ӽڵ�ľ��롣

����ʵ�ַ�����

һ�־��Ǽ�������������������ȵ�ʱ��
�ж��Ƿ����0���������0��˵�������������ڣ�
��ȸ�ֵΪ���ֵ��
*/

int minDepth(struct TreeNode *root)
{
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

int minDepth(struct TreeNode *root)
{
        if(root == NULL)
            return 0;

        //�ж����������������Ƿ�Ϊ��
        //��������Ϊ�գ��򷵻�����������ȣ�
        //��֮���������������
        if(root->left == NULL)
            return minDepth(root->right) + 1;
        if(root->right == NULL)
            return  minDepth(root->left) + 1;

        //�������Ϊ�գ��򷵻�����������������ȵ���Сֵ
        int leftDepth = minDepth(root->left) + 1;
        int rightDepth = minDepth(root->right) + 1;
        return leftDepth < rightDepth ? leftDepth: rightDepth;
}


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


/**
����һ���������������䰴��α����Ľڵ�ֵ��
�������أ������ҷ������нڵ㣩��

����:
����������: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
�������α��������

[
  [3],
  [9,20],
  [15,7]
]


 * ʹ�ö���ʵ�ֲ�α�����Ȼ����ת�������
 */

#define MAXSIZE 1024

int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    struct TreeNode* queue[MAXSIZE];
    int front, back;
    front = back = 0;

    int** res = (int**)malloc(sizeof(int*) * MAXSIZE);
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAXSIZE);

    if(root){
        queue[back++%MAXSIZE] = root;
    }

    while(front < back){//���в�Ϊ��
        (*returnColumnSizes)[*returnSize] = back - front;
        res[*returnSize] = (int*)malloc(sizeof(int) * (*returnColumnSizes)[*returnSize]);
        for(int i = 0; i < (*returnColumnSizes)[*returnSize]; i++){
            struct TreeNode* cur = queue[front++%MAXSIZE];
            res[*returnSize][i] = cur->val;
            if(cur->left){
                queue[back++%MAXSIZE] = cur->left;
            }
            if(cur->right){
                queue[back++%MAXSIZE] = cur->right;
            }
        }
        (*returnSize)++;
    }

    int i = 0, j = *returnSize - 1;
    while(i < j){
        int t = (*returnColumnSizes)[j];
        (*returnColumnSizes)[j] = (*returnColumnSizes)[i];
        (*returnColumnSizes)[i] = t;

        int* p = res[j];
        res[j] = res[i];
        res[i] = p;

        i++; j--;
    }

    return res;
}

/*
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
#define MAX(a, b) (a > b ? a : b)
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
�ڶ������У����ڵ�λ����� 0 ����ÿ�����Ϊ k �Ľڵ���ӽڵ�λ����� k+1 ����

����������������ڵ������ͬ�������ڵ㲻ͬ����������һ�����ֵܽڵ㡣

���Ǹ����˾���Ψһֵ�Ķ������ĸ��ڵ� root���Լ�����������ͬ�ڵ��ֵ x �� y��

ֻ����ֵ x �� y ��Ӧ�Ľڵ������ֵܽڵ�ʱ���ŷ��� true�����򣬷��� false

*/
struct TreeNode* x_f = NULL;
struct TreeNode* y_f = NULL;

int find_depth_x(struct TreeNode* f_node, struct TreeNode* root, int node_val)
{
    if (root == NULL)  return -1;
    if (root->val == node_val) {
        x_f = f_node;
        return 0;
    }
    int ret;
    if ((ret = find_depth_x(root, root->left,  node_val)) >= 0) return ret+1;
    if ((ret = find_depth_x(root, root->right, node_val)) >= 0) return ret+1;
    return -1;
}
int find_depth_y(struct TreeNode* f_node, struct TreeNode* root, int node_val)
{
    if (root == NULL)  return -1;
    if (root->val == node_val) {
        y_f = f_node;
        return 0;
    }
    int ret;
    if ((ret = find_depth_y(root, root->left,  node_val)) >= 0) return ret+1;
    if ((ret = find_depth_y(root, root->right, node_val)) >= 0) return ret+1;
    return -1;
}

bool isCousins(struct TreeNode* root, int x, int y){
    int x_depth = find_depth_x(NULL, root, x);
    int y_depth = find_depth_y(NULL, root, y);
    return (x_f != y_f && x_depth == y_depth);
}

/*
����һ�����������������дӸ��ڵ㵽Ҷ�ӽڵ��·����

˵��: Ҷ�ӽڵ���ָû���ӽڵ�Ľڵ㡣

ʾ��:

����:

   1
 /   \
2     3
 \
  5

���: ["1->2->5", "1->3"]

����: ���и��ڵ㵽Ҷ�ӽڵ��·��Ϊ: 1->2->5, 1->3

*/
void _binaryTreePaths(struct TreeNode* root, int* buf, int bufSize, char** res, int* returnSize){
    if(!root){
	return;
    }

    buf[bufSize++] = root->val;

    if(!root->left && !root->right){
        res[*returnSize] = (char*)malloc(256);
	sprintf(res[*returnSize], "%d", buf[0]);
	for(int i = 1; i < bufSize; i++){
	    sprintf(res[*returnSize], "%s->%d", res[*returnSize], buf[i]);
	}
	(*returnSize)++;
	return;
    }

    _binaryTreePaths(root->left, buf, bufSize, res, returnSize);
    _binaryTreePaths(root->right, buf, bufSize, res, returnSize);
}

char ** binaryTreePaths(struct TreeNode* root, int* returnSize){
   char** res = (char**)malloc(sizeof(char*) * 256);
   *returnSize = 0;
   int buf[256];
   _binaryTreePaths(root, buf, 0, res, returnSize);

   return res;
}



/*
������������������дһ�����������������Ƿ���ͬ��

����������ڽṹ����ͬ�����ҽڵ������ͬ��ֵ������Ϊ��������ͬ�ġ�

ʾ�� 1:

����:       1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

���: true
ʾ�� 2:

����:      1          1
          /           \
         2             2

        [1,2],     [1,null,2]

���: false
ʾ�� 3:

����:       1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

���: false


*/
bool dfs(struct TreeNode* t1, struct TreeNode* t2)
{
	if (t1 == NULL && t2 == NULL)
		return true;
	else if (t1 == NULL && t2 != NULL)
		return false;
	else if (t1 != NULL && t2 == NULL)
		return false;
	else if (t1->val != t2->val)
		return false;


	return dfs(t1->left,t2->left) && dfs(t1->right,t2->right);
}


bool isSameTree(struct TreeNode* p, struct TreeNode* q){
	return dfs(p,q);
}

/*
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
�ӵ�������������ÿ���ڵ�rootΪ���ڵ���������߶�(�������������ĸ߶�ֵ��1max(left,right) + 1)��
�����Ƿ�����һ�� ��/�������߶Ȳ� �� 1 �����ʱ�������������ƽ����������-1��
�����ֲ���ƽ����ʱ������ĸ߶ȼ��㶼û�������ˣ����һ·����-1���������������㡣
�������Ƕ�����һ������DFS��ʱ�临�Ӷ�Ϊ O(N)��

*/
#define max(a, b) ((a) > (b) ? (a) : (b))
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
�Ӷ����ף���������
����һ����ȡ��ǰ�ڵ������ȵķ��� depth() ��ͨ���Ƚ������������߶Ȳ�abs(self.depth(root.left) - self.depth(root.right))�����ж��Դ˽ڵ�Ϊ���ڵ����Ƿ��Ƕ���ƽ������
�Ӷ�����DFS����ÿ���ڵ�Ϊ���ڵ㣬�ݹ��ж��Ƿ���ƽ���������
�����и��ڵ㶼����ƽ����������ʣ��򷵻� True ��
�������κ�һ���ڵ���Ϊ���ڵ�ʱ��������ƽ����������ʣ��򷵻�False��
���������������ظ��Ľڵ���ʺͼ��㣬��������ʱ�临�Ӷ� O(N^2)��

*/

#define max(a, b) ((a) > (b) ? (a) : (b))

int  dfs_depth(struct TreeNode* root)
{
	if (root == NULL)
		return 0;

	return max(dfs_depth(root->left),dfs_depth(root->right)) + 1;
}

bool  isBalanced(struct TreeNode* root)
{
	if (root == NULL)
		return true;

	return (abs(dfs_depth(root->left) - dfs_depth(root->right)) <= 1) &&
			(isBalanced(root->left))&&
			(isBalanced(root->right));
}


