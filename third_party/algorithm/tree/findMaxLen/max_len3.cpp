/*
我认为这个问题的核心是，情况A 及 B 需要不同的信息:
A 需要子树的最大深度，
B 需要子树的最大距离。只要函数能在一个节点同时计算及传回这两个信息，
代码就可以很简单:

计算 result 的代码很清楚；
nMaxDepth 就是左子树和右子树的深度加1；
nMaxDistance 则取 A 和 B 情况的最大值。

为了减少 NULL 的条件测试，
进入函数时，如果节点为 NULL，会传回一个 empty 变量。
比较奇怪的是 empty.nMaxDepth = -1，目的是让调用方 +1 后，
把当前的不存在的 (NULL) 子树当成最大深度为 0。

除了提高了可读性，这个解法的另一个优点是减少了
O(节点数目) 大小的侵入式资料，而改为使用 O(树的最大深度) 大小的栈空间。
这个设计使函数完全没有副作用(side effect)。
*/

#include <iostream>

using namespace std;

struct NODE
{
    NODE *pLeft;
    NODE *pRight;
};

struct RESULT
{
    int nMaxDistance;
    int nMaxDepth;
};

RESULT GetMaximumDistance(NODE* root)
{
    if (!root)
    {
        RESULT empty = { 0, -1 };   // trick: nMaxDepth is -1 and then caller will plus 1 to balance it as zero.
        return empty;
    }

    RESULT lhs = GetMaximumDistance(root->pLeft);
    RESULT rhs = GetMaximumDistance(root->pRight);

    RESULT result;
    result.nMaxDepth = max(lhs.nMaxDepth + 1, rhs.nMaxDepth + 1);
    result.nMaxDistance = max(max(lhs.nMaxDistance, rhs.nMaxDistance), lhs.nMaxDepth + rhs.nMaxDepth + 2);
    return result;
}

void Link(NODE* nodes, int parent, int left, int right)
{
    if (left != -1)
        nodes[parent].pLeft = &nodes[left];

    if (right != -1)
        nodes[parent].pRight = &nodes[right];
}

int main()
{
    // P. 241 Graph 3-12
    NODE test1[9] = { 0 };
    Link(test1, 0, 1, 2);
    Link(test1, 1, 3, 4);
    Link(test1, 2, 5, 6);
    Link(test1, 3, 7, -1);
    Link(test1, 5, -1, 8);
    cout << "test1: " << GetMaximumDistance(&test1[0]).nMaxDistance << endl;

    // P. 242 Graph 3-13 left
    NODE test2[4] = { 0 };
    Link(test2, 0, 1, 2);
    Link(test2, 1, 3, -1);
    cout << "test2: " << GetMaximumDistance(&test2[0]).nMaxDistance << endl;

    // P. 242 Graph 3-13 right
    NODE test3[9] = { 0 };
    Link(test3, 0, -1, 1);
    Link(test3, 1, 2, 3);
    Link(test3, 2, 4, -1);
    Link(test3, 3, 5, 6);
    Link(test3, 4, 7, -1);
    Link(test3, 5, -1, 8);
    cout << "test3: " << GetMaximumDistance(&test3[0]).nMaxDistance << endl;

    // P. 242 Graph 3-14
    // Same as Graph 3-2, not test

    // P. 243 Graph 3-15
    NODE test4[9] = { 0 };
    Link(test4, 0, 1, 2);
    Link(test4, 1, 3, 4);
    Link(test4, 3, 5, 6);
    Link(test4, 5, 7, -1);
    Link(test4, 6, -1, 8);
    cout << "test4: " << GetMaximumDistance(&test4[0]).nMaxDistance << endl;

	return 0;
}