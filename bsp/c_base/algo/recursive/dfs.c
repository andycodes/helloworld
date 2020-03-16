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


/*
������ 16.19. ˮ���С
�Ѷ��е�1
����һ�����ڱ�ʾһƬ���ص���������land���þ�����ÿ�����ֵ�����Ӧ�ص�ĺ��θ߶ȡ���ֵΪ0���ʾˮ���ɴ�ֱ��ˮƽ��Խ����ӵ�ˮ��Ϊ�����������Ĵ�С��ָ�����ӵ�ˮ��ĸ�������дһ��������������������г����Ĵ�С������ֵ��Ҫ��С��������
ʾ����
���룺
[
  [0,2,1,0],
  [0,1,0,1],
  [1,1,0,1],
  [0,1,0,1]
]
����� [1,2,4]

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
17. �绰�������ĸ���
����һ������������ 2-9 ���ַ�����
�����������ܱ�ʾ����ĸ��ϡ�

�������ֵ���ĸ��ӳ�����£���绰������ͬ����
ע�� 1 ����Ӧ�κ���ĸ��



ʾ��:

���룺"23"
�����["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

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
	for (int i = 0; i < leSize; i++) { /*ÿһ��leSize��case */
		tmp[tmpIdx] = letter[digits[start] - '2'][i];
		dfs(digits, srcSize, returnSize, tmp, tmpIdx + 1, start + 1, res);
	}
}


char** letterCombinations(char* digits, int* returnSize) {
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
39. ����ܺ�
����һ�����ظ�Ԫ�ص����� candidates ��һ��Ŀ���� target ��
�ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�

candidates �е����ֿ����������ظ���ѡȡ��

˵����

�������֣����� target��������������
�⼯���ܰ����ظ�����ϡ�
ʾ�� 1:

����: candidates = [2,3,6,7], target = 7,
����⼯Ϊ:
[
  [7],
  [2,2,3]
]

˼·���� target = 7 Ϊ����㣬ÿһ����֧��������
���� 00 ���߸�����ʱ�򣬼�֦�����У�
���� 00 ��ʱ����㣬���� "����" ����˼����ӵ��������
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

/*һֱ�ظ�ʹ�õ�ǰ����άtarget*/
    current[curIdx] = candidates[start];
    dfs(candidates, candidatesSize, start, target - candidates[start],
        returnSize, returnColumnSizes, res, current, curIdx + 1);

/*ʹ����һ�������еݹ����*/
    dfs(candidates, candidatesSize, start + 1, target,
        returnSize, returnColumnSizes, res, current, curIdx);
}

int main(void)
{
	int intput[] = {2,3,6,7};
	int target = 7;

	int retSize;
	int *retColSize;
	int **ret;
	ret = combinationSum(intput, sizeof(intput)/sizeof(int),
		target, &retSize, &retColSize);
	for (int i = 0; i < retSize; i++) {
		 for(int j = 0; j < retColSize[i]; j++) {
			printf("%d", ret[i][j]);
		 }
		 printf("\n");
	}
}


/*
40. ����ܺ� II
����һ������ candidates ��һ��Ŀ���� target ��
�ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�

candidates �е�ÿ��������ÿ�������ֻ��ʹ��һ�Ρ�

˵����

�������֣�����Ŀ������������������
�⼯���ܰ����ظ�����ϡ�


�㷨:
ͬһ��ε����ֲ�Ҫ�ظ����Ϳ��Ա��������ظ���
                  1
                 / \
                2   2  ����������ᷢ��
               /     \
              5       5
                ��2
                  1
                 /
                2      �������ȷ�������
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
216. ����ܺ� III
�ҳ��������֮��Ϊ n �� k ��������ϡ�
�����ֻ������ 1 - 9 ����������
����ÿ������в������ظ������֡�

˵����

�������ֶ�����������
�⼯���ܰ����ظ�����ϡ�
ʾ�� 1:

����: k = 3, n = 7
���: [[1,2,4]]
ʾ�� 2:

����: k = 3, n = 9
���: [[1,2,6], [1,3,5], [2,3,4]]

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
		/*i + 1 :ÿ������в������ظ������֡�
		��Ϊ��������Ԫ�ػ�����ͬ��
		�����һ�����������Ӧ������һ�����������ֵ + 1��*/
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
64 ��С·����
����һ�������Ǹ������� m x n �������ҳ�һ�������Ͻǵ����½ǵ�·����ʹ��·���ϵ������ܺ�Ϊ��С��

˵����ÿ��ֻ�����»��������ƶ�һ����

ʾ��:

����:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
���: 7
����: ��Ϊ·�� 1��3��1��1��1 ���ܺ���С��

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
		int nX = x + d[i][0];
		int nY = y + d[i][1];

		if (nX < gridSize && nY < gridColSize[nX]) {
			dfs(grid, gridSize, gridColSize, sum + grid[nX][nY], nX, nY);
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
����˼·��
�����ǵ��͵Ķ�̬�滮��Ŀ��

״̬���壺

�� dpdp Ϊ��С m \times nm��n �������� dp[i][j]dp[i][j] ��ֵ����ֱ���ߵ� (i,j)(i,j) ����С·���͡�
ת�Ʒ��̣�

��ĿҪ��ֻ�����һ������ߣ����仰˵����ǰ��Ԫ�� (i,j)(i,j) ֻ�ܴ��󷽵�Ԫ�� (i-1,j)(i?1,j) ���Ϸ���Ԫ�� (i,j-1)(i,j?1) �ߵ������ֻ��Ҫ���Ǿ�����߽���ϱ߽硣

�ߵ���ǰ��Ԫ�� (i,j)(i,j) ����С·���� == "���󷽵�Ԫ�� (i-1,j)(i?1,j) �� ���Ϸ���Ԫ�� (i,j-1)(i,j?1) ������ ������С·�����н�С�� " ++ ��ǰ��Ԫ��ֵ grid[i][j]grid[i][j] �������Ϊ���� 44 �������
����ߺ��ϱ߶����Ǿ���߽�ʱ�� ����i \not= 0i
��

 =0, j \not= 0j
��

 =0ʱ��dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]dp[i][j]=min(dp[i?1][j],dp[i][j?1])+grid[i][j] ��
��ֻ������Ǿ���߽�ʱ�� ֻ�ܴ�������������i = 0, j \not= 0i=0,j
��

 =0ʱ�� dp[i][j] = dp[i][j - 1] + grid[i][j]dp[i][j]=dp[i][j?1]+grid[i][j] ��
��ֻ���ϱ��Ǿ���߽�ʱ�� ֻ�ܴ�������������i \not= 0, j = 0i
��

 =0,j=0ʱ�� dp[i][j] = dp[i - 1][j] + grid[i][j]dp[i][j]=dp[i?1][j]+grid[i][j] ��
����ߺ��ϱ߶��Ǿ���߽�ʱ�� ����i = 0, j = 0i=0,j=0ʱ����ʵ������㣬 dp[i][j] = grid[i][j]dp[i][j]=grid[i][j]��
��ʼ״̬��

dpdp ��ʼ�����ɣ�����Ҫ�޸ĳ�ʼ 00 ֵ��
����ֵ��

���� dpdp �������½�ֵ�����ߵ��յ����С·���͡�
��ʵ������ȫ����Ҫ���� dpdp �����˷Ѷ���ռ䣬ֱ�ӱ��� grid[i][j]grid[i][j] �޸ļ��ɡ�������Ϊ��grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j] ��ԭ gridgrid ����Ԫ���б�����Ϊ dpdp Ԫ�غ󣨶����ڵ�ǰ����������Ϸ����������ٱ�ʹ�õ���
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

