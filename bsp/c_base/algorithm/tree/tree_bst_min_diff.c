/*
 ���������������С����

����������������������������顣
��������������� root = [4,2,6,1,3,null,null]��
��������Ľ������ [1, 2, 3, 4, 6]��
��ĿҪ������������С���룬
����Ҫ�������������������
����Ԫ�ز����Сֵ��

*/
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };


#define min(a, b) ((a) < (b) ? (a) : (b))
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

int main()
{}

