#include <stdio.h>

/************************************************************************/
/* ���ܣ�ʵ���������β���ֵ����
/* ������
/*       lhs--int���͵�ָ�룬ָ���������1�ĵ�ַ
/*       rhs--int���͵�ָ�룬ָ���������2�ĵ�ַ
/************************************************************************/
void Swap(int *lhs, int *rhs)
{
	int t = *lhs;

	*lhs = *rhs;
	*rhs = t;
}

/************************************************************************/
/* ���ܣ�ʵ��ȫ���й���
/* ������
/*       source--�������飬�����Ҫȫ���е�Ԫ��
/*       begin --����һ�����еĿ�ʼλ��
/*       end   --����һ�����еĽ���λ�ã���begin=endʱ���������һ������
/************************************************************************/
void numbers_FullPermutation(int source[], int begin, int end)
{
	int i;

	if (begin >= end) // �ҵ�һ������
	{
		for (i = 0; i < end; i++)
		{
			printf("%d", source[i]);
		}
		printf("\n");
	}
	else// û������һ�����У��������������һ��Ԫ��
	{
		for (i = begin; i < end; i++)
		{
			if (begin != i)
			{
				Swap(&source[begin], &source[i]); // ����
			}

			// �ݹ�����ʣ��Ĵ�begin+1��end��Ԫ��
			numbers_FullPermutation(source, begin + 1, end);

			if (begin != i)
			{
				Swap(&source[begin], &source[i]); // ����ʱ��ԭ
			}
		}
	}
}

int test_numbers_FullPermutation(void)
{
	int source[30];
	int i, count;

	scanf("%d", &count);

	// ��ʼ������
	for (i = 0; i < count; i++)
	{
		source[i] = i + 1;
	}

	numbers_FullPermutation(source, 0, count);

	return 0;
}

char **result;
char out[10240][10240];
int j = 0;
void dfs(char * S, int i)
{
	if(i == strlen(S)) {
		strcpy(out[j++],S);
		return;
	}

	dfs(S,i+1);

	if(S[i] < '0' || S[i] > '9'){
		S[i] ^= (1<<5);
		dfs(S,i+1);
	}
}



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCasePermutation(char * S, int* returnSize){
	int i;
	j = 0;
	memset((void*)out,'\0',sizeof(out));
	dfs(S,0);
	*returnSize = j;
	result = (char**)malloc(j* sizeof(char *));

	for(i = 0; i<j;i++){
		result[i] = (char*)malloc(10240);
		strcpy(result[i],out[i]);
	}

	return result;
}

