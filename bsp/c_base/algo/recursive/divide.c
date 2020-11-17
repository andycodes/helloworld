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

/*
312. ������
�� n �����򣬱��Ϊ0 �� n-1��ÿ�������϶�����һ�����֣���Щ���ִ������� nums �С�

����Ҫ����������е����������������� i ���Ϳ��Ի�� nums[left] * nums[i] * nums[right] ��Ӳ�ҡ� ����� left �� right ����� i ���ڵ������������š�ע�⵱����������� i ������ left ������ right �ͱ�������ڵ�����

�����ܻ��Ӳ�ҵ����������

˵��:

����Լ��� nums[-1] = nums[n] = 1����ע�����ǲ�����ʵ���ڵ����Բ����ܱ����ơ�
0 �� n �� 500, 0 �� nums[i] �� 100
ʾ��:

����: [3,1,5,8]
���: 167
����: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
     coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/
int rec[502][502];
int val[502];
int solve(int left, int right) {
    if (left >= right - 1) {
        return 0;
    }
    if (rec[left][right] != -1) {
        return rec[left][right];
    }
    for (int i = left + 1; i < right; i++) {
        int sum = val[left] * val[i] * val[right];
        sum += solve(left, i) + solve(i, right);
        rec[left][right] = fmax(rec[left][right], sum);
    }
    return rec[left][right];
}

int maxCoins(int* nums, int numsSize) {
    memset(rec, -1, sizeof(rec));
    val[0] = val[numsSize + 1] = 1;
    for (int i = 1; i <= numsSize; i++) {
        val[i] = nums[i - 1];
    }

    return solve(0, numsSize + 1);
}

/*
327. ����͵ĸ���
����һ���������� nums������������� [lower, upper] ֮��ĸ��������� lower �� upper��
����� S(i, j) ��ʾ�� nums �У�λ�ô� i �� j ��Ԫ��֮�ͣ����� i �� j (i �� j)��

˵��:
��ֱ�۵��㷨���Ӷ��� O(n2) �����ڴ˻������Ż�����㷨��

ʾ��:

����: nums = [-2,5,-1], lower = -2, upper = 2,
���: 3
����: 3������ֱ���: [0,0], [2,2], [0,2]�����Ǳ�ʾ�ĺͷֱ�Ϊ: -2, -1, 2��
*/

int countRangeSum(int* nums, int numsSize, int lower, int upper){
    long sum;
    int count;
    int i, j;
    if (numsSize == 1) {
        if ((nums[0] >= lower) && (nums[0] <= upper)) { return 1; }
        if ((nums[0] < lower) || (nums[0] > upper)) { return 0; }
    }

    count = 0;
    for (i = 0; i < numsSize; i++) {
        sum = 0;
        for (j = i; j < numsSize; j++) {
            sum += nums[j];
            if ((sum >= lower) && (sum <= upper)) {
                count++;
            }
        }
    }
    return count;
}

int countRangeSumRecursive(long long* sum, int lower, int upper, int left, int right) {
    if (left == right) {
        return 0;
    } else {
        int mid = (left + right) / 2;
        int n1 = countRangeSumRecursive(sum, lower, upper, left, mid);
        int n2 = countRangeSumRecursive(sum, lower, upper, mid + 1, right);
        int ret = n1 + n2;

        // ����ͳ���±�Ե�����
        int i = left;
        int l = mid + 1;
        int r = mid + 1;
        while (i <= mid) {
            while (l <= right && sum[l] - sum[i] < lower) l++;
            while (r <= right && sum[r] - sum[i] <= upper) r++;
            ret += (r - l);
            i++;
        }

        // ���ϲ�������������
        int sorted[right - left + 1];
        memset(sorted, 0, sizeof(sorted));
        int p1 = left, p2 = mid + 1;
        int p = 0;
        while (p1 <= mid || p2 <= right) {
            if (p1 > mid) {
                sorted[p++] = sum[p2++];
            } else if (p2 > right) {
                sorted[p++] = sum[p1++];
            } else {
                if (sum[p1] < sum[p2]) {
                    sorted[p++] = sum[p1++];
                } else {
                    sorted[p++] = sum[p2++];
                }
            }
        }
        for (int i = 0; i < right - left + 1; i++) {
            sum[left + i] = sorted[i];
        }
        return ret;
    }
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long long s = 0;
    long long sum[numsSize + 1];
    sum[0] = 0;
    for (int i = 1; i <= numsSize; i++) {
        sum[i] = sum[i - 1] + nums[i - 1];
    }
    return countRangeSumRecursive(sum, lower, upper, 0, numsSize);
}

