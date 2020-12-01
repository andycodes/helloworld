
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

����'(' ֱ����ջ
����')',���ջ����'(' ˵�����Գɶԣ��Ƴ�ջ����������ջ
�𰸾����ַ����Ƴ�ջ�з��š�
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
					top--;//�ܹ��ɶԣ��Ӷ������޳�
				} else {//��¼��Ҫɾ����
					stack[++top][0] = s[i];
					stack[top][1] = i;
				}
			} else {//��¼��Ҫɾ����
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
394. �ַ�������
����һ������������ַ������������������ַ�����
�������Ϊ: k[encoded_string]����ʾ���з������ڲ���
encoded_string �����ظ� k �Ρ�ע�� k ��֤Ϊ��������
�������Ϊ�����ַ���������Ч�ģ������ַ�����û��
����Ŀո�������ķ��������Ƿ��ϸ�ʽҪ��ġ�
���⣬�������Ϊԭʼ���ݲ��������֣����е�����
ֻ��ʾ�ظ��Ĵ��� k �����粻������� 3a �� 2[4] �����롣
ʾ��:
s = "3[a]2[bc]", ���� "aaabcbc".
s = "3[a2[c]]", ���� "accaccacc".
s = "2[abc]3[cd]ef", ���� "abcabccdcdcdef".
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
			strcpy(tmp, stackStr[topstr--]);//��ʷǰ׺

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
1081. ��ͬ�ַ�����С������
�Ѷ��е�33
�����ַ��� text �а��ֵ���������С�������У��������а�
�� text �����в�ͬ�ַ�һ�Ρ�
ʾ�� 1��
���룺"cdadabcc"
�����"adbc"
ʾ�� 2��
���룺"abcd"
�����"abcd"
*/
char * smallestSubsequence(char * text)
{
	// �����������
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
		�����ǰ�ַ�������stack�У���������ӦƵ�μ�һ��
		������һ���ַ�
	*/
		if (isInQueue(stack, top, text[i])) {
			mask[text[i] - 'a']--;
			continue;
        	}
/*
	�����ǰ�ַ���������stack�У�
	���������б�����(��ʱ���������)��
	���滹����ֵ�ջ��Ԫ�أ�Ȼ����ջ��
	������һ���ַ�
*/
            while (top > -1 && stack[top] > text[i] && mask[stack[top] - 'a'] > 1) {
                mask[stack[top] - 'a']--;   // ����Ҫ��Ƶ�μ�һ��ջ������һλ
                top--;
            }

		stack[++top] = text[i];
	}

	return stack;
}


/*
300. �����������
�Ѷ��е�812
����һ��������������飬�ҵ���������������еĳ��ȡ�
ʾ��:
����: [10,9,2,5,3,7,101,18]
���: 4
����: ��������������� [2,3,7,101]�����ĳ����� 4��
˵��:
"	���ܻ��ж�������������е���ϣ���ֻ��Ҫ�����
Ӧ�ĳ��ȼ��ɡ�
"	���㷨��ʱ�临�Ӷ�Ӧ��Ϊ O(n2) ��
����:

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
		if(nums[i] > stack[top])//����ջ��Ԫ�أ���ջ
			stack[++top]=nums[i];
		else {//С��ջ��Ԫ��
			for(j=0;j <= top;j++) {
				if(nums[i] <= stack[j]) {//�ӵײ���ʼ�޸ģ����ֵ���
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
            if(nums[i]>stack[top-1])//����ջ��Ԫ�أ���ջ
            stack[top++]=nums[i];
            else
            {//С��ջ��Ԫ��
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
84. ��״ͼ�����ľ���
�Ѷ�����836
���� n ���Ǹ�������������ʾ��״ͼ�и������ӵĸ߶ȡ�
ÿ�����ӱ˴����ڣ��ҿ��Ϊ 1 ��
���ڸ���״ͼ�У��ܹ����ճ����ľ��ε���������
��������״ͼ��ʾ��������ÿ�����ӵĿ��Ϊ 1�������ĸ�
��Ϊ [2,1,5,6,2,3]��
ͼ����Ӱ����Ϊ���ܹ��ճ��������������
�����Ϊ 10 ����λ��
ʾ��:
����: [2,1,5,6,2,3]
���: 10
*/
int largestRectangleArea(int* heights, int heightsSize)
{
/*
����Ϊ�˴����㣬�����������ͷ��β���������߶�Ϊ
0 �����塣
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
��ջ��������˵��ջ�е���һ����������䡸��ߵ�һ��С
����������塹��
����ǰ���� i �ĸ߶�С��ջ������ĸ߶ȣ�˵�� i ��ջ������
�ġ��ұߵ�һ��С��ջ����������塹��
�����ջ������Ϊ�ߵľ��ε����ҿ�ȱ߽��ȷ���ˣ�
���Լ������
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
85. ������
����һ�������� 0 �� 1 �Ķ�ά�����ƾ����ҳ�ֻ���� 1 ��
�����Σ��������������
ʾ��:
����:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
���: 6
*/
int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
	if (matrixSize == 0) {
		return 0;
	}

	int heights[*matrixColSize + 1];//С���ɺ�߽�
	memset(heights, 0, sizeof(heights));
	int maxArea = 0;

	for (int row = 0; row < matrixSize; row++) {
		int stack[*matrixColSize + 1];
		int top = -1;
		heights[*matrixColSize] = 0;
		//ÿ��һ���߶Ⱦͽ���ջ�Ĳ���
		for (int col = 0; col <= *matrixColSize; col++) {
			if (col < *matrixColSize) { //�������� 1 ��Ԫ�أ�����Ҫ�ж�
				if (matrix[row][col] == '1') {
					heights[col] += 1;
				} else {
					heights[col] = 0;
				}
			}

			if (top == -1 || heights[col] >= heights[stack[top]]) {
				stack[++top] = col;
			} else {
				//ÿ��Ҫ�ж��µ�ջ���Ƿ���ڵ�ǰԪ��
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
32. ���Ч����
�Ѷ�����897
����һ��ֻ���� '(' �� ')' ���ַ������ҳ���İ�����Ч����
���Ӵ��ĳ��ȡ�
ʾ�� 1:
����: "(()"
���: 2
����: ���Ч�����Ӵ�Ϊ "()"
ʾ�� 2:
����: ")()())"
���: 4
����: ���Ч�����Ӵ�Ϊ "()()"
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

/* 42. ����ˮ */
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
735. ������ײ
����һ���������� asteroids����ʾ��ͬһ�е����ǡ�
���������е�ÿһ��Ԫ�أ������ֵ��ʾ���ǵĴ�С������
��ʾ���ǵ��ƶ���������ʾ�����ƶ�������ʾ�����ƶ�����
ÿһ����������ͬ���ٶ��ƶ���
�ҳ���ײ��ʣ�µ��������ǡ���ײ�������������໥��ײ��
��С�����ǻᱬը������������Ǵ�С��ͬ�����������Ƕ�
�ᱬը�������ƶ�������ͬ�����ǣ���Զ���ᷢ����ײ��
ʾ�� 1:
����:
asteroids = [5, 10, -5]
���: [5, 10]
����:
10 �� -5 ��ײ��ֻʣ�� 10�� 5 �� 10 ��Զ���ᷢ����ײ��
ʾ�� 2:
����:
asteroids = [8, -8]
���: []
����:
8 �� -8 ��ײ�����߶�������ը��
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
1003. ����滻��Ĵ��Ƿ���Ч
������Ч�ַ��� "abc"��

�����κ���Ч���ַ��� V�����ǿ��Խ� V �ֳ��������� X �� Y��ʹ�� X + Y��X �� Y ���ӣ����� V����X �� Y ����Ϊ�ա�����ô��X + "abc" + Y Ҳͬ������Ч�ġ�

���磬��� S = "abc"������Ч�ַ�����ʾ���ǣ�"abc"��"aabcbc"��"abcabc"��"abcabcababcc"����Ч�ַ�����ʾ���ǣ�"abccba"��"ab"��"cababc"��"bac"��

��������ַ��� S ��Ч���򷵻� true�����򣬷��� false��



ʾ�� 1��

���룺"aabcbc"
�����true
���ͣ�
����Ч�ַ��� "abc" ��ʼ��
Ȼ�����ǿ����� "a" �� "bc" ֮�������һ�� "abc"������ "a" + "abc" + "bc"���� "aabcbc"��
ʾ�� 2��

���룺"abcabcababcc"
�����true
���ͣ�
"abcabcabc" ����Ч�ģ�������������ԭ������������ "abc"��
Ȼ�����ǿ��������һ����ĸ֮ǰ���� "abc"������ "abcabcab" + "abc" + "c"���� "abcabcababcc"��
*/

/*

ģʽʶ��

1��ջ
2���ݹ�
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

