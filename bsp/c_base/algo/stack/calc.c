#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/**
 * �Ƚ����������ȼ�
 * @param op ������
 * @return ������ֵ
 */
int priority(char op)
{
	int pp;
	switch (op) {
		case '+':
		case '-':
			pp = 1;
		break;
		case '*':
		case '/':
			pp = 2;
		break;
		default:
			pp = 0;
		break;
	}
	return pp;
}

/**
 * ����ʽת����ʽ
 * @param infix ���ʽ
 */
void postfix(char *infix)
{
	int ii = 0, top = 0;
	int infixlen = strlen(infix);
	char stack[infixlen];
	memset(stack, 0, sizeof(stack));
	char op;

	while (ii < infixlen) {
		op = infix[ii];
		switch (op) {
		case '(': // ��������ջ
			if (top < sizeof(stack)) {
			top++;
			stack[top] = op;
			}
		break;
		case '+':
		case '-':
		case '*':
		case '/':
			while (priority(stack[top]) >= priority(op)) {
				printf("%c", stack[top]);
				top--;
			}
			// ��ջ
			if (top < sizeof(stack)) {
				top++;
				stack[top] = op;
			}
		break;
		case ')': // ��')'�������'('
			while (stack[top] != '(') {
				printf("%c", stack[top]);
				top--;
			}
			top--; // �����(
		break;
		default: // ������Ԫֱ�����
			printf("%c", op);
		break;
	    }
	    ii++;
	  }

	// ��top > 0,�������ջ��δ���������
	while (top > 0) {
		printf("%c", stack[top]);
		top--;
	}
}

 int main(void)
{
	char input[80];
	scanf("%s", input);
	postfix(input);
	return 0;
}
