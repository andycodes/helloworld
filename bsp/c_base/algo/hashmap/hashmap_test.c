/*
454. 四数相加 II
给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组
(i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。
为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且
0 ≤ N ≤ 500 。所有整数的范围在 -228 到 228 - 1 之间，最终结果
不会超过 231 - 1 。
例如:
输入:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]
输出:
2
解释:
两个元组如下:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
*/

typedef struct hash{
    int key;
    int count;
    UT_hash_handle hh;
}*hash_;

int fourSumCount(int* A, int ASize, int* B, int BSize, int* C, int CSize, int* D, int DSize)
{
    hash_ p1 = NULL,t = NULL,p2 = NULL;
    for(int i = 0;i < ASize;i++)
        for(int j = 0; j < ASize;j++){
            int tar = A[i]+B[j];
            HASH_FIND_INT(t, &tar, p1);
            if(!p1){
                p1 = (hash_)malloc(sizeof(*p1));
                p1->key = tar;
                p1->count = 0;
                HASH_ADD_INT(t, key, p1);
            }
            p1->count++;
        }
    int count = 0;
    for(int i = 0;i < ASize;i++)
        for(int j = 0; j < ASize;j++){
            int tar = -(C[i]+D[j]);
            HASH_FIND_INT(t, &tar, p2);
            if(p2)
                count += p2->count;
        }
    return count;
}

/*
面试题 16.21. 交换和
难度中等5
给定两个整数数组，请交换一对数值（每个数组中取一个数
值），使得两个数组所有元素的和相等。
返回一个数组，第一个元素是第一个数组中要交换的元素，
第二个元素是第二个数组中要交换的元素。若有多个答案，
返回任意一个均可。若无满足条件的数值，返回空数组。
示例:
输入: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
输出: [1, 3]
示例:
输入: array1 = [1, 2, 3], array2 = [4, 5, 6]
输出: []
*/
/*
先求两个数组的差值diff = sum(a)-sum(b), 如果为奇数直接return [], 因为
交换任何数得到的diff一定是两个数字差值的2倍
然后将数组b作为集合, 遍历数组a, 判断其每个元素-diff//2是否
在b集合中, 在的话即为所求
交换的两个数的差值一定是2d = (sum(A) - sum(B))
*/

struct Hashmap {
    int value;
    UT_hash_handle hh;
};

int* findSwapValues(int* array1, int array1Size,
int* array2, int array2Size, int* returnSize)
{
	int sum1 = 0;
	int sum2 = 0;
	struct Hashmap *hashmap = NULL;
	struct Hashmap *find = NULL;
	struct Hashmap *s, *tmp;


	*returnSize = 0;

	for (int i = 0; i < array1Size; i++) {
		sum1 += array1[i];
	}

	for (int i = 0; i < array2Size; i++) {
		sum2 += array2[i];
		struct Hashmap *node = (struct Hashmap *)calloc(1, sizeof(struct Hashmap));
		node->value = array2[i];
		HASH_ADD_INT(hashmap, value, node);
	}

	int diff = sum1 - sum2;
	if (diff % 2) {
		return NULL;
	}

	for (int i = 0; i < array1Size; i++) {
		int target = array1[i] - (sum1 - sum2) / 2;
		HASH_FIND_INT(hashmap, &target, find);
		if (find != NULL) {
			int *res = (int *)calloc(2, sizeof(int));
			res[0] = array1[i];
			res[1] = target;
			*returnSize = 2;
			return res;
		}
	}

	HASH_ITER(hh, hashmap, s, tmp) {
		HASH_DEL(hashmap, s);
		free(s);
	}

	return NULL;
}


/*
820. 单词的压缩编码
难度中等165
给定一个单词列表，我们将这个列表编码成一个索引字符串
S 与一个索引列表 A。
例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示
为 S = "time#bell#" 和 indexes = [0, 2, 5]。
对于每一个索引，我们可以通过从字符串 S 中索引的位置开
始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。
那么成功对给定单词列表进行编码的最小字符串长度是多少
呢？
示例：
输入: words = ["time", "me", "bell"]
输出: 10
说明: S = "time#bell#" ， indexes = [0, 2, 5] 。
提示：
1.	1 <= words.length <= 2000
2.	1 <= words[i].length <= 7
3.	每个单词都是小写字母 。
*/
int cmp_w(const void *a, const void *b)
{
	char *str1 = *((char **)a);
	char *str2 = *((char **)b);

	return strlen(str2) - strlen(str1);
}

int minimumLengthEncoding(char ** words, int wordsSize)
{
	qsort(words, wordsSize, sizeof(words[0]), cmp_w);
	char *s = (char *)calloc(102400, sizeof(char));
	char tmp[102400];
	for (int i = 0;i < wordsSize; i++) {
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, words[i]);
		strcat(tmp, "#");
		if (strstr(s, tmp) == NULL) {
			strcat(s, tmp);
		}
	}

	return strlen(s);
}

/*
554. 砖墙
你的面前有一堵方形的、由多行砖块组成的砖墙。 这些砖块
高度相同但是宽度不同。你现在要画一条自顶向下的、穿过
最少砖块的垂线。
砖墙由行的列表表示。 每一行都是一个代表从左至右每块砖
的宽度的整数列表。
如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。
你需要找出怎样画才能使这条线穿过的砖块数量最少，并且
返回穿过的砖块数量。
你不能沿着墙的两个垂直边缘之一画线，这样显然是没有穿
过一块砖的。

示例：
输入: [[1,2,2,1],
      [3,1,2],
      [1,3,2],
      [2,4],
      [3,1,2],
      [1,3,1,1]]

输出: 2

*/
int leastBricks(int** wall, int wallSize, int* wallColSize)
{
	short xgap[60000] = {0}; /*列向 缝隙位置*/
	int i, j, gappos;
	int row = wallSize;

	for (i = 0; i < row; i++) {
		gappos = 0;
		for (j = 0; j < wallColSize[i] - 1; j++) {
			gappos += wall[i][j];
			xgap[gappos]++; /* 每行累计列位置缝隙个数 */
		}
	}

	int maxGap = 0;
	for (i = 0; i < 60000; i++){
		maxGap = fmax(maxGap, xgap[i]);
	}

    return wallSize - maxGap;
}

/*
204. 计数质数
统计所有小于非负整数 n 的质数的数量。
示例 1：
输入：n = 10
输出：4
解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
示例 2：
输入：n = 0
输出：0
示例 3：
输入：n = 1
输出：0
*/
int countPrimes(int n)
{
	int count = 0;
	if (n == 0) {
		return 0;
	}

	bool map[n];
	//初始默认所有数为质数
	for (int i = 0; i < n; i++) {
		map[i] = true;
	}

	for (int i = 2; i < n; i++) {
		if (map[i]) {
			count++;
			for (int j = i + i; j < n; j += i) {
				//排除不是质数的数
				map[j] = false;
			}
		}
	}

	return count;
}

/*
290. 单词规律
给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:

输入: pattern = "abba", str = "dog cat cat dog"
输出: true
示例 2:

输入:pattern = "abba", str = "dog cat cat fish"
输出: false
*/
#define MAX_WORDS_NUM 1000
bool wordPattern(char * pattern, char * s){
    int patternNum = strlen(pattern);
    char *words[MAX_WORDS_NUM];
    char *context;
    int wordsNum = 0;
    words[wordsNum] = strtok_r(s, " ", &context);
    while (words[wordsNum] != NULL) {
        wordsNum++;
        words[wordsNum] = strtok_r(NULL, " ", &context);
    }
    if (patternNum != wordsNum) {
        return false;
    }
    for (int i = 0; i < wordsNum; i++) {
        for (int j = i + 1; j < wordsNum; j++) {
            if ((strcmp(words[i], words[j]) == 0 && pattern[i] != pattern[j]) ||
                (strcmp(words[i], words[j]) != 0 && pattern[i] == pattern[j])) {
                return false;
            }
        }
    }
    return true;
}

/*
219. 存在重复元素 II
给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]，并且 i 和 j 的差的 绝对值 至多为 k。



示例 1:

输入: nums = [1,2,3,1], k = 3
输出: true
示例 2:

输入: nums = [1,0,1,1], k = 1
输出: true
示例 3:

输入: nums = [1,2,3,1,2,3], k = 2
输出: false
*/
typedef struct hash{
    int key;  // 键
    int index;  // 索引值
    UT_hash_handle hh; // 让结构体哈希柄
} *hash_ptr;

bool containsNearbyDuplicate(int* nums, int numsSize, int k){
    hash_ptr p=NULL, tables=NULL;
    for(int i=0;i<numsSize;i++){
        if(tables) HASH_FIND_INT(tables, &(nums[i]), p);
        if(p&&(i-p->index)<=k) return true;
        p=(hash_ptr)malloc(sizeof(*p));
        p->key=nums[i];
        p->index=i;
        HASH_ADD_INT(tables, key, p);
    }
    return false;
}

/*
594. 最长和谐子序列
和谐数组是指一个数组里元素的最大值和最小值之间的差别正好是1。

现在，给定一个整数数组，你需要在所有可能的子序列中找到最长的和谐子序列的长度。

示例 1:

输入: [1,3,2,2,5,2,3,7]
输出: 5
原因: 最长的和谐数组是：[3,2,2,2,3].
*/

int comp(const void* a,const void* b)
{
    return *(int*)a - *(int*)b;
}

int findLHS(int* nums, int numsSize){
    qsort(nums, numsSize, sizeof(int), comp);
    int max = 0;
    int temp;
    int i, j;
    for(i = 0; i < numsSize; i++) {
        for(j = i + 1; j < numsSize; j++) {
            if(nums[j] - nums[i] < 2) {
                continue;
            } else {
                break;
            }
        }
        if(nums[j - 1] - nums[i]) {
            max = fmax(max, j - i);
        }
    }
    return max;
}

/*
652. 寻找重复的子树
给定一棵二叉树，返回所有重复的子树。对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。

两棵树重复是指它们具有相同的结构以及相同的结点值。

示例 1：

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
下面是两个重复的子树：

      2
     /
    4
和

    4
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


#define MAX_STRING_LEN 20000
#define DEBUG

typedef struct {
    char* key;
    struct TreeNode* data;
    int cnt;
    UT_hash_handle hh;
} Hash;

void AddHash(char* key, struct TreeNode* data, Hash** hashObj)
{
    Hash* node;
    HASH_FIND_STR(*hashObj, key, node);
    if (node == NULL) {
        Hash* tmp = calloc(1, sizeof(Hash));
        tmp->key = key;
        tmp->data = data;
        tmp->cnt++;
        HASH_ADD_KEYPTR(hh, *hashObj, key, strlen(key), tmp);
        DEBUG("%s is first record\n", key);
    } else {
        node->cnt++;
        DEBUG("%s is repeat\n", key);
    }
}

void DelHash(Hash** hashObj)
{
    Hash* node;
    Hash* node2;
    HASH_ITER(hh, *hashObj, node, node2) {
        HASH_DEL(*hashObj, node);
        free(node->key);
        free(node);
    }
}

void OutPut(Hash** hashObj, struct TreeNode** recordData, int* returnSize)
{
    Hash* node;
    Hash* node2;
    HASH_ITER(hh, *hashObj, node, node2) {
        if (node->cnt > 1) {
            recordData[*returnSize] = node->data;
            DEBUG("Tree[%d] = %d\n", *returnSize, node->data->val);
            (*returnSize)++;
        }
    }
}

char* Dfs(struct TreeNode* root, Hash** hashObj)
{
    if (root == NULL) {
        return "#";
    }

    char* string = calloc(MAX_STRING_LEN, sizeof(char));
    sprintf(string, "%d ", root->val);
    strcat(string, Dfs(root->left, hashObj));
    strcat(string, Dfs(root->right, hashObj));

    AddHash(string, root, hashObj);
    return string;
}

struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize)
{
	if (root == NULL) {
		*returnSize = 0;
		return NULL;
	}

    Hash* hashObj = NULL;
	Dfs(root, &hashObj);

    *returnSize = 0;
    struct TreeNode** recordData = calloc(HASH_COUNT(hashObj), sizeof(struct TreeNode*));
    OutPut(&hashObj, recordData, returnSize);

    DelHash(&hashObj);
	return recordData;
}