/*
深度优先搜索（Depth-First-Search，DFS）是一种
用于遍历或搜索树或图的算法。
沿着树的深度遍历树的节点，
尽可能深的搜索树的分支。
当节点v的所在边都己被探寻过，
搜索将回溯到发现节点v的那条边的起始节点。
这一过程一直进行到已发现从源节点可达
的所有节点为止。如果还存在未被发现的节点，
则选择其中一个作为源节点并重复以上过程，
整个进程反复进行直到所有节点都被访问为止。

DFS模板

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

*/



/*
733. 图像渲染
有一幅以二维整数数组表示的图画，
每一个整数表示该图画的像素值大小，
数值在 0 到 65535 之间。
给你一个坐标 (sr, sc) 表示图像渲染开始的像素值（行 ，列）
和一个新的颜色值 newColor，让你重新上色这幅图像。

为了完成上色工作，从初始坐标开始，
记录初始坐标的上下左右四个方向上像素值与初始坐
标相同的相连像素点，接着再记录这四个方向上符合条
件的像素点与他们对应四个方向上像素值与初始坐标相同
的相连像素点，……，重复该过程。
将所有有记录的像素点的颜色值改为新的颜色值。

最后返回经过上色渲染后的图像。

输入:
image = [
[1,1,1],
[1,1,0],
[1,0,1]
]
sr = 1, sc = 1, newColor = 2
输出:
[
[2,2,2],
[2,2,0],
[2,0,1]]
解析:
在图像的正中间，(坐标(sr,sc)=(1,1)),
在路径上所有符合条件的像素点的颜色都被更改成2。
注意，右下角的像素没有更改为2，
因为它不是在上下左右四个方向上与初始点相连的像素点。

*/
void changeValue(int** image, int imageSize, int* imageColSize,
int sr, int sc, int newColor, int oldColor)
{
	if ( sr < 0 || sr >= imageSize || sc < 0 || sc >= imageColSize[sr] || image[sr][sc] != oldColor)
		return;

	image[sr][sc] = newColor;

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for (int k = 0; k < 4; k++) {
		  changeValue(image, imageSize, imageColSize,
				sr + d[k][0], sc + d[k][1], newColor, oldColor);
	}
}

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc,
	int newColor, int* returnSize, int** returnColumnSizes)
{
	*returnSize = imageSize;
	*returnColumnSizes = malloc(sizeof(int) * imageSize);
	for (int i = 0; i < imageSize; i++) {
		(*returnColumnSizes)[i] = imageColSize[i];
	}

	if (newColor == image[sr][sc])
		return image;

	changeValue(image, imageSize, imageColSize, sr, sc, newColor, image[sr][sc]);
	return image;
}


/*
200. 岛屿数量
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，
计算岛屿的数量。一个岛被水包围，
并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。
你可以假设网格的四个边均被水包围。

示例 1:

输入:
11110
11010
11000
00000

输出: 1

};
*/
void dfs(char** grid, int gridSize, int gridColSize, int x ,int y)
{
	if (x < 0 || x >= gridSize || y < 0 || y >= gridColSize || grid[x][y] == '0')
		return;

	grid[x][y] = '0';//前序操作

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for(int k = 0; k < 4; k++) {
		dfs(grid,gridSize,gridColSize, x + d[k][0], y + d[k][1]);
	}
}

int numIslands(char** grid, int gridSize, int* gridColSize){
	int num = 0;

	if(grid == NULL  || gridSize == 0 || gridColSize == NULL)
		return num;

	for (int i = 0; i < gridSize; i++) {
		for(int j = 0; j < *gridColSize; j++) {
			if (grid[i][j] == '1') {
				num++;
				dfs(grid,gridSize,*gridColSize,i,j);
			}
		}
	}

	return num;
}

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

方法一：暴力法
思路

我们可以生成所有 2^{2n}2
2n
  个 '(' 和 ')' 字符构成的序列。
  然后，我们将检查每一个是否有效。

算法

为了生成所有序列，我们使用递归。长度为 n 的序列就
是 '(' 加上所有长度为 n-1 的序列，以及 ')' 加上所有长度为 n-1 的序列。

为了检查序列是否为有效的，我们会跟踪 平衡，
也就是左括号的数量减去右括号的数量的净值。
如果这个值始终小于零或者不以零结束，
该序列就是无效的，否则它是有效的。

*/

bool isValid(char* str, int strSize)
{
    int balance = 0;

    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == '(')
            balance++;
        else
            balance--;

        if (balance < 0)
            return false;
    }

    return (balance == 0);
}

void generateAll(char* current, int currentSize, int pos, char** res, int* returnSize)
{
    if (pos == currentSize) {
        if (isValid(current, currentSize)) {
            res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
            strcpy(res[*returnSize], current);
            (*returnSize)++;
        }

        return;
    }

	/*当前位置有两种情况*/
	current[pos] = '(';
	generateAll(current, currentSize, pos + 1, res, returnSize);
	current[pos] = ')';
	generateAll(current, currentSize, pos + 1, res, returnSize);
}

char** generateParenthesis(int n, int* returnSize)
{
	*returnSize = 0;
	if (n == 0) {
		return NULL;
	}

	char** res = (char**)calloc(1024 * 1024, sizeof(char*));
	char* current = (char*)calloc(1024 * 1024, sizeof(char));
	generateAll(current, 2 * n, 0, res, returnSize);
	return res;
}

/*
方法二：DFS
思路和算法

加法

只有在我们知道序列仍然保持有效时才添加 '(' or ')'，
而不是像 方法一 那样每次添加。
我们可以通过跟踪到目前为止放置的左括号和
右括号的数目来做到这一点，

如果我们还剩一个位置，我们可以开始放一个左括号。
如果它不超过左括号的数量，我们可以放一个右括号。

*/
void dfs(char** res, int* returnSize, char* current, int currentSize, int leftCnt, int rightCnt, int max)
{
	if (currentSize == max * 2) {
		res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
		strcpy(res[*returnSize], current);
		(*returnSize)++;
		return;
	}

	if (leftCnt < max) {
		current[currentSize] = '(';
		dfs(res, returnSize, current, currentSize + 1, leftCnt + 1, rightCnt, max);
	}

	if (rightCnt < leftCnt) {
		current[currentSize] = ')';
		dfs(res, returnSize, current, currentSize + 1, leftCnt, rightCnt + 1, max);
	}
}

void dfs(char** res, int* returnSize, char* current, int currentSize, int leftCnt, int rightCnt, int max)
{
	if (leftCnt > max || rightCnt > leftCnt) {
		return;
	}

	if (currentSize == max * 2) {
		res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
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

/* bfs  left right 为总数减法到0 */
char** generateParenthesis(int n, int* returnSize)
{
	*returnSize = 0;
	if (n == 0) {
		return NULL;
	}

	char** res = (char**)calloc(1024 * 1024, sizeof(char*));
	struct List list;
	queue_init(&list);

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->left = n;
	entry->right = n;
	memset(entry->data, 0, sizeof(entry->data));
	ListAddTail(&list, &entry->node);

	while(!queue_empty(&list)) {
		struct Node *pop = queue_pop(&list);
		struct DataEntry  *popEntry = NODE_ENTRY(pop, struct DataEntry, node);

		if (popEntry->left == 0 && popEntry->right == 0) {
			res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
			strcpy(res[*returnSize], popEntry->data);
			(*returnSize)++;
		}

		if (popEntry->left > 0) {
			struct DataEntry  *leftentry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
			leftentry->left = popEntry->left - 1;
			leftentry->right = popEntry->right;
			strcpy(leftentry->data, popEntry->data);
			strcat(leftentry->data, "(");
			ListAddTail(&list, &leftentry->node);
		}

		if (popEntry->right > 0 && popEntry->left < popEntry->right) {
			struct DataEntry  *rightentry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
			rightentry->left = popEntry->left;
			rightentry->right = popEntry->right - 1;
			strcpy(rightentry->data, popEntry->data);
			strcat(rightentry->data, ")");
			ListAddTail(&list, &rightentry->node);
		}
	}

	return res;
}


/*
设所求序列为S[n]，记其序号为n，则S[n]可以来自于之前求出的
序列的组合再加上左右括号。

比如 n = 3 时，我们要求3对括号能组成的有效组合，
现在我们先摆好1对括号" （）"，思考是否能利用之前的组合
填充这个括号，使其组成3对括号？ 可以得出这个填充是：
"（2对括号的有效组合）"，"（1对括号的有效组合）1对括号的
有效组合"，"（）2对括号的有效组合"。

不用考虑"2对括号的有效组合（）"，因为已经包含在上述情
况"（1对括号的有效组合）1对括号的有效组合"。

将S[n]表示为"（左序列）右序列 " ，并且左右序列的序号之和
为n-1，即 S[n] = { '(' + S[n-1] + ')' + S[0] , '(' + S[n-2] + ')' + S[1] , '(' + S[n-2] + ')' + S[1] ...... '(' + S[0]+ ')' + S[n - 1] }
可知S[0] = "" ;

  S[0]         S[1]         S[2]
  { }          { "()" }       {"()()","(())"}
S[3] = { '(' + S[2] + ')' + S[0] ， '(' + S[1] + ')' + S[1] , '(' + S[0] + ')' + S[2] }

      =   {         "(()())" ,"((()))",     "(())()",    "()()()","()(())"      }
class Solution {
public:
    vector<string> generateParenthesis(int n) {
             vector<string> ans ;
        if (n == 0) {
            ans.push_back("");
        } else {
            for (int c = n-1; c >= 0; --c)
                for (string left: generateParenthesis(c))
                    for (string right: generateParenthesis(n-1-c))
                        ans.push_back("(" + left + ")" + right);
        }
        return ans;
    }

};

*/


/*529 see bfs*/
const int dir[8][2] = {{0,1}, {1,0}, {0,-1}, {-1,0},
                 	      {1,1}, {-1,-1},{-1,1},{1,-1}
                 	     };


int  NeighborsHavenumsM(int x, int y,  char **res, int boardSize, int* boardColSize)
{
	int Mcnt = 0;

	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardColSize[nx]) {
			if (res[nx][ny] == 'M' || res[nx][ny] == 'X')
				Mcnt++;
		}
	}

	return Mcnt;
}


void dfs(int boardSize, int* boardColSize, int x, int y, char **res)
{
	int nums = NeighborsHavenumsM(x, y, res, boardSize, boardColSize);

	if (nums > 0) {
		res[x][y] = '0' + nums;
		return;
	}

	res[x][y] = 'B';
	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardColSize[nx]) {
			if (res[nx][ny] == 'E') {
				dfs(boardSize, boardColSize, nx, ny, res);
			}
		}
	}
}

char** updateBoard(char** board, int boardSize, int* boardColSize,
int* click, int clickSize, int* returnSize, int** returnColumnSizes){

	char **res = (char **)calloc(boardSize, sizeof(char *));
	for (int i = 0; i < boardSize; i++) {
	        res[i] = (char *)calloc(boardColSize[i], sizeof(char));
	}

	*returnColumnSizes = calloc(boardSize, sizeof(int *));

	for (int i = 0; i < boardSize; i++){
	        for (int j = 0; j < boardColSize[i]; j++) {
	            res[i][j] = board[i][j];
	        }

		(*returnColumnSizes)[i] = boardColSize[i];
	}

	*returnSize = boardSize;

	int x = click[0];
	int y = click[1];

	if (res[x][y] == 'M') {
	    res[x][y] = 'X';
	} else if (res[x][y] == 'E') {
		dfs(boardSize, boardColSize, x, y, res);
	}
	return res;
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
void dfs(char** board, int boardSize, int* boardColSize, int x, int y)
{
	if (board[x][y] != 'O')
		return;//false

	board[x][y] = 'F';

	int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	for (int i = 0;i < 4; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 &&
			ny < boardColSize[nx] && board[nx][ny] == 'O') {
			dfs(board, boardSize, boardColSize, nx, ny);
		}
	}
}



void solve(char** board, int boardSize, int* boardColSize) {
	if (board == NULL || boardSize <= 0 || boardColSize == NULL )
		return;

	for (int i = 0; i < boardSize; i++) {
		dfs(board, boardSize, boardColSize, i, 0);
		dfs(board, boardSize, boardColSize, i, boardColSize[i] - 1);
	}

	for (int j = 0; j < boardColSize[0]; j++) {
		dfs(board, boardSize, boardColSize, 0, j);
		dfs(board, boardSize, boardColSize, boardSize - 1, j);
	}


	for(int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardColSize[i]; j++) {
			if (board[i][j] == 'O')
				board[i][j] = 'X';
			else if (board[i][j] == 'F')
				board[i][j] = 'O';
		}
	}
}


/*
面试题 16.19. 水域大小
难度中等1
你有一个用于表示一片土地的整数矩阵land，该矩阵中每个点的值代表对应地点的海拔高度。若值为0则表示水域。由垂直、水平或对角连接的水域为池塘。池塘的大小是指相连接的水域的个数。编写一个方法来计算矩阵中所有池塘的大小，返回值需要从小到大排序。
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

#define PARAM_CHECK(land, landSize, landColSize, returnSize) 	\
{\
	if (land == NULL || landSize > 1000 || landSize <= 0 || landColSize == NULL || returnSize == NULL)\
		return NULL;\
}\


void dfs(int** land, int landSize, int* landColSize, int *res, int i, int j)
{
	if (i < 0 || i >= landSize || j < 0 || j >= landColSize[i] || land[i][j] != 0) {
		return;
	}

	(*res)++;
	land[i][j] = 1;

	int d[8][2] = {{0,1},{1,1},{1,0},{1,-1},
		{0,-1},{-1,-1},{-1,0},{-1,1}};

	for (int k = 0; k < 8; k++) {
		dfs(land, landSize, landColSize, res, i + d[k][0], j + d[k][1]);
	}
}


int* pondSizes(int** land, int landSize, int* landColSize, int* returnSize)
{
	*returnSize = 0;

	PARAM_CHECK(land, landSize, landColSize, returnSize);

	int * res = (int *)calloc(landSize * 1024, sizeof(int));

	for(int i = 0; i < landSize; i++) {
		for (int j = 0; j < landColSize[i]; j++) {
			if (land[i][j] == 0) {
				dfs(land, landSize, landColSize, res + *returnSize, i, j);
				(*returnSize)++;
			}
		}
	}

	qsort(res, *returnSize, sizeof(int), cmp_int);

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

int nums[] = { 3,3,3,3,3,4,3,4 };

void dfs(char* digits, int srcSize, int* returnSize,
    char* tmp, int tmpIdx, int start, char** res)
{
	if (start == srcSize) {
		res[*returnSize] = (char*)calloc(1024, sizeof(char));
		strcpy(res[*returnSize], tmp);
		(*returnSize)++;
		return;
	}

	int leSize = nums[digits[start] - '2'];
	for (int i = 0; i < leSize; i++) { /*每一层leSize种case */
		tmp[tmpIdx] = letter[digits[start] - '2'][i];
		dfs(digits, srcSize, returnSize, tmp, tmpIdx + 1, start + 1, res);
	}
}


char** letterCombinations(char* digits, int* returnSize)
{
    if (digits == NULL || 0 == strcmp(digits, "")) {
        *returnSize = 0;
        return NULL;
    }

    char** res = (char **)calloc(1024, sizeof(char*));
    char* tmp = (char*)calloc(1024, sizeof(char));
    int strSize = strlen(digits);

    *returnSize = 0;
    dfs(digits, strSize, returnSize, tmp, 0, 0, res);

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

思路：以 target = 7 为根结点，每一个分支做减法。
减到 00 或者负数的时候，剪枝。其中，
减到 00 的时候结算，这里 "结算" 的意思是添加到结果集。
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

	qsort(candidates, candidatesSize, sizeof(int), cmp_int);
	int** res = (int**)calloc(1024, sizeof(int*));
	*returnColumnSizes = (int*)calloc(1024, sizeof(int));
	int* current = (int*)calloc(1024, sizeof(int));
	dfs(candidates, candidatesSize, 0, target, returnSize,
		returnColumnSizes, res, current, 0);
	return res;
}


void dfs(int* candidates, int candidatesSize, int start,
    int target, int* returnSize, int** returnColumnSizes,
    int **res, int *current, int curIdx, int sum)
{
    if (sum > target) {
        return;
    } else if (sum == target) {
        res[*returnSize] = (int*)calloc(1024, sizeof(int));
        memcpy(res[*returnSize], current, sizeof(int) * curIdx);
        (*returnColumnSizes)[*returnSize] = curIdx;
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize &&  sum + candidates[i] <= target; i++) {
        current[curIdx] = candidates[i];
        dfs(candidates, candidatesSize, i, target,
            returnSize, returnColumnSizes, res, current, curIdx + 1, sum + candidates[i]);
    }
}

int** combinationSum(int* candidates, int candidatesSize,
    int target, int* returnSize, int** returnColumnSizes) {

    *returnSize = 0;
    if (candidates == NULL || candidatesSize <= 0) {
        return NULL;
    }

    qsort(candidates, candidatesSize, sizeof(int), cmp_int);
    int** res = (int**)calloc(1024, sizeof(int*));
    *returnColumnSizes = (int*)calloc(1024, sizeof(int));
    int* current = (int*)calloc(1024, sizeof(int));
    dfs(candidates, candidatesSize, 0, target, returnSize,
        returnColumnSizes, res, current, 0, 0);
    return res;
}


void dfs(int* candidates, int candidatesSize, int start,
    int target, int* returnSize, int** returnColumnSizes,
    int** res, int* current, int curIdx)
{
    if (target == 0) {
        res[*returnSize] = (int*)calloc(1024, sizeof(int));
        memcpy(res[*returnSize], current, sizeof(int) * curIdx);
        (*returnColumnSizes)[*returnSize] = curIdx;
        (*returnSize)++;
        return;
    }

    if (start == candidatesSize || candidates[start] > target) {
        return;
    }

/*一直重复使用当前数降维target*/
    current[curIdx] = candidates[start];
    dfs(candidates, candidatesSize, start, target - candidates[start],
        returnSize, returnColumnSizes, res, current, curIdx + 1);

/*使用下一个数进行递归遍历*/
    dfs(candidates, candidatesSize, start + 1, target,
        returnSize, returnColumnSizes, res, current, curIdx);
}

int main(void)
{
	int intput[] = {2,3,6,7};
	int target = 7;

	int retSize;
	int *returnColumnSizes;
	int **ret;
	ret = combinationSum(intput, sizeof(intput)/sizeof(int),
		target, &retSize, &returnColumnSizes);
	for (int i = 0; i < retSize; i++) {
		 for(int j = 0; j < retColSize[i]; j++) {
			printf("%d", ret[i][j]);
		 }
		 printf("\n");
	}
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

	if (start >= candidatesSize || candidates[start] > target)
		return;

	for (int i = start; i < candidatesSize && target > 0 && candidates[i] <= target; i++) {
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
	int *curBuf = (int *)calloc(1024, sizeof(int));

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

void dfs(
int target, int* returnSize, int** returnColumnSizes,
int start, int **res, int *curBuf, int curSize, int k)
{
	if (target == 0 && curSize == k) {
		res[*returnSize] = (int *)calloc(1024, sizeof(int));
		memcpy(res[*returnSize], curBuf, curSize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = curSize;
		(*returnSize)++;
		return;
	}

	if (start >= 10 || start > target || curSize >= k || target < 0)
		return;

	for (int i = start; i < 10; i++) {
        	curBuf[curSize] = i;
		/*i + 1 :每种组合中不存在重复的数字。
		因为结果集里的元素互不相同，
		因此下一层搜索的起点应该是上一层搜索的起点值 + 1；*/
		dfs(target - i, returnSize, returnColumnSizes, i + 1, res, curBuf, curSize + 1, k);
	}

	return;
}


int** combinationSum3(int k, int n,
	int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;
	int ** res = (int **)calloc(1024, sizeof(int *));
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));
	int *curBuf = (int *)calloc(1024, sizeof(int));

	dfs(n, returnSize, returnColumnSizes, 1, res, curBuf, 0, k);
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


int minsum = INT_MAX;

void dfs(int** grid, int gridSize,
	int* gridColSize, int sum, int x, int y)
{
	if (x == gridSize - 1 && y == gridColSize[x] - 1) {
		minsum = fmin(minsum, sum);
		return;
	}

	int d[2][2] = { {1, 0}, {0, 1} };//down,right
	for (int i = 0; i < 2; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < gridSize && ny < gridColSize[nx]) {
			dfs(grid, gridSize, gridColSize, sum + grid[nx][ny], nx, ny);
		}
	}
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
	minsum = INT_MAX;

	if (grid == NULL || gridSize < 1 || gridColSize == NULL)
		return 0;

	dfs(grid, gridSize, gridColSize, grid[0][0], 0, 0);

    return minsum;
}

int  dfs(int** grid, int gridSize,
	int* gridColSize, int x, int y)
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

int minPathSum(int** grid, int gridSize, int* gridColSize) {
	if (grid == NULL || gridSize < 1 || gridColSize == NULL)
		return 0;

	return dfs(grid, gridSize, gridColSize, 0, 0);
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
	if (grid == NULL || gridSize < 1 || gridColSize == NULL)
		return 0;


	int dp[gridSize][gridColSize[0]];

	dp[0][0] = grid[0][0];
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			if (i >= 1 && j >= 1)
				dp[i][j] = grid[i][j] + fmin(dp[i - 1][j], dp[i][j - 1]);
			else if (i >= 1)
				dp[i][j] = grid[i][j] + dp[i - 1][j];
			else if (j >= 1)
				dp[i][j] = grid[i][j] + dp[i][j - 1];
		}
	}

	return dp[gridSize - 1][gridColSize[0] - 1];
}

/*DP
解题思路：
此题是典型的动态规划题目。

状态定义：

设 dpdp 为大小 m \times nm×n 矩阵，其中 dp[i][j]dp[i][j] 的值代表直到走到 (i,j)(i,j) 的最小路径和。
转移方程：

题目要求，只能向右或向下走，换句话说，当前单元格 (i,j)(i,j) 只能从左方单元格 (i-1,j)(i?1,j) 或上方单元格 (i,j-1)(i,j?1) 走到，因此只需要考虑矩阵左边界和上边界。

走到当前单元格 (i,j)(i,j) 的最小路径和 == "从左方单元格 (i-1,j)(i?1,j) 与 从上方单元格 (i,j-1)(i,j?1) 走来的 两个最小路径和中较小的 " ++ 当前单元格值 grid[i][j]grid[i][j] 。具体分为以下 44 种情况：
当左边和上边都不是矩阵边界时： 即当i \not= 0i


 =0, j \not= 0j


 =0时，dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]dp[i][j]=min(dp[i?1][j],dp[i][j?1])+grid[i][j] ；
当只有左边是矩阵边界时： 只能从上面来，即当i = 0, j \not= 0i=0,j


 =0时， dp[i][j] = dp[i][j - 1] + grid[i][j]dp[i][j]=dp[i][j?1]+grid[i][j] ；
当只有上边是矩阵边界时： 只能从左面来，即当i \not= 0, j = 0i


 =0,j=0时， dp[i][j] = dp[i - 1][j] + grid[i][j]dp[i][j]=dp[i?1][j]+grid[i][j] ；
当左边和上边都是矩阵边界时： 即当i = 0, j = 0i=0,j=0时，其实就是起点， dp[i][j] = grid[i][j]dp[i][j]=grid[i][j]；
初始状态：

dpdp 初始化即可，不需要修改初始 00 值。
返回值：

返回 dpdp 矩阵右下角值，即走到终点的最小路径和。
其实我们完全不需要建立 dpdp 矩阵浪费额外空间，直接遍历 grid[i][j]grid[i][j] 修改即可。这是因为：grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j] ；原 gridgrid 矩阵元素中被覆盖为 dpdp 元素后（都处于当前遍历点的左上方），不会再被使用到。
*/
int minPathSum(int** grid, int gridSize, int* gridColSize) {
	if (grid == NULL || gridSize < 1 || gridColSize == NULL)
		return 0;

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			if (i == 0 && j == 0)
				continue;
			else if (i == 0)
				grid[i][j] += grid[i][j - 1];
			else if (j == 0)
				grid[i][j] += grid[i - 1][j];
			else
				grid[i][j] += fmin(grid[i][j - 1], grid[i - 1][j]);
		}
	}

	return grid[gridSize - 1][gridColSize[0] - 1];
}


/*
77. 组合
难度中等238
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
示例:
输入: n = 4, k = 2
输出:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/

void backtrack(int n, int k, int* returnSize,
				int** returnColumnSizes, int **ret, int *cur, int curCnt, int start)
{
	if (k == curCnt) {
		ret[*returnSize] = (int *)calloc(k, sizeof(int));
		memcpy(ret[*returnSize], cur, sizeof(int) * k);
		(*returnSize)++;
		return;
	}

	if (curCnt > k) {
		return;
	}

	for(int i = start; i <= n; i++) {
		cur[curCnt] = i;
		backtrack(n, k, returnSize, returnColumnSizes, ret, cur, curCnt + 1, i + 1);
	}
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes)
{
	int **ret = (int **)calloc(1 << n, sizeof(int *));
	int *cur = (int *)calloc(1 << n, sizeof(int));

	*returnSize = 0;
	backtrack(n, k, returnSize, returnColumnSizes, ret, cur, 0, 1);
	*returnColumnSizes = (int *)calloc(*returnSize, sizeof(int));
	for (int i = 0; i < *returnSize; i++) {
		(*returnColumnSizes)[i] = k;
	}

	return ret;
}


/*
934. 最短的桥
难度中等68
在给定的二维二进制数组 A 中，存在两座岛。（岛是由四面相连的 1 形成的一个最大组。）
现在，我们可以将 0 变为 1，以使两座岛连接起来，变成一座岛。
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


/*
DFS深度优先遍历先找到第一个岛，并进行染色标志未
2；找到第一个后退出；将找到的第一个岛的位置入队列（C语言没有现成的队列封装函数，需要自己实现）对第一个岛的节点进行广度优先遍历，找到1的层数就是需要返回的值；作者：aabbcc-3链接：https://leetcode-cn.com/problems/shortest-bridge/solution/cyu-yan-bian-xie-dfsbfsdfsran-se-bfsjin-xing-zhao-/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
第一步：dfs将第一个的岛屿元素全部标记出来，并顺序入队；第二步：bfs遍历队内各元素，将未标记元素标记并入队，step++;第三步：找到新的元素为1即为新岛屿，step++返回即可。作者：roychen链接：https://leetcode-cn.com/problems/shortest-bridge/solution/dfsbfs-nei-cun-he-yun-xing-shi-jian-jiao-shao-by-r/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

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
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。

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

void dfs(int* nums, int numsSize, int S, int *cnt, int start)
{
	if (start == numsSize) {
		if (S == 0)
			(*cnt)++;
		return;
	}


	dfs(nums, numsSize, S - nums[start],  cnt, start + 1);
	dfs(nums, numsSize, S + nums[start],  cnt, start + 1);
}

int findTargetSumWays(int* nums, int numsSize, int S)
{
	int cnt = 0;
	dfs(nums, numsSize, S,  &cnt, 0);

	return cnt;
}

/*
面试题13. 机器人的运动范围
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？



示例 1：

输入：m = 2, n = 3, k = 1
输出：3
示例 2：

输入：m = 3, n = 1, k = 0
输出：1
*/
int numsum(int obj)
{
	int sum = 0;
	while(obj != 0) {
		sum += obj % 10;
		obj /= 10;
	}

	return sum;
}

void dfs(int m, int n, int k, int x, int y, int *res, int **visited)
{
	if (x < 0 || x >= m || y < 0 || y >= n) {
		return;
	}

	if (visited[x][y] == 1)
		return;

	int sum = numsum(x) + numsum(y);
	if (sum > k) {
		return;
	}

	(*res)++;
	visited[x][y] = 1;

	int d[2][2] = {{0, 1}, {1, 0}};
	for (int i = 0; i < 2; i++) {
		dfs(m, n, k, x + d[i][0], y + d[i][1], res, visited);
	}
}

int movingCount(int m, int n, int k)
{
	int res = 0;

	int **visited = (int **)calloc(m, sizeof(int *));
	for (int i = 0; i < m; i++) {
		visited[i] = (int *)calloc(n, sizeof(int));
	}

	dfs(m, n, k, 0, 0, &res, visited);
	return res;
}

/*
417. 太平洋大西洋水流问题
难度中等109
给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。"太平洋"处于大陆的左边界和上边界，而"大西洋"处于大陆的右边界和下边界。
规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。
请找出那些水流既可以流动到"太平洋"，又能流动到"大西洋"的陆地单元的坐标。

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
638. 大礼包
难度中等97
在LeetCode商店中， 有许多在售的物品。
然而，也有一些大礼包，每个大礼包以优惠的价格捆绑销售一组物品。
现给定每个物品的价格，每个大礼包包含物品的清单，以及待购物品清单。请输出确切完成待购清单的最低花费。
每个大礼包的由一个数组中的一组数据描述，最后一个数字代表大礼包的价格，其他数字分别表示内含的其他种类物品的数量。
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

用礼包替价格去替换原价，算出替换后的总价，更新最小总价
*/

int Min(int a, int b)
{
    return a > b ? b : a;
}

int g_res;

void Dfs(int** special, int specialSize, int* specialColSize, int* needs, int needsSize, int *specialOrinPrice, int totalOrinPrice) {
    for (int i = 0; i < needsSize; i++) {
        if (needs[i] < 0) {
            return;
        }
    }
    g_res = Min(g_res, totalOrinPrice);
    for (int i = 0; i < specialSize; i++) {
        for (int j = 0; j < specialColSize[i] - 1; j++) {
            needs[j] -= special[i][j];
        }
        //printf("123");
        Dfs(special, specialSize, specialColSize, needs, needsSize, specialOrinPrice, totalOrinPrice - specialOrinPrice[i] + special[i][specialColSize[i] - 1]);
        for (int j = 0; j < specialColSize[i] - 1; j++) {
            needs[j] += special[i][j];
        }
    }
}

int shoppingOffers(int* price, int priceSize, int** special, int specialSize, int* specialColSize, int* needs, int needsSize){
    if (priceSize <= 0) {
        return 0;
    }
    int specialOrinPrice[specialSize];
    for (int i = 0; i < specialSize; i++) {
        int tPrice = 0;
        for (int j = 0; j < specialColSize[i] - 1; j++) {
            tPrice += price[j] * special[i][j];
        }
        specialOrinPrice[i] = tPrice;
    }

    int totalOrinPrice = 0;
    for (int i = 0; i < needsSize; i++) {
        totalOrinPrice += price[i] * needs[i];
    }
    g_res = totalOrinPrice;
    Dfs(special, specialSize, specialColSize, needs, needsSize, specialOrinPrice, totalOrinPrice);
    return g_res;
}

/*
695. 岛屿的最大面积
难度中等288
给定一个包含了一些 0 和 1 的非空二维数组 grid 。
一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为 0 。)

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
 // 每次调用的时候默认num为1，进入后判断如果不是岛屿，则直接返回0，就可以避免预防错误的情况。    // 每次找到岛屿，则直接把找到的岛屿改成0，这是传说中的沉岛思想，就是遇到岛屿就把他和周围的全部沉默。    // ps：如果能用沉岛思想，那么自然可以用朋友圈思想。有兴趣的朋友可以去尝试。作者：mark-42链接：https://leetcode-cn.com/problems/max-area-of-island/solution/biao-zhun-javadong-tai-gui-hua-jie-fa-100-by-mark-/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int dfs(int** grid, int mrow, int mcol, int sx, int sy)
{
	if (sx < 0 || sx >= mrow || sy < 0 || sy >= mcol || grid[sx][sy] == 0) {
		return 0;
	}

	int res = 1;
	grid[sx][sy] = 0;

	int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	for (int i = 0; i < 4; i++) {
		res += dfs(grid, mrow, mcol, sx + d[i][0], sy + d[i][1]);
	}

	return res;
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize)
{
	int max = 0;
	int mrow = gridSize;
	int mcol = *gridColSize;

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			if (grid[i][j] != 0) {
				max = fmax(max, dfs(grid, mrow, mcol, i,j));
			}
		}
	}

	return max;
}

/*
1034. 边框着色
给出一个二维整数网格 grid，网格中的每个值表示该位置处的网格块的颜色。

只有当两个网格块的颜色相同，而且在四个方向中任意一个方向上相邻时，它们属于同一连通分量。

连通分量的边界是指连通分量中的所有与不在分量中的正方形相邻（四个方向上）的所有正方形，或者在网格的边界上（第一行/列或最后一行/列）的所有正方形。

给出位于 (r0, c0) 的网格块和颜色 color，使用指定颜色 color 为所给网格块的连通分量的边界进行着色，并返回最终的网格 grid 。



示例 1：

输入：grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
输出：[[3, 3], [3, 2]]
*/
/*
联通分量内节点的颜色记为sColor，染边框的颜色为tColor。 （source color 与 target color）
dfs遍历整个联通分量：

对于遍历过的节点，我们都让他们的值为负数，这样，就不需要多开空间来记录节点是否遍历过
对于联通分量中内部的节点，他们的值都为sColor，遍历过后，他们的值为-sColor。
对于联通分量边框上的节点，他们的值都为sColor，遍历过后，他们的值为-tColor。
遍历完整个联通分量，将整个grid中的负值改为正值
关键在于怎么判断一个节点在联通分量中是否处于边框的位置：

该节点在整个网格的四周:

x == 0 || x+1 >= g.length || y == 0 || y+1 >= g[0].length
该节点的↑↓←→节点有任意一个节点不属于当前联通分量；对于周围某个节点的颜色nextColor，如果它满足如下条件，那么他就不属于当前联通分量

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
1254. 统计封闭岛屿的数目
有一个二维矩阵 grid ，每个位置要么是陆地（记号为 0 ）要么是水域（记号为 1 ）。

我们从一块陆地出发，每次可以往上下左右 4 个方向相邻区域走，能走到的所有陆地区域，我们将其称为一座「岛屿」。

如果一座岛屿 完全 由水域包围，即陆地边缘上下左右所有相邻区域都是水域，那么我们将其称为 「封闭岛屿」。

请返回封闭岛屿的数目。
*/
void show(int** grid, int gridSize, int* gridColSize)
{
	printf("\n");
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
				printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
}

void dfs(int** grid, int gridSize, int* gridColSize, int startx, int starty)
{
	if (startx < 0 || startx >= gridSize || starty < 0 || starty >= gridColSize[startx] || grid[startx][starty] == 1) {
		return;
	}

	grid[startx][starty] = 1;

	int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	for (int i = 0; i < 4; i++) {
		dfs(grid, gridSize, gridColSize, startx + d[i][0], starty + d[i][1]);
	}
}

int closedIsland(int** grid, int gridSize, int* gridColSize)
{
	//show(grid, gridSize, gridColSize);

	for (int i = 0; i < gridSize; i++) {
		if (grid[i][0] == 0)
			dfs(grid, gridSize, gridColSize, i, 0);
		if (grid[i][gridColSize[i] - 1] == 0)
			dfs(grid, gridSize, gridColSize, i, gridColSize[i] - 1);
	}
	//show(grid, gridSize, gridColSize);

	for (int j = 0; j < gridColSize[0]; j++) {
		if (grid[0][j] == 0)
			dfs(grid, gridSize, gridColSize, 0, j);
		if (grid[gridSize - 1][j] == 0)
			dfs(grid, gridSize, gridColSize, gridSize - 1, j);
	}
	//show(grid, gridSize, gridColSize);

	int cnt = 0;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			if (grid[i][j] == 0) {
				dfs(grid, gridSize, gridColSize, i, j);
				cnt++;
			}
		}
	}

	return cnt;
}

/*
1391. 检查网格中是否存在有效路径
见UF
*/

//定义上 左 右 下
//为了便于寻找对应方向的接口，定义接口时数值设计如下，这样方向x的对应方向即为3-x。
//DIR_UP + DIR_DOWN = 3
//DIR_LEFT + DIR_RIGHT = 3
enum {
    DIR_UP = 0,
    DIR_LEFT = 1,
    DIR_RIGHT = 2,
    DIR_DOWN = 3,
};

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

//定义各图案是否支持指定接口
bool interfaces[7][4] = {
    //上    左      右      下
    {false, false, false,  false},      //0： dummy
    {false, true,  true,   false},      //1： 左右
    {true,  false, false,  true},       //2： 上下
    {false, true,  false,  true},       //3： 左下
    {false, false, true,   true},       //4： 右下
    {true,  true,  false,  false},      //5： 左上
    {true,  false, true,   false},      //6： 右上
};

void dfs(int** grid, int gridSize, int* gridColSize, int row, int col){
    if(grid[row][col] == 0) return; //已经搜索过得会被置0，防止重复搜索

    //置零
    int val =grid[row][col];
    grid[row][col] = 0;

    //遍历四个方向
    for(int i = 0; i < 4; i++){
        //该图案没有当前方向接口,continue
        if(interfaces[val][i] == false) continue;

        //如果有当前方向接口，计算该方向上邻居的坐标
        int r = row + OffsetTbl[i].r;
        int c = col + OffsetTbl[i].c;

        //坐标越界检查
        if(r >= gridSize || r < 0 || c < 0 || c >= gridColSize[row]){
            continue;
        }
        //判断该邻居是否有对应方向(即3-i)的接口，如果有则dfs该邻居；如果没有则代表无法连通，不继续dfs。
        if(interfaces[grid[r][c]][3-i]){
            dfs(grid, gridSize, gridColSize, r, c);
        }
    }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize){
    //力扣惯例，参数检查
    if(!grid || !gridSize || !gridColSize) return false;
    //从位置0,0开始深度优先遍历
    dfs(grid, gridSize, gridColSize, 0, 0);
    //返回最后一个位置是否为0
    return grid[gridSize-1][gridColSize[gridSize-1] - 1] == 0;
}

/*
1376. 通知所有员工所需的时间
难度中等24
公司里有 n 名员工，每个员工的 ID 都是独一无二的，编号从 0 到 n - 1。公司的总负责人通过 headID 进行标识。
在 manager 数组中，每个员工都有一个直属负责人，其中 manager[i] 是第 i 名员工的直属负责人。对于总负责人，manager[headID] = -1。题目保证从属关系可以用树结构显示。
公司总负责人想要向公司所有员工通告一条紧急消息。他将会首先通知他的直属下属们，然后由这些下属通知他们的下属，直到所有的员工都得知这条紧急消息。
第 i 名员工需要 informTime[i] 分钟来通知它的所有直属下属（也就是说在 informTime[i] 分钟后，他的所有直属下属都可以开始传播这一消息）。
返回通知所有员工这一紧急消息所需要的 分钟数 。

示例 1：
输入：n = 1, headID = 0, manager = [-1], informTime = [0]
输出：0
解释：公司总负责人是该公司的唯一一名员工。
示例 2：

输入：n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
输出：1
解释：id = 2 的员工是公司的总负责人，也是其他所有员工的直属负责人，他需要 1 分钟来通知所有员工。
上图显示了公司员工的树结构。

*/

/*DFS自底向上*/
int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime, int informTimeSize)
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


