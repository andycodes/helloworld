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
int tMaxLength=0;    //������
stack<NODE*> s;
//
//��������(����һ)
//
void findMaxLength1(NODE* root)
{
    //�ݹ����
    if(root==NULL)    return;

    //
    //����Ϊ��
    //
    if(root->pLeft==NULL)
        root->nMaxLeft=0;
    //
    //����Ϊ��
    //
    if(root->pRight==NULL)
        root->pRight=0;
    //
    //������Ϊ��
    //
    if(root->pLeft!=NULL)
    {
        findMaxLength1(root->pLeft);
    }
    //
    //������Ϊ��
    //
    if(root->pRight!=NULL)
    {
        findMaxLength1(root->pRight);
    }
    //
    //��������������
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
    //��������������
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
    //����������
    //
    if((root->nMaxLeft+root->nMaxRight)>tMaxLength)
        tMaxLength=root->nMaxLeft+root->nMaxRight;
}
//
//��������(������)
//
void findMaxLength2(NODE* root)
{
    NODE *p=root;
//��¼�ϴη��ʵĽ�㣬��Ҫ�����ڣ��ж��������
//���ܷ��ʡ�����������Һ����Ǹշ��ʵģ���ô���ܷ��ʸ�����ˡ�
    NODE *have_visited=NULL;
    while(p!=NULL||!s.empty())
    {
        //
        //�������֧ѹ��ջ���������������
        //
        while(p!=NULL)
        {
            s.push(p);
            p=p->pLeft;
        }
        p=s.top();
        //
        //����������ǿգ���ô������������������
        //�������ϴη��ʵ����ҽ�㣬��ô���Է��ʸ����
        //
        if(p->pRight==NULL||have_visited==p->pRight)
        {
            //
            //��������������Ĵ��룬�����ں������
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
            //*************************************����
            s.pop();
            have_visited=p;
            p=NULL;
        }
        else
        {
            p=p->pRight; //ָ����������Ϊ�´�ѭ����ѹջ��׼����
        }
    }
}
//
//�������
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
//�������
//
void postOrderTraverse(NODE* root)
{
    NODE *p=root;
    NODE *have_visited=NULL; //��¼�ϴη��ʵĽ�㣬��Ҫ�����ڣ��ж��������                 //���ܷ�������������Һ����Ǹշ��ʵģ���ô���ܷ��ʸ�����ˡ�
    while(p!=NULL||!s.empty())
    {
        //
        //�������֧ѹ��ջ���������������
        //
        while(p!=NULL)
        {
            s.push(p);
            p=p->pLeft;
        }
        p=s.top();
        //
        //����������ǿգ���ô������������������
        //�������ϴη��ʵ����ҽ�㣬��ô���Է��ʸ����
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
            p=p->pRight; //ָ����������Ϊ�´�ѭ����ѹջ��׼����
        }
    }
}

//
//��ʼ����
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