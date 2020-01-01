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

