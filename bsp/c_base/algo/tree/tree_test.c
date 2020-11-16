
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
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
			g_res[resIndex++] = deleteNode->left;
			dfs(deleteNode->left, to_delete, to_deleteSize);
		}

		if (deleteNode->right != NULL) {
			g_res[resIndex++] = deleteNode->right;
			dfs(deleteNode->right, to_delete, to_deleteSize);
		}
		return;
	}

	if (root->left != NULL) {
		if(isDelete(root->left, to_delete, to_deleteSize)) {
			struct TreeNode* deleteNode = root->left;
			root->left = NULL;
			if (deleteNode->left != NULL) {
				g_res[resIndex++] = deleteNode->left;
				dfs(deleteNode->left, to_delete, to_deleteSize);
			}
			if (deleteNode->right != NULL) {
				g_res[resIndex++] = deleteNode->right;
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
				g_res[resIndex++] = deleteNode->left;
				dfs(deleteNode->left, to_delete, to_deleteSize);
			}
			if (deleteNode->right != NULL) {
				g_res[resIndex++] = deleteNode->right;
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
	if (root == NULL || to_delete == NULL) {
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
	for (int i = 0; i < resIndex; i++) {
		if (isDelete(g_res[i], to_delete, to_deleteSize) == false) {
			res[fallyNum] = g_res[i];
			fallyNum++;
		}
	}

	*returnSize = fallyNum;
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MAXSIZE 510
struct TreeNode** parent;   //用于保存节点的父节点的数组
int flag[MAXSIZE];          //用于标记是否已访问的数组：值为0表示未访问；值未1表示已访问
int cnt;                    //用于记录合条件的节点个数

//遍历二叉树，将所有节点的父节点存储在parent数组中
void get_parent(struct TreeNode* p, struct TreeNode** parent)
{
    //如果当前节点p有左孩子
    if(p->left != NULL)
    {
        parent[p->left->val] = p;      //则将左孩子值位置的parent数组值置为p
        get_parent(p->left, parent);   //递归遍历当前节点的左孩子
    }
    //如果当前节点p有右孩子
    if(p->right != NULL)
    {
        parent[p->right->val] = p;    //将右孩子值位置的parent数组值置为p
        get_parent(p->right, parent); //递归遍历当前节点的右孩子
    }
}
//该函数的结果就是，当前节点值为i，则parent[i]就是当前节点的父节点


//深度优先搜索函数：从p的父节点、左孩子、右孩子 三个方向进行搜索
void dfs(struct TreeNode*p, int K, int curdis, int* res)
{
    //如果当前距离为K，则该节点就是要找的节点
    if(curdis == K)
    {
        res[cnt] = p->val;   //将节点值存储在结果数组中
        cnt++;               //cnt++继续进行下一个节点的寻找
        return;
    }

    //如果p的左孩子存在，且左孩子还未被访问过
    if(p->left!=NULL  &&  flag[p->left->val]!=1)
    {
        flag[p->left->val] = 1;            //则标记p的左孩子为已访问
        dfs(p->left, K, curdis+1, res);    //递归遍历p的左孩子
    }
    //如果p的右孩子存在，且右孩子还未被访问过
    if(p->right!=NULL  &&  flag[p->right->val]!=1)
    {
        flag[p->right->val] = 1;           //则标记p的右孩子为已访问
        dfs(p->right, K, curdis+1, res);   //递归遍历p的右孩子
    }

    //如果p的父节点存在，且父节点还未被访问过
    if(parent[p->val]!=0  &&  flag[parent[p->val]->val]!=1)
    {
        flag[parent[p->val]->val] = 1;        //则标记p的父节点为已访问
        dfs(parent[p->val], K, curdis+1, res);//递归遍历p的父节点
    }
}


int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
    //特殊处理
    if(root==NULL || target==NULL || K<0 || K>100)
    {
        *returnSize = 0;
        return NULL;
    }

    //给parent数组申请动态内存并初始化
    parent = malloc(sizeof(struct TreeNode*) * MAXSIZE);
    memset(parent, 0, sizeof(struct TreeNode*)*MAXSIZE);

    //初始化flag数组
    memset(flag, 0, sizeof(int)*MAXSIZE);

    //定义一个结果数组并申请动态内存，初始化
    int* res = malloc(sizeof(int)*MAXSIZE);
    memset(res, -1, sizeof(int)*MAXSIZE);

    //遍历所有的节点，并保存节点们的父节点
    get_parent(root, parent);

    cnt = 0;
    flag[target->val] = 1;   //将target节点标记为已访问
    dfs(target, K, 0, res);  //搜索

    *returnSize = cnt;
    return res;
}

// 创建一个指向当前节点父亲的哈希表 father[5] = 3 C语言怎么搞树节点啊
void dfs(struct TreeNode* root, struct TreeNode** father, struct TreeNode* pre) {
    if (root != NULL) {
        father[root->val] = pre;
        dfs(root->left, father, root);
        dfs(root->right, father, root);
    }
}
int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize) {
    struct TreeNode* father[501];
    int visit[501] = {0};
    dfs(root, father, NULL);

    struct TreeNode* queue[501];
    int front = 0;
    int rear = 1;
    queue[front] = target;
    while (front < rear) {
        if (K-- == 0) {
            printf("  ");
            int *res = (int *)malloc(sizeof(int) * 501);
            *returnSize = 0;
            for (int i = front; i < rear; i++) {
                res[*returnSize] = queue[i]->val;
                (*returnSize)++;
            }
            return res;
        }
        int len =  rear - front;
        for (int j = 0; j < len; j++) {
            if (father[queue[front]->val] != NULL && visit[queue[front]->val] == 0) {
                queue[rear] = father[queue[front]->val];
                visit[queue[front]->val] = 1;
                rear++;
            }
            if (queue[front]->left != NULL && visit[queue[front]->left->val] == 0) {
                queue[rear] = queue[front]->left;
                visit[queue[front]->left->val] = 1;
                rear++;
            }
            if (queue[front]->right != NULL && visit[queue[front]->right->val] == 0) {
                queue[rear] = queue[front]->right;
                visit[queue[front]->right->val] = 1;
                rear++;
            }
            front++;
        }

    }
    *returnSize = 0;
    return NULL;
}


/*
337. 打家劫舍 III
在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

示例 1:

输入: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \
     3   1

输出: 7
解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int rob(struct TreeNode *root)
{
    if (root == NULL) return 0;

    int money = root->val;
    if (root->left != NULL) {
        money += (rob(root->left->left) + rob(root->left->right));
    }

    if (root->right != NULL) {
        money += (rob(root->right->left) + rob(root->right->right));
    }

    return fmax(money, rob(root->left) + rob(root->right));
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct SubtreeStatus {
    int selected;
    int notSelected;
};

struct SubtreeStatus dfs(struct TreeNode *root) {
    if (!root) {
        return (struct SubtreeStatus){0, 0};
    }
    struct SubtreeStatus l = dfs(root->left);
    struct SubtreeStatus r = dfs(root->right);
    int selected = root->val + l.notSelected + r.notSelected;
    int notSelected = fmax(l.selected, l.notSelected) + fmax(r.selected, r.notSelected);
    return (struct SubtreeStatus){selected, notSelected};
}

int rob(struct TreeNode *root) {
    struct SubtreeStatus rootStatus = dfs(root);
    return fmax(rootStatus.selected, rootStatus.notSelected);
}

/*
563. 二叉树的坡度
给定一个二叉树，计算 整个树 的坡度 。

一个树的 节点的坡度 定义即为，该节点左子树的节点之和和右子树节点之和的 差的绝对值 。如果没有左子树的话，左子树的节点之和为 0 ；没有右子树的话也是一样。空结点的坡度是 0 。

整个树 的坡度就是其所有节点的坡度之和。
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int tilt=0;
int traverse(struct TreeNode * root)
    {
        if(root==NULL )
            return 0;
        int left=traverse(root->left);
        int right=traverse(root->right);
        tilt+=fabs(left-right);
        return left+right+root->val;
    }

int findTilt(struct TreeNode * root)
{
	tilt = 0;
	traverse(root);
        return tilt;
}