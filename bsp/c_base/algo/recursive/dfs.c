/*
�������������Depth-First-Search��DFS����һ��
���ڱ�������������ͼ���㷨��
����������ȱ������Ľڵ㣬
����������������ķ�֧��
���ڵ�v�����ڱ߶�����̽Ѱ����
���������ݵ����ֽڵ�v�������ߵ���ʼ�ڵ㡣
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
���:
[
[2,2,2],
[2,2,0],
[2,0,1]]
����:
��ͼ������м䣬(����(sr,sc)=(1,1)),
��·�������з������������ص����ɫ�������ĳ�2��
ע�⣬���½ǵ�����û�и���Ϊ2��
��Ϊ�����������������ĸ����������ʼ�����������ص㡣

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
  �� '(' �� ')' �ַ����ɵ����С�
  Ȼ�����ǽ����ÿһ���Ƿ���Ч��

�㷨

Ϊ�������������У�����ʹ�õݹ顣����Ϊ n �����о�
�� '(' �������г���Ϊ n-1 �����У��Լ� ')' �������г���Ϊ n-1 �����С�

Ϊ�˼�������Ƿ�Ϊ��Ч�ģ����ǻ���� ƽ�⣬
Ҳ���������ŵ�������ȥ�����ŵ������ľ�ֵ��
������ֵʼ��С������߲����������
�����о�����Ч�ģ�����������Ч�ġ�

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

	/*��ǰλ�����������*/
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

/* bfs  left right Ϊ����������0 */
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
����������ΪS[n]���������Ϊn����S[n]����������֮ǰ�����
���е�����ټ����������š�

���� n = 3 ʱ������Ҫ��3����������ɵ���Ч��ϣ�
���������Ȱں�1������" ����"��˼���Ƿ�������֮ǰ�����
���������ţ�ʹ�����3�����ţ� ���Եó��������ǣ�
"��2�����ŵ���Ч��ϣ�"��"��1�����ŵ���Ч��ϣ�1�����ŵ�
��Ч���"��"����2�����ŵ���Ч���"��

���ÿ���"2�����ŵ���Ч��ϣ���"����Ϊ�Ѿ�������������
��"��1�����ŵ���Ч��ϣ�1�����ŵ���Ч���"��

��S[n]��ʾΪ"�������У������� " �������������е����֮��
Ϊn-1���� S[n] = { '(' + S[n-1] + ')' + S[0] , '(' + S[n-2] + ')' + S[1] , '(' + S[n-2] + ')' + S[1] ...... '(' + S[0]+ ')' + S[n - 1] }
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
����һ�������Ǹ������� m x n ����
���ҳ�һ�������Ͻǵ����½ǵ�·����
ʹ��·���ϵ������ܺ�Ϊ��С��

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


/*
77. ���
�Ѷ��е�238
������������ n �� k������ 1 ... n �����п��ܵ� k ��������ϡ�
ʾ��:
����: n = 4, k = 2
���:
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
934. ��̵���
�Ѷ��е�68
�ڸ����Ķ�ά���������� A �У������������������������������� 1 �γɵ�һ������顣��
���ڣ����ǿ��Խ� 0 ��Ϊ 1����ʹ�������������������һ������
���ر��뷭ת�� 0 ����С��Ŀ�������Ա�֤�������� 1����

ʾ�� 1��
���룺[[0,1],[1,0]]
�����1
ʾ�� 2��
���룺[[0,1,0],[0,0,0],[0,0,1]]
�����2
ʾ�� 3��
���룺[[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
�����1

*/


/*
DFS������ȱ������ҵ���һ������������Ⱦɫ��־δ
2���ҵ���һ�����˳������ҵ��ĵ�һ������λ������У�C����û���ֳɵĶ��з�װ��������Ҫ�Լ�ʵ�֣��Ե�һ�����Ľڵ���й�����ȱ������ҵ�1�Ĳ���������Ҫ���ص�ֵ�����ߣ�aabbcc-3���ӣ�https://leetcode-cn.com/problems/shortest-bridge/solution/cyu-yan-bian-xie-dfsbfsdfsran-se-bfsjin-xing-zhao-/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
��һ����dfs����һ���ĵ���Ԫ��ȫ����ǳ�������˳����ӣ��ڶ�����bfs�������ڸ�Ԫ�أ���δ���Ԫ�ر�ǲ���ӣ�step++;���������ҵ��µ�Ԫ��Ϊ1��Ϊ�µ��죬step++���ؼ��ɡ����ߣ�roychen���ӣ�https://leetcode-cn.com/problems/shortest-bridge/solution/dfsbfs-nei-cun-he-yun-xing-shi-jian-jiao-shao-by-r/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������

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
494. Ŀ���
����һ���Ǹ��������飬a1, a2, ..., an, ��һ��Ŀ������S������������������ + �� -�����������е�����һ���������㶼���Դ� + �� -��ѡ��һ�����������ǰ�档

���ؿ���ʹ���������ΪĿ���� S ��������ӷ��ŵķ�������

ʾ�� 1:

����: nums: [1, 1, 1, 1, 1], S: 3
���: 5
����:

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

һ����5�ַ���������Ŀ���Ϊ3��
ע��:

����ǿգ��ҳ��Ȳ��ᳬ��20��
��ʼ������ĺͲ��ᳬ��1000��
��֤���ص����ս���ܱ�32λ�������¡�
ͨ������24,886�ύ����56,525
����ʵ������������������⣿
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
������13. �����˵��˶���Χ
������һ��m��n�еķ��񣬴����� [0,0] ������ [m-1,n-1] ��һ�������˴����� [0, 0] �ĸ��ӿ�ʼ�ƶ�����ÿ�ο��������ҡ��ϡ����ƶ�һ�񣨲����ƶ��������⣩��Ҳ���ܽ�������������������λ֮�ʹ���k�ĸ��ӡ����磬��kΪ18ʱ���������ܹ����뷽�� [35, 37] ����Ϊ3+5+3+7=18���������ܽ��뷽�� [35, 38]����Ϊ3+5+3+8=19�����ʸû������ܹ�������ٸ����ӣ�



ʾ�� 1��

���룺m = 2, n = 3, k = 1
�����3
ʾ�� 2��

���룺m = 3, n = 1, k = 0
�����1
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
417. ̫ƽ�������ˮ������
�Ѷ��е�109
����һ�� m x n �ķǸ�������������ʾһƬ��½�ϸ�����Ԫ��ĸ߶ȡ�"̫ƽ��"���ڴ�½����߽���ϱ߽磬��"������"���ڴ�½���ұ߽���±߽硣
�涨ˮ��ֻ�ܰ����ϡ��¡������ĸ�������������ֻ�ܴӸߵ��ͻ�����ͬ�ȸ߶���������
���ҳ���Щˮ���ȿ���������"̫ƽ��"������������"������"��½�ص�Ԫ�����ꡣ

��ʾ��
1.	��������˳����Ҫ
2.	m �� n ��С��150

ʾ����

��������� 5x5 ����:

  ̫ƽ�� ~   ~   ~   ~   ~
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * ������

����:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (��ͼ�д����ŵĵ�Ԫ)

*/

void dfs(int** matrix, int i, int j, int pre, int row, int col, int visited[row][col])
{
    // �趨�߽�
    if (i<0 || i>=row || j<0 || j>=col) return;
    // ���������ֻ���ɵ͵���
    if (matrix[i][j] < pre || visited[i][j] == 1)
        return;
    visited[i][j] = 1;
    // �������
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
    // ����״̬����
    int visited1[row][col];
    int visited2[row][col];
    memset(visited1, 0, sizeof(visited1));
    memset(visited2, 0, sizeof(visited2));
    // ̫ƽ���ϱ�Ե�ʹ������±�Ե
    for(int i=0;i<row;i++) {
        dfs(matrix, i, 0, 0, row, col, visited1);
        dfs(matrix, i, col-1, 0, row, col, visited2);
    }
    // ̫ƽ�����Ե�ʹ������ұ�Ե
    for(int i=0;i<col;i++) {
        dfs(matrix, 0, i, 0, row, col,visited1);
        dfs(matrix, row-1, i, 0, row, col, visited2);
    }
    int index = 0;
    // ��״̬�����غϵ�λ��
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
638. �����
�Ѷ��е�97
��LeetCode�̵��У� ��������۵���Ʒ��
Ȼ����Ҳ��һЩ�������ÿ����������Żݵļ۸���������һ����Ʒ��
�ָ���ÿ����Ʒ�ļ۸�ÿ�������������Ʒ���嵥���Լ�������Ʒ�嵥�������ȷ����ɴ����嵥����ͻ��ѡ�
ÿ�����������һ�������е�һ���������������һ�����ִ��������ļ۸��������ֱַ��ʾ�ں�������������Ʒ��������
�������������޴ι���
ʾ�� 1:
����: [2,5], [[3,0,5],[1,2,10]], [3,2]
���: 14
����:
��A��B������Ʒ���۸�ֱ�Ϊ?2��?5��
�����1���������?5�ļ۸���3A��0B��
�����2�� �������?10�ļ۸���1A��2B��
����Ҫ����3��A��2��B�� �����㸶��?10������1A��2B�������2�����Լ�?4����2A��
ʾ�� 2:
����: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
���: 11
����:
A��B��C�ļ۸�ֱ�Ϊ?2��?3��?4.
�������?4����1A��1B��Ҳ������?9����2A��2B��1C��
����Ҫ��1A��2B��1C�������㸶��?4����1A��1B�������1�����Լ�?3����1B�� ?4����1C��
�㲻���Թ��򳬳������嵥����Ʒ�����ܹ�������2���ӱ��ˡ�
.

*/

/*
����ʵ����һ���������

���ԭ�۹���������Ʒ���ܻ���.

���ÿ�����ԭ�۹���Ļ���.

�������۸�ȥ�滻ԭ�ۣ�����滻����ܼۣ�������С�ܼ�
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
695. �����������
�Ѷ��е�288
����һ��������һЩ 0 �� 1 �ķǿն�ά���� grid ��
һ�� ���� ����һЩ���ڵ� 1 (��������) ���ɵ���ϣ�����ġ����ڡ�Ҫ������ 1 ������ˮƽ������ֱ���������ڡ�����Լ��� grid ���ĸ���Ե���� 0������ˮ����Χ�š�
�ҵ������Ķ�ά���������ĵ��������(���û�е��죬�򷵻����Ϊ 0 ��)

ʾ�� 1:
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
 // ÿ�ε��õ�ʱ��Ĭ��numΪ1��������ж�������ǵ��죬��ֱ�ӷ���0���Ϳ��Ա���Ԥ������������    // ÿ���ҵ����죬��ֱ�Ӱ��ҵ��ĵ���ĳ�0�����Ǵ�˵�еĳ���˼�룬������������Ͱ�������Χ��ȫ����Ĭ��    // ps��������ó���˼�룬��ô��Ȼ����������Ȧ˼�롣����Ȥ�����ѿ���ȥ���ԡ����ߣ�mark-42���ӣ�https://leetcode-cn.com/problems/max-area-of-island/solution/biao-zhun-javadong-tai-gui-hua-jie-fa-100-by-mark-/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
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
1034. �߿���ɫ
����һ����ά�������� grid�������е�ÿ��ֵ��ʾ��λ�ô�����������ɫ��

ֻ�е�������������ɫ��ͬ���������ĸ�����������һ������������ʱ����������ͬһ��ͨ������

��ͨ�����ı߽���ָ��ͨ�����е������벻�ڷ����е����������ڣ��ĸ������ϣ������������Σ�����������ı߽��ϣ���һ��/�л����һ��/�У������������Ρ�

����λ�� (r0, c0) ����������ɫ color��ʹ��ָ����ɫ color Ϊ������������ͨ�����ı߽������ɫ�����������յ����� grid ��



ʾ�� 1��

���룺grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
�����[[3, 3], [3, 2]]
*/
/*
��ͨ�����ڽڵ����ɫ��ΪsColor��Ⱦ�߿����ɫΪtColor�� ��source color �� target color��
dfs����������ͨ������

���ڱ������Ľڵ㣬���Ƕ������ǵ�ֵΪ�������������Ͳ���Ҫ�࿪�ռ�����¼�ڵ��Ƿ������
������ͨ�������ڲ��Ľڵ㣬���ǵ�ֵ��ΪsColor�������������ǵ�ֵΪ-sColor��
������ͨ�����߿��ϵĽڵ㣬���ǵ�ֵ��ΪsColor�������������ǵ�ֵΪ-tColor��
������������ͨ������������grid�еĸ�ֵ��Ϊ��ֵ
�ؼ�������ô�ж�һ���ڵ�����ͨ�������Ƿ��ڱ߿��λ�ã�

�ýڵ����������������:

x == 0 || x+1 >= g.length || y == 0 || y+1 >= g[0].length
�ýڵ�ġ��������ڵ�������һ���ڵ㲻���ڵ�ǰ��ͨ������������Χĳ���ڵ����ɫnextColor�����������������������ô���Ͳ����ڵ�ǰ��ͨ����

nextColor != sColor && nextColor != -sColor && nextColor != -tColor
nextColor != sColor����ɫ�Ͽ����������ڵ�ǰ��ͨ����
nextColor != -sColor���������Ѿ�����������ͨ�����ڲ��ڵ�
nextColor != -tColor���������Ѿ�����������ͨ�����߿�ڵ�

*/

    // ���ʡ��������ڵ�ʱ����x, y��ƫ����
    int dis[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void dfs(int** g, int gridSize, int* gridColSize, int x, int y, int sColor, int tColor)
{
        // Խ�� || ������ͬһ����ͨ���� || �����ʹ�
        if(x < 0 || x >= gridSize || y < 0 || y >= gridColSize[x] || g[x][y] != sColor || g[x][y] < 0) {
            return;
        }

        // ��ǰ�ڵ��Ѿ������ʣ����ø�ֵ
        g[x][y] = -sColor;

        // �жϱ߽�
        if(x == 0 || x+1 >= gridSize || y == 0 || y+1 >= gridColSize[x]) {
            // ����߽�
            g[x][y] = -tColor;
        } else {
            // ��ͨ�����ı߽�
            for(int i = 0 ; i < 4 ; i++) {
                int nextColor = g[x + dis[i][0]][y + dis[i][1]];
                // �����ǹؼ���
                if(nextColor != sColor && nextColor != -sColor && nextColor != -tColor) {
                    g[x][y] = -tColor;
                    break;
                }
            }
        }

        // �����������������
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
        // ����ֵ��Ϊ��ֵ
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
1254. ͳ�Ʒ�յ������Ŀ
��һ����ά���� grid ��ÿ��λ��Ҫô��½�أ��Ǻ�Ϊ 0 ��Ҫô��ˮ�򣨼Ǻ�Ϊ 1 ����

���Ǵ�һ��½�س�����ÿ�ο������������� 4 ���������������ߣ����ߵ�������½���������ǽ����Ϊһ�������졹��

���һ������ ��ȫ ��ˮ���Χ����½�ر�Ե����������������������ˮ����ô���ǽ����Ϊ ����յ��졹��

�뷵�ط�յ������Ŀ��
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
1391. ����������Ƿ������Ч·��
��UF
*/

//������ �� �� ��
//Ϊ�˱���Ѱ�Ҷ�Ӧ����Ľӿڣ�����ӿ�ʱ��ֵ������£���������x�Ķ�Ӧ����Ϊ3-x��
//DIR_UP + DIR_DOWN = 3
//DIR_LEFT + DIR_RIGHT = 3
enum {
    DIR_UP = 0,
    DIR_LEFT = 1,
    DIR_RIGHT = 2,
    DIR_DOWN = 3,
};

//�����������������ʱ�������offset
struct{
    int r;
    int c;
}OffsetTbl[4] = {
// row  col
    {-1, 0},    //��
    {0, -1},    //��
    {0, 1},     //��
    {1, 0}      //��
};

//�����ͼ���Ƿ�֧��ָ���ӿ�
bool interfaces[7][4] = {
    //��    ��      ��      ��
    {false, false, false,  false},      //0�� dummy
    {false, true,  true,   false},      //1�� ����
    {true,  false, false,  true},       //2�� ����
    {false, true,  false,  true},       //3�� ����
    {false, false, true,   true},       //4�� ����
    {true,  true,  false,  false},      //5�� ����
    {true,  false, true,   false},      //6�� ����
};

void dfs(int** grid, int gridSize, int* gridColSize, int row, int col){
    if(grid[row][col] == 0) return; //�Ѿ��������ûᱻ��0����ֹ�ظ�����

    //����
    int val =grid[row][col];
    grid[row][col] = 0;

    //�����ĸ�����
    for(int i = 0; i < 4; i++){
        //��ͼ��û�е�ǰ����ӿ�,continue
        if(interfaces[val][i] == false) continue;

        //����е�ǰ����ӿڣ�����÷������ھӵ�����
        int r = row + OffsetTbl[i].r;
        int c = col + OffsetTbl[i].c;

        //����Խ����
        if(r >= gridSize || r < 0 || c < 0 || c >= gridColSize[row]){
            continue;
        }
        //�жϸ��ھ��Ƿ��ж�Ӧ����(��3-i)�Ľӿڣ��������dfs���ھӣ����û��������޷���ͨ��������dfs��
        if(interfaces[grid[r][c]][3-i]){
            dfs(grid, gridSize, gridColSize, r, c);
        }
    }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize){
    //���۹������������
    if(!grid || !gridSize || !gridColSize) return false;
    //��λ��0,0��ʼ������ȱ���
    dfs(grid, gridSize, gridColSize, 0, 0);
    //�������һ��λ���Ƿ�Ϊ0
    return grid[gridSize-1][gridColSize[gridSize-1] - 1] == 0;
}

/*
1376. ֪ͨ����Ա�������ʱ��
�Ѷ��е�24
��˾���� n ��Ա����ÿ��Ա���� ID ���Ƕ�һ�޶��ģ���Ŵ� 0 �� n - 1����˾���ܸ�����ͨ�� headID ���б�ʶ��
�� manager �����У�ÿ��Ա������һ��ֱ�������ˣ����� manager[i] �ǵ� i ��Ա����ֱ�������ˡ������ܸ����ˣ�manager[headID] = -1����Ŀ��֤������ϵ���������ṹ��ʾ��
��˾�ܸ�������Ҫ��˾����Ա��ͨ��һ��������Ϣ������������֪ͨ����ֱ�������ǣ�Ȼ������Щ����֪ͨ���ǵ�������ֱ�����е�Ա������֪����������Ϣ��
�� i ��Ա����Ҫ informTime[i] ������֪ͨ��������ֱ��������Ҳ����˵�� informTime[i] ���Ӻ���������ֱ�����������Կ�ʼ������һ��Ϣ����
����֪ͨ����Ա����һ������Ϣ����Ҫ�� ������ ��

ʾ�� 1��
���룺n = 1, headID = 0, manager = [-1], informTime = [0]
�����0
���ͣ���˾�ܸ������Ǹù�˾��Ψһһ��Ա����
ʾ�� 2��

���룺n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
�����1
���ͣ�id = 2 ��Ա���ǹ�˾���ܸ����ˣ�Ҳ����������Ա����ֱ�������ˣ�����Ҫ 1 ������֪ͨ����Ա����
��ͼ��ʾ�˹�˾Ա�������ṹ��

*/

/*DFS�Ե�����*/
int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime, int informTimeSize)
{
        //���ս��
        int res = 0;

        for(int i =0;i<managerSize;i++){
            //�ж��Ƿ�Ϊ�����㣬��֦
            if(informTime[i]==0){
                //��ʱֵ
                int temp = 0;
                int index=i;
                //���ϱ���
                while(index!=-1){
                    temp+=informTime[index];
                    index=manager[index];
                }
                res = fmax(res,temp);
            }
        }
        return res;
}

/*DFS�Ե�����
��������Ա������������ײ�Ա����Ҷ�ӽڵ㣩��DFS�������ڵ㣬ֱ��û�и��ڵ�Ϊֹ����¼���б��������ʱ�伴Ϊ�𰸡�*/
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
DFS�Զ�����
�㷨����
ʹ���ڽӱ�����ʾ��Ŀ�е�N������
����headidΪ��㣬�������ı�������¼���������м���������֪ͨʱ�䣬��Ϊ�𰸡�
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


