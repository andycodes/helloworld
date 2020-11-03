
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

/*
199. 二叉树的右视图
难度中等271
给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
示例:
输入: [1,2,3,null,5,null,4]
输出: [1, 3, 4]
解释:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---

*/
#define MAX 1024 * 1024
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize)
{
	int *res = (int *)calloc(MAX, sizeof(int));
	*returnSize = 0;

	if (root == NULL)
		return res;

	struct TreeNode* queue[MAX];
	int head = 0;
	int rear = 0;

	queue[rear++] = root;

	while(head != rear) {
		int floorSize = rear - head;
		while(floorSize) {
			struct TreeNode* pop = queue[head++];

			if (floorSize == 1) {
				res[*returnSize] = pop->val;
				(*returnSize)++;
			}

			if (pop->left)
				queue[rear++] = pop->left;

			if (pop->right)
				queue[rear++] = pop->right;

			floorSize--;
		}
	}

	return res;
}

#define MAX 1024 * 1024
void dfs(struct TreeNode* root, int deep, int *res, int* returnSize)
{
	if (root == NULL)
		return;

	if (*returnSize == deep) {// 当数组长度等于当前 深度 时, 把当前的值加入数组
		res[*returnSize] = root->val;
		(*returnSize)++;
	}

	dfs(root->right, deep + 1, res, returnSize); // 先从右边开始, 当右边没了, 再轮到左边
	dfs(root->left, deep + 1, res, returnSize);
}

int* rightSideView(struct TreeNode* root, int* returnSize)
{
	int *res = (int *)calloc(MAX, sizeof(int));
	*returnSize = 0;

	if (root == NULL)
		return res;

	dfs(root, 0, res, returnSize);
	return res;
}

/*
863. 二叉树中所有距离为 K 的结点
给定一个二叉树（具有根结点 root）， 一个目标结点 target ，和一个整数值 K 。

返回到目标结点 target 距离为 K 的所有结点的值的列表。 答案可以以任何顺序返回。



示例 1：

输入：root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
输出：[7,4,1]
解释：
所求结点为与目标结点（值为 5）距离为 2 的结点，
值分别为 7，4，以及 1
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 /*
首先使用 DFS 遍历二叉树，为每个节点保存其父结点；
使用 BFS 向三个方向搜索（左孩子、右孩子、父结点），当搜索第 K 次时，队列中的全部结点即为所求；

注意：

BFS 要保存已访问结点；
每次都将当前队列中全部元素向外延伸一个结点；

 */
void dfs(struct List *listFather, struct TreeNode* root, struct TreeNode* father)
{
	if (root == NULL) {
		return;
	}

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->cur = root;
	entry->father = father;
	entry->visited = 0;
	ListAddTail(listFather, &entry->node);

	dfs(listFather, root->left, root);
	dfs(listFather, root->right, root);
}

void setVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			entry->visited = 1;
		}
	}
}

bool checkVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->visited;
		}
	}

	return false;
}

struct TreeNode* getFather(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->father;
		}
	}

	return NULL;
}


int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
	struct List dListFather;
	struct List *listFather = &dListFather;

	ListInit(listFather);
	dfs(listFather, root, NULL); //记录父结点

	struct List dqueue;
	struct List *queue = &dqueue;

	queue_init(queue);

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->cur = target;
	ListAddTail(queue, &entry->node);
	setVisited(listFather, target);

	while(!queue_empty(queue)) {
		if (K-- == 0) {
			*returnSize = 0;
			int *res = (int *)calloc(2048, sizeof(int));
			while(!queue_empty(queue)) {
				struct DataEntry *pop = queue_pop_entry(queue);
				res[*returnSize] = pop->cur->val;
				(*returnSize)++;
			}

			return res;
		}

		int qSize = queue_size(queue);
		for (int i = 0; i < qSize; i++) {
			struct DataEntry *pop = queue_pop_entry(queue);
			if (pop->cur->left && !checkVisited(listFather, pop->cur->left)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->left;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->left);
			}

			if (pop->cur->right && !checkVisited(listFather, pop->cur->right)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->right;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->right);
			}

			struct TreeNode* father = getFather(listFather, pop->cur);
			if (father != NULL && !checkVisited(listFather, father)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = father;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, father);
			}
		}
	}

	return NULL;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define MAXSIZE 510
struct TreeNode** parent_array;
int flag[MAXSIZE];
int count;

void get_parent(struct TreeNode* node, struct TreeNode** parent_array);
void dfs(struct TreeNode* node, int K, int dis, int* res);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
    if (root == NULL || target == NULL || K < 0 || K > 500) {
        *returnSize = 0;
        return NULL;
    }

    // 父结点数组申请内存
    parent_array = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAXSIZE);
    memset(parent_array, 0, MAXSIZE * sizeof(struct TreeNode*));
    // flag数组初始化，用于标记访问过的结点
    memset(flag, 0, MAXSIZE * sizeof(int));
    // 存放满足要求的结点值的结果数组
    int *res = (int *)malloc(sizeof(int) * MAXSIZE);
    memset(res, -1, MAXSIZE * sizeof(int));

    // 二叉树遍历找到每个结点的父结点，将该结点的值作为parent_array的索引，在parent_array中存放对应父结点
    get_parent(root, parent_array);

    // DFS搜索
    count = 0;
    flag[target->val] = 1;
    dfs(target, K, 0, res);

    // 返回结果
    *returnSize = count;
    return res;
}

void get_parent(struct TreeNode* node, struct TreeNode** parent_array)
{
    if (node->right != NULL) {
        parent_array[node->right->val] = node;
        get_parent(node->right, parent_array);
    }
    if (node->left != NULL) {
        parent_array[node->left->val] = node;
        get_parent(node->left, parent_array);
    }
}

void dfs(struct TreeNode* node, int K, int dis, int* res)
{
    if (dis == K) {
        res[count] = node->val;
        count++;
        return;
    }

    if (node->left != NULL && flag[node->left->val] != 1) {
        flag[node->left->val] = 1;
        dfs(node->left, K, dis + 1, res);
    }

    if (node->right != NULL && flag[node->right->val] != 1) {
        flag[node->right->val] = 1;
        dfs(node->right, K, dis + 1, res);
    }

    if (parent_array[node->val] != 0 && flag[parent_array[node->val]->val] != 1) {
        flag[parent_array[node->val]->val] = 1;
        dfs(parent_array[node->val], K, dis + 1, res);
    }
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


