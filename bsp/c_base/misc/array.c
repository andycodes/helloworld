#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "flag_type.h"
#include "../algo/math/math.h"
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
void array_vla(int tmp)
    {
            int a;

            scanf("%d", &a);
            int b[tmp];
            int c[a];
            printf ("size(b) = %lu, size(c) = %lu\n", sizeof(b)/sizeof(int), sizeof(c)/sizeof(int));
    }


/*
����һ������ A�����仮��Ϊ�������ཻ��û�й���Ԫ�أ�
������������ left �� right�� ʹ�ã�

left �е�ÿ��Ԫ�ض�С�ڻ���� right �е�ÿ��Ԫ�ء�
left �� right ���Ƿǿյġ�
left Ҫ������С��
����������ķ���󷵻� left �ĳ��ȡ�
���Ա�֤���������Ļ��ַ�����
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
289. ������Ϸ
����һ������ m �� n �����ӵ���壬
ÿһ�����Ӷ����Կ�����һ��ϸ����
ÿ��ϸ������һ����ʼ״̬ live��1����Ϊ��ϸ����
�� dead��0����Ϊ��ϸ����ÿ��ϸ������˸�����λ
�ã�ˮƽ����ֱ���Խ��ߣ�
��ϸ������ѭ�����������涨�ɣ�

�����ϸ����Χ�˸�λ�õĻ�ϸ��������������
���λ�û�ϸ��������
�����ϸ����Χ�˸�λ����������������ϸ����
���λ�û�ϸ����Ȼ��
�����ϸ����Χ�˸�λ���г���������ϸ����
���λ�û�ϸ��������
�����ϸ����Χ������������ϸ�������λ����ϸ�����
���ݵ�ǰ״̬��дһ�����������������
ϸ������һ����һ�θ��º�ģ�״̬��
��һ��״̬��ͨ������������ͬʱӦ����
��ǰ״̬�µ�ÿ��ϸ�����γɵģ�
����ϸ���ĳ�����������ͬʱ�����ġ�
*/
void gameOfLife(int** board, int boardSize, int* boardColSize){
    int m = boardSize;
    int n = *boardColSize;
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

		int d[8][2] = {{0,1},{1,1},{1,0},{1,-1},
			{0,-1},{-1,-1},{-1,0},{-1,1}};
		 int sum = 0;
		for (int k = 0; k < 8; k++) {
			int nx = x + d[k][0];
			int ny = y + d[k][1];
			sum += midArr[nx][ny];
		}
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
int* profit, int profitSize, int* worker, int workerSize)
{
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
���� �ַ��� text �� �ַ����б� words,
�������е������� [i, j] ʹ���������Է�Χ�ڵ�
���ַ��� text[i]...text[j]������ i �� j�������ַ����б� words��

ʾ�� 1:

����: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
���: [[3,7],[9,13],[10,17]]
ʾ�� 2:

����: text = "ababa", words = ["aba","ab"]
���: [[0,1],[0,2],[2,3],[2,4]]
����:
ע�⣬���ص���Կ����н��棬
���磬"aba" ���� [0,2] ��Ҳ�� [2,4] ��
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

int** indexPairs(char * text, char ** words, int wordsSize,
	int* returnSize, int** returnColumnSizes){
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

    qsort(res, cnt, sizeof(res[0]), cmp); // ��άָ����������
    *returnSize = cnt;
    returnColumnSizes[0] = (int *)malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; i++) {
        returnColumnSizes[0][i] = 2;
    }
    return res;
}

/*
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
bool splitArray(int* nums, int numsSize){
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
����һ�������б���������� word1 �� word2��
�����б�������������֮�����̾��롣

ʾ��:
���� words = ["practice", "makes", "perfect", "coding", "makes"]

����: word1 = "coding", word2 = "practice"
���: 3
����: word1 = "makes", word2 = "coding"
���: 1

*/
int shortestDistance(char ** words, int wordsSize, char * word1, char * word2){
	int word1Record[wordsSize];
	int word2Record[wordsSize];
	int word1Cnt = 0;
	int word2Cnt = 0;
	int juli = wordsSize;

	if (words == NULL || wordsSize == 0 || word1 == NULL || word2 == NULL)
		return wordsSize;

	memset((void*)word1Record, 0, sizeof(word1Record));
	memset((void*)word2Record, 0, sizeof(word2Record));

	for(int i = 0; i < wordsSize; i++) {
		if (strcmp(words[i], word1) == 0) {
			word1Record[word1Cnt++] = i;
		} else if (strcmp(words[i], word2) == 0) {
			word2Record[word2Cnt++] = i;
		}
	}

	for(int i = 0; i < word1Cnt; i++) {
		for (int j = 0; j < word2Cnt;j++){
			juli = juli > abs(word2Record[j] - word1Record[i]) ?  abs(word2Record[j] - word1Record[i]) : juli;
		}
	}

	return juli;
}
/*
����һ�������б���������� word1 �� word2��
�����б�������������֮�����̾��롣

word1 �� word2 ���п�����ͬ�ģ�
�������ǽ��ֱ��ʾΪ�б������������ĵ��ʡ�

ʾ��:
���� words = ["practice", "makes", "perfect", "coding", "makes"].

����: word1 = "makes", word2 = "coding"
���: 1
����: word1 = "makes", word2 = "makes"
���: 3

*/
int shortestWordDistance(char ** words, int wordsSize, char * word1, char * word2){

	if (words == NULL || wordsSize == 0 || word1 == NULL || word2 == NULL)
		return 0;

	int word1L[wordsSize];
	int word2L[wordsSize];
	int cnt1 = 0;
	int cnt2 = 0;
	int min = 0xFFFF;

	memset((void*)word1L, 0 ,sizeof(word1L));
	memset((void*)word2L, 0, sizeof(word2L));

	for (int i = 0; i < wordsSize; i++) {
		if (strcmp(words[i],word1) == 0) {
			word1L[cnt1++] = i;
		}

		if (strcmp(words[i],word2) == 0) {
			word2L[cnt2++] = i;
		}
	}

	for (int i = 0; i < cnt1; i++) {
		for (int j = 0; j < cnt2; j++) {
			if (word1L[i] !=  word2L[j])
				min = min > abs(word1L[i] - word2L[j]) ? abs(word1L[i] - word2L[j]) : min;
		}
	}

	return min;
}
/*
����һ���ڰ�������ɵ�ͼ��, �����ɫ�¶����ص�������

ͼ����һ����'B'��'W'��ɶ�ά�ַ������ʾ, 'B'��'W'�ֱ�����ɫ���غͰ�ɫ���ء�

��ɫ�¶�����ָ������ͬһ�к�ͬһ�в�����������ɫ���صĺ�ɫ���ء�

ʾ��:

����:
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

���: 3
����: ȫ������'B'���Ǻ�ɫ�¶����ء�

*/
int findLonelyPixel(char** picture, int pictureSize, int* pictureColSize){
	int line[pictureSize];
	int row_size = 0;
	int cnt = 0;

	for(int i = 0; i < pictureSize; i++) {
		row_size = row_size < pictureColSize[i] ? pictureColSize[i] : row_size;
	}

	int row[row_size];

	memset((void*)line, 0 ,sizeof(line));
	memset((void*)row, 0 , sizeof(row));

	for(int i = 0; i < pictureSize; i++) {
		for (int j = 0; j < pictureColSize[i]; j++) {
			if (picture[i][j] == 'B') {
				line[i]++;
				row[j]++;
			}
		}
	}

	for(int i = 0; i < pictureSize; i++) {
		for (int j = 0; j < pictureColSize[i]; j++) {

			if (picture[i][j] == 'B' && line[i] == 1 && row[j] == 1) {
				cnt++;
			}
		}
	}

    return cnt;
}


/*
����һ����������� nums, �������� ԭ��
���ź�ʹ�� nums[0] <= nums[1] >= nums[2] <= nums[3]...��

ʾ��:

����: nums = [3,5,2,1,6,4]
���: һ�����ܵĽ���� [3,5,1,6,2,4]

*/
void wiggleSort(int* nums, int numsSize){
	bool flag = true;
	for(int i = 0; i + 1 < numsSize; i++){
		if (flag == true) {
			if (nums[i] > nums[i + 1]) {
				swap(*(nums + i), *(nums + i + 1));
			}
		}else {
			if (nums[i] < nums[i + 1]) {
				swap(*(nums + i), *(nums + i + 1));
			}
		}

		flag = !flag;
	}
}


/*
����һ������ʱ�䰲�ŵ����飬
ÿ������ʱ�䶼�������ʼ�ͽ�����ʱ��
[[s1,e1],[s2,e2],...] (si < ei)��Ϊ��������ͻ��
ͬʱҪ���ǳ�����û�������Դ��
�������������Ҫ���ټ�����ң�
����������Щ���鰲�š�

ʾ�� 1:

����: [[0, 30],[5, 10],[15, 20]]
���: 2
ʾ�� 2:

����: [[7,10],[2,4]]
���: 1


����
ֱ��

�ṩ�����ǵĻ���ʱ�����ȷ��һ���������¼���ʱ��˳�������õ���ÿ������Ŀ�ʼ�ͽ���ʱ�䣬�����������Ƕ����˳��

���ݻ���Ŀ�ʼʱ�������Ż��������������˽���Щ�������Ȼ˳��Ȼ��������֪������Ŀ�ʼʱ�䣬�������Ը������ǻ���ĳ���ʱ�䡣���ǻ���Ҫ���ս���ʱ��������飬��Ϊһ��"�������"�¼��������Ǳ�Ȼ�ж�Ӧ��"���鿪ʼ"�¼�������Ҫ���ǣ�"�������"�¼����Ը������ǣ�һ��֮ǰ��ռ�õĻ��������ڿ����ˡ�

һ���������俪ʼ�ͽ���ʱ�䶨�塣Ȼ�����ڱ��㷨�У�������Ҫ �ֱ� ����ʼʱ��ͽ���ʱ�䡣��էһ�����ܲ�̫�����Ͼ���ʼ�ͽ���ʱ�䶼�ǻ����һ���֣�������ǽ��������Է��벢�ֱ��������������ݾ���ʧ�ˡ����ǣ���������ʵ�ǿ�ȡ�ģ���Ϊ��

����������"�������"�¼�ʱ����ζ��һЩ���翪ʼ�Ļ����Ѿ����������ǲ������ĵ������ĸ������������������Ҫ��ֻ�� һЩ �������,�Ӷ��ṩһ���շ��䡣

������һ������ʹ�õİ����� Ҫ���ǵĻ���Ϊ�� (1, 10), (2, 7), (3, 19), (8, 12), (10, 20), (11, 30)����֮ǰ��������һ��ͼ˵��ǰ��������˴˳�ͻ����Ҫ�ֱ���䷿�䡣


�㷨

�ֱ𽫿�ʼʱ��ͽ���ʱ�����������顣
�ֱ�Կ�ʼʱ��ͽ���ʱ�����������ע�⣬�⽫���ҿ�ʼʱ��ͽ���ʱ���ԭʼ��Ӧ��ϵ�����ǽ����ֱ���
��������ָ�룺 s_ptr �� e_ptr���ֱ����ʼָ��ͽ���ָ�롣��ʼָ�����ÿ�����飬����ָ��������Ǹ��ٻ����Ƿ������
������ s_ptr ָ����ض�����ʱ�����ÿ�ʼʱ���Ƿ���� e_ptr ָ��Ļ��顣����ˣ���˵�� s_ptr ��ʼʱ���Ѿ��л���������������ǿ������÷��䡣�������Ǿ���Ҫ���·��䡣
���л��������������֮�� start[s_ptr] >= end[e_ptr]�������� e_ptr��
�ظ���һ���̣�ֱ�� s_ptr ���������л��顣

*/
int minMeetingRooms(int** intervals, int intervalsSize, int* intervalsColSize){
	if (intervals ==  NULL || intervalsSize <= 0 || intervalsColSize == NULL)
		return 0;

	int startArr[intervalsSize];
	int endArr[intervalsSize];

	for (int i = 0; i < intervalsSize; i++) {
		startArr[i] = intervals[i][0];
		endArr[i] = intervals[i][1];
	}

	qsort(startArr,sizeof(startArr)/sizeof(startArr[0]),sizeof(startArr[0]),cmp_int);
	qsort(endArr,sizeof(endArr)/sizeof(endArr[0]),sizeof(endArr[0]),cmp_int);

	// The two pointers in the algorithm: e_ptr and s_ptr.
	  int startPointer = 0, endPointer = 0;

	    // Variables to keep track of maximum number of rooms used.
	    int usedRooms = 0;

	    // Iterate over intervals.
	    while (startPointer < intervalsSize) {

	      // If there is a meeting that has ended by the time the meeting at `start_pointer` starts
	      if (startArr[startPointer] >= endArr[endPointer]) {
		        usedRooms -= 1;
		        endPointer += 1;
	      }

	      // We do this irrespective of whether a room frees up or not.
	      // If a room got free, then this used_rooms += 1 wouldn't have any effect. used_rooms would
	      // remain the same in that case. If no room was free, then this would increase used_rooms
	      usedRooms += 1;
	      startPointer += 1;

	    }

	    return usedRooms;
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


