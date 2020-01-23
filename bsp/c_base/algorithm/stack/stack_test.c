/*
给定一个以字符串表示的任意嵌套的三元表达式，计算表达式的值。你可以假定给定的表达式始终都是有效的并且只包含数字 0-9, ?, :, T 和?F (T 和?F?分别表示真和假）。

注意：

给定的字符串长度?≤ 10000。
所包含的数字都只有一位数。
条件表达式从右至左结合（和大多数程序设计语言类似）。
条件是?T?和?F其一，即条件永远不会是数字。
表达式的结果是数字?0-9, T 或者?F。
?

示例 1：

输入： "T?2:3"

输出： "2"

解释： 如果条件为真，结果为 2；否则，结果为 3。
*/

/*
优先级从右向左，因此反向遍历字符串，
可用两个栈分别记录操作（?的前一个字符）和值，
当值有两个且有一个操作时，执行三元运算
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
1249. 移除无效的括号
给你一个由 '('、')' 和小写字母组成的字符串 s。

你需要从字符串中删除最少数目的 '(' 或者 ')' （可以删除任意位置的括号)，使得剩下的「括号字符串」有效。

请返回任意一个合法字符串。

有效「括号字符串」应当符合以下 任意一条 要求：

空字符串或只包含小写字母的字符串
可以被写作 AB（A 连接 B）的字符串，其中 A 和 B 都是有效「括号字符串」
可以被写作 (A) 的字符串，其中 A 是一个有效的「括号字符串」


示例 1：

输入：s = "lee(t(c)o)de)"
输出："lee(t(c)o)de"
解释："lee(t(co)de)" , "lee(t(c)ode)" 也是一个可行答案。

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

