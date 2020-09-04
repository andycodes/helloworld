#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

/**
241. Ϊ������ʽ������ȼ�
����һ���������ֺ���������ַ�����
Ϊ���ʽ������ţ��ı����������ȼ��������ͬ
�Ľ��������Ҫ�������п��ܵ���ϵĽ����
��Ч��������Ű��� +, - �Լ� * ��

ʾ�� 1:

����: "2-1-1"
���: [0, 2]
����:
((2-1)-1) = 0
(2-(1-1)) = 2

*/
int GetNum(char* input, int begin, int end)
{
	int i;
	int num = 0;

	for (i = begin; i <= end; i++) {
		num = num * 10 + input[i] - '0';
	}

	return num;
}


int* CalNum(char* input, int begin, int end, int*returnSize)
{
	int i;
	int m, n;
	int* res = NULL;
	int* leftOut = NULL;
	int* rightOut = NULL;
	int leftNumSize = 0;
	int rightNumSize = 0;
	bool isdigit = true;
	int result = 0;

	res = (int*)malloc(sizeof(int) * 2000);
	*returnSize = 0;

	for (i = begin; i <= end; i++) {
		if (ispunct(input[i])) {
			leftOut = CalNum(input, begin, i - 1, &leftNumSize);
			rightOut = CalNum(input, i + 1, end, &rightNumSize);

			for (m = 0; m < leftNumSize; m++) {
				for (n = 0; n < rightNumSize; n++) {
					switch (input[i]) {
						case '+':
						result = leftOut[m] + rightOut[n];
						break;
						case '-':
						result = leftOut[m] - rightOut[n];
						break;
						case '*':
						result = leftOut[m] * rightOut[n];
						break;
						default:
						break;
					}

					res[*returnSize] = result;
					(*returnSize)++;
				}
			}

			free(leftOut);
			free(rightOut);
			leftOut = NULL;
			rightOut = NULL;

			isdigit = false;
		}
	}

	if (isdigit) {//�ַ���û�з���λ����������
		res[*returnSize] = GetNum(input, begin, end);
		(*returnSize)++;
	}
	return res;
}

int* diffWaysToCompute(char* input, int* returnSize)
{
	*returnSize = 0;
	return CalNum(input, 0, strlen(input) - 1, returnSize);
}


/*
932. Ư������
����ĳЩ�̶��� N��������� A ������ 1, 2, ..., N ��ɵ����У�
ʹ�ã�
����ÿ�� i < j���������� k ���� i < k < j ʹ�� A[k] * 2 = A[i] + A[j]��
��ô���� A ��Ư�����顣
���� N����������Ư������ A����֤����һ������
ʾ�� 1��
���룺4
�����[2,1,4,3]

*/
/*
Ư�����������µ�����:

��1��A��һ��Ư�����飬
�����A������Ԫ�����һ��������
��ô������һ��Ư�����顣

��2��A��һ��Ư�����飬
�����A������Ԫ�س���һ��������
��ôA����һ��Ư�����顣

��3��A��һ��Ư�����飬���ɾ��һЩA������Ԫ�أ�
��ôA����һ��Ư�����顣

��4) A��һ���������ɵ�Ư�����飬
B��һ��ż�����ɵ�Ư�����飬��ôA+BҲ��һ��Ư������
����:{1,5,3,7}+{2,6,4,8}={1,5,3,7,2,6,4,8}Ҳ��һ��Ư�����顣

�������Ǽ���һ��{1-m}��������Ư�����飬
����ͨ������ķ�ʽ����Ư������{1-2m}:

��{1-m}�����е�������2-1��
����һ������Ư������A����{1,3,2,4},���Եõ�{1,5,3,7}
��{1-m}�����е�������2,
����һ��ż��Ư������B,��{1,3,2,4}, ���Եõ�{2,6,4,8}
A+B������{1-2m}��Ư�����顣{1,5,3,7}+{2,6,4,8}={1,5,3,7,2,6,4,8}
����ɾ����Ҫ�����ּ��ɡ�

������ȷһ�£����һ������X��Ư������
"	��ô2X(ÿ��Ԫ�س���2)��Ҳ��Ư������
"	��ô2X-1(ÿ��Ԫ�س���2����һ)��Ҳ��Ư������

��������������ΪƯ�����飺

ÿ�� i < j���������� k ���� i < k < j ʹ�� A[k] * 2 = A[i] + A[j]
��������+ż�� = ����
2* [������ż��] = ż��
��ˣ�������ż���ֿ����ֳ������֣�
��ô�������־����������������������ΪX��ż������ΪY
Ȼ���X���в�֣���X������λ�����ƶ�һλ��Ȼ������ż
��Y���в�֣���Y������λ�����ƶ�һλ��Ȼ������żs
*/

int* GetBeautifulArray(int num, int** saveArray, int* size)
{
    int* outArray = NULL;
    int* leftArray = NULL;
    int* rightArray = NULL;
    int leftSize = 0;
    int rightSize = 0;
    int i;

    if (saveArray[num] != NULL) {
        *size = num;
        return saveArray[num];
    }

    if (num == 1) {
        outArray = (int*)malloc(sizeof(int));
        outArray[0] = 1;
        *size = 1;
        saveArray[num] = outArray;
        return outArray;
    }

    leftArray = GetBeautifulArray((num + 1) / 2, saveArray, &leftSize);
    rightArray = GetBeautifulArray(num / 2, saveArray, &rightSize);

    *size = leftSize + rightSize;
    outArray = (int*)malloc(sizeof(int) * (*size));
    for (i = 0; i < leftSize; i++) {
        outArray[i] = leftArray[i] * 2 - 1;
    }
    for (i = 0; i < rightSize; i++) {
        outArray[i + leftSize] = rightArray[i] * 2;
    }

    saveArray[num] = outArray;

    return outArray;
}


/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int* beautifulArray(int N, int* returnSize)
{
    int* outArray = NULL;
    int i;
    int** saveArray = (int**)malloc(sizeof(int*) * (N + 1));

    (void)memset(saveArray, 0, sizeof(int*) * (N + 1));
    outArray = GetBeautifulArray(N, saveArray, returnSize);
    for (i = 0; i < N; i++) {
        if (saveArray[i] != NULL) {
            free(saveArray[i]);
        }
    }
    free(saveArray);
    return outArray;
}

/*
50. Pow(x, n)
�Ѷ��е�390�ղط����л�ΪӢ�Ĺ�ע����
ʵ�� pow(x, n) �������� x �� n ���ݺ�����
ʾ�� 1:
����: 2.00000, 10
���: 1024.00000
ʾ�� 2:
����: 2.10000, 3
���: 9.26100
ʾ�� 3:
����: 2.00000, -2
���: 0.25000
����: 2-2 = 1/22 = 1/4 = 0.25

*/
double dfs(double x, long long N)
{
	if (n == 0) {
		return 1.0;
	}

	double y = dfs(x, N / 2);

	return N % 2 == 0 ? y * y : y * y * x;
}

double traverse(double x, long long N)
{
        double ans = 1.0;
        // ���׵ĳ�ʼֵΪ x
        double x_contribute = x;
        // �ڶ� N ���ж����Ʋ�ֵ�ͬʱ�����
        while (N > 0) {
            if (N % 2 == 1) {
                // ��� N �����Ʊ�ʾ�����λΪ 1����ô��Ҫ���빱��
                ans *= x_contribute;
            }
            // �����ײ��ϵ�ƽ��
            x_contribute *= x_contribute;
            // ���� N �����Ʊ�ʾ�����λ����������ÿ��ֻҪ�ж����λ����
            N /= 2;
        }
        return ans;
}

double myPow(double x, int n)
{
	long long N = n;
	return N >= 0 ? traverse(x, N) : 1.0 / traverse(x, -N);
}

/*
395. ������K���ظ��ַ�����Ӵ�
�Ѷ��е�152
�ҵ������ַ�������Сд�ַ���ɣ��е���Ӵ� T �� Ҫ�� T �е�ÿһ�ַ����ִ����������� k ����� T �ĳ��ȡ�
ʾ�� 1:
����:
s = "aaabb", k = 3

���:
3

��Ӵ�Ϊ "aaa" ������ 'a' �ظ��� 3 �Ρ�
ʾ�� 2:
����:
s = "ababbc", k = 2

���:
5

��Ӵ�Ϊ "ababb" ������ 'a' �ظ��� 2 �Σ� 'b' �ظ��� 3 �Ρ�

*/
/*
����˼·���ݹ����Ӵ������Ρ���ͳ�Ƴ�ÿ���ַ����ֵ�Ƶ�Σ�ά��һ��˫ָ�룬����β��ʼͳ�ƣ�����β���м��ų���������ִ���С��k�򲻿��ܳ����������Ӵ��У��ų���Ų��ָ�룬Ȼ��õ���ʱ�Ӵ������δ�ͷ������һ�����ֳ���Ƶ��С��k���ַ����Ը��ַ�Ϊ�ָ��ߣ��ֱ�ݹ��������ֵ���ء�
*/

int divide(char *s, int k, int left, int right)
{
	if (right - left + 1 < k)
		return 0;

	int mapcnt[26];
	memset(mapcnt, 0, sizeof(mapcnt));

	for (int i = left; i <= right; i++) {
		mapcnt[s[i] - 'a']++;
	}

	while(right - left + 1 >= k && mapcnt[s[left] - 'a'] < k) {
		left++;
	}

	while(right - left + 1 >= k && mapcnt[s[right] - 'a'] < k) {
		right--;
	}

	if (right - left + 1 < k)
		return 0;

	for (int i = left; i <= right; i++) {
		if (mapcnt[s[i] - 'a'] < k) {
			return fmax(divide(s, k, left, i - 1), divide(s, k, i + 1, right));
		}
	}

	return right - left + 1;
}

int longestSubstring(char * s, int k)
{
	int slen = strlen(s);

	if (slen == 0 || k > slen)
		return 0;

	if (k < 2)
		return slen;

	return divide(s, k, 0, slen - 1);
}
