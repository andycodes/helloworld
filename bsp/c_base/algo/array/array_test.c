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


/*
915. �ָ�����
�Ѷ��е�40
����һ������ A�����仮��Ϊ�������ཻ��û�й���Ԫ�أ�
������������ left �� right�� ʹ�ã�
"	left �е�ÿ��Ԫ�ض�С�ڻ���� right �е�ÿ��Ԫ�ء�
"	left �� right ���Ƿǿյġ�
"	left Ҫ������С��
����������ķ���󷵻� left �ĳ��ȡ����Ա�֤��������
�Ļ��ַ�����

ʾ�� 1��
���룺[5,0,3,8,6]
�����3
����
*/
int partitionDisjoint(int* A, int ASize)
{
	int leftMax[ASize];
	int rightMin[ASize];

	leftMax[0] = A[0];
	for (int i = 1; i < ASize; i++) {
		leftMax[i] = fmax(leftMax[i - 1], A[i]);
	}

	rightMin[ASize - 1] = A[ASize - 1];
	for (int i = ASize - 2; i >= 0; i--) {
		rightMin[i] = fmin(rightMin[i + 1], A[i]);
	}

	for (int i = 0; i < ASize - 1; i++) {
		if (leftMax[i] <= rightMin[i + 1])
			return i + 1;
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
	int* returnSize, int** returnColumnSizes)
{
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
313. ��������
�Ѷ��е�80
��дһ�γ��������ҵ� n ������������
����������ָ���������������ǳ���Ϊ k �������б� primes �е���������
ʾ��:
����: n = 12, primes = [2,7,13,19]
���: 32
����: ��������Ϊ 4 �������б� primes = [2,7,13,19]��ǰ 12 ��������������Ϊ��[1,2,4,7,8,13,14,16,19,26,28,32] ��
˵��:
"	1 ���κθ��� primes �ĳ���������
"	 ���� primes �е��������������С�
"	0 < k �� 100, 0 < n �� 106, 0 < primes[i] < 1000 ��
*/

/*
 * @lc app=leetcode.cn id=313 lang=c
 *
 * [313] ��������
 */

// @lc code=start

//���㷨˼·����ѧ�������Ĺ��췽����
int nthSuperUglyNumber(int n, int* primes, int primesSize){
    if(n == 1)
    {
        return 1;
    }

    int *res = (int *)calloc(n, sizeof(int));
    int rsize = 0;

    int *pids = (int *)calloc(primesSize, sizeof(int));

    res[rsize++] = 1;

    while(rsize < n)
    {
        // ѡ����С��(����*res[pid])��������pid
        int min = INT_MAX;
        int id = 0;

        for(int i = 0; i < primesSize; i++)
        {
            int tmin = primes[i] * res[ pids[i] ];

            if(tmin < min)
            {
                min = tmin;
                id = i;
            }
            // ȥ���ظ�
            else if(tmin == min)
            {
                pids[i]++;
            }
        }

        res[rsize++] = min;
        pids[id]++;
    }

    return res[n - 1];
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
48. ��תͼ��
����һ�� n �� n �Ķ�ά�����ʾһ��ͼ��

��ͼ��˳ʱ����ת 90 �ȡ�

˵����

�������ԭ����תͼ������ζ������Ҫֱ���޸�����Ķ�ά�����벻Ҫʹ����һ����������תͼ��

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
void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
    int n = matrixSize;

    // transpose matrix
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        int tmp = matrix[j][i];
        matrix[j][i] = matrix[i][j];
        matrix[i][j] = tmp;
      }
    }
    // reverse each row
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n / 2; j++) {
        int tmp = matrix[i][j];
        matrix[i][j] = matrix[i][n - j - 1];
        matrix[i][n - j - 1] = tmp;
      }
    }
}


void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
        int n = matrixSize;
        for(int i = 0; i < (n >> 1); ++i){
            for(int j = i; j < n - 1 - i; ++j){
                swap(matrix[i][j], matrix[j][n - 1 - i]);
                swap(matrix[i][j], matrix[n - 1 - i][n - 1 - j]);
                swap(matrix[i][j], matrix[n - 1 - j][i]);
            }
        }
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
int distanceBetweenBusStops(int* distance, int distanceSize, int start, int destination){
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
����һ��δ������������飬�����ҳ�����û�г��ֵ���С����������

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

int firstMissingPositive(int* nums, int numsSize) {
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

int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; ++i) {
        while (nums[i] > 0 && nums[i] <= numsSize &&
               nums[nums[i] - 1] != nums[i]) {
            int t = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i], nums[i] = t;
        }
    }
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return numsSize + 1;
}

/*
717. 1������2�����ַ�
�Ѷȼ�136
�����������ַ�����һ���ַ�������һ����0����ʾ���ڶ����ַ�������������(10 �� 11)����ʾ��
�ָ�һ�������ɱ�����ɵ��ַ����������һ���ַ��Ƿ�ض�Ϊһ��һ�����ַ����������ַ���������0������
ʾ�� 1:
����:
bits = [1, 0, 0]
���: True
����:
Ψһ�ı��뷽ʽ��һ���������ַ���һ��һ�����ַ����������һ���ַ���һ�����ַ���

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

// �������� [1,2,3] �����ؽ�����κ� [1,2,3]�����з��صĸ���Ӧ����ͬ��
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

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int randomInt(int min, int max){
    int ret = rand() % (max - min + 1) + min;
    return ret;
}

Solution* solutionCreate(int* nums, int numsSize) {
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
int* solutionReset(Solution* obj, int* retSize) {
    *retSize = obj->size;
    for(int i = 0; i < *retSize; i++){
        obj->array[i] = obj->origin[i];
    }
    return obj->array;
}

/** Returns a random shuffling of the array. */
int* solutionShuffle(Solution* obj, int* retSize) {
    *retSize = obj->size;
    int swapIndex;
    //srand(time(NULL));
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
����һλϵͳ����Ա��������һ���ļ����б� folder�����������Ҫɾ�����б��е����� ���ļ��У����� ����˳�� ����ʣ�µ��ļ��С�
�����������塸���ļ��С���
"	����ļ��� folder[i] λ����һ���ļ��� folder[j] �£���ô folder[i] ���� folder[j] �����ļ��С�
�ļ��еġ�·��������һ�����������¸�ʽ�����γɵ��ַ�����
"	/ ���һ�����߶��СдӢ����ĸ��
���磬/leetcode �� /leetcode/problems ������Ч��·���������ַ����� / ���ǡ�

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
54. ��������
�Ѷ��е�446
����һ������ m x n ��Ԫ�صľ���m ��, n �У����밴��˳ʱ������˳�򣬷��ؾ����е�����Ԫ�ء�
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
        int *order = (int *)calloc(total, sizeof(int));

        int row = 0, column = 0;
        int directionIndex = 0;
        for (int i = 0; i < total; i++) {
            order[i] = matrix[row][column];
            visited[row][column] = true;
            int nextRow = row + directions[directionIndex][0];
			int nextColumn = column + directions[directionIndex][1];
            if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns || visited[nextRow][nextColumn]) {
                directionIndex = (directionIndex + 1) % 4;
            }
            row += directions[directionIndex][0];
            column += directions[directionIndex][1];
        }
        *returnSize = total;
        return order;
}

int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	if (matrix == NULL || matrixSize <= 0 || matrixColSize == NULL) {
		*returnSize = 0;
		return NULL;
	}

        int rows = matrixSize, columns = *matrixColSize;
        int *order = (int *)calloc(rows * columns, sizeof(int));
	int orderCnt = 0;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) {
                order[orderCnt++] = matrix[top][column];
            }
            for (int row = top + 1; row <= bottom; row++) {
                order[orderCnt++] = matrix[row][right];
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    order[orderCnt++] = matrix[bottom][column];
                }
                for (int row = bottom; row > top; row--) {
                    order[orderCnt++] = matrix[row][left];
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
		*returnSize = orderCnt;
        return order;
}

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	if (matrix == NULL || matrixSize <= 0 || matrixColSize == NULL) {
		return NULL;
	}

	int row = matrixSize;
	int col = *matrixColSize;
	int *ans = (int *)calloc(row * col, sizeof(int));
	*returnSize = 0;

        int u = 0; //��ֵ�������ұ߽�
        int d = row - 1;
        int l = 0;
        int r = col - 1;
        while(true)
        {
            for(int i = l; i <= r; ++i) {
				ans[*returnSize] = matrix[u][i]; //�����ƶ�ֱ������
				(*returnSize)++;
			}
		if(++ u > d) break; //�����趨�ϱ߽磬���ϱ߽�����±߽磬�����������ɣ���ͬ
            for(int i = u; i <= d; ++i) {
				ans[*returnSize] = matrix[i][r]; //����
(*returnSize)++;
			}
	if(-- r < l) break; //�����趨�б߽�
            for(int i = r; i >= l; --i) {ans[*returnSize] = matrix[d][i]; //����
(*returnSize)++;
			}

			if(-- d < u) break; //�����趨�±߽�
            for(int i = d; i >= u; --i) {
				ans[*returnSize] = matrix[i][l]; //����
				(*returnSize)++;
			}
            if(++ l > r) break; //�����趨��߽�
        }
        return ans;
    }



int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize)
{
    if(matrixSize==0){
        *returnSize = 0;
        return NULL;
    }
    int top = 0, bottom = matrixSize - 1, left = 0, right = *matrixColSize - 1;
    int totalElement = *matrixColSize * matrixSize;
    *returnSize = totalElement;
    int *res = (int *)malloc(sizeof(int) * totalElement);
    int m=0, n=0;
    int direction = 0;
    // 0:right   1:down   2:left   3:up
    for(int i=0; i<totalElement; i++){
        switch (direction)
        {
            case 0:
                res[i] = matrix[m][n];
                if(n==right){
                    top++;
                    direction = 1;
                    m++;
                }
                else{
                    n++;
                }
                break;
            case 1:
                res[i] = matrix[m][n];
                if(m==bottom){
                    right--;
                    direction=2;
                    n--;
                }
                else{
                    m++;
                }
                break;

            case 2:
                res[i] = matrix[m][n];
                if(n==left){
                    bottom--;
                    direction = 3;
                    m--;
                }
                else{
                    n--;
                }
                break;

            case 3:
                res[i] = matrix[m][n];
                if(m==top){
                    left++;
                    direction=0;
                    n++;
                }
                else{
                    m--;
                }
                break;

            default:
                break;
        }
    }
    return res;
}
/*
class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        if not matrix:return []

        x=y=0                                     # ����Ԫ��λ�ó�ʼ��
        res = []                                  # ��ʼ�����洢������ľ���Ԫ��
        dx = [ 0, 1, 0,-1]                        # �����ң��£�����
        dy = [ 1, 0,-1, 0]                        # ע����ͨ��ƽ������ϵ �Ǻ� ��ͬ
        di = 0                                    # ��ʼ���������
        visited = set()                           # ��ʼ�����ϣ��洢���߹�������
        m,n = len(matrix),len(matrix[0])          # ���������

        for i in range(m*n):                                     #
            res.append(matrix[x][y])                             # �洢�����������Ԫ��
            visited.add((x,y))                                   # �洢������������
            tx,ty = x+dx[di],y+dy[di]                            # �ȼ�¼��һ�����꣬�����ж���һ����ô��
            if 0<=tx<m and 0<=ty<n and (tx,ty) not in visited:   # �ж������Ƿ��������û�б�����
                x,y = tx,ty
            else:
                di = (di+1)%4                                    # �ı䷽����������ΪһȦ����ֹ��������Խ��
                x,y = x + dx[di],y+dy[di]                        # ��һ������
        return res
*/

//����Ϊ��+��������
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    if(!matrixSize) { *returnSize = 0; return NULL;}
    *returnSize = matrixSize * matrixColSize[0];
    int* nums = (int *)malloc(sizeof(int) * (*returnSize));
    int cur = 0, l = 0, t = 0, r = matrixColSize[0] - 1, b = matrixSize - 1;
    while(cur < *returnSize) {
        for(int i = l; cur < *returnSize && i <= r; i++) nums[cur++] = matrix[t][i]; t++;
        for(int i = t; cur < *returnSize && i <= b; i++) nums[cur++] = matrix[i][r]; r--;
        for(int i = r; cur < *returnSize && i >= l; i--) nums[cur++] = matrix[b][i]; b--;
        for(int i = b; cur < *returnSize && i >= t; i--) nums[cur++] = matrix[i][l]; l++;
    }
    return nums;
}

/*
59. �������� II
�Ѷ��е�219
����һ�������� n������һ������ 1 �� n2 ����Ԫ�أ���Ԫ�ذ�˳ʱ��˳���������е������ξ���
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
        while(num <= tar){
            for(int i = l; i <= r; i++) mat[t][i] = num++; // left to right.
            t++;
            for(int i = t; i <= b; i++) mat[i][r] = num++; // top to bottom.
            r--;
            for(int i = r; i >= l; i--) mat[b][i] = num++; // right to left.
            b--;
            for(int i = b; i >= t; i--) mat[i][l] = num++; // bottom to top.
            l++;
        }



		*returnSize = n;
        return mat;
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
int cmp_int(const void *a, const void *b)
{
	long int aa = *((int *)a);
	long int bb = *((int *)b);
	return (int)(aa -bb);
}
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

