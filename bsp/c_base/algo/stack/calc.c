#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/**
 * 比较运算子优先级
 * @param op 运算子
 * @return 运算子值
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
 * 中序式转后序式
 * @param infix 表达式
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
		case '(': // 运算子入栈
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
			// 入栈
			if (top < sizeof(stack)) {
				top++;
				stack[top] = op;
			}
		break;
		case ')': // 遇')'则输出至'('
			while (stack[top] != '(') {
				printf("%c", stack[top]);
				top--;
			}
			top--; // 不输出(
		break;
		default: // 遇运算元直接输出
			printf("%c", op);
		break;
	    }
	    ii++;
	  }

	// 当top > 0,继续输出栈中未输出的内容
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
