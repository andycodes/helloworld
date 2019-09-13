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
void FullPermutation(int source[], int begin, int end)
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
			FullPermutation(source, begin + 1, end);

			if (begin != i)
			{
				Swap(&source[begin], &source[i]); // ����ʱ��ԭ
			}
		}
	}
}

int main()
{
	int source[30];
	int i, count;

	scanf("%d", &count);

	// ��ʼ������
	for (i = 0; i < count; i++)
	{
		source[i] = i + 1;
	}

	FullPermutation(source, 0, count);

	return 0;
}
