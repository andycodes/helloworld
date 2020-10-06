/*
回溯法的基本思想：

针对所给问题，定义问题的解空间；
DFS 搜索解空间，并在搜索过程中用剪枝函数避免无效搜索。
在DFS的过程中发现不是问题的解，
那么就开始回溯到上一层或者上一个节点。

回溯法的代码套路是使用两个变量： res 和 path，
res 表示最终的结果，
path 保存已经走过的路径。
如果搜到一个状态满足题目要求，
就把 path 放到 res 中


result = []
def backtrack(路径, 选择列表):
    if 满足「结束条件」:
        result.add(「路径」)
        return

    for 选择 in 「选择列表」:  (类似N叉树)  当前层次
        #做选择
	 将该选择从选择列表移除
	 「路径」.add(选择)
        backtrack(路径, 选择列表)
        #撤销选择
        「路径」.remove(选择)
    	 将该选择再加入选择列表
*/

/*
子集:
子集问题的选择列表，是上一条选择路径之后的数,
递归进入下一层，注意i+1，标识下一个选择列表的开始位置，最重要的一步

组合:


全排列


搜索
*/


/*
剑指 Offer 38. 字符串的排列
难度中等49
输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，
但里面不能有重复元素。
示例:
输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]
*/
void backtrack(char* s, int slen, int* returnSize,
	char **res, char *path, int pathSize, bool *visited)
{
	if (pathSize == slen) {
		res[*returnSize] = strdup(path);
		(*returnSize)++;
		return;
	}

	for (int i = 0; i < slen; i++) {
		if (visited[i] == true) {
			continue;
		}

		if (i > 0 && visited[i - 1] == true && s[i - 1] == s[i]) {
			continue;
		}

		path[pathSize++] = s[i];
		visited[i] = true;

		backtrack(s, slen, returnSize, res, path, pathSize, visited);

		pathSize--;
		visited[i] = false;
	}
}

char** permutation(char* s, int* returnSize)
{
	int slen = strlen(s);
	qsort(s, slen, sizeof(s[0]), cmp_char);
	int kind = 1;
	for (int i = 2; i <= slen; i++) {
		kind *= i;
	}
	char **res = (char **)calloc(kind, sizeof(char *));
	char path[slen + 1];
	memset(path, 0, sizeof(path));
	bool visited[slen];
	memset(visited, false, sizeof(visited));
	*returnSize = 0;
	backtrack(s, slen, returnSize, res, path, 0, visited);
	return res;
}

/*
401. 二进制手表
二进制手表顶部有 4 个 LED 代表小时（0-11），
底部的 6 个 LED 代表分钟（0-59）。
每个 LED 代表一个 0 或 1，最低位在右侧。
例如，上面的二进制手表读取 "3:25"。
给定一个非负整数 n 代表当前 LED 亮着的数量，
返回所有可能的时间。
案例:
输入: n = 1
返回: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
*/

#define MAX_LEN 1024
int g_led[10] = { 8, 4, 2, 1, 32, 16, 8, 4, 2, 1 };

void Dft(int num, char **res, int *returnSize, int hour, int min, int pos)
{
    if (num == 0) {
        if (hour > 9) {
            res[*returnSize] = (char *)malloc(6 * sizeof(char));
        } else {
            res[*returnSize] = (char *)malloc(5 * sizeof(char));
        }
        if (min > 9) {
            sprintf(res[*returnSize], "%d:%d", hour, min);
        } else {
            sprintf(res[*returnSize], "%d:0%d", hour, min);
        }
        (*returnSize)++;
        return;
    }

    for (int i = pos; i < 10; i++) {
        if ((i < 4) && (hour + g_led[i] < 12)) {
            Dft(num - 1, res, returnSize, hour + g_led[i], min, i + 1);
        } else if ((i >= 4) && (min + g_led[i] < 60)) {
            Dft(num - 1, res, returnSize, hour, min + g_led[i], i + 1);
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **readBinaryWatch(int num, int *returnSize)
{
    char **res = (char **)malloc(MAX_LEN * sizeof(char *));
    *returnSize = 0;
    Dft(num, res, returnSize, 0, 0, 0);
    return res;
}


/*
面试题 08.02. 迷路的机器人
难度中等13
设想有个机器人坐在一个网格的左上角，网格 r 行 c 列。
机器人只能向下或向右移动，但不能走到一些被禁止的网格（
有障碍物）。设计一种算法，寻找机器人从左上角移动到右
下角的路径。
网格中的障碍物和空位置分别用 1 和 0 来表示。
返回一条可行的路径，路径由经过的网格的行号和列号组成。
左上角为 0 行 0 列。
示例 1:
输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: [[0,0],[0,1],[0,2],[1,2],[2,2]]
解释:
输入中标粗的位置即为输出表示的路径，即
0行
*/
bool backtrack(int** obstacleGrid, int row, int col, int cx, int cy,
int **res, int *returnSize,  bool visited[][100], int** returnColumnSizes)
{
	if(cx >= row || cy >= col || obstacleGrid[cx][cy] == 1 || visited[cx][cy])
		return false;

	visited[cx][cy] = 1;
	res[*returnSize] = (int *)calloc(2, sizeof(int));
	res[*returnSize][0] = cx;
	res[*returnSize][1] = cy;
	(*returnColumnSizes)[*returnSize] = 2;
	(*returnSize)++;

	if(cx == (row - 1) && cy == (col - 1)) {
		return true;
	}

	if (backtrack(obstacleGrid, row, col, cx, cy + 1, res, returnSize, visited, returnColumnSizes) ||
		backtrack(obstacleGrid, row, col, cx + 1, cy, res, returnSize, visited, returnColumnSizes)) {
		return true;
	}

	if (res[*returnSize] != NULL) {
		free(res[*returnSize]);
		res[*returnSize] = NULL;

	}

	(*returnSize)--;

	return false;
}

int** pathWithObstacles(int** obstacleGrid, int obstacleGridSize,
int* obstacleGridColSize, int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;
	int **res = (int **)calloc(200, sizeof(int *));
	bool visited[100][100];
	memset(visited, 0, sizeof(visited));
	*returnColumnSizes = (int *)calloc(200, sizeof(int));
    	int row = obstacleGridSize;
	int col = *obstacleGridColSize;
	bool  arrived = backtrack(obstacleGrid, row, col, 0, 0, res, returnSize, visited, returnColumnSizes);
	if(arrived == false) {
		*returnSize = 0;
	}

	return res;
}

/*
97. 交错字符串
难度困难319
给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。
示例 1：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出：true
示例 2：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出：false
*/
/*
带记忆化的回溯从暴力回溯可知，当i、j、k一定的情况下，
返回值一定，由此我们可以将i、j、k、返回值用meom[i][j][k]记录
起来，当回溯再次遇到此i、j、k时，直接返回。显然当i、j一
定时，k一定，因为k = i + j，因此，可以将状态缩减成两维，
即meom[i][j]。我们对上述暴力回溯进行改造，在回溯返回false的
地方用meom[i][j]记录下来，在返回true的地方不用记录，因为一
旦返回true，回溯就会一直返回，直到回溯入口。
*/
bool backtrack(char *s1, char * s2, char * s3, int i, int j, int k,
int size1, int size2, int dp[size1][size2])
{
	if (dp[i][j] != 13) {
		return dp[i][j];
	}

	// 若回溯用完了s1,s2,s3，说明能够s3能够被交替组成
	if(i == strlen(s1) && j == strlen(s2) && k == strlen(s3))
		return true;

	if(k >= strlen(s3)) {
		dp[i][j] = false;
		return false;
	}

	if(i < strlen(s1)) {
/*
若当前s1的i位置的字符与s3的k位置字符相等，则消耗一个字符，
并向下回溯，若回溯返回true则返回的这个true最开始一定
是由该函数内第二行代码返回的，
即表示s3能够被交替组成，直接返回true
*/
		if(s1[i] == s3[k] && backtrack(s1, s2, s3, i+1, j, k+1, size1, size2, dp))
			return true;
	}

	if(j < strlen(s2)){
		if(s2[j] == s3[k] && backtrack(s1, s2, s3, i, j+1, k+1,  size1, size2, dp))
			return true;
	}

	dp[i][j] = false;
/*
在此i、j、k下，无论如何都不能组成s3.substring(0, k+1),返回false
*/
	return false;
}

bool isInterleave(char* s1, char* s2, char* s3)
{
	if(s1 == NULL) s1 = "";
	if(s2 == NULL) s2 = "";
	if(s3 == NULL) s3 = "";

	int len1 = strlen(s1) + 1;
	int len2 = strlen(s2) + 1;
	int dp[len1][len2];
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			dp[i][j] = 13;
		}
	}

	return backtrack(s1, s2, s3, 0, 0, 0, len1, len2, dp);
}


/*
679. 24 点游戏
你有 4 张写有 1 到 9 数字的牌。你需要判断是否能通过 *，/，
+，-，(，) 的运算得到 24。
示例 1:
输入: [4, 1, 8, 7]
输出: True
解释: (8-4) * (7-1) = 24
示例 2:
输入: [1, 2, 1, 2]
输出: False
注意:
除法运算符 / 表示实数除法，而不是整数除法。
例如 4 / (1 - 2/3) = 12 。
每个运算符对两个数进行运算。特别是我们不能用 - 作为一
元运算符。例如，[1, 1, 1, 1] 作为输入时，表达式 -1 - 1 - 1 - 1 是不
允许的。
你不能将数字连接在一起。例如，输入为 [1, 2, 1, 2] 时，不能写
成 12 + 12 。
*/

typedef double (*ClacFunc) (double a, double b);
double Add(double a, double b) { return a + b; };
double Sub(double a, double b) { return a - b; };
double Mul(double a, double b) { return a * b; };
double Div(double a, double b) { return a / b; };

typedef struct {
    bool isSwap;    // 是否交换
    ClacFunc func;  // 函数
}CLAC;

#define CLAC_TYPE 4
static CLAC g_clacFunc[CLAC_TYPE] = {
    {0, Add},//交换一样
    {1, Sub},//交换不一样
    {0, Mul},
    {1, Div}
};

bool backtrack(double* nums, int size)
{
	if (size == 1) {
		return (fabs(nums[0] - 24) <= 1e-6);
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {//两两取数
			double newNums[3] = {0};
			int newSize = 0;

			for (int k = 0; k < size; k++) {//init
				if (k != i && k != j) {
					newNums[newSize++] = nums[k];
				}
			}

			for (int k = 0; k < CLAC_TYPE; k++) {
					bool isOK = false;
					if (g_clacFunc[k].isSwap) {
						newNums[newSize] = g_clacFunc[k].func(nums[j], nums[i]);
						isOK = backtrack(newNums, newSize + 1);
						if (isOK) {
							return true;
						}
					}

					newNums[newSize] = g_clacFunc[k].func(nums[i], nums[j]);
					isOK = backtrack(newNums, newSize + 1);
					if (isOK) {
						return true;
					}
			}
		}
	}

	return false;
}


bool judgePoint24(int* nums, int numsSize)
{
	if (nums == NULL || numsSize != 4) {
		return false;
	}

	double dnums[numsSize];
	for (int i = 0; i < numsSize; i++) {
		dnums[i] = nums[i];
	}

	return backtrack(dnums, numsSize);
}

/*
488. 祖玛游戏
难度困难54
回忆一下祖玛游戏。现在桌上有一串球，颜色有红色(R)，
黄色(Y)，蓝色(B)，绿色(G)，还有白色(W)。 现在你手里也有几
个球。
每一次，你可以从手里的球选一个，然后把这个球插入到一
串球中的某个位置上（包括最左端，最右端）。接着，如果
有出现三个或者三个以上颜色相同的球相连的话，就把它们
移除掉。重复这一步骤直到桌上所有的球都被移除。
找到插入并可以移除掉桌上所有球所需的最少的球数。如果
不能移除桌上所有的球，输出 -1 。
示例:
输入: "WRRBBW", "RB"
输出: -1
解释: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW （翻译者标注：
手上球已经用完，桌上还剩两个球无法消除，返回-1）

输入: "WWRRBBWW", "WRBRW"
输出: 2
解释: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty
*/

int backtrack(char * board, int *map)
{
	int blen = strlen(board);
	if (board == NULL || board[0] == '\0' ||blen <= 0) {
		return 0;
	}

	int i = 0;
	int ans = INT_MAX;

	while(i < blen) {
		int j = i;
		while( j < blen && (board[i] == board[j]))
			j++;

		int cnt = fmax(0, 3 - (j - i));
		if (map[board[i] - 'A'] >= cnt) {
			char newBoard[blen];
			memset(newBoard, 0, sizeof(newBoard));
			strncpy(newBoard, board, i);
			strcat(newBoard, board + j);
			map[board[i] - 'A'] -= cnt;
			int res = backtrack(newBoard, map);
			if (res >= 0)
				ans = fmin(ans, res + cnt);
			map[board[i] - 'A'] += cnt;
		}
		i++;
	}

	return ans == INT_MAX ? -1 :ans;
}

int findMinStep(char * board, char * hand)
{
	int map[26] = {0};
	int i = 0;

	while(hand[i] != '\0') {
		map[hand[i] - 'A']++;
		i++;
	}

	return backtrack(board, map);
}


/*
37. 解数独
难度困难497
编写一个程序，通过已填充的空格来解决数独问题。
一个数独的解法需遵循如下规则：
1.	数字 1-9 在每一行只能出现一次。
2.	数字 1-9 在每一列只能出现一次。
3.	数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。

*/

bool backtrack(char** board, bool rowVisited[9][10], bool colVisited[9][10],
bool boxVisited[3][3][10], int cx, int cy, int boardSize, int* boardColSize)
{
	// 边界校验, 如果已经填充完成, 返回true, 表示一切结束
	if(cy == *boardColSize) {
		cy = 0;
		cx++;
		if(cx == boardSize){
			return true;
		}
	}

	// 是空则尝试填充, 否则跳过继续尝试填充下一个位置
	if(board[cx][cy] == '.') {
		// 尝试填充1~9
		for(int num = 1; num <= 9; num++){
			bool canUsed = !(rowVisited[cx][num] || colVisited[cy][num] || boxVisited[cx/3][cy/3][num]);
			if(canUsed){
				rowVisited[cx][num] = true;
				colVisited[cy][num] = true;
				boxVisited[cx/3][cy/3][num] = true;

				board[cx][cy] = (char)('0' + num);
				if(backtrack(board, rowVisited, colVisited, boxVisited, cx, cy + 1, boardSize, boardColSize)){
					return true;
				}

				board[cx][cy] = '.';

				rowVisited[cx][num] = false;
				colVisited[cy][num] = false;
				boxVisited[cx/3][cy/3][num] = false;
			}
		}
	} else {
		return backtrack(board, rowVisited, colVisited, boxVisited, cx, cy + 1, boardSize, boardColSize);
	}

	return false;
}

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
	bool rowVisited[9][10];//0~9使用1~9
	bool colVisited[9][10];
	bool boxVisited[3][3][10];
	memset(rowVisited, 0, sizeof(rowVisited));
	memset(colVisited, 0, sizeof(colVisited));
	memset(boxVisited, 0, sizeof(boxVisited));

	// 初始化
	for(int cx = 0; cx < boardSize; cx++){
		for(int cy = 0; cy < *boardColSize; cy++) {
			int num = board[cx][cy] - '0';
			if(1 <= num && num <= 9) {
				rowVisited[cx][num] = true;
				colVisited[cy][num] = true;
				boxVisited[cx / 3][cy / 3][num] = true;
			}
		}
	}

	backtrack(board, rowVisited, colVisited, boxVisited, 0, 0, boardSize, boardColSize);
}

/*
10. 正则表达式匹配
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.'
和 '*' 的正则表达式匹配。
'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
说明:
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
*/
bool isMatch(char * s, char * p)
{
	if (!*p)
		return !*s;

	bool first_match = *s && (*s == *p || *p == '.');
	if (*(p+1) == '*') {
		return isMatch(s, p+2) || (first_match && isMatch(++s, p));
	}
	else {
		return first_match && isMatch(++s, ++p);
	}
}

int memo[100][100];
bool backtrack(char *s, char *p, int sIdx, int pIdx)
{
	if(s[sIdx] == '\0' && p[pIdx] == '\0')
		return true;//如果都遍历到最后说明匹配成功

	if(p[pIdx] == '\0')
		return false;//如果p字符串匹配到最后, 而s没有, 则匹配不成功

/*
记忆化, 判断当前位置是否被搜过, 是子直接返回当前结果, 省
去重复步骤
*/
	if(memo[sIdx][pIdx]!=-1)
		return memo[sIdx][pIdx];

	bool flag = false;//初始标记
	//首先判断该位置是否是点
	if(p[pIdx] == '.') {
/*
然后判断下一个是否是*, 如果是*, 则可以匹配s中的任意个不
同字符
*/
		if(p[pIdx+1] == '*') {
			//遍历s当前位置到末尾, 看是否能匹配成功
			for(int i = sIdx;i<=strlen(s);i++) {
				flag = backtrack(s, p, i, pIdx+2); //p是.*代替s, 所以加2
				if(flag == true)//如果能匹配直接停止
					break;
			}
		} else if(s[sIdx]!='\0') {//如果下一个不是*, 一个.只能匹配一个字符
			flag = backtrack(s, p, sIdx+1, pIdx+1);//p是.代替s一个字符, 所以各加1
		}
	} else if(p[pIdx+1] == '*') {//如果当前位置是字母, 下一个是*, *可以匹配0个或多个s中与当前字母一样的字符
		flag = backtrack(s, p, sIdx, pIdx+2);//当匹配0个的情况, p中字母+*代替s中0个字符
		if(flag == false) {//如果匹配不成功
			for(int i = sIdx;i<strlen(s);i++) {//遍历s当前位置到末尾, 看是否能匹配成功
				if(s[i] == p[pIdx])//即p中字母+*是否等价于s当前位置的字母, 是则进行下一位置的匹配
					flag = backtrack(s, p, i+1, pIdx+2);
				else//否则停止
					break;
				if(flag == true)//如果匹配成功停止
					break;
			}
		}
	} else if(s[sIdx] == p[pIdx]) {//在以上情况不满足的情况下, 如果两字符相等, 则遍历下一位置
		flag = backtrack(s, p, sIdx+1, pIdx+1);
	}

	//其他情况皆为false
	memo[sIdx][pIdx] = flag;//记忆化存储
	return flag;
}

bool isMatch(char * s,  char * p)
{
	memset(memo, -1, sizeof(memo));//设-1为未访问过
	return backtrack(s, p, 0, 0);
}


/*
351. 安卓系统手势解锁
我们都知道安卓有个手势解锁的界面，是一个 3 x 3 的点所绘
制出来的网格。
给你两个整数，分别为 ??m 和 n，其中 1 ≤ m ≤ n ≤ 9，那么请
你统计一下有多少种解锁手势，是至少需要经过 m 个点，
但是最多经过不超过 n 个点的。
先来了解下什么是一个有效的安卓解锁手势:
每一个解锁手势必须至少经过 m 个点、最多经过 n 个点。
解锁手势里不能设置经过重复的点。
假如手势中有两个点是顺序经过的，那么这两个点的手势轨
迹之间是绝对不能跨过任何未被经过的点。
经过点的顺序不同则表示为不同的解锁手势。
解释:
| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |
无效手势：4 - 1 - 3 - 6
连接点 1 和点 3 时经过了未被连接过的 2 号点。
无效手势：4 - 1 - 9 - 2
连接点 1 和点 9 时经过了未被连接过的 5 号点。
有效手势：2 - 4 - 1 - 3 - 6
连接点 1 和点 3 是有效的，因为虽然它经过了点 2 ，但是点 2
在该手势中之前已经被连过了。
有效手势：6 - 5 - 4 - 1 - 9 - 2
连接点 1 和点 9 是有效的，因为虽然它经过了按键 5 ，但是
点 5 在该手势中之前已经被连过了。
*/
/*
共3种出发情况：角落出发、边缘出发和中心出发，分别对应
4、4、1的重复情况。
对于两个点是否可以划过去，可以通过查表的方式获得。
当有了一些滑动步骤，那么之前不能走的点之间就有可能可
以走了，只要判断两个点编号的中间点已经走过了就可以走
了。
所以判断两点之间是否可以划过去的方法就是：
1、先查表如果可以走直接走，否则做逻辑判断；
2、判断阻隔两点的中间点是否已经走过了。
*/

static const bool walk_map[9][9] = {
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
};

static void backtrack(int arr[], int pos, int len, int level, int cnt[]);
int numberOfPatterns(int m, int n)
{
    int cnt[10] = {0};
    int corner[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    backtrack(corner, 1, 9, n, cnt);
    int edge[9] = {1, 0, 2, 3, 4, 5, 6, 7, 8};
    backtrack(edge, 1, 9, n, cnt);
    for (int i = 1; i <= n; i++)
        cnt[i] *= 4;
    int core[9] = {4, 0, 1, 2, 3, 5, 6, 7, 8};
    backtrack(core, 1, 9, n, cnt);

    int result = 0;
    for (int i = m; i <= n; i++)
        result += cnt[i];

    return result;
}

static inline void swap(int arr[], int l, int r)
{
    int temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

static inline bool can_walk(int arr[], int used, int from, int to)
{
    if (walk_map[from][to])
        return true;
    int spring_board = (from + to) / 2;
    for (int i = 0; i < used; i++)
        if (arr[i] == spring_board)
            return true;
    return false;
}

static void backtrack(int arr[], int pos, int len, int level, int cnt[])
{
    cnt[pos]++;
    if (pos == level)
        return;

    for (int i = pos; i < len; i++) {
        if (!can_walk(arr, pos, arr[pos - 1], arr[i]))
            continue;
        swap(arr, pos, i);
        backtrack(arr, pos + 1, len, level, cnt);
        swap(arr, pos, i);
    }
}

/*
306. 累加数
累加数是一个字符串，组成它的数字可以形成累加序列。
一个有效的累加序列必须至少包含 3 个数。除了最开始的两
个数以外，字符串中的其他数都等于它之前两个数相加的和。
给定一个只包含数字 '0'-'9' 的字符串，编写一个算法来判断给
定输入是否是累加数。
说明: 累加序列里的数不会以 0 开头，所以不会出现 1, 2, 03 或
者 1, 02, 3 的情况。
示例 1:
输入: "112358"
输出: true
解释: 累加序列为: 1, 1, 2, 3, 5, 8 。1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
示例 2:
输入: "199100199"
输出: true
解释: 累加序列为: 1, 99, 100, 199。1 + 99 = 100, 99 + 100 = 199
*/

void backtrack(char * num,int cidx, long *tmp,int tmpSize,bool *re)
{
	if(tmpSize >= 3) {
		if(tmp[tmpSize-3]+tmp[tmpSize-2]!=tmp[tmpSize-1]) {
			return;//当暂时数组里的数字个数超过3个但不符合累加数要求，不用继续查找，直接返回
		}
	}

	if(cidx == strlen(num)) {//用光了字符数组里所有字符
		if(tmpSize<3) return;//只组成了少于3个数字，肯定为假，返回

		int i  = 0;
		for(i  = 0;i<tmpSize-2;i++) {//遍历暂时数组所有元素是否满足累加数要求
			if(tmp[i]+tmp[i+1]!=tmp[i+2]) {
				break;
			}
		}

		if(i == tmpSize-2) {//有满足的情况，将返回值改为真
			*re=true;
		}
		return;
	}
/*
由于不能有前导零，如果当前数字为0，那么本次取的数字只
能为0
*/	if(num[cidx] == '0') {
		tmp[tmpSize]  = 0;
		backtrack(num,cidx+1,tmp,tmpSize+1,re);
		return;
	}

	int i  = 0,cnt  = 0;
	long sum  = 0;
	for(i = cidx;i<strlen(num);i++) {//一般情况
		sum  = sum*10+num[i]-'0';
		cnt++;
/*
下面这句是为了防止数字过大溢出long类型，可以轻松想到
如果某个数字取了大于strlen(num)/2长度的字符，
就不满足tmp[i]+tmp[i+1]  = tmp[i+2]这个条件
所以设置记数cnt，防止以上情况出现
*/
		if(2*cnt>strlen(num))
			break;
		tmp[tmpSize]  = sum;
		backtrack(num,i+1,tmp,tmpSize+1,re);
	}
}

bool isAdditiveNumber(char * num)
{
	if(strlen(num)<3)
		return false;

	bool re  = false;
	int size  = 0;
	long tmp[strlen(num)];//暂时存放取出的n个字符组成的数字
	memset(tmp,0,sizeof(tmp));
	backtrack(num,0,tmp,0,&re);
	return re;
}


/*
79. 单词搜索
给定一个二维网格和一个单词，找出该单词是否存在于网格
中。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。
示例:
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
给定 word = "ABCCED", 返回 true
给定 word = "SEE", 返回 true
给定 word = "ABCB", 返回 false
*/

int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool backtrack(char** board, int row, int col, int cx, int cy, char *word, int wordIdx)
{
	if (wordIdx == strlen(word)) {
		return true;
	}

	if (cx  < 0 || cx >= row || cy < 0 || cy >= col) {
		return false;
	}

	if (board[cx][cy] == 0) {
		return false;
	}

	if (board[cx][cy] != word[wordIdx]) {
		return false;
	}

	int tmp = board[cx][cy];
	board[cx][cy] = 0;

	for (int i = 0; i < 4; i++) {
		int nx = cx + dir[i][0];
		int ny = cy + dir[i][1];

		bool ret = backtrack(board, row, col, nx, ny,  word, wordIdx + 1);
		if (ret) {
			return true;
		}
	}

	board[cx][cy] = tmp;
	return false;
}

bool exist(char** board, int boardSize, int* boardColSize, char * word)
{
	int row = boardSize;
	int col = *boardColSize;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == word[0]) {
				bool ret = backtrack(board, row, col, i, j, word, 0);
				if (ret) {
					return true;
				}
			}
		}
	}

	return false;
}

/*
89. 格雷编码
格雷编码是一个二进制数字系统，在该系统中，两个连续的
数值仅有一个位数的差异。
给定一个代表编码总位数的非负整数 n，打印其格雷编码序
列。即使有多个不同答案，你也只需要返回其中一种。
格雷编码序列必须以 0 开头。
示例 1:
输入: 2
输出: [0,1,3,2]
解释:
00 - 0
01 - 1
11 - 3
10 - 2
对于给定的 n，其格雷编码序列并不唯一。
例如，[0,2,3,1] 也是一个有效的格雷编码序列。
00 - 0
10 - 2
11 - 3
01 - 1
*/


/// 递归辅助函数
int helper(int* ret, int* repeat, int n, int size, int i)
{
    /// 递归出口：如果已经到最后一个编码返回结束标志
    if (i == size - 1)
        return 1;

    int code;

    /// 尝试分别对第 i 次获得编码的每一位进行反转
    for (int j = 0; j < n; ++j)
    {
        /// 利用异或操作计算得新编码
        code = ret[i] ^ (1u << j);

        /// 如果该编码已经使用过则跳过
        if (repeat[code])
            continue;

        /// 更新编码与重复表
        ret[i + 1] = code;
        repeat[code] = 1;

        /// 递归对下一个编码进行计算
        if (helper(ret, repeat, n, size, i + 1))
            return 1;
    }

    return 0;
}

int* grayCode(int n, int* returnSize)
{
    /// 编码的个数可直接由 n 确定
	*returnSize = pow(2, n);

    /// 所有情况下第一个元素都是 0
    int* ret = malloc(sizeof(int) * *returnSize);
    *ret = 0;

    /// 如果 n 为 0 则直接返回
    if (*returnSize == 0)
    {
        return ret;
    }

    /// 初始化重复表，并且默认情况下 0 已经被使用过
    int* repeat = calloc(sizeof(int), *returnSize);
    *repeat = 1;

    helper(ret, repeat, n, *returnSize, 0);

    free(repeat);

    return ret;
}


/*
131. 分割回文串
给定一个字符串 s，将 s 分割成一些子串，使每个子串都
是回文串。
返回 s 所有可能的分割方案。
示例:
输入: "aab"
输出:
[
  ["aa","b"],
  ["a","a","b"]
]
*/

#define MAX_RET 10000

char ***g_ans;
int g_ansSize;

char *substr(char *s, int l, int r) {
    char *sub = malloc(r - l + 2);
    int index = 0;
    while (l <= r) {
        sub[index++] = s[l++];
    }
    sub[index] = '\0';
    return sub;
}

bool isPalindrome(char *s, int l, int r) {
    if (l == r) {
        return true;
    }
    while (l < r) {
        if (s[l++] != s[r--]) {
            return false;
        }
    }
    return true;
}

void dump(char **subs, int subSize) {
    for (int i = 0; i < subSize; ++i) {
        printf("%s, ", subs[i]);
    }
    printf("\n");
}

void copyToAns(char **subs, int subSize, int *retColSize) {
    g_ans[g_ansSize] = malloc(sizeof(char *) * subSize);
    retColSize[g_ansSize] = subSize;
    for (int i = 0; i < subSize; ++i) {
        g_ans[g_ansSize][i] = malloc(sizeof(char) * (strlen(subs[i]) + 1)); // one more char for '\0'
        strcpy(g_ans[g_ansSize][i], subs[i]);
    }
    ++g_ansSize;
}

void backtrack(char *s, int len, int pos, char **subs, int subSize, int *retColSize) {
    if (pos == len) {
            // dump(subs, subSize);
        copyToAns(subs, subSize, retColSize);
        return;
    }
    for (int i = pos; i < len; ++i) {
        if (isPalindrome(s, pos, i)) {
            subs[subSize] = substr(s, pos, i);
            backtrack(s, len, i + 1, subs, subSize + 1, retColSize);
            free(subs[subSize]);
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** partition(char * s, int* returnSize, int** returnColumnSizes){
    g_ansSize = 0;
    g_ans = (char ***)malloc(sizeof(char *) * MAX_RET);
    char **tmpSubs = malloc(sizeof(char *) * strlen(s));    // s can be splited into strlen(s) sub strings if length of each sub string is 1
    *returnColumnSizes = (int *)malloc(sizeof(int) * MAX_RET);
    backtrack(s, strlen(s), 0, tmpSubs, 0, *returnColumnSizes);
    *returnSize = g_ansSize;

    free(tmpSubs);
    return g_ans;
}

