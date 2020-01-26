#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


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