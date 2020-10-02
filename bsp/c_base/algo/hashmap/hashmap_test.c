/*
454. 四数相加 II
给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组 (i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。

为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且 0 ≤ N ≤ 500 。所有整数的范围在 -228 到 228 - 1 之间，最终结果不会超过 231 - 1 。

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

int fourSumCount(int* A, int ASize, int* B, int BSize, int* C, int CSize, int* D, int DSize){
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
给定两个整数数组，请交换一对数值（每个数组中取一个数值），使得两个数组所有元素的和相等。
返回一个数组，第一个元素是第一个数组中要交换的元素，第二个元素是第二个数组中要交换的元素。若有多个答案，返回任意一个均可。若无满足条件的数值，返回空数组。
示例:
输入: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
输出: [1, 3]
示例:
输入: array1 = [1, 2, 3], array2 = [4, 5, 6]
输出: []

*/
/*
先求两个数组的差值diff = sum(a)-sum(b), 如果为奇数直接return [], 因为交换任何数得到的diff一定是两个数字差值的2倍
然后将数组b作为集合, 遍历数组a, 判断其每个元素-diff//2是否在b集合中, 在的话即为所求

*/
/*
交换的两个数的差值一定是d = (sum(A) - sum(B)) / 2
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
781. 森林中的兔子
森林中，每个兔子都有颜色。其中一些兔子（可能是全部）
告诉你还有多少其他的兔子和自己有相同的颜色。我们将这
些回答放在 answers 数组里。
返回森林中兔子的最少数量。
示例:
输入: answers = [1, 1, 2]
输出: 5
解释:
两只回答了 "1" 的兔子可能有相同的颜色，设为红色。
之后回答了 "2" 的兔子不会是红色，否则他们的回答会相互矛
盾。
设回答了 "2" 的兔子为蓝色。
此外，森林中还应有另外 2 只蓝色兔子的回答没有包含在数
组中。
因此森林中兔子的最少数量是 5: 3 只回答的和 2 只没有回答的。

输入: answers = [10, 10, 10]
输出: 11

输入: answers = []
输出: 0
*/
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} entry;

void DeleteHash(entry** hashTable)
{
    entry* curEntry, *tmpEntry;
    HASH_ITER(hh, *hashTable, curEntry, tmpEntry) {
        HASH_DEL(*hashTable, curEntry);
        free(curEntry);
    }
    free(*hashTable);
    return;
}

int numRabbits(int* answers, int answersSize){
    if (!answers || answersSize <= 0) {
        return 0;
    }
    int cnt = 0;

    entry* hashTable = NULL;
    entry* findK;
    int k;
    for (int i = 0; i < answersSize; i++) {
        findK = NULL;
        k = answers[i];
        HASH_FIND_INT(hashTable, &k, findK);
        if (!findK) {
            cnt += (k + 1);
            entry* e = (entry*)malloc(sizeof(entry));
            e->key = k;
            e->val = 1;
            HASH_ADD_INT(hashTable, key, e);
        } else {
            (findK->val)++;
            int num = findK->key + 1;
            if (findK->val > num) {
                cnt += num;
                findK->val = 1;
            }
        }
    }
    DeleteHash(&hashTable);
    return cnt;
}

/*
820. 单词的压缩编码
难度中等165
给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A。
例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示为 S = "time#bell#" 和 indexes = [0, 2, 5]。
对于每一个索引，我们可以通过从字符串 S 中索引的位置开始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。
那么成功对给定单词列表进行编码的最小字符串长度是多少呢？

示例：
输入: words = ["time", "me", "bell"]
输出: 10
说明: S = "time#bell#" ， indexes = [0, 2, 5] 。

提示：
1.	1 <= words.length <= 2000
2.	1 <= words[i].length <= 7
3.	每个单词都是小写字母 。

*/
int minimumLengthEncoding(char ** words, int wordsSize)
{
	struct HashTable dht;
	struct HashTable *ht = &dht;
	HashInit(ht, wordsSize, hashequal_str, hashcode_str);

	for (int i = 0; i < wordsSize; i++) {
		struct DataEntry cmpEntry;
		cmpEntry.key = words[i];
		struct DataEntry *find = hashFind(ht, &cmpEntry);
		if (find == NULL) {
			struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
			entry->key = words[i];
			HashAdd(ht, &entry->node);
		}
	}

	for (int i = 0; i < wordsSize; i++) {
		for (int j = 1; j < strlen(words[i]); j++) {
			struct DataEntry cmpEntry;
			cmpEntry.key = &words[i][j];
			struct DataEntry *find = hashFind(ht, &cmpEntry);
			if (find != NULL) {
				HashRemove(&find->node);
				//free
			}
		}
	}

	int len = 0;
	int cnt = 0;
	for (size_t i = 0; i < ht->bktSize; i++) {
		if (!ListEmpty(&ht->bkts[i])) {
			struct Node *node = NULL;
			LIST_FOR_EACH(node, &ht->bkts[i]) {
				struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
				len += strlen(entry->key);
				cnt++;
			}
			//printf("\n");
		}
	}

	return len + cnt;
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
	for (i = 0; i < 10000; i++){
		maxGap = fmax(maxGap, xgap[i]);
	}

    return wallSize - maxGap;
}


/*
500. 键盘行
给定一个单词列表，只返回可以使用在键盘同一行的字母打
印出来的单词。键盘如下图所示。
American keyboard
示例：
输入: ["Hello", "Alaska", "Dad", "Peace"]
输出: ["Alaska", "Dad"]
*/
char ** findWords(char ** words, int wordsSize, int* returnSize){
    *returnSize = 0;
    if(words == NULL || wordsSize == 0){
        return NULL;
    }
    // 26个大写字母对应的行号，如Q在第1行
    //             A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
    int hash[26]= {2, 3, 3, 2, 1, 2, 2, 2, 1, 2, 2, 2, 3, 3, 1, 1, 1, 1, 2, 1, 1, 3, 1, 3, 1, 3};
    char **result = (char **)calloc(wordsSize, sizeof(char *));
    int i, j, len;
    int num = 0;//字符所在行号

    for(i = 0; i < wordsSize; i++){
        len = strlen(words[i]);
        if(len == 0) continue;
        num = hash[toupper(words[i][0]) - 'A']; //第一个字符的行号
        for(j = 1; j < len; j++){
            if(num != hash[toupper(words[i][j]) - 'A']){
                break;
            }
        }
        if(j == len){//单词所有字符在一行
            result[(*returnSize)++] = words[i];
        }
    }
    return result;
}

int cmp (char* s) {
    char* s1 = "qwertyuiopQWERTYUIOP";
    char* s2 = "asdfghjklASDFGHJKL";
    char* s3 = "zxcvbnmZXCVBNM";

    if (strchr(s1, s) != NULL) {
        return 1;
    } else if (strchr(s2, s) != NULL) {
        return 2;
    }
    return 3;
}
char ** findWords(char ** words, int wordsSize, int* returnSize){
    char** ret = (char **)malloc(wordsSize * sizeof(char *));
    * returnSize = 0;
    for (int i = 0; i < wordsSize; i++) {
        int len = strlen(words[i]);
        int flag = cmp(words[i][0]);
        for (int j = 1; j < len; j++) {
            if (cmp(words[i][j]) != flag) {
                flag = -1;
            }
        }
        if (flag != -1) {
            ret[*returnSize] = (char *)malloc((len + 1) * sizeof(char));
            memcpy(ret[*returnSize], words[i], len + 1);
            (*returnSize)++;
        }
    }
    return ret;
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


int countPrimes(int n) {
    int count = 0;
    //初始默认所有数为质数
    //vector<bool> signs(n, true);
    if (n == 0) {
            return 0;
    }
    bool signs[n];
    for (int i = 0; i < n; i++) {
            signs[i] = true;
    }
    for (int i = 2; i < n; i++) {
        if (signs[i]) {
            count++;
            for (int j = i + i; j < n; j += i) {
                //排除不是质数的数
                signs[j] = false;
            }
        }
    }
    return count;
}

