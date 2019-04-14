#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

struct NODE
{
    NODE* pLeft;
    NODE* pRight;
    int nMaxLeft;
    int nMaxRight;
    char nValue;
};
int tMaxLength=0;    //最大距离
stack<NODE*> s;
//
//求最大距离(方法一)
//
void findMaxLength1(NODE* root)
{
    //递归结束
    if(root==NULL)    return;

    //
    //左树为空
    //
    if(root->pLeft==NULL)
        root->nMaxLeft=0;
    //
    //右树为空
    //
    if(root->pRight==NULL)
        root->pRight=0;
    //
    //左树不为空
    //
    if(root->pLeft!=NULL)
    {
        findMaxLength1(root->pLeft);
    }
    //
    //右树不为空
    //
    if(root->pRight!=NULL)
    {
        findMaxLength1(root->pRight);
    }
    //
    //求左子树最大距离
    //
    if(root->pLeft!=NULL)
    {
        int nTempMax=0;
        if(root->pLeft->nMaxLeft>root->pLeft->nMaxRight)
            nTempMax=root->pLeft->nMaxLeft;
        else
            nTempMax=root->pLeft->nMaxRight;
        root->nMaxLeft=nTempMax+1;
    }
    //
    //求右子树最大距离
    //
    if(root->pRight!=NULL)
    {
        int nTempMax=0;
        if(root->pRight->nMaxLeft>root->pRight->nMaxRight)
            nTempMax=root->pRight->nMaxLeft;
        else
            nTempMax=root->pRight->nMaxRight;
        root->nMaxRight=nTempMax+1;
    }
    //
    //更新最大距离
    //
    if((root->nMaxLeft+root->nMaxRight)>tMaxLength)
        tMaxLength=root->nMaxLeft+root->nMaxRight;
}
//
//求最大距离(方法二)
//
void findMaxLength2(NODE* root)
{
    NODE *p=root;
//记录上次访问的结点，主要是用在：判定根结点是
//否能访问。如果根结点的右孩子是刚访问的，那么就能访问根结点了。
    NODE *have_visited=NULL;
    while(p!=NULL||!s.empty())
    {
        //
        //把最左分支压入栈，类似于中序遍历
        //
        while(p!=NULL)
        {
            s.push(p);
            p=p->pLeft;
        }
        p=s.top();
        //
        //如果右子树是空，那么后序遍历就是中序遍历
        //如果如果上次访问的是右结点，那么可以访问根结点
        //
        if(p->pRight==NULL||have_visited==p->pRight)
        {
            //
            //以下是求最大距离的代码，不属于后序遍历
            //
            if(p->pLeft!=NULL)
            {
                p->nMaxLeft=p->pLeft->nMaxLeft+1;
                if(p->pLeft->nMaxRight+1>p->nMaxLeft)
                    p->nMaxLeft=p->pLeft->nMaxRight+1;
            }
            if(p->pRight!=NULL)
            {
                p->nMaxRight=p->pRight->nMaxRight+1;
                if(p->pRight->nMaxLeft+1>p->nMaxRight)
                    p->nMaxRight=p->pRight->nMaxLeft+1;
            }
            if((root->nMaxLeft+root->nMaxRight)>tMaxLength)
                tMaxLength=root->nMaxLeft+root->nMaxRight;
            //*************************************结束
            s.pop();
            have_visited=p;
            p=NULL;
        }
        else
        {
            p=p->pRight; //指向右子树，为下次循环，压栈做准备。
        }
    }
}
//
//中序遍历
//
void inOrderTraverse(NODE* root)
{

    s.push(root);
    while(!s.empty())
    {
        while(s.top()!=NULL)
        {
            NODE* t=s.top()->pLeft;
            s.push(t);
        }
        s.pop();
        if(!s.empty())
        {
            NODE* top=s.top();
            s.pop();
            printf("%d ",top->nValue);
            s.push(top->pRight);
        }
    }


}
//
//后序遍历
//
void postOrderTraverse(NODE* root)
{
    NODE *p=root;
    NODE *have_visited=NULL; //记录上次访问的结点，主要是用在：判定根结点是                 //否能访问如果根结点的右孩子是刚访问的，那么就能访问根结点了。
    while(p!=NULL||!s.empty())
    {
        //
        //把最左分支压入栈，类似于中序遍历
        //
        while(p!=NULL)
        {
            s.push(p);
            p=p->pLeft;
        }
        p=s.top();
        //
        //如果右子树是空，那么后序遍历就是中序遍历
        //如果如果上次访问的是右结点，那么可以访问根结点
        //
        if(p->pRight==NULL||have_visited==p->pRight)
        {
            printf("%d ",p->nValue);
            s.pop();
            have_visited=p;
            p=NULL;
        }
        else
        {
            p=p->pRight; //指向右子树，为下次循环，压栈做准备。
        }
    }
}

//
//初始化树
//
NODE* initTree()
{
    NODE* tree[10];

    for(int i=0;i<10;i++)
    {
        tree[i]=(NODE*)malloc(sizeof(NODE));
        tree[i]->nMaxLeft=0;
        tree[i]->nMaxRight=0;
        tree[i]->pLeft=NULL;
        tree[i]->pRight=NULL;
        tree[i]->nValue=(char)i;
    }
    for(int i=0;i<=2;i++)
    {
        tree[i]->pLeft=tree[2*i+1];
        tree[i]->pRight=tree[2*i+2];
    }
    tree[3]->pLeft=tree[7];
    tree[5]->pRight=tree[8];
    return tree[0];
}
int main()
{
    printf("After the sequence traversal \n");
    postOrderTraverse(initTree());
    printf("\n");
    printf("In the sequence traversal\n");
    inOrderTraverse(initTree());
    printf("\n");
    findMaxLength2(initTree());
    printf("not recursive method:%d\n",tMaxLength);
    findMaxLength1(initTree());
    printf(" recursive method:%d\n",tMaxLength);
    return 0;
}