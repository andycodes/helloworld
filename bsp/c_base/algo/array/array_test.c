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
548. 将数组分割成和相等的子数组
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
/*固定j，前后分别遍历i和k，其中j前后总和的差超过最大和最小的差就剪枝掉*/
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
41. 缺失的第一个正数
难度困难703
给你一个未排序的整数数组，请你找出其中没有出现的最小
的正整数。

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
717. 1比特与2比特字符
难度简单136
有两种特殊字符。第一种字符可以用一比特0来表示。第二
种字符可以用两比特(10 或 11)来表示。
现给一个由若干比特组成的字符串。问最后一个字符是否
必定为一个一比特字符。给定的字符串总是由0结束。
示例 1:
输入:
bits = [1, 0, 0]
输出: True
解释:
唯一的编码方式是一个两比特字符和一个一比特字符。
所以最后一个字符是一比特字符。
*/

/*
我们可以对 \mathrm{bits}bits 数组从左到右扫描来判断最后一位是否为一比特字符。当扫描到第 ii 位时，如果 \mathrm{bits}[i]=1bits[i]=1，那么说明这是一个两比特字符，将 ii 的值增加 2。如果 \mathrm{bits}[i]=0bits[i]=0，那么说明这是一个一比特字符，将 ii 的值增加 1。如果 ii 最终落在了 \mathrm{bits}.\mathrm{length}-1bits.length?1 的位置，那么说明最后一位一定是一比特字符。作者：LeetCode链接：https://leetcode-cn.com/problems/1-bit-and-2-bit-characters/solution/1bi-te-yu-2bi-te-zi-fu-by-leetcode/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
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
// 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率
应该相同。
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
1233. 删除子文件夹
难度中等24
你是一位系统管理员，手里有一份文件夹列表 folder，你的任
务是要删除该列表中的所有 子文件夹，并以 任意顺序 返
回剩下的文件夹。
我们这样定义「子文件夹」：
"	如果文件夹 folder[i] 位于另一个文件夹 folder[j] 下，那么 folder[i]
就是 folder[j] 的子文件夹。
文件夹的「路径」是由一个或多个按以下格式串联形成的
字符串：
"	/ 后跟一个或者多个小写英文字母。
例如，/leetcode 和 /leetcode/problems 都是有效的路径，而空字符串
和 / 不是。

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
128. 最长连续序列
难度困难487
给定一个未排序的整数数组，找出最长连续序列的长度。
要求算法的时间复杂度为 O(n)。
示例:
输入: [100, 4, 200, 1, 3, 2]
输出: 4
解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。

*/

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

/*
30. 串联所有单词的子串
给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰
好可以由 words 中所有单词串联形成的子串的起始位置。
注意子串要与 words 中的单词完全匹配，中间不能有其他字
符，但不需要考虑 words 中单词串联的顺序。
示例 1：
输入：
  s = "barfoothefoobarman",
  words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。
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
723. 粉碎糖果
这个问题是实现一个简单的消除算法。
给定一个二维整数数组 board 代表糖果所在的方格，不同的
正整数 board[i][j] 代表不同种类的糖果，如果 board[i][j] = 0 代表 (i, j)
这个位置是空的。给定的方格是玩家移动后的游戏状态，
现在需要你根据以下规则粉碎糖果，使得整个方格处于稳
定状态并最终输出。
如果有三个及以上水平或者垂直相连的同种糖果，同一时
间将它们粉碎，即将这些位置变成空的。
在同时粉碎掉这些糖果之后，如果有一个空的位置上方还
有糖果，那么上方的糖果就会下落直到碰到下方的糖果或
者底部，这些糖果都是同时下落，也不会有新的糖果从顶
部出现并落下来。
通过前两步的操作，可能又会出现可以粉碎的糖果，请继
续重复前面的操作。
当不存在可以粉碎的糖果，也就是状态稳定之后，请输出
最终的状态。
你需要模拟上述规则并使整个方格达到稳定状态，并输出。
样例 :
输入:
board =
[[110,5,112,113,114],[210,211,5,213,214],[310,311,3,313,314],[410,411,412,5,414],
[5,1,512,3,3],[610,4,1,613,614],[710,1,2,713,714],[810,1,2,1,1],[1,1,2,2,2],[4,1,4,4,1014]]
输出:
[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[110,0,0,0,114],[210,0,0,0,214],[310,0,0,113,314],
[410,0,0,213,414],[610,211,112,313,614],[710,311,412,613,714],[810,411,512,713,1014]]
*/

int** candyCrush(int** board, int boardSize, int* boardColSize,
int* returnSize, int** returnColumnSizes)
{
	int rows = boardSize, cols = *boardColSize;
	bool todo = false;   // 是否存在要粉碎的糖果

	// 一行一行扫描
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c + 2 < cols; ++c) {
			// 取出这个点的绝对值（可能被取反了，所以要绝对值）
			int v = abs(board[r][c]);
			// 如果连续三个格子是相同的糖果
			if (v != 0 && v == abs(board[r][c + 1]) && v == abs(board[r][c + 2])) {
				// 把这三个连续格子的糖果数值取反，
				//表明待粉碎状态
				board[r][c] = board[r][c + 1] = board[r][c + 2] = -v;
				todo = true;
			}
		}
	}

	// 一列一列扫描
	for (int r = 0; r + 2 < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			// 取出这个点的绝对值（可能被取反了，
			//所以要绝对值）
			int v = abs(board[r][c]);
			// 如果连续三个格子是相同的糖果
			if (v != 0 && v == abs(board[r + 1][c]) && v == abs(board[r + 2][c])) {
				// 把这三个连续格子的糖果数值取反，
				//表明待粉碎状态
				board[r][c] = board[r + 1][c] = board[r + 2][c] = -v;
				todo = true;
			}
		}
	}

/*
经过上面两个 for 循环后，需要粉碎糖果的格子已经变为负数
遍历所有格子进行粉碎糖果
*/
	if (todo) {
		for (int c = 0; c < cols; ++c) {   // 从左到右每一列
			int wr = rows - 1;  // 接收掉落糖果所在行
			for (int r = rows - 1; r >= 0; r--) {  // 从下往上遍历每一行
				if (board[r][c] > 0) {
					// 把 (r,c) 的糖果掉落到 (wr,c) 上
					// r 和 wr 要么在同一行，要么 r 在上面，
					//因此不用特地找到 wr 的初始行。
					board[wr][c] = board[r][c];
					wr--;   // 往上走一行
				}
			}
			// 如果 wr 没有走到最顶行，说明上面应该全是要粉碎的
			while (wr >= 0) {
				board[wr--][c] = 0;
			}
		}
	}
	// 如果还有需要粉碎的糖果，则再调用一次 candyCrush(board)
	// 注意，本次 candyCrush 后是不确定存不存在新的要粉碎的糖果，只能再调用一次 candyCrush
	// 如果多调用的 candyCrush 中两个 for 循环都没有把 tod0 标记为 true，则表示结束了
	// 因此，本方法都会多调用一次 candyCrush 但不进行粉碎的操作。

	*returnColumnSizes = boardColSize;
	*returnSize = boardSize;
	return todo ?
	candyCrush(board, boardSize, boardColSize, returnSize, returnColumnSizes) : board;
}


/*
48. 旋转图像
给定一个 n × n 的二维矩阵表示一个图像。
将图像顺时针旋转 90 度。
说明：
你必须在原地旋转图像，这意味着你需要直接修改输入的
二维矩阵。请不要使用另一个矩阵来旋转图像。
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

/*
先沿右上 - 左下的对角线翻转（270° +270°+ 一次镜像），再沿水平中线上下翻转（-180° +?180°+ 一次镜像），可以实现顺时针 9090 度的旋转效果作者：ChopinXBP链接：https://leetcode-cn.com/problems/rotate-image/solution/zi-wai-xiang-nei-shun-shi-zhen-xun-huan-jiao-huan-/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
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
54. 螺旋矩阵
难度中等446
给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时
针螺旋顺序，返回矩阵中的所有元素。
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

//画地为牢+步步紧逼
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
59. 螺旋矩阵 II
难度中等219
给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素
按顺时针顺序螺旋排列的正方形矩阵。
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
628. 三个数的最大乘积
给定一个整型数组，在数组中找出由三个数组成的最大乘积，并输出这个乘积。

示例 1:

输入: [1,2,3]
输出: 6
示例 2:

输入: [1,2,3,4]
输出: 24
*/
int maximumProduct(int* nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	return fmax(nums[0] * nums[1] * nums[numsSize - 1], nums[numsSize - 1] * nums[numsSize - 2] * nums[numsSize - 3]);

}

/*
1074. 元素和为目标值的子矩阵数量
给出矩阵 matrix 和目标值 target，返回元素总和等于目标值的非空子矩阵的数量。

子矩阵 x1, y1, x2, y2 是满足 x1 <= x <= x2 且 y1 <= y <= y2 的所有单元 matrix[x][y] 的集合。

如果 (x1, y1, x2, y2) 和 (x1', y1', x2', y2') 两个子矩阵中部分坐标不同（如：x1 != x1'），那么这两个子矩阵也不同。



示例 1：

输入：matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
输出：4
解释：四个只含 0 的 1x1 子矩阵。
*/
int preSum[301][301];
int getSum(int x1,int y1,int x2,int y2)//返回指定左上角和右下角的矩阵元素和
{
    return preSum[x2][y2]-preSum[x1-1][y2]-preSum[x2][y1-1]+preSum[x1-1][y1-1];
}

int numSubmatrixSumTarget(int** matrix, int matrixSize, int* matrixColSize, int target){
    memset(preSum,0,sizeof(preSum));
    int r=matrixSize;
    int c=matrixColSize[0];
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)//构造前缀和数组，注意这里和下面的四重循环都是以1为起点而不是0
            preSum[i][j]=preSum[i-1][j]+preSum[i][j-1]-preSum[i-1][j-1]+matrix[i-1][j-1];
    int count=0;//记录符合条件的矩阵个数
    for(int i=1;i<=r;i++)
    {
        for(int j=i;j<=r;j++)
        {
            for(int k=1;k<=c;k++)
            {
                for(int l=k;l<=c;l++)//四重循环冲！
                {
                    if(getSum(i,k,j,l)==target)
                        count++;
                }
            }
        }
    }
    return count;
}