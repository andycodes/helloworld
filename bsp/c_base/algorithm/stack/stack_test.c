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

