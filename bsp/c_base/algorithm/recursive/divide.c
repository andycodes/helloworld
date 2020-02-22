#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

/**
241. 为运算表达式设计优先级
给定一个含有数字和运算符的字符串，
为表达式添加括号，改变其运算优先级以求出不同
的结果。你需要给出所有可能的组合的结果。
有效的运算符号包含 +, - 以及 * 。

示例 1:

输入: "2-1-1"
输出: [0, 2]
解释:
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
932. 漂亮数组
对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，
使得：

对于每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]。

那么数组 A 是漂亮数组。



给定 N，返回任意漂亮数组 A（保证存在一个）。



示例 1：

输入：4
输出：[2,1,4,3]

*/
/*
漂亮数组有以下的性质:

（1）A是一个漂亮数组，
如果对A中所有元素添加一个常数，
那么Ａ还是一个漂亮数组。

（2）A是一个漂亮数组，
如果对A中所有元素乘以一个常数，
那么A还是一个漂亮数组。

（3）A是一个漂亮数组，如果删除一些A中所有元素，
那么A还是一个漂亮数组。

（4) A是一个奇数构成的漂亮数组，
B是一个偶数构成的漂亮数组，那么A+B也是一个漂亮数组
比如:{1,5,3,7}+{2,6,4,8}={1,5,3,7,2,6,4,8}也是一个漂亮数组。

所以我们假设一个{1-m}的数组是漂亮数组，
可以通过下面的方式构造漂亮数组{1-2m}:

对{1-m}中所有的数乘以2-1，
构成一个奇数漂亮数组A。如{1,3,2,4},可以得到{1,5,3,7}
对{1-m}中所有的数乘以2,
构成一个偶数漂亮数组B,如{1,3,2,4}, 可以得到{2,6,4,8}
A+B构成了{1-2m}的漂亮数组。{1,5,3,7}+{2,6,4,8}={1,5,3,7,2,6,4,8}
从中删除不要的数字即可。

首先明确一下，如果一个数组X是漂亮数组
"	那么2X(每个元素乘以2)，也是漂亮数组
"	那么2X-1(每个元素乘以2，减一)，也是漂亮数组

满足下面条件的为漂亮数组：

每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]
由于奇数+偶数 = 奇数
2* [奇数或偶数] = 偶数
因此，首先奇偶数分开，分成两部分，那么这两部分就满足这个条件，奇数部分为X，偶数部分为Y

然后对X进行拆分，将X的所有位向右移动一位，然后拆分奇偶

对Y进行拆分，将Y的所有位向右移动一位，然后拆分奇偶

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