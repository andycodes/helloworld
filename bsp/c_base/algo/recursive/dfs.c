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
连通器个数
*/


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
int cmp_int ( const void *a , const void *b)
{
        return *(int *)a > *(int *)b;
}

void dfs(int* candidates, int candidatesSize, int cidx,
    int target, int* returnSize, int** returnColumnSizes,
    int **res, int *path, int pathSize)
{
	if (target == 0) {
		res[*returnSize] = (int*)calloc(1024, sizeof(int));
		memcpy(res[*returnSize], path, sizeof(int) * pathSize);
		(*returnColumnSizes)[*returnSize] = pathSize;
		(*returnSize)++;
		return;
	}

	/*cidx:
		for : cidx~candidatesSize
		2367所有组合可能
		  367所有组合可能
		   67所有组合可能
		     7所有组合可能
	*/
	for (int i = cidx; i < candidatesSize &&  candidates[i] <= target; i++) {
		path[pathSize] = candidates[i];
		dfs(candidates, candidatesSize, i, target - candidates[i],
			returnSize, returnColumnSizes, res, path, pathSize + 1);
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
	int path[1024] = {0};
	dfs(candidates, candidatesSize, 0, target, returnSize, returnColumnSizes, res, path, 0);
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
int dis[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
void dfs(int** g, int gridSize, int* gridColSize, int cx, int cy, int oldcolor, int newcolor)
{
	// 越界 || 不属于同一个联通分量 || 被访问过
	if(cx < 0 || cx >= gridSize || cy < 0 || cy >= gridColSize[cx] ||
		g[cx][cy] != oldcolor || g[cx][cy] < 0) {
		return;
	}

	// 当前节点已经被访问，设置负值
	g[cx][cy] = -oldcolor;

	// 判断边界
	if(cx == 0 || cx+1 >= gridSize || cy == 0 || cy+1 >= gridColSize[cx]) {
		// 区域边界
		g[cx][cy] = -newcolor;
	} else {
		// 连通分量的边界
		for(int i = 0 ; i < 4 ; i++) {
			int nextColor = g[cx + dis[i][0]][cy + dis[i][1]];
			// 这里是关键点
			if(nextColor != oldcolor && nextColor != -oldcolor && nextColor != -newcolor) {
				g[cx][cy] = -newcolor;
				break;
			}
		}
	}

	for(int i = 0 ; i < 4 ; i++) {
		dfs(g, gridSize, gridColSize, cx+dis[i][0], cy+dis[i][1], oldcolor, newcolor);
	}
}

int** colorBorder(int** grid, int gridSize, int* gridColSize, int r0, int c0,
	int color, int* returnSize, int** returnColumnSizes)
{
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

int dirs[4][2] = {
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
		int nx = row + dirs[i][0];
		int ny = col + dirs[i][1];

		//坐标越界检查
		if(nx >= gridSize || nx < 0 || ny < 0 || ny >= gridColSize[row]){
			continue;
		}
		/*
		判断该邻居是否有对应方向(即3-i)的接口，
		*/
		if(interfaces[grid[nx][ny]][3-i]) {
			dfs(grid, gridSize, gridColSize, nx, ny);
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

/*DFS自底向上
1) 从每个叶子节点出发递归向上,得出每个路劲的累计分
钟
2)球各个路径最大值
*/
int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime,
int informTimeSize)
{
	int res = 0;

	for(int i =0;i<managerSize;i++){
		if(informTime[i]==0){ //叶子节点
			//临时值
			int temp = 0;
			int index=i;
			//向上遍历
			while(index!=-1) {
				temp+=informTime[index];
				index=manager[index];
			}
			res = fmax(res,temp);
		}
	}
	return res;
}

/*DFS自底向上
遍历所有员工，对所有最底层员工（叶子节点），
DFS搜索父节点，直到没有父节点为止。记录所有遍历
的最大时间即为答案。*/
int dfs(int* manager, int *informTime, int id, int t)
{
    int m = manager[id];
    if (m == -1) {
        return t;
    }
    return dfs(manager, informTime, m, t + informTime[m]);
}

int numOfMinutes(int n, int headID, int* manager, int managerSize,
int* informTime, int informTimeSize)
{
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (informTime[i] != 0) {//不是叶子节点
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
再以headid为起点，进行树的遍历，记录搜索过程中计算出
的
最大通知时间，即为答案。
*/

/*
959 unionfind
*/
int d[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
void dfs(int x, int y, int n, int grid[n][n])
{
	grid[x][y] = 1;

	for (int i = 0; i < 4; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
			continue;
		}

		if (grid[nx][ny] == 1)
			continue;

		dfs(nx, ny, n, grid);
	}
}

int regionsBySlashes(char ** grid, int gridSize)
{
	int n = gridSize;
	int newGridSize = 3 * n;
	int newGrid[newGridSize][newGridSize];
	memset(newGrid, 0, sizeof(newGrid));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] == '/') {
				newGrid[3*i][3*j+2] = 1;
				newGrid[3*i+1][3*j+1] = 1;
				newGrid[3*i+2][3*j] = 1;
			} else if (grid[i][j] == '\\') {
				newGrid[3*i][3*j] = 1;
				newGrid[3*i+1][3*j+1] = 1;
				newGrid[3*i+2][3*j+2] = 1;
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < 3*n; ++i) {
		for (int j = 0; j < 3*n; ++j) {
			if (newGrid[i][j] == 0) {
				cnt++;
				dfs(i, j, newGridSize, newGrid);
			}
		}
	}

	return cnt;
}

/*
301. 删除无效的括号
难度困难217
删除最小数量的无效括号，使得输入的字符串有效，返
回所有可能的结果。
说明: 输入可能包含了除 ( 和 ) 以外的字符。
示例 1:
输入: "()())()"
输出: ["()()()", "(())()"]
示例 2:
输入: "(a)())()"
输出: ["(a)()()", "(a())()"]

*/
void GetInvalidNum(char *s, int *left, int *right)
{
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
}

bool IsValid(char *s)
{
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

void DeletChar(char *s, int num)
{
	char *p = s;
	char *q = s;
	for (int i = 0; i < strlen(s); i++) {
		if (i == num) {
			q++;
		}
		*(p++) = *(q++);
	}

	*p = '\0';
}

void dfs(char *s, int left, int right, int start, char **res, int *returnSize)
{
	char *temp;
	if ((left == 0) && (right == 0)) {
		if (IsValid(s)) {
			res[*returnSize] = strdup(s);
			(*returnSize)++;
		}
		return;
	}

	temp = (char *)malloc((strlen(s)+1) * sizeof(char));
	for (int i = start; i < strlen(s); i++) {
		/*
		重复情况，比如，())()有两个相同的括号)连在一起，那么选择前一个删除后一个，或者删除前一个选择后一个这两种情况是相同的，会导致重复的情况，很显然我们不想重复。作者：durant-5链接：https://leetcode-cn.com/problems/remove-invalid-parentheses/solution/jian-zhi-de-yi-xie-xi-jie-by-durant-5/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
		*/
		if ((i >= 1) && (s[i] == s[i-1])) {
			continue;
		}

		memcpy(temp, s, strlen(s)+1);

		if ((left > 0) && (s[i] == '(')) {
			DeletChar(temp, i);
			dfs(temp, left-1, right, i, res, returnSize);
		}

		if ((right > 0) && (s[i] == ')')) {
			DeletChar(temp, i);
			dfs(temp, left, right-1, i, res, returnSize);
		}
	}
}

char ** removeInvalidParentheses(char * s, int* returnSize)
{
	int left, right;
	char **res;

	res = (char **)calloc(100, sizeof(char *));
	*returnSize = 0;
	GetInvalidNum(s, &left, &right);
	dfs(s, left, right, 0, res, returnSize);

	return res;
}


/*
93. 复原IP地址
难度中等320
给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
有效的 IP 地址正好由四个整数（每个整数位于 0 到 255 之间组成），整数之间用 '.' 分隔。

示例:
输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]
*/
#define MAX_SIZE 1024
bool isValid(char *s, int len)
{
	if (s == '\0') {
		return false;
	}

	if (s[0] == '0' && len > 1) {
		return false;
	}

	int num = 0;
	for (int i = 0; i < len; i++) {
		num = num * 10 + s[i] - '0';
	}
	if (num >= 0 && num <= 255) {
		return true;
	}
	return false;
}

void dfs(char *s, char **res, int *returnSize, char *path, int pathSize, int validNum)
{
	if (validNum > 4) {
		return;
	}

	if (s[0] == '\0' && validNum == 4) {
		res[*returnSize] = strdup(path);
		(*returnSize)++;
	}

	if (validNum > 0 && validNum < 4) {
		path[pathSize++] = '.';
	}

	for (int substrlen = 1; substrlen <= 3 && substrlen <= strlen(s); substrlen++) {
		if (!isValid(s, substrlen)) {
			continue;
		}

		for (int i = 0; i < substrlen; i++) {
			path[pathSize + i] = s[i];
		}
		dfs(s + substrlen, res, returnSize, path, pathSize + substrlen, validNum + 1);
	}
}

char ** restoreIpAddresses(char * s, int* returnSize)
{
	char **res = (char **)malloc(MAX_SIZE * sizeof(char *));
	*returnSize = 0;
	char *path = (char *)calloc(strlen(s) + 4, sizeof(char));
	dfs(s, res, returnSize, path, 0, 0);
	return res;
}


/*
491. 递增子序列
难度中等104
给定一个整型数组, 你的任务是找到所有该数组的递增子
序列，递增子序列的长度至少是2。
示例:
输入: [4, 6, 7, 7]
输出: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
说明:
1.	给定数组的长度不会超过15。
2.	数组中的整数范围是 [-100,100]。
3.	给定数组中可能包含重复数字，相等的数字应该被视
为递增的一种情况。
*/

#define BIG_NUM 100000
void dfs(int* nums, int numsSize, int *path, int index, int pathsize,
int **ret, int *retCol, int *returnSize)
{
	int map[201] = {0};

	if (pathsize > 1) {
		ret[*returnSize] = malloc(sizeof(int) * pathsize);
		memcpy(ret[*returnSize], path, sizeof(int) * pathsize);
		retCol[*returnSize] = pathsize;
		(*returnSize)++;
	}

	for (int i = index; i < numsSize; i++) {
		// 去重，本层不重复遍历相同的数字
		if (map[nums[i]+100] != 0) {
			continue;
		}

		map[nums[i]+100] = 1;

		if (pathsize > 0) {
			if (nums[i] >= path[pathsize-1]) {
				path[pathsize] = nums[i];
				dfs(nums, numsSize, path, i+1, pathsize+1, ret, retCol, returnSize);
			}
		} else {
			path[pathsize] = nums[i];
			dfs(nums, numsSize, path, i+1, pathsize+1, ret, retCol, returnSize);
		}
	}
}

int** findSubsequences(int* nums, int numsSize,
	int* returnSize, int** returnColumnSizes)
{
	int **res = malloc(sizeof(int *) * BIG_NUM);
	int *retCol = malloc(sizeof(int) * BIG_NUM);
	int path[15] = {0};
	*returnSize = 0;
	dfs(nums, numsSize, path, 0, 0, res, retCol, returnSize);
	*returnColumnSizes = retCol;
	return res;
}

/*
133. 克隆图
给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）。
图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。
class Node {
    public int val;
    public List<Node> neighbors;
}

测试用例格式：
简单起见，每个节点的值都和它的索引相同。例如，第一个节点值为 1（val = 1），第二个节点值为 2（val = 2），以此类推。该图在测试用例中使用邻接列表表示。
邻接列表 是用于表示有限图的无序列表的集合。每个列表都描述了图中节点的邻居集。
给定节点将始终是图中的第一个节点（值为 1）。你必须将 给定节点的拷贝 作为对克隆图的引用返回。

示例 1：

输入：adjList = [[2,4],[1,3],[2,4],[1,3]]
输出：[[2,4],[1,3],[2,4],[1,3]]
解释：
图中有 4 个节点。
节点 1 的值是 1，它有两个邻居：节点 2 和 4 。
节点 2 的值是 2，它有两个邻居：节点 1 和 3 。
节点 3 的值是 3，它有两个邻居：节点 2 和 4 。
节点 4 的值是 4，它有两个邻居：节点 1 和 3 。
示例 2：

*/
struct Node* dfs(struct Node* s, struct Node** visited)
{
	if (s == NULL) {
		return NULL;
	}
/*
如果该节点已经被访问过了，则直接从哈希表中取出对
应的克隆节点返回
*/
	if (visited[s->val]) {
		return visited[s->val];
	}
/*
克隆节点，注意到为了深拷贝我们不会克隆它的邻居的
列表
*/
	struct Node* cloneNode = (struct Node*)malloc(sizeof(struct Node));
	cloneNode->val = s->val;
	cloneNode->numNeighbors = s->numNeighbors;

// 哈希表存储
	visited[cloneNode->val] = cloneNode;
	cloneNode->neighbors = (struct Node**)malloc(sizeof(struct Node*) * cloneNode->numNeighbors);

// 遍历该节点的邻居并更新克隆节点的邻居列表
	for (int i = 0; i < cloneNode->numNeighbors; i++) {
		cloneNode->neighbors[i] = dfs(s->neighbors[i], visited);
	}
	return cloneNode;
}

struct Node* cloneGraph(struct Node* s)
{
	struct Node** visited = (struct Node**)calloc(101, sizeof(struct Node*));
	return dfs(s, visited);
}

