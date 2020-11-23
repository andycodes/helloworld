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

int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
int(*p)[4];
�����е�*���� p ��һ��ָ�룬��ָ��һ�����飬
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
int two_dimensional_array_point_access(void)
{
	int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	int(*p)[4];

	int i,j;
	p = a;
	for(i=0; i<3; i++) {
		for(j=0; j<4; j++) {
			printf("%2d  ",*(*(p+i)+j));
		}
		printf("\n");
	}

	/*ע�����sizeof�Ĵ�С*/
	printf("%ld\n", sizeof(*(p+1)));

	return 0;
}


/*
����ָ�������
int *(p1[5]);  //ָ�����飬����ȥ������ֱ��д�� int *p1[5];
*/

/*
��άָ��
int **a;

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


/*
548. ������ָ�ɺ���ȵ�������
����һ���� n �����������飬
����Ҫ�ҵ�����������������Ԫ�� (i, j, k) ��

0 < i, i + 1 < j, j + 1 < k < n - 1
������ (0, i - 1)��(i + 1, j - 1)��(j + 1, k - 1)��
(k + 1, n - 1) �ĺ�Ӧ����ȡ�
�������Ƕ��������� (L, R) ��ʾԭ����
������ΪL��Ԫ�ؿ�ʼ������ΪR��Ԫ�ء�
ʾ��:
����: [1,2,1,2,1,2,1]
���: True
����:
i = 1, j = 3, k = 5.
sum(0, i - 1) = sum(0, 0) = 1
sum(i + 1, j - 1) = sum(2, 2) = 1
sum(j + 1, k - 1) = sum(4, 4) = 1
sum(k + 1, n - 1) = sum(6, 6) = 1

*/
/*�̶�j��ǰ��ֱ����i��k������jǰ���ܺ͵Ĳ��������С�Ĳ�ͼ�֦��*/
bool splitArray(int* nums, int numsSize)
{
	if (numsSize < 7) {
		return false;
	}

	int min = nums[0];
	int max = nums[0];
	for (int i = 1; i < numsSize; i++) {
		min = fmin(min, nums[i]);
		max = fmax(max, nums[i]);
		nums[i] += nums[i - 1];
	}

	for (int j = 3; j < numsSize - 3; j++) {
		if (abs(nums[j - 1] - (nums[numsSize - 1] - nums[j])) > max - min) {
			continue;
		}

		for (int i = 1; i < j - 1; i++) {
			if (nums[i - 1] != nums[j - 1] - nums[i]) {
				continue;
			}

			for (int k = j + 2; k < numsSize - 1; k++) {
				int a = nums[k - 1] - nums[j];
				int b = nums[numsSize - 1] - nums[k];
				if (a == b && a == nums[i - 1]) {
					return true;
				}
			}
		}
	}
	return false;
}


/*
825. ���������
���ǻụ�෢�ͺ����������ڸ���һ��������������������飬ages[i] ��ʾ�� i ���˵����䡣

��������������ʱ��A ���ܸ� B��A��B��Ϊͬһ�ˣ����ͺ�������

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
����A ���Ը� B ���ͺ�������

ע����� A �� B ���������󣬲����� B Ҳһ������ A �������󡣶��ң����ǲ�����Լ����ͺ�������

���ܹ��ᷢ�����ٷݺ�������?



ʾ�� 1:

����: [16,16]
���: 2
����: ���˿��Ի����������롣
ʾ�� 2:

����: [16,17,18]
���: 2
����: ��������ɲ����� 17 -> 16, 18 -> 17.
ʾ�� 3:

����: [20,30,100,110,120]
���: 3
����: ��������ɲ����� 110 -> 100, 120 -> 110, 120 -> 100.
*/
/*
�����뷨�����Ǳ������е� 20000 ���ˣ�����ֻ���Ǳ������е�Ԫ�� (age, count) ��ʾ���������ж����ˡ���Ϊ���ֻ�� 120 �����ܵ���ͣ������һ���ܿ���������㷨����ÿ��Ԫ�� (ageA, countA)��(ageB, countB)��������������Ӧ����ͣ���ô�ý� countA * countB ���뷢����������������� ageA == ageB ��ʱ�����Ǿ������ˣ�����ֻ�� countA * (countA - 1) �Ժ���������Ϊ�㲻�ܺ��Լ������������ߣ�LeetCode���ӣ�https://leetcode-cn.com/problems/friends-of-appropriate-ages/solution/gua-ling-de-peng-you-by-leetcode/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
int numFriendRequests(int* ages, int agesSize)
{
	int cnt[121];
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < agesSize; i++) {
		cnt[ages[i]]++;
	}

	int ret = 0;
	for (int agea = 0; agea <= 120; agea++) {
		int cnta = cnt[agea];
		for (int ageb = 0; ageb <= 120; ageb++) {
			int cntb = cnt[ageb];
			if (agea * 0.5 + 7 >= ageb) continue;
			if (agea < ageb) continue;
			if (agea < 100 && 100 < ageb) continue;
			ret += cnta * cntb;
			if (agea == ageb)
				ret -= cntb;
		}
	}

	return ret;
}

/*
957. N �����η�
�Ѷ��е�52
8 ���η��ų�һ�ţ�ÿ���η���������ס���ǿ��š�
ÿ�죬�����η��Ǳ�ռ�û���ã�����������¹�����и��ģ�
"	���һ���η����������ڵķ��䶼��ռ�û��ǿյģ���ô���η��ͻᱻռ�á�
"	�������ͻᱻ���á�
����ע�⣬���ڼ����е��η��ų�һ�У��������еĵ�һ�������һ�������޷����������ڵķ��䡣��
���������·�ʽ���������ĵ�ǰ״̬������� i ���η���ռ�ã��� cell[i]==1������ cell[i]==0��
���ݼ����ĳ�ʼ״̬���� N ��󷵻ؼ�����״���������� N �ֱ仯����

ʾ�� 1��
���룺cells = [0,1,0,1,1,0,0,1], N = 7
�����[0,0,1,1,0,0,0,0]
���ͣ�
�±�����˼���ÿ���״����
Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
Day 7: [0, 0, 1, 1, 0, 0, 0, 0]

ʾ�� 2��

*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* prisonAfterNDays(int* cells, int cellsSize, int N, int* returnSize)
{
	int *array = NULL;
	int *temp = NULL;
	int *day1 = NULL;
	int i, j;
	int cycle = 1; // ����
	int cnt = 0;

	if ((cells == NULL) || (N < 1 || N > 1000000000))  return NULL;

	array = calloc(cellsSize, sizeof(int));
	temp  = calloc(cellsSize, sizeof(int));
	day1  = calloc(cellsSize, sizeof(int));
	if (array == NULL || temp == NULL || day1 == NULL)  return NULL;

	// �����һ��仯
	for (i = 1; i < cellsSize-1; i++) {
	    day1[i] = (cells[i-1] == cells[i+1]) ? 1 : 0;
	    array[i] = day1[i];
	}

	// �ҳ�ѭ������
	while(true) {
	    for (i = 1; i < cellsSize-1; i++) {
	        temp[i] = (array[i-1] == array[i+1]) ? 1 : 0;
	    }
	    memcpy(array, temp, cellsSize * sizeof(int));

	    if (memcmp(array, day1, cellsSize * sizeof(int)) == 0)
			break;
	    cycle++;
	}

	// ���������ڵı仯
	cnt = (N-1) % cycle;
	for (i = 0; i < cnt; i++)
	{
	    for (j = 1; j < cellsSize-1; j++) {
	        temp[j] = (array[j-1] == array[j+1]) ? 1 : 0;
	    }
	    memcpy(array, temp, cellsSize * sizeof(int));
	}

	*returnSize = cellsSize;
	return array;
}


/*
1414. ��Ϊ K ������쳲�����������Ŀ
�������� k �����㷵�غ�Ϊ k ��쳲��������ֵ�������Ŀ�����У�ÿ��쳲��������ֶ����Ա�ʹ�ö�Ρ�

쳲��������ֶ���Ϊ��

F1 = 1
F2 = 1
Fn = Fn-1 + Fn-2 �� ���� n > 2 ��
���ݱ�֤���ڸ����� k ��һ�����ҵ����н⡣
*/
int findMinFibonacciNumbers(int k)
{
        int a = 0, b = 1;
        int fibo[100000];
	memset(fibo, 0, sizeof(fibo));
	fibo[a] = 1;
	fibo[b] = 1;
	int fiboCnt = 2;
        while (fibo[a] + fibo[b] <= k) {
		fibo[fiboCnt] = fibo[a] + fibo[b];
		a = b;
		b = fiboCnt;
		fiboCnt++;
        }

        int ans = 0;
        for (int i = fiboCnt - 1; i >= 0; --i) {
            if (k >= fibo[i]) {
                ++ans;
                k -= fibo[i];
            }
        }
        return ans;
}

/*
������ 16.04. ������Ϸ
���һ���㷨���ж�����Ƿ�Ӯ�˾�����Ϸ��������һ��
N x N ���������̣����ַ�" "��"X"��"O"��ɣ������ַ�" "����һ
����λ��
�����Ǿ�����Ϸ�Ĺ���
����������ַ������λ��" "���С�
��һ��������Ƿ��ַ�"O"���ҵڶ���������Ƿ��ַ�"X"��
"X"��"O"ֻ��������ڿ�λ�У���������ѷ����ַ���λ�ý�
����䡣
����N����ͬ���ҷǿգ����ַ�����κ��С��л�Խ���ʱ����Ϸ��������Ӧ���ַ�����һ�ʤ��
������λ�÷ǿ�ʱ��Ҳ��Ϊ��Ϸ������
�����Ϸ��������Ҳ������ٷ����ַ���
�����Ϸ���ڻ�ʤ�ߣ��ͷ��ظ���Ϸ�Ļ�ʤ��ʹ�õ��ַ�
��"X"��"O"���������Ϸ��ƽ�ֽ������򷵻� "Draw"������Ի�
���ж�����Ϸδ���������򷵻� "Pending"��

ʾ�� 1��

���룺 board = ["O X"," XO","X O"]
����� "X"
*/
char* tictactoe(char** board, int boardSize)
{
	int o1 = 0,x1 = 0,o2 = 0,x2 = 0,n = 0;

	for(int i = 0;i < boardSize; i++) {
		if(board[i][i]=='O')
			o1++;
		if(board[i][i]=='X')
			x1++;
		if(board[i][boardSize-i-1]=='O')
			o2++;
		if(board[i][boardSize-i-1]=='X')
			x2++;
	}

	if(o1==boardSize||o2==boardSize)
		return "O";
	if(x1==boardSize||x2==boardSize)
		return "X";

	for(int i=0;i<boardSize;i++) {
		o1 = 0; x1 = 0; o2=0; x2 = 0;
		for(int j=0;j<boardSize;j++) {
			if(board[i][j]=='O')
				o1++;
			if(board[i][j]=='X')
				x1++;
			if(board[j][i]=='O')
				o2++;
			if(board[j][i]=='X')
				x2++;
			if(board[i][j]==' ')
				n++;
		}

		if(o1==boardSize||o2==boardSize)
			return "O";
		if(x1==boardSize||x2==boardSize)
			return "X";
	}

	if(n!=0)
		return "Pending";
	else
		return "Draw";
}

/*
1184. ����վ��ľ���
�Ѷȼ�27
���ι���·������ n ��վ��������� 0 �� n - 1 ���б�š�������֪ÿһ�����ڹ���վ֮��ľ��룬distance[i] ��ʾ���Ϊ i �ĳ�վ�ͱ��Ϊ (i + 1) % n �ĳ�վ֮��ľ��롣
�����ϵĹ����������԰�˳ʱ�����ʱ��ķ�����ʻ��
���س˿ʹӳ����� start ��Ŀ�ĵ� destination ֮�����̾��롣

ʾ�� 1��

���룺distance = [1,2,3,4], start = 0, destination = 1
�����1
���ͣ�����վ 0 �� 1 ֮��ľ����� 1 �� 9����Сֵ�� 1��

*/
int distanceBetweenBusStops(int* distance, int distanceSize, int start,
int destination){
	int dis1 = 0, dis2 = 0;;
	int s;
	s = start;
	while (s != destination) {
		dis1 += distance[s];
		s = (s + 1) % distanceSize;
	}

	while (s != start) {
		dis2 += distance[s];
		s = (s + 1) % distanceSize;
	}
	return dis1 < dis2 ? dis1 : dis2;

}

/*
41. ȱʧ�ĵ�һ������
�Ѷ�����703
����һ��δ������������飬�����ҳ�����û�г��ֵ���С
����������

ʾ�� 1:
����: [1,2,0]
���: 3
ʾ�� 2:
����: [3,4,-1,1]
���: 2
ʾ�� 3:
����: [7,8,9,11,12]
���: 1


*/

int firstMissingPositive(int* nums, int numsSize)
{
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] <= 0) {
            nums[i] = numsSize + 1;
        }
    }
    for (int i = 0; i < numsSize; ++i) {
        int num = abs(nums[i]);
        if (num <= numsSize) {
            nums[num - 1] = -abs(nums[num - 1]);
        }
    }
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > 0) {
            return i + 1;
        }
    }
    return numsSize + 1;
}

/*
717. 1������2�����ַ�
�Ѷȼ�136
�����������ַ�����һ���ַ�������һ����0����ʾ���ڶ�
���ַ�������������(10 �� 11)����ʾ��
�ָ�һ�������ɱ�����ɵ��ַ����������һ���ַ��Ƿ�
�ض�Ϊһ��һ�����ַ����������ַ���������0������
ʾ�� 1:
����:
bits = [1, 0, 0]
���: True
����:
Ψһ�ı��뷽ʽ��һ���������ַ���һ��һ�����ַ���
�������һ���ַ���һ�����ַ���
*/

/*
���ǿ��Զ� \mathrm{bits}bits ���������ɨ�����ж����һλ�Ƿ�Ϊһ�����ַ�����ɨ�赽�� ii λʱ����� \mathrm{bits}[i]=1bits[i]=1����ô˵������һ���������ַ����� ii ��ֵ���� 2����� \mathrm{bits}[i]=0bits[i]=0����ô˵������һ��һ�����ַ����� ii ��ֵ���� 1����� ii ���������� \mathrm{bits}.\mathrm{length}-1bits.length?1 ��λ�ã���ô˵�����һλһ����һ�����ַ������ߣ�LeetCode���ӣ�https://leetcode-cn.com/problems/1-bit-and-2-bit-characters/solution/1bi-te-yu-2bi-te-zi-fu-by-leetcode/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
bool isOneBitCharacter(int* bits, int bitsSize)
{
        int i = 0;
        while (i < bitsSize - 1) {
            i += bits[i] + 1;
        }
        return i == bitsSize - 1;
}

/*
384. ��������
�Ѷ��е�85
����һ��û���ظ�Ԫ�ص����顣
ʾ��:
// �����ּ��� 1, 2 �� 3 ��ʼ�����顣
int[] nums = {1,2,3};
Solution solution = new Solution(nums);
// �������� [1,2,3] �����ؽ�����κ� [1,2,3]�����з��صĸ���
Ӧ����ͬ��
solution.shuffle();
// �������鵽���ĳ�ʼ״̬[1,2,3]��
solution.reset();
// �����������[1,2,3]���Һ�Ľ����
solution.shuffle();
*/

#include <time.h>

typedef struct {
	int *array;
	int *origin;
	int size;
} Solution;

int randomInt(int min, int max)
{
	int ret = rand() % (max - min + 1) + min;
	return ret;
}

Solution* solutionCreate(int* nums, int numsSize)
{
	Solution *new = malloc(sizeof(Solution));
	new->size = numsSize;
	new->array = malloc(sizeof(int) * numsSize);
	new->origin = malloc(sizeof(int) * numsSize);
	for(int i = 0; i <  numsSize; i++){
		new->array[i] = nums[i];
		new->origin[i] = nums[i];
	}
	return new;
}

/** Resets the array to its original configuration and return it. */
int* solutionReset(Solution* obj, int* retSize)
{
	*retSize = obj->size;
	for(int i = 0; i < *retSize; i++){
		obj->array[i] = obj->origin[i];
	}
	return obj->array;
}

/** Returns a random shuffling of the array. */
int* solutionShuffle(Solution* obj, int* retSize)
{
	*retSize = obj->size;
	int swapIndex;

	for(int i = 0; i < *retSize; i++){
		swapIndex = randomInt(i, *retSize - 1);
		swap(&(obj->array[i]), &(obj->array[swapIndex]));
	}

	return obj->array;
}

void solutionFree(Solution* obj) {
    free(obj->array);
    free(obj->origin);
    free(obj);
    return;
}

/*
1233. ɾ�����ļ���
�Ѷ��е�24
����һλϵͳ����Ա��������һ���ļ����б� folder�������
����Ҫɾ�����б��е����� ���ļ��У����� ����˳�� ��
��ʣ�µ��ļ��С�
�����������塸���ļ��С���
"	����ļ��� folder[i] λ����һ���ļ��� folder[j] �£���ô folder[i]
���� folder[j] �����ļ��С�
�ļ��еġ�·��������һ�����������¸�ʽ�����γɵ�
�ַ�����
"	/ ���һ�����߶��СдӢ����ĸ��
���磬/leetcode �� /leetcode/problems ������Ч��·���������ַ���
�� / ���ǡ�

ʾ�� 1��
���룺folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
�����["/a","/c/d","/c/f"]
���ͣ�"/a/b/" �� "/a" �����ļ��У��� "/c/d/e" �� "/c/d" �����ļ��С�
*/
int Comp2Str(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

char **removeSubfolders(char **folder, int folderSize, int *returnSize)
{
    char **ret;
    ret = malloc(sizeof(char *) * folderSize);
    *returnSize = 0;
    char *p;
    int i;

    qsort(folder, folderSize, sizeof(char *), Comp2Str);

    ret[*returnSize] = folder[0];
    *returnSize = 1;

    for (i = 1; i < folderSize; i++) {
        p = strstr(folder[i], ret[*returnSize - 1]);
        if (p == NULL) {
            ret[*returnSize] = folder[i];
            *returnSize = *returnSize + 1;
        } else if (p[strlen(ret[*returnSize - 1])] != '/') {
            ret[*returnSize] = folder[i];
            *returnSize = *returnSize + 1;
        }
    }

    return ret;
}

/*
128. ���������
�Ѷ�����487
����һ��δ������������飬�ҳ���������еĳ��ȡ�
Ҫ���㷨��ʱ�临�Ӷ�Ϊ O(n)��
ʾ��:
����: [100, 4, 200, 1, 3, 2]
���: 4
����: ����������� [1, 2, 3, 4]�����ĳ���Ϊ 4��

*/

int longestConsecutive(int* nums, int numsSize)
{
    if (numsSize == 0) return 0;
	qsort(nums, numsSize, sizeof(int), cmp_int);
   // Arrays.sort(nums);

    // max ���ս��, curr ��ǰ����, last �ϸ�����
    int max = 1, curr = 1, last = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == last) continue;
        if (nums[i] == last + 1) curr++; // �������������� +1
        else {
            max = fmax(max, curr); // �������ˣ���¼����
            curr = 1; // ���¿�ʼ
        }
        last = nums[i];
    }
    max = fmax(max, curr); // ���������һ�ε���������
    return max;
}

int longestConsecutive(int* nums, int numsSize)
{
    if (numsSize == 0) return 0;

    int n = numsSize, max = 1;
struct HashTable dht;
struct HashTable *ht = &dht;
	HashInit(ht, numsSize, hashequal_int, hashcode_int);
	for (int i = 0; i < numsSize; i++) {
		hashPushKey(ht, nums[i]);
	}

    for (int i = 0; i < numsSize; i++) {
        // ���ɣ�����б��Լ�Сһ��ģ����Լ����飬��С��ȥ��
	struct DataEntry *find = hashFindKey(ht, nums[i] - 1);
	if (find != NULL) {
		continue;
	}


        int r = nums[i]; // r: right ��ʾ���� v ��ͷ�������������١�
        while (hashFindKey(ht, r + 1)) r++; // ����鿴
        max = fmax(max, r - nums[i] + 1); // ��¼���� [v, r] ����
    }
    return max;
}

/*
30. �������е��ʵ��Ӵ�
����һ���ַ��� s ��һЩ������ͬ�ĵ��� words���ҳ� s ��ǡ
�ÿ����� words �����е��ʴ����γɵ��Ӵ�����ʼλ�á�
ע���Ӵ�Ҫ�� words �еĵ�����ȫƥ�䣬�м䲻����������
����������Ҫ���� words �е��ʴ�����˳��
ʾ�� 1��
���룺
  s = "barfoothefoobarman",
  words = ["foo","bar"]
�����[0,9]
���ͣ�
������ 0 �� 9 ��ʼ���Ӵ��ֱ��� "barfoo" �� "foobar" ��
�����˳����Ҫ, [9,0] Ҳ����Ч�𰸡�
*/
#define printf() void();
 char ** g_words;
 int g_wordsSize;
 int g_wordsLen;

int isok(char *s,int i,int len)
{
	int *wordsVisted=calloc(g_wordsSize,sizeof(int));
	int matchSize=0;
	int matchFlag=0;

	printf("!!!!!!!!!!i=%d\n",i);
	while(i<len) {
		matchFlag=0;
		for(int k=0;k<g_wordsSize;k++) {
			//if(wordsVisted[k]==0)printf("s+i:%s \ntry to match %s\n",s+i,g_words[k]);
			if(wordsVisted[k]==0&&strncmp(s+i,g_words[k],g_wordsLen)==0) {
				printf("matched %s\n",g_words[k]);
				wordsVisted[k]=1;
				matchFlag=1;
				matchSize++;
				i=i+g_wordsLen;
				break;
			}
		}

		if(matchFlag==0)
			return 0;
		if(matchSize==g_wordsSize)
			return 1;
	}

	if(matchSize==g_wordsSize)
		return 1;
	return 0;
}

int* findSubstring(char * s, char ** words, int wordsSize, int* returnSize)
{
	int slen=strlen(s);
	int * out = calloc(slen,sizeof(int));
	(*returnSize)=0;

	if(wordsSize==0||slen==0||s==NULL||words==NULL){
		return out;
	}

	g_words=words;
	g_wordsSize=wordsSize;
	g_wordsLen=strlen(words[0]);

	for(int i=0; slen-i >= wordsSize * g_wordsLen; i++){
		if(isok(s,i,slen)){
			out[*returnSize]=i;
			(*returnSize)++;
		}
	}

	return out;
}

/*
723. �����ǹ�
���������ʵ��һ���򵥵������㷨��
����һ����ά�������� board �����ǹ����ڵķ��񣬲�ͬ��
������ board[i][j] ����ͬ������ǹ������ board[i][j] = 0 ���� (i, j)
���λ���ǿյġ������ķ���������ƶ������Ϸ״̬��
������Ҫ��������¹�������ǹ���ʹ��������������
��״̬�����������
���������������ˮƽ���ߴ�ֱ������ͬ���ǹ���ͬһʱ
�佫���Ƿ��飬������Щλ�ñ�ɿյġ�
��ͬʱ�������Щ�ǹ�֮�������һ���յ�λ���Ϸ���
���ǹ�����ô�Ϸ����ǹ��ͻ�����ֱ�������·����ǹ���
�ߵײ�����Щ�ǹ�����ͬʱ���䣬Ҳ�������µ��ǹ��Ӷ�
�����ֲ���������
ͨ��ǰ�����Ĳ����������ֻ���ֿ��Է�����ǹ������
���ظ�ǰ��Ĳ�����
�������ڿ��Է�����ǹ���Ҳ����״̬�ȶ�֮�������
���յ�״̬��
����Ҫģ����������ʹ��������ﵽ�ȶ�״̬���������
���� :
����:
board =
[[110,5,112,113,114],[210,211,5,213,214],[310,311,3,313,314],[410,411,412,5,414],
[5,1,512,3,3],[610,4,1,613,614],[710,1,2,713,714],[810,1,2,1,1],[1,1,2,2,2],[4,1,4,4,1014]]
���:
[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[110,0,0,0,114],[210,0,0,0,214],[310,0,0,113,314],
[410,0,0,213,414],[610,211,112,313,614],[710,311,412,613,714],[810,411,512,713,1014]]
*/

int** candyCrush(int** board, int boardSize, int* boardColSize,
int* returnSize, int** returnColumnSizes)
{
	int rows = boardSize, cols = *boardColSize;
	bool todo = false;   // �Ƿ����Ҫ������ǹ�

	// һ��һ��ɨ��
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c + 2 < cols; ++c) {
			// ȡ�������ľ���ֵ�����ܱ�ȡ���ˣ�����Ҫ����ֵ��
			int v = abs(board[r][c]);
			// �������������������ͬ���ǹ�
			if (v != 0 && v == abs(board[r][c + 1]) && v == abs(board[r][c + 2])) {
				// ���������������ӵ��ǹ���ֵȡ����
				//����������״̬
				board[r][c] = board[r][c + 1] = board[r][c + 2] = -v;
				todo = true;
			}
		}
	}

	// һ��һ��ɨ��
	for (int r = 0; r + 2 < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			// ȡ�������ľ���ֵ�����ܱ�ȡ���ˣ�
			//����Ҫ����ֵ��
			int v = abs(board[r][c]);
			// �������������������ͬ���ǹ�
			if (v != 0 && v == abs(board[r + 1][c]) && v == abs(board[r + 2][c])) {
				// ���������������ӵ��ǹ���ֵȡ����
				//����������״̬
				board[r][c] = board[r + 1][c] = board[r + 2][c] = -v;
				todo = true;
			}
		}
	}

/*
������������ for ѭ������Ҫ�����ǹ��ĸ����Ѿ���Ϊ����
�������и��ӽ��з����ǹ�
*/
	if (todo) {
		for (int c = 0; c < cols; ++c) {   // ������ÿһ��
			int wr = rows - 1;  // ���յ����ǹ�������
			for (int r = rows - 1; r >= 0; r--) {  // �������ϱ���ÿһ��
				if (board[r][c] > 0) {
					// �� (r,c) ���ǹ����䵽 (wr,c) ��
					// r �� wr Ҫô��ͬһ�У�Ҫô r �����棬
					//��˲����ص��ҵ� wr �ĳ�ʼ�С�
					board[wr][c] = board[r][c];
					wr--;   // ������һ��
				}
			}
			// ��� wr û���ߵ���У�˵������Ӧ��ȫ��Ҫ�����
			while (wr >= 0) {
				board[wr--][c] = 0;
			}
		}
	}
	// ���������Ҫ������ǹ������ٵ���һ�� candyCrush(board)
	// ע�⣬���� candyCrush ���ǲ�ȷ���治�����µ�Ҫ������ǹ���ֻ���ٵ���һ�� candyCrush
	// �������õ� candyCrush ������ for ѭ����û�а� tod0 ���Ϊ true�����ʾ������
	// ��ˣ���������������һ�� candyCrush �������з���Ĳ�����

	*returnColumnSizes = boardColSize;
	*returnSize = boardSize;
	return todo ?
	candyCrush(board, boardSize, boardColSize, returnSize, returnColumnSizes) : board;
}


/*
48. ��תͼ��
����һ�� n �� n �Ķ�ά�����ʾһ��ͼ��
��ͼ��˳ʱ����ת 90 �ȡ�
˵����
�������ԭ����תͼ������ζ������Ҫֱ���޸������
��ά�����벻Ҫʹ����һ����������תͼ��
ʾ�� 1:
���� matrix =
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],
ԭ����ת�������ʹ���Ϊ:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
*/

/*
�������� - ���µĶԽ��߷�ת��270�� +270��+ һ�ξ��񣩣�����ˮƽ�������·�ת��-180�� +?180��+ һ�ξ��񣩣�����ʵ��˳ʱ�� 9090 �ȵ���תЧ�����ߣ�ChopinXBP���ӣ�https://leetcode-cn.com/problems/rotate-image/solution/zi-wai-xiang-nei-shun-shi-zhen-xun-huan-jiao-huan-/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
	int n = matrixSize;

	// transpose matrix
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			swap(matrix[i][j],matrix[j][i]);
		}
	}

	// reverse each row
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n / 2; j++) {
			int tmp = matrix[i][j];
			matrix[i][j] = matrix[i][n - j - 1];
			matrix[i][n - j - 1] = tmp;
			swap(matrix[i][j],matrix[i][n - j - 1]);
		}
	}
}


/*
54. ��������
�Ѷ��е�446
����һ������ m x n ��Ԫ�صľ���m ��, n �У����밴��˳ʱ
������˳�򣬷��ؾ����е�����Ԫ�ء�
ʾ�� 1:
����:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
���: [1,2,3,6,9,8,7,4,5]
*/
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	if (matrix == NULL || matrixSize <= 0 || matrixColSize == NULL) {
		*returnSize = 0;
		return NULL;
	}

	int rows = matrixSize, columns = *matrixColSize;
	int visited[rows][columns];
	memset(visited, 0, sizeof(visited));
	int total = rows * columns;
	int *res = (int *)calloc(total, sizeof(int));

	int row = 0, column = 0;
	int directionIndex = 0;
	for (int i = 0; i < total; i++) {
		res[i] = matrix[row][column];
		visited[row][column] = true;

		int nextRow = row + directions[directionIndex][0];
		int nextColumn = column + directions[directionIndex][1];

		if (nextRow < 0 || nextRow >= rows || nextColumn < 0 ||
			nextColumn >= columns || visited[nextRow][nextColumn]) {
			directionIndex = (directionIndex + 1) % 4;
		}

		row += directions[directionIndex][0];
		column += directions[directionIndex][1];
	}

	*returnSize = total;
	return res;
}

//����Ϊ��+��������
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	if(!matrixSize)
		{ *returnSize = 0; return NULL;}

	*returnSize = matrixSize * matrixColSize[0];
	int* nums = (int *)malloc(sizeof(int) * (*returnSize));
	int cur = 0, l = 0, t = 0, r = matrixColSize[0] - 1, b = matrixSize - 1;
	while(cur < *returnSize) {
		for(int i = l; cur < *returnSize && i <= r; i++)
			nums[cur++] = matrix[t][i]; t++;
		for(int i = t; cur < *returnSize && i <= b; i++) nums[cur++] = matrix[i][r]; r--;
		for(int i = r; cur < *returnSize && i >= l; i--) nums[cur++] = matrix[b][i]; b--;
		for(int i = b; cur < *returnSize && i >= t; i--) nums[cur++] = matrix[i][l]; l++;
	}
	return nums;
}


/*
59. �������� II
�Ѷ��е�219
����һ�������� n������һ������ 1 �� n2 ����Ԫ�أ���Ԫ��
��˳ʱ��˳���������е������ξ���
ʾ��:
����: 3
���:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes)
{
        int l = 0, r = n - 1, t = 0, b = n - 1;
        int **mat = (int **)calloc(n, sizeof(int *));
	*returnColumnSizes = (int *)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		mat[i] = (int *)calloc(n, sizeof(int));
		(*returnColumnSizes)[i] = n;
	}

        int num = 1, tar = n * n;
        while(num <= tar) {
            for(int i = l; i <= r; i++)
				mat[t][i] = num++; // left to right.
            t++;

            for(int i = t; i <= b; i++)
				mat[i][r] = num++; // top to bottom.
            r--;

            for(int i = r; i >= l; i--)
				mat[b][i] = num++; // right to left.
            b--;

            for(int i = b; i >= t; i--)
				mat[i][l] = num++; // bottom to top.
            l++;

        }

	*returnSize = n;
        return mat;
}

/*
628. �����������˻�
����һ���������飬���������ҳ�����������ɵ����˻������������˻���

ʾ�� 1:

����: [1,2,3]
���: 6
ʾ�� 2:

����: [1,2,3,4]
���: 24
*/
int maximumProduct(int* nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	return fmax(nums[0] * nums[1] * nums[numsSize - 1], nums[numsSize - 1] * nums[numsSize - 2] * nums[numsSize - 3]);

}

/*
1074. Ԫ�غ�ΪĿ��ֵ���Ӿ�������
�������� matrix ��Ŀ��ֵ target������Ԫ���ܺ͵���Ŀ��ֵ�ķǿ��Ӿ����������

�Ӿ��� x1, y1, x2, y2 ������ x1 <= x <= x2 �� y1 <= y <= y2 �����е�Ԫ matrix[x][y] �ļ��ϡ�

��� (x1, y1, x2, y2) �� (x1', y1', x2', y2') �����Ӿ����в������겻ͬ���磺x1 != x1'������ô�������Ӿ���Ҳ��ͬ��



ʾ�� 1��

���룺matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
�����4
���ͣ��ĸ�ֻ�� 0 �� 1x1 �Ӿ���
*/
int preSum[301][301];
int getSum(int x1,int y1,int x2,int y2)//����ָ�����ϽǺ����½ǵľ���Ԫ�غ�
{
    return preSum[x2][y2]-preSum[x1-1][y2]-preSum[x2][y1-1]+preSum[x1-1][y1-1];
}

int numSubmatrixSumTarget(int** matrix, int matrixSize, int* matrixColSize, int target){
    memset(preSum,0,sizeof(preSum));
    int r=matrixSize;
    int c=matrixColSize[0];
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)//����ǰ׺�����飬ע����������������ѭ��������1Ϊ��������0
            preSum[i][j]=preSum[i-1][j]+preSum[i][j-1]-preSum[i-1][j-1]+matrix[i-1][j-1];
    int count=0;//��¼���������ľ������
    for(int i=1;i<=r;i++)
    {
        for(int j=i;j<=r;j++)
        {
            for(int k=1;k<=c;k++)
            {
                for(int l=k;l<=c;l++)//����ѭ���壡
                {
                    if(getSum(i,k,j,l)==target)
                        count++;
                }
            }
        }
    }
    return count;
}