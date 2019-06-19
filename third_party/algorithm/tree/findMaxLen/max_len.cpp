/*
��Ŀ����һ�ö������У��ҳ������Զ�������ڵ�֮��ľ��룬
�������ؾ���ֵ����ʾ���ݹ飩
���������뵽�������ڵ�ض���ĳ���ڵ�����������У�
��ôֻҪ�ҵ��ýڵ�������������Ľڵ��Լ�����������
��Ľڵ㣬����֮�ͼ�Ϊ��������ڵ�ľ��룬
�����ÿ���ڵ���ͬ�������㣬ȡ���ֵ����ô���Եõ�
��Զ���롣�ظ��ؼ���ÿһ���ڵ��Ȼ���ʱ�临�Ӷȣ�
���Եݹ���һ������ķ�ʽ��
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