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
1219                                                                                                                                                                                                . �ƽ��
��Ҫ����һ����󣬵��ʿ���ѧ���Ѿ�̽����
��������е���Դ�ֲ������ô�СΪ m * n ������
grid �����˱�ע��ÿ����Ԫ���е������ͱ�ʾ��һ
��Ԫ���еĻƽ�����������õ�Ԫ���ǿյģ���ô���� 0��
Ϊ��ʹ������󻯣�����Ҫ�����¹��������ɻƽ�
ÿ���󹤽���һ����Ԫ���ͻ��ռ��õ�Ԫ���е����лƽ�
��ÿ�ο��Դӵ�ǰλ�������������ĸ������ߡ�
ÿ����Ԫ��ֻ�ܱ����ɣ����룩һ�Ρ�
���ÿ��ɣ����룩�ƽ���ĿΪ 0 �ĵ�Ԫ��
�󹤿��Դ������� ����һ�� �лƽ�ĵ�Ԫ�����������ֹͣ��


ʾ�� 1��

���룺grid = [[0,6,0],[5,8,7],[0,9,0]]
�����24
���ͣ�
[[0,6,0],
 [5,8,7],
 [0,9,0]]
һ���ռ����ƽ��·���ǣ�9 -> 8 -> 7��
*/
int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int backtrack(int** grid, int row, int col, int x, int y)
{
	int curVal = grid[x][y];
	grid[x][y] = 0;
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + d[i][0];
		int ny = y + d[i][1];

		if (nx < 0 || nx >= row || ny < 0 || ny >= col || grid[nx][ny] == 0) {
			continue;
		}

		sum = fmax(sum, backtrack(grid, row, col, nx, ny));
	}

	grid[x][y] = curVal;
	return sum + curVal;
}

int getMaximumGold(int** grid, int gridSize, int* gridColSize){
    if(grid == NULL || gridSize <= 0 || gridColSize == NULL) {
        return 0;
    }

    int row = gridSize;
    int col = *gridColSize;
    int res = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i];j++) {
            if (grid[i][j] != 0) {
                res = fmax(res, backtrack(grid, row, col, i, j));
            }
        }
    }

    return res;
}

/*
46. ȫ����
�Ѷ��е�838
����һ�� û���ظ� ���ֵ����У����������п��ܵ�ȫ���С�
ʾ��:
����: [1,2,3]
���:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

*/
void backtrack(int* nums, int numsSize, int* returnSize, int** returnColumnSizes,
                int** res, bool* visited, int* path, int pathSize)
{
	if (numsSize == pathSize) {
		res[*returnSize] = (int*)malloc(numsSize * sizeof(int));
		memcpy(res[*returnSize], path, numsSize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = numsSize;
		(*returnSize)++;
		return;
	}

        for (int index = 0; index < numsSize; index++) {
		if (visited[index] == true) {
			continue;
		}

                visited[index] = true;
                path[pathSize] = nums[index];
                pathSize++;

                backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, pathSize);

                pathSize--; // ����
                visited[index] = false;
        }
}

int** permute(int* nums, int numsSize, int* returnSize,
			     int** returnColumnSizes)
{
	int **res = (int **)calloc (17000,  sizeof(int *));
	*returnColumnSizes = (int *)calloc(17000, sizeof(int));
	int path[numsSize];
	memset(path, 0, sizeof(path));
	bool visited[numsSize];
	memset(visited, false, sizeof(visited));
	*returnSize = 0;
	backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, 0);
	return res;
}

/*
47. ȫ���� II
�Ѷ��е�320
����һ���ɰ����ظ����ֵ����У��������в��ظ���ȫ���С�
ʾ��:
����: [1,1,2]
���:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/
#define MAX_SIZE 5000
void backtrack(int* nums, int numsSize, int* returnSize, int** returnColumnSizes,
                int** res, bool* visited, int* path, int pathSize)
{
	if (numsSize == pathSize) {
		res[*returnSize] = (int*)malloc(numsSize * sizeof(int));
		memcpy(res[*returnSize], path, numsSize * sizeof(int));
		(*returnColumnSizes)[*returnSize] = numsSize;
		(*returnSize)++;
		return;
	}

        for (int index = 0; index < numsSize; index++) {
		if (visited[index] == true) {
			continue;
		}

		if (index > 0 &&  visited[index - 1] == true &&  nums[index - 1] == nums[index]) {
			continue;
		}

                visited[index] = true;
                path[pathSize] = nums[index];
                pathSize++;

                backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, pathSize);

                pathSize--; // ����
                visited[index] = false;
        }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

    int** res = (int**)malloc(MAX_SIZE * sizeof(int*));
    bool* visited = (bool*)malloc(numsSize * sizeof(bool));
    memset(visited, false, numsSize);
    int* path = (int*)malloc(numsSize * sizeof(int));

    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(MAX_SIZE * sizeof(int));

    backtrack(nums, numsSize, returnSize, returnColumnSizes, res, visited, path, 0);

    return res;
}

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
int cmp_char(const void *a, const void *b)
{
	return  *((char *)a) - *((char *)b);
}

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
void backtrack(int num, char ** res, int* returnSize,
int hour, int minute, int it)
{
	if (num == 0) {
		res[*returnSize] = (char *)calloc(10, sizeof(char *));
		sprintf(res[*returnSize] , "%d:%02d", hour, minute);
		(*returnSize)++;
		return;
	}
/*
0 - 5 �� ���� 6 - 9 ��Сʱ��
*/
	for (int i = it; i < 10; i++) {
		if (i <= 5) {
			minute += (1 << i);
			if (minute > 59) {
				minute -= (1 << i);
				continue;
			}
		} else {
			hour += (1 << i - 6);//�������ȼ�����<<
			if (hour > 11)
				return;
		}

		backtrack(num -1, res,  returnSize, hour,  minute, i + 1);

		if (i <= 5)
			minute -= (1 << i);
		else
			hour -= (1 << i - 6);
	}
}

char ** readBinaryWatch(int num, int* returnSize)
{
	char ** res = (char **)calloc(1024, sizeof(char *));

	*returnSize = 0;
	backtrack(num, res, returnSize, 0, 0, 0);

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
bool backtrack(int** obstacleGrid, int row, int col, int itx, int ity,
int **res, int *returnSize,  bool visited[][100], int** returnColumnSizes)
{
	if(itx >= row || ity >= col || obstacleGrid[itx][ity] == 1 || visited[itx][ity])
		return false;

	visited[itx][ity] = 1;
	res[*returnSize] = (int *)calloc(2, sizeof(int));
	res[*returnSize][0] = itx;
	res[*returnSize][1] = ity;
	(*returnColumnSizes)[*returnSize] = 2;
	(*returnSize)++;

	if(itx == (row - 1) && ity == (col - 1)) {
		return true;
	}

	if (backtrack(obstacleGrid, row, col, itx, ity + 1, res, returnSize, visited, returnColumnSizes) ||
		backtrack(obstacleGrid, row, col, itx + 1, ity, res, returnSize, visited, returnColumnSizes)) {
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
332. ���°����г�
�Ѷ��е�102
����һ����Ʊ���ַ�����ά���� [from, to]���������е�������Ա
�ֱ��ʾ�ɻ������ͽ���Ļ����ص㣬�Ը��г̽������¹�
������������Щ��Ʊ������һ����JFK������Ϲ��ʻ�����
���������������Ը��г̱���� JFK ������
˵��:
1.	������ڶ�����Ч���г̣�����԰��ַ���Ȼ���򷵻�
��С���г���ϡ����磬�г� ["JFK", "LGA"] �� ["JFK", "LGB"] ��Ⱦ͸�
С���������ǰ
2.	���еĻ�������������д��ĸ��ʾ���������룩��
3.	�ٶ����л�Ʊ���ٴ���һ�ֺ�����г̡�
ʾ�� 1:
����: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
���: ["JFK", "MUC", "LHR", "SFO", "SJC"]
ʾ�� 2:
����: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
���: ["JFK","ATL","JFK","SFO","ATL","SFO"]
����: ��һ����Ч���г��� ["JFK","SFO","ATL","JFK","ATL","SFO"]��������
��Ȼ������������

*/
 void backtrack(char *** tickets, int ticketsSize,
 	char ** res, char *start, int *count, int *visited)
 {  //�����ɻ�Ʊ
	for (int i = 0; i < ticketsSize; i++) {
		if (visited[i] == 0 && strcmp(start, tickets[i][0]) == 0) {//�ҵ�Ŀ�ĵ�
			(*count)++;
			visited[i] = 1;
			char *newStart = tickets[i][1];

			//��Ŀ�ĵؼӵ����������
			res[*count] = strdup(newStart);
			//�����¸�Ŀ�ĵ�
			backtrack(tickets, ticketsSize, res, newStart, count, visited);
			//������������ˣ��򷵻ء�
			if (*count  == ticketsSize ) {
				return;
			}
			//�����������
			(*count)--;
			visited[i] = 0;
		}
	}
 }

int cmp(const void *str1, const void *str2)
{
    const char **tmp1 = *(char**)str1;
    const char **tmp2 = *(char**)str2;
    int ret = strcmp(tmp1[0], tmp2[0]);
    if (ret == 0) {
        return strcmp(tmp1[1], tmp2[1]);
    }

    return ret;
}

char ** findItinerary(char *** tickets, int ticketsSize, int* ticketsColSize, int* returnSize)
{
	*returnSize = ticketsSize + 1;
	char **res = (char**)calloc(*returnSize, sizeof(char*));
	qsort(tickets, ticketsSize, sizeof(tickets[0]), cmp);

	res[0] = strdup("JFK");
	int count = 0;
	int visited[ticketsSize];
	memset(visited, 0, sizeof(visited));
	backtrack(tickets, ticketsSize, res, res[0], &count, visited);

	return res;
}


/*
638. �����
�Ѷ��е�97
��LeetCode�̵��У� ��������۵���Ʒ��
Ȼ����Ҳ��һЩ�������ÿ����������Żݵļ۸���������
һ����Ʒ��
�ָ���ÿ����Ʒ�ļ۸�ÿ�������������Ʒ���嵥���Լ�
������Ʒ�嵥�������ȷ����ɴ����嵥����ͻ��ѡ�
ÿ�����������һ�������е�һ���������������һ������
���������ļ۸��������ֱַ��ʾ�ں�������������Ʒ
��������
�������������޴ι���
ʾ�� 1:
����: [2,5], [[3,0,5],[1,2,10]], [3,2]
���: 14
����:
��A��B������Ʒ���۸�ֱ�Ϊ?2��?5��
�����1���������?5�ļ۸���3A��0B��
�����2�� �������?10�ļ۸���1A��2B��
����Ҫ����3��A��2��B�� �����㸶��?10������1A��2B��
�����2�����Լ�?4����2A��
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
�������۸�ȥ�滻ԭ�ۣ�����滻����ܼۣ�
������С�ܼ�
*/
int g_res;
void backtrack(int** special, int specialSize, int* specialColSize, int* needs,
	int needsSize, int *specialOrinPrice, int totalNeedOrinPrice)
{
	for (int i = 0; i < needsSize; i++) {
		if (needs[i] < 0) {
			return;
		}
	}

	g_res = fmin(g_res, totalNeedOrinPrice);

	for (int i = 0; i < specialSize; i++) {
		for (int j = 0; j < specialColSize[i] - 1; j++) {
			needs[j] -= special[i][j];
		}

		backtrack(special, specialSize, specialColSize, needs, needsSize,
		specialOrinPrice,
		/*�ܼ�- (һ�����ԭ�� -  һ������Żݼ۸�)
			�ܼ�-(�Żݲ��) = �Żݼ۸�
		*/
		totalNeedOrinPrice - (specialOrinPrice[i] - special[i][specialColSize[i] - 1]));

		for (int j = 0; j < specialColSize[i] - 1; j++) {
			needs[j] += special[i][j];
		}
	}
}

int shoppingOffers(int* price, int priceSize,
	int** special, int specialSize,
	int* specialColSize, int* needs, int needsSize)
{
	if (priceSize <= 0) {
		return 0;
	}

	int specialOrinPrice[specialSize];
	memset(specialOrinPrice, 0, sizeof(specialOrinPrice));

	/*���������Ʒԭʼ�ܼ�*/
	for (int i = 0; i < specialSize; i++) {
		for (int j = 0; j < specialColSize[i] - 1; j++) {
			specialOrinPrice[i] += price[j] * special[i][j];
		}
	}

	int totalNeedOrinPrice = 0;
	for (int i = 0; i < needsSize; i++) {
		totalNeedOrinPrice += price[i] * needs[i];
	}

	g_res = totalNeedOrinPrice;
	backtrack(special, specialSize, specialColSize, needs, needsSize,
		specialOrinPrice, totalNeedOrinPrice);
	return g_res;
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
	// �ڴ�i��j��k�£�������ζ��������s3.substring(0, k+1),����false
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
��̬�滮
״̬����
��dp[i][j]Ϊ�ַ��Ӵ�s1[0, i),s2[0, j)�ܷ����s3[0, i+j)��
ps: s1[0, i) = s1.substring(0, i),������i��

�����ַ�����״̬dp[i]��˵��ͨ��Ҫ���������Ӵ��ĳ���[0, n]����˶���dp[n+1],n���ַ���s�ĳ��ȣ�ͬ���άҲһ����

״̬ת��
����dp[i][j]��״̬��˵��Ҫ�����s3[0,i+j)����s3[0, i+j)���һ���ַ�s3[i+j-1]Ҫô����s1[i-1], Ҫô����s2[j-1],��ˣ�״̬ת�ƣ�

��s1[i-1]==s3[i+j-1]��
dp[i][j] = dp[i-1][j],i > 0
dp[i][j]=dp[i?1][j],i>0

��s2[j-1]==s3[i+j-1]��
dp[i][j] = dp[i][j-1],j >0
dp[i][j]=dp[i][j?1],j>0

״̬��ʼ����dp[0][0] = true����ʾ�������ַ����ܹ����һ�����ַ�����

*/
bool isInterleave(char* s1, char* s2, char* s3) {
    int n = strlen(s1), m = strlen(s2), t = strlen(s3);

    int f[n + 1][m + 1];
    memset(f, 0, sizeof(f));

    if (n + m != t) {
        return false;
    }

    f[0][0] = true;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int p = i + j - 1;
            if (i > 0) {
                f[i][j] |= (f[i - 1][j] && s1[i - 1] == s3[p]);
            }
            if (j > 0) {
                f[i][j] |= (f[i][j - 1] && s2[j - 1] == s3[p]);
            }
        }
    }

    return f[n][m];
}


/*
679. 24 ����Ϸ
���� 4 ��д�� 1 �� 9 ���ֵ��ơ�����Ҫ�ж��Ƿ���ͨ�� *��/��+��-��(��) ������õ� 24��

ʾ�� 1:

����: [4, 1, 8, 7]
���: True
����: (8-4) * (7-1) = 24
ʾ�� 2:

����: [1, 2, 1, 2]
���: False
ע��:

��������� / ��ʾʵ���������������������������� 4 / (1 - 2/3) = 12 ��
ÿ����������������������㡣�ر������ǲ����� - ��ΪһԪ����������磬[1, 1, 1, 1] ��Ϊ����ʱ�����ʽ -1 - 1 - 1 - 1 �ǲ�����ġ�
�㲻�ܽ�����������һ�����磬����Ϊ [1, 2, 1, 2] ʱ������д�� 12 + 12 ��
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

bool backtrack(char** board, bool rowVisited[9][10],
    bool colVisited[9][10], bool boxVisited[3][3][10], int idx, int idy, int boardSize, int* boardColSize)
{
	// �߽�У��, ����Ѿ�������, ����true, ��ʾһ�н���
	if(idy == *boardColSize) {
		idy = 0;
		idx++;
		if(idx == boardSize){
			return true;
		}
	}

	// �ǿ��������, ���������������������һ��λ��
	if(board[idx][idy] == '.') {
		// �������1~9
		for(int num = 1; num <= 9; num++){
			bool canUsed = !(rowVisited[idx][num] || colVisited[idy][num] || boxVisited[idx/3][idy/3][num]);
			if(canUsed){
				rowVisited[idx][num] = true;
				colVisited[idy][num] = true;
				boxVisited[idx/3][idy/3][num] = true;

				board[idx][idy] = (char)('0' + num);
				if(backtrack(board, rowVisited, colVisited, boxVisited, idx, idy + 1, boardSize, boardColSize)){
					return true;
				}

				board[idx][idy] = '.';

				rowVisited[idx][num] = false;
				colVisited[idy][num] = false;
				boxVisited[idx/3][idy/3][num] = false;
			}
		}
	} else {
		return backtrack(board, rowVisited, colVisited, boxVisited, idx, idy + 1, boardSize, boardColSize);
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
	for(int idx = 0; idx < boardSize; idx++){
		for(int idy = 0; idy < *boardColSize; idy++) {
			int num = board[idx][idy] - '0';
			if(1 <= num && num <= 9) {
				rowVisited[idx][num] = true;
				colVisited[idy][num] = true;
				boxVisited[idx / 3][idy / 3][num] = true;
			}
		}
	}

	backtrack(board, rowVisited, colVisited, boxVisited, 0, 0, boardSize, boardColSize);
}

/*
10. ������ʽƥ��
����һ���ַ��� s ��һ���ַ����� p��������ʵ��һ��֧�� '.' �� '*' ��������ʽƥ�䡣

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
bool isMatch(char * s, char * p){
    if (!*p) return !*s;
    bool first_match = *s && (*s == *p || *p == '.');
    if (*(p+1) == '*') {
        return isMatch(s, p+2) || (first_match && isMatch(++s, p));
    }
    else {
        return first_match && isMatch(++s, ++p);
    }
}

int memo[100][100];
bool dfs(char *s,char *p,int s_index,int p_index)
{
    if(s[s_index]=='\0'&&p[p_index]=='\0')return true;//��������������˵��ƥ��ɹ�
    if(p[p_index]=='\0')return false;//���p�ַ���ƥ�䵽���,��sû��,��ƥ�䲻�ɹ�
    if(memo[s_index][p_index]!=-1)return memo[s_index][p_index];//���仯,�жϵ�ǰλ���Ƿ��ѹ�,����ֱ�ӷ��ص�ǰ���,ʡȥ�ظ�����
    bool flag=false;//��ʼ���
    if(p[p_index]=='.')//�����жϸ�λ���Ƿ��ǵ�
    {
        if(p[p_index+1]=='*')//Ȼ���ж���һ���Ƿ���*,�����*,�����ƥ��s�е��������ͬ�ַ�
        {
            for(int i=s_index;i<=strlen(s);i++)//����s��ǰλ�õ�ĩβ,���Ƿ���ƥ��ɹ�
            {
                flag=dfs(s,p,i,p_index+2);//p��.*����s,���Լ�2
                if(flag==true)//�����ƥ��ֱ��ֹͣ
                    break;
            }
        }
        else if(s[s_index]!='\0')//�����һ������*,һ��.ֻ��ƥ��һ���ַ�
        {
            flag=dfs(s,p,s_index+1,p_index+1);//p��.����sһ���ַ�,���Ը���1
        }
    }
    else if(p[p_index+1]=='*')//�����ǰλ������ĸ,��һ����*,*����ƥ��0������s���뵱ǰ��ĸһ�����ַ�
    {
        flag=dfs(s,p,s_index,p_index+2);//��ƥ��0�������,p����ĸ+*����s��0���ַ�
        if(flag==false)//���ƥ�䲻�ɹ�
        {
            for(int i=s_index;i<strlen(s);i++)//����s��ǰλ�õ�ĩβ,���Ƿ���ƥ��ɹ�
            {
                if(s[i]==p[p_index])//��p����ĸ+*�Ƿ�ȼ���s��ǰλ�õ���ĸ,���������һλ�õ�ƥ��
                    flag=dfs(s,p,i+1,p_index+2);
                else//����ֹͣ
                    break;
                if(flag==true)//���ƥ��ɹ�ֹͣ
                    break;
            }
        }
    }
    else if(s[s_index]==p[p_index])//���������������������,������ַ����,�������һλ��
    {
        flag=dfs(s,p,s_index+1,p_index+1);
    }
    //���������Ϊfalse
    memo[s_index][p_index]=flag;//���仯�洢
    return flag;
}
bool isMatch(char * s, char * p){
    memset(memo,-1,sizeof(memo));//��-1Ϊδ���ʹ�
    return dfs(s,p,0,0);
}
/*
"mississippi"
"mis*is*p*."
"ab"
".*"
""
".*"
"a"
".*..a*"
"aab"
"c*a*b"
*/

/*
351. ��׿ϵͳ���ƽ���
���Ƕ�֪����׿�и����ƽ����Ľ��棬��һ�� 3 x 3 �ĵ������Ƴ���������

���������������ֱ�Ϊ ??m �� n������ 1 �� m �� n �� 9����ô����ͳ��һ���ж����ֽ������ƣ���������Ҫ���� m ���㣬������ྭ�������� n ����ġ�



�����˽���ʲô��һ����Ч�İ�׿��������:

ÿһ���������Ʊ������پ��� m ���㡢��ྭ�� n ���㡣
���������ﲻ�����þ����ظ��ĵ㡣
��������������������˳�򾭹��ģ���ô������������ƹ켣֮���Ǿ��Բ��ܿ���κ�δ�������ĵ㡣
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
���ӵ� 1 �͵� 3 ����Ч�ģ���Ϊ��Ȼ�������˵� 2 �����ǵ� 2 �ڸ�������֮ǰ�Ѿ��������ˡ�

��Ч���ƣ�6 - 5 - 4 - 1 - 9 - 2
���ӵ� 1 �͵� 9 ����Ч�ģ���Ϊ��Ȼ�������˰��� 5 �����ǵ� 5 �ڸ�������֮ǰ�Ѿ��������ˡ�
*/
/*
��3�ֳ�������������������Ե���������ĳ������ֱ��Ӧ4��4��1���ظ������
�����������Ƿ���Ի���ȥ������ͨ�����ķ�ʽ��á�
������һЩ�������裬��ô֮ǰ�����ߵĵ�֮����п��ܿ������ˣ�ֻҪ�ж��������ŵ��м���Ѿ��߹��˾Ϳ������ˡ�
�����ж�����֮���Ƿ���Ի���ȥ�ķ������ǣ�
1���Ȳ�����������ֱ���ߣ��������߼��жϣ�2���ж����������м���Ƿ��Ѿ��߹��ˡ�

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

static void dfs(int arr[], int pos, int len, int level, int cnt[]);
int numberOfPatterns(int m, int n)
{
    int cnt[10] = {0};
    int corner[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    dfs(corner, 1, 9, n, cnt);
    int edge[9] = {1, 0, 2, 3, 4, 5, 6, 7, 8};
    dfs(edge, 1, 9, n, cnt);
    for (int i = 1; i <= n; i++)
        cnt[i] *= 4;
    int core[9] = {4, 0, 1, 2, 3, 5, 6, 7, 8};
    dfs(core, 1, 9, n, cnt);

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

static void dfs(int arr[], int pos, int len, int level, int cnt[])
{
    cnt[pos]++;
    if (pos == level)
        return;

    for (int i = pos; i < len; i++) {
        if (!can_walk(arr, pos, arr[pos - 1], arr[i]))
            continue;
        swap(arr, pos, i);
        dfs(arr, pos + 1, len, level, cnt);
        swap(arr, pos, i);
    }
}

/*
306. �ۼ���
�ۼ�����һ���ַ���������������ֿ����γ��ۼ����С�

һ����Ч���ۼ����б������ٰ��� 3 �����������ʼ�����������⣬�ַ����е���������������֮ǰ��������ӵĺ͡�

����һ��ֻ�������� '0'-'9' ���ַ�������дһ���㷨���жϸ��������Ƿ����ۼ�����

˵��: �ۼ���������������� 0 ��ͷ�����Բ������ 1, 2, 03 ���� 1, 02, 3 �������

ʾ�� 1:

����: "112358"
���: true
����: �ۼ�����Ϊ: 1, 1, 2, 3, 5, 8 ��1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
ʾ�� 2:

����: "199100199"
���: true
����: �ۼ�����Ϊ: 1, 99, 100, 199��1 + 99 = 100, 99 + 100 = 199
*/

void dfs(char * num,int index,long *tmp,int tmpSize,bool *re){
    if(tmpSize>=3)
    {
        if(tmp[tmpSize-3]+tmp[tmpSize-2]!=tmp[tmpSize-1])
        {
            return;//����ʱ����������ָ�������3�����������ۼ���Ҫ�󣬲��ü������ң�ֱ�ӷ���
        }
    }
    if(index==strlen(num))//�ù����ַ������������ַ�
    {
        if(tmpSize<3) return;//ֻ���������3�����֣��϶�Ϊ�٣�����
        int i=0;
        for(i=0;i<tmpSize-2;i++)//������ʱ��������Ԫ���Ƿ������ۼ���Ҫ��
        {
            if(tmp[i]+tmp[i+1]!=tmp[i+2])
            {
                break;
            }
        }
        if(i==tmpSize-2)//������������������ֵ��Ϊ��
        {
            *re=true;
        }
        return;
    }
    if(num[index]=='0')//���ڲ�����ǰ���㣬�����ǰ����Ϊ0����ô����ȡ������ֻ��Ϊ0
    {
        tmp[tmpSize]=0;
        dfs(num,index+1,tmp,tmpSize+1,re);
        return;
    }
    int i=0,cnt=0;
    long sum=0;
    for(i=index;i<strlen(num);i++)//һ�����
    {
        sum=sum*10+num[i]-'0';
        cnt++;
        //���������Ϊ�˷�ֹ���ֹ������long���ͣ����������뵽
        //���ĳ������ȡ�˴���strlen(num)/2���ȵ��ַ����Ͳ�����tmp[i]+tmp[i+1]=tmp[i+2]�������
        //�������ü���cnt����ֹ�����������
        if(2*cnt>strlen(num)) break;
        tmp[tmpSize]=sum;
        dfs(num,i+1,tmp,tmpSize+1,re);
    }
}
bool isAdditiveNumber(char * num){
    if(strlen(num)<3) return false;
    bool re=false;
    int size=0;
    long tmp[strlen(num)];//��ʱ���ȡ����n���ַ���ɵ�����
    memset(tmp,0,sizeof(tmp));
    dfs(num,0,tmp,0,&re);
    return re;
}

/*
90. �Ӽ� II
����һ�����ܰ����ظ�Ԫ�ص��������� nums�����ظ��������п��ܵ��Ӽ����ݼ�����

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
int cmp_int(const void *a, const void *b)
{
	return *((int *)a) > *((int *)b);
}

void backtrack(int* nums, int numsSize, int* returnSize, int** returnColumnSizes,
	int **res, int *path, int pathSize, int cidx)
{
	res[*returnSize] = (int *)calloc(pathSize, sizeof(int));
	memcpy(res[*returnSize], path, sizeof(int) * pathSize);
	(*returnColumnSizes)[*returnSize] = pathSize;
	(*returnSize)++;

	for (int i = cidx; i < numsSize; i++) {
		if (i > cidx && nums[i] == nums[i - 1]) {
			continue;
		}

		path[pathSize] = nums[i];
		backtrack(nums, numsSize, returnSize, returnColumnSizes, res, path, pathSize + 1, i + 1);
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

	backtrack(nums, numsSize, returnSize, returnColumnSizes, res, path, 0, 0);
	return res;
}

/*
79. ��������
����һ����ά�����һ�����ʣ��ҳ��õ����Ƿ�����������С�

���ʱ��밴����ĸ˳��ͨ�����ڵĵ�Ԫ���ڵ���ĸ���ɣ����С����ڡ���Ԫ������Щˮƽ���ڻ�ֱ���ڵĵ�Ԫ��ͬһ����Ԫ���ڵ���ĸ�������ظ�ʹ�á�



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
#define DIR 4
int direction[DIR][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int dfs(char** board, int row, int col, int i, int j, int** visted, char * word,int deepth)
{
    if (deepth == strlen(word)) {
        return 1;
    }
    if (i < 0 || i >= row || j < 0 || j >= col) {
        return 0;
    }
    if (visted[i][j] || board[i][j] != word[deepth]) {
        return 0;
    }
    visted[i][j] = 1;
    for (int k = 0; k < DIR; k++) {
        int newx = i + direction[k][0];
        int newy = j + direction[k][1];
        if (dfs(board, row, col, newx, newy, visted, word, deepth + 1)) {
            return 1;
        }
    }
    visted[i][j] = 0;
    return 0;
}
bool exist(char** board, int boardSize, int* boardColSize, char * word)
{
    int m = boardSize;
    int n = *boardColSize;
    int **visted = (int **)calloc(m,sizeof(int *));
    for (int i = 0; i < m; i++) {
        visted[i] = (int *)calloc(n, sizeof(int));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dfs(board, m, n, i, j, visted, word,0)) {
                return true;
            }
        }
    }
    return false;
}

bool _exist(char **board, int row, int col, char *word, int y, int x)
{
    if (*word == '\0')
        return true;
    if (y < 0 || y >= row || x < 0 || x >= col || *word != board[y][x])
        return false;
    board[y][x] = '\0';
    bool result = _exist(board, row, col, word + 1, y, x - 1) ||
                  _exist(board, row, col, word + 1, y - 1, x) ||
                  _exist(board, row, col, word + 1, y, x + 1) ||
                  _exist(board, row, col, word + 1, y + 1, x);
    board[y][x] = *word;
    return result;
}
bool exist(char **board, int boardSize, int *boardColSize, char *word)
{
    for (int y = 0; y < boardSize; y++)
        for (int x = 0; x < boardColSize[0]; x++)
            if (board[y][x] == word[0] && _exist(board, boardSize, boardColSize[0], word, y, x))
                return true;
    return false;
}

int flag = false;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool dfs(char ** board, int m, int n, char * word, int len, int index, int x, int y)
{
    if(index == len) {
        return true;
    }
    if(x < 0 || x >= m || y < 0 || y >= n || board[x][y] != word[index]){
        return false;
    }
    char tmp = board[x][y];
    board[x][y] = '0';
    if(dfs(board, m, n, word, len, index + 1, x + 1, y) ||
       dfs(board, m, n, word, len, index + 1, x - 1, y) ||
       dfs(board, m, n, word, len, index + 1, x, y + 1) ||
       dfs(board, m, n, word, len, index + 1, x, y - 1)) {
                return true;
    }
    board[x][y] = tmp;
    return false;
}


bool exist(char** board, int boardSize, int* boardColSize, char * word){
    flag = false;
    int len1 = strlen(word);
    int m = boardSize;
    int n = boardColSize[0];

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(word[0] == board[i][j]){
                if(dfs(board, m, n, word, len1, 0, i, j))
                    return true;
            }
        }

    }

    return false;
}

/*
357. �������λ����ͬ�����ָ���
����һ���Ǹ����� n�������λ���ֶ���ͬ������ x �ĸ��������� 0 �� x < 10n ��

ʾ��:

����: 2
���: 91
����: ��ӦΪ��ȥ 11,22,33,44,55,66,77,88,99 �⣬�� [0,100) �����ڵ��������֡�
*/
int countNumbersWithUniqueDigits(int n){
        if (n == 0) return 1;
        int res = 10, k = 9, temp = 9;
        for (int i = 2; i <= fmin(n, 10); ++i){
            temp *= k;
            k--;
            res += temp;
        }
        return res;
}

/*
��Ŀ����
���� (288)
���(262)
�ύ��¼
89. ���ױ���
���ױ�����һ������������ϵͳ���ڸ�ϵͳ�У�������������ֵ����һ��λ���Ĳ��졣

����һ�����������λ���ķǸ����� n����ӡ����ױ������С���ʹ�ж����ͬ�𰸣���Ҳֻ��Ҫ��������һ�֡�

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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// ������
unsigned pow2(unsigned n)
{
    unsigned ret = 1;
    unsigned mod = 2;

    for (; n; n >>= 1)
    {
        if (n & 0x01)
            ret *= mod;
        mod = mod * mod;
    }

    return ret;
}

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
    *returnSize = pow2(n);

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

int str2int(char *str, int n){
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum * 2 + (str[i] - '0');
    }
    return sum;
}

void dfs(int n, int num, int *returnSize, int *res, char *str, int *visited)
{
    if (num == (*returnSize)) { // ȫ���ҵ���
        return;
    }

    for (int i = 0; i < n; i++) {
        str[i] = (str[i] == '0' ? '1' : '0');
        if (visited[str2int(str, n)] == 0) {
            visited[str2int(str, n)] = 1;
            res[*returnSize] = str2int(str, n);
            (*returnSize)++;
            dfs(n, num, returnSize, res, str, visited);
        } else {
            str[i] = (str[i] == '0' ? '1' : '0');
        }
    }
}

int* grayCode(int n, int* returnSize){
    int num = 1 << n;
    int *res = (int *)malloc(num * sizeof(int));

    char *str = (char *)calloc(n + 1, sizeof(char));
    for (int i = 0; i < n; i++) {
        str[i] = '0';
    }
    int *visited = (int *)calloc(num, sizeof(int));


    *returnSize = 1;
    res[0] = 0;
    visited[str2int(str, n)] = 1;
    dfs(n, num, returnSize, res, str, visited);
    return res;
}

/*
131. �ָ���Ĵ�
����һ���ַ��� s���� s �ָ��һЩ�Ӵ���ʹÿ���Ӵ����ǻ��Ĵ���

���� s ���п��ܵķָ����

ʾ��:

����: "aab"
���:
[
  ["aa","b"],
  ["a","a","b"]
]
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
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

void dfs(char *s, int len, int pos, char **subs, int subSize, int *retColSize) {
    if (pos == len) {
            // dump(subs, subSize);
        copyToAns(subs, subSize, retColSize);
        return;
    }
    for (int i = pos; i < len; ++i) {
        if (isPalindrome(s, pos, i)) {
            subs[subSize] = substr(s, pos, i);
            dfs(s, len, i + 1, subs, subSize + 1, retColSize);
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
    dfs(s, strlen(s), 0, tmpSubs, 0, *returnColumnSizes);
    *returnSize = g_ansSize;

    free(tmpSubs);
    return g_ans;
}