#ifndef EXPR_H_INCLUDED_
#define EXPR_H_INCLUDED_

#include "lw_oopc.h"

// ���ʽ�ڵ�
ABS_CLASS(Expr_node)
{
	int use;        // ���ü���

    void (*print)(Expr_node* t);        // ��ӡ���ʽ�ڵ�
    //int (*eval)(Expr_node* t, int* value);
	void (*finalize)(Expr_node* t);     // ����ͨ����дfinalize������ʵ�ֶ���Դ������Ϊ�Ķ���
};

// ���ʽ�������ĸ�������У�init*�������ṩ�˹��������ĸ߲�API�������û�ʹ��
CLASS(Expr)
{
	int use;        // ���ü���
	Expr_node* p;   // �����ĸ��ڵ�

    // �����������ʽ������һ������ֵ�����ӱ��ʽ��
	void (*initInt)(Expr* t, int);

    // ����һԪ���ʽ������һ����������һ���ӱ��ʽ��
	void (*initUnary)(Expr* t, const char*, Expr*);
    // ����һԪ���ʽ��������ʽ(ͨ������һ������ֵ����������һ���ӱ��ʽΪ�������ʽ��һԪ���ʽ��
	void (*initUnaryX)(Expr* t, const char*, int);

    // ������Ԫ���ʽ������һ���������������ӱ��ʽ��
	void (*initBinary)(Expr* t, const char*, Expr*, Expr*);
    // ������Ԫ���ʽ��������ʽ(ͨ��������������ֵ���������������ӱ��ʽ��Ϊ�������ʽ�Ķ�Ԫ���ʽ��
	void (*initBinaryX)(Expr* t, const char*, int, int);

    // ������Ԫ���ʽ������һ���������������ӱ��ʽ��
	void (*initTernary)(Expr* t, const char*, Expr*, Expr*, Expr*);
    // ������Ԫ���ʽ��������ʽ(ͨ��������������ֵ���������������ӱ��ʽ��Ϊ�������ʽ����Ԫ���ʽ��
	void (*initTernaryX)(Expr* t, const char*, int, int, int);

	void (*print)(Expr* t);     // ��ӡ����
};

// �������ʽ�ڵ�
CLASS(Int_node)
{
    EXTENDS(Expr_node);     // �̳�Expr_node

	int n;                  // ����ֵ   

    // ��ʼ���������ʽ�ڵ㣨��������ֵ��
	void (*init)(Int_node* t, int k);   
};

// һԪ���ʽ�ڵ�
CLASS(Unary_node)
{
    EXTENDS(Expr_node);     // �̳�Expr_node

	char op[3];		        // ����������������2���ַ�
    Expr* opnd;             // �ӱ��ʽ
	
    // ��ʼ��һԪ���ʽ�ڵ㣨�����������1���ӱ��ʽ��
	void (*init)(Unary_node* t, const char* a, Expr* b);
};

// ��Ԫ���ʽ�ڵ�
CLASS(Binary_node)
{
	EXTENDS(Expr_node);     // �̳�Expr_node

    char op[3];		        // ����������������2���ַ�
    Expr* left;             // ���ӱ��ʽ 
    Expr* right;            // ���ӱ��ʽ

    // ��ʼ����Ԫ���ʽ�ڵ㣨�����������2���ӱ��ʽ��
	void (*init)(Binary_node* t, const char* a, Expr* b, Expr* c);
};

// ��Ԫ���ʽ�ڵ�
CLASS(Ternary_node)
{
	EXTENDS(Expr_node);

	char op[3];		        // ����������������2���ַ�
	Expr* left;
	Expr* middle;
	Expr* right;

    // ��ʼ����Ԫ���ʽ�ڵ㣨�����������3���ӱ��ʽ��
	void (*init)(Ternary_node* t, const char* op, Expr* left, Expr* middle, Expr* right);
};

#endif