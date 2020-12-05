/*
224. ����������
227. ���������� II
772. ���������� III
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
282. �����ʽ��������
�Ѷ�����136�ղط����л�ΪӢ�Ĺ�ע����
����һ������������ 0-9 ���ַ�����һ��Ŀ��ֵ��������֮��
��Ӷ�Ԫ�����������һԪ��+��- �� * �����������ܹ��õ�
Ŀ��ֵ�ı��ʽ��
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


