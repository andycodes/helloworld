/*
回溯法的基本思想：

针对所给问题，定义问题的解空间；
DFS 搜索解空间，并在搜索过程中用剪枝函数避免无效搜索。
在DFS的过程中发现不是问题的解，
那么就开始回溯到上一层或者上一个节点。

回溯法的代码套路是使用两个变量： res 和 path，
res 表示最终的结果，path 保存已经走过的路径。
如果搜到一个状态满足题目要求，
就把 path 放到 res 中


result = []
def backtrack(路径, 选择列表):
    if 满足「结束条件」:
        result.add(「路径」)
        return

    for 选择 in 「选择列表」:  (类似N叉树)
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

int backtrack(int ** grid, int gridSize, int* gridColSize,int i, int j)
{
	if (i < 0 || i >= gridSize || j < 0 || j >= gridColSize[0] || grid[i][j] == 0)
		return 0;

	int curVal = grid[i][j];
	grid[i][j] = 0;
	int ret = 0;

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for(int k = 0; k < 4; k++) {
		int nX = i + d[k][0];
		int nY = j + d[k][1];
		ret = fmax(ret, curVal + backtrack(grid,gridSize,gridColSize,nX,nY));
	}

	grid[i][j] = curVal;

	return ret;
}


int getMaximumGold(int** grid, int gridSize, int* gridColSize)
{
	if (grid == NULL || gridSize < 0 || gridColSize == NULL)
		return 0;

	int sumMax = 0;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			sumMax = fmax(sumMax, backtrack(grid, gridSize, gridColSize, i, j));
		}
	}

	return sumMax;
}

/*全排列*/
void backtrack(int source[], int start, int end, int *resSize, int **res)
{
	// 找到一个排列
	if (start == end) {
		res[*resSize] = (int *)calloc(end, sizeof(int));
		memcpy(res[*resSize], source, sizeof(int) * end);
		(*resSize)++;
	} else {
		// 没有找完一个排列，则继续往下找下一个元素
		for (int i = start; i < end; i++) {
			if (start != i) {// 两两交换
				swap(source[start], source[i]);
			}

			// 递归排列剩余的从start+1到end的元素
			backtrack(source, start + 1, end, resSize, res);

			if (start != i) {// 回溯时还原
				swap(source[start], source[i]);
			}
		}
	}
}

int** permute(int* nums, int numsSize, int* returnSize,
			     int** returnColumnSizes)
{
	int **res = (int **)calloc (17000,  sizeof(int *));
	int resSize = 0;

	backtrack(nums, 0, numsSize, &resSize, res);

	*returnSize = resSize;
	*returnColumnSizes = (int *)calloc(17000, sizeof(int));
	for (int i = 0; i < resSize; i++) {
		(*returnColumnSizes)[i] = numsSize;
	}

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
通过次数65,930
提交次数111,408

*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 //还是用老方法吧，用swap虽然节省了一些参数。但是这一题就解决不了，有重复元素的要排序剪枝，但swap会打乱顺序
#define MAX_SIZE 5000

static int compare(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

static void backtrack(int* nums, int numsSize, int* returnSize, int** returnColumnSizes,
                int** ppRes, bool* pbUsed, int* pBuffer)
{
    static int length = 0;
    int index = 0;

    if (numsSize == length)
    {
        ppRes[*returnSize] = (int*)malloc(numsSize * sizeof(int));
        memcpy(ppRes[*returnSize], pBuffer, numsSize * sizeof(int));
        (*returnColumnSizes)[*returnSize] = numsSize;
        (*returnSize)++;
    }
    else
    {
        for (index = 0; index <= numsSize - 1; index++)
        {
            if (false == pbUsed[index])
            {
                if (index > 0 && nums[index - 1] == nums[index] && true == pbUsed[index - 1])
                {
                    continue; // 这里条件换成false == pbUsed[index - 1]也成立，本质是定一个规则这次找还是下次找
                }

                pbUsed[index] = true;
                pBuffer[length] = nums[index];
                length++;

                backtrack(nums, numsSize, returnSize, returnColumnSizes, ppRes, pbUsed, pBuffer);

                length--; // 回溯
                pbUsed[index] = false;
            }
        }
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    qsort(nums, numsSize, sizeof(int), compare);

    int** ppRes = (int**)malloc(MAX_SIZE * sizeof(int*));
    bool* pbUsed = (bool*)malloc(numsSize * sizeof(bool));
    memset(pbUsed, false, numsSize);
    int* pBuffer = (int*)malloc(numsSize * sizeof(int));

    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(MAX_SIZE * sizeof(int));

    backtrack(nums, numsSize, returnSize, returnColumnSizes, ppRes, pbUsed, pBuffer);

    return ppRes;
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
void backTrace(char* S, int* returnSize, int len, int depth, char **ret, char *path, char *visited)
{
  if(depth == len)
  {
    int retIndex = (*returnSize)++;
    ret[retIndex] = malloc(len + 1);
    strcpy(ret[retIndex], path);
    return;
  }

  char duplicateMap[128] = {0};

  for(int i = 0; i < len; i++)
  {
    if(visited[i])          continue;
    if(duplicateMap[S[i]])  continue;   // the letter has shown up at this position

    duplicateMap[S[i]] = 1;
    visited[i] = 1;
    path[depth] = S[i];
    backTrace(S, returnSize, len, depth + 1, ret, path, visited);
    visited[i] = 0;
  }
}

#define MAX_LEN 1000

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** permutation(char* S, int* returnSize){

  char **ret = calloc(MAX_LEN, sizeof(char *));
  int len = strlen(S);

  char path[10] = {0};
  char visited[10] = {0};

  *returnSize = 0;
  backTrace(S, returnSize, len, 0, ret, path, visited);

  return ret;
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
int curH, int curM, int pos)
{
	if (num == 0) {
		res[*returnSize] = (char *)calloc(10, sizeof(char *));
		sprintf(res[*returnSize] , "%d:%02d", curH, curM);
		(*returnSize)++;
		return;
	}
/*
其实这个题目可以归于有多少 n个1的二进制组合。
转换为字符串即可。
这里将 0 - 9，划分一下
0 - 5 是 分钟
6 - 9 是小时计算。
*/
	for (int i = pos; i < 10; i++) {
		if (i <= 5) {
			curM += (1 << i);
			if (curM > 59) {
				curM -= (1 << i);
				continue;
			}
		} else {
			curH += (1 << i - 6);
			if (curH > 11)
				return;
		}

		backtrack(num -1, res,  returnSize, curH,  curM, i + 1);

		if (i <= 5)
			curM -= (1 << i);
		else
			curH -= (1 << i - 6);
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
设想有个机器人坐在一个网格的左上角，网格 r 行 c 列。机器人只能向下或向右移动，但不能走到一些被禁止的网格（有障碍物）。设计一种算法，寻找机器人从左上角移动到右下角的路径。

网格中的障碍物和空位置分别用 1 和 0 来表示。
返回一条可行的路径，路径由经过的网格的行号和列号组成。左上角为 0 行 0 列。
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

bool backtrack(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize, int row, int col,
int **ret, int *returnSize,  bool visited[][100], int** returnColumnSizes)
{
	if(row >= obstacleGridSize || col >= obstacleGridColSize[row] || obstacleGrid[row][col] == 1 || visited[row][col])
		return false;

	visited[row][col] = 1;
	ret[*returnSize] = (int *)calloc(2, sizeof(int));
	ret[*returnSize][0] = row;
	ret[*returnSize][1] = col;
	(*returnColumnSizes)[*returnSize] = 2;
	(*returnSize)++;

	if(row == (obstacleGridSize - 1) && col == (obstacleGridColSize[row] - 1)) {
		return true;
	}

	if (backtrack(obstacleGrid, obstacleGridSize, obstacleGridColSize, row, col + 1, ret, returnSize, visited, returnColumnSizes) ||
		backtrack(obstacleGrid, obstacleGridSize, obstacleGridColSize, row + 1, col, ret, returnSize, visited, returnColumnSizes)) {
		return true;
	}

	if (ret[*returnSize] != NULL) {
		free(ret[*returnSize]);
		ret[*returnSize] = NULL;

	}

	(*returnSize)--;

	return false;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathWithObstacles(int** obstacleGrid, int obstacleGridSize,
int* obstacleGridColSize, int* returnSize, int** returnColumnSizes){
	*returnSize = 0;
	int **ret = calloc(200, sizeof(int *));
	bool visited[100][100];
	memset(visited, 0, sizeof(visited));
	*returnColumnSizes = calloc(200, sizeof(int));
	bool  arrived = backtrack(obstacleGrid, obstacleGridSize, obstacleGridColSize,
	0, 0, ret, returnSize, visited, returnColumnSizes);
	if(arrived == false) {
		*returnSize = 0;
	}

	return ret;
}

/*
332. 重新安排行程
难度中等102
给定一个机票的字符串二维数组 [from, to]，子数组中的两个成员分别表示飞机出发和降落的机场地点，对该行程进行重新规划排序。所有这些机票都属于一个从JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 出发。
说明:
1.	如果存在多种有效的行程，你可以按字符自然排序返回最小的行程组合。例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前
2.	所有的机场都用三个大写字母表示（机场代码）。
3.	假定所有机票至少存在一种合理的行程。
示例 1:
输入: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
输出: ["JFK", "MUC", "LHR", "SFO", "SJC"]
示例 2:
输入: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
输出: ["JFK","ATL","JFK","SFO","ATL","SFO"]
解释: 另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"]。但是它自然排序更大更靠后。

*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define STR_LEN 4
int g_flag[300];
 void backtrack(char *** tickets, int ticketsSize, char *** res, char *start, int *count)
 {  //遍历飞机票
    for (int i = 0; i < ticketsSize; i++) {
        if (g_flag[i] == 0 && strcmp(start, tickets[i][0]) == 0) {//找到目的地
            (*count)++;
            //printf("#####%d %s\n", *count, start);
            g_flag[i] = *count;
            char *newStart = tickets[i][1];

            (*res)[(*count)] = (char*)calloc(STR_LEN, sizeof(char));
            //将目的地加到结果数组中
            strncpy((*res)[(*count)], newStart, STR_LEN);
            //遍历下个目的地
            backtrack(tickets, ticketsSize, res, newStart, count);
            //当结果数组满了，则返回。
            if (*count  == ticketsSize ) {
                return;
            }
            //不符合则回溯
            (*count)--;
            g_flag[i] = 0;
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

char ** findItinerary(char *** tickets, int ticketsSize, int* ticketsColSize, int* returnSize){
    *returnSize = ticketsSize + 1; //
    char **res = (char**)calloc(*returnSize, sizeof(char*));
    memset(g_flag, 0, sizeof(g_flag));
    //排序 自然序
    qsort(tickets, ticketsSize, sizeof(tickets[0]), cmp);

    char *start= "JFK";
    int count = 0;

    backtrack(tickets, ticketsSize, &res, start, &count);

    res[0] = (char*)calloc(STR_LEN, sizeof(char));
    strncpy(res[0], start, STR_LEN);

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
你需要购买3个A和2个B， 所以你付了?10购买了1A和2B（大礼包2），以及?4购买2A。
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
		specialOrinPrice, totalNeedOrinPrice - specialOrinPrice[i] +
		special[i][specialColSize[i] - 1]);

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
	backtrack(special, specialSize, specialColSize, needs, needsSize, specialOrinPrice, totalNeedOrinPrice);
	return g_res;
}

