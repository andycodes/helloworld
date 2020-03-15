#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "flag_type.h"
#include "../algo/math/math.h"
/*
一维数组的两种访问方式。
以int b[10]为例, int *p = b;。
b[0] 等同于 *(p+0);
b[9] 等同于 *(p+9);
b[i] 等同于 *(p+i)


二维数组作为参数传递给函数
有以下三种形式:
void Func(int array[3][10]);
void Func(int array[ ][10]);
void Func(int (*array)[10]);

int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
int(*p)[4];
括号中的*表明 p 是一个指针，它指向一个数组，
数组的类型为int [4]，
这正是 a 所包含的每个一维数组的类型。

p 指向的数据类型是int [4]，那么p+1就前进 4×4 = 16 个字节，
p-1就后退 16 个字节，这正好是数组 a 所包含的每
个一维数组的长度。也就是说，
p+1会使得指针指向二维数组的下一行，
p-1会使得指针指向数组的上一行。
数组名 a 在表达式中也会被转换为和 p 等价的指针！

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

	/*注意这个sizeof的大小*/
	printf("%ld\n", sizeof(*(p+1)));

	return 0;
}


/*
储存指针的数组
int *(p1[5]);  //指针数组，可以去掉括号直接写作 int *p1[5];
*/

/*
二维指针
int **a;

*/

/*
变长数组(variable-length array,VLA)(C99）
C99标准引入了变长数组，它允许使用变量定义数组各维
int quarters = 4;
int regions = 5;
double sales[quarters][regions]; //一个变长数组VAL

变长数组有一些限制：变长数组必须是自动存储类的，
意味着它们必须在函数内部或作为函数参数声明，
而且声明时不可以进行初始化。

C99标准规定，可以省略函数原型中的名称，
但是如果省略名称，则需要用星号来代替省略的维数:
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
给定一个数组 A，将其划分为两个不相交（没有公共元素）
的连续子数组 left 和 right， 使得：

left 中的每个元素都小于或等于 right 中的每个元素。
left 和 right 都是非空的。
left 要尽可能小。
在完成这样的分组后返回 left 的长度。
可以保证存在这样的划分方法。
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
289. 生命游戏
给定一个包含 m × n 个格子的面板，
每一个格子都可以看成是一个细胞。
每个细胞具有一个初始状态 live（1）即为活细胞，
或 dead（0）即为死细胞。每个细胞与其八个相邻位
置（水平，垂直，对角线）
的细胞都遵循以下四条生存定律：

如果活细胞周围八个位置的活细胞数少于两个，
则该位置活细胞死亡；
如果活细胞周围八个位置有两个或三个活细胞，
则该位置活细胞仍然存活；
如果活细胞周围八个位置有超过三个活细胞，
则该位置活细胞死亡；
如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
根据当前状态，写一个函数来计算面板上
细胞的下一个（一次更新后的）状态。
下一个状态是通过将上述规则同时应用于
当前状态下的每个细胞所形成的，
其中细胞的出生和死亡是同时发生的。
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

双指针

*/

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
给出 字符串 text 和 字符串列表 words,
返回所有的索引对 [i, j] 使得在索引对范围内的
子字符串 text[i]...text[j]（包括 i 和 j）属于字符串列表 words。

示例 1:

输入: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
输出: [[3,7],[9,13],[10,17]]
示例 2:

输入: text = "ababa", words = ["aba","ab"]
输出: [[0,1],[0,2],[2,3],[2,4]]
解释:
注意，返回的配对可以有交叉，
比如，"aba" 既在 [0,2] 中也在 [2,4] 中
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

    qsort(res, cnt, sizeof(res[0]), cmp); // 二维指针数组排序
    *returnSize = cnt;
    returnColumnSizes[0] = (int *)malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; i++) {
        returnColumnSizes[0][i] = 2;
    }
    return res;
}

/*
给定一个有 n 个整数的数组，
你需要找到满足以下条件的三元组 (i, j, k) ：

0 < i, i + 1 < j, j + 1 < k < n - 1
子数组 (0, i - 1)，(i + 1, j - 1)，(j + 1, k - 1)，
(k + 1, n - 1) 的和应该相等。
这里我们定义子数组 (L, R) 表示原数组
从索引为L的元素开始至索引为R的元素。



示例:

输入: [1,2,1,2,1,2,1]
输出: True
解释:
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
给定一个单词列表和两个单词 word1 和 word2，
返回列表中这两个单词之间的最短距离。

示例:
假设 words = ["practice", "makes", "perfect", "coding", "makes"]

输入: word1 = "coding", word2 = "practice"
输出: 3
输入: word1 = "makes", word2 = "coding"
输出: 1

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
给定一个单词列表和两个单词 word1 和 word2，
返回列表中这两个单词之间的最短距离。

word1 和 word2 是有可能相同的，
并且它们将分别表示为列表中两个独立的单词。

示例:
假设 words = ["practice", "makes", "perfect", "coding", "makes"].

输入: word1 = "makes", word2 = "coding"
输出: 1
输入: word1 = "makes", word2 = "makes"
输出: 3

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
给定一幅黑白像素组成的图像, 计算黑色孤独像素的数量。

图像由一个由'B'和'W'组成二维字符数组表示, 'B'和'W'分别代表黑色像素和白色像素。

黑色孤独像素指的是在同一行和同一列不存在其他黑色像素的黑色像素。

示例:

输入:
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

输出: 3
解析: 全部三个'B'都是黑色孤独像素。

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
给你一个无序的数组 nums, 将该数字 原地
重排后使得 nums[0] <= nums[1] >= nums[2] <= nums[3]...。

示例:

输入: nums = [3,5,2,1,6,4]
输出: 一个可能的解答是 [3,5,1,6,2,4]

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
给定一个会议时间安排的数组，
每个会议时间都会包括开始和结束的时间
[[s1,e1],[s2,e2],...] (si < ei)，为避免会议冲突，
同时要考虑充分利用会议室资源，
请你计算至少需要多少间会议室，
才能满足这些会议安排。

示例 1:

输入: [[0, 30],[5, 10],[15, 20]]
输出: 2
示例 2:

输入: [[7,10],[2,4]]
输出: 1


有序化
直觉

提供给我们的会议时间可以确定一天中所有事件的时间顺序。我们拿到了每个会议的开始和结束时间，这有助于我们定义此顺序。

根据会议的开始时间来安排会议有助于我们了解这些会议的自然顺序。然而，仅仅知道会议的开始时间，还不足以告诉我们会议的持续时间。我们还需要按照结束时间排序会议，因为一个"会议结束"事件告诉我们必然有对应的"会议开始"事件，更重要的是，"会议结束"事件可以告诉我们，一个之前被占用的会议室现在空闲了。

一个会议由其开始和结束时间定义。然而，在本算法中，我们需要 分别 处理开始时间和结束时间。这乍一听可能不太合理，毕竟开始和结束时间都是会议的一部分，如果我们将两个属性分离并分别处理，会议自身的身份就消失了。但是，这样做其实是可取的，因为：

当我们遇到"会议结束"事件时，意味着一些较早开始的会议已经结束。我们并不关心到底是哪个会议结束。我们所需要的只是 一些 会议结束,从而提供一个空房间。

考虑上一方法中使用的案例。 要考虑的会议为： (1, 10), (2, 7), (3, 19), (8, 12), (10, 20), (11, 30)。像之前那样，第一张图说明前三个会议彼此冲突，需要分别分配房间。


算法

分别将开始时间和结束时间存进两个数组。
分别对开始时间和结束时间进行排序。请注意，这将打乱开始时间和结束时间的原始对应关系。它们将被分别处理。
考虑两个指针： s_ptr 和 e_ptr，分别代表开始指针和结束指针。开始指针遍历每个会议，结束指针帮助我们跟踪会议是否结束。
当考虑 s_ptr 指向的特定会议时，检查该开始时间是否大于 e_ptr 指向的会议。若如此，则说明 s_ptr 开始时，已经有会议结束。于是我们可以重用房间。否则，我们就需要开新房间。
若有会议结束，换而言之， start[s_ptr] >= end[e_ptr]，则自增 e_ptr。
重复这一过程，直到 s_ptr 处理完所有会议。

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


