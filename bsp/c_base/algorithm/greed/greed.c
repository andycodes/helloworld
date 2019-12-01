#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
������������������⣬
��˾���Ƚ��� 2N ����ȫ�����ŷ��� B �У�
��ѡ�� N ���˸ı����ǵ��г̣������Ƿ��� A �С�
���ѡ��ı�һ���˵��г̣�
��ô��˾������⸶�� price_A - price_B �ķ��ã�
������ÿ����ɸ���


������ŵķ����ǣ�ѡ�� price_A - price_B ��С�� N ���ˣ�
�����Ƿ��� A �У������˷��� B �С�
�㷨���� price_A - price_B ��С��������
��ǰ N ���˷��� A �У������˷��� B �У�
��������ܷ��á�
*/

struct obj{
    int a;
    int b;
    int diff;
};

void bubble_sort(struct obj  *data,int size)
{
    for (int i=size;i>0;i--)
    {
        for (int j=0;j<(i-1);j++)
            {
                if (data[j].diff >data[j+1].diff)
                    {
                        struct obj  tmp;
                        tmp=data[j];
                        data[j]=data[j+1];
                        data[j+1]=tmp;
                    }
            }
       }
}



int twoCitySchedCost(int costs[][2], int costsSize, int* costsColSize){
        int i;
        struct obj ob[100];
        int sum = 0;

        for(i = 0; i < costsSize; i++){
                ob[i].a = costs[i][0];
                ob[i].b = costs[i][1];
                ob[i].diff = ob[i].a - ob[i].b;
        }

        bubble_sort(ob,costsSize);

        for (i = 0;i<costsSize/2;i++){
            sum += ob[i].a;
        }

        for (i = costsSize/2;i<costsSize;i++){
            sum += ob[i].b;
        }

        return sum;
}


int main()
{
    int a[][2] = {{259,770},{448,54},{926,667},{184,139},{840,118},{577,469}};
    int b;
    printf("%d\n",twoCitySchedCost(a,6,&b));
    return 0;
}


/*
����˼·�� ��Ʊ�������ԣ�
���������գ������۸� p1������۸� p2����������롢
����������׬ȡ��� p2-p1����ֵ������𣩡�
�������ǽ����գ� ������ǽ����չ�Ʊ�۸�ֱ�Ϊ
p1,p2,.....pn�����һ�������һ����������󣬼
pn-p1���ȼ���ÿ�춼�������
pn-p1=(p2-p1)+(p3-p2)+(p4-p3)+....+(pn-P(n-1))��
�����½������գ� ������������󣬼������Ǯ��
�㷨���̣�  ����������Ʊ�����ռ۸��б� price��
�������������ǽ����ն�������׬���������󣩣�
�����½������ն���������������Ǯ����
�� tmp Ϊ�� i-1 ��������� i ������׬ȡ������
�� tmp = prices[i] - prices[i - 1] �� ����������Ϊ�� tmp > 0��
��������������� profit��������Ϊ 00 ��Ϊ����
��ֱ�������� ������ɺ󣬷��������� profit��

*/
int maxProfit(int* prices, int pricesSize){
        int profit = 0;
        for (int i = 1; i <pricesSize; i++) {
            int tmp = prices[i] - prices[i - 1];
            if (tmp > 0) profit += tmp;
        }
        return profit;
}


/*
��һ����ƽ���ַ������У�'L' �� 'R' �ַ�����������ͬ�ġ�

����һ��ƽ���ַ��� s�����㽫���ָ�ɾ����ܶ��ƽ���ַ�����

���ؿ���ͨ���ָ�õ���ƽ���ַ��������������

����������ָ�ƽ�⴮���õ������ܶ��ƽ�⴮������һ������̰���㷨�����⣬���ʵ���λ�ýض�Դ���õ�ƽ���Ӵ����ضϺ�ǰ���Ӵ��ļ���������Ӱ�죨�޺�Ч�ԣ��������оֲ�������Ӽ�Ϊ��������Ž⡣
���˼·��

����һ��'L'��'R'�Ĳ�ֵ������diffCount������һ��ƽ���Ӵ�������count��
˳�����Դ���ַ�����L��diffCount+1������R��diffCount-1��
ÿ����һ���ַ����һ��diffCount�Ƿ�Ϊ0����Ϊ0��count+1

*/

int balancedStringSplit(char * s){
	int diffCnt = 0;
	int count = 0;

	if (s == NULL)
		return 0;

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'L')
			diffCnt++;
		else
			diffCnt--;

		if (diffCnt == 0)
			count++;
	}

	return count;
}

