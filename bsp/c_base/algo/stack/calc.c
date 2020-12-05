/*
224. 基本计算器
227. 基本计算器 II
772. 基本计算器 III
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

void postfix(char *instr, char *postarr)
{
	int i = 0, top = -1;
	int instrlen = strlen(instr);
	char stack[instrlen];
	char op;

	while (i < instrlen) {
		op = instr[i];
		switch (op) {
			case ' ':break;
			case '(':
				stack[++top] = op;
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				while (top >= 0 && priority(stack[top]) >= priority(op)) {
					sprintf(postarr + strlen(postarr), "%c", stack[top]);
					top--;
				}

				stack[++top] = op;
				break;
			case ')':
				while (stack[top] != '(') {
					sprintf(postarr + strlen(postarr), "%c", stack[top]);
					top--;
				}
				top--;
				break;
			default:
				{	unsigned int num = 0;
					while(isdigit(instr[i])) {
						num = num * 10 + instr[i] - '0';
						i++;
					}

					sprintf(postarr + strlen(postarr), "#%u", num);
					i--;
				}
			break;
		}
		i++;
	}

	while (top >= 0) {
		sprintf(postarr + strlen(postarr), "%c", stack[top]);
		top--;
	}
}

unsigned int math(unsigned int d0, unsigned int d1, int op)
{
	switch (op) {
		case '+':
			return d0 + d1;
		case '-':
			return d0 - d1;
		case '*':
			return d0 * d1;
		case '/':
			return d0 / d1;
		default: return 0;
	}

	return 0;
}

bool checkfuhao(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int calculate(char * s)
{
	char *instr = s;
        int slen = strlen(s);
	char posstr[2 * slen + 1];
        memset(posstr, '\0', sizeof(posstr));
	postfix(instr, posstr);
	//printf("%s", posstr);

	unsigned int stack[slen];
	int top = -1;

	int plen = strlen(posstr);
	for (int i = 0; i < plen; i++) {
		if (posstr[i] == '#') {
			unsigned int num = 0;
			i++;
			while(isdigit(posstr[i])) {
				num = num * 10 + posstr[i] - '0';
				i++;
			}
			i--;
			stack[++top] = num;
		} else if (checkfuhao(posstr[i])) {
			unsigned int d1 = stack[top--];
			unsigned int d0 = stack[top--];

			stack[++top] = math(d0, d1, posstr[i]);
		}
	}

	return (int)stack[0];
}

/*
282. 给表达式添加运算符
难度困难136收藏分享切换为英文关注反馈
给定一个仅包含数字 0-9 的字符串和一个目标值，在数字之间
添加二元运算符（不是一元）+、- 或 * ，返回所有能够得到
目标值的表达式。
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


