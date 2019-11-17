
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
给定一个二叉树，找出其最大深度。
二叉树的深度为根节点到最远叶子节点的距离。

如果二叉树为空，则深度为0
如果不为空，分别求左子树的深度和右子树的深度，
取最大的再加1。
*/

int maxDepth(struct TreeNode* root){
    if(root == NULL)
        return 0;

    //分别计算左子树和右子树的深度
    int leftDepth = maxDepth(root->left) + 1;
    int rightDepth = maxDepth(root->right) + 1;

    return leftDepth > rightDepth ? leftDepth: rightDepth;
}


/*
给定一个二叉树，找出其最小深度。
二叉树的最小深度为根节点到最近叶子节点的距离。

两种实现方法：

一种就是计算左子树和右子树深度的时候，
判断是否等于0，如果等于0，说明该子树不存在，
深度赋值为最大值。
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
第二种就是判断左子树或右子树是否为空，
若左子树为空，则返回右子树的深度，
反之返回左子树的深度，如果都不为空，
则返回左子树和右子树深度的最小值。
*/

int minDepth(TreeNode *root) {
        if(root == nullptr)
            return 0;

        //判断左子树或右子树是否为空
        //若左子树为空，则返回右子树的深度，反之返回左子树的深度
        if(root->left == nullptr)
            return minDepth(root->right) + 1;
        if(root->right == nullptr)
            return  minDepth(root->left) + 1;

        //如果都不为空，则返回左子树和右子树深度的最小值
        int leftDepth = minDepth(root->left) + 1;
        int rightDepth = minDepth(root->right) + 1;

        return leftDepth < rightDepth ? leftDepth: rightDepth;
}


/*
AB两棵树 同步递归 用B更新A并返回A递归过程:
如果A当前节点为空 返回B的当前节点
如果B当前节点为空 返回A的当前节点
(此情况已经包含在上述两种)
AB的两个当前节点都为空 返回null
都不为空 则将B的val 加到A的val上 返回当前节点
*/

struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2){
        //空节点直接返回
        if(t1 == NULL) return t2;
        if(t2 == NULL) return t1;

        //根节点权值相加
        t1->val += t2->val;

        //向左右节点递归
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);

        //返回根节点
        return t1;
}


/**
给定一个二叉树，返回其按层次遍历的节点值。
（即逐层地，从左到右访问所有节点）。

例如:
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [9,20],
  [15,7]
]


 * 使用队列实现层次遍历，然后逆转结果数组
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

    while(front < back){//队列不为空
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
给定一个二叉树，找到最长的路径，
这个路径中的每个节点具有相同值。
这条路径可以经过也可以不经过根节点。

注意：两个节点之间的路径长度由它们
之间的边数表示。

示例 1:

输入:

              5
             / \
            4   5
           / \   \
          1   1   5
输出:

2
示例 2:

输入:

              1
             / \
            4   5
           / \   \
          4   4   5
输出:

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
叶子相似的树
请考虑一颗二叉树上所有的叶子，
这些叶子的值按从左到右的顺序排列形成一个 叶值序列 。

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
给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

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


