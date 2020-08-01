/*
DFS

模板
result = []
def dfs(路径, 选择列表):
    if 满足「结束条件」:
        result.add(「路径」)
        return

    for 选择 in 「选择列表」:  (类似N叉树)
        #做选择
	 将该选择从选择列表移除
	 「路径」.add(选择)
        dfs(路径, 选择列表)
	 (注意跟回溯差异:没有反悔撤销而剪枝)


BFS+DFS问题
逆向传播
*/

/*
22. 括号生成
给出 n 代表生成括号的对数，请你写出一个函数，
使其能够生成所有可能的并且有效的括号组合。

例如，给出 n = 3，生成结果为：

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

为了生成所有序列，我们使用递归。长度为 n 的序列就
是 '(' 加上所有长度为 n-1 的序列，以及 ')' 加上所有长度为 n-1 的
序列。
*/

/*
DFS
思路和算法

加法

只有在我们知道序列仍然保持有效时才添加 '(' or ')'，
我们可以通过跟踪到目前为止放置的左括号和
右括号的数目来做到这一点，

如果我们还剩一个位置，我们可以开始放一个左括号。
如果它不超过左括号的数量，我们可以放一个右括号。

*/
void dfs(char **res, int* returnSize, int left, int right, int n, int idx, char *tmp)
{
	if (left + right == 2 * n) {
		res[*returnSize] = (char *)calloc(2 * n + 1, sizeof(char));
		strcpy(res[*returnSize], tmp);
		(*returnSize)++;
		return;
	}

	if (left < n) {
		tmp[idx] = '(';
		dfs(res, returnSize, left + 1, right, n, idx + 1, tmp);
	}

	if (right < left) {
		tmp[idx] = ')';
		dfs(res, returnSize, left, right + 1, n, idx + 1, tmp);
	}
}

void dfs(char** res, int* returnSize, char* current, int currentSize, int leftCnt, int rightCnt, int max)
{
	if (leftCnt > max || rightCnt > leftCnt) {
		return;
	}

	if (currentSize == max * 2) {
		res[*returnSize] = (char*)calloc(max * 2 + 1, sizeof(char));
		strcpy(res[*returnSize], current);
		(*returnSize)++;
		return;
	}

	current[currentSize] = '(';
	dfs(res, returnSize, current, currentSize + 1, leftCnt + 1, rightCnt, max);
	current[currentSize] = ')';
	dfs(res, returnSize, current, currentSize + 1, leftCnt, rightCnt + 1, max);
}

char** generateParenthesis(int n, int* returnSize)
{
    *returnSize = 0;
    if (n == 0) {
        return NULL;
    }

    char** res = (char**)calloc(1024 * 1024, sizeof(char*));
    char* current = (char*)calloc(1024 * 1024, sizeof(char));
    dfs(res, returnSize, current, 0, 0, 0, n);
    return res;
}


/*529 see bfs*/
int d[8][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {-1,-1},{-1,1},{1,-1}};
void dfs(char** board, int row, int col, int x, int y)
{
	if (board[x][y] == 'M') {
		board[x][y] = 'X';
		return;
	}

	if (board[x][y] != 'E') {
		return;
	}

	int cnt = 0;
	for (int i = 0; i < 8; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
			continue;
		}

		if (board[nx][ny] == 'X' || board[nx][ny] == 'M') {
			cnt++;
		}
	}

	if (cnt == 0) {
		board[x][y] = 'B';

		for (int i = 0; i < 8; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
			continue;
		}

		if (board[nx][ny] == 'M' || board[nx][ny] == 'E') {
			dfs(board, row, col, nx, ny);
		}
	}
	} else {
		board[x][y] = '0' + cnt;
	}
}

char** updateBoard(char** board, int boardSize, int* boardColSize,
int* click, int clickSize, int* returnSize, int** returnColumnSizes)
{
	*returnSize = boardSize;
	*returnColumnSizes = boardColSize;

	if (board[click[0]][click[1]] == 'M') {
		board[click[0]][click[1]] = 'X';
		return board;
	}

	int row = boardSize;
	int col = *boardColSize;
	dfs(board, row, col, click[0], click[1]);
	return board;
}


/*
130. 被围绕的区域
给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。

找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

示例:

X X X X
X O O X
X X O X
X O X X
运行你的函数后，矩阵变为：

X X X X
X X X X
X X X X
X O X X


这时候的 OO 是不做替换的。
因为和边界是连通的。为了记录这种状态，
我们把这种情况下的 OO 换成 # 作为占位符，
待搜索结束之后，遇到 OO 替换为 XX（和边界
不连通的 OO）；遇到 #，替换回 $O(和边界连通
的 OO)。
*/
void dfs(char** board, int row , int col, int x, int y)
{
	if (board[x][y] != 'O')
		return;

	board[x][y] = 'B';

	for (int i = 0; i < 4; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
			continue;
		}

		dfs(board, row, col, nx, ny);
	}
}

void solve(char** board, int boardSize, int* boardColSize)
{
	if (board == NULL || boardSize <= 0 || boardColSize == NULL)
		return board;

	int row = boardSize;
	int col = *boardColSize;

	for (int i = 0; i < col; i++) {
		dfs(board, row, col, 0, i);
		dfs(board, row, col, row - 1, i);
	}

	for (int i = 0; i < row; i++) {
		dfs(board, row, col, i, 0);
		dfs(board, row, col, i, col - 1);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == 'O') {
				board[i][j] = 'X';
			} else if (board[i][j] == 'B'){
				board[i][j] = 'O';
			}
		}
	}
}


/*
面试题 16.19. 水域大小
难度中等1
你有一个用于表示一片土地的整数矩阵land，该矩阵中每个点的
值代表对应地点的海拔高度。若值为0则表示水域。由垂直、
水平或对角连接的水域为池塘。池塘的大小是指相连接的水域
的个数。编写一个方法来计算矩阵中所有池塘的大小，
返回值需要从小到大排序。
示例：
输入：
[
  [0,2,1,0],
  [0,1,0,1],
  [1,1,0,1],
  [0,1,0,1]
]
输出： [1,2,4]

*/

int d[8][2] = {{0,1},{1,1},{1,0},{1,-1},
		{0,-1},{-1,-1},{-1,0},{-1,1}};
void  dfs(int** land, int row, int col, int x, int y, int *cnt)
{
	if (land[x][y] != 0)
		return;

	land[x][y] = 1;
	(*cnt)++;

	for (int i = 0; i < 8; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
			continue;
		}

		dfs(land, row, col, nx, ny, cnt);
	}
}

int* pondSizes(int** land, int landSize, int* landColSize, int* returnSize)
{
	if (land == NULL || landSize <= 0 || landColSize == NULL || returnSize == NULL)
		return NULL;

	int *res = (int *)calloc(1001 * 1001, sizeof(int));
	int row = landSize;
	int col = *landColSize;

	*returnSize = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (land[i][j] == 0) {
				int cnt = 0;
				dfs(land, row, col, i, j, &cnt);
				res[*returnSize] = cnt;
				(*returnSize)++;
			}
		}
	}

	qsort(res, *returnSize, sizeof(res[0]), cmp_int);
	return res;
}

int d[8][2] = {{0,1},{1,1},{1,0},{1,-1},
		{0,-1},{-1,-1},{-1,0},{-1,1}};

int  dfs(int** land, int row, int col, int x, int y)
{
	if (land[x][y] != 0)
		return 0;

	land[x][y] = 1;
	int ret = 1;

	for (int i = 0; i < 8; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
			continue;
		}

		ret += dfs(land, row, col, nx, ny);
	}

	return ret;
}

int* pondSizes(int** land, int landSize, int* landColSize, int* returnSize)
{
	if (land == NULL || landSize <= 0 || landColSize == NULL || returnSize == NULL)
		return NULL;

	int *res = (int *)calloc(1001 * 1001, sizeof(int));
	int row = landSize;
	int col = *landColSize;

	*returnSize = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (land[i][j] == 0) {
				res[*returnSize] = dfs(land, row, col, i, j);
				(*returnSize)++;
			}
		}
	}

	qsort(res, *returnSize, sizeof(res[0]), cmp_int);
	return res;
}


/*
17. 电话号码的字母组合
给定一个仅包含数字 2-9 的字符串，
返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。
注意 1 不对应任何字母。
示例:

输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/
char letter[][4] = {
    {'a', 'b', 'c', 0},
    {'d', 'e', 'f', 0},
    {'g', 'h', 'i', 0},
    {'j', 'k', 'l', 0},
    {'m', 'n', 'o', 0},
    {'p', 'q', 'r', 's'},
    {'t', 'u', 'v', 0},
    {'w', 'x', 'y', 'z'}
};
int nums[] = {3,3,3,3,3,4,3,4};

void dfs(char* digits, int srcSize, int* returnSize, char* tmp, int start, char** res)
{
	if (start == srcSize) {
		res[*returnSize] = strdup(tmp);
		(*returnSize)++;
		return;
	}

	int leSize = nums[digits[start] - '2'];
	for (int i = 0; i < leSize; i++) { /*当前层次的种类*/
		tmp[start] = letter[digits[start] - '2'][i];
		dfs(digits, srcSize, returnSize, tmp, start + 1, res);
	}
}

char** letterCombinations(char* digits, int* returnSize)
{
	*returnSize = 0;
	int slen = strlen(digits);
	if (digits == NULL || slen == 0) {
		return NULL;
	}

	char** res = (char **)calloc(1024, sizeof(char*));
	char tmp[1024];
	memset(tmp, 0, sizeof(tmp));
	dfs(digits, slen, returnSize, tmp, 0, res);
	return res;
}


/*
39. 组合总和
给定一个无重复元素的数组 candidates 和一个目标数 target ，
找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。
示例 1:
输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
  [7],
  [2,2,3]
]

target 减法-->0
sum 加法--->target
*/
void dfs(int* candidates, int candidatesSize, int start,
    int target, int* returnSize, int** returnColumnSizes,
    int **res, int *current, int curIdx)
{
	if (target == 0) {
		res[*returnSize] = (int*)calloc(1024, sizeof(int));
		memcpy(res[*returnSize], current, sizeof(int) * curIdx);
		(*returnColumnSizes)[*returnSize] = curIdx;
		(*returnSize)++;
		return;
	}

	/*start:组合不重复，上一层已经选用的元
	素下一层再使用造成重复*/
	for (int i = start; i < candidatesSize &&  candidates[i] <= target; i++) {
		current[curIdx] = candidates[i];
		dfs(candidates, candidatesSize, i, target - candidates[i],
			returnSize, returnColumnSizes, res, current, curIdx + 1);
	}
}

int** combinationSum(int* candidates, int candidatesSize,
    int target, int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;
	if (candidates == NULL || candidatesSize <= 0) {
		return NULL;
	}

	qsort(candidates, candidatesSize, sizeof(int), cmp_int);/*must*/
	int** res = (int**)calloc(1024, sizeof(int*));
	*returnColumnSizes = (int*)calloc(1024, sizeof(int));
	int current[1024] = {0};
	dfs(candidates, candidatesSize, 0, target, returnSize,
		returnColumnSizes, res, current, 0);
	return res;
}

/*
40. 组合总和 II
给定一个数组 candidates 和一个目标数 target ，
找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。
说明：
所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。


算法:
同一层次的数字不要重复，就可以避免整体重复。
                  1
                 / \
                2   2  这种情况不会发生
               /     \
              5       5
                例2
                  1
                 /
                2      这种情况确是允许的
               /
              2

*/
void dfs(int* candidates, int candidatesSize,
int target, int* returnSize, int** returnColumnSizes,
int start, int **res, int *curBuf, int curSize)
{
	if (target == 0) {
		res[*returnSize] = (int *)calloc(1024, sizeof(int));
		memcpy(res[*returnSize], curBuf, curSize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = curSize;
		(*returnSize)++;
		return;
	}

	for (int i = start; i < candidatesSize && target > 0 && candidates[i] <= target; i++) {
/*排序之后相同的肯定是挨着的，
if（candidates[i] == candidates[i - 1]）我们就过滤掉candidates[i]*/
/*
无论是求组合/子集/排列，只要原数组中含有重复元素，通用一个去重方法：
1.先排序，使相同元素相邻；
2.在backtrack的for循环里：


if(i>start&&candidates[i]==candidates[i-1]) continue;
其中i>start一定要理解，i是当前考察的元素下标，start是本层最开始的那个元素的下标，我们的去重是要同层去重，
如果你只写candidates[i]==candidates[i-1]这一个判断条件，那么在dfs树的时候，身处不同层的相同元素的组合/排列也都生成不了
*/
		if ( i > start && candidates[i] == candidates[i - 1])
			continue;

        	curBuf[curSize] = candidates[i];
		dfs(candidates, candidatesSize, target - candidates[i],
		returnSize, returnColumnSizes, i + 1, res, curBuf, curSize  + 1);
	}
}


int** combinationSum2(int* candidates, int candidatesSize,
int target, int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;
	if (candidates == NULL || candidatesSize <= 0)
		return NULL;

	int ** res = (int **)calloc(1024, sizeof(int *));
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));
	int curBuf[1024] = {0};

	qsort(candidates, candidatesSize, sizeof(int), cmp_int);
	dfs(candidates, candidatesSize, target,
	returnSize, returnColumnSizes, 0, res, curBuf, 0);
	return res;
}

/*
216. 组合总和 III
找出所有相加之和为 n 的 k 个数的组合。
组合中只允许含有 1 - 9 的正整数，
并且每种组合中不存在重复的数字。

说明：

所有数字都是正整数。
解集不能包含重复的组合。
示例 1:

输入: k = 3, n = 7
输出: [[1,2,4]]
示例 2:

输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]

*/
void dfs(int k, int n, int* returnSize, int** returnColumnSizes,
int **res, int *tmp, int tmpIdx, int start)
{
	if (k == 0 && n == 0) {
		res[*returnSize] = (int *)calloc(tmpIdx, sizeof(int));
		memcpy(res[*returnSize], tmp, tmpIdx * sizeof(int));
		(*returnColumnSizes)[*returnSize] = tmpIdx;
		(*returnSize)++;
		return;
	}

	for (int i = start; i <= 9 && k > 0 && n > 0 && i <= n; i++) {
		tmp[tmpIdx] = i;
		/*i + 1 :每种组合中不存在重复的数字。
		因为结果集里的元素互不相同，
		因此下一层搜索的起点应该是上一层搜索的起点值 + 1；*/
		dfs(k - 1, n  - i, returnSize, returnColumnSizes, res, tmp, tmpIdx + 1, i + 1);
	}
}

int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes)
{
	int **res = (int **)calloc(1024, sizeof(int **));
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));
	*returnSize = 0;
	int tmp[1024] = {0};
	dfs(k, n, returnSize, returnColumnSizes, res, tmp, 0, 1);
	return res;
}


/*
64 最小路径和
给定一个包含非负整数的 m x n 网格，
请找出一条从左上角到右下角的路径，
使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

示例:

输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 7
解释: 因为路径 1→3→1→1→1 的总和最小。

*/
int  dfs(int** grid, int gridSize, int* gridColSize, int x, int y)
{
	if (x == gridSize - 1 && y == gridColSize[x] - 1) {
		return grid[x][y];
	}

	if (x + 1 >= gridSize)
		return grid[x][y] + dfs(grid, gridSize, gridColSize, x, y + 1);

	if (y + 1 >= gridColSize[x])
		return grid[x][y] + dfs(grid, gridSize, gridColSize, x + 1, y);

	return grid[x][y] + fmin(dfs(grid, gridSize, gridColSize, x, y + 1),
		dfs(grid, gridSize, gridColSize, x + 1, y));
}

int minPathSum(int** grid, int gridSize, int* gridColSize)
{
	if (grid == NULL || gridSize < 1 || gridColSize == NULL)
		return 0;

	return dfs(grid, gridSize, gridColSize, 0, 0);
}

/*
934. 最短的桥
难度中等68
在给定的二维二进制数组 A 中，存在两座岛。（岛是由四面
相连的 1 形成的一个最大组。）
现在，我们可以将 0 变为 1，以使两座岛连接起来，变成一
座岛。
返回必须翻转的 0 的最小数目。（可以保证答案至少是 1。）

示例 1：
输入：[[0,1],[1,0]]
输出：1
示例 2：
输入：[[0,1,0],[0,0,0],[0,0,1]]
输出：2
示例 3：
输入：[[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
输出：1

*/

/*(明确是2座岛)
第一步：dfs将第一个的岛屿元素全部标记出来，并顺序入队；
第二步：bfs遍历队内各元素，将未标记元素标记并入队，step++;
第三步：找到新的元素为1即为新岛屿，step++返回即可。
*/
int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void dfs(int** A, int ASize, int* AColSize, int x, int y)
{
	if (x < 0 || y < 0 || x >= ASize || y >= AColSize[x]) {
		return;
	}

	if (A[x][y] != 1)
		return;

	A[x][y] = 2;

	for (int i = 0; i < 4; i++) {
		dfs(A, ASize, AColSize, x + d[i][0], y + d[i][1]);
	}
}

void colorFirstIsland(int** A, int ASize, int* AColSize)
{
	for (int i = 0; i < ASize; i++) {
		for (int j = 0; j < AColSize[i]; j++) {
			if (A[i][j] == 1) {
				dfs(A, ASize, AColSize, i, j);
				return;
			}
		}
	}
}

int shortestBridge(int** A, int ASize, int* AColSize)
{
	colorFirstIsland(A, ASize, AColSize);
	struct List queue;
	struct List* pqueue = &queue;
	queue_init(pqueue);

	for (int i = 0; i < ASize; i++) {
		for (int j = 0; j < AColSize[i]; j++) {
			if (A[i][j] == 2) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->key = i;
				entry->value = j;
				entry->step = 0;
				ListAddTail(pqueue, &entry->node);
			}
		}
	}

	while(!queue_empty(pqueue)) {
		struct DataEntry *pop = queue_pop_entry(pqueue);
		for (int i = 0; i < 4; i++) {
			int nx = pop->key + d[i][0];
			int ny = pop->value + d[i][1];

			if (nx < 0 || ny < 0 || nx >= ASize || ny >= AColSize[nx])
				continue;

			if (A[nx][ny] == 1)
				return pop->step;

			if (A[nx][ny] == 0) {
				A[nx][ny] = 2;
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->key = nx;
				entry->value = ny;
				entry->step = pop->step + 1;
				ListAddTail(pqueue, &entry->node);
			}
		}
	}

	return 0;
}


/*
494. 目标和
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。
现在你有两个符号 + 和 -。对于数组中的任意一个整数，
你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
示例 1:
输入: nums: [1, 1, 1, 1, 1], S: 3
输出: 5
解释:
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

一共有5种方法让最终目标和为3。
注意:

数组非空，且长度不会超过20。
初始的数组的和不会超过1000。
保证返回的最终结果能被32位整数存下。
通过次数24,886提交次数56,525
在真实的面试中遇到过这道题？
*/
void dfs(int* nums, int n, long int S, int idx, int *cnt)
{
	if (S == 0 && n == 0) {
		(*cnt)++;
		return ;
	}

	if (n <= 0)
		return;

	dfs(nums, n - 1, S - nums[idx], idx + 1, cnt);
	dfs(nums, n - 1, S + nums[idx], idx + 1, cnt);
}

int findTargetSumWays(int* nums, int numsSize, int S)
{
	int cnt = 0;
	dfs(nums, numsSize, S, 0, &cnt);
	return cnt;
}


/*
417. 太平洋大西洋水流问题
难度中等109
给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格
的高度。"太平洋"处于大陆的左边界和上边界，而"大西洋"处
于大陆的右边界和下边界。
规定水流只能按照上、下、左、右四个方向流动，且只能从
高到低或者在同等高度上流动。
请找出那些水流既可以流动到"太平洋"，又能流动到"大西洋"
的陆地单元的坐标。

提示：
1.	输出坐标的顺序不重要
2.	m 和 n 都小于150
示例：
给定下面的 5x5 矩阵:
  太平洋 ~   ~   ~   ~   ~
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * 大西洋
返回:
[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (上图中带括号的单元)
*/
void dfs(int** matrix, int i, int j, int pre, int row, int col, int visited[row][col])
{
    // 设定边界
    if (i<0 || i>=row || j<0 || j>=col) return;
    // 逆向遍历，只能由低到高
    if (matrix[i][j] < pre || visited[i][j] == 1)
        return;
    visited[i][j] = 1;
    // 方向矩阵
    int direction[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for(int k=0;k<4;k++){
        dfs(matrix, i+direction[k][0], j+direction[k][1], matrix[i][j], row, col, visited);
    }
}
int** pacificAtlantic(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes){
    if (matrixSize == 0) {
        returnColumnSizes[0] = NULL;
        *returnSize = 0;
        return NULL;
    }
    int row = matrixSize, col = *matrixColSize;
    int** res = (int**)malloc(row*col*sizeof(int*));
    returnColumnSizes[0] = (int*)malloc(row*col*sizeof(int));
    for (int i=0;i<row*col;i++) {
        res[i] = (int*)malloc(sizeof(int)*2);
        returnColumnSizes[0][i] = 2;
    }
    // 构建状态矩阵
    int visited1[row][col];
    int visited2[row][col];
    memset(visited1, 0, sizeof(visited1));
    memset(visited2, 0, sizeof(visited2));
    // 太平洋上边缘和大西洋下边缘
    for(int i=0;i<row;i++) {
        dfs(matrix, i, 0, 0, row, col, visited1);
        dfs(matrix, i, col-1, 0, row, col, visited2);
    }
    // 太平洋左边缘和大西洋右边缘
    for(int i=0;i<col;i++) {
        dfs(matrix, 0, i, 0, row, col,visited1);
        dfs(matrix, row-1, i, 0, row, col, visited2);
    }
    int index = 0;
    // 找状态矩阵重合的位置
    for (int i=0;i<row;i++) {
        for (int j=0;j<col;j++) {
            if (visited1[i][j] && visited2[i][j]) {
                res[index][0] = i;
                res[index++][1] = j;
            }
        }
    }
    *returnSize = index;
    return res;
}

/*
695. 岛屿的最大面积
难度中等288
给定一个包含了一些 0 和 1 的非空二维数组 grid 。
一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的
「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可
以假设 grid 的四个边缘都被 0（代表水）包围着。
找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，
则返回面积为 0 。)

示例 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]

*/

/*
 // 每次调用的时候默认num为1，进入后判断如果不是岛屿，
 则直接返回0，就可以避免预防错误的情况。
 // 每次找到岛屿，则直接把找到的岛屿改成0，
 这是传说中的沉岛思想，就是遇到岛屿就把他和周围的
 全部沉默。
 // ps：如果能用沉岛思想，那么自然可以用朋友圈思想。
*/
int dfs(int** grid, int row, int col, int sx, int sy)
{
	if (sx < 0 || sx >= row || sy < 0 || sy >= col || grid[sx][sy] == 0) {
		return 0;
	}

	int res = 1;
	grid[sx][sy] = 0;

	int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	for (int i = 0; i < 4; i++) {
		res += dfs(grid, row, col, sx + d[i][0], sy + d[i][1]);
	}

	return res;
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize)
{
	int max = 0;
	int row = gridSize;
	int col = *gridColSize;

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			if (grid[i][j] != 0) {
				max = fmax(max, dfs(grid, row, col, i,j));
			}
		}
	}

	return max;
}

/*
1034. 边框着色
给出一个二维整数网格 grid，网格中的每个值表示该位置处的
网格块的颜色。
只有当两个网格块的颜色相同，而且在四个方向中任意一个
方向上相邻时，它们属于同一连通分量。
连通分量的边界是指连通分量中的所有与不在分量中的正方
形相邻（四个方向上）的所有正方形，或者在网格的边界
上（第一行/列或最后一行/列）的所有正方形。
给出位于 (r0, c0) 的网格块和颜色 color，使用指定颜色 color 为所
给网格块的连通分量的边界进行着色，并返回最终的网格
grid 。
示例 1：
输入：grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
输出：[[3, 3], [3, 2]]
示例 3：
输入：grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
输出：[[2, 2, 2], [2, 1, 2], [2, 2, 2]]
*/

/*
联通分量内节点的颜色记为sColor，染边框的颜色为tColor。
（source color 与 target color）
dfs遍历整个联通分量：
对于遍历过的节点，我们都让他们的值为负数，
这样，就不需要多开空间来记录节点是否遍历过
对于联通分量中内部的节点，他们的值都为sColor，遍历过后，
他们的值为-sColor。
对于联通分量边框上的节点，他们的值都为sColor，遍历过后，
他们的值为-tColor。
遍历完整个联通分量，将整个grid中的负值改为正值
关键在于怎么判断一个节点在联通分量中是否处于边框的位
置：
该节点在整个网格的四周:

x == 0 || x+1 >= g.length || y == 0 || y+1 >= g[0].length
该节点的↑↓←→节点有任意一个节点不属于当前联通分量；
对于周围某个节点的颜色nextColor，如果它满足如下条件，
那么他就不属于当前联通分量
nextColor != sColor && nextColor != -sColor && nextColor != -tColor
nextColor != sColor：颜色上看根本不属于当前联通分量
nextColor != -sColor：它不是已经遍历过的联通分量内部节点
nextColor != -tColor：它不是已经遍历过的联通分量边框节点
*/
// 访问↑↓←→节点时坐标x, y的偏移量
int dis[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
void dfs(int** g, int gridSize, int* gridColSize, int x, int y, int sColor, int tColor)
{
        // 越界 || 不属于同一个联通分量 || 被访问过
        if(x < 0 || x >= gridSize || y < 0 || y >= gridColSize[x] || g[x][y] != sColor || g[x][y] < 0) {
            return;
        }

        // 当前节点已经被访问，设置负值
        g[x][y] = -sColor;

        // 判断边界
        if(x == 0 || x+1 >= gridSize || y == 0 || y+1 >= gridColSize[x]) {
            // 区域边界
            g[x][y] = -tColor;
        } else {
            // 连通分量的边界
            for(int i = 0 ; i < 4 ; i++) {
                int nextColor = g[x + dis[i][0]][y + dis[i][1]];
                // 这里是关键点
                if(nextColor != sColor && nextColor != -sColor && nextColor != -tColor) {
                    g[x][y] = -tColor;
                    break;
                }
            }
        }

        // 深度优先搜索，继续
        for(int i = 0 ; i < 4 ; i++) {
            dfs(g, gridSize, gridColSize, x+dis[i][0], y+dis[i][1], sColor, tColor);
        }
    }


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** colorBorder(int** grid, int gridSize, int* gridColSize, int r0, int c0, int color, int* returnSize, int** returnColumnSizes){

	dfs(grid, gridSize, gridColSize, r0, c0, grid[r0][c0], color);
        // 将负值置为正值
        for(int i = 0 ; i < gridSize ; i++) {
            for(int j = 0 ; j < gridColSize[i] ; j++) {
                grid[i][j] = grid[i][j] > 0 ? grid[i][j] : -grid[i][j];
            }
        }

	*returnSize = gridSize;
	*returnColumnSizes = (int *)calloc(gridSize, sizeof(int));
	for (int i = 0; i < gridSize; i++) {
		(*returnColumnSizes)[i] = gridColSize[i];
	}
        return grid;
}

/*
1391. 检查网格中是否存在有效路径
见UF
*/

//定义向各个方向搜索时，坐标的offset
struct{
    int r;
    int c;
}OffsetTbl[4] = {
// row  col
    {-1, 0},    //上
    {0, -1},    //左
    {0, 1},     //右
    {1, 0}      //下
};

bool interfaces[7][4] = {
    //上    左      右      下
    {false, false, false,  false},      //0： dummy
    {false, true,  true,   false},
    {true,  false, false,  true},
    {false, true,  false,  true},
    {false, false, true,   true},
    {true,  true,  false,  false},
    {true,  false, true,   false}
};

void dfs(int** grid, int gridSize, int* gridColSize, int row, int col)
{
    if(grid[row][col] == 0)
		return;

    int val =grid[row][col];
    grid[row][col] = 0;

    for(int i = 0; i < 4; i++){
        //该图案没有当前方向接口,continue
        if(interfaces[val][i] == false)
			continue;

        //如果有当前方向接口，计算该方向上邻居的坐标
        int r = row + OffsetTbl[i].r;
        int c = col + OffsetTbl[i].c;

        //坐标越界检查
        if(r >= gridSize || r < 0 || c < 0 || c >= gridColSize[row]){
            continue;
        }
/*
判断该邻居是否有对应方向(即3-i)的接口，
*/
        if(interfaces[grid[r][c]][3-i]){
            dfs(grid, gridSize, gridColSize, r, c);
        }
    }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize)
{
	if(grid == NULL || gridSize  <= 0|| gridColSize == NULL)
		return false;

	dfs(grid, gridSize, gridColSize, 0, 0);

	return grid[gridSize-1][gridColSize[gridSize-1] - 1] == 0;
}


/*
1376. 通知所有员工所需的时间
难度中等24
公司里有 n 名员工，每个员工的 ID 都是独一无二的，编号从 0
到 n - 1。公司的总负责人通过 headID 进行标识。
在 manager 数组中，每个员工都有一个直属负责人，其中 manager[i]
是第 i 名员工的直属负责人。对于总负责人，manager[headID] = -1。
题目保证从属关系可以用树结构显示。
公司总负责人想要向公司所有员工通告一条紧急消息。他将
会首先通知他的直属下属们，然后由这些下属通知他们的下
属，直到所有的员工都得知这条紧急消息。
第 i 名员工需要 informTime[i] 分钟来通知它的所有直属下属（也就
是说在 informTime[i] 分钟后，他的所有直属下属都可以开始传播
这一消息）。
返回通知所有员工这一紧急消息所需要的 分钟数 。

示例 1：
输入：n = 1, headID = 0, manager = [-1], informTime = [0]
输出：0
解释：公司总负责人是该公司的唯一一名员工。
示例 2：

输入：n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
输出：1
解释：id = 2 的员工是公司的总负责人，也是其他所有员工的
直属负责人，他需要 1 分钟来通知所有员工。
上图显示了公司员工的树结构。

*/

/*DFS自底向上*/
int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime,
int informTimeSize)
{
        //最终结果
        int res = 0;

        for(int i =0;i<managerSize;i++){
            //判断是否为结束点，剪枝
            if(informTime[i]==0){
                //临时值
                int temp = 0;
                int index=i;
                //向上遍历
                while(index!=-1){
                    temp+=informTime[index];
                    index=manager[index];
                }
                res = fmax(res,temp);
            }
        }
        return res;
}

/*DFS自底向上
遍历所有员工，对所有最底层员工（叶子节点），DFS搜索父节点，直到没有父节点为止。记录所有遍历的最大时间即为答案。*/
int dfs(int* manager, int *informTime, int id, int t)
{
    int m = manager[id];
    if (m == -1) {
        return t;
    }
    return dfs(manager, informTime, m, t + informTime[m]);
}

int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime, int informTimeSize){
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (informTime[i]) {
            continue;
        }

        int t = dfs(manager, informTime, i, 0);
        max = max >= t ? max : t;
    }
    return max;
}

/*
DFS自顶向下
算法描述
使用邻接表来表示题目中的N叉树，
再以headid为起点，进行树的遍历，记录搜索过程中计算出的最大通知时间，即为答案。
*/
typedef struct
{
    int key;
    UT_hash_handle hh;
}SetNode;

typedef struct
{
    int key;
    SetNode *set;
    UT_hash_handle hh;
}HashNode;

void dfs(int *visited, int *inform, int n, HashNode *hash, int pt, int id, int *t) {
    HashNode *node;
    HASH_FIND_INT(hash, &id, node);
    if (!node) {
        return;
    }

    pt += inform[id];
    *t = *t >= pt ? *t : pt;

    SetNode *curr, *tmp;
    HASH_ITER(hh, node->set, curr, tmp) {
        if (visited[curr->key]) {
            continue;
        }

        visited[curr->key] = 1;
        dfs(visited, inform, n, hash, pt, curr->key, t);
    }
}

int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime, int informTimeSize){
    int visited[n];
    memset(visited, 0, sizeof(int)*n);

    HashNode *hash = NULL;
    for (int i = 0; i < n; i++) {
        HashNode *node;
        HASH_FIND_INT(hash, &manager[i], node);
        if (!node) {
            node = malloc(sizeof(HashNode));
            node->key = manager[i];
            node->set = NULL;
            HASH_ADD_INT(hash, key, node);
        }

        SetNode *e = malloc(sizeof(SetNode));
        e->key = i;
        HASH_ADD_INT(node->set, key, e);
    }

    visited[headID] = 1;
    int t = 0;
    dfs(visited, informTime, n, hash, 0, headID, &t);
    return t;
}

/*
959 unionfind
*/
int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void dfs(int x, int y, int n, int grid[n][n]) {

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < n && !grid[nx][ny]) {
                grid[nx][ny] = 1;
                dfs(nx, ny, n, grid);
            }
        }
    }


int regionsBySlashes(char ** grid, int gridSize)
{
        int n = gridSize;
	int newGridSize = 3 * n;
	 int new_grid[newGridSize][newGridSize];
	memset(new_grid, 0, sizeof(new_grid));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '/') {
                    new_grid[3*i][3*j+2] = 1;
                    new_grid[3*i+1][3*j+1] = 1;
                    new_grid[3*i+2][3*j] = 1;
                } else if (grid[i][j] == '\\') {
                    new_grid[3*i][3*j] = 1;
                    new_grid[3*i+1][3*j+1] = 1;
                    new_grid[3*i+2][3*j+2] = 1;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < 3*n; ++i) {
            for (int j = 0; j < 3*n; ++j) {
                if (!new_grid[i][j]) {
                    cnt++;
                    new_grid[i][j] = 1;
                    dfs(i, j, newGridSize, new_grid);
                }
            }
        }
        return cnt;
}

/*
947 unionfind
*/
int row = 0;
void dfs(int x, int y, int** stones, int* visit) {
    for (int i = 0; i < row; i++) {

        if ((stones[i][0] == x || stones[i][1] == y)) {
            if (visit[i] == 0) {
                //printf("%d %d %d %d \n", stones[i][0], stones[i][1], x , y);
                visit[i] = 1;
                dfs(stones[i][0], stones[i][1], stones, visit);
            }
        }
    }
}

int removeStones(int** stones, int stonesSize, int* stonesColSize){
    if (stones == NULL || stonesSize == 0) {
        return 0;
    }
    int *visit = (int *)malloc(sizeof(int) * stonesSize);
    memset(visit, 0, sizeof(int) * stonesSize);
    int num = 0; // 连通数
    row = stonesSize;
    for (int i = 0; i < stonesSize; i++) {
            if (visit[i] == 0) {
                num++;
                visit[i] = 1;
                //printf("%d %d\n", stones[i][0], stones[i][1]);
                dfs(stones[i][0], stones[i][1], stones, visit);
            }
    }
    return stonesSize - num;

}

/*
301. 删除无效的括号
难度困难217
删除最小数量的无效括号，使得输入的字符串有效，返回所有可能的结果。
说明: 输入可能包含了除 ( 和 ) 以外的字符。
示例 1:
输入: "()())()"
输出: ["()()()", "(())()"]
示例 2:
输入: "(a)())()"
输出: ["(a)()()", "(a())()"]

*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int gResultSize = 0;
char **gResult;
bool IsValid(char *s){
    int cnt = 0;
    char *p = s;
    while (*p != '\0') {
        if (*p == '(') {
            cnt++;
        }
        else if (*p == ')') {
            cnt--;
        }
        if (cnt < 0) {
            return false;
        }
        p++;
    }
    return cnt == 0;
}

void removeInvalidParentheses2(char * s, int sLen , int start, int leftCnt, int rightCnt){
    if (start > sLen) {
        return;
    }
    //printf("enter:%s :%d:%d:%d\n", s, start, leftCnt, rightCnt);
    if (leftCnt == 0 && rightCnt == 0) {
        //printf("wait:%s\n", s);
        if (IsValid(s)) {
            gResult[gResultSize] = malloc(sizeof(char) * sLen + 1);
            strcpy(gResult[gResultSize], s);
            gResultSize++;
            //printf("%s\n", s);
        }
        return;
    }
    char subStr[sLen];
    for (int i = start; i < sLen; ++i) {
        if (i > start && s[i] == s[i - 1]){
            continue;
        }
        if (s[i] == '(' && leftCnt > 0){
            memcpy(subStr, s, i);
            subStr[i] = '\0';
            strcat(subStr, s + i + 1);
            removeInvalidParentheses2(subStr, sLen - 1, i, leftCnt - 1, rightCnt);
        } else if (s[i] == ')' && rightCnt > 0){
            memcpy(subStr, s, i);
            subStr[i] = '\0';
            strcat(subStr, s + i + 1);
            //printf("subStr-->%s\n", subStr);
            removeInvalidParentheses2(subStr, sLen - 1, i, leftCnt, rightCnt - 1);
        }
    }
}
#define MAX_RESULT_LEN 10000
char ** removeInvalidParentheses(char * s, int* returnSize){
    int leftCnt = 0;
    int rightCnt = 0;
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] == '(') {
            leftCnt++;
        } else if (s[i] == ')'){
            if (leftCnt == 0){
                rightCnt++;
            } else {
                leftCnt--;
            }
        }
    }
    char **ans = malloc(sizeof(char*) * MAX_RESULT_LEN);
    memset(ans, 0, sizeof(char*) * MAX_RESULT_LEN);
    gResult = ans;
    gResultSize = 0;
    removeInvalidParentheses2(s, strlen(s), 0, leftCnt, rightCnt);
    //printf("%d\n", gResultSize);
    if (gResultSize == 0){
        gResult[0] = "";
        gResultSize = 1;
    }
    *returnSize = gResultSize;

    return ans;
}
#define MAX_QUEUE_SIZE 10000
#define MAX_WORD_SIZE  50
#define LEFT_P '('
#define RIGHT_P ')'

struct Queue {
    char** parentheses;
    int head;
    int rear;
};
typedef struct Queue Queue_t;

void InitQueue(Queue_t* que)
{
    que->parentheses = (char**)calloc(MAX_QUEUE_SIZE, sizeof(char*));
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        que->parentheses[i] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
    }
    que->head = que->rear = 0;
}

void DeInitQueue(Queue_t* que)
{
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        free(que->parentheses[i]);
    }
    free(que->parentheses);
}

bool IsEmpty(Queue_t* que)
{
    return que->head == que->rear;
}

void EnQueue(Queue_t* que, char* strParentheses)
{
    strcpy(que->parentheses[que->rear], strParentheses);
    que->rear = (que->rear + 1) % MAX_QUEUE_SIZE;
}

void DeQueue(Queue_t* que, char** strParentheses)
{
    if (que->head >= que->rear) {
        return;
    }

    // strcpy(strParentheses, que->parentheses[que->head]);
    *strParentheses =  que->parentheses[que->head];
    que->head = (que->head + 1) % MAX_QUEUE_SIZE;
}

int GetQueueSize(Queue_t* que)
{
    return que->rear - que->head;
}

bool IsStringValid(char* pString, int* delta)
{
    int leftCount = 0;
    int rightCount = 0;
    bool flag = true;
    for (int i = 0; i < strlen(pString); i++) {
        if (pString[i] == LEFT_P) {
            leftCount++;
        } else if (pString[i] == RIGHT_P) {
            rightCount++;
        }
        if (leftCount < rightCount) {
            flag = false;
        }
    }
    *delta = leftCount - rightCount;
    if (flag && *delta == 0) {
        return true;
    } else {
        return false;
    }
}

bool IsInQueue(char* pString, Queue_t* que)
{
    for (int i = que->head; i < que->rear; i++) {
        if (strcmp(pString, que->parentheses[i]) == 0) {
            return true;
        }
    }
    return false;
}

void RemoveChar(char* pString, int index)
{
    int len = strlen(pString);
    if (index < 0 || index >= len) {
        return;
    }

    for (int i = index; i < len - 1; i++) {
        pString[i] = pString[i + 1];
    }
    pString[len - 1] = '\0';
}

void BFS(Queue_t* quePtr, char** rst, int* returnSize)
{
    char* tmpStr = NULL;
    bool flag = false;
    int delta = 0;

    while (!IsEmpty(quePtr)) {
        int curSize = GetQueueSize(quePtr);
        for (int i = 0; i < curSize; i++) {
            // termination is result ok
            DeQueue(quePtr, &tmpStr);
            // process
            if (IsStringValid(tmpStr, &delta)) {
                rst[*returnSize] = (char*)calloc(strlen(tmpStr) + 1, sizeof(char));
                strcpy(rst[*returnSize], tmpStr);
                *returnSize = *returnSize + 1;
                flag = true;
            }

            // drill down and enqueue
            if (!flag) { // if find result this round
                for (int k = 0; k < strlen(tmpStr); k++) {
                    if (tmpStr[k] != LEFT_P && tmpStr[k] != RIGHT_P) {
                        continue;
                    }

                    if (tmpStr[k] == LEFT_P && delta < 0) {
                        continue;
                    }

                    if (tmpStr[k] == RIGHT_P && delta > 0) {
                        continue;
                    }

                    char* tmpStr2 = (char*)calloc(strlen(tmpStr) + 1, sizeof(char));
                    strcpy(tmpStr2, tmpStr);
                    RemoveChar(tmpStr2, k);
                    if (!IsInQueue(tmpStr2, quePtr)) {
                        EnQueue(quePtr, tmpStr2);
                    } else {
                        free(tmpStr2);
                    }
                }
            }
        }
        if (flag) {
            return;
        }
    }
    return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeInvalidParentheses(char* s, int* returnSize)
{
    Queue_t que;
    InitQueue(&que);
    EnQueue(&que, s);
    char** rst = (char**)calloc(MAX_QUEUE_SIZE, sizeof(char*));
    *returnSize = 0;

    BFS(&que, rst, returnSize);
    return rst;
}

void GetInvalidNum(char *s, int *left, int *right) {
    int leftNum = 0;
    int rightNum = 0;

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(') {
            leftNum++;
        } else if (s[i] == ')') {
            if (leftNum > 0) {
                leftNum--;
            } else {
                rightNum++;
            }
        }
    }
    *left = leftNum;
    *right = rightNum;
    return;
}

bool IsValid(char *s) {
    int leftNum = 0;

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(') {
            leftNum++;
        } else if (s[i] == ')') {
            leftNum--;
        }
        if (leftNum < 0) {
            return false;
        }
    }
    return leftNum == 0 ? true : false;
}

void AddToArry(char *s, char **returnArry, int *returnSize) {
    int row = *returnSize;
    returnArry[row] = (char *)malloc((strlen(s) + 1) * sizeof(char));
    memcpy(returnArry[row], s, (strlen(s) + 1) * sizeof(char));
    *returnSize = row + 1;
    return;
}

void DeletChar(char *s, int num) {
    char *p = s;
    char *q = s;
    for (int i = 0; i < strlen(s); i++) {
        if (i == num) {
            q++;
        }
        *(p++) = *(q++);
    }

    *p = '\0';
    return;
}

void dfs(char *s, int left, int right, int start, char **returnArry, int *returnSize) {
    char *temp;
    if ((left == 0) && (right == 0)) {
        if (IsValid(s)) {
            AddToArry(s, returnArry, returnSize);
        }
        return;
    }

    temp = (char *)malloc((strlen(s)+1) * sizeof(char));
    for (int i = start; i < strlen(s); i++) {
        if ((i >= 1) && (s[i] == s[i-1])) {
            continue;
        }

        memcpy(temp, s, strlen(s)+1);

        if ((left > 0) && (s[i] == '(')) {
            DeletChar(temp, i);
            dfs(temp, left-1, right, i, returnArry, returnSize);
        }
        if ((right > 0) && (s[i] == ')')) {
            DeletChar(temp, i);
            dfs(temp, left, right-1, i, returnArry, returnSize);
        }
    }

    return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** removeInvalidParentheses(char * s, int* returnSize){
    int left, right;
    char **returnArry;

    returnArry = (char **)malloc(100 * sizeof(char *));
    memset(returnArry, 0, 100 * sizeof(char *));
    *returnSize = 0;
    GetInvalidNum(s, &left, &right);
    dfs(s, left, right, 0, returnArry, returnSize);

    return returnArry;
}
