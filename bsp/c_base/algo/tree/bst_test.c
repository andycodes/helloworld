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
�뽫������Ҫ����Ϊ��������������һ����������ֵ��
����С�ڵ��ڸ�����Ŀ��ֵ V����һ����������ֵ������
����Ŀ��ֵ V�����в���һ��Ҫ����ֵΪ V �Ľ�㡣
����֮�⣬���д󲿷ֽṹ����Ҫ������Ҳ����˵ԭʼ����
���ڵ� P �������ӽڵ� C�������ֺ���������ͬһ�������У�
��ô��� P Ӧ��Ϊ C ���ӽ�㡣
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
501. �����������е�����
����һ������ֵͬ�Ķ�����������BST�����ҳ� BST �е���������������Ƶ����ߵ�Ԫ�أ���

�ٶ� BST �����¶��壺

�������������������ֵС�ڵ��ڵ�ǰ����ֵ
�������������������ֵ���ڵ��ڵ�ǰ����ֵ
�����������������Ƕ���������
���磺
���� BST [1,null,2,2],

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
538. �Ѷ���������ת��Ϊ�ۼ���
�������� ���� ���ĸ��ڵ㣬�����Ľڵ�ֵ������ͬ�����㽫��ת��Ϊ�ۼ�����Greater Sum Tree����ʹÿ���ڵ� node ����ֵ����ԭ���д��ڻ���� node.val ��ֵ֮�͡�

����һ�£�������������������Լ��������

�ڵ���������������� С�� �ڵ���Ľڵ㡣
�ڵ���������������� ���� �ڵ���Ľڵ㡣
��������Ҳ�����Ƕ�����������
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
