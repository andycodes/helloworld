/*
回溯法的基本思想：

针对所给问题，定义问题的解空间；
确定易于搜索的解空间结构；
以深度优先方式搜索解空间，
并在搜索过程中用剪枝函数避免无效搜索。


回溯法是求问题的解，
使用的是DFS（深度优先搜索）。
在DFS的过程中发现不是问题的解，
那么就开始回溯到上一层或者上一个节点。
DFS是遍历整个搜索空间，
而不管是否是问题的解。
所以更觉得回溯法是DFS的一种应用，
DFS更像是一种工具。

result = []
def backtrack(路径, 选择列表):
    if 满足「结束条件」:
        result.add(「路径」)
        return

    for 选择 in 「选择列表」:  (类似N叉树)
        #做选择
	 将该选择从选择列表移除
	 「路径」.add(选择)
        backtrack(路径, 选择列表)
        #撤销选择
        「路径」.remove(选择)
    	 将该选择再加入选择列表

*/


/*全排列*/
void backtrack(int source[], int start, int end, int *resSize, int **res)
{
	// 找到一个排列
	if (start == end) {
		res[*resSize] = (int *)calloc (sizeof(int)*end);
		memcpy(res[*resSize], source, sizeof(int) * end);
		(*resSize)++;
	} else {
		// 没有找完一个排列，则继续往下找下一个元素
		for (int i = start; i < end; i++) {
			if (start != i) {// 两两交换
				swap(source[start], source[i]);
			}

			// 递归排列剩余的从start+1到end的元素
			backtrack(source, start + 1, end, resSize, res);

			if (start != i) {// 回溯时还原
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
401. 二进制手表
二进制手表顶部有 4 个 LED 代表小时（0-11），
底部的 6 个 LED 代表分钟（0-59）。
每个 LED 代表一个 0 或 1，最低位在右侧。

例如，上面的二进制手表读取 "3:25"。

给定一个非负整数 n 代表当前 LED 亮着的数量，
返回所有可能的时间。

案例:

输入: n = 1
返回: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
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
其实这个题目可以归于有多少 n个1的二进制组合。
转换为字符串即可。
这里将 0 - 9，划分一下
0 - 5 是 分钟
6 - 9 是小时计算。
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
1219. 黄金矿工
你要开发一座金矿，地质勘测学家已经探明了
这座金矿中的资源分布，并用大小为 m * n 的网格
grid 进行了标注。每个单元格中的整数就表示这一
单元格中的黄金数量；如果该单元格是空的，那么就是 0。

为了使收益最大化，矿工需要按以下规则来开采黄金：

每当矿工进入一个单元，就会收集该单元格中的所有黄金。
矿工每次可以从当前位置向上下左右四个方向走。
每个单元格只能被开采（进入）一次。
不得开采（进入）黄金数目为 0 的单元格。
矿工可以从网格中 任意一个 有黄金的单元格出发或者是停止。


示例 1：

输入：grid = [[0,6,0],[5,8,7],[0,9,0]]
输出：24
解释：
[[0,6,0],
 [5,8,7],
 [0,9,0]]
一种收集最多黄金的路线是：9 -> 8 -> 7。

*/

int backtrack(int ** grid, int gridSize, int* gridColSize,int i, int j)
{
	if (i < 0 || i >= gridSize || j < 0 || j >= gridColSize[0] || grid[i][j] == 0)
		return 0;

	int v = grid[i][j];
	grid[i][j] = 0;
	int ret = 0;

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};/*上右下左*/
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

//矿工可以从网格中 任意一个 有黄金的单元格出发或者是停止。
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            sumMax = fmax(sumMax, backtrack(grid, gridSize, gridColSize, i, j));
        }
    }

    return sumMax;
}


/*
17. 电话号码的字母组合
给定一个仅包含数字 2-9 的字符串，
返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。
注意 1 不对应任何字母。



示例:

输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

题解
第一时间想到回溯，因为这种找全部的解，常规都是使用回溯

回溯
初始化词典phone=\{"2":["a","b","c"],\cdots\}phone={"2":["a","b","c"],?}，初始化res=[]res=[]

特判，若字符串为空，返回[][]

定义回溯函数helper(s,tmp)helper(s,tmp)：ss表示待匹配的字符串，tmptmp表示之前匹配的结果

若s==""s==""：表示匹配完毕，此时将tmptmp加入resres，并返回
遍历s[0]s[0]对应的所有可能的字母cc：
执行helper(s[i+1,...],tmp+c)helper(s[i+1,...],tmp+c)
执行helper(digits,"")helper(digits,"")

返回resres


也可以选择BFS
就是一个环形队列的感觉，左边进，右边出，
循环一圈开始下一轮：
比如题目中给的'23'：
第一次跑'2'，队列变成【c,b,a】
然后跑'3'，弹出队队尾的元素【a】，
看这个元素的长度是不是等于2，如果不是，
就分别把3对应的字母【d,e,f】分别和弹出的【a】拼起来，
从队首插进去，这样再跑完一圈，
队列变成了【cf,ce,cd,bf,be,bd,af,ae,ad】

如果输入的是'234'，那下一轮就继续跑'4'。
弹出队尾的元素【ad】，看长度是否等于3，
如果不是，就把4对应的【h,i,g】分别和弹出的【ad】，
拼起来，从队首往回插。

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
    for (int i = 0; i < leSize; i++) { /*每一层leSize种case */
        tmp[*tmpIdx] = letter[digits[start] - '2'][i];
        (*tmpIdx)++;/*前进一层*/
        backtrack(digits, srcSize, returnSize, tmp, tmpIdx, start + 1, res);
        (*tmpIdx)--;/*回溯反悔一层*/
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

/*
39. 组合总和
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：

所有数字（包括 target）都是正整数。
解集不能包含重复的组合。
示例 1:

输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
  [7],
  [2,2,3]
]

思路：以 target = 7 为根结点，每一个分支做减法。
减到 00 或者负数的时候，剪枝。其中，
减到 00 的时候结算，这里 "结算" 的意思是添加到结果集。
*/

int cmp_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().

	按层回溯
 */

void backtrack(int* candidates, int candidatesSize, int start,
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

	if (start == candidatesSize) {
        return;
    }

    for (int i = start; i < candidatesSize && target - candidates[i] >= 0; i++) {
        current[curIdx++] = candidates[i];
        backtrack(candidates, candidatesSize, i, target - candidates[i],
            returnSize, returnColumnSizes, res, current, curIdx);
        curIdx--;
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
    backtrack(candidates, candidatesSize, 0, target, returnSize,
        returnColumnSizes, res, current, 0);
    return res;
}

/*
这道题我用的是减法，有兴趣的朋友还可以使用加法，
加到 target 的时候结算，超过 target 的时候剪枝。
*/
int cmp_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 按层回溯
 */

void backtrack(int* candidates, int candidatesSize, int start,
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
        current[curIdx++] = candidates[i];
        backtrack(candidates, candidatesSize, i, target,
            returnSize, returnColumnSizes, res, current, curIdx, sum + candidates[i]);
	// 无论是该路径大于target还是等于target，
	//都需要对其删除最后一个元素，进行其余支路的搜索
        curIdx--;
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
    backtrack(candidates, candidatesSize, 0, target, returnSize,
        returnColumnSizes, res, current, 0, 0);
    return res;
}



int cmp_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
	金典回溯
 */

void backtrack(int* candidates, int candidatesSize, int start,
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

    current[curIdx++] = candidates[start];
    backtrack(candidates, candidatesSize, start, target - candidates[start],
        returnSize, returnColumnSizes, res, current, curIdx);
    curIdx--;
    //继续搜索此时达到target的下一个
    backtrack(candidates, candidatesSize, start + 1, target,
        returnSize, returnColumnSizes, res, current, curIdx);
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
    backtrack(candidates, candidatesSize, 0, target, returnSize,
        returnColumnSizes, res, current, 0);
    return res;
}