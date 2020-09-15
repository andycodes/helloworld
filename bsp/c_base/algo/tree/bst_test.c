/*
���������������ʣ�
�����������нڵ�ֵС�ڸ��ڵ��ֵ
�����������нڵ�ֵ���ڸ��ڵ��ֵ

ʵ�ڲ�������---��������
*/

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


/*
669. �޼�����������
����һ��������������ͬʱ������С�߽�L?��
���߽�?R��ͨ���޼�������������ʹ������
�ڵ��ֵ��[L, R]�� (R>=L) ���������Ҫ�ı����ĸ��ڵ㣬
���Խ��Ӧ�������޼��õĶ������������µĸ��ڵ㡣
����:
    1
   / \
  0   2

  L = 1
  R = 2

���:
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
783. �����������ڵ���С����
����������������������������顣
��������������� root = [4,2,6,1,3,null,null]��
��������Ľ������ [1, 2, 3, 4, 6]��
��ĿҪ������������С���룬
����Ҫ�������������������
����Ԫ�ز����Сֵ��
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
897. ����˳�������
����һ���������������������������
ʹ��������ߵĽ�����������ĸ���
����ÿ�����û�����ӽ�㣬ֻ��һ�����ӽ�㡣

ʾ�� ��

���룺[5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

�����[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

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
108. ����������ת��Ϊ����������
��һ�������������е��������飬
ת��Ϊһ�ø߶�ƽ�������������
�����У�һ���߶�ƽ���������ָ
һ��������ÿ���ڵ� ����������������
�߶Ȳ�ľ���ֵ������ 1��
ʾ��:
������������: [-10,-3,0,5,9],
һ�����ܵĴ��ǣ�[0,-3,9,-10,null,5]��
�����Ա�ʾ��������߶�ƽ�������������

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
	root->left = ToBST(nums,left,mid-1);//ע��mid-1 ����벿�ֽ��еݹ�
	root->right = ToBST(nums,mid+1,right);//ע��mid+1 ���Ұ벿�ֽ��еݹ�
	return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize)
{
    return ToBST(nums,0,numsSize-1);
}

/*
����һ��������������
��дһ������ kthSmallest ���������е� k ����С��Ԫ�ء�

˵����
����Լ��� k ������Ч�ģ�1 �� k �� ����������Ԫ�ظ�����

*/
/*�������(������)+��ǰ��ֹ*/
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
285. �����������е�˳����
����һ�����������������е�ĳһ����㣬�����ҳ��ý����
����˳���̵Ľڵ㡣
��� p �ĺ����ֵ�� p.val ��Ľ���м�ֵ��С�Ľ�㡣

*/

/*
ѭ��ʵ��
�����ǰֵ��<=x�ģ���ô����BST������ֻ��Ҫ����������
�ң�cur=cur.right��
�����ǰֵ>x����ǰֵ�п��ܣ�����������Ҳ�п�����
��С�ĵ���Ҳ>x�ġ���ÿ�����������֧ʱ����ǰ����һ��
��ѡ�㣬��¼�ýڵ��ֵ����ʷ��С�ڵ��ֵ��
ʱ��O(logN)���ռ�O(1��

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
98. ��֤����������
����һ�����������ж����Ƿ���һ����Ч�Ķ�����������
����һ��������������������������
�ڵ��������ֻ����С�ڵ�ǰ�ڵ������
�ڵ��������ֻ�������ڵ�ǰ�ڵ������
�������������������������Ҳ�Ƕ�����������
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
 * ǰ�����"������"
 ǰ����� - ��->��->��
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
 * �������"������"
 ������� - ��->��->��
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
 * �������"������"
 ������� - ��->��->��
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
 * (�ݹ�ʵ��)����"������x"�м�ֵΪkey�Ľڵ�
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
 * ������С��㣺����treeΪ�����Ķ���������С��㡣
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
 * ��������㣺����treeΪ�����Ķ�����������㡣
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
 * ɾ�����(z)�������ظ��ڵ�
 *
 * ����˵����
 *     root �������ĸ����
 *     z ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�
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
 * ɾ�����(keyΪ�ڵ�ļ�ֵ)�������ظ��ڵ�
 *
 * ����˵����
 *     root �������ĸ����
 *     z ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�
 */
struct TreeNode* delete_bstree(struct TreeNode* root, Type val)
{
	struct TreeNode *z, *node;

	if ((z = bstree_search(root, val)) != NULL)
		root = bstree_delete(root, z);

	return root;
}


 /*
270. ��ӽ��Ķ���������ֵ
�Ѷȼ�31
����һ����Ϊ�յĶ�����������һ��Ŀ��ֵ target�����ڸö������������ҵ���ӽ�Ŀ��ֵ target ����ֵ��
ע�⣺
"	������Ŀ��ֵ target ��һ��������
"	��Ŀ��֤�ڸö�����������ֻ�����һ����ӽ�Ŀ��ֵ����
ʾ����
����: root = [4,2,5,1,3]��Ŀ��ֵ target = 3.714286

    4
   / \
  2   5
 / \
1   3

���: 4

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
109. ��������ת������������
�Ѷ��е�277
����һ�����������е�Ԫ�ذ��������򣬽���ת��Ϊ�߶�ƽ��Ķ�����������
�����У�һ���߶�ƽ���������ָһ��������ÿ���ڵ� ���������������ĸ߶Ȳ�ľ���ֵ������ 1��
ʾ��:
�������������� [-10, -3, 0, 5, 9],

һ�����ܵĴ��ǣ�[0, -3, 9, -10, null, 5], �����Ա�ʾ��������߶�ƽ�������������

      0
     / \
   -3   9
   /   /
 -10  5

*/
struct ListNode* preMid(struct ListNode *head){       //�������м����ǰһ�����
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
    if(head==NULL) return NULL;                             //�ݹ����ֹ����:������ֻ��0��1��Ԫ��
    if(head->next==NULL) return newTreeNode(head->val);
    struct ListNode* premid=preMid(head);
    struct ListNode* mid=premid->next;
    premid->next=NULL;              //�Ͽ����� ��Ϊǰ��������
    struct TreeNode* root=newTreeNode(mid->val);
    root->left=sortedListToBST(head);
    root->right=sortedListToBST(mid->next);
    return root;
}

/*
������ 17.12. BiNode
���������ݽṹTreeNode��������ʾ������������left�ÿգ�rightΪ��һ������ڵ㣩��ʵ��һ���������Ѷ���������ת��Ϊ��������Ҫ����Ȼ���϶��������������ʣ�ת������Ӧ��ԭַ�ģ�Ҳ������ԭʼ�Ķ�����������ֱ���޸ġ�

����ת����ĵ��������ͷ�ڵ㡣

ע�⣺�������ԭ�������Ķ�



ʾ����

���룺 [4,2,5,1,3,null,6,0]
����� [0,null,1,null,2,null,3,null,4,null,5,null,6]
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
        node->left=NULL;    //���ýڵ��������ΪNULL
        cur->right=node;    //���ýڵ㸳����һ���ڵ���Һ���
        cur=node;           //����cur
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
1038. �Ӷ������������������
�������� ���� ���ĸ��ڵ㣬�ö������Ľڵ�ֵ������ͬ���޸Ķ�������ʹÿ���ڵ� node ����ֵ����ԭ���д��ڻ���� node.val ��ֵ֮�͡�

����һ�£�������������������Լ��������

�ڵ���������������� С�� �ڵ���Ľڵ㡣
�ڵ���������������� ���� �ڵ���Ľڵ㡣
��������Ҳ�����Ƕ�����������
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
1382. ��������������ƽ��
����һ�ö��������������㷵��һ�� ƽ��� �Ķ����������������ɵ���Ӧ����ԭ������������ͬ�Ľڵ�ֵ��

���һ�ö����������У�ÿ���ڵ�����������߶Ȳ���� 1 �����Ǿͳ���ö����������� ƽ��� ��

����ж��ֹ��췽�������㷵������һ�֡�


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
    if(root)//������������������õ�һ����������
    {
        func(root->left,re,returnSize);
        re[(*returnSize)++]=root->val;
        func(root->right,re,returnSize);
    }
}
struct TreeNode* createTree(int *nums,int numsSize){
    //����һ���������鴴��ƽ�����������
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
1373. ������������������ֵ��
����һ���� root Ϊ���� ������ �����㷵�� ���� ������������������ֵ�͡�

�����������Ķ������£�

����ڵ���������еļ�ֵ�� С�� �˽ڵ�ļ�ֵ��
����ڵ���������еļ�ֵ�� ���� �˽ڵ�ļ�ֵ��
����ڵ�������������������Ƕ�����������

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
776. ��ֶ���������
����һ�ö�����������BST�������ĸ���� root �Լ�Ŀ��ֵ V��

�뽫������Ҫ����Ϊ��������������һ����������ֵ������С�ڵ��ڸ�����Ŀ��ֵ V����һ����������ֵ���������Ŀ��ֵ V�����в���һ��Ҫ����ֵΪ V �Ľ�㡣

����֮�⣬���д󲿷ֽṹ����Ҫ������Ҳ����˵ԭʼ���и��ڵ� P �������ӽڵ� C�������ֺ���������ͬһ�������У���ô��� P Ӧ��Ϊ C ���ӽ�㡣

����Ҫ���ز�ֺ����������ĸ���� TreeNode��˳�����⡣



ʾ����

���룺root = [4,2,6,1,3,5,7], V = 2
�����[[2,1],[4,3,6,null,null,5,7]]
���ͣ�
ע������ output[0] �� output[1] ���� TreeNode ���󣬲������顣

�������� [4,2,6,1,3,5,7] �ɻ�Ϊ����ʾ��ͼ��

          4
        /   \
      2      6
     / \    / \
    1   3  5   7

�����ʾ��ͼ���£�

          4
        /   \
      3      6       ��    2
            / \           /
           5   7         1


��ʾ��

�����������ڵ���������� 50
����������ʼ������Ч�ģ�����ÿ���ڵ��ֵ������ͬ
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