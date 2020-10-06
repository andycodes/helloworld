/*
���ݷ��Ļ���˼�룺

����������⣬��������Ľ�ռ䣻
DFS ������ռ䣬���������������ü�֦����������Ч������
��DFS�Ĺ����з��ֲ�������Ľ⣬
��ô�Ϳ�ʼ���ݵ���һ�������һ���ڵ㡣

���ݷ��Ĵ�����·��ʹ������������ res �� path��
res ��ʾ���յĽ����
path �����Ѿ��߹���·����
����ѵ�һ��״̬������ĿҪ��
�Ͱ� path �ŵ� res ��


result = []
def backtrack(·��, ѡ���б�):
    if ���㡸����������:
        result.add(��·����)
        return

    for ѡ�� in ��ѡ���б�:  (����N����)  ��ǰ���
        #��ѡ��
	 ����ѡ���ѡ���б��Ƴ�
	 ��·����.add(ѡ��)
        backtrack(·��, ѡ���б�)
        #����ѡ��
        ��·����.remove(ѡ��)
    	 ����ѡ���ټ���ѡ���б�
*/

/*
�Ӽ�:
�Ӽ������ѡ���б�����һ��ѡ��·��֮�����,
�ݹ������һ�㣬ע��i+1����ʶ��һ��ѡ���б�Ŀ�ʼλ�ã�����Ҫ��һ��

���:


ȫ����


����
*/


/*
��ָ Offer 38. �ַ���������
�Ѷ��е�49
����һ���ַ�������ӡ�����ַ������ַ����������С�
�����������˳�򷵻�����ַ������飬
�����治�����ظ�Ԫ�ء�
ʾ��:
���룺s = "abc"
�����["abc","acb","bac","bca","cab","cba"]
*/
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
401. �������ֱ�
�������ֱ����� 4 �� LED ����Сʱ��0-11����
�ײ��� 6 �� LED ������ӣ�0-59����
ÿ�� LED ����һ�� 0 �� 1�����λ���Ҳࡣ
���磬����Ķ������ֱ��ȡ "3:25"��
����һ���Ǹ����� n ����ǰ LED ���ŵ�������
�������п��ܵ�ʱ�䡣
����:
����: n = 1
����: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
*/

#define MAX_LEN 1024
int g_led[10] = { 8, 4, 2, 1, 32, 16, 8, 4, 2, 1 };

void Dft(int num, char **res, int *returnSize, int hour, int min, int pos)
{
    if (num == 0) {
        if (hour > 9) {
            res[*returnSize] = (char *)malloc(6 * sizeof(char));
        } else {
            res[*returnSize] = (char *)malloc(5 * sizeof(char));
        }
        if (min > 9) {
            sprintf(res[*returnSize], "%d:%d", hour, min);
        } else {
            sprintf(res[*returnSize], "%d:0%d", hour, min);
        }
        (*returnSize)++;
        return;
    }

    for (int i = pos; i < 10; i++) {
        if ((i < 4) && (hour + g_led[i] < 12)) {
            Dft(num - 1, res, returnSize, hour + g_led[i], min, i + 1);
        } else if ((i >= 4) && (min + g_led[i] < 60)) {
            Dft(num - 1, res, returnSize, hour, min + g_led[i], i + 1);
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **readBinaryWatch(int num, int *returnSize)
{
    char **res = (char **)malloc(MAX_LEN * sizeof(char *));
    *returnSize = 0;
    Dft(num, res, returnSize, 0, 0, 0);
    return res;
}


/*
������ 08.02. ��·�Ļ�����
�Ѷ��е�13
�����и�����������һ����������Ͻǣ����� r �� c �С�
������ֻ�����»������ƶ����������ߵ�һЩ����ֹ������
���ϰ�������һ���㷨��Ѱ�һ����˴����Ͻ��ƶ�����
�½ǵ�·����
�����е��ϰ���Ϳ�λ�÷ֱ��� 1 �� 0 ����ʾ��
����һ�����е�·����·���ɾ�����������кź��к���ɡ�
���Ͻ�Ϊ 0 �� 0 �С�
ʾ�� 1:
����:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
���: [[0,0],[0,1],[0,2],[1,2],[2,2]]
����:
�����б�ֵ�λ�ü�Ϊ�����ʾ��·������
0��
*/
bool backtrack(int** obstacleGrid, int row, int col, int cx, int cy,
int **res, int *returnSize,  bool visited[][100], int** returnColumnSizes)
{
	if(cx >= row || cy >= col || obstacleGrid[cx][cy] == 1 || visited[cx][cy])
		return false;

	visited[cx][cy] = 1;
	res[*returnSize] = (int *)calloc(2, sizeof(int));
	res[*returnSize][0] = cx;
	res[*returnSize][1] = cy;
	(*returnColumnSizes)[*returnSize] = 2;
	(*returnSize)++;

	if(cx == (row - 1) && cy == (col - 1)) {
		return true;
	}

	if (backtrack(obstacleGrid, row, col, cx, cy + 1, res, returnSize, visited, returnColumnSizes) ||
		backtrack(obstacleGrid, row, col, cx + 1, cy, res, returnSize, visited, returnColumnSizes)) {
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
97. �����ַ���
�Ѷ�����319
���������ַ��� s1, s2, s3, ��֤ s3 �Ƿ����� s1 �� s2 ������ɵġ�
ʾ�� 1��
���룺s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
�����true
ʾ�� 2��
���룺s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
�����false
*/
/*
�����仯�Ļ��ݴӱ������ݿ�֪����i��j��kһ��������£�
����ֵһ�����ɴ����ǿ��Խ�i��j��k������ֵ��meom[i][j][k]��¼
�������������ٴ�������i��j��kʱ��ֱ�ӷ��ء���Ȼ��i��jһ
��ʱ��kһ������Ϊk = i + j����ˣ����Խ�״̬��������ά��
��meom[i][j]�����Ƕ������������ݽ��и��죬�ڻ��ݷ���false��
�ط���meom[i][j]��¼�������ڷ���true�ĵط����ü�¼����Ϊһ
������true�����ݾͻ�һֱ���أ�ֱ��������ڡ�
*/
bool backtrack(char *s1, char * s2, char * s3, int i, int j, int k,
int size1, int size2, int dp[size1][size2])
{
	if (dp[i][j] != 13) {
		return dp[i][j];
	}

	// ������������s1,s2,s3��˵���ܹ�s3�ܹ����������
	if(i == strlen(s1) && j == strlen(s2) && k == strlen(s3))
		return true;

	if(k >= strlen(s3)) {
		dp[i][j] = false;
		return false;
	}

	if(i < strlen(s1)) {
/*
����ǰs1��iλ�õ��ַ���s3��kλ���ַ���ȣ�������һ���ַ���
�����»��ݣ������ݷ���true�򷵻ص����true�ʼһ��
���ɸú����ڵڶ��д��뷵�صģ�
����ʾs3�ܹ���������ɣ�ֱ�ӷ���true
*/
		if(s1[i] == s3[k] && backtrack(s1, s2, s3, i+1, j, k+1, size1, size2, dp))
			return true;
	}

	if(j < strlen(s2)){
		if(s2[j] == s3[k] && backtrack(s1, s2, s3, i, j+1, k+1,  size1, size2, dp))
			return true;
	}

	dp[i][j] = false;
/*
�ڴ�i��j��k�£�������ζ��������s3.substring(0, k+1),����false
*/
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
679. 24 ����Ϸ
���� 4 ��д�� 1 �� 9 ���ֵ��ơ�����Ҫ�ж��Ƿ���ͨ�� *��/��
+��-��(��) ������õ� 24��
ʾ�� 1:
����: [4, 1, 8, 7]
���: True
����: (8-4) * (7-1) = 24
ʾ�� 2:
����: [1, 2, 1, 2]
���: False
ע��:
��������� / ��ʾʵ������������������������
���� 4 / (1 - 2/3) = 12 ��
ÿ����������������������㡣�ر������ǲ����� - ��Ϊһ
Ԫ����������磬[1, 1, 1, 1] ��Ϊ����ʱ�����ʽ -1 - 1 - 1 - 1 �ǲ�
����ġ�
�㲻�ܽ�����������һ�����磬����Ϊ [1, 2, 1, 2] ʱ������д
�� 12 + 12 ��
*/

typedef double (*ClacFunc) (double a, double b);
double Add(double a, double b) { return a + b; };
double Sub(double a, double b) { return a - b; };
double Mul(double a, double b) { return a * b; };
double Div(double a, double b) { return a / b; };

typedef struct {
    bool isSwap;    // �Ƿ񽻻�
    ClacFunc func;  // ����
}CLAC;

#define CLAC_TYPE 4
static CLAC g_clacFunc[CLAC_TYPE] = {
    {0, Add},//����һ��
    {1, Sub},//������һ��
    {0, Mul},
    {1, Div}
};

bool backtrack(double* nums, int size)
{
	if (size == 1) {
		return (fabs(nums[0] - 24) <= 1e-6);
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {//����ȡ��
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
488. ������Ϸ
�Ѷ�����54
����һ��������Ϸ������������һ������ɫ�к�ɫ(R)��
��ɫ(Y)����ɫ(B)����ɫ(G)�����а�ɫ(W)�� ����������Ҳ�м�
����
ÿһ�Σ�����Դ��������ѡһ����Ȼ����������뵽һ
�����е�ĳ��λ���ϣ���������ˣ����Ҷˣ������ţ����
�г���������������������ɫ��ͬ���������Ļ����Ͱ�����
�Ƴ������ظ���һ����ֱ���������е��򶼱��Ƴ���
�ҵ����벢�����Ƴ���������������������ٵ����������
�����Ƴ��������е������ -1 ��
ʾ��:
����: "WRRBBW", "RB"
���: -1
����: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW �������߱�ע��
�������Ѿ����꣬���ϻ�ʣ�������޷�����������-1��

����: "WWRRBBWW", "WRBRW"
���: 2
����: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty
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
37. ������
�Ѷ�����497
��дһ������ͨ�������Ŀո�������������⡣
һ�������Ľⷨ����ѭ���¹���
1.	���� 1-9 ��ÿһ��ֻ�ܳ���һ�Ρ�
2.	���� 1-9 ��ÿһ��ֻ�ܳ���һ�Ρ�
3.	���� 1-9 ��ÿһ���Դ�ʵ�߷ָ��� 3x3 ����ֻ�ܳ���һ�Ρ�
�հ׸��� '.' ��ʾ��

*/

bool backtrack(char** board, bool rowVisited[9][10], bool colVisited[9][10],
bool boxVisited[3][3][10], int cx, int cy, int boardSize, int* boardColSize)
{
	// �߽�У��, ����Ѿ�������, ����true, ��ʾһ�н���
	if(cy == *boardColSize) {
		cy = 0;
		cx++;
		if(cx == boardSize){
			return true;
		}
	}

	// �ǿ��������, ���������������������һ��λ��
	if(board[cx][cy] == '.') {
		// �������1~9
		for(int num = 1; num <= 9; num++){
			bool canUsed = !(rowVisited[cx][num] || colVisited[cy][num] || boxVisited[cx/3][cy/3][num]);
			if(canUsed){
				rowVisited[cx][num] = true;
				colVisited[cy][num] = true;
				boxVisited[cx/3][cy/3][num] = true;

				board[cx][cy] = (char)('0' + num);
				if(backtrack(board, rowVisited, colVisited, boxVisited, cx, cy + 1, boardSize, boardColSize)){
					return true;
				}

				board[cx][cy] = '.';

				rowVisited[cx][num] = false;
				colVisited[cy][num] = false;
				boxVisited[cx/3][cy/3][num] = false;
			}
		}
	} else {
		return backtrack(board, rowVisited, colVisited, boxVisited, cx, cy + 1, boardSize, boardColSize);
	}

	return false;
}

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
	bool rowVisited[9][10];//0~9ʹ��1~9
	bool colVisited[9][10];
	bool boxVisited[3][3][10];
	memset(rowVisited, 0, sizeof(rowVisited));
	memset(colVisited, 0, sizeof(colVisited));
	memset(boxVisited, 0, sizeof(boxVisited));

	// ��ʼ��
	for(int cx = 0; cx < boardSize; cx++){
		for(int cy = 0; cy < *boardColSize; cy++) {
			int num = board[cx][cy] - '0';
			if(1 <= num && num <= 9) {
				rowVisited[cx][num] = true;
				colVisited[cy][num] = true;
				boxVisited[cx / 3][cy / 3][num] = true;
			}
		}
	}

	backtrack(board, rowVisited, colVisited, boxVisited, 0, 0, boardSize, boardColSize);
}

/*
10. ������ʽƥ��
����һ���ַ��� s ��һ���ַ����� p��������ʵ��һ��֧�� '.'
�� '*' ��������ʽƥ�䡣
'.' ƥ�����ⵥ���ַ�
'*' ƥ���������ǰ�����һ��Ԫ��
��νƥ�䣬��Ҫ���� ���� �ַ��� s�ģ������ǲ����ַ�����
˵��:
s ����Ϊ�գ���ֻ������ a-z ��Сд��ĸ��
p ����Ϊ�գ���ֻ������ a-z ��Сд��ĸ���Լ��ַ� . �� *��
ʾ�� 1:
����:
s = "aa"
p = "a"
���: false
����: "a" �޷�ƥ�� "aa" �����ַ�����
*/
bool isMatch(char * s, char * p)
{
	if (!*p)
		return !*s;

	bool first_match = *s && (*s == *p || *p == '.');
	if (*(p+1) == '*') {
		return isMatch(s, p+2) || (first_match && isMatch(++s, p));
	}
	else {
		return first_match && isMatch(++s, ++p);
	}
}

int memo[100][100];
bool backtrack(char *s, char *p, int sIdx, int pIdx)
{
	if(s[sIdx] == '\0' && p[pIdx] == '\0')
		return true;//��������������˵��ƥ��ɹ�

	if(p[pIdx] == '\0')
		return false;//���p�ַ���ƥ�䵽���, ��sû��, ��ƥ�䲻�ɹ�

/*
���仯, �жϵ�ǰλ���Ƿ��ѹ�, ����ֱ�ӷ��ص�ǰ���, ʡ
ȥ�ظ�����
*/
	if(memo[sIdx][pIdx]!=-1)
		return memo[sIdx][pIdx];

	bool flag = false;//��ʼ���
	//�����жϸ�λ���Ƿ��ǵ�
	if(p[pIdx] == '.') {
/*
Ȼ���ж���һ���Ƿ���*, �����*, �����ƥ��s�е��������
ͬ�ַ�
*/
		if(p[pIdx+1] == '*') {
			//����s��ǰλ�õ�ĩβ, ���Ƿ���ƥ��ɹ�
			for(int i = sIdx;i<=strlen(s);i++) {
				flag = backtrack(s, p, i, pIdx+2); //p��.*����s, ���Լ�2
				if(flag == true)//�����ƥ��ֱ��ֹͣ
					break;
			}
		} else if(s[sIdx]!='\0') {//�����һ������*, һ��.ֻ��ƥ��һ���ַ�
			flag = backtrack(s, p, sIdx+1, pIdx+1);//p��.����sһ���ַ�, ���Ը���1
		}
	} else if(p[pIdx+1] == '*') {//�����ǰλ������ĸ, ��һ����*, *����ƥ��0������s���뵱ǰ��ĸһ�����ַ�
		flag = backtrack(s, p, sIdx, pIdx+2);//��ƥ��0�������, p����ĸ+*����s��0���ַ�
		if(flag == false) {//���ƥ�䲻�ɹ�
			for(int i = sIdx;i<strlen(s);i++) {//����s��ǰλ�õ�ĩβ, ���Ƿ���ƥ��ɹ�
				if(s[i] == p[pIdx])//��p����ĸ+*�Ƿ�ȼ���s��ǰλ�õ���ĸ, ���������һλ�õ�ƥ��
					flag = backtrack(s, p, i+1, pIdx+2);
				else//����ֹͣ
					break;
				if(flag == true)//���ƥ��ɹ�ֹͣ
					break;
			}
		}
	} else if(s[sIdx] == p[pIdx]) {//���������������������, ������ַ����, �������һλ��
		flag = backtrack(s, p, sIdx+1, pIdx+1);
	}

	//���������Ϊfalse
	memo[sIdx][pIdx] = flag;//���仯�洢
	return flag;
}

bool isMatch(char * s,  char * p)
{
	memset(memo, -1, sizeof(memo));//��-1Ϊδ���ʹ�
	return backtrack(s, p, 0, 0);
}


/*
351. ��׿ϵͳ���ƽ���
���Ƕ�֪����׿�и����ƽ����Ľ��棬��һ�� 3 x 3 �ĵ�����
�Ƴ���������
���������������ֱ�Ϊ ??m �� n������ 1 �� m �� n �� 9����ô��
��ͳ��һ���ж����ֽ������ƣ���������Ҫ���� m ���㣬
������ྭ�������� n ����ġ�
�����˽���ʲô��һ����Ч�İ�׿��������:
ÿһ���������Ʊ������پ��� m ���㡢��ྭ�� n ���㡣
���������ﲻ�����þ����ظ��ĵ㡣
��������������������˳�򾭹��ģ���ô������������ƹ�
��֮���Ǿ��Բ��ܿ���κ�δ�������ĵ㡣
�������˳��ͬ���ʾΪ��ͬ�Ľ������ơ�
����:
| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |
��Ч���ƣ�4 - 1 - 3 - 6
���ӵ� 1 �͵� 3 ʱ������δ�����ӹ��� 2 �ŵ㡣
��Ч���ƣ�4 - 1 - 9 - 2
���ӵ� 1 �͵� 9 ʱ������δ�����ӹ��� 5 �ŵ㡣
��Ч���ƣ�2 - 4 - 1 - 3 - 6
���ӵ� 1 �͵� 3 ����Ч�ģ���Ϊ��Ȼ�������˵� 2 �����ǵ� 2
�ڸ�������֮ǰ�Ѿ��������ˡ�
��Ч���ƣ�6 - 5 - 4 - 1 - 9 - 2
���ӵ� 1 �͵� 9 ����Ч�ģ���Ϊ��Ȼ�������˰��� 5 ������
�� 5 �ڸ�������֮ǰ�Ѿ��������ˡ�
*/
/*
��3�ֳ�������������������Ե���������ĳ������ֱ��Ӧ
4��4��1���ظ������
�����������Ƿ���Ի���ȥ������ͨ�����ķ�ʽ��á�
������һЩ�������裬��ô֮ǰ�����ߵĵ�֮����п��ܿ�
�����ˣ�ֻҪ�ж��������ŵ��м���Ѿ��߹��˾Ϳ�����
�ˡ�
�����ж�����֮���Ƿ���Ի���ȥ�ķ������ǣ�
1���Ȳ�����������ֱ���ߣ��������߼��жϣ�
2���ж����������м���Ƿ��Ѿ��߹��ˡ�
*/

static const bool walk_map[9][9] = {
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
};

static void backtrack(int arr[], int pos, int len, int level, int cnt[]);
int numberOfPatterns(int m, int n)
{
    int cnt[10] = {0};
    int corner[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    backtrack(corner, 1, 9, n, cnt);
    int edge[9] = {1, 0, 2, 3, 4, 5, 6, 7, 8};
    backtrack(edge, 1, 9, n, cnt);
    for (int i = 1; i <= n; i++)
        cnt[i] *= 4;
    int core[9] = {4, 0, 1, 2, 3, 5, 6, 7, 8};
    backtrack(core, 1, 9, n, cnt);

    int result = 0;
    for (int i = m; i <= n; i++)
        result += cnt[i];

    return result;
}

static inline void swap(int arr[], int l, int r)
{
    int temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

static inline bool can_walk(int arr[], int used, int from, int to)
{
    if (walk_map[from][to])
        return true;
    int spring_board = (from + to) / 2;
    for (int i = 0; i < used; i++)
        if (arr[i] == spring_board)
            return true;
    return false;
}

static void backtrack(int arr[], int pos, int len, int level, int cnt[])
{
    cnt[pos]++;
    if (pos == level)
        return;

    for (int i = pos; i < len; i++) {
        if (!can_walk(arr, pos, arr[pos - 1], arr[i]))
            continue;
        swap(arr, pos, i);
        backtrack(arr, pos + 1, len, level, cnt);
        swap(arr, pos, i);
    }
}

/*
306. �ۼ���
�ۼ�����һ���ַ���������������ֿ����γ��ۼ����С�
һ����Ч���ۼ����б������ٰ��� 3 �����������ʼ����
�������⣬�ַ����е���������������֮ǰ��������ӵĺ͡�
����һ��ֻ�������� '0'-'9' ���ַ�������дһ���㷨���жϸ�
�������Ƿ����ۼ�����
˵��: �ۼ���������������� 0 ��ͷ�����Բ������ 1, 2, 03 ��
�� 1, 02, 3 �������
ʾ�� 1:
����: "112358"
���: true
����: �ۼ�����Ϊ: 1, 1, 2, 3, 5, 8 ��1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
ʾ�� 2:
����: "199100199"
���: true
����: �ۼ�����Ϊ: 1, 99, 100, 199��1 + 99 = 100, 99 + 100 = 199
*/

void backtrack(char * num,int cidx, long *tmp,int tmpSize,bool *re)
{
	if(tmpSize >= 3) {
		if(tmp[tmpSize-3]+tmp[tmpSize-2]!=tmp[tmpSize-1]) {
			return;//����ʱ����������ָ�������3�����������ۼ���Ҫ�󣬲��ü������ң�ֱ�ӷ���
		}
	}

	if(cidx == strlen(num)) {//�ù����ַ������������ַ�
		if(tmpSize<3) return;//ֻ���������3�����֣��϶�Ϊ�٣�����

		int i  = 0;
		for(i  = 0;i<tmpSize-2;i++) {//������ʱ��������Ԫ���Ƿ������ۼ���Ҫ��
			if(tmp[i]+tmp[i+1]!=tmp[i+2]) {
				break;
			}
		}

		if(i == tmpSize-2) {//������������������ֵ��Ϊ��
			*re=true;
		}
		return;
	}
/*
���ڲ�����ǰ���㣬�����ǰ����Ϊ0����ô����ȡ������ֻ
��Ϊ0
*/	if(num[cidx] == '0') {
		tmp[tmpSize]  = 0;
		backtrack(num,cidx+1,tmp,tmpSize+1,re);
		return;
	}

	int i  = 0,cnt  = 0;
	long sum  = 0;
	for(i = cidx;i<strlen(num);i++) {//һ�����
		sum  = sum*10+num[i]-'0';
		cnt++;
/*
���������Ϊ�˷�ֹ���ֹ������long���ͣ����������뵽
���ĳ������ȡ�˴���strlen(num)/2���ȵ��ַ���
�Ͳ�����tmp[i]+tmp[i+1]  = tmp[i+2]�������
�������ü���cnt����ֹ�����������
*/
		if(2*cnt>strlen(num))
			break;
		tmp[tmpSize]  = sum;
		backtrack(num,i+1,tmp,tmpSize+1,re);
	}
}

bool isAdditiveNumber(char * num)
{
	if(strlen(num)<3)
		return false;

	bool re  = false;
	int size  = 0;
	long tmp[strlen(num)];//��ʱ���ȡ����n���ַ���ɵ�����
	memset(tmp,0,sizeof(tmp));
	backtrack(num,0,tmp,0,&re);
	return re;
}


/*
79. ��������
����һ����ά�����һ�����ʣ��ҳ��õ����Ƿ����������
�С�
���ʱ��밴����ĸ˳��ͨ�����ڵĵ�Ԫ���ڵ���ĸ���ɣ�
���С����ڡ���Ԫ������Щˮƽ���ڻ�ֱ���ڵĵ�Ԫ��
ͬһ����Ԫ���ڵ���ĸ�������ظ�ʹ�á�
ʾ��:
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
���� word = "ABCCED", ���� true
���� word = "SEE", ���� true
���� word = "ABCB", ���� false
*/

int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool backtrack(char** board, int row, int col, int cx, int cy, char *word, int wordIdx)
{
	if (wordIdx == strlen(word)) {
		return true;
	}

	if (cx  < 0 || cx >= row || cy < 0 || cy >= col) {
		return false;
	}

	if (board[cx][cy] == 0) {
		return false;
	}

	if (board[cx][cy] != word[wordIdx]) {
		return false;
	}

	int tmp = board[cx][cy];
	board[cx][cy] = 0;

	for (int i = 0; i < 4; i++) {
		int nx = cx + dir[i][0];
		int ny = cy + dir[i][1];

		bool ret = backtrack(board, row, col, nx, ny,  word, wordIdx + 1);
		if (ret) {
			return true;
		}
	}

	board[cx][cy] = tmp;
	return false;
}

bool exist(char** board, int boardSize, int* boardColSize, char * word)
{
	int row = boardSize;
	int col = *boardColSize;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == word[0]) {
				bool ret = backtrack(board, row, col, i, j, word, 0);
				if (ret) {
					return true;
				}
			}
		}
	}

	return false;
}

/*
89. ���ױ���
���ױ�����һ������������ϵͳ���ڸ�ϵͳ�У�����������
��ֵ����һ��λ���Ĳ��졣
����һ�����������λ���ķǸ����� n����ӡ����ױ�����
�С���ʹ�ж����ͬ�𰸣���Ҳֻ��Ҫ��������һ�֡�
���ױ������б����� 0 ��ͷ��
ʾ�� 1:
����: 2
���: [0,1,3,2]
����:
00 - 0
01 - 1
11 - 3
10 - 2
���ڸ����� n������ױ������в���Ψһ��
���磬[0,2,3,1] Ҳ��һ����Ч�ĸ��ױ������С�
00 - 0
10 - 2
11 - 3
01 - 1
*/


/// �ݹ鸨������
int helper(int* ret, int* repeat, int n, int size, int i)
{
    /// �ݹ���ڣ�����Ѿ������һ�����뷵�ؽ�����־
    if (i == size - 1)
        return 1;

    int code;

    /// ���Էֱ�Ե� i �λ�ñ����ÿһλ���з�ת
    for (int j = 0; j < n; ++j)
    {
        /// ����������������±���
        code = ret[i] ^ (1u << j);

        /// ����ñ����Ѿ�ʹ�ù�������
        if (repeat[code])
            continue;

        /// ���±������ظ���
        ret[i + 1] = code;
        repeat[code] = 1;

        /// �ݹ����һ��������м���
        if (helper(ret, repeat, n, size, i + 1))
            return 1;
    }

    return 0;
}

int* grayCode(int n, int* returnSize)
{
    /// ����ĸ�����ֱ���� n ȷ��
	*returnSize = pow(2, n);

    /// ��������µ�һ��Ԫ�ض��� 0
    int* ret = malloc(sizeof(int) * *returnSize);
    *ret = 0;

    /// ��� n Ϊ 0 ��ֱ�ӷ���
    if (*returnSize == 0)
    {
        return ret;
    }

    /// ��ʼ���ظ�������Ĭ������� 0 �Ѿ���ʹ�ù�
    int* repeat = calloc(sizeof(int), *returnSize);
    *repeat = 1;

    helper(ret, repeat, n, *returnSize, 0);

    free(repeat);

    return ret;
}


/*
131. �ָ���Ĵ�
����һ���ַ��� s���� s �ָ��һЩ�Ӵ���ʹÿ���Ӵ���
�ǻ��Ĵ���
���� s ���п��ܵķָ����
ʾ��:
����: "aab"
���:
[
  ["aa","b"],
  ["a","a","b"]
]
*/

#define MAX_RET 10000

char ***g_ans;
int g_ansSize;

char *substr(char *s, int l, int r) {
    char *sub = malloc(r - l + 2);
    int index = 0;
    while (l <= r) {
        sub[index++] = s[l++];
    }
    sub[index] = '\0';
    return sub;
}

bool isPalindrome(char *s, int l, int r) {
    if (l == r) {
        return true;
    }
    while (l < r) {
        if (s[l++] != s[r--]) {
            return false;
        }
    }
    return true;
}

void dump(char **subs, int subSize) {
    for (int i = 0; i < subSize; ++i) {
        printf("%s, ", subs[i]);
    }
    printf("\n");
}

void copyToAns(char **subs, int subSize, int *retColSize) {
    g_ans[g_ansSize] = malloc(sizeof(char *) * subSize);
    retColSize[g_ansSize] = subSize;
    for (int i = 0; i < subSize; ++i) {
        g_ans[g_ansSize][i] = malloc(sizeof(char) * (strlen(subs[i]) + 1)); // one more char for '\0'
        strcpy(g_ans[g_ansSize][i], subs[i]);
    }
    ++g_ansSize;
}

void backtrack(char *s, int len, int pos, char **subs, int subSize, int *retColSize) {
    if (pos == len) {
            // dump(subs, subSize);
        copyToAns(subs, subSize, retColSize);
        return;
    }
    for (int i = pos; i < len; ++i) {
        if (isPalindrome(s, pos, i)) {
            subs[subSize] = substr(s, pos, i);
            backtrack(s, len, i + 1, subs, subSize + 1, retColSize);
            free(subs[subSize]);
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** partition(char * s, int* returnSize, int** returnColumnSizes){
    g_ansSize = 0;
    g_ans = (char ***)malloc(sizeof(char *) * MAX_RET);
    char **tmpSubs = malloc(sizeof(char *) * strlen(s));    // s can be splited into strlen(s) sub strings if length of each sub string is 1
    *returnColumnSizes = (int *)malloc(sizeof(int) * MAX_RET);
    backtrack(s, strlen(s), 0, tmpSubs, 0, *returnColumnSizes);
    *returnSize = g_ansSize;

    free(tmpSubs);
    return g_ans;
}

