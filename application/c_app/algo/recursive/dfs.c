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


组合问题(子序列)
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
		/* i  :每个数字在每个组合中重复使用 */
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
int start, int **res, int *path, int pathSize)
{
	if (target == 0) {
		res[*returnSize] = (int *)calloc(1024, sizeof(int));
		memcpy(res[*returnSize], path, pathSize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = pathSize;
		(*returnSize)++;
		return;
	}

	for (int i = start; i < candidatesSize && target > 0 && candidates[i] <= target; i++) {
		if ( i > start && candidates[i] == candidates[i - 1])
			continue;

        	path[pathSize] = candidates[i];
		dfs(candidates, candidatesSize, target - candidates[i],
		returnSize, returnColumnSizes, i + 1, res, path, pathSize  + 1);
		/* i + 1 :每个数字在每个组合中只能使用一次 */
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
	int path[1024] = {0};

	qsort(candidates, candidatesSize, sizeof(int), cmp_int);
	dfs(candidates, candidatesSize, target,
	returnSize, returnColumnSizes, 0, res, path, 0);
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
int **res, int *path, int pathsize, int cidx)
{
	if (k == 0 && n == 0) {
		res[*returnSize] = (int *)calloc(pathsize, sizeof(int));
		memcpy(res[*returnSize], path, pathsize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = pathsize;
		(*returnSize)++;
		return;
	}

	for (int i = cidx; i <= 9 && k > 0 && n > 0 && i <= n; i++) {
		path[pathsize] = i;
		/*i + 1 :每种组合中不存在重复的数字。
		因为结果集里的元素互不相同，
		因此下一层搜索的起点应该是上一层搜索的起点值 + 1；*/
		dfs(k - 1, n  - i, returnSize, returnColumnSizes, res, path, pathsize + 1, i + 1);
	}
}

int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes)
{
	int **res = (int **)calloc(1024, sizeof(int **));
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));
	*returnSize = 0;
	int path[1024] = {0};
	dfs(k, n, returnSize, returnColumnSizes, res, path, 0, 1);
	return res;
}

/*
90. 子集 II
给定一个可能包含重复元素的整数数组 nums，返回该数组所有
可能的子集（幂集）。
说明：解集不能包含重复的子集。
示例:
输入: [1,2,2]
输出:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/
void dfs(int* nums, int numsSize, int* returnSize, int** returnColumnSizes,
	int **res, int *path, int pathSize, int ccx)
{
	res[*returnSize] = (int *)calloc(pathSize, sizeof(int));
	memcpy(res[*returnSize], path, sizeof(int) * pathSize);
	(*returnColumnSizes)[*returnSize] = pathSize;
	(*returnSize)++;

	for (int i = ccx; i < numsSize; i++) {
		if (i > ccx && nums[i] == nums[i - 1]) {
			continue;
		}

		path[pathSize] = nums[i];
		dfs(nums, numsSize, returnSize, returnColumnSizes, res, path, pathSize + 1, i + 1);
	}
}

int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);
	int resSize = fmax(1024, pow(2, numsSize));
	*returnColumnSizes = (int *)calloc(resSize, sizeof(int));
	int **res = (int **)calloc(resSize, sizeof(int *));
	int path[numsSize];
	memset(path, 0, sizeof(path));

	dfs(nums, numsSize, returnSize, returnColumnSizes, res, path, 0, 0);
	return res;
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
int numOfMinutes(int n, int headID, int* manager, int managerSize,
int* informTime, int informTimeSize)
{
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (informTime[i] != 0) { //叶子节点
			continue;
		}

		int root = manager[i];
		int sum = 0;
		while(root != -1) {
			sum += informTime[root];
			root = manager[root];
		}

		max = fmax(sum, max);
	}

	return max;
}

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
		if (informTime[i] != 0) {
			continue;
		}

		int t = dfs(manager, informTime, i, 0);
		max = fmax(max, t);
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

void delChar(char *s, int num)
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
	if ((left == 0) && (right == 0)) {
		if (IsValid(s)) {
			res[*returnSize] = strdup(s);
			(*returnSize)++;
		}
		return;
	}

	int slen = strlen(s) + 1;
	char temp[slen];
	for (int i = start; i < strlen(s); i++) {
		/*
		重复情况，比如，())()有两个相同的括号)连在一起，那么
		选择前一个删除后一个，或者删除前一个选择后一个这两
		种情况是相同的，会导致重复的情况，很显然我们不想重
		复。
		*/
		if ((i > start) && (s[i] == s[i-1])) {
			continue;
		}

		strcpy(temp, s);

		if ((left > 0) && (s[i] == '(')) {
			delChar(temp, i);
			dfs(temp, left-1, right, i, res, returnSize);
		}

		if ((right > 0) && (s[i] == ')')) {
			delChar(temp, i);
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

void dfs(char *s, char **res, int *returnSize, char *path, int pathSize, int groupNum)
{
	if (groupNum > 4) {
		return;
	}

	if (s[0] == '\0' && groupNum == 4) {
		res[*returnSize] = strdup(path);
		(*returnSize)++;
		return;
	}

	if (groupNum > 0) {
		path[pathSize++] = '.';
	}

	for (int substrlen = 1; substrlen <= 3 && substrlen <= strlen(s); substrlen++) {
		if (!isValid(s, substrlen)) {
			continue;
		}

		for (int i = 0; i < substrlen; i++) {
			path[pathSize + i] = s[i];
		}

		dfs(s + substrlen, res, returnSize, path, pathSize + substrlen, groupNum + 1);
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

/*
967. 连续差相同的数字
返回所有长度为 N 且满足其每两个连续位上的数字之间的
差的绝对值为 K 的非负整数。
请注意，除了数字 0 本身之外，答案中的每个数字都不能
有前导零。例如，01 因为有一个前导零，所以是无效的；
但 0 是有效的。
你可以按任何顺序返回答案。
示例 1：
输入：N = 3, K = 7
输出：[181,292,707,818,929]
解释：注意，070 不是一个有效的数字，因为它有前导零。
示例 2：
输入：N = 2, K = 1
输出：[10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
提示：
1 <= N <= 9
0 <= K <= 9
通过次数3,737提交次数9,891
*/
#define MAX_SIZE 5000
void dfs(int N, int K, int *res, int *returnSize, int num, int result)
{
	if (result != 0 && abs((result) % 10 - num) != K) {
	// 不满足连续两位相差K，直接返回
		return;
	}

	if (N == 1) { //当 N== 1 时，N位数满足条件，填到res结果中
		result = (result) * 10 + num;  //本次匹配的结果
		res[(*returnSize)++] = result;
		return;
	}

	for (int i = 0; i < 10; i++) {
		dfs(N - 1, K, res, returnSize, i, result * 10 + num);
	}
}
//从高位到低位
int* numsSameConsecDiff(int N, int K, int* returnSize)
{
	*returnSize = 0;
	if (N == 1) {
		int *res = (int *)malloc(10 * sizeof(int));
		for (int i = 0; i < 10; i++) {
			res[(*returnSize)++] = i;
		}
		return res;
	}

	int *res = (int *)malloc(MAX_SIZE * sizeof(int));

	for (int i = 1; i < 10; i++) {
		dfs(N, K, res, returnSize, i, 0);
	}

	return res;
}

/*
329. 矩阵中的最长递增路径
给定一个整数矩阵，找出最长递增路径的长度。

对于每个单元格，你可以往上，下，左，右四个方向移动。 你不能在对角线方向上移动或移动到边界外（即不允许环绕）。

示例 1:

输入: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
输出: 4
解释: 最长递增路径为 [1, 2, 6, 9]。
*/
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int dfs(int** matrix, int row, int col, int visited[row][col][4], int cx, int cy)
{
	int max = 0;
	for (int i = 0; i < 4; i++) {
		int nx = cx + dir[i][0];
		int ny = cy + dir[i][1];

		if (nx < 0 || nx >= row ||ny < 0 || ny >= col) {
			continue;
		}

		if (matrix[nx][ny] <= matrix[cx][cy]) {
			continue;
		}

		if (visited[nx][ny][i] == 1) {
			continue;
		}

		visited[nx][ny][i] = 1;

		max = fmax(max, dfs(matrix, row, col, visited, nx, ny));
	}

	return max + 1;
}

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize)
{
	if (matrix == NULL || matrixSize <= 0 || matrixColSize == NULL)
		return 0;

	int row = matrixSize;
	int col = *matrixColSize;
	int max = 1;
	int visited[row][col][4];

	for(int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			memset(visited, 0, sizeof(visited));
			max = fmax(max, dfs(matrix, row, col, visited, i,j));
		}
	}

	return max;
}

/*
面试题 08.06. 汉诺塔问题
在经典汉诺塔问题中，有 3 根柱子及 N 个不同大小的穿孔圆盘，盘子可以滑入任意一根柱子。一开始，所有盘子自上而下按升序依次套在第一根柱子上(即每一个盘子只能放在更大的盘子上面)。移动圆盘时受到以下限制:
(1) 每次只能移动一个盘子;
(2) 盘子只能从柱子顶端滑出移到下一根柱子;
(3) 盘子只能叠在比它大的盘子上。

请编写程序，用栈将所有盘子从第一根柱子移到最后一根柱子。

你需要原地修改栈。

示例1:

 输入：A = [2, 1, 0], B = [], C = []
 输出：C = [2, 1, 0]
示例2:

 输入：A = [1, 0], B = [], C = []
 输出：C = [1, 0]
*/
#define MAX_LEN 200
typedef struct {
    int* data;
    int size;
}Stack;
int cnt = 0;
void Push(Stack* s, int d)
{
    s->data[s->size++] = d;
}
int Pop(Stack* s){
    return s->data[--s->size];
}

void hannuota(int n, Stack* A, Stack* B, Stack* C){
    if(n == 1){
        cnt ++;
        Push(C, Pop(A));
        return;
    }
    hannuota(n-1, A, C, B);
    hannuota(1, A, B, C);
    hannuota(n-1, B, A, C);
}

void hanota(int* A, int ASize, int* B, int BSize, int** C, int* CSize){
    if(ASize <= 0) return;
    Stack X,Y,Z;
    X.data = A;
    X.size = ASize;
    Y.data = (int*)malloc(sizeof(int)*MAX_LEN);
    Y.size = 0;
    int *p = (int*)malloc(sizeof(int)*MAX_LEN);
    Z.data = p;
    Z.size = 0;
    hannuota(ASize, &X, &Y, &Z);
    *C = p;
    *CSize = Z.size;
    free(Y.data);
}

/*
248. 中心对称数 III
中心对称数是指一个数字在旋转了 180 度之后看起来依旧相同的数字（或者上下颠倒地看）。

写一个函数来计算范围在 [low, high] 之间中心对称数的个数。

示例:

输入: low = "50", high = "100"
输出: 3
解释: 69，88 和 96 是三个在该范围内的中心对称数
*/

int g_ret;
char a[] = {'9', '6', '8', '1', '0'};
void Dfs(char *low, char *high, int n, int step, char *buff)
{
    int m = (n + 1) / 2;
    if (m < step) {
        if (strlen(low) == n && strcmp(buff, low) >= 0) {
            if (strlen(high) > n || strcmp(buff, high) <= 0) {
                g_ret++;
            }
        } else if (strlen(high) == n && strcmp(buff, high) <= 0) {
            if (strlen(low) < n || strcmp(buff, low) >= 0) {
                g_ret++;
            }
        }
        return;
    }
    if (step == 1 && n % 2 == 1) {
        for (int i = 2; i < 5; i++) {
            buff[m - step] = a[i];
            Dfs(low, high, n, step + 1, buff);
        }
        return;
    }
    if (m == step) {
        for (int i = 0; i < 4; i++) {
            buff[m - step] = a[i];
            buff[n - m + step - 1] = i < 2 ? a[1 - i] : a[i];
            Dfs(low, high, n, step + 1, buff);
        }
        return;
    }
    for (int i = 0; i < 5; i++) {
        buff[m - step] = a[i];
        buff[n - m + step - 1] = i < 2 ? a[1 - i] : a[i];
        Dfs(low, high, n, step + 1, buff);
    }
}
void Calc(char *low, char *high, int n)
{
    char *buff = (char*)calloc(n + 1, 1);
    Dfs(low, high, n, 1, buff);
    free(buff);
}
int Calc1(int n)
{
    int count;
    if (n % 2 == 1) {
        count = 3;  // 中心位置
    } else {
        count = 1;
    }
    n -= 2;
    count *= 4; // 首尾
    n /= 2;
    while (n > 0) {
        count *= 5;
        n--;
    }
    return count;
}
int strobogrammaticInRange(char * low, char * high)
{
    g_ret = 0;
    if (strlen(low) == strlen(high)) {
        if (strcmp(high, low) < 0) {
            return g_ret;
        }
    } else if (strlen(low) > strlen(high)) {
        return g_ret;
    }

    if (strlen(high) > strlen(low)) {
        Calc(low, high, strlen(high));
        Calc(low, high, strlen(low));
        int n = strlen(high) - 1;
        while (n > strlen(low)) {
            g_ret += Calc1(n);
            n--;
        }
    } else {
        Calc(low, high, strlen(high));
    }
    return g_ret;
}

/*
761. 特殊的二进制序列
特殊的二进制序列是具有以下两个性质的二进制序列：

0 的数量与 1 的数量相等。
二进制序列的每一个前缀码中 1 的数量要大于等于 0 的数量。
给定一个特殊的二进制序列 S，以字符串形式表示。定义一个操作 为首先选择 S 的两个连续且非空的特殊的子串，然后将它们交换。（两个子串为连续的当且仅当第一个子串的最后一个字符恰好为第二个子串的第一个字符的前一个字符。)

在任意次数的操作之后，交换后的字符串按照字典序排列的最大的结果是什么？

示例 1:

输入: S = "11011000"
输出: "11100100"
解释:
将子串 "10" （在S[1]出现） 和 "1100" （在S[3]出现）进行交换。
这是在进行若干次操作后按字典序排列最大的结果。
*/
int cmp(const void *a, const void *b) {
    char *a1 = *(char **)a;
    char *b1 = *(char **)b;

    int tt = strcmp(a1, b1);
    return -tt;
}

char * makeLargestSpecial(char * S){

    if ((NULL == S) || (strlen(S) <= 2)) return S;

    int len = strlen(S);

    int cnt = 0;
    int substrnum = 0, substrpos[len / 2];
    for (int i = 0; i < len; i++) {
        cnt += ('1' == S[i]) ? 1 : -1;
        if (0 == cnt) substrpos[substrnum++] = i;
    }

    char *res = (char *) malloc(sizeof(char) * (len + 1));
    memset(res, '\0', len + 1);

    int tmp = 0;
    if (1 == substrnum) {
        res[0] = '1';
        res[len - 1] = '0';
        char * substr = (char *) malloc(sizeof(char) * (len - 1));
        memset(substr, '\0', len - 1);
        for (int i = 1; i < len - 1; i++) {
            substr[tmp++] = S[i];
        }
        substr = makeLargestSpecial(substr);
        tmp = 0;
        for (int j = 1; j < len - 1; j++) res[j] = substr[tmp++];
    } else {

        char **str = (char **) malloc(sizeof(char*) * substrnum);
        for (int i = 0; i < substrnum; i++) {
            str[i] = (char *) malloc(sizeof(char) * (len - 1));
            memset(str[i], '\0', len - 1);
            int custrlen = (i > 0) ? (substrpos[i] - substrpos[i - 1]) : (substrpos[i] + 1);
            for (int j = 0; j < custrlen; j++) {
                str[i][j] = S[tmp++];
            }
            str[i] = makeLargestSpecial(str[i]);
        }

        qsort(str, substrnum, sizeof(char *), cmp);
        tmp = 0;
        for (int i = 0; i < substrnum; i++) {
            for(int j = 0; j < strlen(str[i]); j++) {
                res[tmp++] = str[i][j];
            }
        }
    }

    return res;

}

/*
514. 自由之路
电子游戏“辐射4”中，任务“通向自由”要求玩家到达名为“Freedom Trail Ring”的金属表盘，并使用表盘拼写特定关键词才能开门。

给定一个字符串 ring，表示刻在外环上的编码；给定另一个字符串 key，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数。

最初，ring 的第一个字符与12:00方向对齐。您需要顺时针或逆时针旋转 ring 以使 key 的一个字符在 12:00 方向对齐，然后按下中心按钮，以此逐个拼写完 key 中的所有字符。

旋转 ring 拼出 key 字符 key[i] 的阶段中：

您可以将 ring 顺时针或逆时针旋转一个位置，计为1步。旋转的最终目的是将字符串 ring 的一个字符与 12:00 方向对齐，并且这个字符必须等于字符 key[i] 。
如果字符 key[i] 已经对齐到12:00方向，您需要按下中心按钮进行拼写，这也将算作 1 步。按完之后，您可以开始拼写 key 的下一个字符（下一阶段）, 直至完成所有拼写。
示例：





输入: ring = "godding", key = "gd"
输出: 4
解释:
 对于 key 的第一个字符 'g'，已经在正确的位置, 我们只需要1步来拼写这个字符。
 对于 key 的第二个字符 'd'，我们需要逆时针旋转 ring "godding" 2步使它变成 "ddinggo"。
 当然, 我们还需要1步进行拼写。
 因此最终的输出是 4。
*/

#include <limits.h>
#define MMIN(a, b)      ((a) < (b)? (a) : (b))

char *rr;
int rlen;
char *kk;
int klen;

int memo[100][100];

//返回从rid，和kid的位置遍历完序列的最小步骤
int helper(int rid, int kid) {
    if(kid == klen) {
        return 0;
    }

    if(memo[rid][kid] != 0) {
        return memo[rid][kid] - 1;
    }

    int min_steps = INT_MAX;
    int cur_steps = 0;

    //遍历ring，找到所有的相同位置
    for(int i = 0; i < rlen; i++) {
        //实际访问位置
        int id = (rid + i) % rlen;
        if(rr[id] == kk[kid]) {
            cur_steps = MMIN(i, rlen - i);

            int ret = helper(id, kid + 1);

            min_steps = MMIN(min_steps, ret + cur_steps);
        }
    }

    memo[rid][kid] = min_steps + 1;

    return min_steps;
}

//【算法思路】DFS。
int findRotateSteps(char * ring, char * key){
    rr = ring;
    rlen = strlen(ring);
    kk = key;
    klen = strlen(key);

    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            memo[i][j] = 0;
        }
    }

    int ret = helper(0, 0);

    return ret + klen;
}

