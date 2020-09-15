/*
二叉搜索树的性质：
左子数的所有节点值小于根节点的值
右子数的所有节点值大于根节点的值

实在不会做的---有序数组
*/

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


/*
669. 修剪二叉搜索树
给定一个二叉搜索树，同时给定最小边界L?和
最大边界?R。通过修剪二叉搜索树，使得所有
节点的值在[L, R]中 (R>=L) 。你可能需要改变树的根节点，
所以结果应当返回修剪好的二叉搜索树的新的根节点。
输入:
    1
   / \
  0   2

  L = 1
  R = 2

输出:
    1
      \
       2
*/
struct TreeNode* trimBST(struct TreeNode* root, int L, int R)
{
        if (root ==  NULL)
			return root;
        if (root->val > R)
			return trimBST(root->left, L, R);
        if (root->val < L)
			return trimBST(root->right, L, R);

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
}


/*
783. 二叉搜索树节点最小距离
二叉搜索树的中序遍历是升序数组。
比如对于样例输入 root = [4,2,6,1,3,null,null]，
中序遍历的结果就是 [1, 2, 3, 4, 6]。
题目要求两个结点的最小距离，
就是要求中序遍历数组里相邻
两个元素差的最小值。
*/
int min;
struct TreeNode* pre = NULL;

void InOrder(struct TreeNode* root)
{
	if(root==NULL)
		return;
	InOrder(root->left);
	min = pre == NULL ? min : fmin(min, root->val - pre->val);
	pre = root;
	InOrder(root->right);
}

int minDiffInBST(struct TreeNode* root)
{
    min = INT_MAX;
    pre = NULL;
    InOrder(root);
    return min;
}


/*
897. 递增顺序查找树
给定一个树，按中序遍历重新排列树，
使树中最左边的结点现在是树的根，
并且每个结点没有左子结点，只有一个右子结点。

示例 ：

输入：[5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

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
            \
             7
              \
               8
                \
                 9

*/
struct TreeNode* prev;
 void inorder(struct TreeNode* node)
 {
	if (node == NULL)
		return;

	inorder(node->left);

	node->left = NULL;
	prev->right = node;
	prev = node;

	inorder(node->right);
}

struct TreeNode* increasingBST(struct TreeNode* root)
{
	struct TreeNode* ans = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
	prev = ans;
	inorder(root);
	return ans->right;
}

/*
108. 将有序数组转换为二叉搜索树
将一个按照升序排列的有序数组，
转换为一棵高度平衡二叉搜索树。
本题中，一个高度平衡二叉树是指
一个二叉树每个节点 的左右两个子树的
高度差的绝对值不超过 1。
示例:
给定有序数组: [-10,-3,0,5,9],
一个可能的答案是：[0,-3,9,-10,null,5]，
它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5
*/
struct TreeNode* ToBST(int nums[],int left,int right)
{
	if (left > right)
		return NULL;

 	int mid = left + (right - left >> 1);
	struct TreeNode *root = malloc(sizeof(struct TreeNode));
	root->val = nums[mid];
	root->left = ToBST(nums,left,mid-1);//注意mid-1 对左半部分进行递归
	root->right = ToBST(nums,mid+1,right);//注意mid+1 对右半部分进行递归
	return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize)
{
    return ToBST(nums,0,numsSize-1);
}

/*
给定一个二叉搜索树，
编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。

说明：
你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。

*/
/*中序遍历(生成器)+提前终止*/
void dfs(struct TreeNode* root, int k, int *cnt, int *ret)
{
    if(root == NULL)
        return;

    dfs(root->left, k, cnt, ret);
    if(++ (*cnt) ==k) {
        *ret = root->val;
        return;
    }
    dfs(root->right, k, cnt, ret);
}

int kthSmallest(struct TreeNode* root, int k){
    int ret = 0;
    int i = 0;
    dfs(root,k, &i,&ret);
    return ret;
}

/*
285. 二叉搜索树中的顺序后继
给你一个二叉搜索树和其中的某一个结点，请你找出该结点在
树中顺序后继的节点。
结点 p 的后继是值比 p.val 大的结点中键值最小的结点。

*/

/*
循环实现
如果当前值是<=x的，那么根据BST的特性只需要在右子树中
找：cur=cur.right。
如果当前值>x，则当前值有可能，它的左子树也有可能有
更小的但是也>x的。则每次走入这个分支时，当前点是一个
候选点，记录该节点的值和历史最小节点的值。
时间O(logN)，空间O(1）

*/
struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p)
{
	if (root == NULL || p == NULL) {
		return NULL;
	}

	struct TreeNode* cur = root;
	struct TreeNode* res = NULL;

	while (cur != NULL) {
		if (cur->val <= p->val) {
			cur = cur->right;
		} else {
			if (res == NULL || res->val > cur->val) {
				res = cur;
			}
			cur = cur->left;
		}
	}

	return res;
}

/*
98. 验证二叉搜索树
给定一个二叉树，判断其是否是一个有效的二叉搜索树。
假设一个二叉搜索树具有如下特征：
节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
*/
bool dfs(struct TreeNode* root, long low, long high)
{
	if (root == NULL)
		return true;

	long num = root->val;
	if (num <= low || num >= high)
		return false;

	return dfs(root->left, low, num) && dfs(root->right, num, high);
}
bool isValidBST(struct TreeNode* root)
{
	return dfs(root, LONG_MIN, LONG_MAX);
}


/*
 * 前序遍历"二叉树"
 前序遍历 - 根->左->右
 */
void preorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	printf("%d ", root->val);
	preorder_bstree(root->left);
	preorder_bstree(root->right);
}

/*
 * 中序遍历"二叉树"
 中序遍历 - 左->根->右
 */
void inorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	inorder_bstree(root->left);
	printf("%d ", root->val);
	inorder_bstree(root->right);
}

/*
 * 后序遍历"二叉树"
 后序遍历 - 左->右->根
 */
void postorder_bstree(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}

	postorder_bstree(root->left);
	postorder_bstree(root->right);
	printf("%d ", root->val);
}

/*
 * (递归实现)查找"二叉树x"中键值为key的节点
 */
struct TreeNode* bstree_search(struct TreeNode* root, int val)
{
	if (root==NULL || root->val==val)
		return root;

	if (val < root->val)
		return bstree_search(root->left, val);
	else
		return bstree_search(root->right, val);
}


/*
 * 查找最小结点：返回tree为根结点的二叉树的最小结点。
 */
struct TreeNode* bstree_minimum(struct TreeNode* root)
{
	if (root == NULL)
		return NULL;

	while(root->left != NULL)
		root = root->left;
	return root;
}

/*
 * 查找最大结点：返回tree为根结点的二叉树的最大结点。
 */
struct TreeNode* bstree_maximum(struct TreeNode* root)
{
	if (root == NULL)
		return NULL;

	while(root->right != NULL)
		root = root->right;
	return root;
}

/*
 * 删除结点(z)，并返回根节点
 *
 * 参数说明：
 *     root 二叉树的根结点
 *     z 删除的结点
 * 返回值：
 *     根节点
 */
static struct TreeNode* bstree_delete(struct TreeNode* root, struct TreeNode *z)
{
	struct TreeNode *root=NULL;
    struct TreeNode *y=NULL;

	if ((z->left == NULL) || (z->right == NULL) )
		y = z;
	else
		y = bstree_successor(z);

	if (y->left != NULL)
		root = y->left;
	else
		root = y->right;

	if (root != NULL)
		root->parent = y->parent;

	if (y->parent == NULL)
		root = root;
	else if (y == y->parent->left)
		y->parent->left = root;
	else
		y->parent->right = root;

	if (y != z)
		z->val = y->val;

	if (y!=NULL)
		free(y);

	return root;
}

/*
 * 删除结点(key为节点的键值)，并返回根节点
 *
 * 参数说明：
 *     root 二叉树的根结点
 *     z 删除的结点
 * 返回值：
 *     根节点
 */
struct TreeNode* delete_bstree(struct TreeNode* root, Type val)
{
	struct TreeNode *z, *node;

	if ((z = bstree_search(root, val)) != NULL)
		root = bstree_delete(root, z);

	return root;
}


 /*
270. 最接近的二叉搜索树值
难度简单31
给定一个不为空的二叉搜索树和一个目标值 target，请在该二叉搜索树中找到最接近目标值 target 的数值。
注意：
"	给定的目标值 target 是一个浮点数
"	题目保证在该二叉搜索树中只会存在一个最接近目标值的数
示例：
输入: root = [4,2,5,1,3]，目标值 target = 3.714286

    4
   / \
  2   5
 / \
1   3

输出: 4

 */
int closestValue(struct TreeNode* root, double target)
{
        int l = root->val, r = root->val;
        while(root){
            if(target < root->val){
                r = root->val;
                root = root->left;
            }else if(target > root->val){
                l = root->val;
                root = root->right;
            }else
                return root->val;
        }
        return fabs(target - l) < fabs(r - target) ? l:r;
}

 int closestValue(struct TreeNode* root, double target)
{
	int val;
	int closest = root->val;

	while(root != NULL) {
		val = root->val;
		closest = fabs(val - target) < fabs(closest - target) ? val : closest;
		root = target < root->val ? root->left : root->right;
	}

	return closest;
}

/*
109. 有序链表转换二叉搜索树
难度中等277
给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
示例:
给定的有序链表： [-10, -3, 0, 5, 9],

一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5

*/
struct ListNode* preMid(struct ListNode *head){       //找链表中间结点的前一个结点
    struct ListNode* slow=head,*fast=head,*preslow=head;
    while(fast!=NULL&&fast->next!=NULL)
    {
        preslow=slow;
        slow=slow->next;
        fast=fast->next->next;
    }
    return preslow;
}
struct TreeNode* newTreeNode(int x){
    struct TreeNode* root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val=x;
    root->left=root->right=NULL;
    return root;
}
struct TreeNode* sortedListToBST(struct ListNode* head){
    if(head==NULL) return NULL;                             //递归的终止条件:链表中只有0或1个元素
    if(head->next==NULL) return newTreeNode(head->val);
    struct ListNode* premid=preMid(head);
    struct ListNode* mid=premid->next;
    premid->next=NULL;              //断开链表 分为前后两部分
    struct TreeNode* root=newTreeNode(mid->val);
    root->left=sortedListToBST(head);
    root->right=sortedListToBST(mid->next);
    return root;
}

/*
面试题 17.12. BiNode
二叉树数据结构TreeNode可用来表示单向链表（其中left置空，right为下一个链表节点）。实现一个方法，把二叉搜索树转换为单向链表，要求依然符合二叉搜索树的性质，转换操作应是原址的，也就是在原始的二叉搜索树上直接修改。

返回转换后的单向链表的头节点。

注意：本题相对原题稍作改动



示例：

输入： [4,2,5,1,3,null,6,0]
输出： [0,null,1,null,2,null,3,null,4,null,5,null,6]
*/
/**
 * Definition for a binary root node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode *cur;
    void inOrder(struct TreeNode* node)
    {
        if(node==NULL)  return ;
        inOrder(node->left);
        node->left=NULL;    //将该节点的左孩子设为NULL
        cur->right=node;    //将该节点赋给上一个节点的右孩子
        cur=node;           //更新cur
        inOrder(node->right);
    }
struct TreeNode* convertBiNode(struct TreeNode* root)
{
    struct TreeNode *ans = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
        cur = ans;
        inOrder(root);
        return ans->right;
}

/*
1038. 从二叉搜索树到更大和树
给出二叉 搜索 树的根节点，该二叉树的节点值各不相同，修改二叉树，使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。
*/

/**
 * Definition for a binary root node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int sum = 0;
struct TreeNode* backingInOrder(struct TreeNode* root)
{
	if (root == NULL) {
		return NULL;
	}

	backingInOrder(root->right);
	sum = sum + root->val;
	root->val = sum;
	backingInOrder(root->left);
	return root;
}

struct TreeNode* bstToGst(struct TreeNode* root)
{
	sum = 0;
	return backingInOrder(root);
}

/*
1382. 将二叉搜索树变平衡
给你一棵二叉搜索树，请你返回一棵 平衡后 的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。

如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 1 ，我们就称这棵二叉搜索树是 平衡的 。

如果有多种构造方法，请你返回任意一种。


*/

/**
 * Definition for a binary root node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void func(struct TreeNode* root,int *re,int *returnSize){
    if(root)//中序遍历二叉搜索树得到一个递增数组
    {
        func(root->left,re,returnSize);
        re[(*returnSize)++]=root->val;
        func(root->right,re,returnSize);
    }
}
struct TreeNode* createTree(int *nums,int numsSize){
    //利用一个递增数组创建平衡二叉搜索树
    if(numsSize==0) return NULL;
    struct TreeNode *node=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val=nums[numsSize/2];
    node->left=createTree(nums,numsSize/2);
    node->right=createTree(&nums[numsSize/2+1],numsSize-1-numsSize/2);
    return node;
}
struct TreeNode* balanceBST(struct TreeNode* root){
    int numsSize=0,nums[10000]={0};
    func(root,nums,&numsSize);
    return createTree(nums,numsSize);
}


/*
1373. 二叉搜索子树的最大键值和
给你一棵以 root 为根的 二叉树 ，请你返回 任意 二叉搜索子树的最大键值和。

二叉搜索树的定义如下：

任意节点的左子树中的键值都 小于 此节点的键值。
任意节点的右子树中的键值都 大于 此节点的键值。
任意节点的左子树和右子树都是二叉搜索树。

*/
 int result = 0;
struct Result{
    bool isBST;
    int sum;
    int minLeft;
    int maxLeft;
};

     struct Result* isBST(struct TreeNode *root){
        if(root == NULL){
            return NULL;
        }

	struct Result *res = (struct Result *)calloc(1, sizeof(struct Result));
        res->isBST = true;
        res->sum = root->val;
        res->maxLeft = root->val;
        res->minLeft = root->val;
        if(root->left == NULL && root->right == NULL){
            res->sum = root->val;
            res->isBST = true;
            res->minLeft = root->val;
            res->maxLeft = root->val;
            result = fmax(result,res->sum);
            return res;
        }else{
            struct Result* leftRes = isBST(root->left);
            struct Result* rightRes = isBST(root->right);
            if(leftRes!=NULL){
                res->isBST = res->isBST&&leftRes->isBST&&(root->val>leftRes->maxLeft);
                res->sum += leftRes->sum;
                res->maxLeft = fmax(leftRes->maxLeft,res->maxLeft);
                res->minLeft = fmin(leftRes->minLeft,res->minLeft);
            }
            if(rightRes != NULL){
                res->isBST = res->isBST&&rightRes->isBST&&(root->val<rightRes->minLeft);
                res->sum += rightRes->sum;
                res->maxLeft = fmax(rightRes->maxLeft,res->maxLeft);
                res->minLeft = fmin(rightRes->minLeft,res->minLeft);
            }
            if(res->isBST){
                result = fmax(result,res->sum);
            }
            return res;
        }
    }

int maxSumBST(struct TreeNode* root){
	result = 0;
		isBST(root);
        return result;
}


/*
776. 拆分二叉搜索树
给你一棵二叉搜索树（BST）、它的根结点 root 以及目标值 V。

请将该树按要求拆分为两个子树：其中一个子树结点的值都必须小于等于给定的目标值 V；另一个子树结点的值都必须大于目标值 V；树中并非一定要存在值为 V 的结点。

除此之外，树中大部分结构都需要保留，也就是说原始树中父节点 P 的任意子节点 C，假如拆分后它们仍在同一个子树中，那么结点 P 应仍为 C 的子结点。

你需要返回拆分后两个子树的根结点 TreeNode，顺序随意。



示例：

输入：root = [4,2,6,1,3,5,7], V = 2
输出：[[2,1],[4,3,6,null,null,5,7]]
解释：
注意根结点 output[0] 和 output[1] 都是 TreeNode 对象，不是数组。

给定的树 [4,2,6,1,3,5,7] 可化为如下示意图：

          4
        /   \
      2      6
     / \    / \
    1   3  5   7

输出的示意图如下：

          4
        /   \
      3      6       和    2
            / \           /
           5   7         1


提示：

二叉搜索树节点个数不超过 50
二叉搜索树始终是有效的，并且每个节点的值都不相同
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int splitSubBST(struct TreeNode* root, int V, struct TreeNode** left, struct TreeNode** right){
    *left = NULL;
    *right = NULL;
    if (root == NULL) {
        return 0;
    }
    if (root->val <= V) {
        splitSubBST(root->right, V, left, right);
        root->right = *left;
        *left = root;
    } else {
        splitSubBST(root->left, V, left, right);
        root->left = *right;
        *right = root;
    }
    return 0;
}

struct TreeNode** splitBST(struct TreeNode* root, int V, int* returnSize){
   struct TreeNode** res = (struct TreeNode**)malloc(2 * sizeof(struct TreeNode*));
    *returnSize = 2;
    res[0] = NULL;
    res[1] = NULL;
    if (root == NULL) {
        return res;
    }
    splitSubBST(root, V, &res[0], &res[1]);
    return res;
}