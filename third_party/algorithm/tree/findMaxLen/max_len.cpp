/*
题目：在一棵二叉树中，找出相距最远的两个节点之间的距离，
函数返回距离值（提示：递归）
解答如果能想到这两个节点必定在某个节点的左右子树中，
那么只要找到该节点左子树中最深的节点以及右子树中最
深的节点，二者之和即为左右最深节点的距离，
如果对每个节点做同样的运算，取最大值，那么可以得到
最远距离。重复地计算每一个节点必然提高时间复杂度，
所以递归是一个不错的方式。
*/

#include<iostream>
using namespace std;

struct TreeNode{
	int m_data;
	TreeNode* m_pLeft;
	TreeNode* m_pRight;
	TreeNode(const int data = 0,TreeNode* left=NULL,TreeNode* right=NULL):
		m_data(data),m_pLeft(left),m_pRight(right){}
};

int LongestPathRecursive(TreeNode* pNode,int& left_len,int& right_len,int& max_len)
{
	if(NULL == pNode)
	{
		left_len = 0;
		right_len = 0;
		max_len = 0;
		return max_len;
	}
	int left_left_len = 0;
	int left_right_len = 0;
	int left_max_len = 0;
	int right_left_len = 0;
	int right_right_len = 0;
	int right_max_len = 0;
	LongestPathRecursive(pNode->m_pLeft,left_left_len,left_right_len,left_max_len);
	LongestPathRecursive(pNode->m_pRight,right_left_len,right_right_len,right_max_len);

	left_len = max(left_left_len,left_right_len) + 1;
	right_len = max(right_left_len,right_right_len) + 1;
	max_len = max(left_left_len+right_left_len,max(left_max_len,right_max_len));
	return max_len;
}

int LongestPath(TreeNode* pRoot)
{
	if(!pRoot)
		return -1;
	int left_len = 0;
	int right_len = 0;
	int max_len = 0;
	return LongestPathRecursive(pRoot,left_len,right_len,max_len);
}