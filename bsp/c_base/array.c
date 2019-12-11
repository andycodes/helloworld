#include <stdio.h>

/*


һά��������ַ��ʷ�ʽ��
��int b[10]Ϊ��, int *p = b;��
b[0] ��ͬ�� *(p+0);
b[9] ��ͬ�� *(p+9);
b[i] ��ͬ�� *(p+i)


��ά������Ϊ�������ݸ�����
������������ʽ:
void Func(int array[3][10]);
void Func(int array[ ][10]);
void Func(int (*array)[10]);
*/




/*
��ά����ָ��
ָ������     ��     ָ��
*/
int two_dimensional_array_point_access(void)
{
    int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};

/*�����е�*���� p ��һ��ָ�룬��ָ��һ�����飬
���������Ϊint [4]��
������ a ��������ÿ��һά��������͡�

p ָ�������������int [4]����ôp+1��ǰ�� 4��4 = 16 ���ֽڣ�
p-1�ͺ��� 16 ���ֽڣ������������� a ��������ÿ
��һά����ĳ��ȡ�Ҳ����˵��
p+1��ʹ��ָ��ָ���ά�������һ�У�
p-1��ʹ��ָ��ָ���������һ�С�
������ a �ڱ��ʽ��Ҳ�ᱻת��Ϊ�� p �ȼ۵�ָ�룡

a+i == p+i
a[i] == p[i] == *(a+i) == *(p+i)
a[i][j] == p[i][j] == *(a[i]+j) == *(p[i]+j) == *(*(a+i)+j) == *(*(p+i)+j)
*/
    int(*p)[4];

    int i,j;
    p=a;
    for(i=0; i<3; i++){
		for(j=0; j<4; j++)
			printf("%2d  ",*(*(p+i)+j));
		printf("\n");
	}
	return 0;
}


/*
����ָ�������
int *(p1[5]);  //ָ�����飬����ȥ������ֱ��д�� int *p1[5];
*/






/*
�䳤����(variable-length array,VLA)(C99��
C99��׼�����˱䳤���飬������ʹ�ñ������������ά
int quarters = 4;
int regions = 5;
double sales[quarters][regions]; //һ���䳤����VAL

�䳤������һЩ���ƣ��䳤����������Զ��洢��ģ�
��ζ�����Ǳ����ں����ڲ�����Ϊ��������������
��������ʱ�����Խ��г�ʼ����

C99��׼�涨������ʡ�Ժ���ԭ���е����ƣ�
�������ʡ�����ƣ�����Ҫ���Ǻ�������ʡ�Ե�ά��:
int sum2d(int , int, int ar[*][*]);

6.7.5.2 Array declarators
Array objects declared with the static or extern storage-class specifier
cannot have a variable length array (VLA) type
*/
void array_vla(int tmp)
    {
            int a;

            scanf("%d", &a);
            int b[tmp];
            int c[a];
            printf ("size(b) = %lu, size(c) = %lu\n", sizeof(b)/sizeof(int), sizeof(c)/sizeof(int));
    }


/*
����һ������ A�����仮��Ϊ�������ཻ��û�й���Ԫ�أ������������� left �� right�� ʹ�ã�

left �е�ÿ��Ԫ�ض�С�ڻ���� right �е�ÿ��Ԫ�ء�
left �� right ���Ƿǿյġ�
left Ҫ������С��
����������ķ���󷵻� left �ĳ��ȡ����Ա�֤���������Ļ��ַ�����
*/
int partitionDisjoint(int* A, int ASize){
	int *left_max = malloc(ASize * sizeof(int));
	int *right_min = malloc(ASize * sizeof(int));

	int tmp = A[0];
	for (int i = 0; i < ASize; i++) {
		tmp = tmp > A[i] ? tmp : A[i];
		left_max[i] = tmp;
	}

	tmp = A[ASize - 1];
	for (int i = ASize -1; i >= 0; i--) {
		tmp = tmp < A[i] ? tmp : A[i];
		right_min[i] = tmp;
	}

	for (int i = 1; i < ASize; i++){
		if (left_max[i -1] <= right_min[i])
			return i;
	}

	return ASize;
}


/*
����һ������ m �� n �����ӵ���壬ÿһ�����Ӷ����Կ�����һ��ϸ����ÿ��ϸ������һ����ʼ״̬ live��1����Ϊ��ϸ���� �� dead��0����Ϊ��ϸ����ÿ��ϸ������˸�����λ�ã�ˮƽ����ֱ���Խ��ߣ�
��ϸ������ѭ�����������涨�ɣ�

�����ϸ����Χ�˸�λ�õĻ�ϸ�����������������λ�û�ϸ��������
�����ϸ����Χ�˸�λ����������������ϸ�������λ�û�ϸ����Ȼ��
�����ϸ����Χ�˸�λ���г���������ϸ�������λ�û�ϸ��������
�����ϸ����Χ������������ϸ�������λ����ϸ�����
���ݵ�ǰ״̬��дһ�����������������ϸ������һ����һ�θ��º�ģ�״̬����һ��״̬��ͨ������������ͬʱӦ���ڵ�ǰ״̬�µ�ÿ��ϸ�����γɵģ�����ϸ���ĳ�����������ͬʱ�����ġ�
*/
void gameOfLife(int** board, int boardSize, int* boardColSize){
    int m = boardSize;
    int n = *boardColSize;
    int sum = 0;
    int midArr[m+2][n+2];

    for(int i = 0; i < (m +2); i++) {
        for(int j = 0; j < (n+2);j++) {
            midArr[i][j] = 0;
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n;j++) {
            midArr[i + 1][j + 1] = board[i][j];
        }
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int x = i + 1;
            int y = j + 1;
            sum = midArr[x - 1][y] + midArr[x + 1][y] + midArr[x][y - 1] + midArr[x][y + 1] + midArr[x - 1][y - 1] + midArr[x + 1][y + 1] + midArr[x + 1][y - 1] + midArr[x - 1][y + 1];
            if((sum == 3) || ((board[i][j] == 1) && (sum == 2))) {
                board[i][j] = 1;
            } else {
                board[i][j] = 0;
            }
        }
    }
}

/*

˫ָ��

*/

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


/*
���� �ַ��� text �� �ַ����б� words, �������е������� [i, j] ʹ���������Է�Χ�ڵ����ַ��� text[i]...text[j]������ i �� j�������ַ����б� words��



ʾ�� 1:

����: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
���: [[3,7],[9,13],[10,17]]
ʾ�� 2:

����: text = "ababa", words = ["aba","ab"]
���: [[0,1],[0,2],[2,3],[2,4]]
����:
ע�⣬���ص���Կ����н��棬���磬"aba" ���� [0,2] ��Ҳ�� [2,4] ��
*/
int cmp(const void *a,const void *b)
{
    int *ap = *(int **)a;
    int *bp = *(int **)b;

    if(ap[0] == bp[0])
        return ap[1] - bp[1];
    else
        return ap[0] - bp[0];

}

int** indexPairs(char * text, char ** words, int wordsSize, int* returnSize, int** returnColumnSizes){
    int i, j;
    int** res = (int **)malloc(sizeof(int *) * 1000);
    int cnt = 0;
    int len1 = strlen(text);

    for (i = 0; i < wordsSize; i++) {
        int len2 = strlen(words[i]);
        if(len2 > len1)
		continue;

	for (j = 0; j < len1 - len2 + 1; j++) {
            if (strncmp(text + j, words[i], strlen(words[i])) == 0) {
                res[cnt] = (int *)malloc(sizeof(int) * 2);
                res[cnt][0] = j;
                res[cnt][1] = j + strlen(words[i]) - 1;
                cnt++;
                //printf("j = %d endIdx = %d cnt = %d\n", j, j + strlen(words[i]) - 1, cnt);
            }
        }
	}

    qsort(res, cnt, sizeof(res[0]), cmp); // ��ά��������
    *returnSize = cnt;
    returnColumnSizes[0] = (int *)malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; i++) {
        returnColumnSizes[0][i] = 2;
    }
    return res;
}



int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("argc err\n");
		return -1;
	}

	switch(atoi(argv[1])) {
	case 1:
		two_dimensional_array_point_access();
	break;
	case 2:
	break;
	case 3:
	break;
	case 4:
	default:
	break;
	}

	return 0;
}


