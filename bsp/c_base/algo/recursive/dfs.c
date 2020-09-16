/*
DFS

ģ��
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


BFS+DFS����
���򴫲�
��ͨ������
*/


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

target ����-->0
sum �ӷ�--->target
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
		2367������Ͽ���
		  367������Ͽ���
		   67������Ͽ���
		     7������Ͽ���
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

	for (int i = start; i < candidatesSize && target > 0 && candidates[i] <= target; i++) {
/*����֮����ͬ�Ŀ϶��ǰ��ŵģ�
if��candidates[i] == candidates[i - 1]�����Ǿ͹��˵�candidates[i]*/
/*
�����������/�Ӽ�/���У�ֻҪԭ�����к����ظ�Ԫ�أ�ͨ��һ��ȥ�ط�����
1.������ʹ��ͬԪ�����ڣ�
2.��backtrack��forѭ���


if(i>start&&candidates[i]==candidates[i-1]) continue;
����i>startһ��Ҫ��⣬i�ǵ�ǰ�����Ԫ���±꣬start�Ǳ����ʼ���Ǹ�Ԫ�ص��±꣬���ǵ�ȥ����Ҫͬ��ȥ�أ�
�����ֻдcandidates[i]==candidates[i-1]��һ���ж���������ô��dfs����ʱ������ͬ�����ͬԪ�ص����/����Ҳ�����ɲ���
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
		/*i + 1 :ÿ������в������ظ������֡�
		��Ϊ��������Ԫ�ػ�����ͬ��
		�����һ�����������Ӧ������һ�����������ֵ + 1��*/
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
1034. �߿���ɫ
����һ����ά�������� grid�������е�ÿ��ֵ��ʾ��λ�ô���
��������ɫ��
ֻ�е�������������ɫ��ͬ���������ĸ�����������һ��
����������ʱ����������ͬһ��ͨ������
��ͨ�����ı߽���ָ��ͨ�����е������벻�ڷ����е�����
�����ڣ��ĸ������ϣ������������Σ�����������ı߽�
�ϣ���һ��/�л����һ��/�У������������Ρ�
����λ�� (r0, c0) ����������ɫ color��ʹ��ָ����ɫ color Ϊ��
����������ͨ�����ı߽������ɫ�����������յ�����
grid ��
ʾ�� 1��
���룺grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
�����[[3, 3], [3, 2]]
ʾ�� 3��
���룺grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
�����[[2, 2, 2], [2, 1, 2], [2, 2, 2]]
*/
int dis[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
void dfs(int** g, int gridSize, int* gridColSize, int cx, int cy, int oldcolor, int newcolor)
{
	// Խ�� || ������ͬһ����ͨ���� || �����ʹ�
	if(cx < 0 || cx >= gridSize || cy < 0 || cy >= gridColSize[cx] ||
		g[cx][cy] != oldcolor || g[cx][cy] < 0) {
		return;
	}

	// ��ǰ�ڵ��Ѿ������ʣ����ø�ֵ
	g[cx][cy] = -oldcolor;

	// �жϱ߽�
	if(cx == 0 || cx+1 >= gridSize || cy == 0 || cy+1 >= gridColSize[cx]) {
		// ����߽�
		g[cx][cy] = -newcolor;
	} else {
		// ��ͨ�����ı߽�
		for(int i = 0 ; i < 4 ; i++) {
			int nextColor = g[cx + dis[i][0]][cy + dis[i][1]];
			// �����ǹؼ���
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
1391. ����������Ƿ������Ч·��
��UF
*/

int dirs[4][2] = {
	{-1, 0},    //��
	{0, -1},    //��
	{0, 1},     //��
	{1, 0}      //��
};

bool interfaces[7][4] = {
	//��    ��      ��      ��
	{false, false, false,  false},      //0�� dummy
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
		//��ͼ��û�е�ǰ����ӿ�,continue
		if(interfaces[val][i] == false)
			continue;

		//����е�ǰ����ӿڣ�����÷������ھӵ�����
		int nx = row + dirs[i][0];
		int ny = col + dirs[i][1];

		//����Խ����
		if(nx >= gridSize || nx < 0 || ny < 0 || ny >= gridColSize[row]){
			continue;
		}
		/*
		�жϸ��ھ��Ƿ��ж�Ӧ����(��3-i)�Ľӿڣ�
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
1376. ֪ͨ����Ա�������ʱ��
�Ѷ��е�24
��˾���� n ��Ա����ÿ��Ա���� ID ���Ƕ�һ�޶��ģ���Ŵ� 0
�� n - 1����˾���ܸ�����ͨ�� headID ���б�ʶ��
�� manager �����У�ÿ��Ա������һ��ֱ�������ˣ����� manager[i]
�ǵ� i ��Ա����ֱ�������ˡ������ܸ����ˣ�manager[headID] = -1��
��Ŀ��֤������ϵ���������ṹ��ʾ��
��˾�ܸ�������Ҫ��˾����Ա��ͨ��һ��������Ϣ������
������֪ͨ����ֱ�������ǣ�Ȼ������Щ����֪ͨ���ǵ���
����ֱ�����е�Ա������֪����������Ϣ��
�� i ��Ա����Ҫ informTime[i] ������֪ͨ��������ֱ��������Ҳ��
��˵�� informTime[i] ���Ӻ���������ֱ�����������Կ�ʼ����
��һ��Ϣ����
����֪ͨ����Ա����һ������Ϣ����Ҫ�� ������ ��

ʾ�� 1��
���룺n = 1, headID = 0, manager = [-1], informTime = [0]
�����0
���ͣ���˾�ܸ������Ǹù�˾��Ψһһ��Ա����
ʾ�� 2��

���룺n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
�����1
���ͣ�id = 2 ��Ա���ǹ�˾���ܸ����ˣ�Ҳ����������Ա����
ֱ�������ˣ�����Ҫ 1 ������֪ͨ����Ա����
��ͼ��ʾ�˹�˾Ա�������ṹ��

*/

/*DFS�Ե�����
1) ��ÿ��Ҷ�ӽڵ�����ݹ�����,�ó�ÿ��·�����ۼƷ�
��
2)�����·�����ֵ
*/
int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime,
int informTimeSize)
{
	int res = 0;

	for(int i =0;i<managerSize;i++){
		if(informTime[i]==0){ //Ҷ�ӽڵ�
			//��ʱֵ
			int temp = 0;
			int index=i;
			//���ϱ���
			while(index!=-1) {
				temp+=informTime[index];
				index=manager[index];
			}
			res = fmax(res,temp);
		}
	}
	return res;
}

/*DFS�Ե�����
��������Ա������������ײ�Ա����Ҷ�ӽڵ㣩��
DFS�������ڵ㣬ֱ��û�и��ڵ�Ϊֹ����¼���б���
�����ʱ�伴Ϊ�𰸡�*/
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
		if (informTime[i] != 0) {//����Ҷ�ӽڵ�
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
����headidΪ��㣬�������ı�������¼���������м����
��
���֪ͨʱ�䣬��Ϊ�𰸡�
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
301. ɾ����Ч������
�Ѷ�����217
ɾ����С��������Ч���ţ�ʹ��������ַ�����Ч����
�����п��ܵĽ����
˵��: ������ܰ����˳� ( �� ) ������ַ���
ʾ�� 1:
����: "()())()"
���: ["()()()", "(())()"]
ʾ�� 2:
����: "(a)())()"
���: ["(a)()()", "(a())()"]

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
		�ظ���������磬())()��������ͬ������)����һ����ôѡ��ǰһ��ɾ����һ��������ɾ��ǰһ��ѡ���һ���������������ͬ�ģ��ᵼ���ظ������������Ȼ���ǲ����ظ������ߣ�durant-5���ӣ�https://leetcode-cn.com/problems/remove-invalid-parentheses/solution/jian-zhi-de-yi-xie-xi-jie-by-durant-5/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
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
93. ��ԭIP��ַ
�Ѷ��е�320
����һ��ֻ�������ֵ��ַ�������ԭ�����������п��ܵ� IP ��ַ��ʽ��
��Ч�� IP ��ַ�������ĸ�������ÿ������λ�� 0 �� 255 ֮����ɣ�������֮���� '.' �ָ���

ʾ��:
����: "25525511135"
���: ["255.255.11.135", "255.255.111.35"]
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
491. ����������
�Ѷ��е�104
����һ����������, ����������ҵ����и�����ĵ�����
���У����������еĳ���������2��
ʾ��:
����: [4, 6, 7, 7]
���: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
˵��:
1.	��������ĳ��Ȳ��ᳬ��15��
2.	�����е�������Χ�� [-100,100]��
3.	���������п��ܰ����ظ����֣���ȵ�����Ӧ�ñ���
Ϊ������һ�������
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
		// ȥ�أ����㲻�ظ�������ͬ������
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
133. ��¡ͼ
�������� ��ͨ ͼ��һ���ڵ�����ã����㷵�ظ�ͼ�� �������¡����
ͼ�е�ÿ���ڵ㶼��������ֵ val��int�� �����ھӵ��б�list[Node]����
class Node {
    public int val;
    public List<Node> neighbors;
}

����������ʽ��
�������ÿ���ڵ��ֵ��������������ͬ�����磬��һ���ڵ�ֵΪ 1��val = 1�����ڶ����ڵ�ֵΪ 2��val = 2�����Դ����ơ���ͼ�ڲ���������ʹ���ڽ��б��ʾ��
�ڽ��б� �����ڱ�ʾ����ͼ�������б�ļ��ϡ�ÿ���б�������ͼ�нڵ���ھӼ���
�����ڵ㽫ʼ����ͼ�еĵ�һ���ڵ㣨ֵΪ 1��������뽫 �����ڵ�Ŀ��� ��Ϊ�Կ�¡ͼ�����÷��ء�

ʾ�� 1��

���룺adjList = [[2,4],[1,3],[2,4],[1,3]]
�����[[2,4],[1,3],[2,4],[1,3]]
���ͣ�
ͼ���� 4 ���ڵ㡣
�ڵ� 1 ��ֵ�� 1�����������ھӣ��ڵ� 2 �� 4 ��
�ڵ� 2 ��ֵ�� 2�����������ھӣ��ڵ� 1 �� 3 ��
�ڵ� 3 ��ֵ�� 3�����������ھӣ��ڵ� 2 �� 4 ��
�ڵ� 4 ��ֵ�� 4�����������ھӣ��ڵ� 1 �� 3 ��
ʾ�� 2��

*/
struct Node* dfs(struct Node* s, struct Node** visited)
{
	if (s == NULL) {
		return NULL;
	}
/*
����ýڵ��Ѿ������ʹ��ˣ���ֱ�Ӵӹ�ϣ����ȡ����
Ӧ�Ŀ�¡�ڵ㷵��
*/
	if (visited[s->val]) {
		return visited[s->val];
	}
/*
��¡�ڵ㣬ע�⵽Ϊ��������ǲ����¡�����ھӵ�
�б�
*/
	struct Node* cloneNode = (struct Node*)malloc(sizeof(struct Node));
	cloneNode->val = s->val;
	cloneNode->numNeighbors = s->numNeighbors;

// ��ϣ��洢
	visited[cloneNode->val] = cloneNode;
	cloneNode->neighbors = (struct Node**)malloc(sizeof(struct Node*) * cloneNode->numNeighbors);

// �����ýڵ���ھӲ����¿�¡�ڵ���ھ��б�
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

