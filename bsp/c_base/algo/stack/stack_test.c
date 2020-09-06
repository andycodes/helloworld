/*
439
给定一个以字符串表示的任意嵌套的三元表达式，
计算表达式的值。你可以假定给定的表达式始终
都是有效的并且只包含数字 0-9, ?, :,
T 和?F (T 和?F?分别表示真和假）。

注意：

给定的字符串长度 ≤ 10000。
所包含的数字都只有一位数。
条件表达式从右至左结合（和大多数程序设计语言类似）。
条件是 T 和 F其一，即条件永远不会是数字。
表达式的结果是数字 0-9, T 或者 F。


示例 1：

输入： "T?2:3"

输出： "2"

解释： 如果条件为真，结果为 2；否则，结果为 3。

“F?1:T?4:5”Output: “4”


“F?T?4:5:T?4:5

示例 3：

输入： "T?T?F:5:3"

输出： "F"

解释： 条件表达式自右向左结合。使用括号的话，相当于：

             "(T ? (T ? F : 5) : 3)"                   "(T ? (T ? F : 5) : 3)"
          -> "(T ? F : 3)"                 或者       -> "(T ? F : 5)"
          -> "F"                                     -> "F"
*/

/*
优先级从右向左，因此反向遍历字符串，
可用两个栈分别记录操作（?的前一个字符）和值，
当值有两个且有一个操作时，执行三元运算
*/
#define STACK_MAX 10000
char* parseTernary(char* expression)
{
	int stackData[STACK_MAX];
	int topData = -1;

	int stackOp[STACK_MAX];
	int topOp = -1;

	int slen = strlen(expression);
	for (int i = slen - 1; i >= 0; i--) {
		if (isdigit(expression[i]) || expression[i] == 'T' || expression[i] == 'F') {
			stackData[++topData] = expression[i];
		}else if(expression[i] == ':') {
			continue;
		} else if(expression[i] == '?') {
			stackOp[++topOp] = expression[--i];
		}

		if(topOp >= 0 && topData >= 1) {
			int data1 = stackData[topData--];
			int data2 = stackData[topData--];
			int op = stackOp[topOp--];
			stackData[++topData] = op == 'T' ? data1 : data2;
		}
	}

	char *out = (char *)calloc(2, sizeof(char));
	out[0] =  stackData[0];
	return out;
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

遇到'(' 直接入栈
遇到')',如果栈顶是'(' 说明可以成对，移除栈顶，否者入栈
答案就是字符串移除栈中符号。
*/
char * minRemoveToMakeValid(char * s)
{
	char *res = (char *)calloc(1, strlen(s) + 1);
	int slen = strlen(s);

	int stack[slen][2];// 0-data  1-idx
	int top = -1;
	memset(stack, 0, sizeof(stack));

	for (int i = 0; i < strlen(s); i++){
		if (s[i] == '(') {
			stack[++top][0] = s[i];
			stack[top][1] = i;
		}else if(s[i] == ')') {
			if (top >= 0) {
				if(stack[top][0] == '(') {
					top--;//能够成对，从队列中剔除
				} else {//记录需要删除的
					stack[++top][0] = s[i];
					stack[top][1] = i;
				}
			} else {//记录需要删除的
				stack[++top][0] = s[i];
				stack[top][1] = i;
			}
		}
	}

	int i = 0;
	int j = 0;
	int k = 0;
	while(s[i] != '\0') {
		if (i == stack[k][1] && k <= top){
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
char * simplifyPath(char * path)
{
	if (path == NULL || path[0] != '/')
		return NULL;

	char *it = NULL;
	char *tmp = NULL;
	int slen = strlen(path);

	char* stack[slen];
	int top = -1;

	it = strtok_r(path, "/", &tmp);
	while(it != NULL) {
		if (strcmp(it, ".") == 0) {
		} else if(strcmp(it, "..") == 0){
			if (top >= 0) {
				top--;
			}
		} else {
			stack[++top] = it;
		}

		it = strtok_r(NULL, "/", &tmp);
	}

	char *res = calloc(slen + 1, sizeof(char));

	if (top == -1)
		res[0] = '/';

	for (int i = 0; i <= top; i++) {
		strcat(res, "/");
		strcat(res, stack[i]);
	}

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

char * decodeString(char * s)
{
	int num = 0;
	char *str = (char *)calloc(1024000, sizeof(char));
	int strCnt = 0;
	int slen = strlen(s);

	if (s == NULL || strlen(s) == 0)
		return str;

	int stackNum[slen];
	int topnum = -1;
	char stackStr[slen][1024000];
	int topstr = -1;

	for(int i = 0; i < strlen(s); i++) {
		if (isdigit(s[i])) {
			num = num * 10 + s[i] - '0';
		} else if (isalpha(s[i])) {
			str[strCnt++] = s[i];
		} else if (s[i] == '[') {
			stackNum[++topnum] = num;
			num = 0;

			strcpy(stackStr[++topstr], str);
			memset(str, '\0', sizeof(str));
			strCnt = 0;
		} else {//"]"
			int times = stackNum[topnum--];

			char tmp[1024000] = {{'\0'}};
			strcpy(tmp, stackStr[topstr--]);//历史前缀

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
char * removeDuplicates(char * s, int k)
{
	if (s == NULL || strlen(s) < k || k < 2)
		return s;

	int slen = strlen(s);
	int stack[slen][2]; // 0 --al  1 --cnt
	int top = -1;

	int i = 0;
	while(s[i] != '\0') {
		if (top < 0) {
			stack[++top][0] = s[i];
			stack[top][1] = 1;
		} else {
			if (s[i] == stack[top][0]) {
				if (stack[top][1] == k -1) {
					top--;
				} else {
					stack[top][1]++;
				}
			} else {
				stack[++top][0] = s[i];
				stack[top][1] = 1;
			}
		}
		i++;
	}

	char *res = (char *)calloc(slen + 1, sizeof(char));
	int resCnt = 0;
	for (int i = 0; i <= top; i++) {
		for (int j = 0; j < stack[i][1]; j++)
			res[resCnt++] = stack[i][0];
	}

	return res;
}

/*
946. 验证栈序列
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
入栈
栈顶等于popped 则出栈
判断是否栈空
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
	int top = -1;

	for (int i = 0, j = 0; i < pushedSize; i++) {
		stack[++top] = pushed[i];
		while(top >= 0 && stack[top] == popped[j]) {
			top--;
			j++;
		}
	}

	return top == -1;
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
	*returnSize = TSize;
	if (T == NULL || TSize <= 0) {
		return T;
	}

	int stack[TSize][2];//0--value ; 1---idx
	int top = -1;

	int *res = (int *)calloc(TSize, sizeof(int));

	for (int i = 0; i < TSize; i++) {
		if (top < 0 || T[i] <= stack[top][0]) {
			stack[++top][0] = T[i];
			stack[top][1] = i;
			continue;
		}

		while(top >= 0 && T[i] > stack[top][0]) {
			int idx = stack[top--][1];
			res[idx] = i - idx;
		}

		stack[++top][0] = T[i];
		stack[top][1] = i;
	}

	return res;
}

/*
496. 下一个更大元素 I
难度简单186
给定两个没有重复元素的数组 nums1 和 nums2 ，其中nums1 是
nums2 的子集。找到 nums1 中每个元素在 nums2 中的下一个比其大
的值。nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位
置的右边的第一个比 x 大的元素。如果不存在，对应位置输
出-1。
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
int* nextGreaterElement(int* nums1, int nums1Size,
int* nums2, int nums2Size, int* returnSize)
{
	if (nums1Size == 0 || nums2Size == 0) {
		*returnSize = 0;
		return NULL;
	}

	int nums2NextBig[nums2Size];//对nums2 建立一下个更大元素
	memset(nums2NextBig, -1, sizeof(nums2NextBig));

	int stack[nums2Size];//idx
	int top = -1;
	for(int i = 0; i < nums2Size; i++) {
		while (top >= 0 && nums2[i] > nums2[stack[top]]) {
			nums2NextBig[stack[top]] = nums2[i];
			top--;
		}

		stack[++top] = i;
	}

	int *ret = calloc(nums1Size, sizeof(int));
	for(int i = 0; i < nums1Size; i++) {
		for (int j = 0; j < nums2Size; j++) {
			if (nums1[i] == nums2[j]) {
				ret[i] = nums2NextBig[j];
			}
		}
	}

	*returnSize = nums1Size;
	return ret;
}

/*
503. 下一个更大元素 II
给定一个循环数组（最后一个元素的下一个元素
是数组的第一个元素），输出每个元素的下一个更大元素。
数字 x 的下一个更大的元素是按数组遍历顺序，
这个数字之后的第一个比它更大的数，这意味着你应该
循环地搜索它的下一个更大的数。
如果不存在，则输出 -1。
示例 1:
输入: [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数；
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
*/
int* nextGreaterElements(int* nums, int numsSize, int* returnSize)
{
	if (nums == NULL || numsSize <= 0) {
		*returnSize = 0;
		return NULL;
	}

	int *res = (int *)calloc(numsSize, sizeof(int));
	memset(res, -1, sizeof(int) * numsSize);

	int stack[2 * numsSize];//idx
	int top = -1;

	for (int i = 0; i < 2 * numsSize; i++) {
		int idx = i % numsSize;
		while(top >= 0 && nums[stack[top]] < nums[idx]) {
			res[stack[top--]] = nums[idx];
		}

		stack[++top] = idx;
	}

	*returnSize = numsSize;
	return res;
}


/*
1081. 不同字符的最小子序列
难度中等33
返回字符串 text 中按字典序排列最小的子序列，该子序列包
含 text 中所有不同字符一次。

示例 1：
输入："cdadabcc"
输出："adbc"
示例 2：
输入："abcd"
输出："abcd"
*/
char * smallestSubsequence(char * text)
{
	// 处理特殊情况
	if (text == NULL || strlen(text) == 0) {
		return "";
	}

	if (strlen(text) == 1) {
		return text;
	}

	int slen = strlen(text);
	int mask[26];
	memset(mask, 0, sizeof(mask));

	for (int i = 0; i < slen; i++) {
		mask[text[i] - 'a']++;
	}

	char *stack = (char *)calloc(slen * 2, sizeof(char));
	int top = -1;

	for (int i = 0; i < slen; i++) {
	/*
		如果当前字符存在于stack中，跳过，对应频次减一，
		遍历下一个字符
	*/
		if (isInQueue(stack, top, text[i])) {
			mask[text[i] - 'a']--;
			continue;
        	}
/*
	如果当前字符不存在于stack中，
	则跳过所有比它大(此时不可能相等)、
	后面还会出现的栈顶元素，然后入栈，
	遍历下一个字符
*/
            while (top > -1 && stack[top] > text[i] && mask[stack[top] - 'a'] > 1) {
                mask[stack[top] - 'a']--;   // 跳过要求频次减一，栈顶下移一位
                top--;
            }

		stack[++top] = text[i];
	}

	return stack;
}

/*
300. 最长上升子序列
难度中等812
给定一个无序的整数数组，找到其中最长上升子序列的长度。
示例:
输入: [10,9,2,5,3,7,101,18]
输出: 4
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
说明:
"	可能会有多种最长上升子序列的组合，你只需要输出对
应的长度即可。
"	你算法的时间复杂度应该为 O(n2) 。
进阶:

*/
int lengthOfLIS(int* nums, int numsSize)
{
	if(numsSize==0)
		return 0;

	int stack[numsSize],i=0;
	int top = -1;
	int j;

	stack[++top]=nums[0];
	for(i = 1;i < numsSize; i++) {
		if(nums[i] > stack[top])//大于栈顶元素，入栈
			stack[++top]=nums[i];
		else {//小于栈顶元素
			for(j=0;j <= top;j++) {
				if(nums[i] <= stack[j]) {//从底部开始修改，保持递增
					stack[j] = nums[i];
					break;
				}
			}
		}
	}

	return top + 1;
}

int lengthOfLIS(int* nums, int numsSize){
    if(numsSize==0)
    return 0;
    int stack[numsSize],i=0,top=0,j;
    int low,high,mid;
    stack[top++]=nums[0];
    for(i=1;i<numsSize;i++)
        {
            if(nums[i]>stack[top-1])//大于栈顶元素，入栈
            stack[top++]=nums[i];
            else
            {//小于栈顶元素
                low=0;
                high=top-1;
                while(high>=low)
                {
                    mid=(low+high)/2;
                    if(stack[mid]>=nums[i])
                    high=mid-1;
                    else
                    low=mid+1;
                }
                stack[high+1]=nums[i];
            }
        }
    return top;
}

int lengthOfLIS(int* nums, int numsSize)
{
	if(numsSize==0)
		return 0;
	int stack[numsSize],i=0,top=0,j;
	int low,high,mid;
	stack[top++]=nums[0];
	for(i = 1;i<numsSize;i++) {
		if(nums[i]>stack[top-1])//大于栈顶元素，入栈
			stack[top++]=nums[i];
		else {//小于栈顶元素
			low=0;
			high=top-1;
			while(high>=low) {
				mid=(low+high)/2;
				if(stack[mid]>=nums[i])
					high=mid-1;
				else
					low=mid+1;
			}
			stack[high+1]=nums[i];
		}
	}
	return top;
}

/*
84. 柱状图中最大的矩形
难度困难836
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。


以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。


图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。

示例:
输入: [2,1,5,6,2,3]
输出: 10

*/

int largestRectangleArea(int* heights, int heightsSize){
        int ans = 0;
        // 枚举左边界
        for (int left = 0; left < heightsSize; ++left) {
            int minHeight = INT_MAX;
            // 枚举右边界
            for (int right = left; right < heightsSize; ++right) {
                // 确定高度
                minHeight = fmin(minHeight, heights[right]);
                // 计算面积
                ans = fmax(ans, (right - left + 1) * minHeight);
            }
        }
        return ans;
}

int largestRectangleArea(int* heights, int heightsSize)
{
        int n = heightsSize;
        int ans = 0;
        for (int mid = 0; mid < n; ++mid) {
            // 枚举高
            int height = heights[mid];
            int left = mid, right = mid;
            // 确定左右边界
            while (left - 1 >= 0 && heights[left - 1] >= height) {
                --left;
            }
            while (right + 1 < n && heights[right + 1] >= height) {
                ++right;
            }
            // 计算面积
            ans = fmax(ans, (right - left + 1) * height);
        }
        return ans;
}

int largestRectangleArea(int* heights, int heightsSize)
{
        // 这里为了代码简便，在柱体数组的头和尾加了两个高度为 0 的柱体。
        int tmp[heightsSize + 2];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < heightsSize; i++) {
		tmp[i + 1] = heights[i];
	}

        //Deque<Integer> stack = new ArrayDeque<>();
	int stack[heightsSize + 2];
	int top = -1;
        int area = 0;
        for (int i = 0; i < heightsSize + 2; i++) {
            // 对栈中柱体来说，栈中的下一个柱体就是其「左边第一个小于自身的柱体」；
            // 若当前柱体 i 的高度小于栈顶柱体的高度，说明 i 是栈顶柱体的「右边第一个小于栈顶柱体的柱体」。
            // 因此以栈顶柱体为高的矩形的左右宽度边界就确定了，可以计算面积??? ～
            while (top > -1 && tmp[i] < tmp[stack[top]]) {
                int h = tmp[stack[top--]];
                area = fmax(area, (i - stack[top] - 1) * h);
            }
	     stack[++top] = i;
        }

        return area;
}

/*
85. 最大矩形
给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。

示例:

输入:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
输出: 6
*/
int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
    if (matrixSize == 0) {
        return 0;
    }
    //保存以当前数字结尾的连续 1 的个数
    int width[matrixSize][*matrixColSize];
	memset(width, 0, sizeof(width));
    int maxArea = 0;
    //遍历每一行
    for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < *matrixColSize; col++) {
            //更新 width
            if (matrix[row][col] == '1') {
                if (col == 0) {
                    width[row][col] = 1;
                } else {
                    width[row][col] = width[row][col - 1] + 1;
                }
            } else {
                width[row][col] = 0;
            }
            //记录所有行中最小的数
            int minWidth = width[row][col];
            //向上扩展行
            for (int up_row = row; up_row >= 0; up_row--) {
                int height = row - up_row + 1;
                //找最小的数作为矩阵的宽
                minWidth = fmin(minWidth, width[up_row][col]);
                //更新面积
                maxArea = fmax(maxArea, height * minWidth);
            }
        }
    }
    return maxArea;
}

int largestRectangleArea(int* heights, int heightsSize)
{
        // 这里为了代码简便，在柱体数组的头和尾加了两个高度为 0 的柱体。
        int tmp[heightsSize + 2];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < heightsSize; i++) {
		tmp[i + 1] = heights[i];
	}

        //Deque<Integer> stack = new ArrayDeque<>();
	int stack[heightsSize + 2];
	int top = -1;
        int area = 0;
        for (int i = 0; i < heightsSize + 2; i++) {
            // 对栈中柱体来说，栈中的下一个柱体就是其「左边第一个小于自身的柱体」；
            // 若当前柱体 i 的高度小于栈顶柱体的高度，说明 i 是栈顶柱体的「右边第一个小于栈顶柱体的柱体」。
            // 因此以栈顶柱体为高的矩形的左右宽度边界就确定了，可以计算面积??? ～
            while (top > -1 && tmp[i] < tmp[stack[top]]) {
                int h = tmp[stack[top--]];
                area = fmax(area, (i - stack[top] - 1) * h);
            }
	     stack[++top] = i;
        }

        return area;
}


int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
    if (matrixSize == 0) {
        return 0;
    }
    int heights[*matrixColSize];
	memset(heights, 0, sizeof(heights));
    int maxArea = 0;
    for (int row = 0; row < matrixSize; row++) {
        //遍历每一列，更新高度
        for (int col = 0; col < *matrixColSize; col++) {
            if (matrix[row][col] == '1') {
                heights[col] += 1;
            } else {
                heights[col] = 0;
            }
        }
        //调用上一题的解法，更新函数
        maxArea = fmax(maxArea, largestRectangleArea(heights, *matrixColSize));
    }
    return maxArea;
}

int largestRectangleArea(int* heights, int heightsSize)
{
        // 这里为了代码简便，在柱体数组的头和尾加了两个高度为 0 的柱体。
        int tmp[heightsSize + 2];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < heightsSize; i++) {
		tmp[i + 1] = heights[i];
	}

        //Deque<Integer> stack = new ArrayDeque<>();
	int stack[heightsSize + 2];
	int top = -1;
        int area = 0;
        for (int i = 0; i < heightsSize + 2; i++) {
            // 对栈中柱体来说，栈中的下一个柱体就是其「左边第一个小于自身的柱体」；
            // 若当前柱体 i 的高度小于栈顶柱体的高度，说明 i 是栈顶柱体的「右边第一个小于栈顶柱体的柱体」。
            // 因此以栈顶柱体为高的矩形的左右宽度边界就确定了，可以计算面积??? ～
            while (top > -1 && tmp[i] < tmp[stack[top]]) {
                int h = tmp[stack[top--]];
                area = fmax(area, (i - stack[top] - 1) * h);
            }
	     stack[++top] = i;
        }

        return area;
}


int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
    if (matrixSize == 0) {
        return 0;
    }

    int heights[*matrixColSize + 1];//小技巧后边讲
	memset(heights, 0, sizeof(heights));
	int maxArea = 0;
    for (int row = 0; row < matrixSize; row++) {
        int stack[*matrixColSize + 1];
		int top = -1;
        heights[*matrixColSize] = 0;
        //每求一个高度就进行栈的操作
        for (int col = 0; col <= *matrixColSize; col++) {
            if (col < *matrixColSize) { //多申请了 1 个元素，所以要判断
                if (matrix[row][col] == '1') {
                    heights[col] += 1;
                } else {
                    heights[col] = 0;
                }
            }
            if (top == -1 || heights[col] >= heights[stack[top]]) {
                stack[++top] = col;
            } else {
                //每次要判断新的栈顶是否高于当前元素
                while (top > -1 && heights[col] < heights[stack[top]]) {
                    int height = heights[stack[top--]];
                    int leftLessMin = top == -1 ? -1 : stack[top];
                    int RightLessMin = col;
                    int area = (RightLessMin - leftLessMin - 1) * height;
                    maxArea = fmax(area, maxArea);
                }
                stack[++top] = col;
            }
        }

    }
    return maxArea;
}

/*
32. 最长有效括号
难度困难897
给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
示例 1:
输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"
示例 2:
输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"

*/

int longestValidParentheses(char* s) {
    int maxans = 0, n = strlen(s);
    int stk[n + 1], top = -1;
    stk[++top] = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stk[++top] = i;
        } else {
            --top;
            if (top == -1) {
                stk[++top] = i;
            } else {
                maxans = fmax(maxans, i - stk[top]);
            }
        }
    }
    return maxans;
}

/* 42. 接雨水 */
int trap(int* height, int heightSize)
{
	if (height == NULL || heightSize <= 0)
		return 0;

	int ans = 0, current = 0;
	int stackSize = fmax(heightSize, 1024);
	int stack[stackSize];
	int top = -1;

	while (current < heightSize) {
		while (top > -1 && height[current] > height[stack[top]]) {
			int low = stack[top--];
			if (top < 0)
				break;
			int distance = current - stack[top] - 1;
			int bounded_height = fmin(height[current], height[stack[top]]) - height[low];
			ans += distance * bounded_height;
		}

		stack[++top] = current++;
	}

	return ans;
}

