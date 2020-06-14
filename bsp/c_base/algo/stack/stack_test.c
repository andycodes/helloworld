/*
439
给定一个以字符串表示的任意嵌套的三元表达式，
计算表达式的值。你可以假定给定的表达式始终
都是有效的并且只包含数字 0-9, ?, :,
T 和?F (T 和?F?分别表示真和假）。

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

“F?1:T?4:5”Output: “4”
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
你需要从字符串中删除最少数目的 '(' 或者 ')'
（可以删除任意位置的括号)，
使得剩下的「括号字符串」有效。
请返回任意一个合法字符串。
有效「括号字符串」应当符合以下 任意一条 要求：
空字符串或只包含小写字母的字符串
可以被写作 AB（A 连接 B）的字符串，
其中 A 和 B 都是有效「括号字符串」
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

char * minRemoveToMakeValid(char * s)
{
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
71. 简化路径
以 Unix 风格给出一个文件的绝对路径，你需要简化它。
或者换句话说，将其转换为规范路径。
在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；
此外，两个点 （..） 表示将目录切换到上一级（指向父目录
）；两者都可以是复杂相对路径的组成部分。
更多信息请参阅：Linux / Unix中的绝对路径 vs 相对路径
请注意，返回的规范路径必须始终以斜杠 / 开头，
并且两个目录名之间必须只有一个斜杠 /。
最后一个目录名（如果存在）不能以 / 结尾。
此外，规范路径必须是表示绝对路径的最短字符串。

示例 1：

输入："/home/"
输出："/home"
解释：注意，最后一个目录名后面没有斜杠。
示例 2：
输入："/../"
输出："/"
解释：从根目录向上一级是不可行的，
因为根是你可以到达的最高级。
示例 3：

输入："/home//foo/"
输出："/home/foo"
解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。
示例 4：

输入："/a/./b/../../c/"
输出："/c"
示例 5：

输入："/a/../../b/../c//.//"
输出："/c"
示例 6：

输入："/a//b////c/d//././/.."
输出："/a/b/c"

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
394. 字符串解码
给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为: k[encoded_string]，表示其中方括号内部的
encoded_string 正好重复 k 次。注意 k 保证为正整数。
你可以认为输入字符串总是有效的；输入字符串中没有
额外的空格，且输入的方括号总是符合格式要求的。
此外，你可以认为原始数据不包含数字，所有的数字
只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
示例:
s = "3[a]2[bc]", 返回 "aaabcbc".
s = "3[a2[c]]", 返回 "accaccacc".
s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".
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
		} else {//"]"
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
1209. 删除字符串中的所有相邻重复项 II
给你一个字符串 s，「k 倍重复项删除操作」将会从 s 中选择
k 个相邻且相等的字母，并删除它们，使被删去的字符串的
左侧和右侧连在一起。
你需要对 s 重复进行无限次这样的删除操作，直到无法继
续为止。
在执行完所有删除操作后，返回最终得到的字符串。
本题答案保证唯一。
示例 1：
输入：s = "abcd", k = 2
输出："abcd"
解释：没有要删除的内容。
示例 2：
输入：s = "deeedbbcccbdaa", k = 3
输出："aa"
解释：
先删除 "eee" 和 "ccc"，得到 "ddbbbdaa"
再删除 "bbb"，得到 "dddaa"
最后删除 "ddd"，得到 "aa"

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
给定 pushed 和 popped 两个序列，每个序列中的 值都不重复，
只有当它们可能是在最初空栈上进行的推入 push 和弹出
pop 操作序列的结果时，返回 true；否则，返回 false 。
示例 1：
输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
示例 2：
输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
输出：false
解释：1 不能在 2 之前弹出。
*/
/*
方法一： 贪心
思路
所有的元素一定是按顺序 push 进去的，重要的是怎么 pop 出来？
假设当前栈顶元素值为 2，同时对应的 popped 序列中下一个要
pop 的值也为 2，那就必须立刻把这个值 pop 出来。因为之后的
push 都会让栈顶元素变成不同于 2 的其他值，这样再 pop 出来
的数 popped 序列就不对应了。
算法
将 pushed 队列中的每个数都 push 到栈中，同时检查这个数是不
是 popped 序列中下一个要 pop 的值，如果是就把它 pop 出来。
最后，检查不是所有的该 pop 出来的值都是 pop 出来了。
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
解法一：
使用数组来实现栈的作用，模拟栈的出栈入栈操作。
size表示栈的大小，size-1就是栈顶的位置了。

注意：用数组来实现栈，虽然存取更快，但多数情况下其
实不推荐。特别是数组pushed可能特别大的时候，那作为栈
的数组stack也会特别大。但实际上同时存在栈中的元素往
往不是特别多，这就存在很大的浪费了。
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

/*  递减栈
739. 每日温度
难度中等283
根据每日 气温 列表，请重新生成一个列表，对应位置的
输出是需要再等待多久温度才会升高超过该日的天数。
如果之后都不会升高，请在该位置用 0 来代替。
例如，给定一个列表
temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，
你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。
提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均
为华氏度，都是在 [30, 100] 范围内的整数。
*/
/*
遍历整个数组，如果栈不空，且当前数字大于栈顶元素，
那么如果直接入栈的话就不是 递减栈 ，
所以需要取出栈顶元素，由于当前数字大于栈顶元素的
数字，而且一定是第一个大于栈顶元素的数，
直接求出下标差就是二者的距离。

继续看新的栈顶元素，直到当前数字小于等于栈顶元
素停止，然后将数字入栈，这样就可以一直保持递减栈，
且每个数字和第一个大于它的数的距离也可以算出来。
*/
int* dailyTemperatures(int* T, int TSize, int* returnSize)
{
	int *ret = (int *)calloc(TSize, sizeof(int));
	struct List list;
	stack_init(&list);
	for(int i = 0; i < TSize; i++) {
		while(!stack_empty(&list)) {
			struct DataEntry *entry = stack_entry_top(&list);
			if (T[i] > T[entry->key])  {
				stack_pop(&list);
				ret[entry->key] = i - entry->key;
			} else {
				break;
			}
		}
		stack_key_push(&list, i);
	}

	*returnSize = TSize;
	return ret;
}

/*单调栈
496. 下一个更大元素 I
难度简单186
给定两个没有重复元素的数组 nums1 和 nums2 ，其中nums1 是
nums2 的子集。找到 nums1 中每个元素在 nums2 中的下一个比其大的值。
nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置
的右边的第一个比 x 大的元素。如果不存在，对应位置输出-1。
示例 1:
输入: nums1 = [4,1,2], nums2 = [1,3,4,2].
输出: [-1,3,-1]
解释:
    对于num1中的数字4，你无法在第二个数组中找到
    下一个更大的数字，因此输出 -1。
    对于num1中的数字1，
    第二个数组中数字1右边的下一个较大数字是 3。
    对于num1中的数字2，第二个数组中没有下一个更大的数字，
    因此输出 -1。
注意:
1.	nums1和nums2中所有元素是唯一的。

*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(
int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
	if (nums1Size == 0 || nums2Size == 0) {
		*returnSize = 0;
		return NULL;
	}

	int nextBig[nums2Size];
	memset(nextBig, -1, sizeof(nextBig));

	struct List list;
	stack_init(&list);
	for(int i = 0; i < nums2Size; i++) {
		while (!stack_empty(&list) ) {
			struct DataEntry *top =  stack_top_entry(&list);
			if (nums2[i] > nums2[top->key]) {
				stack_pop(&list);
				nextBig[top->key] = nums2[i];
			}else {
				break;
			}
		}

		stack_push_key(&list, i);
	}

	int *ret = calloc(nums1Size, sizeof(int));
	for(int i = 0; i < nums1Size; i++) {
		for (int j = 0; j < nums2Size; j++) {
			if (nums1[i] == nums2[j]) {
				ret[i] = nextBig[j];
			}
		}
	}

	*returnSize = nums1Size;
	return ret;
}

/*
503. 下一个更大元素 II
给定一个循环数组（最后一个元素的下一个元素是数组的第一
个元素），输出每个元素的下一个更大元素。数字 x 的下一个
更大的元素是按数组遍历顺序，这个数字之后的第一个比它
更大的数，这意味着你应该循环地搜索它的下一个更大的数。
如果不存在，则输出 -1。
示例 1:
输入: [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数；
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElements(int* nums, int numsSize, int* returnSize)
{
	struct astack *stack = astack_init(2 * numsSize);
	int *res = (int *)calloc(numsSize, sizeof(int));
	memset(res, -1, sizeof(int) * numsSize);

	for (int i = 0; i < 2 * numsSize - 1; i++) {
		int idx = i % numsSize;
		while(!astack_empty(stack) && nums[astack_top_key(stack)] < nums[idx]) {
			struct astack_load pop = astack_pop(stack);
			res[pop.key] =  nums[idx];
		}

		struct astack_load load;
		load.key = idx;
		astack_push(stack, load);
	}

	*returnSize = numsSize;
	astack_exit(stack);
	return res;
}

