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


/*
915. 分割数组
难度中等40
给定一个数组 A，将其划分为两个不相交（没有公共元素）
的连续子数组 left 和 right， 使得：
"	left 中的每个元素都小于或等于 right 中的每个元素。
"	left 和 right 都是非空的。
"	left 要尽可能小。
在完成这样的分组后返回 left 的长度。可以保证存在这样
的划分方法。

示例 1：
输入：[5,0,3,8,6]
输出：3
解释
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


/*
825. 适龄的朋友
人们会互相发送好友请求，现在给定一个包含有他们年龄的数组，ages[i] 表示第 i 个人的年龄。

当满足以下条件时，A 不能给 B（A、B不为同一人）发送好友请求：

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
否则，A 可以给 B 发送好友请求。

注意如果 A 向 B 发出了请求，不等于 B 也一定会向 A 发出请求。而且，人们不会给自己发送好友请求。

求总共会发出多少份好友请求?



示例 1:

输入: [16,16]
输出: 2
解释: 二人可以互发好友申请。
示例 2:

输入: [16,17,18]
输出: 2
解释: 好友请求可产生于 17 -> 16, 18 -> 17.
示例 3:

输入: [20,30,100,110,120]
输出: 3
解释: 好友请求可产生于 110 -> 100, 120 -> 110, 120 -> 100.
*/
/*
计数想法不考虑遍历所有的 20000 个人，我们只考虑遍历所有的元组 (age, count) 表示在这个年纪有多少人。因为最多只有 120 个可能的年纪，这会是一个很快的提升。算法对于每个元组 (ageA, countA)，(ageB, countB)，如果条件满足对应的年纪，那么久将 countA * countB 加入发好友请求的人数。当 ageA == ageB 的时候我们就数多了：我们只有 countA * (countA - 1) 对好友请求，因为你不能和自己发送请求。作者：LeetCode链接：https://leetcode-cn.com/problems/friends-of-appropriate-ages/solution/gua-ling-de-peng-you-by-leetcode/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
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
957. N 天后的牢房
难度中等52
8 间牢房排成一排，每间牢房不是有人住就是空着。
每天，无论牢房是被占用或空置，都会根据以下规则进行更改：
"	如果一间牢房的两个相邻的房间都被占用或都是空的，那么该牢房就会被占用。
"	否则，它就会被空置。
（请注意，由于监狱中的牢房排成一行，所以行中的第一个和最后一个房间无法有两个相邻的房间。）
我们用以下方式描述监狱的当前状态：如果第 i 间牢房被占用，则 cell[i]==1，否则 cell[i]==0。
根据监狱的初始状态，在 N 天后返回监狱的状况（和上述 N 种变化）。

示例 1：
输入：cells = [0,1,0,1,1,0,0,1], N = 7
输出：[0,0,1,1,0,0,0,0]
解释：
下表概述了监狱每天的状况：
Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
Day 7: [0, 0, 1, 1, 0, 0, 0, 0]

示例 2：

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
	int cycle = 1; // 周期
	int cnt = 0;

	if ((cells == NULL) || (N < 1 || N > 1000000000))  return NULL;

	array = calloc(cellsSize, sizeof(int));
	temp  = calloc(cellsSize, sizeof(int));
	day1  = calloc(cellsSize, sizeof(int));
	if (array == NULL || temp == NULL || day1 == NULL)  return NULL;

	// 保存第一天变化
	for (i = 1; i < cellsSize-1; i++) {
	    day1[i] = (cells[i-1] == cells[i+1]) ? 1 : 0;
	    array[i] = day1[i];
	}

	// 找出循环周期
	while(true) {
	    for (i = 1; i < cellsSize-1; i++) {
	        temp[i] = (array[i-1] == array[i+1]) ? 1 : 0;
	    }
	    memcpy(array, temp, cellsSize * sizeof(int));

	    if (memcmp(array, day1, cellsSize * sizeof(int)) == 0)
			break;
	    cycle++;
	}

	// 计算周期内的变化
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
313. 超级丑数
难度中等80
编写一段程序来查找第 n 个超级丑数。
超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。
示例:
输入: n = 12, primes = [2,7,13,19]
输出: 32
解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
说明:
"	1 是任何给定 primes 的超级丑数。
"	 给定 primes 中的数字以升序排列。
"	0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000 。
*/

/*
 * @lc app=leetcode.cn id=313 lang=c
 *
 * [313] 超级丑数
 */

// @lc code=start

//【算法思路】数学。丑数的构造方法。
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
        // 选择最小的(素数*res[pid])，更新其pid
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
            // 去除重复
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
1414. 和为 K 的最少斐波那契数字数目
给你数字 k ，请你返回和为 k 的斐波那契数字的最少数目，其中，每个斐波那契数字都可以被使用多次。

斐波那契数字定义为：

F1 = 1
F2 = 1
Fn = Fn-1 + Fn-2 ， 其中 n > 2 。
数据保证对于给定的 k ，一定能找到可行解。
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
面试题 16.04. 井字游戏
设计一个算法，判断玩家是否赢了井字游戏。输入是一个
N x N 的数组棋盘，由字符" "，"X"和"O"组成，其中字符" "代表一
个空位。
以下是井字游戏的规则：
玩家轮流将字符放入空位（" "）中。
第一个玩家总是放字符"O"，且第二个玩家总是放字符"X"。
"X"和"O"只允许放置在空位中，不允许对已放有字符的位置进
行填充。
当有N个相同（且非空）的字符填充任何行、列或对角线时，游戏结束，对应该字符的玩家获胜。
当所有位置非空时，也算为游戏结束。
如果游戏结束，玩家不允许再放置字符。
如果游戏存在获胜者，就返回该游戏的获胜者使用的字符
（"X"或"O"）；如果游戏以平局结束，则返回 "Draw"；如果仍会
有行动（游戏未结束），则返回 "Pending"。

示例 1：

输入： board = ["O X"," XO","X O"]
输出： "X"
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
48. 旋转图像
给定一个 n × n 的二维矩阵表示一个图像。

将图像顺时针旋转 90 度。

说明：

你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

示例 1:

给定 matrix =
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

原地旋转输入矩阵，使其变为:
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
1184. 公交站间的距离
难度简单27
环形公交路线上有 n 个站，按次序从 0 到 n - 1 进行编号。我们已知每一对相邻公交站之间的距离，distance[i] 表示编号为 i 的车站和编号为 (i + 1) % n 的车站之间的距离。
环线上的公交车都可以按顺时针和逆时针的方向行驶。
返回乘客从出发点 start 到目的地 destination 之间的最短距离。

示例 1：

输入：distance = [1,2,3,4], start = 0, destination = 1
输出：1
解释：公交站 0 和 1 之间的距离是 1 或 9，最小值是 1。

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
41. 缺失的第一个正数
难度困难703
给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。

示例 1:
输入: [1,2,0]
输出: 3
示例 2:
输入: [3,4,-1,1]
输出: 2
示例 3:
输入: [7,8,9,11,12]
输出: 1


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
717. 1比特与2比特字符
难度简单136
有两种特殊字符。第一种字符可以用一比特0来表示。第二种字符可以用两比特(10 或 11)来表示。
现给一个由若干比特组成的字符串。问最后一个字符是否必定为一个一比特字符。给定的字符串总是由0结束。
示例 1:
输入:
bits = [1, 0, 0]
输出: True
解释:
唯一的编码方式是一个两比特字符和一个一比特字符。所以最后一个字符是一比特字符。

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
384. 打乱数组
难度中等85
打乱一个没有重复元素的数组。

示例:
// 以数字集合 1, 2 和 3 初始化数组。
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。
solution.shuffle();

// 重设数组到它的初始状态[1,2,3]。
solution.reset();

// 随机返回数组[1,2,3]打乱后的结果。
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
1233. 删除子文件夹
难度中等24
你是一位系统管理员，手里有一份文件夹列表 folder，你的任务是要删除该列表中的所有 子文件夹，并以 任意顺序 返回剩下的文件夹。
我们这样定义「子文件夹」：
"	如果文件夹 folder[i] 位于另一个文件夹 folder[j] 下，那么 folder[i] 就是 folder[j] 的子文件夹。
文件夹的「路径」是由一个或多个按以下格式串联形成的字符串：
"	/ 后跟一个或者多个小写英文字母。
例如，/leetcode 和 /leetcode/problems 都是有效的路径，而空字符串和 / 不是。

示例 1：
输入：folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
输出：["/a","/c/d","/c/f"]
解释："/a/b/" 是 "/a" 的子文件夹，而 "/c/d/e" 是 "/c/d" 的子文件夹。

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
54. 螺旋矩阵
难度中等446
给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。
示例 1:
输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]

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

        int u = 0; //赋值上下左右边界
        int d = row - 1;
        int l = 0;
        int r = col - 1;
        while(true)
        {
            for(int i = l; i <= r; ++i) {
				ans[*returnSize] = matrix[u][i]; //向右移动直到最右
				(*returnSize)++;
			}
		if(++ u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
            for(int i = u; i <= d; ++i) {
				ans[*returnSize] = matrix[i][r]; //向下
(*returnSize)++;
			}
	if(-- r < l) break; //重新设定有边界
            for(int i = r; i >= l; --i) {ans[*returnSize] = matrix[d][i]; //向左
(*returnSize)++;
			}

			if(-- d < u) break; //重新设定下边界
            for(int i = d; i >= u; --i) {
				ans[*returnSize] = matrix[i][l]; //向上
				(*returnSize)++;
			}
            if(++ l > r) break; //重新设定左边界
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

        x=y=0                                     # 矩阵元素位置初始化
        res = []                                  # 初始化，存储遍历后的矩阵元素
        dx = [ 0, 1, 0,-1]                        # 方向：右，下，左，上
        dy = [ 1, 0,-1, 0]                        # 注：与通常平面坐标系 记号 不同
        di = 0                                    # 初始化方向变量
        visited = set()                           # 初始化集合，存储已走过的坐标
        m,n = len(matrix),len(matrix[0])          # 矩阵的行列

        for i in range(m*n):                                     #
            res.append(matrix[x][y])                             # 存储遍历矩阵过的元素
            visited.add((x,y))                                   # 存储遍历过的坐标
            tx,ty = x+dx[di],y+dy[di]                            # 先记录下一步坐标，用于判断下一步怎么走
            if 0<=tx<m and 0<=ty<n and (tx,ty) not in visited:   # 判断坐标是否需变向，且没有遍历过
                x,y = tx,ty
            else:
                di = (di+1)%4                                    # 改变方向，右下左上为一圈，防止方向坐标越界
                x,y = x + dx[di],y+dy[di]                        # 下一步坐标
        return res
*/

//画地为牢+步步紧逼
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
59. 螺旋矩阵 II
难度中等219
给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。
示例:
输入: 3
输出:
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
128. 最长连续序列
难度困难487
给定一个未排序的整数数组，找出最长连续序列的长度。
要求算法的时间复杂度为 O(n)。
示例:
输入: [100, 4, 200, 1, 3, 2]
输出: 4
解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。

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

    // max 最终结果, curr 当前长度, last 上个数字
    int max = 1, curr = 1, last = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == last) continue;
        if (nums[i] == last + 1) curr++; // 符合连续，长度 +1
        else {
            max = fmax(max, curr); // 连不上了，记录长度
            curr = 1; // 重新开始
        }
        last = nums[i];
    }
    max = fmax(max, curr); // 别忘了最后一段的连续区间
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
        // 技巧：如果有比自己小一点的，那自己不查，让小的去查
	struct DataEntry *find = hashFindKey(ht, nums[i] - 1);
	if (find != NULL) {
		continue;
	}


        int r = nums[i]; // r: right 表示「以 v 开头，能连续到多少」
        while (hashFindKey(ht, r + 1)) r++; // 逐个查看
        max = fmax(max, r - nums[i] + 1); // 记录区间 [v, r] 长度
    }
    return max;
}

