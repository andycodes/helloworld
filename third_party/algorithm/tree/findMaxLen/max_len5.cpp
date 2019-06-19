#include<iostream>
using namespace std;
typedef struct BiTNode
{
    BiTNode *left;
    BiTNode *right;
}BiTNode, *BiTree;

int maxDis = 0;

void createTree(BiTree &root)
{
    BiTree left1 = new(BiTNode);
    BiTree right1 = new(BiTNode);

    left1->left = NULL;
    left1->right = NULL;
    right1->left = NULL;
    right1->right = NULL;

    root->left = left1;
    root->right = right1;


    BiTree left2 = new(BiTNode);
    left2->left = NULL;
    left2->right = NULL;
    BiTree right2 = new(BiTNode);
    right2->left = NULL;
    right2->right = NULL;
    left1->left = left2;
    left1->right = right2;

    BiTree left3 = new(BiTNode);
    left3->left = NULL;
    left3->right = NULL;
    BiTree right3 = new(BiTNode);
    right3->left = NULL;
    right3->right = NULL;
    left2->left = left3;
    left2->right = right3;
}

void deleteTree(BiTree root)
{
    if(root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete(root);
        root = NULL;
    }
}

int height(BiTree root)
{
    if(root == NULL)
        return 0;
    else
        return height(root->left) > height(root->right) ? height(root->left) + 1 : height(root->right) + 1;
}

int max(int a, int b, int c)
{
    int tmp = a > b ? a : b;
    return tmp > c ? tmp : c;
}

int treeDistance(BiTree root)
{
    if(root == NULL)
        return 0;
    else if(root->left == NULL && root->right == NULL)
        return 0;
    int dis = max(height(root->left) + height(root->right), treeDistance(root->left), treeDistance(root->right));
    if(maxDis < dis)
        maxDis = dis;
    return dis;
}

int main()
{
    BiTree root = new(BiTNode);
    root->right = root->left = NULL;
    createTree(root);
    cout << "height:" << height(root) << endl;
    cout << "treeDistance:" << treeDistance(root) << endl;
    cout << "_____________________" << endl;
    deleteTree(root);
}