#include <stdio.h>
#include "string.h"
#include "Expr.h"

ABS_CTOR(Expr_node)
	cthis->use = 1;             // ���캯���У������ü�����ʼ��Ϊ1
END_ABS_CTOR
	
// Expr_node������������DTOR/END_DTOR����ʵ�������������壩
DTOR(Expr_node)
	if (--cthis->use == 0)      // �ݼ����ü������������Ϊ0���ͷ��Լ�
	{
		cthis->finalize(cthis); // �ͷ��ڴ�֮ǰ��������Դ(������Ҫ�ͷŵĶ���
		return lw_oopc_true;
	}

	return lw_oopc_false;
END_DTOR

// �����������ʽ������һ������ֵ�����ӱ��ʽ����nΪ����ֵ
void Expr_initInt(Expr* expr, int n)
{
	Int_node* intNode = Int_node_new(lw_oopc_file_line);
	intNode->init(intNode, n);
	
	expr->p = SUPER_PTR(intNode, Expr_node);
}
	
// ����һԪ���ʽ������һ����������һ���ӱ��ʽ����opΪ��������opndΪ�ӱ��ʽ
void Expr_initUnary(Expr* expr, const char* op, Expr* opnd)
{
	Unary_node* unaryNode = Unary_node_new(lw_oopc_file_line);
	unaryNode->init(unaryNode, op, opnd);
	expr->p = SUPER_PTR(unaryNode, Expr_node);
}

// ����һԪ���ʽ��������ʽ(ͨ������һ������ֵ����������һ���ӱ��ʽΪ�������ʽ��һԪ���ʽ��
// opΪ��������aΪ�ӱ��ʽ������ֵ
void Expr_initUnaryX(Expr* expr, const char* op, int a)
{
	Expr* intExpr = Expr_new(lw_oopc_file_line);
	Unary_node* unaryNode = Unary_node_new(lw_oopc_file_line);

	intExpr->initInt(intExpr, a);
	unaryNode->init(unaryNode, op, intExpr);
	expr->p = SUPER_PTR(unaryNode, Expr_node);

	Expr_delete(intExpr);
}

// ������Ԫ���ʽ������һ���������������ӱ��ʽ��
// opΪ��������leftΪ���ӱ��ʽ��rightΪ���ӱ��ʽ
void Expr_initBinary(Expr* expr, const char* op, Expr* left, Expr* right)
{
	Binary_node* binaryNode = Binary_node_new(lw_oopc_file_line);
	binaryNode->init(binaryNode, op, left, right);
	expr->p = SUPER_PTR(binaryNode, Expr_node);
}

// ������Ԫ���ʽ��������ʽ(ͨ��������������ֵ���������������ӱ��ʽ��Ϊ�������ʽ�Ķ�Ԫ���ʽ��
// opΪ��������aΪ���ӱ��ʽ������ֵ��bΪ���ӱ��ʽ������ֵ
void Expr_initBinaryX(Expr* expr, const char* op, int a, int b)
{
	Expr* left = Expr_new(lw_oopc_file_line);
	Expr* right = Expr_new(lw_oopc_file_line);
	Binary_node* binaryNode = Binary_node_new(lw_oopc_file_line);

	left->initInt(left, a);
	right->initInt(right, b);

	binaryNode->init(binaryNode, op, left, right);
	expr->p = SUPER_PTR(binaryNode, Expr_node);

	Expr_delete(left);
	Expr_delete(right);
}

// ��ӡ���ʽ��������
void Expr_print(Expr* t)
{
	Expr_node* p = t->p;
	p->print(p);
}

CTOR(Expr)
FUNCTION_SETTING(initInt, Expr_initInt);
FUNCTION_SETTING(initUnary, Expr_initUnary);
FUNCTION_SETTING(initUnaryX, Expr_initUnaryX);
FUNCTION_SETTING(initBinary, Expr_initBinary);
FUNCTION_SETTING(initBinaryX, Expr_initBinaryX);
FUNCTION_SETTING(print, Expr_print);
	cthis->use = 1;             // ���캯���У������ü�����ʼ��Ϊ1
END_CTOR

// Expr������������DTOR/END_DTOR����ʵ�������������壩
DTOR(Expr)
	if (--cthis->use == 0)      // �ݼ����ü������������Ϊ0���ͷ��Լ�
	{
		Expr_node_delete(cthis->p);
		return lw_oopc_true;
	}

	return lw_oopc_false;
END_DTOR

// �������ʽ�ڵ�ĳ�ʼ��
void Int_node_init(Int_node* t, int k)
{
	t->n = k;
}

// �������ʽ�ڵ�Ĵ�ӡ
void Int_node_print(Expr_node* t) 
{
	Int_node* cthis = SUB_PTR(t, Expr_node, Int_node);
	printf("%d", cthis->n); 
}

// �������ʽ�ڵ����Դ����
void Int_node_finalize(Expr_node* t)
{
	// ʲô������Ҫ��
}

CTOR(Int_node)
SUPER_CTOR(Expr_node);
FUNCTION_SETTING(init, Int_node_init);
FUNCTION_SETTING(Expr_node.print, Int_node_print);
FUNCTION_SETTING(Expr_node.finalize, Int_node_finalize);
END_CTOR

// ���ýڵ�Ĳ�����
void setOp(char* opAddr, const char* opValue)
{
	memset(opAddr, 0, 3);
	strncpy(opAddr, opValue, 2);
}

// һԪ���ʽ�ڵ�ĳ�ʼ��
void Unary_node_init(Unary_node* t, const char* opValue, Expr* b)
{
	setOp(t->op, opValue);
	t->opnd = b;
	++b->use;   // ָ�븳ֵʱ����ָ����ָ��������ü�������
}

// һԪ���ʽ�ڵ�Ĵ�ӡ
void Unary_node_print(Expr_node* t)
{
	Unary_node* cthis = SUB_PTR(t, Expr_node, Unary_node);
	Expr* opnd = cthis->opnd;

	printf("(");
	printf("%s", cthis->op);
	opnd->print(opnd);
	printf(")"); 
}

// һԪ���ʽ�ڵ����Դ����
void Unary_node_finalize(Expr_node* t)
{
	Unary_node* cthis = SUB_PTR(t, Expr_node, Unary_node);

	Expr_delete(cthis->opnd);
}

CTOR(Unary_node)
SUPER_CTOR(Expr_node);
FUNCTION_SETTING(init, Unary_node_init);
FUNCTION_SETTING(Expr_node.print, Unary_node_print);
FUNCTION_SETTING(Expr_node.finalize, Unary_node_finalize);
END_CTOR

// ��Ԫ���ʽ�ڵ�ĳ�ʼ��
void Binary_node_init(Binary_node* t, const char* opValue, Expr* left, Expr* right)
{
    setOp(t->op, opValue);
	t->left = left;
	t->right = right;
	++left->use;    // ָ�븳ֵʱ����ָ����ָ��������ü�������
	++right->use;   // ָ�븳ֵʱ����ָ����ָ��������ü�������
}

// ��Ԫ���ʽ�ڵ�Ĵ�ӡ
void Binary_node_print(Expr_node* t)
{
	Binary_node* cthis = SUB_PTR(t, Expr_node, Binary_node);

	Expr* left = cthis->left;
	Expr* right = cthis->right;

	printf("(");
	left->print(left);
	printf("%s", cthis->op);
	right->print(right);
	printf(")"); 
}

// ��Ԫ���ʽ�ڵ����Դ����
void Binary_node_finalize(Expr_node* t)
{
	Binary_node* cthis = SUB_PTR(t, Expr_node, Binary_node);

	Expr_delete(cthis->left);
	Expr_delete(cthis->right);
}

CTOR(Binary_node)
SUPER_CTOR(Expr_node);
FUNCTION_SETTING(init, Binary_node_init);
FUNCTION_SETTING(Expr_node.print, Binary_node_print);
FUNCTION_SETTING(Expr_node.finalize, Binary_node_finalize);
END_CTOR