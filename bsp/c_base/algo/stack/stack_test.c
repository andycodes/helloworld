/*
����һ�����ַ�����ʾ������Ƕ�׵���Ԫ����ʽ��
�������ʽ��ֵ������Լٶ������ı���ʽʼ��
������Ч�Ĳ���ֻ�������� 0-9, ?, :,
T ��?F (T ��?F?�ֱ��ʾ��ͼ٣���

ע�⣺

�������ַ�������?�� 10000��
�����������ֶ�ֻ��һλ����
��������ʽ���������ϣ��ʹ������������������ƣ���
������?T?��?F��һ����������Զ���������֡�
����ʽ�Ľ��������?0-9, T ����?F��
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

����Ҫ���ַ�����ɾ��������Ŀ�� '(' ���� ')'
������ɾ������λ�õ�����)��
ʹ��ʣ�µġ������ַ�������Ч��

�뷵������һ���Ϸ��ַ�����

��Ч�������ַ�����Ӧ���������� ����һ�� Ҫ��

���ַ�����ֻ����Сд��ĸ���ַ���
���Ա�д�� AB��A ���� B�����ַ�����
���� A �� B ������Ч�������ַ�����
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

/*
71. ��·��

�� Unix ������һ���ļ��ľ���·��������Ҫ���������߻��仰˵������ת��Ϊ�淶·����

�� Unix �����ļ�ϵͳ�У�һ���㣨.����ʾ��ǰĿ¼���������⣬������ ��..�� ��ʾ��Ŀ¼�л�����һ����ָ��Ŀ¼�������߶������Ǹ������·������ɲ��֡�������Ϣ����ģ�Linux / Unix�еľ���·�� vs ���·��

��ע�⣬���صĹ淶·������ʼ����б�� / ��ͷ����������Ŀ¼��֮�����ֻ��һ��б�� /�����һ��Ŀ¼����������ڣ������� / ��β�����⣬�淶·�������Ǳ�ʾ����·��������ַ�����



ʾ�� 1��

���룺"/home/"
�����"/home"
���ͣ�ע�⣬���һ��Ŀ¼������û��б�ܡ�
ʾ�� 2��

���룺"/../"
�����"/"
���ͣ��Ӹ�Ŀ¼����һ���ǲ����еģ���Ϊ��������Ե������߼���
ʾ�� 3��

���룺"/home//foo/"
�����"/home/foo"
���ͣ��ڹ淶·���У��������б����Ҫ��һ��б���滻��
ʾ�� 4��

���룺"/a/./b/../../c/"
�����"/c"
ʾ�� 5��

���룺"/a/../../b/../c//.//"
�����"/c"
ʾ�� 6��

���룺"/a//b////c/d//././/.."
�����"/a/b/c"

*/
char* simplifyPath(char * path)
{
	if (path == NULL || path[0] != '/')
		return NULL;

	char *iterator;
	struct astack *astack = astack_init(1024);

	iterator = strtok(path, "/");
	while(iterator != NULL) {
	        if(strcmp(iterator, "..") == 0) {
			if (!astack_empty(astack)) {
				(void)astack_pop(astack);
			}
	        } else if(strcmp(iterator, ".") == 0) {
	        } else{
			struct astack_load load;
			load.string = iterator;
			astack_push(astack, load);
	        }

	        iterator = strtok(NULL, "/");
	}


	char * res = (char *)calloc(1024, sizeof(char));
	res[0] = '/';

	for(int i = 0; i < astack_size(astack); i++) {
		strcat(res, astack->load[i].string);
		if (i  != astack_size(astack) - 1)
			strcat(res, "/");
	}

	astack_exit(astack);

	return res;
}


/*
394. �ַ�������
����һ������������ַ������������������ַ�����

�������Ϊ: k[encoded_string]����ʾ���з������ڲ��� encoded_string �����ظ� k �Ρ�ע�� k ��֤Ϊ��������

�������Ϊ�����ַ���������Ч�ģ������ַ�����û�ж���Ŀո�������ķ��������Ƿ��ϸ�ʽҪ��ġ�

���⣬�������Ϊԭʼ���ݲ��������֣����е�����ֻ��ʾ�ظ��Ĵ��� k �����粻������� 3a �� 2[4] �����롣

ʾ��:

s = "3[a]2[bc]", ���� "aaabcbc".
s = "3[a2[c]]", ���� "accaccacc".
s = "2[abc]3[cd]ef", ���� "abcabccdcdcdef".

*/
struct astack_load{
	union dtype { /*Overload*/
		int times;
		char str[1024000];
	}utype;
};


struct astack{
	int count;
	int size;
	struct astack_load load[0];
};

char * decodeString(char * s){
	int num = 0;
	char *str = (char *)calloc(1024000, sizeof(char));
	int strCnt = 0;

	struct astack *numStack = astack_init(strlen(s));
	struct astack *strStack = astack_init(strlen(s));

	for(int i = 0; i < strlen(s); i++) {
		if (isdigit(s[i])) {
			num = num * 10 + s[i] - '0';
		} else if (isalpha(s[i])) {
			str[strCnt++] = s[i];
		} else if (s[i] == '[') {
			struct astack_load load;
			load.utype.times = num;
			astack_push(numStack, load);
			num = 0;

			struct astack_load strobj;
			strcpy(strobj.utype.str, str);
			astack_push(strStack, strobj);
			memset(str, '\0', sizeof(str));
			strCnt = 0;
		} else {
			struct astack_load load =  astack_pop(numStack);
			int times = load.utype.times;

			char tmp[1024000] = {{'\0'}};
			struct astack_load strobj = astack_pop(strStack);

			strcpy(tmp, strobj.utype.str);

			for (int j = 0; j < times; j++) {
				 strcat(tmp, str);
			}

			strcpy(str, tmp);
			strCnt = strlen(str);
		}
	}

	return str;
}

/*
1209. ɾ���ַ����е����������ظ��� II
����һ���ַ��� s����k ���ظ���ɾ������������� s ��ѡ�� k ����������ȵ���ĸ����ɾ�����ǣ�ʹ��ɾȥ���ַ����������Ҳ�����һ��

����Ҫ�� s �ظ��������޴�������ɾ��������ֱ���޷�����Ϊֹ��

��ִ��������ɾ�������󣬷������յõ����ַ�����

����𰸱�֤Ψһ��



ʾ�� 1��

���룺s = "abcd", k = 2
�����"abcd"
���ͣ�û��Ҫɾ�������ݡ�
ʾ�� 2��

���룺s = "deeedbbcccbdaa", k = 3
�����"aa"
���ͣ�
��ɾ�� "eee" �� "ccc"���õ� "ddbbbdaa"
��ɾ�� "bbb"���õ� "dddaa"
���ɾ�� "ddd"���õ� "aa"

*/
char * removeDuplicates(char * s, int k){
	int sLen = strlen(s);

	struct astack * numstack = astack_init(sLen);
	struct astack * strstack = astack_init(sLen);

	for (int i = 0 ; i < sLen; i++) {
		if (astack_empty(strstack)){
			struct astack_load numLoad;
			numLoad.utype.times = 1;
			astack_push(numstack, numLoad);

			struct astack_load strLoad;
			strLoad.utype.str = s[i];
			astack_push(strstack,strLoad);
		} else {
				struct astack_load strload = astack_top(strstack);
				if (strload.utype.str == s[i]) {
					struct astack_load numload = astack_top(numstack);
					if (numload.utype.times == k - 1) {
							(void)astack_pop(numstack);
							(void)astack_pop(strstack);
					} else {
							struct astack_load numLoad = astack_pop(numstack);
							numLoad.utype.times++;
							astack_push(numstack, numLoad);
					}
				} else {
						struct astack_load numLoad;
						numLoad.utype.times = 1;
						astack_push(numstack, numLoad);

						struct astack_load strLoad;
						strLoad.utype.str = s[i];
						astack_push(strstack,strLoad);
				}
		}
	}

	char *out = (char *)calloc(sLen, sizeof(char));
	int outCnt = 0;
	for (int i = 0; i < astack_size(strstack); i++) {

		for(int j = 0; j < numstack->load[i].utype.times; j++){
			out[outCnt++] = strstack->load[i].utype.str;
		}
	}

	return out;
}

/*
���� pushed �� popped �������У�ÿ�������е� ֵ�����ظ���ֻ�е����ǿ������������ջ�Ͻ��е����� push �͵��� pop �������еĽ��ʱ������ true�����򣬷��� false ��



ʾ�� 1��

���룺pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
�����true
���ͣ����ǿ��԰�����˳��ִ�У�
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
ʾ�� 2��

���룺pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
�����false
���ͣ�1 ������ 2 ֮ǰ������

*/
/*
����һ�� ̰��
˼·

���е�Ԫ��һ���ǰ�˳�� push ��ȥ�ģ���Ҫ������ô pop ������

���赱ǰջ��Ԫ��ֵΪ 2��ͬʱ��Ӧ�� popped ��������һ��Ҫ pop ��ֵҲΪ 2���Ǿͱ������̰����ֵ pop ��������Ϊ֮��� push ������ջ��Ԫ�ر�ɲ�ͬ�� 2 ������ֵ�������� pop �������� popped ���оͲ���Ӧ�ˡ�

�㷨

�� pushed �����е�ÿ������ push ��ջ�У�ͬʱ���������ǲ��� popped ��������һ��Ҫ pop ��ֵ������ǾͰ��� pop ������

��󣬼�鲻�����еĸ� pop ������ֵ���� pop �����ˡ�

*/

bool validateStackSequences(int* pushed, int pushedSize,
	int* popped, int poppedSize)
{
	if (pushed == NULL || popped == NULL) {
		return false;
	}

	struct astack *stack = astack_init(pushedSize);
	int j = 0;
	for (int i = 0; i < pushedSize; i++) {
		struct astack_load load;
		load.data = pushed[i];
		astack_push(stack, load);

		while(!astack_empty(stack) && j < pushedSize) {
			struct astack_load load = astack_top(stack);
			if (load.data == popped[j]) {
				astack_pop(stack);
				j++;
			} else {
				break;
			}
		}
	}

	return j == pushedSize;
}
/*
�ⷨһ��
ʹ��������ʵ��ջ�����ã�ģ��ջ�ĳ�ջ��ջ������size��ʾջ�Ĵ�С��size-1����ջ����λ���ˡ�

ע�⣺��������ʵ��ջ����Ȼ��ȡ���죬�������������ʵ���Ƽ����ر�������pushed�����ر���ʱ������Ϊջ������stackҲ���ر�󡣵�ʵ����ͬʱ����ջ�е�Ԫ�����������ر�࣬��ʹ��ںܴ���˷��ˡ�

*/
bool validateStackSequences(int* pushed, int pushedSize,
	int* popped, int poppedSize)
{
	if (pushed == NULL || popped == NULL) {
		return false;
	}

    if (pushedSize == 0 && poppedSize == 0)
        return true;
    else if(pushedSize != poppedSize)
        return false;

	int stack[pushedSize];

	int size = 0;
	for (int i = 0, j = 0; i < pushedSize; i++) {
		stack[size++] = pushed[i];
		while(size != 0 && stack[size -1] == popped[j]) {
			size--;j++;
		}
	}

	return size ==0;
}