
/*
��һЩ������difficulty[i] ��ʾ��i���������Ѷȣ�profit[i]��ʾ��i�����������档

����������һЩ���ˡ�worker[i]�ǵ�i�����˵����������ù���ֻ������Ѷ�С�ڵ���worker[i]�Ĺ�����

ÿһ�����˶����ֻ�ܰ���һ������������һ������������ɶ�Ρ�

�ٸ����ӣ����3�����˶��������һ�ݱ���Ϊ1��ͬ����������ô������Ϊ $3�����һ�����˲�������κι�������������Ϊ $0 ��

�����ܵõ�����������Ƕ��٣�

ʾ����

����: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
���: 100
����: ���˱�����Ĺ����Ѷ��� [4,4,6,6] ���ֱ��� [20,20,30,30] �����档


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

