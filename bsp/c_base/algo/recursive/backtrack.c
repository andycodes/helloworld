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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int count = 0;                              //�洢����count
//char **arr = NULL;
void swap(char* s, int i, int j){           //����һ����������
    char tmp = s[j];
    s[j] = s[i];
    s[i] = tmp;
}

bool judge(char* s, int start, int end){    //����ĸΪabbʱ��ȫ������ܳ����ظ��������Ҫȥ��
    int i;
    for (i = start; i < end; i++){      //��ǰ�����ֱַ��벻�����������ֽ�����1����1����2����2��
        if (s[i] == s[end]){
            return true;
        }
    }
    return false;
}

void perm(char* s, int p, char** arr, int len){     //����ȫ����
    if (p == len){                                  //����ֹͣ��������pָ���ַ�����ĩβʱ��ֹ
        s[len] = '\0';                              //����ǰs��ӽ�ֹ��'\0'
        memcpy(arr[count], s, len);                 //��s��ֵ����ά����arr
        count++;                                    //����������1
        return;
    }
    int i;
    for (i = p; i < len; i++){                      //���ν�ÿ�������ڵ�һλ
        if (judge(s, p, i)){                        //�ж��Ƿ��ظ�
            continue;
        }
        swap(s, p, i);                              //�ѱ���ָ������ŵ���һλ
        perm(s, p + 1, arr, len);                   //��ʣ�µ�������ȫ����
        swap(s, p, i);                              //�ٰ�ԭ���ĵ�һλ��������
    }
}

char** permutation(char* s, int* returnSize){
    int total = 1;                                  //total�洢N������ȫ�������ΪN!
    int len = strlen(s);
    int i;
    count = 0;
    for (i = 2; i <= len; i++){
        total *= i;
    }
    char** arr = (char**)malloc(sizeof(char*) * total);     //����һ���ܹ��洢N!�����ڴ�
    for (i = 0; i < total; i++){
        arr[i] = (char*)calloc(len + 1, sizeof(char));      //����ÿһ�д洢���ڴ���
    }
    perm(s, 0, arr, len);                           //����ȫ����
    * returnSize = count;
    return arr;
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
int curH, int curM, int pos)
{
	if (num == 0) {
		res[*returnSize] = (char *)calloc(10, sizeof(char *));
		sprintf(res[*returnSize] , "%d:%02d", curH, curM);
		(*returnSize)++;
		return;
	}
/*
��ʵ�����Ŀ���Թ����ж��� n��1�Ķ�������ϡ�
ת��Ϊ�ַ������ɡ�
���ｫ 0 - 9������һ��
0 - 5 �� ����
6 - 9 ��Сʱ���㡣
*/
	for (int i = pos; i < 10; i++) {
		if (i <= 5) {
			curM += (1 << i);
			if (curM > 59) {
				curM -= (1 << i);
				continue;
			}
		} else {
			curH += (1 << i - 6);
			if (curH > 11)
				return;
		}

		backtrack(num -1, res,  returnSize, curH,  curM, i + 1);

		if (i <= 5)
			curM -= (1 << i);
		else
			curH -= (1 << i - 6);
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
�����и�����������һ����������Ͻǣ����� r �� c �С�������ֻ�����»������ƶ����������ߵ�һЩ����ֹ���������ϰ�������һ���㷨��Ѱ�һ����˴����Ͻ��ƶ������½ǵ�·����

�����е��ϰ���Ϳ�λ�÷ֱ��� 1 �� 0 ����ʾ��
����һ�����е�·����·���ɾ�����������кź��к���ɡ����Ͻ�Ϊ 0 �� 0 �С�
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

bool backtrack(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize, int row, int col,
int **ret, int *returnSize,  bool visited[][100], int** returnColumnSizes)
{
	if(row >= obstacleGridSize || col >= obstacleGridColSize[row] || obstacleGrid[row][col] == 1 || visited[row][col])
		return false;

	visited[row][col] = 1;
	ret[*returnSize] = (int *)calloc(2, sizeof(int));
	ret[*returnSize][0] = row;
	ret[*returnSize][1] = col;
	(*returnColumnSizes)[*returnSize] = 2;
	(*returnSize)++;

	if(row == (obstacleGridSize - 1) && col == (obstacleGridColSize[row] - 1)) {
		return true;
	}

	if (backtrack(obstacleGrid, obstacleGridSize, obstacleGridColSize, row, col + 1, ret, returnSize, visited, returnColumnSizes) ||
		backtrack(obstacleGrid, obstacleGridSize, obstacleGridColSize, row + 1, col, ret, returnSize, visited, returnColumnSizes)) {
		return true;
	}

	if (ret[*returnSize] != NULL) {
		free(ret[*returnSize]);
		ret[*returnSize] = NULL;

	}

	(*returnSize)--;

	return false;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathWithObstacles(int** obstacleGrid, int obstacleGridSize,
int* obstacleGridColSize, int* returnSize, int** returnColumnSizes){
	*returnSize = 0;
	int **ret = calloc(200, sizeof(int *));
	bool visited[100][100];
	memset(visited, 0, sizeof(visited));
	*returnColumnSizes = calloc(200, sizeof(int));
	bool  arrived = backtrack(obstacleGrid, obstacleGridSize, obstacleGridColSize,
	0, 0, ret, returnSize, visited, returnColumnSizes);
	if(arrived == false) {
		*returnSize = 0;
	}

	return ret;
}

/*
332. ���°����г�
�Ѷ��е�102
����һ����Ʊ���ַ�����ά���� [from, to]���������е�������Ա�ֱ��ʾ�ɻ������ͽ���Ļ����ص㣬�Ը��г̽������¹滮����������Щ��Ʊ������һ����JFK������Ϲ��ʻ��������������������Ը��г̱���� JFK ������
˵��:
1.	������ڶ�����Ч���г̣�����԰��ַ���Ȼ���򷵻���С���г���ϡ����磬�г� ["JFK", "LGA"] �� ["JFK", "LGB"] ��Ⱦ͸�С���������ǰ
2.	���еĻ�������������д��ĸ��ʾ���������룩��
3.	�ٶ����л�Ʊ���ٴ���һ�ֺ�����г̡�
ʾ�� 1:
����: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
���: ["JFK", "MUC", "LHR", "SFO", "SJC"]
ʾ�� 2:
����: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
���: ["JFK","ATL","JFK","SFO","ATL","SFO"]
����: ��һ����Ч���г��� ["JFK","SFO","ATL","JFK","ATL","SFO"]����������Ȼ������������

*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define STR_LEN 4
int g_flag[300];
 void backtrack(char *** tickets, int ticketsSize, char *** res, char *start, int *count)
 {  //�����ɻ�Ʊ
    for (int i = 0; i < ticketsSize; i++) {
        if (g_flag[i] == 0 && strcmp(start, tickets[i][0]) == 0) {//�ҵ�Ŀ�ĵ�
            (*count)++;
            //printf("#####%d %s\n", *count, start);
            g_flag[i] = *count;
            char *newStart = tickets[i][1];

            (*res)[(*count)] = (char*)calloc(STR_LEN, sizeof(char));
            //��Ŀ�ĵؼӵ����������
            strncpy((*res)[(*count)], newStart, STR_LEN);
            //�����¸�Ŀ�ĵ�
            backtrack(tickets, ticketsSize, res, newStart, count);
            //������������ˣ��򷵻ء�
            if (*count  == ticketsSize ) {
                return;
            }
            //�����������
            (*count)--;
            g_flag[i] = 0;
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

char ** findItinerary(char *** tickets, int ticketsSize, int* ticketsColSize, int* returnSize){
    *returnSize = ticketsSize + 1; //
    char **res = (char**)calloc(*returnSize, sizeof(char*));
    memset(g_flag, 0, sizeof(g_flag));
    //���� ��Ȼ��
    qsort(tickets, ticketsSize, sizeof(tickets[0]), cmp);

    char *start= "JFK";
    int count = 0;

    backtrack(tickets, ticketsSize, &res, start, &count);

    res[0] = (char*)calloc(STR_LEN, sizeof(char));
    strncpy(res[0], start, STR_LEN);

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
		specialOrinPrice, totalNeedOrinPrice - specialOrinPrice[i] +
		special[i][specialColSize[i] - 1]);

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
	backtrack(special, specialSize, specialColSize, needs, needsSize, specialOrinPrice, totalNeedOrinPrice);
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
�����仯�Ļ��ݴӱ������ݿ�֪����i��j��kһ��������£�����ֵһ�����ɴ����ǿ��Խ�i��j��k������ֵ��meom[i][j][k]��¼�������������ٴ�������i��j��kʱ��ֱ�ӷ��ء���Ȼ��i��jһ��ʱ��kһ������Ϊk = i + j����ˣ����Խ�״̬��������ά����meom[i][j]�����Ƕ������������ݽ��и��죬�ڻ��ݷ���false�ĵط���meom[i][j]��¼�������ڷ���true�ĵط����ü�¼����Ϊһ������true�����ݾͻ�һֱ���أ�ֱ��������ڡ����ߣ�antione���ӣ�https://leetcode-cn.com/problems/interleaving-string/solution/you-bao-li-hui-su-dao-ji-yi-hua-fen-xiang-wo-de-do/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
bool helper(char *s1, char * s2, char * s3, int i, int j, int k, int size1, int size2, int dp[size1][size2])
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

        if(i < strlen(s1)){
            // ����ǰs1��iλ�õ��ַ���s3��kλ���ַ���ȣ�������һ���ַ���
            // �����»��ݣ������ݷ���true�򷵻ص����true�ʼһ��
            // ���ɸú����ڵڶ��д��뷵�صģ�����ʾs3�ܹ���������ɣ�ֱ�ӷ���true
            if(s1[i] == s3[k] &&
            helper(s1, s2, s3, i+1, j, k+1, size1, size2, dp))
                return true;
        }

        if(j < strlen(s2)){
            if(s2[j] == s3[k] &&
            helper(s1, s2, s3, i, j+1, k+1,  size1, size2, dp))
                return true;
        }


		dp[i][j] = false;
        // �ڴ�i��j��k�£�������ζ��������s3.substring(0, k+1),����false
        return false;
    }


bool isInterleave(char* s1, char* s2, char* s3) {
        // ��Ŀû����ȷ˵��s123�Ƿ�ΪNULL����Ҫ��NULL������ֱ��������ڿ��ַ�
        // ��s1Ϊ�գ������������ָ���쳣Ҳ������뵽���㵱��
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
        return helper(s1, s2, s3, 0, 0, 0, len1, len2, dp);
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
#define DEBUG_PRINTF // printf

void debugPrintf(double* nums, int size)
{
    DEBUG_PRINTF("calc[%d]:", size);
    for (int k = 0; k < size; k++) {
        DEBUG_PRINTF("%lf ", nums[k]);
    }

    DEBUG_PRINTF("\n");
}

double Add(double a, double b) { DEBUG_PRINTF("%lf+%lf=%lf\n", a, b, a + b); return a + b; };
double Sub(double a, double b) { DEBUG_PRINTF("%lf-%lf=%lf\n", a, b, a - b);  return a - b; };
double Mul(double a, double b) { DEBUG_PRINTF("%lf*%lf=%lf\n", a, b, a * b);  return a * b; };
double Div(double a, double b) { DEBUG_PRINTF("%lf/%lf=%lf\n", a, b, a / b);  return a / b; };

typedef struct {
    bool isSwap;    // �Ƿ񽻻�
    ClacFunc func;  // ����
}CLAC;

#define CLAC_TYPE 4
#define NUM_SIZE 4
static CLAC g_clacFunc[CLAC_TYPE] = {
    {0, Add},
    {1, Sub},
    {0, Mul},
    {1, Div}
};

bool calc(double* nums, int size){
    debugPrintf(nums, size);
    if (size == 1) {
        return (fabs((nums[0] - 24)) <= 1e-6);
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            double result[3] = {0};
            int cnt = 0;

            for (int k = 0; k < size; k++) {
                if (k != i && k != j) {
                    result[cnt++] = nums[k];
                }
            }

            for (int k = 0; k < CLAC_TYPE; k++) {
                int calcCnt = cnt + 1;
                bool isOK = false;
                if (g_clacFunc[k].isSwap) {
                    result[cnt] = g_clacFunc[k].func(nums[j], nums[i]);
                    isOK = calc(result, calcCnt);
                    if (isOK) {
                        return true;
                    }
                }

                result[cnt] = g_clacFunc[k].func(nums[i], nums[j]);
                isOK = calc(result, calcCnt);
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
    double tmpNums[NUM_SIZE] = {0};

    for (int i = 0; i < numsSize; i++) {
        tmpNums[i] = nums[i];
    }

    return calc(tmpNums, numsSize);
}

typedef double (*ClacFunc) (double a, double b);
#define DEBUG_PRINTF  // printf

void debugPrintf(double* nums, int size)
{
    DEBUG_PRINTF("calc[%d]:", size);
    for (int k = 0; k < size; k++) {
        DEBUG_PRINTF("%lf ", nums[k]);
    }

    DEBUG_PRINTF("\n");
}

double Add(double a, double b) { DEBUG_PRINTF("%lf+%lf=%lf\n", a, b, a + b); return a + b; };
double Sub(double a, double b) { DEBUG_PRINTF("%lf-%lf=%lf\n", a, b, a - b);  return a - b; };
double Mul(double a, double b) { DEBUG_PRINTF("%lf*%lf=%lf\n", a, b, a * b);  return a * b; };
double Div(double a, double b) { DEBUG_PRINTF("%lf/%lf=%lf\n", a, b, a / b);  return a / b; };

typedef struct {
    bool isSwap;    // �Ƿ񽻻�
    ClacFunc func;  // ����
}CLAC;

#define CLAC_TYPE 4
#define NUM_SIZE 4
static CLAC g_clacFunc[CLAC_TYPE] = {
    {0, Add},
    {1, Sub},
    {0, Mul},
    {1, Div}
};

bool calc(double* nums, int size){
    debugPrintf(nums, size);
    if (size == 1) {
       return (fabs((nums[0] - 24)) <= 1e-6);
    }
    //���ĸ���ʱ�򣬵�һ��ѡ������ʱ��4*3�֣�֮��ѡ�����Ϊ12*4=48��
    //Ȼ��3��ѡ����Ϊ3*2�֣�֮��ѡ�������6*4 = 24��
    //���2��ѡ�������2*4�֣����Ⱥ�˳��֮�֣�
    //����+��*���㽻����
    //��ѡ������
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            double result[3] = {0};
            int cnt = 0;
            //�������i��j  ��Ϊi��j����λ�õ���������Ҫ���м���
            for (int k = 0; k < size; k++) {
                if (k != i && k != j) {
                    result[cnt++] = nums[k]; // ��ʣ�µĴ�������ļ�λ��
                }
            }
            //�������4������
            for (int k = 0; k < CLAC_TYPE; k++) {
                int calcCnt = cnt + 1;
                bool isOK = false;
                //#1�����㽻���� - / ���� #2������ a - b ֮�󻹵���������¼��� b - a
                if (g_clacFunc[k].isSwap) {
                    result[cnt] = g_clacFunc[k].func(nums[j], nums[i]);
                    isOK = calc(result, calcCnt); // �ݹ�ʱ�Ĳ������������� result���������δʣ�µ������µõ��Ľ��
                    if (isOK) {
                        return true;
                    }
                }
                //#2 ȫ������һ��
                result[cnt] = g_clacFunc[k].func(nums[i], nums[j]);
                isOK = calc(result, calcCnt);
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
    double tmpNums[NUM_SIZE] = {0};

    for (int i = 0; i < numsSize; i++) {
        tmpNums[i] = nums[i];
    }

    return calc(tmpNums, numsSize);
}

/*
488. ������Ϸ
�Ѷ�����54
����һ��������Ϸ������������һ������ɫ�к�ɫ(R)����ɫ(Y)����ɫ(B)����ɫ(G)�����а�ɫ(W)�� ����������Ҳ�м�����
ÿһ�Σ�����Դ��������ѡһ����Ȼ����������뵽һ�����е�ĳ��λ���ϣ���������ˣ����Ҷˣ������ţ�����г���������������������ɫ��ͬ���������Ļ����Ͱ������Ƴ������ظ���һ����ֱ���������е��򶼱��Ƴ���
�ҵ����벢�����Ƴ���������������������ٵ���������������Ƴ��������е������ -1 ��
ʾ��:
����: "WRRBBW", "RB"
���: -1
����: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW �������߱�ע���������Ѿ����꣬���ϻ�ʣ�������޷�����������-1��

����: "WWRRBBWW", "WRBRW"
���: 2
����: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty


*/

int dfs(char * board, int *map)
{
	int blen = strlen(board);
	if (board == NULL || board[0] == '\0' ||blen <= 0) {
		return 0;
	}

	int i = 0;
	int ans = INT_MAX;
	while(i < blen) {
		int j = i;
		while( j < blen && (board[i] == board[j])) j++;
		int cnt = fmax(0, 3 - (j - i));
		if (map[board[i] - 'A'] >= cnt) {
			char newBoard[blen];
			memset(newBoard, 0, sizeof(newBoard));
			strncpy(newBoard, board, i);
			strcat(newBoard, board + j);
			map[board[i] - 'A'] -= cnt;
			int res = dfs(newBoard, map);
			if (res >= 0) ans = fmin(ans, res + cnt);
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

	return dfs(board, map);
}
