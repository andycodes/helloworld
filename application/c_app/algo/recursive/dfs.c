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


�������(������)
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
		/* i  :ÿ��������ÿ��������ظ�ʹ�� */
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
		/* i + 1 :ÿ��������ÿ�������ֻ��ʹ��һ�� */
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
		/*i + 1 :ÿ������в������ظ������֡�
		��Ϊ��������Ԫ�ػ�����ͬ��
		�����һ�����������Ӧ������һ�����������ֵ + 1��*/
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
90. �Ӽ� II
����һ�����ܰ����ظ�Ԫ�ص��������� nums�����ظ���������
���ܵ��Ӽ����ݼ�����
˵�����⼯���ܰ����ظ����Ӽ���
ʾ��:
����: [1,2,2]
���:
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
int numOfMinutes(int n, int headID, int* manager, int managerSize,
int* informTime, int informTimeSize)
{
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (informTime[i] != 0) { //Ҷ�ӽڵ�
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
DFS�Զ�����
�㷨����
ʹ���ڽӱ�����ʾ��Ŀ�е�N������
����headidΪ��㣬�������ı�������¼���������м����
��
���֪ͨʱ�䣬��Ϊ�𰸡�
*/


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
		�ظ���������磬())()��������ͬ������)����һ����ô
		ѡ��ǰһ��ɾ����һ��������ɾ��ǰһ��ѡ���һ������
		���������ͬ�ģ��ᵼ���ظ������������Ȼ���ǲ�����
		����
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

/*
967. ��������ͬ������
�������г���Ϊ N ��������ÿ��������λ�ϵ�����֮���
��ľ���ֵΪ K �ķǸ�������
��ע�⣬�������� 0 ����֮�⣬���е�ÿ�����ֶ�����
��ǰ���㡣���磬01 ��Ϊ��һ��ǰ���㣬��������Ч�ģ�
�� 0 ����Ч�ġ�
����԰��κ�˳�򷵻ش𰸡�
ʾ�� 1��
���룺N = 3, K = 7
�����[181,292,707,818,929]
���ͣ�ע�⣬070 ����һ����Ч�����֣���Ϊ����ǰ���㡣
ʾ�� 2��
���룺N = 2, K = 1
�����[10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
��ʾ��
1 <= N <= 9
0 <= K <= 9
ͨ������3,737�ύ����9,891
*/
#define MAX_SIZE 5000
void dfs(int N, int K, int *res, int *returnSize, int num, int result)
{
	if (result != 0 && abs((result) % 10 - num) != K) {
	// ������������λ���K��ֱ�ӷ���
		return;
	}

	if (N == 1) { //�� N== 1 ʱ��Nλ�������������res�����
		result = (result) * 10 + num;  //����ƥ��Ľ��
		res[(*returnSize)++] = result;
		return;
	}

	for (int i = 0; i < 10; i++) {
		dfs(N - 1, K, res, returnSize, i, result * 10 + num);
	}
}
//�Ӹ�λ����λ
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
329. �����е������·��
����һ�����������ҳ������·���ĳ��ȡ�

����ÿ����Ԫ����������ϣ��£������ĸ������ƶ��� �㲻���ڶԽ��߷������ƶ����ƶ����߽��⣨���������ƣ���

ʾ�� 1:

����: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
���: 4
����: �����·��Ϊ [1, 2, 6, 9]��
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
������ 08.06. ��ŵ������
�ھ��人ŵ�������У��� 3 �����Ӽ� N ����ͬ��С�Ĵ���Բ�̣����ӿ��Ի�������һ�����ӡ�һ��ʼ�������������϶��°������������ڵ�һ��������(��ÿһ������ֻ�ܷ��ڸ������������)���ƶ�Բ��ʱ�ܵ���������:
(1) ÿ��ֻ���ƶ�һ������;
(2) ����ֻ�ܴ����Ӷ��˻����Ƶ���һ������;
(3) ����ֻ�ܵ��ڱ�����������ϡ�

���д������ջ���������Ӵӵ�һ�������Ƶ����һ�����ӡ�

����Ҫԭ���޸�ջ��

ʾ��1:

 ���룺A = [2, 1, 0], B = [], C = []
 �����C = [2, 1, 0]
ʾ��2:

 ���룺A = [1, 0], B = [], C = []
 �����C = [1, 0]
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
248. ���ĶԳ��� III
���ĶԳ�����ָһ����������ת�� 180 ��֮������������ͬ�����֣��������µߵ��ؿ�����

дһ�����������㷶Χ�� [low, high] ֮�����ĶԳ����ĸ�����

ʾ��:

����: low = "50", high = "100"
���: 3
����: 69��88 �� 96 �������ڸ÷�Χ�ڵ����ĶԳ���
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
        count = 3;  // ����λ��
    } else {
        count = 1;
    }
    n -= 2;
    count *= 4; // ��β
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
761. ����Ķ���������
����Ķ����������Ǿ��������������ʵĶ��������У�

0 �������� 1 ��������ȡ�
���������е�ÿһ��ǰ׺���� 1 ������Ҫ���ڵ��� 0 ��������
����һ������Ķ��������� S�����ַ�����ʽ��ʾ������һ������ Ϊ����ѡ�� S �����������ҷǿյ�������Ӵ���Ȼ�����ǽ������������Ӵ�Ϊ�����ĵ��ҽ�����һ���Ӵ������һ���ַ�ǡ��Ϊ�ڶ����Ӵ��ĵ�һ���ַ���ǰһ���ַ���)

����������Ĳ���֮�󣬽�������ַ��������ֵ������е����Ľ����ʲô��

ʾ�� 1:

����: S = "11011000"
���: "11100100"
����:
���Ӵ� "10" ����S[1]���֣� �� "1100" ����S[3]���֣����н�����
�����ڽ������ɴβ������ֵ����������Ľ����
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
514. ����֮·
������Ϸ������4���У�����ͨ�����ɡ�Ҫ����ҵ�����Ϊ��Freedom Trail Ring���Ľ������̣���ʹ�ñ���ƴд�ض��ؼ��ʲ��ܿ��š�

����һ���ַ��� ring����ʾ�����⻷�ϵı��룻������һ���ַ��� key����ʾ��Ҫƴд�Ĺؼ��ʡ�����Ҫ����ܹ�ƴд�ؼ����������ַ������ٲ�����

�����ring �ĵ�һ���ַ���12:00������롣����Ҫ˳ʱ�����ʱ����ת ring ��ʹ key ��һ���ַ��� 12:00 ������룬Ȼ�������İ�ť���Դ����ƴд�� key �е������ַ���

��ת ring ƴ�� key �ַ� key[i] �Ľ׶��У�

�����Խ� ring ˳ʱ�����ʱ����תһ��λ�ã���Ϊ1������ת������Ŀ���ǽ��ַ��� ring ��һ���ַ��� 12:00 ������룬��������ַ���������ַ� key[i] ��
����ַ� key[i] �Ѿ����뵽12:00��������Ҫ�������İ�ť����ƴд����Ҳ������ 1 ��������֮�������Կ�ʼƴд key ����һ���ַ�����һ�׶Σ�, ֱ���������ƴд��
ʾ����





����: ring = "godding", key = "gd"
���: 4
����:
 ���� key �ĵ�һ���ַ� 'g'���Ѿ�����ȷ��λ��, ����ֻ��Ҫ1����ƴд����ַ���
 ���� key �ĵڶ����ַ� 'd'��������Ҫ��ʱ����ת ring "godding" 2��ʹ����� "ddinggo"��
 ��Ȼ, ���ǻ���Ҫ1������ƴд��
 ������յ������ 4��
*/

#include <limits.h>
#define MMIN(a, b)      ((a) < (b)? (a) : (b))

char *rr;
int rlen;
char *kk;
int klen;

int memo[100][100];

//���ش�rid����kid��λ�ñ��������е���С����
int helper(int rid, int kid) {
    if(kid == klen) {
        return 0;
    }

    if(memo[rid][kid] != 0) {
        return memo[rid][kid] - 1;
    }

    int min_steps = INT_MAX;
    int cur_steps = 0;

    //����ring���ҵ����е���ͬλ��
    for(int i = 0; i < rlen; i++) {
        //ʵ�ʷ���λ��
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

//���㷨˼·��DFS��
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

