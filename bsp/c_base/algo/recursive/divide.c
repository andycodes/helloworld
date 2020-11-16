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
ÿ�� i < j���������� k ���� i < k < j ʹ�� A[k] * 2 = A[i] + A[j]
��������+ż�� = ����
2* [������ż��] = ż��
��ˣ�������ż���ֿ����ֳ������֣�
��ô�������־����������������������ΪX��ż������ΪY
*/
void exec(int* arr, int size, int* tmp1, int* tmp2)
{
    int i;
    int j = 0;
    int k = 0;

    // ������鳤��С�ڵ���2 �����账��
    if (size <= 2) {
        return;
    }

    // �������飬������1 3 5 7 ����ǰ�棬��2 4 6 8...���ں���
	//��ͣ��ż�����������벿�ַ�
    for (i = 0; i < size; i++) {
        if (i % 2 == 0) {
            tmp1[j++] = arr[i];
        } else {
            tmp2[k++] = arr[i];
        }
    }

    memcpy(arr, tmp1, j * sizeof(int));
    memcpy(arr + j, tmp2, k * sizeof(int));

    // ��ǰ���1 3 5 7...�ظ��ô������
    exec(arr, j, tmp1, tmp2);

    // �Ժ����2 4 6 8...�ظ��ô������
    exec(arr + j, k, tmp1, tmp2);
}

int* beautifulArray(int N, int* returnSize)
{
    int* arr;
    int* tmp1;
    int* tmp2;
    int i;


    *returnSize = N;

    // ���ص�����
    arr = (int*)malloc(sizeof(int) * N);

    // ������ʱ�������ڴ����ʱ����
    tmp1 = (int*)malloc(sizeof(int) * N);
    tmp2 = (int*)malloc(sizeof(int) * N);

    for (i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    exec(arr, N, tmp1, tmp2);

    free(tmp1);
    free(tmp2);

    return arr;
}

/*
395. ������K���ظ��ַ�����Ӵ�
�Ѷ��е�152
�ҵ������ַ�������Сд�ַ���ɣ��е���Ӵ� T �� Ҫ��
T �е�ÿһ�ַ����ִ����������� k ����� T �ĳ��ȡ�
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
����˼·���ݹ����Ӵ������Ρ���ͳ�Ƴ�ÿ���ַ����ֵ�
Ƶ�Σ�ά��һ��˫ָ�룬����β��ʼͳ�ƣ�����β���м���
����������ִ���С��k�򲻿��ܳ����������Ӵ��У��ų���
Ų��ָ�룬Ȼ��õ���ʱ�Ӵ������δ�ͷ������һ�����ֳ�
��Ƶ��С��k���ַ����Ը��ַ�Ϊ�ָ��ߣ��ֱ�ݹ��������
ֵ���ء�
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
