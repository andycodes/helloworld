/*
���ݷ��Ļ���˼�룺

����������⣬��������Ľ�ռ䣻
ȷ�����������Ľ�ռ�ṹ��
��������ȷ�ʽ������ռ䣬
���������������ü�֦����������Ч������


���ݷ���������Ľ⣬
ʹ�õ���DFS�����������������
��DFS�Ĺ����з��ֲ�������Ľ⣬
��ô�Ϳ�ʼ���ݵ���һ�������һ���ڵ㡣
DFS�Ǳ������������ռ䣬
�������Ƿ�������Ľ⡣
���Ը����û��ݷ���DFS��һ��Ӧ�ã�
DFS������һ�ֹ��ߡ�

result = []
def backtrack(·��, ѡ���б�):
    if ���㡸����������:
        result.add(��·����)
        return

    for ѡ�� in ��ѡ���б�:  (����N����)
        #��ѡ��
	 ����ѡ���ѡ���б��Ƴ�
	 ��·����.add(ѡ��)
        backtrack(·��, ѡ���б�)
        #����ѡ��
        ��·����.remove(ѡ��)
    	 ����ѡ���ټ���ѡ���б�

*/


/*ȫ����*/
void backtrack(int source[], int start, int end, int *resSize, int **res)
{
	// �ҵ�һ������
	if (start == end) {
		res[*resSize] = (int *)calloc (sizeof(int)*end);
		memcpy(res[*resSize], source, sizeof(int) * end);
		(*resSize)++;
	} else {
		// û������һ�����У��������������һ��Ԫ��
		for (int i = start; i < end; i++) {
			if (start != i) {// ��������
				swap(source[start], source[i]);
			}

			// �ݹ�����ʣ��Ĵ�start+1��end��Ԫ��
			backtrack(source, start + 1, end, resSize, res);

			if (start != i) {// ����ʱ��ԭ
				swap(source[start], source[i]);
			}
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be calloc ed, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
	int **res = (int **)calloc (17000 * sizeof(int *));
	int resSize = 0;

	backtrack(nums, 0, numsSize, &resSize, res);

	*returnSize = resSize;
	*returnColumnSizes = (int *)calloc (sizeof(int) * 17000);
	for (int i = 0; i < resSize; i++) {
		(*returnColumnSizes)[i] = numsSize;
	}

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

void backtrack(int num, char ** res, int* returnSize, int curH, int curM, int pos)
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
1219. �ƽ��
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

int backtrack(int ** grid, int gridSize, int* gridColSize,int i, int j)
{
	if (i < 0 || i >= gridSize || j < 0 || j >= gridColSize[0] || grid[i][j] == 0)
		return 0;

	int v = grid[i][j];
	grid[i][j] = 0;
	int ret = 0;

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};/*��������*/
	for(int k = 0; k < 4; k++) {
		int nX = i + d[k][0];
		int nY = j + d[k][1];
		ret = fmax(ret, v + backtrack(grid,gridSize,gridColSize,nX,nY));
	}

	grid[i][j] = v;

	return ret;
}


int getMaximumGold(int** grid, int gridSize, int* gridColSize){
    if (grid == NULL || gridSize < 0 || gridColSize == NULL)
        return 0;

    int sumMax = 0;

//�󹤿��Դ������� ����һ�� �лƽ�ĵ�Ԫ�����������ֹͣ��
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            sumMax = fmax(sumMax, backtrack(grid, gridSize, gridColSize, i, j));
        }
    }

    return sumMax;
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

���
��һʱ���뵽���ݣ���Ϊ������ȫ���Ľ⣬���涼��ʹ�û���

����
��ʼ���ʵ�phone=\{"2":["a","b","c"],\cdots\}phone={"2":["a","b","c"],?}����ʼ��res=[]res=[]

���У����ַ���Ϊ�գ�����[][]

������ݺ���helper(s,tmp)helper(s,tmp)��ss��ʾ��ƥ����ַ�����tmptmp��ʾ֮ǰƥ��Ľ��

��s==""s==""����ʾƥ����ϣ���ʱ��tmptmp����resres��������
����s[0]s[0]��Ӧ�����п��ܵ���ĸcc��
ִ��helper(s[i+1,...],tmp+c)helper(s[i+1,...],tmp+c)
ִ��helper(digits,"")helper(digits,"")

����resres


Ҳ����ѡ��BFS
����һ�����ζ��еĸо�����߽����ұ߳���
ѭ��һȦ��ʼ��һ�֣�
������Ŀ�и���'23'��
��һ����'2'�����б�ɡ�c,b,a��
Ȼ����'3'�������Ӷ�β��Ԫ�ء�a����
�����Ԫ�صĳ����ǲ��ǵ���2��������ǣ�
�ͷֱ��3��Ӧ����ĸ��d,e,f���ֱ�͵����ġ�a��ƴ������
�Ӷ��ײ��ȥ������������һȦ��
���б���ˡ�cf,ce,cd,bf,be,bd,af,ae,ad��

����������'234'������һ�־ͼ�����'4'��
������β��Ԫ�ء�ad�����������Ƿ����3��
������ǣ��Ͱ�4��Ӧ�ġ�h,i,g���ֱ�͵����ġ�ad����
ƴ�������Ӷ������ز塣

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

void backtrack(char* digits, int srcSize, int* returnSize,
    char* tmp, int *tmpIdx, int start, char** res)
{
    if (start == srcSize) {
        res[*returnSize] = (char*)calloc(1024, sizeof(char));
        //strcpy_s(res[*returnSize],1024, tmp);
        strcpy(res[*returnSize], tmp);
        (*returnSize)++;
        return;
    }

    int leSize = nums[digits[start] - '2'];
    for (int i = 0; i < leSize; i++) { /*ÿһ��leSize��case */
        tmp[*tmpIdx] = letter[digits[start] - '2'][i];
        (*tmpIdx)++;/*ǰ��һ��*/
        backtrack(digits, srcSize, returnSize, tmp, tmpIdx, start + 1, res);
        (*tmpIdx)--;/*���ݷ���һ��*/
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
    int tmpIdx = 0;
    backtrack(digits, strSize, returnSize, tmp, &tmpIdx, 0, res);

    return res;
}
