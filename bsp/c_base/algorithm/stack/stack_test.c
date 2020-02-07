/*
����һ�����ַ�����ʾ������Ƕ�׵���Ԫ���ʽ��
������ʽ��ֵ������Լٶ������ı��ʽʼ��
������Ч�Ĳ���ֻ�������� 0-9, ?, :,
T ��?F (T ��?F?�ֱ��ʾ��ͼ٣���

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

�� Unix �����ļ�ϵͳ�У�һ���㣨.����ʾ��ǰĿ¼�������⣬������ ��..�� ��ʾ��Ŀ¼�л�����һ����ָ��Ŀ¼�������߶������Ǹ������·������ɲ��֡�������Ϣ����ģ�Linux / Unix�еľ���·�� vs ���·��

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

struct astack *astack_init(int sz)
{
	struct astack * stack =
		(struct astack  *)malloc(sizeof(struct astack) + sz*sizeof(struct astack_load));
	if (stack == NULL) {
		printf("arr malloc error!");
		return NULL;
	}

	stack->size = sz;
	stack->count = 0;

	return stack;
}

/*     1|2|3|4....       */
void astack_push(struct astack * stack,struct astack_load load)
{
	stack->load[stack->count++] = load;
	if (stack->count > stack->size) {
		printf("[%s] astack_push count[%d] too big\n", __func__, stack->count);
		stack->count = stack->count % stack->size;
	}
}

// ·µ»Ø¡°Õ»¡±µÄ´óÐ¡
int astack_size(struct astack * stack)
{
	return stack->count;
}

// ·µ»Ø¡°Õ»¡±ÊÇ·ñÎª¿Õ
int astack_empty(struct astack * stack)
{
	return astack_size(stack)==0;
}

// ·µ»Ø¡°Õ»¶¥ÔªËØÖµ¡±
struct astack_load  astack_top(struct astack * stack)
{
	if (astack_empty(stack)) {
		printf("err astack_empty\n");
		return stack->load[0];
	}

	return stack->load[stack->count -1];
}


// ·µ»Ø¡°Õ»¶¥ÔªËØÖµ¡±£¬²¢É¾³ý¡°Õ»¶¥ÔªËØ¡±
struct astack_load  astack_pop(struct astack * stack)
{
	if (astack_empty(stack)) {
		printf("err astack_empty\n");
		return stack->load[0];
	}

	struct astack_load  ret = stack->load[stack->count -1];
	stack->count--;
	return ret;
}


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
