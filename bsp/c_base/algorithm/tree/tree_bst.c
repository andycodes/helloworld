#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*  Definition for a binary tree node.*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


/*
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

struct TreeNode* trimBST(struct TreeNode* root, int L, int R){
        if (root ==  NULL) return root;
        if (root->val > R) return trimBST(root->left, L, R);
        if (root->val < L) return trimBST(root->right, L, R);

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
}


/*
 ���������������С����

����������������������������顣
��������������� root = [4,2,6,1,3,null,null]��
��������Ľ������ [1, 2, 3, 4, 6]��
��ĿҪ������������С���룬
����Ҫ�������������������
����Ԫ�ز����Сֵ��

*/


int ret = 2147483647;
bool first = true;
int last;//��һ������ֵ
void help(struct TreeNode* root)
{
    if(root)
    {
        //������
        help(root->left);

        //��ǰ��㴦��
        if(!first)
            ret = min(ret, abs(root->val - last));
        else
        {
            first = false;
        }
        last = root->val;

        //������
        help(root->right);
    }
}



int minDiffInBST(struct TreeNode* root){
     ret = 2147483647;
    first = true;
    help(root);
    return ret;
}

/*
����һ���������������������������ʹ��������ߵĽ�����������ĸ�������ÿ�����û�����ӽ�㣬ֻ��һ�����ӽ�㡣

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
struct TreeNode* increasingBST(struct TreeNode* root){
	if (root == NULL)
		return NULL;

	struct TreeNode* ans = root;

	if (root->right != NULL)
		root->right = increasingBST(root->right);

	if (root->left != NULL){
		ans = increasingBST(root->left);
		struct TreeNode* ans1 = ans;
		while(ans1->right != NULL)
			ans1 = ans1->right;
		ans1->right = root;
		root->left = NULL;
	}

	return ans;
}


/*
��һ�������������е��������飬ת��Ϊһ�ø߶�ƽ�������������

�����У�һ���߶�ƽ���������ָһ��������ÿ���ڵ� ���������������ĸ߶Ȳ�ľ���ֵ������ 1��

ʾ��:

������������: [-10,-3,0,5,9],

һ�����ܵĴ��ǣ�[0,-3,9,-10,null,5]�������Ա�ʾ��������߶�ƽ�������������

      0
     / \
   -3   9
   /   /
 -10  5
*/
struct TreeNode* ToBST(int nums[],int left,int right){
	if(left>right)return NULL;//����Ķ�������Ϊ[left,right]���޷����м����ݹ飬ֱ���˳�
	int mid = (int)(left+right)/2;//������ֵ
	struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
	root->left = ToBST(nums,left,mid-1);//ע��mid-1 ����벿�ֽ��еݹ�
	root->right = ToBST(nums,mid+1,right);//ע��mid+1 ���Ұ벿�ֽ��еݹ�
	return root;
}


struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    return ToBST(nums,0,numsSize-1);
}

/*
����һ����������������дһ������ kthSmallest ���������е� k ����С��Ԫ�ء�

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


