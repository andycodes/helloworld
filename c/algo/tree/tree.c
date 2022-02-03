struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* 前序遍历 - 根->左->右*/
void preorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	printf("%d ", root->val);
	preorder_bstree(root->left);
	preorder_bstree(root->right);
}

/*中序遍历 - 左->根->右*/
void inorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	inorder_bstree(root->left);
	printf("%d ", root->val);
	inorder_bstree(root->right);
}

/*后序遍历 - 左->右->根*/
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
AB两棵树 同步递归 用B更新A并返回A递归过程:
如果A当前节点为空 返回B的当前节点
如果B当前节点为空 返回A的当前节点
(此情况已经包含在上述两种)
AB的两个当前节点都为空 返回null
都不为空 则将B的val 加到A的val上 返回当前节点
*/
struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2)
{
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



/*
226. 翻转二叉树
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
687. 最长同值路径
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


bool isSymmetric(struct TreeNode* root)
{
	return isMirror(root, root);
}

/*
110. 平衡二叉树
给定一个二叉树，判断它是否是高度平衡的二叉树。
本题中，一棵高度平衡二叉树定义为：
一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
示例 1:

给定二叉树 [3,9,20,null,null,15,7]

    3
   / \
  9  20
    /  \
   15   7
返回 true 。

示例 2:

给定二叉树 [1,2,2,3,3,null,null,4,4]

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
返回 false 。



从底至顶（提前阻断法）
对二叉树做深度优先遍历DFS，递归过程中：
终止条件：当DFS越过叶子节点时，返回高度0；
返回值：
从底至顶，返回以每个节点root为根节点的子树
最大高度(左右子树中最大的高度值加1max(left,right) + 1)；
当我们发现有一例 左/右子树高度差 ＞ 1 的情况时，
代表此树不是平衡树，返回-1；
当发现不是平衡树时，
后面的高度计算都没有意义了，
因此一路返回-1，避免后续多余计算。
最差情况是对树做一遍完整DFS，时间复杂度为 O(N)。

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
面试题 04.08. 首个共同祖先
难度中等7
设计并实现一个算法，找出二叉树中某两个节点的第一个共同
祖先。不得将其他的节点存储在另外的数据结构中。注意：
这不一定是二叉搜索树。
例如，给定如下二叉树: root = [3,5,1,6,2,0,8,null,null,7,4]
    3
   / \
  5   1
 / \ / \
6  2 0  8
  / \
 7   4
示例 1:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输入: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

*/
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
// 到底了还没找到，返回 null
// 如果找到了 p 或 q，返回它
	if (root == NULL || p == root || q == root)
		return root;
//用left记录在左子树中查找p或q的情况，找到了其中之一立刻结束查找！找不到为null.
	struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
//用right记录在右子树中查找p或q的情况，找到了其中之一立刻结束查找！！找不到为null.
	struct TreeNode* right = lowestCommonAncestor(root->right, p, q);
//如果left为空，说明这两个节点在cur结点的右子树上，我们只需要返回右子树查找的结果即可
	if (left == NULL) {
		return right;
	}

	if (right == NULL) {
		return left;
	}
//如果left和right都不为空，说明这两个节点一个在cur的左子树上一个在cur的右子树上，
        // 它们分别在以 root 为根的左右子树中，所以 root 就是它们的最近公共祖先
	return root;
}


/*
654. 最大二叉树
给定一个不含重复元素的整数数组。
一个以此数组构建的最大二叉树定义如下：
二叉树的根是数组中的最大元素。
左子树是通过数组中最大值左边部分构造出的最大二叉树。
右子树是通过数组中最大值右边部分构造出的最大二叉树。
通过给定的数组构建最大二叉树，并且输出这个树的根节点。
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
114. 二叉树展开为链表
给定一个二叉树，原地将它展开为一个单链表。



例如，给定二叉树

    1
   / \
  2   5
 / \   \
3   4   6
将其展开为：

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
        //左子树为 null，直接考虑下一个节点
        if (root->left == NULL) {
            root = root->right;
        } else {
            // 找左子树最右边的节点
            struct TreeNode* pre = root->left;
            while (pre->right != NULL) {
                pre = pre->right;
            }
            //将原来的右子树接到左子树的最右边节点
            pre->right = root->right;
            // 将左子树插入到右子树的地方
            root->right = root->left;
            root->left = NULL;
            // 考虑下一个节点
            root = root->right;
        }
    }
}


/*
105. 从前序与中序遍历序列构造二叉树
根据一棵树的前序遍历与中序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

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
二叉树前序遍历的顺序为：先遍历根节点；随后递归地遍历左子树；最后递归地遍
历右子树。二叉树中序遍历的顺序为：先递归地遍历左子树；随后遍历根节点；
最后递归地遍历右子树。
对于任意一颗树而言，前序遍历的形式总是[ 根节点, [左子树的前序遍历结果],
[右子树的前序遍历结果] ]即根节点总是前序遍历中的第一个节点。而中序遍历的形
式总是[ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]
前序遍历的特点是， 根节点 始终出现在数组的第一位，而中序遍历中 根节点 出现
在数组的中间位置。根据上面给出的两个数组，首先我们就可以拼出 根节点，
它就是 1。
*/

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
	if ((preorderSize == 0) || (inorderSize == 0)) {
		return NULL;
	}

	struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	root->val = *preorder;// 前序遍历中的第一个节点就是根节点
	root->left = NULL;
	root->right = NULL;

	int posion = 0;// 在中序遍历中定位根节点
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
106. 从中序与后序遍历序列构造二叉树
根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]
返回如下的二叉树：

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
    if(postorderSize == 0 || inorderSize == 0)return NULL;      //叶子结点的左右子树为空

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize-1];                     //根结点值为后序遍历最后一位

    int left;
    for(left=0;left<inorderSize;left++){
        if(inorder[left] == root->val)break;                    //找到中序列表中的根结点，其索引为左子树结点个数
    }
    int right = inorderSize - left - 1;                         //计算右子树结点个数

    root->left = buildTree(inorder,left,postorder,left);        //递归构建左、右子树
    root->right = buildTree(inorder+left+1,right,postorder+left,right);

    return root;
}


