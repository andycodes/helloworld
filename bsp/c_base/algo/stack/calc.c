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

 /*
227. 基本计算器 II
难度中等173收藏分享切换为英文关注反馈
实现一个基本的计算器来计算一个简单的字符串表达式的值。
字符串表达式仅包含非负整数，+， - ，*，/ 四种运算符和空格  。 整数除法仅保留整数部分。
示例 1:
输入: "3+2*2"
输出: 7
 */

 int calculate(char * s){
    int stack[strlen(s)/2+1];
    int tail=0;     //堆栈尾部
    int num=0;
    int pos=0;      //字符串s中的位置
    //字符表达式仅含非负数，所以第一个符号设为正
    char flag='+';
    //等于号是为了应对最后一个字符是空格的情况
    while(pos<=strlen(s)){
        //'('是在运算符后面的
        if(s[pos]=='('){
            pos++;  //指向下一个数字再递归
            num=calculate(&(s[pos]));
        }
        while(isdigit(s[pos])){
            num=num*10+(s[pos]-'0');
            pos++;
        }
        if(s[pos]!=' '){
            switch (flag) {
                case '+':
                    stack[tail]=num;
                    tail++;
                    break;
                case '-':
                    stack[tail]=-1*num;
                    tail++;
                    break;
                case '*':
                    stack[tail-1]*=num;
                    break;
                case '/':
                    stack[tail-1]/=num;
                    break;
            }
            //')'在数字字符后面，遇到则跳出循环，计算栈中的结果并返回
            if(s[pos]==')'){
                break;
            }
            //重置
            num=0;
            flag=s[pos];
        }
            //是不是空格pos都要++
            pos++;
    }
    //输出结果
    int ret=0;
    for(int i=0;i<tail;i++){
        ret+=stack[i];
    }
    return ret;
}

/*
282. 给表达式添加运算符
难度困难136收藏分享切换为英文关注反馈
给定一个仅包含数字 0-9 的字符串和一个目标值，在数字之间添加二元运算符（不是一元）+、- 或 * ，返回所有能够得到目标值的表达式。
示例 1:
输入: num = "123", target = 6
输出: ["1+2+3", "1*2*3"]
示例 2:
输入: num = "232", target = 8
输出: ["2*3+2", "2+3*2"]


*/

#define MAX_COUNT 10000 // 解的个数足够大
#define NUM_COUNT 100 // 操作数的个数足够大
long long num[NUM_COUNT] = {0};

long long calc(char *a)
{ // 计算表达式a的值
	// 将数字和符号，入栈
	memset(num, 0, sizeof(num));
	int numCnt = 0, opCnt = 0;
	long long value = 0;
    char oper = '+';
	int len = strlen(a);
	for (int i = 0; i < len; i++) {
		if (a[i] == '0') { // 05这种以0开头的数字不符合要求
			if (i < len - 1 && isdigit(a[i+1])) {
				return INT_MIN; // 发现格式不对，直接返回
			}
		}
		if (isdigit(a[i])) {
			for (; isdigit(a[i]); i++) { // 计数数值
				value = value * 10 + (a[i] - '0');
			}
		}
		if (!isdigit(a[i]) || i == len -1) {
			switch(oper) {
			case '+':
				num[numCnt++] = value;
				break;
			case '-':
				num[numCnt++] = -value;
				break;
			case '*':
				value *= num[numCnt - 1];
				num[numCnt - 1] = value;
				break;
			default:
				return INT_MIN; // 发现格式不对，直接返回
			}
			value = 0;
			oper = a[i];
		}
	}
	value = num[numCnt - 1];
	for (numCnt--; numCnt > 0; numCnt--) {
		value += num[numCnt - 1];
	}
	return value;
}

char* newStr(char *a, int len, int pos, const char*op)
{
	char *t = (char*)calloc(sizeof(char), len);
	strncpy(t, a, pos); // 前段
	strcat(t, op); // 符号
	strcat(t, a + pos); // 后段
	return t;
}

void dfs(char *a, int pos, int target, char**p, int* returnSize)
{
	if (a == NULL || a[0] == 0 || p == NULL || returnSize == NULL) {
		return;
	}
	int len = strlen(a);
	if (pos >= len) { // 符号已经加全了
		if (target == calc(a)) { // 符合
			if (*returnSize > MAX_COUNT) {
				printf("overflow\n");
				return;
			}
			p[*returnSize] = a;
			(*returnSize)++;
		} else { // 不符合，丢掉
			free(a);
		}
	} else {
		char *a1 = newStr(a, len + 2, pos, "*"); // *号
		char *a2 = newStr(a, len + 2, pos, "+"); // +号
		char *a3 = newStr(a, len + 2, pos, "-"); // -号
		dfs(a1, pos + 2, target, p, returnSize); // *号
		dfs(a2, pos + 2, target, p, returnSize); // +号
		dfs(a3, pos + 2, target, p, returnSize); // -号
		dfs(a, pos + 1, target, p, returnSize); // 不加符号
	}
}

char **addOperators(char *a, int target, int* returnSize)
{
	if (a == NULL || returnSize == NULL) {
		return NULL;
	}
	char **p = (char**)calloc(MAX_COUNT, sizeof(char*));
	if (p == NULL) {
		return NULL;
	}
	*returnSize = 0;
	dfs(strdup(a), 1, target, p, returnSize);
	return p;
}

/*
772. 基本计算器 III
难度困难32收藏分享切换为英文关注反馈
实现一个基本的计算器来计算简单的表达式字符串。
表达式字符串可以包含左括号 ( 和右括号 )，加号 + 和减号 -，非负 整数和空格 。
表达式字符串只包含非负整数， +, -, *, / 操作符，左括号 ( ，右括号 )和空格 。整数除法需要向下截断。
你可以假定给定的字符串总是有效的。所有的中间结果的范围为 [-2147483648, 2147483647]。

一些例子：
"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12


*/

int calculate(char* s){
    int len1 = strlen(s);
    // 去掉空格
    int k =0;
    for(int i= 0; i < len1; i++){
        if(s[i] != ' '){
            s[k++] = s[i];
        }
    }
    s[k] = '\0';

    int len = strlen(s);
    int top = -1;
    int *stack = calloc(sizeof(int), len);

    long num = 0;
    char fuhao = '#';
    for(int i = 0; i< len;i++) {
        num = 0;
        if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            fuhao = s[i];
            continue;
        }

        // 针对括号做递归操作
        if (s[i] == '(') {
           int cnt = 0;
           int index = i;
           int m = 0;
           char *temp = calloc(sizeof(char), 2500);
           for (; i < len; i++) {
               if (s[i] == '(') {
                   ++cnt;
               } else if (s[i] == ')') {
                   --cnt;
               }
               if(i!=index) {
                   temp[m++] = s[i];
               }
               if (cnt == 0) {
                   temp[m-1] = '\0';
                   num = calculate(temp);
                   break;
               }
           }
           free(temp);
        }

		// 对数字进行处理
        int flag = 0;
        while(isdigit(s[i])) {
            num = (s[i]- '0')+ num*10;
            i++;
            flag = 1;
        }
        if(flag ==1)i--;

        if(fuhao == '+' || fuhao == '#'){
            stack[++top] = num;
        } else if (fuhao == '-') {
            stack[++top] = num * (-1);
        } else if (fuhao == '*') {
           stack[top] = stack[top] * num;
        } else if (fuhao == '/') {
           stack[top] = stack[top] / num;
        }
    }

    int sum = 0;
    for(int i = 0; i <= top; i++) {
        sum += stack[i];
    }
    return sum;
}

/*
224. 基本计算器
实现一个基本的计算器来计算一个简单的字符串表达式的值。
字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格  。

示例 1:

输入: "1 + 1"
输出: 2
示例 2:

输入: " 2-1 + 2 "
输出: 3
*/

int calculate(char * s)
{
	 int stack[1024];
	 int top = -1;

	int res = 0, n = strlen(s), sign = 1;
        for(int i=0; i<n; i++) {
            int num = 0;
            if(s[i] >= '0') {
                while(i<n && s[i] >= '0') {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                i--;
                res += sign * num;
            }
            else if(s[i] == '+') sign = 1;
            else if(s[i] == '-') sign = -1;
            else if(s[i] == '(') {
                //st.push(res);
				stack[++top] = res;
               // st.push(sign);
				stack[++top] = sign;
                res = 0;
                sign = 1;
            }
            else if(s[i] == ')') {
			res *= stack[top--];
               // res *= st.top(); st.pop();
               // res += st.top(); st.pop();
				res += stack[top--];
            }
        }
        return res;

}