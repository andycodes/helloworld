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
请将该树按要求拆分为两个子树：其中一个子树结点的值都
必须小于等于给定的目标值 V；另一个子树结点的值都必须
大于目标值 V；树中并非一定要存在值为 V 的结点。
除此之外，树中大部分结构都需要保留，也就是说原始树中
父节点 P 的任意子节点 C，假如拆分后它们仍在同一个子树中，
那么结点 P 应仍为 C 的子结点。
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

/*
501. 二叉搜索树中的众数
给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素）。

假定 BST 有如下定义：

结点左子树中所含结点的值小于等于当前结点的值
结点右子树中所含结点的值大于等于当前结点的值
左子树和右子树都是二叉搜索树
例如：
给定 BST [1,null,2,2],

   1
    \
     2
    /
   2
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int* answer;
int answerSize;
int base, count, maxCount;

void update(int x) {
    if (x == base) {
        ++count;
    } else {
        count = 1;
        base = x;
    }
    if (count == maxCount) {
        answer[answerSize++] = base;
    }
    if (count > maxCount) {
        maxCount = count;
        answerSize = 0;
        answer[answerSize++] = base;
    }
}

void dfs(struct TreeNode* o) {
    if (!o) {
        return;
    }
    dfs(o->left);
    update(o->val);
    dfs(o->right);
}

int* findMode(struct TreeNode* root, int* returnSize) {
    base = count = maxCount = 0;
    answer = malloc(sizeof(int) * 4001);
    answerSize = 0;
    dfs(root);
    *returnSize = answerSize;
    return answer;
}

/*
538. 把二叉搜索树转换为累加树
给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。
*/
/**
 * Definition for a binary tree node.
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

struct TreeNode* convertBST(struct TreeNode* root)
{
	sum = 0;
	return backingInOrder(root);
}
