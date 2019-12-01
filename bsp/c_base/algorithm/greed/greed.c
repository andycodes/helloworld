#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
我们这样来看这个问题，
公司首先将这 2N 个人全都安排飞往 B 市，
再选出 N 个人改变它们的行程，让他们飞往 A 市。
如果选择改变一个人的行程，
那么公司将会额外付出 price_A - price_B 的费用，
这个费用可正可负。


因此最优的方案是，选出 price_A - price_B 最小的 N 个人，
让他们飞往 A 市，其余人飞往 B 市。
算法按照 price_A - price_B 从小到大排序；
将前 N 个人飞往 A 市，其余人飞往 B 市，
并计算出总费用。
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
解题思路： 股票买卖策略：
单独交易日：设今天价格 p1、明天价格 p2，则今天买入、
明天卖出可赚取金额 p2-p1（负值代表亏损）。
连续上涨交易日： 设此上涨交易日股票价格分别为
p1,p2,.....pn，则第一天买最后一天卖收益最大，�
pn-p1；等价于每天都买卖，�
pn-p1=(p2-p1)+(p3-p2)+(p4-p3)+....+(pn-P(n-1))。
连续下降交易日： 则不买卖收益最大，即不会亏钱。
算法流程：  遍历整个股票交易日价格列表 price，
策略是所有上涨交易日都买卖（赚到所有利润），
所有下降交易日都不买卖（永不亏钱）。
设 tmp 为第 i-1 日买入与第 i 日卖出赚取的利润，
即 tmp = prices[i] - prices[i - 1] ； 当该天利润为正 tmp > 0，
则将利润加入总利润 profit；当利润为 00 或为负，
则直接跳过； 遍历完成后，返回总利润 profit。

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
在一个「平衡字符串」中，'L' 和 'R' 字符的数量是相同的。

给出一个平衡字符串 s，请你将它分割成尽可能多的平衡字符串。

返回可以通过分割得到的平衡字符串的最大数量。

问题分析：分割平衡串，得到尽可能多的平衡串。这是一个适用贪心算法的问题，在适当的位置截断源串得到平衡子串，截断后前后子串的计数不互相影响（无后效性），且所有局部最优相加即为整体的最优解。
解决思路：

设置一个'L'与'R'的差值计数器diffCount，设置一个平衡子串计数器count；
顺序遍历源串字符，遇L则diffCount+1，遇到R则diffCount-1；
每遍历一个字符检查一次diffCount是否为0，若为0则count+1

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

