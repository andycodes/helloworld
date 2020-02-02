/*
�������������Depth-First-Search��DFS����һ��
���ڱ�������������ͼ���㷨��
����������ȱ������Ľڵ㣬
����������������ķ�֧��
���ڵ�v�����ڱ߶�����̽Ѱ����
���������ݵ����ֽڵ�v����
���ߵ���ʼ�ڵ㡣
��һ����һֱ���е��ѷ��ִ�Դ�ڵ�ɴ�
�����нڵ�Ϊֹ�����������δ�����ֵĽڵ㣬
��ѡ������һ����ΪԴ�ڵ㲢�ظ����Ϲ��̣�
�������̷�������ֱ�����нڵ㶼������Ϊֹ��

DFSģ��

result = []
def dfs(·��, ѡ���б�):
    if ���㡸����������:
        result.add(��·����)
        return

    for ѡ�� in ��ѡ���б�:  (����N����)
        #��ѡ��
	 ����ѡ���ѡ���б��Ƴ�
	 ��·����.add(ѡ��)
        dfs(·��, ѡ���б�)
	 (ע������ݲ���:û�з��ڳ�������֦)

*/



/*
733. ͼ����Ⱦ
��һ���Զ�ά���������ʾ��ͼ����
ÿһ��������ʾ��ͼ��������ֵ��С��
��ֵ�� 0 �� 65535 ֮�䡣
����һ������ (sr, sc) ��ʾͼ����Ⱦ��ʼ������ֵ���� ���У�
��һ���µ���ɫֵ newColor������������ɫ���ͼ��

Ϊ�������ɫ�������ӳ�ʼ���꿪ʼ��
��¼��ʼ��������������ĸ�����������ֵ���ʼ��
����ͬ���������ص㣬�����ټ�¼���ĸ������Ϸ�����
�������ص������Ƕ�Ӧ�ĸ�����������ֵ���ʼ������ͬ
���������ص㣬�������ظ��ù��̡�
�������м�¼�����ص����ɫֵ��Ϊ�µ���ɫֵ��

��󷵻ؾ�����ɫ��Ⱦ���ͼ��

����:
image = [
[1,1,1],
[1,1,0],
[1,0,1]
]
sr = 1, sc = 1, newColor = 2
���: [[2,2,2],[2,2,0],[2,0,1]]
����:
��ͼ������м䣬(����(sr,sc)=(1,1)),
��·�������з������������ص����ɫ�������ĳ�2��
ע�⣬���½ǵ�����û�и���Ϊ2��
��Ϊ�����������������ĸ����������ʼ�����������ص㡣

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
200. ��������
����һ���� '1'��½�أ��� '0'��ˮ����ɵĵĶ�ά����
���㵺���������һ������ˮ��Χ��
��������ͨ��ˮƽ�����ֱ���������ڵ�½�����Ӷ��ɵġ�
����Լ���������ĸ��߾���ˮ��Χ��

ʾ�� 1:

����:
11110
11010
11000
00000

���: 1

};
*/
void dfs(char** grid, int gridSize, int gridColSize, int x ,int y)
{
	if (x < 0 || x >= gridSize || y < 0 || y >= gridColSize || grid[x][y] == '0')
		return;

	grid[x][y] = '0';//ǰ�����

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
22. ��������
���� n �����������ŵĶ���������д��һ��������
ʹ���ܹ��������п��ܵĲ�����Ч��������ϡ�

���磬���� n = 3�����ɽ��Ϊ��

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

����һ��������
˼·

���ǿ����������� 2^{2n}2
2n
  �� '(' �� ')' �ַ����ɵ����С�Ȼ�����ǽ����ÿһ���Ƿ���Ч��

�㷨

Ϊ�������������У�����ʹ�õݹ顣����Ϊ n �����о��� '(' �������г���Ϊ n-1 �����У��Լ� ')' �������г���Ϊ n-1 �����С�

Ϊ�˼�������Ƿ�Ϊ��Ч�ģ����ǻ���� ƽ�⣬Ҳ���������ŵ�������ȥ�����ŵ������ľ�ֵ��������ֵʼ��С������߲���������������о�����Ч�ģ�����������Ч�ġ�

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
��������DFS
˼·���㷨

�ӷ�

ֻ��������֪��������Ȼ������Чʱ����� '(' or ')'��
�������� ����һ ����ÿ����ӡ�
���ǿ���ͨ�����ٵ�ĿǰΪֹ���õ������ź�
�����ŵ���Ŀ��������һ�㣬

������ǻ�ʣһ��λ�ã����ǿ��Կ�ʼ��һ�������š�
����������������ŵ����������ǿ��Է�һ�������š�

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
����

��ͼ�Ժ󣬿��Է������Ľ��ۣ�

��ǰ�������Ŷ��д��� 00 ������ʹ�õ�ʱ�򣬲Ų�����֧��

�������֧��ʱ��ֻ����ǰ�Ƿ��������ſ���ʹ�ã�

�����ҷ�֧��ʱ�򣬻��ܵ����֧�����ƣ�
�ұ�ʣ�����ʹ�õ���������һ�������ϸ�
�������ʣ���������ʱ�򣬲ſ��Բ�����֧��

����ߺ��ұ�ʣ��������������� 00 ��ʱ����㡣

*/

/*bfs
�˴�׫д����˼·
ģ�⽫ n��'(' �� n��')' �ֱ��������ջ��left��right��ÿ�δ�����ջ��ȡֵ,���ҵ�str��
���left==right����ʱ����ֻ�ܴ�left�г�ջ��
���left<=right ��ô��������ѡ��Ҫô��left�г�ջ��Ҫô��right�г�ջ��
�������̣�Ҫ��֤left<=right��

����֪�������е���ȷ�����Ŷ�������ջ���жϣ���ջ�����ţ���ջ�����ţ������Կ���ʹ��ջ+���ݵķ���ʵ��
PS����ʵ����ջ�����ú�����һ������Ϊֻ��һ�����ţ�
��������Ժ���Ŀ��չ�� ����С�������ţ���ôʹ��ջֻ�øĺ��ٵĴ��롣����"��"��ɼ�pop��

дһ���ݹ飬ÿ�ο�������ջ�ͳ�ջ�������������п����ԡ�

var ans []string

func dfs(n int, cur string, stack []byte) {    // ��ǰ�ַ������ cur����ǰǰ����ջ��ֻ�洢ǰ���ţ�stack
    if len(cur)>=n*2 {
        if len(stack)==0 {
            ans = append(ans, cur)
        }
        return
    }
    // ���ֲ�������ջ�ͳ�ջ
    if len(stack) <= n && len(cur) <=n*2 {   // ��ջ������ǰ�ַ��� cur �ۼ�һ��ǰ���ţ�ǰ����ջֻ�洢ǰ���ţ���С���ܳ���3
        dfs(n, cur+"(", append(stack, '('))
    }
    if len(stack) > 0 {                     // ��ջ������ǰ�ַ��� cur �ۼ�һ�������ţ�ǰ����ջ��ʱ����Ϊ��
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
����������ΪS[n]���������Ϊn����S[n]����������֮ǰ��������е�����ټ����������š�

���� n = 3 ʱ������Ҫ��3����������ɵ���Ч��ϣ����������Ȱں�1������" ����"��˼���Ƿ�������֮ǰ��������������ţ�ʹ�����3�����ţ� ���Եó��������ǣ� "��2�����ŵ���Ч��ϣ�"��"��1�����ŵ���Ч��ϣ�1�����ŵ���Ч���"��"����2�����ŵ���Ч���"��

���ÿ���"2�����ŵ���Ч��ϣ���"����Ϊ�Ѿ��������������"��1�����ŵ���Ч��ϣ�1�����ŵ���Ч���"��

��S[n]��ʾΪ"�������У������� " �������������е����֮��Ϊn-1���� S[n] = { '(' + S[n-1] + ')' + S[0] , '(' + S[n-2] + ')' + S[1] , '(' + S[n-2] + ')' + S[1] ...... '(' + S[0]+ ')' + S[n - 1] }
��֪S[0] = "" ;

  S[0]         S[1]         S[2]
  { }          { "()" }       {"()()","(())"}
S[3] = { '(' + S[2] + ')' + S[0] �� '(' + S[1] + ')' + S[1] , '(' + S[0] + ')' + S[2] }

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
130. ��Χ�Ƶ�����
����һ����ά�ľ��󣬰��� 'X' �� 'O'����ĸ O����

�ҵ����б� 'X' Χ�Ƶ����򣬲�����Щ���������е� 'O' �� 'X' ��䡣

ʾ��:

X X X X
X O O X
X X O X
X O X X
������ĺ����󣬾����Ϊ��

X X X X
X X X X
X X X X
X O X X


��ʱ��� OO �ǲ����滻�ġ�
��Ϊ�ͱ߽�����ͨ�ġ�Ϊ�˼�¼����״̬��
���ǰ���������µ� OO ���� # ��Ϊռλ����
����������֮������ OO �滻Ϊ XX���ͱ߽�
����ͨ�� OO�������� #���滻�� $O(�ͱ߽���ͨ
�� OO)��
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

