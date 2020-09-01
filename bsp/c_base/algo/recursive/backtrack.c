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
1219                                                                                                                                                                                                . 黄金矿工
你要开发一座金矿，地质勘测学家已经探明了
这座金矿中的资源分布，并用大小为 m * n 的网格
grid 进行了标注。每个单元格中的整数就表示这一
单元格中的黄金数量；如果该单元格是空的，那么就是 0。
为了使收益最大化，矿工需要按以下规则来开采黄金：
每当矿工进入一个单元，就会收集该单元格中的所有黄金。
矿工每次可以从当前位置向上下左右四个方向走。
每个单元格只能被开采（进入）一次。
不得开采（进入）黄金数目为 0 的单元格。
矿工可以从网格中 任意一个 有黄金的单元格出发或者是停止。


示例 1：

输入：grid = [[0,6,0],[5,8,7],[0,9,0]]
输出：24
解释：
[[0,6,0],
 [5,8,7],
 [0,9,0]]
一种收集最多黄金的路线是：9 -> 8 -> 7。
*/
int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int backtrack(int** grid, int row, int col, int x, int y)
{
	int curVal = grid[x][y];
	grid[x][y] = 0;
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= row || ny < 0 || ny >= col || grid[nx][ny] == 0) {
			continue;
		}

		sum = fmax(sum, backtrack(grid, row, col, nx, ny));
	}

	grid[x][y] = curVal;
	return sum + curVal;
}

int getMaximumGold(int** grid, int gridSize, int* gridColSize){
    if(grid == NULL || gridSize <= 0 || gridColSize == NULL) {
        return 0;
    }

    int row = gridSize;
    int col = *gridColSize;
    int res = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i];j++) {
            if (grid[i][j] != 0) {
                res = fmax(res, backtrack(grid, row, col, i, j));
            }
        }
    }

    return res;
}

/*
46. 全排列
难度中等838
给定一个 没有重复 数字的序列，返回其所有可能的全排列。
示例:
输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

*/
void backtrack(int* nums, int numsSize, int* returnSize, int** returnColumnSizes,
                int** res, bool* visited, int* path, int pathSize)
{
	if (numsSize == pathSize) {
		res[*returnSize] = (int*)malloc(numsSize * sizeof(int));
		memcpy(res[*returnSize], path, numsSize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = numsSize;
		(*returnSize)++;
		return;
	}

        for (int index = 0; index < numsSize; index++) {
		if (visited[index] == true) {
			continue;
		}

                visited[index] = true;
                path[pathSize] = nums[index];
                pathSize++;

                backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, pathSize);

                pathSize--; // 回溯
                visited[index] = false;
        }
}

int** permute(int* nums, int numsSize, int* returnSize,
			     int** returnColumnSizes)
{
	int **res = (int **)calloc (17000,  sizeof(int *));
	*returnColumnSizes = (int *)calloc(17000, sizeof(int));
	int path[numsSize];
	memset(path, 0, sizeof(path));
	bool visited[numsSize];
	memset(visited, false, sizeof(visited));
	*returnSize = 0;
	backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, 0);
	return res;
}

/*
47. 全排列 II
难度中等320
给定一个可包含重复数字的序列，返回所有不重复的全排列。
示例:
输入: [1,1,2]
输出:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/
#define MAX_SIZE 5000
void backtrack(int* nums, int numsSize, int* returnSize, int** returnColumnSizes,
                int** res, bool* visited, int* path, int pathSize)
{
	if (numsSize == pathSize) {
		res[*returnSize] = (int*)malloc(numsSize * sizeof(int));
		memcpy(res[*returnSize], path, numsSize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = numsSize;
		(*returnSize)++;
		return;
	}

        for (int index = 0; index < numsSize; index++) {
		if (visited[index] == true) {
			continue;
		}

		if (index > 0 &&  visited[index - 1] == true &&  nums[index - 1] == nums[index]) {
			continue;
		}

                visited[index] = true;
                path[pathSize] = nums[index];
                pathSize++;

                backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, pathSize);

                pathSize--; // 回溯
                visited[index] = false;
        }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

    int** res = (int**)malloc(MAX_SIZE * sizeof(int*));
    bool* visited = (bool*)malloc(numsSize * sizeof(bool));
    memset(visited, false, numsSize);
    int* path = (int*)malloc(numsSize * sizeof(int));

    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(MAX_SIZE * sizeof(int));

    backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, 0);

    return res;
}

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
int cmp_char(const void *a, const void *b)
{
	return  *((char *)a) - *((char *)b);
}

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
void backtrack(int num, char ** res, int* returnSize,
int hour, int minute, int it)
{
	if (num == 0) {
		res[*returnSize] = (char *)calloc(10, sizeof(char *));
		sprintf(res[*returnSize] , "%d:%02d", hour, minute);
		(*returnSize)++;
		return;
	}
/*
0 - 5 是 分钟 6 - 9 是小时。
*/
	for (int i = it; i < 10; i++) {
		if (i <= 5) {
			minute += (1 << i);
			if (minute > 59) {
				minute -= (1 << i);
				continue;
			}
		} else {
			hour += (1 << i - 6);//减法优先级高于<<
			if (hour > 11)
				return;
		}

		backtrack(num -1, res,  returnSize, hour,  minute, i + 1);

		if (i <= 5)
			minute -= (1 << i);
		else
			hour -= (1 << i - 6);
	}
}

char ** readBinaryWatch(int num, int* returnSize)
{
	char ** res = (char **)calloc(1024, sizeof(char *));

	*returnSize = 0;
	backtrack(num, res, returnSize, 0, 0, 0);

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
bool backtrack(int** obstacleGrid, int row, int col, int itx, int ity,
int **res, int *returnSize,  bool visited[][100], int** returnColumnSizes)
{
	if(itx >= row || ity >= col || obstacleGrid[itx][ity] == 1 || visited[itx][ity])
		return false;

	visited[itx][ity] = 1;
	res[*returnSize] = (int *)calloc(2, sizeof(int));
	res[*returnSize][0] = itx;
	res[*returnSize][1] = ity;
	(*returnColumnSizes)[*returnSize] = 2;
	(*returnSize)++;

	if(itx == (row - 1) && ity == (col - 1)) {
		return true;
	}

	if (backtrack(obstacleGrid, row, col, itx, ity + 1, res, returnSize, visited, returnColumnSizes) ||
		backtrack(obstacleGrid, row, col, itx + 1, ity, res, returnSize, visited, returnColumnSizes)) {
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
332. 重新安排行程
难度中等102
给定一个机票的字符串二维数组 [from, to]，子数组中的两个成员
分别表示飞机出发和降落的机场地点，对该行程进行重新规
划排序。所有这些机票都属于一个从JFK（肯尼迪国际机场）
出发的先生，所以该行程必须从 JFK 出发。
说明:
1.	如果存在多种有效的行程，你可以按字符自然排序返回
最小的行程组合。例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更
小，排序更靠前
2.	所有的机场都用三个大写字母表示（机场代码）。
3.	假定所有机票至少存在一种合理的行程。
示例 1:
输入: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
输出: ["JFK", "MUC", "LHR", "SFO", "SJC"]
示例 2:
输入: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
输出: ["JFK","ATL","JFK","SFO","ATL","SFO"]
解释: 另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"]。但是它
自然排序更大更靠后。

*/
 void backtrack(char *** tickets, int ticketsSize,
 	char ** res, char *start, int *count, int *visited)
 {  //遍历飞机票
	for (int i = 0; i < ticketsSize; i++) {
		if (visited[i] == 0 && strcmp(start, tickets[i][0]) == 0) {//找到目的地
			(*count)++;
			visited[i] = 1;
			char *newStart = tickets[i][1];

			//将目的地加到结果数组中
			res[*count] = strdup(newStart);
			//遍历下个目的地
			backtrack(tickets, ticketsSize, res, newStart, count, visited);
			//当结果数组满了，则返回。
			if (*count  == ticketsSize ) {
				return;
			}
			//不符合则回溯
			(*count)--;
			visited[i] = 0;
		}
	}
 }

int cmp(const void *str1, const void *str2)
{
    const char **tmp1 = *(char**)str1;
    const char **tmp2 = *(char**)str2;
    int ret = strcmp(tmp1[0], tmp2[0]);
    if (ret == 0) {
        return strcmp(tmp1[1], tmp2[1]);
    }

    return ret;
}

char ** findItinerary(char *** tickets, int ticketsSize, int* ticketsColSize, int* returnSize)
{
	*returnSize = ticketsSize + 1;
	char **res = (char**)calloc(*returnSize, sizeof(char*));
	qsort(tickets, ticketsSize, sizeof(tickets[0]), cmp);

	res[0] = strdup("JFK");
	int count = 0;
	int visited[ticketsSize];
	memset(visited, 0, sizeof(visited));
	backtrack(tickets, ticketsSize, res, res[0], &count, visited);

	return res;
}


/*
638. 大礼包
难度中等97
在LeetCode商店中， 有许多在售的物品。
然而，也有一些大礼包，每个大礼包以优惠的价格捆绑销售
一组物品。
现给定每个物品的价格，每个大礼包包含物品的清单，以及
待购物品清单。请输出确切完成待购清单的最低花费。
每个大礼包的由一个数组中的一组数据描述，最后一个数字
代表大礼包的价格，其他数字分别表示内含的其他种类物品
的数量。
任意大礼包可无限次购买。
示例 1:
输入: [2,5], [[3,0,5],[1,2,10]], [3,2]
输出: 14
解释:
有A和B两种物品，价格分别为?2和?5。
大礼包1，你可以以?5的价格购买3A和0B。
大礼包2， 你可以以?10的价格购买1A和2B。
你需要购买3个A和2个B， 所以你付了?10购买了1A和2B（
大礼包2），以及?4购买2A。
示例 2:
输入: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
输出: 11
解释:
A，B，C的价格分别为?2，?3，?4.
你可以用?4购买1A和1B，也可以用?9购买2A，2B和1C。
你需要买1A，2B和1C，所以你付了?4买了1A和1B（大礼包1），以及?3购买1B， ?4购买1C。
你不可以购买超出待购清单的物品，尽管购买大礼包2更加便宜。
.
*/

/*
本题实质是一个组合问题
求出原价购买所有物品的总花费.
求出每个礼包原价购买的花费.
用礼包替价格去替换原价，算出替换后的总价，
更新最小总价
*/
int g_res;
void backtrack(int** special, int specialSize, int* specialColSize, int* needs,
	int needsSize, int *specialOrinPrice, int totalNeedOrinPrice)
{
	for (int i = 0; i < needsSize; i++) {
		if (needs[i] < 0) {
			return;
		}
	}

	g_res = fmin(g_res, totalNeedOrinPrice);

	for (int i = 0; i < specialSize; i++) {
		for (int j = 0; j < specialColSize[i] - 1; j++) {
			needs[j] -= special[i][j];
		}

		backtrack(special, specialSize, specialColSize, needs, needsSize,
		specialOrinPrice,
		/*总价- (一个礼包原价 -  一个礼包优惠价格)
			总价-(优惠差价) = 优惠价格
		*/
		totalNeedOrinPrice - (specialOrinPrice[i] - special[i][specialColSize[i] - 1]));

		for (int j = 0; j < specialColSize[i] - 1; j++) {
			needs[j] += special[i][j];
		}
	}
}

int shoppingOffers(int* price, int priceSize,
	int** special, int specialSize,
	int* specialColSize, int* needs, int needsSize)
{
	if (priceSize <= 0) {
		return 0;
	}

	int specialOrinPrice[specialSize];
	memset(specialOrinPrice, 0, sizeof(specialOrinPrice));

	/*礼包各类礼品原始总价*/
	for (int i = 0; i < specialSize; i++) {
		for (int j = 0; j < specialColSize[i] - 1; j++) {
			specialOrinPrice[i] += price[j] * special[i][j];
		}
	}

	int totalNeedOrinPrice = 0;
	for (int i = 0; i < needsSize; i++) {
		totalNeedOrinPrice += price[i] * needs[i];
	}

	g_res = totalNeedOrinPrice;
	backtrack(special, specialSize, specialColSize, needs, needsSize,
		specialOrinPrice, totalNeedOrinPrice);
	return g_res;
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
	// 在此i、j、k下，无论如何都不能组成s3.substring(0, k+1),返回false
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
动态规划
状态定义
令dp[i][j]为字符子串s1[0, i),s2[0, j)能否组成s3[0, i+j)。
ps: s1[0, i) = s1.substring(0, i),不包含i。

对于字符串的状态dp[i]来说，通常要考虑所有子串的长度[0, n]，因此定义dp[n+1],n是字符串s的长度，同理二维也一样。

状态转移
对于dp[i][j]该状态来说，要想组成s3[0,i+j)，其s3[0, i+j)最后一个字符s3[i+j-1]要么来自s1[i-1], 要么来自s2[j-1],因此，状态转移：

若s1[i-1]==s3[i+j-1]：
dp[i][j] = dp[i-1][j],i > 0
dp[i][j]=dp[i?1][j],i>0

若s2[j-1]==s3[i+j-1]：
dp[i][j] = dp[i][j-1],j >0
dp[i][j]=dp[i][j?1],j>0

状态初始化：dp[0][0] = true，表示两个空字符串能够组成一个空字符串。

*/
bool isInterleave(char* s1, char* s2, char* s3) {
    int n = strlen(s1), m = strlen(s2), t = strlen(s3);

    int f[n + 1][m + 1];
    memset(f, 0, sizeof(f));

    if (n + m != t) {
        return false;
    }

    f[0][0] = true;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int p = i + j - 1;
            if (i > 0) {
                f[i][j] |= (f[i - 1][j] && s1[i - 1] == s3[p]);
            }
            if (j > 0) {
                f[i][j] |= (f[i][j - 1] && s2[j - 1] == s3[p]);
            }
        }
    }

    return f[n][m];
}


/*
679. 24 点游戏
你有 4 张写有 1 到 9 数字的牌。你需要判断是否能通过 *，/，+，-，(，) 的运算得到 24。

示例 1:

输入: [4, 1, 8, 7]
输出: True
解释: (8-4) * (7-1) = 24
示例 2:

输入: [1, 2, 1, 2]
输出: False
注意:

除法运算符 / 表示实数除法，而不是整数除法。例如 4 / (1 - 2/3) = 12 。
每个运算符对两个数进行运算。特别是我们不能用 - 作为一元运算符。例如，[1, 1, 1, 1] 作为输入时，表达式 -1 - 1 - 1 - 1 是不允许的。
你不能将数字连接在一起。例如，输入为 [1, 2, 1, 2] 时，不能写成 12 + 12 。
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

bool backtrack(char** board, bool rowVisited[9][10],
    bool colVisited[9][10], bool boxVisited[3][3][10], int idx, int idy, int boardSize, int* boardColSize)
{
	// 边界校验, 如果已经填充完成, 返回true, 表示一切结束
	if(idy == *boardColSize) {
		idy = 0;
		idx++;
		if(idx == boardSize){
			return true;
		}
	}

	// 是空则尝试填充, 否则跳过继续尝试填充下一个位置
	if(board[idx][idy] == '.') {
		// 尝试填充1~9
		for(int num = 1; num <= 9; num++){
			bool canUsed = !(rowVisited[idx][num] || colVisited[idy][num] || boxVisited[idx/3][idy/3][num]);
			if(canUsed){
				rowVisited[idx][num] = true;
				colVisited[idy][num] = true;
				boxVisited[idx/3][idy/3][num] = true;

				board[idx][idy] = (char)('0' + num);
				if(backtrack(board, rowVisited, colVisited, boxVisited, idx, idy + 1, boardSize, boardColSize)){
					return true;
				}

				board[idx][idy] = '.';

				rowVisited[idx][num] = false;
				colVisited[idy][num] = false;
				boxVisited[idx/3][idy/3][num] = false;
			}
		}
	} else {
		return backtrack(board, rowVisited, colVisited, boxVisited, idx, idy + 1, boardSize, boardColSize);
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
	for(int idx = 0; idx < boardSize; idx++){
		for(int idy = 0; idy < *boardColSize; idy++) {
			int num = board[idx][idy] - '0';
			if(1 <= num && num <= 9) {
				rowVisited[idx][num] = true;
				colVisited[idy][num] = true;
				boxVisited[idx / 3][idy / 3][num] = true;
			}
		}
	}

	backtrack(board, rowVisited, colVisited, boxVisited, 0, 0, boardSize, boardColSize);
}

/*
10. 正则表达式匹配
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

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
bool isMatch(char * s, char * p){
    if (!*p) return !*s;
    bool first_match = *s && (*s == *p || *p == '.');
    if (*(p+1) == '*') {
        return isMatch(s, p+2) || (first_match && isMatch(++s, p));
    }
    else {
        return first_match && isMatch(++s, ++p);
    }
}

int memo[100][100];
bool dfs(char *s,char *p,int s_index,int p_index)
{
    if(s[s_index]=='\0'&&p[p_index]=='\0')return true;//如果都遍历到最后说明匹配成功
    if(p[p_index]=='\0')return false;//如果p字符串匹配到最后,而s没有,则匹配不成功
    if(memo[s_index][p_index]!=-1)return memo[s_index][p_index];//记忆化,判断当前位置是否被搜过,是子直接返回当前结果,省去重复步骤
    bool flag=false;//初始标记
    if(p[p_index]=='.')//首先判断该位置是否是点
    {
        if(p[p_index+1]=='*')//然后判断下一个是否是*,如果是*,则可以匹配s中的任意个不同字符
        {
            for(int i=s_index;i<=strlen(s);i++)//遍历s当前位置到末尾,看是否能匹配成功
            {
                flag=dfs(s,p,i,p_index+2);//p是.*代替s,所以加2
                if(flag==true)//如果能匹配直接停止
                    break;
            }
        }
        else if(s[s_index]!='\0')//如果下一个不是*,一个.只能匹配一个字符
        {
            flag=dfs(s,p,s_index+1,p_index+1);//p是.代替s一个字符,所以各加1
        }
    }
    else if(p[p_index+1]=='*')//如果当前位置是字母,下一个是*,*可以匹配0个或多个s中与当前字母一样的字符
    {
        flag=dfs(s,p,s_index,p_index+2);//当匹配0个的情况,p中字母+*代替s中0个字符
        if(flag==false)//如果匹配不成功
        {
            for(int i=s_index;i<strlen(s);i++)//遍历s当前位置到末尾,看是否能匹配成功
            {
                if(s[i]==p[p_index])//即p中字母+*是否等价于s当前位置的字母,是则进行下一位置的匹配
                    flag=dfs(s,p,i+1,p_index+2);
                else//否则停止
                    break;
                if(flag==true)//如果匹配成功停止
                    break;
            }
        }
    }
    else if(s[s_index]==p[p_index])//在以上情况不满足的情况下,如果两字符相等,则遍历下一位置
    {
        flag=dfs(s,p,s_index+1,p_index+1);
    }
    //其他情况皆为false
    memo[s_index][p_index]=flag;//记忆化存储
    return flag;
}
bool isMatch(char * s, char * p){
    memset(memo,-1,sizeof(memo));//设-1为未访问过
    return dfs(s,p,0,0);
}
/*
"mississippi"
"mis*is*p*."
"ab"
".*"
""
".*"
"a"
".*..a*"
"aab"
"c*a*b"
*/