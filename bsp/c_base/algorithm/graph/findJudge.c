#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
���ٲ������κ���
����Ҫ��N-1��������
ֻ��һ�����Ǳ�N-1������
ֻ��һ������
*/
int findJudge(int N, int** trust, int trustSize, int* trustColSize){
    int *ret_val = (int *)calloc(N+2, sizeof(int));
    for (int i = 0; i < N+1; ++i)         ret_val[i] = 0;

	//��¼�����ŵĴ���
    for (int i = 0; i < trustSize; ++i) ++ret_val[trust[i][1]];

	//��������ű��ˣ��ͶԱ����ŵĴ�������
    for (int i = 0; i < trustSize; ++i)   ret_val[trust[i][0]] = 0;

    int num = 0;
    int top = -1;
    for (int i = 1; i <= N; ++i) {
        if (ret_val[i] == N-1) {  //�������Ŵ���ΪN-1����
            ++num;
            top = i;//��¼�±�
        }
    }

//����д���1�����٣���Ϊ-1�������Ϊ���±�
    return (num > 1 ? -1 : top);
}



int main()
{
}

