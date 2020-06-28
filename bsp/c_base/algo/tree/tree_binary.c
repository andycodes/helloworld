
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
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
        if (root == NULL || returnSize == NULL || returnColumnSizes == NULL) {
            *returnSize = 0;
            *returnColumnSizes = (int *)malloc(sizeof(int) * 1);
            (*returnColumnSizes)[0] = 0;
            return NULL;
        }

	struct List dlist;
	struct List *list = &dlist;
	queue_init(list);


	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->root = root;
	ListAddTail(list, &entry->node);

        int depth = maxDepth(root);
        *returnSize = depth;
        int **res = (int **)malloc(sizeof(int *) * depth);
        *returnColumnSizes = (int *)malloc(sizeof(int) * depth);
        if (res == NULL || returnColumnSizes == NULL)
                return NULL;

        int cur_depth = 0;
        while(!queue_empty(list)) {
                int level_size = queue_size(list);
                /* create raw */
                (*returnColumnSizes)[cur_depth] = level_size;
                res[cur_depth] = (int *)malloc(sizeof(int) * level_size);
                int cur = 0;
                while (level_size--) {
			struct DataEntry *pop = queue_pop_entry(list);
                        /* add node->val to res */
                        res[cur_depth][cur] = pop->root->val;

                        if (pop->root->left) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->root = pop->root->left;
				ListAddTail(list, &entry->node);
			}

                        if (pop->root->right) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->root = pop->root->right;
				ListAddTail(list, &entry->node);
			}

                    cur++;
                }
                cur_depth++;
        }
        return res;
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

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
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
面试题 04.03. 特定深度节点链表
给定一棵二叉树，设计一个算法，创建含有某一深度上所有节点的链表（比如，若一棵树的深度为 D，则会创建出 D 个链表）。返回一个包含所有深度的链表的数组。



示例：

输入：[1,2,3,4,5,null,7,8]

        1
       /  \
      2    3
     / \    \
    4   5    7
   /
  8

输出：[[1],[2,3],[4,5,7],[8]]
*/
struct ListNode** bfs(struct TreeNode *root, int *returnSize)
{
	struct List queue;
	queue_init(&queue);

	int size = getTreeDepth(root);
	struct ListNode **ans = malloc(sizeof(struct ListNode *) * size);
	int ansSize = 0;

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->tree = root;
	ListAddTail(&queue, &entry->node);

    	while (!queue_empty(&queue)) {
	int curSize = queue_size(&queue);
	struct ListNode *pre = NULL;
        for (int i = 0; i < curSize; ++i) {
		struct DataEntry *pop = queue_pop_entry(&queue);
            if (i == 0) {
                ans[ansSize] = malloc(sizeof(struct ListNode)); // head of each list
                ans[ansSize]->val = pop->tree->val;
                ans[ansSize]->next = NULL;
                pre = ans[ansSize];
            } else {
                struct ListNode *newListNode = malloc(sizeof(struct ListNode));
                newListNode->val = pop->tree->val;
                newListNode->next = NULL;
                pre->next = newListNode;
                pre = pre->next;
            }

            if (pop->tree->left != NULL) {
		struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
		entry->tree = pop->tree->left;
		ListAddTail(&queue, &entry->node);
            }
            if (pop->tree->right != NULL) {
		struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
		entry->tree = pop->tree->right;
		ListAddTail(&queue, &entry->node);
            }
        }
        ++ansSize;
    }
    *returnSize = ansSize;
    return ans;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct ListNode** listOfDepth(struct TreeNode* tree, int* returnSize){
    if (tree == NULL) {
        return NULL;
    }
    return bfs(tree, returnSize);
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
给定一个二叉树和一个目标和，
判断该树中是否存在根节点
到叶子节点的路径，这条路径上所有节点值相加
等于目标和。

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
给定一个二叉树和一个目标和，
找到所有从根节点到叶子节点路径总和等于
给定目标和的路径。

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

int** pathSum(struct TreeNode* root, int sum,
	int* returnSize, int** returnColumnSizes) {

	*returnSize = 0;
	int ** res = (int **)calloc(1024, sizeof(int *));
	*returnColumnSizes = (int*)calloc(1024, sizeof(int));
	int* current = (int*)calloc(1024, sizeof(int));

	dfs(root, sum, returnSize, returnColumnSizes, res, current, 0);

	return res;
}

/*
1145. 二叉树着色游戏
难度中等17
有两位极客玩家参与了一场「二叉树着色」的游戏。游戏中，给出二叉树的根节点 root，树上总共有 n 个节点，且 n 为奇数，其中每个节点上的值从 1 到 n 各不相同。

游戏从「一号」玩家开始（「一号」玩家为红色，「二号」玩家为蓝色），最开始时，
「一号」玩家从 [1, n] 中取一个值 x（1 <= x <= n）；
「二号」玩家也从 [1, n] 中取一个值 y（1 <= y <= n）且 y != x。
「一号」玩家给值为 x 的节点染上红色，而「二号」玩家给值为 y 的节点染上蓝色。

之后两位玩家轮流进行操作，每一回合，玩家选择一个他之前涂好颜色的节点，将所选节点一个 未着色 的邻节点（即左右子节点、或父节点）进行染色。
如果当前玩家无法找到这样的节点来染色时，他的回合就会被跳过。
若两个玩家都没有可以染色的节点时，游戏结束。着色节点最多的那位玩家获得胜利 ??。

现在，假设你是「二号」玩家，根据所给出的输入，假如存在一个 y 值可以确保你赢得这场游戏，则返回 true；若无法获胜，就请返回 false。

示例：

输入：root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
输出：True
解释：第二个玩家可以选择值为 2 的节点。

提示：
"	二叉树的根节点为 root，树上由 n 个节点，节点上的值从 1 到 n 各不相同。
"	n 为奇数。
"	1 <= x <= n <= 100

*/
int dfs(struct TreeNode* root, int mid, int x, bool *res)
{
	if (root == NULL)
		return 0;

	int l = dfs(root->left, mid, x, res);
	int r = dfs(root->right, mid, x, res);

       if (root->val == x) {
            // 当x的左子数数量或者右子数数量大于一半，或者整个x树的数量<=一半的时候，结果为true
            if (l > mid || r > mid || (l + r + 1 <= mid)) {
                *res = true;
                return;
            }
        }

        return l + r + 1;
}

bool btreeGameWinningMove(struct TreeNode* root, int n, int x)
{
	bool res = false;
	int mid = n >> 1;
	dfs(root, mid, x, &res);
	return res;
}

/*
面试题 04.12. 求和路径
给定一棵二叉树，其中每个节点都含有一个整数数值
(该值或正或负)。设计一个算法，打印节点数值总和等
于某个给定值的所有路径的数量。注意，路径不一定非
得从二叉树的根节点或叶节点开始或结束，
但是其方向必须向下(只能从父节点指向子节点方向)。

示例:
给定如下二叉树，以及目标和 sum = 22，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
返回:

3
解释：和为 22 的路径有：[5,4,11,2], [5,8,4,5], [4,11,7]
提示：

节点总数 <= 10000
*/
/*
题目的要求是求得所有等于sum的路径；所以我们想象每
一个节点都是根节点，再从每一个节点DFS找到它有几条
等于sum的路径；思路：1、用DFS遍历所有的节点；
2、以第一步遍历到的当前节点为根节点，
用DFS_Path找它有几条等于sum的路径。
*/
void dfs_sum(struct TreeNode* root, int target, int *ret)
{
	if (target == 0) {
		(*ret)++;
	}

	if (root->left)
		dfs_sum(root->left, target - root->left->val, ret);
	if (root->right)
		dfs_sum(root->right, target - root->right->val, ret);
}


void dfs_for_each_node(struct TreeNode* root, int sum, int *ret)
{
	if (root == NULL)
		return;

	//dfs_sum(root, sum - root->val, ret);
	dfs_for_each_node(root->left, sum, ret);
	//dfs_sum(root, sum - root->val, ret);
	dfs_for_each_node(root->right, sum, ret);
	dfs_sum(root, sum - root->val, ret);
}

int pathSum(struct TreeNode* root, int sum)
{
	int ret = 0;
	dfs_for_each_node(root, sum, &ret);
	return ret;
}


/*
面试题 04.08. 首个共同祖先
难度中等7
设计并实现一个算法，找出二叉树中某两个节点的第一个共同祖先。不得将其他的节点存储在另外的数据结构中。注意：这不一定是二叉搜索树。
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

/*
思路
分析
对于当前的根节点root
若root为空，直接返回root，表示没有找到目标
若root为p或q
若左子树或右子树中含有另外一个目标节点，那么root就是最终答案，返回root
否则，也应当返回root，表示找到了其中一个目标
否则
若左子树和右子树分别含有p、q中的一个，那么root就是最终答案，返回root
否则
若两子树中含有p或q中的一个，即返回那个节点，表示找到了其中一个目标
否则返回nullptr，表示没有找到目标
整理
经过整理我们发现
若root为p或q，无论子树是否含有另外一个目标，都应该返回root
另外，当左右子树的均含有目标节点时，返回root，否则只需返回找到的目标节点或空指针
算法
若root为空或root == p或root == q，返回root
分别将root->left、root->right作为根节点，调用自身，得到返回值left、right
若left不为空
若right不为空，返回root
否则返回left
否则返回right

*/
struct TreeNode* lowestCommonAncestor
	(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
	if (root == NULL)
		return NULL;

	struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
	struct TreeNode* right = lowestCommonAncestor(root->right, p, q);
	if (root == p || root == q)
		return root;
	else if (left != NULL && right != NULL)
		return root;
	else if (left != NULL)
		return left;
	else
		return right;
}

/*
116. 填充每个节点的下一个右侧节点指针
给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。
*/
void dfs(struct Node* root, struct Node* next)
{
	if (root == NULL)
		return;

	root->next = next;
	dfs(root->left, root->right);
	dfs(root->right, root->next != NULL ? root->next->left : NULL);
}

struct Node* connect(struct Node* root)
{
	dfs(root, NULL);
	return root;
}

/*
654. 最大二叉树
给定一个不含重复元素的整数数组。一个以此数组构建的最大二叉树定义如下：

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
652. 寻找重复的子树
给定一棵二叉树，返回所有重复的子树。对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。

两棵树重复是指它们具有相同的结构以及相同的结点值。

示例 1：

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
下面是两个重复的子树：

      2
     /
    4
和

    4
*/

char* dfs(struct TreeNode* root, struct HashTable *ht)
{
	if (root == NULL) {
		return "#";
	}

	char* string = calloc(20000, sizeof(char));
	sprintf(string, "%d ", root->val);
	strcat(string, dfs(root->left, ht));
	strcat(string, dfs(root->right, ht));

	struct DataEntry cmpEntry;
	cmpEntry.key = string;
	struct DataEntry *find = hashFind(ht, &cmpEntry);
	if (find == NULL) {
		struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		entry->key = string;
		entry->root = root;
		entry->value = 1;
		HashAdd(ht, &entry->node);
	} else {
		find->value++;
	}

	return string;
}

struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize)
{
	*returnSize = 0;

	if (root == NULL) {
		return NULL;
	}

	struct HashTable dht;
	struct HashTable *ht = &dht;
	HashInit(ht, 40960, hashequal_str, hashcode_str);

	dfs(root, ht);
    	struct TreeNode** recordData = calloc(40960, sizeof(struct TreeNode*));

	for (size_t i = 0; i < ht->bktSize; i++) {
		if (!ListEmpty(&ht->bkts[i])) {
			struct Node *node = NULL;
			LIST_FOR_EACH(node, &ht->bkts[i]) {
				struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
				if (entry->value > 1) {
					recordData[*returnSize] = entry->root;
					(*returnSize)++;
				}
			}
		}
	}

	return recordData;
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
// 递归
void flatten(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}
	flatten(root->left);
	flatten(root->right);
	if (root->left != NULL) {
		struct TreeNode* lr = root->left;
		while (lr->right != NULL) {
			lr = lr->right;
		}
		lr->right = root->right;
		root->right = root->left;
		root->left = NULL;
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


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
    if ((preorderSize == 0) || (inorderSize == 0)) {
        return NULL;
    }
    struct TreeNode* res = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    res->val = *preorder;
    res->left = NULL;
    res->right = NULL;
    int posion = 0;
    for (int i = 0; i < preorderSize; i++) {
        if (*preorder == inorder[i]) {
            posion = i;
            break;
        }
    }
    res->left = buildTree(preorder + 1, posion, inorder, posion);
    res->right = buildTree(preorder + posion + 1, inorderSize - posion - 1,
                           inorder + posion + 1, inorderSize - posion - 1);
    return res;
}

/*
951. 翻转等价二叉树
难度中等41
我们可以为二叉树 T 定义一个翻转操作，如下所示：选择任意节点，然后交换它的左子树和右子树。
只要经过一定次数的翻转操作后，能使 X 等于 Y，我们就称二叉树 X 翻转等价于二叉树 Y。
编写一个判断两个二叉树是否是翻转等价的函数。这些树由根节点 root1 和 root2 给出。

*/
bool flipEquiv(struct TreeNode* root1, struct TreeNode* root2)
{
	if (root1 == NULL && root2 == NULL) return true;

	if (root1 == NULL || root2 == NULL) return false;

	return (root1->val == root2->val) &&
		(flipEquiv(root1->right, root2->left) && flipEquiv(root1->left, root2->right) ||
		flipEquiv(root1->right, root2->right) && flipEquiv(root1->left, root2->left));
}

/*
1110. 删点成林
难度中等46
给出二叉树的根节点 root，树上每个节点都有一个不同的值。
如果节点值在 to_delete 中出现，我们就把该节点从树上删去，最后得到一个森林（一些不相交的树构成的集合）。
返回森林中的每棵树。你可以按任意顺序组织答案。

示例：

输入：root = [1,2,3,4,5,6,7], to_delete = [3,5]
输出：[[1,2,null,4],[6],[7]]

*/

#define MAX 1000
struct TreeNode **g_res;
int resIndex;

bool isDelete(struct TreeNode* root, int* to_delete, int to_deleteSize)
{
    for (int i = 0; i < to_deleteSize; i++) {
        if (root->val == to_delete[i]) {
            return true;
        }
    }
    return false;
}

void dfs(struct TreeNode* root, int* to_delete, int to_deleteSize)
{
    if (root == NULL) {
        return;
    }
    if(isDelete(root, to_delete, to_deleteSize)) {
        struct TreeNode* deleteNode = root;
        if (deleteNode->left != NULL) {
            g_res[resIndex] = deleteNode->left;
            resIndex++;
            dfs(deleteNode->left, to_delete, to_deleteSize);
        }
        if (deleteNode->right != NULL) {
            g_res[resIndex] = deleteNode->right;
            resIndex++;
            dfs(deleteNode->right, to_delete, to_deleteSize);
        }
        return;
    }
    if (root->left != NULL) {
        if(isDelete(root->left, to_delete, to_deleteSize)) {
            struct TreeNode* deleteNode = root->left;
            root->left = NULL;
            if (deleteNode->left != NULL) {
                g_res[resIndex] = deleteNode->left;
                resIndex++;
                dfs(deleteNode->left, to_delete, to_deleteSize);
            }
            if (deleteNode->right != NULL) {
                g_res[resIndex] = deleteNode->right;
                resIndex++;
                dfs(deleteNode->right, to_delete, to_deleteSize);
            }
        } else {
            dfs(root->left, to_delete, to_deleteSize);
        }
    }
    if (root->right != NULL) {
        if(isDelete(root->right, to_delete, to_deleteSize)) {
            struct TreeNode* deleteNode = root->right;
            root->right = NULL;
            if (deleteNode->left != NULL) {
                g_res[resIndex] = deleteNode->left;
                resIndex++;
                dfs(deleteNode->left, to_delete, to_deleteSize);
            }
            if (deleteNode->right != NULL) {
                g_res[resIndex] = deleteNode->right;
                resIndex++;
                dfs(deleteNode->right, to_delete, to_deleteSize);
            }
        } else {
            dfs(root->right, to_delete, to_deleteSize);
        }
    }
}

struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize)
{
    resIndex = 0;
    if (root == NULL) {
        return NULL;
    }
    if (to_delete == NULL) {
        return root;
    }
    g_res = (struct TreeNode** )malloc(sizeof(struct TreeNode *) * MAX);
    for (int i = 0; i < MAX; i++) {
        g_res[i] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    }
    g_res[resIndex++] = root;
    dfs(root, to_delete, to_deleteSize);
    // printf("right = %d ", g_res[0]->right->val);
    struct TreeNode **res = (struct TreeNode** )malloc(sizeof(struct TreeNode *) * resIndex);
    for (int i = 0; i < resIndex; i++) {
        res[i] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    }
    int fallyNum = 0;
    for (int i = 0; i < resIndex; i++)
    {
        if (isDelete(g_res[i], to_delete, to_deleteSize) == false) {
            res[fallyNum] = g_res[i];
            fallyNum++;
        }
    }
    *returnSize = fallyNum;
    return res;
}

