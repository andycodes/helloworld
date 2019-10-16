#include <stdio.h>

/************************************************************************/
/* 功能：实现两个整形参数值交换
/* 参数：
/*       lhs--int类型的指针，指向待交换数1的地址
/*       rhs--int类型的指针，指向待交换数2的地址
/************************************************************************/
void Swap(int *lhs, int *rhs)
{
	int t = *lhs;

	*lhs = *rhs;
	*rhs = t;
}

/************************************************************************/
/* 功能：实现全排列功能
/* 参数：
/*       source--整数数组，存放需要全排列的元素
/*       begin --查找一个排列的开始位置
/*       end   --查找一个排列的结束位置，当begin=end时，表明完成一个排列
/************************************************************************/
void numbers_FullPermutation(int source[], int begin, int end)
{
	int i;

	if (begin >= end) // 找到一个排列
	{
		for (i = 0; i < end; i++)
		{
			printf("%d", source[i]);
		}
		printf("\n");
	}
	else// 没有找完一个排列，则继续往下找下一个元素
	{
		for (i = begin; i < end; i++)
		{
			if (begin != i)
			{
				Swap(&source[begin], &source[i]); // 交换
			}

			// 递归排列剩余的从begin+1到end的元素
			numbers_FullPermutation(source, begin + 1, end);

			if (begin != i)
			{
				Swap(&source[begin], &source[i]); // 回溯时还原
			}
		}
	}
}

int test_numbers_FullPermutation(void)
{
	int source[30];
	int i, count;

	scanf("%d", &count);

	// 初始化数组
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

