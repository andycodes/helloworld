
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
Invert a binary tree.

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
给定一个二叉树，找出其最大深度。
二叉树的深度为根节点到最远叶子节点的距离。

如果二叉树为空，则深度为0
如果不为空，分别求左子树的深度和右子树的深度，
取最大的再加1。
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
给定一个二叉树，找出其最小深度。
二叉树的最小深度为根节点
到最近叶子节点的距离。

两种实现方法：

一种就是计算左子树和右子树深度的时候，
判断是否等于0，如果等于0，说明该子树不存在，
深度赋值为最大值。
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
第二种就是判断左子树或右子树是否为空，
若左子树为空，则返回右子树的深度，
反之返回左子树的深度，如果都不为空，
则返回左子树和右子树深度的最小值。
*/

int minDepth(struct TreeNode *root)
{
        if(root == NULL)
            return 0;

        //判断左子树或右子树是否为空
        //若左子树为空，则返回右子树的深度，
        //反之返回左子树的深度
        if(root->left == NULL)
            return minDepth(root->right) + 1;
        if(root->right == NULL)
            return  minDepth(root->left) + 1;

        //如果都不为空，则返回左子树和右子树深度的最小值
        int leftDepth = minDepth(root->left) + 1;
        int rightDepth = minDepth(root->right) + 1;
        return leftDepth < rightDepth ? leftDepth: rightDepth;
}

/*
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


/**
102. 二叉树的层次遍历
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

int GetTreeDepth(const struct TreeNode* root)
{
        if (root == NULL)
                return 0;

        int left = GetTreeDepth(root->left);
        int right = GetTreeDepth(root->right);

        return left > right ? left + 1 : right + 1;
}


int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
        if (root == NULL || returnSize == NULL || returnColumnSizes == NULL) {
            *returnSize = 0;
            *returnColumnSizes = (int *)malloc(sizeof(int) * 1);
            (*returnColumnSizes)[0] = 0;
            return NULL;
        }

	struct aqueue_blk * aqueue = aqueue_init(1024);

	struct aqueue_load load;
	load.node = root;
	aqueue_push_last_val(aqueue,  load);

        int depth = GetTreeDepth(root);
        *returnSize = depth;
        int **matrix = (int **)malloc(sizeof(int *) * depth);
        *returnColumnSizes = (int *)malloc(sizeof(int) * depth);
        if (matrix == NULL || returnColumnSizes == NULL)
                return NULL;

        int cur_depth = 0;
        while(aqueue_size(aqueue) != 0) {
                int level_size = aqueue_size(aqueue);
                /* create raw */
                (*returnColumnSizes)[cur_depth] = level_size;
                matrix[cur_depth] = (int *)malloc(sizeof(int) * level_size);
                int cur = 0;
                while (level_size--) {
                        struct TreeNode* node;

			struct aqueue_load pop = aqueue_pop_first_val(aqueue);
                       node = pop.node;
                        /* add node->val to res */
                        matrix[cur_depth][cur] = node->val;

                        if (node->left) {
				struct aqueue_load next;
				next.node = pop.node->left;
				aqueue_push_last_val(aqueue,  next);
			}

                        if (node->right) {
				struct aqueue_load next;
				next.node = pop.node->right;
				aqueue_push_last_val(aqueue,  next);
			}

                    cur++;
                }
                cur_depth++;
        }
        return matrix;
}


#define MaxSize 1000
void dfs(struct TreeNode* root, int** result, int* ColumnSizes, int i, int* maxh)
{
	if (root != NULL) {
		result[i][ColumnSizes[i]] = root->val;
		ColumnSizes[i]++;
		if(i+1>*maxh)
			*maxh = i+1;
		dfs(root->left, result, ColumnSizes, i + 1, maxh);
		dfs(root->right, result, ColumnSizes, i + 1, maxh);
	}
}

int** levelOrder(
		  struct TreeNode* root,
                 int* returnSize,
                 int** returnColumnSizes)
{
    int** result = (int**)malloc(sizeof(int*) * MaxSize);
    for (int i = 0; i < MaxSize; i++)
        result[i] = (int*)malloc(sizeof(int) * MaxSize);

    *returnColumnSizes = (int*)calloc(MaxSize, sizeof(int));
    *returnSize = 0;
    if(root==NULL)
        return NULL;
    dfs(root, result, *returnColumnSizes, 0, returnSize);
    return result;
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
给你一棵二叉树的根节点 root，
找出这棵树的 每一棵 子树的 平均值 中的 最大 值。
子树是树中的任意节点和它的所有后代构成的集合。
树的平均值是树中节点值的总和除以节点数。



示例：



输入：[5,6,1]
输出：6.00000
解释：
以 value = 5 的节点作为子树的根节点，得到的平均值为 (5 + 6 + 1) / 3 = 4。
以 value = 6 的节点作为子树的根节点，得到的平均值为 6 / 1 = 6。
以 value = 1 的节点作为子树的根节点，得到的平均值为 1 / 1 = 1。
所以答案取最大值 6。

*/
double result = 0;
int dfs(struct TreeNode* root)
{
	int left, right;
	double sum = 0;

	if (root == NULL)
		return 0;
	left = dfs(root->left);
	right = dfs(root->right);
	if (root->left != NULL  && root->right != NULL) {
		sum = left + right + root->val;
        sum /= 3;
		result = max(result, sum);
		return sum;
	}
	else if (root->left != NULL) {
		sum = left + root->val;
        sum /= 2;
		result = max(result, sum);
		return sum;
	}
	else if (root->right != NULL) {
		sum = right + root->val;
        sum /= 2;
		result = max(result, sum);
		return sum;
	}
	else {
		sum = root->val;
		result = max(result, sum);
		return sum;
	}
}

double maximumAverageSubtree(struct TreeNode* root) {
	result = 0;
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL) {
		return root->val;
	}

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

/*
在二叉树中，根节点位于深度 0 处，每个深度为 k 的节点的子节点位于深度 k+1 处。

如果二叉树的两个节点深度相同，但父节点不同，则它们是一对堂兄弟节点。

我们给出了具有唯一值的二叉树的根节点 root，以及树中两个不同节点的值 x 和 y。

只有与值 x 和 y 对应的节点是堂兄弟节点时，才返回 true。否则，返回 false

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
给定一个二叉树，返回所有从根节点到叶子节点的路径。

说明: 叶子节点是指没有子节点的节点。

示例:

输入:

   1
 /   \
2     3
 \
  5

输出: ["1->2->5", "1->3"]

解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3

*/
void _binaryTreePaths(struct TreeNode* root, int* buf, int bufSize, char** res, int* returnSize){

	if(root == NULL) {
		return;
	}

	buf[bufSize++] = root->val;

	if((root->left == NULL) && (root->right == NULL)){
		res[*returnSize] = (char*)malloc(256);
		sprintf(res[*returnSize], "%d", buf[0]);
		for(int i = 1; i < bufSize; i++) {
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
给定两个二叉树，编写一个函数来检验它们是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

示例 1:

输入:       1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

输出: true
示例 2:

输入:      1          1
          /           \
         2             2

        [1,2],     [1,null,2]

输出: false
示例 3:

输入:       1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

输出: false


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
从顶至底（暴力法）
构造一个获取当前节点最大深度的方法 depth() ，
通过比较左右子树最大高度差abs(self.depth(root.left) - self.depth(root.right))，
来判断以此节点为根节点下是否是二叉平衡树；
从顶至底DFS，以每个节点为根节点，
递归判断是否是平衡二叉树：
若所有根节点都满足平衡二叉树性质，则返回 True ；
若其中任何一个节点作为根节点时，
不满足平衡二叉树性质，则返回False。
本方法产生大量重复的节点访问和计算，
最差情况下时间复杂度 O(N^2)。
*/

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


/*
给定一个二叉树和一个目标和，判断该树中是否存在根节点
到叶子节点的路径，这条路径上所有节点值相加等于目标和。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
返回 true, 因为存在目标和为 22 的根节点到叶子节点的
路径 5->4->11->2。

*/
/*
最直接的方法就是利用递归，遍历整棵树：
如果当前节点不是叶子，对它的所有孩子节点，
递归调用 hasPathSum 函数，其中 sum 值减去当前节点的权值；
如果当前节点是叶子，检查 sum 值是否为 0，
也就是是否找到了给定的目标和。

复杂度分析

时间复杂度：我们访问每个节点一次，时间复杂度为 O(N)O(N) ，
其中 NN 是节点个数。
空间复杂度：最坏情况下，整棵树是非平衡的，
例如每个节点都只有一个孩子，递归会调用 NN 次（树的高度），
因此栈的空间开销是 O(N)O(N) 。但在最好情况下，
树是完全平衡的，高度只有 \log(N)log(N)，因此在这种情况
下空间复杂度只有 O(\log(N))O(log(N)) 。

*/
bool hasPathSum(struct TreeNode* root, int sum){
	if(root == NULL)
		return false;

	sum -= root->val;

	if ((root->left == NULL) && (root->right == NULL))
		return  sum == 0;

	return hasPathSum(root->left,sum) || hasPathSum(root->right,sum);
}

/*
第二种方法是，声明一个变量记录已经经过的节点的值之和，
每经过一个节点就加上这个节点的值，
在叶子节点判断变量值是否为目标值。
*/
bool dfs(struct TreeNode* root, int cur, int sum)
{
	if (root == NULL)
		return false;

	cur += root->val;

	if (root->left == NULL && root->right == NULL) {
		return cur == sum;
	} else {
		return dfs(root->left,cur,sum) ||dfs(root->right,cur,sum);
	}
}

bool hasPathSum(struct TreeNode* root, int sum){
	return dfs(root,0,sum);
}


/*
给定一个二叉树，其中所有的右节点
要么是具有兄弟节点（拥有相同父节点的左节点）的叶节点，
要么为空，将此二叉树上下翻转并将它变成一棵树，
原来的右节点将转换成左叶节点。返回新的根。

例子:

输入: [1,2,3,4,5]

    1
   / \
  2   3
 / \
4   5

输出: 返回二叉树的根 [4,5,2,#,#,3,1]

   4
  / \
 5   2
    / \
   3   1
说明:

对 [4,5,2,#,#,3,1] 感到困惑? 下面详细介绍请查看 二叉树是如何被序列化的。

二叉树的序列化遵循层次遍历规则，当没有节点存在时，'#' 表示路径终止符。

这里有一个例子:

   1
  / \
 2   3
    /
   4
    \
     5
上面的二叉树则被序列化为 [1,2,3,#,#,4,#,#,5].

*/
struct TreeNode* upsideDownBinaryTree(struct TreeNode* root){
	if (root == NULL || root->left == NULL)
		return root;

	struct TreeNode *left = root->left;
	struct TreeNode *right = root->right;

	root->left = NULL;
	root->right = NULL;

	struct TreeNode* res = upsideDownBinaryTree(left);
	left->left = right;
	left->right = root;
	return res;
}



/*
113. 路径总和 II
给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

*/

void dfs(struct TreeNode* root, int sum, int* returnSize,
		int** returnColumnSizes, int **res, int *cur, int curCnt)
{
    	if (root == NULL)
		return;

    	cur[curCnt++] = root->val;

	if (root->left == NULL && root->right == NULL && sum == root->val) {
		res[*returnSize] = (int *)calloc(curCnt, sizeof(int));
		memcpy(res[*returnSize], cur, sizeof(int) * curCnt);
		(*returnColumnSizes)[*returnSize] = curCnt;
		(*returnSize)++;
		return;
	}


	dfs(root->left, sum - root->val, returnSize,
		returnColumnSizes, res, cur, curCnt);
	dfs(root->right, sum - root->val, returnSize,
		returnColumnSizes, res, cur, curCnt);
}


void dfs(struct TreeNode* root, int sum, int* returnSize,
		int** returnColumnSizes, int **res, int *cur, int curCnt)
{
    if (root == NULL)
		return;

	    sum -= root->val;
	    cur[curCnt++] = root->val;

	if (root->left == NULL && root->right == NULL && sum == 0) {
		res[*returnSize] = (int *)calloc(curCnt, sizeof(int));
		memcpy(res[*returnSize], cur, sizeof(int) * curCnt);
		(*returnColumnSizes)[*returnSize] = curCnt;
		(*returnSize)++;
		return;
	}


	dfs(root->left, sum, returnSize,
		returnColumnSizes, res, cur, curCnt);
	dfs(root->right, sum, returnSize,
		returnColumnSizes, res, cur, curCnt);

}


/*下面是回溯；注意跟上面DFS的区别，
sum -= root->val; 改变了当前栈空间的对象对回溯也没有什么用；
回溯到上一层sum，不是同一个sum;
每一层sum 在栈上都是独立储存的对象，
参数 ，内部变量都是自动回溯*/
void dfs(struct TreeNode* root, int sum, int* returnSize,
		int** returnColumnSizes, int **res, int *cur, int curCnt)
{
	if (root == NULL)
	return;

	cur[curCnt++] = root->val;

	if (root->left == NULL && root->right == NULL && sum == root->val) {
		res[*returnSize] = (int *)calloc(curCnt, sizeof(int));
		memcpy(res[*returnSize], cur, sizeof(int) * curCnt);
		(*returnColumnSizes)[*returnSize] = curCnt;
		(*returnSize)++;
		return;
	}

	sum -= root->val;
	dfs(root->left, sum, returnSize,
	returnColumnSizes, res, cur, curCnt);
	sum += root->val;

	sum -= root->val;
	dfs(root->right, sum, returnSize,
	returnColumnSizes, res, cur, curCnt);
	sum += root->val;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int sum,
	int* returnSize, int** returnColumnSizes) {

	*returnSize = 0;
	int ** res = (int **)calloc(1024, sizeof(int *));
	*returnColumnSizes = (int*)calloc(1024, sizeof(int));
	int* current = (int*)calloc(1024, sizeof(int));

	dfs(root, sum, returnSize, returnColumnSizes, res, current, 0);

	return res;
}
