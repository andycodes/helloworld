/*
深度优先搜索（Depth-First-Search，DFS）是一种
用于遍历或搜索树或图的算法。
沿着树的深度遍历树的节点，
尽可能深的搜索树的分支。
当节点v的所在边都己被探寻过，
搜索将回溯到发现节点v的那
条边的起始节点。
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
输出: [[2,2,2],[2,2,0],[2,0,1]]
解析:
在图像的正中间，(坐标(sr,sc)=(1,1)),
在路径上所有符合条件的像素点的颜色都被更改成2。
注意，右下角的像素没有更改为2，
因为它不是在上下左右四个方向上与初始点相连的像素点。

*/
void changeValue(int** image, int imageSize, int* imageColSize,
int sr, int sc, int newColor, int** res, bool** visited, int* returnSize, int** returnColumnSizes, int value) {

	if ( sr < 0 || sr >= imageSize || sc < 0 ||
		sc >= imageColSize[sr] || image[sr][sc] != value || visited[sr][sc])
		return;

	res[sr][sc] = newColor;
	visited[sr][sc] = true;

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for (int k = 0; k < 4; k++) {
		int nX = sr + d[k][0];
		int nY = sc + d[k][1];
		  changeValue(image, imageSize, imageColSize,
				nX, nY, newColor, res, visited, returnSize, returnColumnSizes, value);
	}
}



int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc,
	int newColor, int* returnSize, int** returnColumnSizes){
	int** res = malloc(sizeof(int*) * imageSize);
	bool** visited = malloc(sizeof(bool*) * imageSize);

	*returnSize = imageSize;
	*returnColumnSizes = malloc(sizeof(int) * imageSize);

	for (int i = 0; i < imageSize; i++) {
		res[i] = malloc(sizeof(int) * imageColSize[i]);
		visited[i] = malloc(sizeof(bool) * imageColSize[i]);
		memset(res[i], 0, sizeof(int) * imageColSize[i]);
		memset(visited[i], 0, sizeof(bool) * imageColSize[i]);
		(*returnColumnSizes)[i] = imageColSize[i];
	}

	changeValue(image, imageSize, imageColSize, sr, sc, newColor,
	res, visited, returnSize, returnColumnSizes, image[sr][sc]);

	for (int i = 0; i < imageSize; i++) {
		for (int j = 0; j < imageColSize[i]; j++) {
			if (visited[i][j] == false)
				res[i][j] = image[i][j];
		}
		free(visited[i]);
	}

	free(visited);
	return res;
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
		int nX = x + d[k][0];
		int nY = y + d[k][1];
		dfs(grid,gridSize,gridColSize,nX,nY);
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
  个 '(' 和 ')' 字符构成的序列。然后，我们将检查每一个是否有效。

算法

为了生成所有序列，我们使用递归。长度为 n 的序列就是 '(' 加上所有长度为 n-1 的序列，以及 ')' 加上所有长度为 n-1 的序列。

为了检查序列是否为有效的，我们会跟踪 平衡，也就是左括号的数量减去右括号的数量的净值。如果这个值始终小于零或者不以零结束，该序列就是无效的，否则它是有效的。

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

void generateAll(char* current, int currentSize,
    int pos, char** res, int* returnSize)
{
    if (pos == currentSize) {
        if (isValid(current, currentSize)) {
            res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
            strcpy(res[*returnSize], current);
            //strcpy_s(res[*returnSize], 1024 * 1024, current);
            (*returnSize)++;
        }

        return;
    }

    current[pos] = '(';
    generateAll(current, currentSize, pos + 1, res, returnSize);
    current[pos] = ')';
    generateAll(current, currentSize, pos + 1, res, returnSize);
}

char** generateParenthesis(int n, int* returnSize) {

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

void dfs(char** res, int* returnSize,
    char* current, int currentSize, int left, int right, int max)
{
    if (currentSize == max * 2) {
        res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
        strcpy(res[*returnSize], current);
        //strcpy_s(res[*returnSize], 1024 * 1024, current);
        (*returnSize)++;
        return;
    }

    if (left < max) {
        current[currentSize] = '(';
        dfs(res, returnSize, current, currentSize + 1, left + 1, right, max);
    }

    if (right < left) {
        current[currentSize] = ')';
        dfs(res, returnSize, current, currentSize + 1, left, right + 1, max);
    }
}

char** generateParenthesis(int n, int* returnSize) {

    *returnSize = 0;
    if (n == 0) {
        return NULL;
    }

    char** res = (char**)calloc(1024 * 1024, sizeof(char*));
    char* current = (char*)calloc(1024 * 1024, sizeof(char));

    dfs(res, returnSize, current, 0, 0, 0, n);

    return res;
}

/*
减法

画图以后，可以分析出的结论：

当前左右括号都有大于 00 个可以使用的时候，才产生分支；

产生左分支的时候，只看当前是否还有左括号可以使用；

产生右分支的时候，还受到左分支的限制，
右边剩余可以使用的括号数量一定得在严格
大于左边剩余的数量的时候，才可以产生分支；

在左边和右边剩余的括号数都等于 00 的时候结算。

*/

/*bfs
此处撰写解题思路
模拟将 n个'(' 和 n个')' 分别放入两个栈中left和right。每次从两个栈中取值,并且到str中
如果left==right，此时我们只能从left中出栈，
如果left<=right 那么就有两种选择，要么从left中出栈，要么充right中出栈。
整个过程，要保证left<=right。

我们知道，所有的正确的括号都可以用栈来判断（入栈左括号，出栈右括号），所以可以使用栈+回溯的方法实现
PS：其实这里栈的作用和数字一样，因为只有一种括号，
但是如果以后题目拓展成 大中小三种括号，那么使用栈只用改很少的代码。（加"）"变成加pop）

写一个递归，每次可以有入栈和出栈操作，遍历所有可能性。

var ans []string

func dfs(n int, cur string, stack []byte) {    // 当前字符串组合 cur，当前前括号栈（只存储前括号）stack
    if len(cur)>=n*2 {
        if len(stack)==0 {
            ans = append(ans, cur)
        }
        return
    }
    // 两种操作：入栈和出栈
    if len(stack) <= n && len(cur) <=n*2 {   // 入栈，代表当前字符串 cur 累加一个前括号；前括号栈只存储前括号，大小不能超过3
        dfs(n, cur+"(", append(stack, '('))
    }
    if len(stack) > 0 {                     // 出栈，代表当前字符串 cur 累加一个后括号；前括号栈此时不能为空
        dfs(n, cur+")", stack[:len(stack)-1])
    }
}

func generateParenthesis(n int) []string {
    ans = []string{}
    dfs(n, "", []byte{})
    return ans
}


*/

/*
设所求序列为S[n]，记其序号为n，则S[n]可以来自于之前求出的序列的组合再加上左右括号。

比如 n = 3 时，我们要求3对括号能组成的有效组合，现在我们先摆好1对括号" （）"，思考是否能利用之前的组合填充这个括号，使其组成3对括号？ 可以得出这个填充是： "（2对括号的有效组合）"，"（1对括号的有效组合）1对括号的有效组合"，"（）2对括号的有效组合"。

不用考虑"2对括号的有效组合（）"，因为已经包含在上述情况"（1对括号的有效组合）1对括号的有效组合"。

将S[n]表示为"（左序列）右序列 " ，并且左右序列的序号之和为n-1，即 S[n] = { '(' + S[n-1] + ')' + S[0] , '(' + S[n-2] + ')' + S[1] , '(' + S[n-2] + ')' + S[1] ...... '(' + S[0]+ ')' + S[n - 1] }
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

