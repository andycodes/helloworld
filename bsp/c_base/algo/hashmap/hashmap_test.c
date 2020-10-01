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
30. 串联所有单词的子串
难度困难317
给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

示例 1：
输入：
  s = "barfoothefoobarman",
  words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。
示例 2：
输入：
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
输出：[]


*/
uint32_t simple_hash(char *s, int len)
{
    uint32_t ret = 0;
    for (int i = 0; i < len; i++)
    {
        char shift = i % 4;
        ret += (*(s + i) << shift * 8);
    }

    return ret;
}

int isContactSubstr(uint32_t *pow_s_hash, uint32_t add_words_hash, int wordsSize, int word_len)
{
    uint32_t add_s_hash = 0;

    for (int i = 0; i < wordsSize; i++)
    {
        add_s_hash += pow_s_hash[i * word_len];
    }

    return add_words_hash == add_s_hash;
}

int *findSubstring(char *s, char **words, int wordsSize, int *returnSize)
{
    *returnSize = 0;
    int *results = (int *)malloc(sizeof(int) * 0xFF);

    if (!wordsSize || !s[0])
    {
        return results;
    }

    int word_len = strlen(words[0]);
    int substr_len = wordsSize * word_len;

    uint32_t pow_s_hash[0xFFFF];
    uint32_t add_words_hash = 0;

    int s_len = strlen(s);

    for (int i = 0; i <= s_len - word_len; i++)
    {
        uint32_t hash  = simple_hash(s + i, word_len);
        pow_s_hash[i] = hash * hash;
    }

    for (int i = 0; i < wordsSize; i++)
    {
        uint32_t hash = simple_hash(words[i], word_len);
        add_words_hash += hash * hash;
    }

    for (int i = 0; i <= s_len - substr_len; i++)
    {
        if (isContactSubstr(pow_s_hash + i, add_words_hash, wordsSize, word_len))
        {
            results[(*returnSize)++] = i;
        }
    }

    return results;
}

#define printf() void();
 char ** g_words;
 int g_wordsSize;
 int g_wordsLen;

int isok(char *s,int i,int len)
{

    int *bitmap=calloc(g_wordsSize,sizeof(int));//利用calloc能初始化成0的性质，0代表未使用过
    int matchSize=0;
    int matchFlag=0;
    printf("!!!!!!!!!!i=%d\n",i);
    while(i<len){
        matchFlag=0;
        for(int k=0;k<g_wordsSize;k++) {
            //if(bitmap[k]==0)printf("s+i:%s \ntry to match %s\n",s+i,g_words[k]);
            if(bitmap[k]==0&&strncmp(s+i,g_words[k],g_wordsLen)==0) {
                printf("matched %s\n",g_words[k]);
                bitmap[k]=1;
                matchFlag=1;
                matchSize++;
                i=i+g_wordsLen;
                break;
            }
        }
        if(matchFlag==0)return 0;
        if(matchSize==g_wordsSize)return 1;
    }
    if(matchSize==g_wordsSize)return 1;
    return 0;
}




int* findSubstring(char * s, char ** words, int wordsSize, int* returnSize){

    int len=strlen(s);
    int * out = calloc(len,sizeof(int));
    (*returnSize)=0;
    if(wordsSize==0||len==0||s==NULL||words==NULL){////注意入特殊情况，对参判断！！！
        return out;
    }
    g_words=words;
    g_wordsSize=wordsSize;   ////如果入参是空，给全局变量复制会编译异常！！！！
    g_wordsLen=strlen(words[0]);
    for(int i=0;len-i>=wordsSize*g_wordsLen;i++){///剩余能匹配的字段小于太短，就不循环了
        if(isok(s,i,len)){
            out[*returnSize]=i;
            (*returnSize)++;
        }
    }
    return out;
}

/*
447. 回旋镖的数量
给定平面上 n 对不同的点，“回旋镖” 是由点表示的元组 (i, j, k) ，其中 i 和 j 之间的距离和 i 和 k 之间的距离相等（需要考虑元组的顺序）。

找到所有回旋镖的数量。你可以假设 n 最大为 500，所有点的坐标在闭区间 [-10000, 10000] 中。

示例:

输入:
[[0,0],[1,0],[2,0]]

输出:
2

解释:
两个回旋镖为 [[1,0],[0,0],[2,0]] 和 [[1,0],[2,0],[0,0]]
*/
#include <stdlib.h>
#define MAX_N 500

int compare(const void* a, const void* b)
{
	return *(int*)a > *(int*)b;
}

int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize)
{
    if (points == NULL || pointsSize < 3 || pointsSize > 500) {
        return 0;
    }

    int distance[MAX_N] = {0};  // 距离数组
    int sum = 0;
    int i;	// 指针，选择锚点
    int j;	// 指针，计算距离

    for (i = 0; i < pointsSize; i++) {
    	// 计算每一点到点i的距离
    	for (j = 0; j < pointsSize; j++) {
    		distance[j] = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) +
    					  (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
    	}

    	// 对距离按升序排序
    	qsort(distance, pointsSize, sizeof(int), compare);

    	int currCount = 1;  // 当前计数

    	// 遍历排序后的距离，统计个数
    	for (j = 1; j < pointsSize; j++) {
    		if (distance[j] != distance[j - 1]) {
    			sum += currCount * (currCount - 1);
    			currCount = 1;
    		} else {
    			currCount++;
    		}
    	}

    	// 记得统计最后一个单词
    	sum += currCount * (currCount - 1);
    }

    return sum;
}

int cmp(const void* a, const void* b){
    if(*(int*) a > *(int*)b){
        return 1;
    }else{
        return -1;
    }
}
int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize){
    int cmp(const void* a, const void* b);
    int* Distances = (int*)malloc(sizeof(int) * pointsSize);
    int Num_Boo = 0;
    for(int i = 0; i < pointsSize; i++){
        for(int j = 0; j < pointsSize; j++){
            Distances[j] = pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2);
        }
        qsort(Distances, pointsSize, sizeof(int), cmp);
        int Count = 1;
        for(int j = 1; j < pointsSize; j++){
            if(Distances[j] == Distances[j - 1]){
                Count++;
            }else if(Count > 1){
                Num_Boo += Count * (Count - 1);
                Count = 1;
            }else{
                continue;
            }
        }
        Num_Boo += Count * (Count - 1);
    }
    free(Distances);
    return Num_Boo;
}

/*
500. 键盘行
给定一个单词列表，只返回可以使用在键盘同一行的字母打印出来的单词。键盘如下图所示。



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
697. 数组的度
难度简单115
给定一个非空且只包含非负数的整数数组 nums,
数组的度的定义是指数组里任一元素出现频数的最大值。
你的任务是找到与 nums 拥有相同大小的度的最短连续子数组，
返回其长度。
示例 1:
输入: [1, 2, 2, 3, 1]
输出: 2
解释:
输入数组的度是2，因为元素1和2的出现频数最大，均为2.
连续子数组里面拥有相同度的有如下所示:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
最短连续子数组[2, 2]的长度为2，所以返回2.
示例 2:
输入: [1,2,2,3,1,4,2]
输出: 6

*/
struct Degree {
	int cnt;
	int start;
	int len;
};

int findShortestSubArray(int* nums, int numsSize)
{
	struct Degree map[50000];
	memset(map, 0, sizeof(map));

	for (int i = 0; i < numsSize; i++) {
		map[nums[i]].cnt++;
		if (map[nums[i]].cnt == 1) {
			map[nums[i]].start = i;
			map[nums[i]].len = 1;
		} else {
			map[nums[i]].len = i - map[nums[i]].start + 1;
		}
	}

	int maxdegree = 0;
	for (int i = 0; i < numsSize; i++) {
		maxdegree = fmax(maxdegree, map[nums[i]].cnt);
	}

	int minsize = numsSize;
	for (int i = 0; i < numsSize; i++) {
		if (map[nums[i]].cnt == maxdegree)
			minsize = fmin(minsize, map[nums[i]].len);
	}

	return minsize;
}

