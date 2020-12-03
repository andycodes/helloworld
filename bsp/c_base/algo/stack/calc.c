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

 /*
227. ���������� II
�Ѷ��е�173�ղط����л�ΪӢ�Ĺ�ע����
ʵ��һ�������ļ�����������һ���򵥵��ַ������ʽ��ֵ��
�ַ������ʽ�������Ǹ�������+�� - ��*��/ ����������Ϳո�  �� ���������������������֡�
ʾ�� 1:
����: "3+2*2"
���: 7
 */

 int calculate(char * s){
    int stack[strlen(s)/2+1];
    int tail=0;     //��ջβ��
    int num=0;
    int pos=0;      //�ַ���s�е�λ��
    //�ַ����ʽ�����Ǹ��������Ե�һ��������Ϊ��
    char flag='+';
    //���ں���Ϊ��Ӧ�����һ���ַ��ǿո�����
    while(pos<=strlen(s)){
        //'('��������������
        if(s[pos]=='('){
            pos++;  //ָ����һ�������ٵݹ�
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
            //')'�������ַ����棬����������ѭ��������ջ�еĽ��������
            if(s[pos]==')'){
                break;
            }
            //����
            num=0;
            flag=s[pos];
        }
            //�ǲ��ǿո�pos��Ҫ++
            pos++;
    }
    //������
    int ret=0;
    for(int i=0;i<tail;i++){
        ret+=stack[i];
    }
    return ret;
}

/*
282. �����ʽ��������
�Ѷ�����136�ղط����л�ΪӢ�Ĺ�ע����
����һ������������ 0-9 ���ַ�����һ��Ŀ��ֵ��������֮����Ӷ�Ԫ�����������һԪ��+��- �� * �����������ܹ��õ�Ŀ��ֵ�ı��ʽ��
ʾ�� 1:
����: num = "123", target = 6
���: ["1+2+3", "1*2*3"]
ʾ�� 2:
����: num = "232", target = 8
���: ["2*3+2", "2+3*2"]


*/

#define MAX_COUNT 10000 // ��ĸ����㹻��
#define NUM_COUNT 100 // �������ĸ����㹻��
long long num[NUM_COUNT] = {0};

long long calc(char *a)
{ // ������ʽa��ֵ
	// �����ֺͷ��ţ���ջ
	memset(num, 0, sizeof(num));
	int numCnt = 0, opCnt = 0;
	long long value = 0;
    char oper = '+';
	int len = strlen(a);
	for (int i = 0; i < len; i++) {
		if (a[i] == '0') { // 05������0��ͷ�����ֲ�����Ҫ��
			if (i < len - 1 && isdigit(a[i+1])) {
				return INT_MIN; // ���ָ�ʽ���ԣ�ֱ�ӷ���
			}
		}
		if (isdigit(a[i])) {
			for (; isdigit(a[i]); i++) { // ������ֵ
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
				return INT_MIN; // ���ָ�ʽ���ԣ�ֱ�ӷ���
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
	strncpy(t, a, pos); // ǰ��
	strcat(t, op); // ����
	strcat(t, a + pos); // ���
	return t;
}

void dfs(char *a, int pos, int target, char**p, int* returnSize)
{
	if (a == NULL || a[0] == 0 || p == NULL || returnSize == NULL) {
		return;
	}
	int len = strlen(a);
	if (pos >= len) { // �����Ѿ���ȫ��
		if (target == calc(a)) { // ����
			if (*returnSize > MAX_COUNT) {
				printf("overflow\n");
				return;
			}
			p[*returnSize] = a;
			(*returnSize)++;
		} else { // �����ϣ�����
			free(a);
		}
	} else {
		char *a1 = newStr(a, len + 2, pos, "*"); // *��
		char *a2 = newStr(a, len + 2, pos, "+"); // +��
		char *a3 = newStr(a, len + 2, pos, "-"); // -��
		dfs(a1, pos + 2, target, p, returnSize); // *��
		dfs(a2, pos + 2, target, p, returnSize); // +��
		dfs(a3, pos + 2, target, p, returnSize); // -��
		dfs(a, pos + 1, target, p, returnSize); // ���ӷ���
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
772. ���������� III
�Ѷ�����32�ղط����л�ΪӢ�Ĺ�ע����
ʵ��һ�������ļ�����������򵥵ı��ʽ�ַ�����
���ʽ�ַ������԰��������� ( �������� )���Ӻ� + �ͼ��� -���Ǹ� �����Ϳո� ��
���ʽ�ַ���ֻ�����Ǹ������� +, -, *, / �������������� ( �������� )�Ϳո� ������������Ҫ���½ضϡ�
����Լٶ��������ַ���������Ч�ġ����е��м����ķ�ΧΪ [-2147483648, 2147483647]��

һЩ���ӣ�
"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12


*/

int calculate(char* s){
    int len1 = strlen(s);
    // ȥ���ո�
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

        // ����������ݹ����
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

		// �����ֽ��д���
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
224. ����������
ʵ��һ�������ļ�����������һ���򵥵��ַ������ʽ��ֵ��
�ַ������ʽ���԰��������� ( �������� )���Ӻ� + ������ -���Ǹ������Ϳո�  ��

ʾ�� 1:

����: "1 + 1"
���: 2
ʾ�� 2:

����: " 2-1 + 2 "
���: 3
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