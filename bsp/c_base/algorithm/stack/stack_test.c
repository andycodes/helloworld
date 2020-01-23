/*
����һ�����ַ�����ʾ������Ƕ�׵���Ԫ���ʽ��������ʽ��ֵ������Լٶ������ı��ʽʼ�ն�����Ч�Ĳ���ֻ�������� 0-9, ?, :, T ��?F (T ��?F?�ֱ��ʾ��ͼ٣���

ע�⣺

�������ַ�������?�� 10000��
�����������ֶ�ֻ��һλ����
�������ʽ���������ϣ��ʹ������������������ƣ���
������?T?��?F��һ����������Զ���������֡�
���ʽ�Ľ��������?0-9, T ����?F��
?

ʾ�� 1��

���룺 "T?2:3"

����� "2"

���ͣ� �������Ϊ�棬���Ϊ 2�����򣬽��Ϊ 3��
*/

/*
���ȼ�����������˷�������ַ�����
��������ջ�ֱ��¼������?��ǰһ���ַ�����ֵ��
��ֵ����������һ������ʱ��ִ����Ԫ����
*/
char* parseTernary(char* expression) {
	struct stack_blk* opStack = create_array_stack(10000);
	struct stack_blk* valueStack = create_array_stack(10000);

	for (int i = strlen(expression) - 1; i >= 0; --i) {
		if (isdigit(expression[i]) || expression[i] == 'T' || expression[i] == 'F') {
			struct stack_load load;
			load.data = expression[i];
			push(valueStack, load);
		}else if (expression[i] == '?') {
			i--;
			struct stack_load load;
			load.data = expression[i];
			push(opStack, load);
		}


		while (size(valueStack) >= 2 && size(opStack) >= 1) {

			struct stack_load c = pop(opStack);
			struct stack_load a = pop(valueStack);
			struct stack_load b = pop(valueStack);

			if (c.data == 'T') {
				push(valueStack, a);
			}
			else {
				push(valueStack, b);
			}
		}
	}

	struct stack_load out = pop(valueStack);
	char* outstr = (char *)malloc(2);
	outstr[0] = out.data;
	outstr[1] = '\0';
	return  outstr;
}


/*
1249. �Ƴ���Ч������
����һ���� '('��')' ��Сд��ĸ��ɵ��ַ��� s��

����Ҫ���ַ�����ɾ��������Ŀ�� '(' ���� ')' ������ɾ������λ�õ�����)��ʹ��ʣ�µġ������ַ�������Ч��

�뷵������һ���Ϸ��ַ�����

��Ч�������ַ�����Ӧ���������� ����һ�� Ҫ��

���ַ�����ֻ����Сд��ĸ���ַ���
���Ա�д�� AB��A ���� B�����ַ��������� A �� B ������Ч�������ַ�����
���Ա�д�� (A) ���ַ��������� A ��һ����Ч�ġ������ַ�����


ʾ�� 1��

���룺s = "lee(t(c)o)de)"
�����"lee(t(c)o)de"
���ͣ�"lee(t(co)de)" , "lee(t(c)ode)" Ҳ��һ�����д𰸡�

struct stack_load{
	char data;
	int pos;
};

*/

char * minRemoveToMakeValid(char * s){

	struct stack_blk * stack = create_array_stack(strlen(s));
	char *res = (char *)calloc(1, strlen(s) + 1);

	for (int i = 0; i < strlen(s); i++){
		if (s[i] == '(') {
			struct stack_load load;
			load.data = s[i];
			load.pos = i;
			push(stack,load);
		}else if(s[i] == ')') {
			if (!is_empty(stack)) {
				struct stack_load load = peek(stack);
				if (load.data == '(')
					(void)pop(stack);
				else {
					struct stack_load load;
					load.data = s[i];
					load.pos = i;
					push(stack,load);
				}
			} else {
				struct stack_load load;
				load.data = s[i];
				load.pos = i;
				push(stack,load);
			}
		}
	}

	//print_array_stack(stack);

	int i = 0;
	int j = 0;
	int k = 0;
	while(s[i] != '\0') {
		if (i == stack->load[k].pos && k < size(stack)){
			k++;
		} else {
			res[j++] = s[i];
		}

		i++;
	}

	return res;
}

