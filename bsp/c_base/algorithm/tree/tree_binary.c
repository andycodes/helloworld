
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
����һ���������������䰴��α����Ľڵ�ֵ�� �������أ������ҷ������нڵ㣩��

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


