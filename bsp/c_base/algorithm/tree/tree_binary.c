
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

int maxDepth(struct TreeNode* root){
    if(root == NULL)
        return 0;

    //�ֱ�����������������������
    int leftDepth = maxDepth(root->left) + 1;
    int rightDepth = maxDepth(root->right) + 1;

    return leftDepth > rightDepth ? leftDepth: rightDepth;
}


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


/*
AB������ ͬ���ݹ� ��B����A������A�ݹ����:
���A��ǰ�ڵ�Ϊ�� ����B�ĵ�ǰ�ڵ�
���B��ǰ�ڵ�Ϊ�� ����A�ĵ�ǰ�ڵ�
(������Ѿ���������������)
AB��������ǰ�ڵ㶼Ϊ�� ����null
����Ϊ�� ��B��val �ӵ�A��val�� ���ص�ǰ�ڵ�
*/

struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2){
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


