
/*
有一些工作：difficulty[i] 表示第i个工作的难度，profit[i]表示第i个工作的收益。

现在我们有一些工人。worker[i]是第i个工人的能力，即该工人只能完成难度小于等于worker[i]的工作。

每一个工人都最多只能安排一个工作，但是一个工作可以完成多次。

举个例子，如果3个工人都尝试完成一份报酬为1的同样工作，那么总收益为 $3。如果一个工人不能完成任何工作，他的收益为 $0 。

我们能得到的最大收益是多少？

示例：

输入: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
输出: 100
解释: 工人被分配的工作难度是 [4,4,6,6] ，分别获得 [20,20,30,30] 的收益。


*/
struct profit_str{
	int index;
	int profit;
};

int cmp_struct( const void *a ,const void *b){
	struct profit_str *c = (struct profit_str *)a;
	struct profit_str *d = (struct profit_str *)b;
	return c->profit < d->profit;
}


int maxProfitAssignment(int* difficulty, int difficultySize,
int* profit, int profitSize, int* worker, int workerSize){

	if (difficulty == NULL || difficultySize <= 0 || profit == NULL ||
		profitSize <= 0 || worker == NULL || workerSize <= 0)
		return 0;

	if (profitSize != difficultySize)
		return 0;

	int sum = 0;
	struct profit_str * pStr = malloc(sizeof(struct profit_str) * profitSize);

	for (int i = 0; i < profitSize; i++) {
		(pStr + i)->index = i;
		(pStr + i)->profit = profit[i];
	}

	qsort(pStr,profitSize,sizeof(pStr[0]),cmp_struct);

	for (int i = 0; i < workerSize; i++) {
		int j = 0;
		while((j < difficultySize) && (worker[i] < difficulty[pStr[j].index])){
			j++;}

		if (j != difficultySize)
			sum += pStr[j].profit;
	}

	return sum;

}

