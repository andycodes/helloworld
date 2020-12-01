
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

int lengthOfLIS(int* nums, int numsSize)
{
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

/*
84. 柱状图中最大的矩形
难度困难836
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。
每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高
度为 [2,1,5,6,2,3]。
图中阴影部分为所能勾勒出的最大矩形面积，
其面积为 10 个单位。
示例:
输入: [2,1,5,6,2,3]
输出: 10
*/
int largestRectangleArea(int* heights, int heightsSize)
{
/*
这里为了代码简便，在柱体数组的头和尾加了两个高度为
0 的柱体。
*/
        int tmp[heightsSize + 2];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < heightsSize; i++) {
		tmp[i + 1] = heights[i];
	}

	int stack[heightsSize + 2];
	int top = -1;
        int area = 0;
        for (int i = 0; i < heightsSize + 2; i++) {
/*
对栈中柱体来说，栈中的下一个柱体就是其「左边第一个小
于自身的柱体」；
若当前柱体 i 的高度小于栈顶柱体的高度，说明 i 是栈顶柱体
的「右边第一个小于栈顶柱体的柱体」。
因此以栈顶柱体为高的矩形的左右宽度边界就确定了，
可以计算面积
*/
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
给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的
最大矩形，并返回其面积。
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
给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号
的子串的长度。
示例 1:
输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"
示例 2:
输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"
*/
int longestValidParentheses(char* s)
{
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

/*
735. 行星碰撞
给定一个整数数组 asteroids，表示在同一行的行星。
对于数组中的每一个元素，其绝对值表示行星的大小，正负
表示行星的移动方向（正表示向右移动，负表示向左移动）。
每一颗行星以相同的速度移动。
找出碰撞后剩下的所有行星。碰撞规则：两个行星相互碰撞，
较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都
会爆炸。两颗移动方向相同的行星，永远不会发生碰撞。
示例 1:
输入:
asteroids = [5, 10, -5]
输出: [5, 10]
解释:
10 和 -5 碰撞后只剩下 10。 5 和 10 永远不会发生碰撞。
示例 2:
输入:
asteroids = [8, -8]
输出: []
解释:
8 和 -8 碰撞后，两者都发生爆炸。
*/
int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize)
{
	*returnSize = 0;
	if (asteroids == NULL || asteroidsSize <= 0) {
		return NULL;
	}

	int *stack = (int *)calloc(asteroidsSize, sizeof(int));
	int top = -1;

	for (int i = 0; i < asteroidsSize; i++) {
		if (top == -1) {
			stack[++top] = asteroids[i];
		} else {
			if (stack[top] * asteroids[i] > 0) {
				stack[++top] = asteroids[i];
			} else {
				if (stack[top] < 0) {
					stack[++top] = asteroids[i];
				} else {
					if (stack[top] + asteroids[i] < 0) {
						top--;
						i--;
					} else if (stack[top] + asteroids[i] == 0) {
						top--;
					}
				}
			}
		}
	}
	*returnSize = top + 1;
	return stack;
}

/*
1003. 检查替换后的词是否有效
给定有效字符串 "abc"。

对于任何有效的字符串 V，我们可以将 V 分成两个部分 X 和 Y，使得 X + Y（X 与 Y 连接）等于 V。（X 或 Y 可以为空。）那么，X + "abc" + Y 也同样是有效的。

例如，如果 S = "abc"，则有效字符串的示例是："abc"，"aabcbc"，"abcabc"，"abcabcababcc"。无效字符串的示例是："abccba"，"ab"，"cababc"，"bac"。

如果给定字符串 S 有效，则返回 true；否则，返回 false。



示例 1：

输入："aabcbc"
输出：true
解释：
从有效字符串 "abc" 开始。
然后我们可以在 "a" 和 "bc" 之间插入另一个 "abc"，产生 "a" + "abc" + "bc"，即 "aabcbc"。
示例 2：

输入："abcabcababcc"
输出：true
解释：
"abcabcabc" 是有效的，它可以视作在原串后连续插入 "abc"。
然后我们可以在最后一个字母之前插入 "abc"，产生 "abcabcab" + "abc" + "c"，即 "abcabcababcc"。
*/

/*

模式识别：

1、栈
2、递归
*/

bool isValid(char * s){

int len = strlen(s);
char *stack = calloc(len+1, sizeof(char));

if(s[0] != 'a')
    return false;

int top = -1;
int i = 0;


    while(*(s+i) != 0)
    {
        stack[++top] = *(s+i);
        if(stack[top] == 'c')
        {
            if(top >=2 && memcmp(&stack[top-2], "abc", 3) == 0)
                top -= 3;
        }

        i++;
    }

if(top == -1)
    return true;
else
    return false;

}

