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

int* CalNum(char* input, int begin, int end, int* num)
{
    int i;
    int m, n;
    int* out = NULL;
    int* leftOut = NULL;
    int* rightOut = NULL;
    int leftNum = 0;
    int rightNum = 0;
    bool isNum = true;
    int res = 0;

    out = (int*)malloc(sizeof(int) * 2000);
    *num = 0;

    for (i = begin; i <= end; i++) {
        //if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
           if (ispunct(input[i])) {
            leftOut = CalNum(input, begin, i - 1, &leftNum);
            rightOut = CalNum(input, i + 1, end, &rightNum);

            for (m = 0; m < leftNum; m++) {
                for (n = 0; n < rightNum; n++) {
                    switch (input[i]) {
                    case '+':
                        res = leftOut[m] + rightOut[n];
                        break;
                    case '-':
                        res = leftOut[m] - rightOut[n];
                        break;
                    case '*':
                        res = leftOut[m] * rightOut[n];
                        break;
                    default:
                        break;
                    }
                    out[*num] = res;
                    *num += 1;
                }
            }
            free(leftOut);
            free(rightOut);
            leftOut = NULL;
            rightOut = NULL;
            isNum = false;
        }
    }

    if (isNum) {
        out[*num] = GetNum(input, begin, end);
        *num += 1;
    }
    return out;
}


/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int* diffWaysToCompute(char* input, int* returnSize) {
    return CalNum(input, 0, strlen(input) - 1, returnSize);
}




int main(void) {
    char array[2][20] = {
        "2-1-1",
        "2*3-4*5"
    };

    for (int j = 0; j < 2; j++) {
        int returnSize = 0;
        int* result = NULL;
        result = diffWaysToCompute(array[j], &returnSize);
        qsort(result, returnSize, sizeof(int), cmp_int);
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }
    return 0;
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
��ˣ�������ż���ֿ����ֳ������֣���ô�������־����������������������ΪX��ż������ΪY

Ȼ���X���в�֣���X������λ�����ƶ�һλ��Ȼ������ż

��Y���в�֣���Y������λ�����ƶ�һλ��Ȼ������ż

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