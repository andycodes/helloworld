#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <hhash.h>
/*
1. 两数之和
难度简单7810
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整
数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
示例:
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

*/

#define MAXN 100
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	struct HashTable ht;
    	size_t bktSize = numsSize;
	int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
	//SHOULD(ret == 0);

	int* res = (int *)calloc(2, sizeof(int));

	for (int i = 0; i < numsSize; i++) {
		int diff = target - nums[i];
		struct Node *findNode;
		struct DataEntry findEntry;
		findEntry.key = diff;
		findNode = HashFind(&ht, &findEntry.node);
		if(findNode == NULL) {
			struct DataEntry *newEntry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
			newEntry->key = nums[i];
			newEntry->value = i;
			HashAdd(&ht, &newEntry->node);
		} else {
				*returnSize = 2;
				res[1] = i;
				struct DataEntry *entry;
				entry = NODE_ENTRY(findNode, struct DataEntry, node);
				res[0] = entry->value;
				break;
		}
	}

	HashDeinit(&ht, NULL);
	return res;
}

int main()
{
	int array[] = {2, 7, 11, 15};
	int target = 9;
	int returnSize;
	int *ret = twoSum(array, 4, target, &returnSize);

	for (int i = 0; i < returnSize; i++) {
			printf("%d", ret[i]);
	}
}



int cmp_char(const void *a, const void *b)
{
	return  *((char *)a) - *((char *)b);
}


struct HashCallBack {
	char ***res;
	int* returnSize;
	int** returnColumnSizes;
};

void nodeFuncX(struct Node *node, void *arg)
{
	struct HashCallBack *cb = (struct HashCallBack *)arg;
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	int cnt = (*cb->returnColumnSizes)[*cb->returnSize];
	cb->res[*cb->returnSize][cnt] = strdup(entry->value);
	(*cb->returnColumnSizes)[*cb->returnSize]++;
}


void nodeFree(struct Node *node)
{
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	free(entry->key);
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
	if (returnSize == NULL) {
		return NULL;
	}

	if (strs == NULL || strsSize <= 0) {
		*returnSize = 0;
		return NULL;
	}

	struct HashTable ht;
	int ret = HashInit(&ht, (size_t)strsSize * 3, hashequal_str, hashcode_str);
	for (int i = 0; i < strsSize; i++) {
		struct DataEntry *newEntry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		char *sort = strdup(strs[i]);
		qsort(sort, strlen(sort), sizeof(char), cmp_char);
		newEntry->key = sort;
		newEntry->value = strs[i];
		HashAdd(&ht, &newEntry->node);
	}

	char ***res = (char ***)calloc(1024, sizeof(char **));
	for (int i = 0; i < 1024; i++) {
		res[i] = (char **)calloc(1024, sizeof(char *));
		for (int j = 0; j < strsSize; j++) {
			res[i][j] = calloc(1024, sizeof(char));
		}
	}

	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	struct HashCallBack arg;
	arg.res = res;
	arg.returnSize = returnSize;
	arg.returnColumnSizes = returnColumnSizes;

	for (int i = 0; i < ht.bktSize; i++) {
		if(!ListEmpty(&ht.bkts[i])) {
			struct Node *node;
			LIST_FOR_EACH(node, &ht.bkts[i]) {
				nodeFuncX(node, &arg);
			}
			(*returnSize)++;
		}
	}

	HashDeinit(&ht, nodeFree);
	return res;
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSwapValues(int* array1, int array1Size, int* array2, int array2Size, int* returnSize)
{
	int sum1 = 0;
	int sum2 = 0;

	*returnSize = 0;

	struct HashTable dht;
	struct HashTable *ht = &dht;
	HashInit(ht, array2Size, hashequal_int, hashcode_int);

	for (int i = 0; i < array1Size; i++) {
		sum1 += array1[i];
	}

	for (int i = 0; i < array2Size; i++) {
		sum2 += array2[i];
		hashPushKey(ht, array2[i]);
	}

	int diff = sum1 - sum2;
	if (diff % 2) {
		return NULL;
	}

	diff =  diff / 2;

	int *ret = (int *)calloc(2, sizeof(int));
	for (int i = 0; i < array1Size; i++) {
		struct DataEntry *find = hashFindKey(ht, array1[i] - diff);
		if (find != NULL) {
			ret[0] = array1[i];
			ret[1] = array1[i] - diff;
			*returnSize = 2;
			break;
		}
	}

	HashDeinit(ht, node_free);
	return ret;
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
难度中等75收藏分享切换为英文关注反馈
你的面前有一堵方形的、由多行砖块组成的砖墙。 这些砖块高度相同但是宽度不同。你现在要画一条自顶向下的、穿过最少砖块的垂线。
砖墙由行的列表表示。 每一行都是一个代表从左至右每块砖的宽度的整数列表。
如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。你需要找出怎样画才能使这条线穿过的砖块数量最少，并且返回穿过的砖块数量。
你不能沿着墙的两个垂直边缘之一画线，这样显然是没有穿过一块砖的。

示例：
输入: [[1,2,2,1],
      [3,1,2],
      [1,3,2],
      [2,4],
      [3,1,2],
      [1,3,1,1]]

输出: 2

*/
int leastBricks(int** wall, int wallSize, int* wallColSize){
    short cnt[60000] = {0};
    int i, j, tmp;

    for (i = 0; i < wallSize; i++){
        tmp = 0;
        for (j = 0; j < (wallColSize[i] - 1); j++){
            tmp += wall[i][j];
            cnt[tmp]++;
        }
    }

    tmp = 0;
    for (i = 0; i < 10000; i++){
        if (cnt[i] > tmp){
            tmp = cnt[i];
        }
    }

    return wallSize - tmp;
}

/*
781. 森林中的兔子
森林中，每个兔子都有颜色。其中一些兔子（可能是全部）告诉你还有多少其他的兔子和自己有相同的颜色。我们将这些回答放在 answers 数组里。

返回森林中兔子的最少数量。

示例:
输入: answers = [1, 1, 2]
输出: 5
解释:
两只回答了 "1" 的兔子可能有相同的颜色，设为红色。
之后回答了 "2" 的兔子不会是红色，否则他们的回答会相互矛盾。
设回答了 "2" 的兔子为蓝色。
此外，森林中还应有另外 2 只蓝色兔子的回答没有包含在数组中。
因此森林中兔子的最少数量是 5: 3 只回答的和 2 只没有回答的。

输入: answers = [10, 10, 10]
输出: 11

输入: answers = []
输出: 0
*/

bool hashequal_int(const struct Node *node1, const struct Node *node2)
{
	struct DataEntry *entry1 = NODE_ENTRY(node1, struct DataEntry, node);
	struct DataEntry *entry2 = NODE_ENTRY(node2, struct DataEntry, node);

	return entry1->key == entry2->key && entry2->value < entry2->key;
}
int numRabbits(int* answers, int answersSize)
{
	struct HashTable dht;
	struct HashTable *ht = &dht;

	if (answers == NULL || answersSize <= 0)
		return 0;

	HashInit(ht, answersSize, hashequal_int, hashcode_int);

	for (int i = 0; i < answersSize; i++) {
		struct DataEntry *find = hashFindKey(ht, answers[i] + 1);
		if (find != NULL) {
			find->value++;
		} else {
			struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
			entry->key = answers[i] + 1;
			entry->value = 1;
			HashAdd(ht, &entry->node);
		}
	}

	int res = 0;
	for (size_t i = 0; i < ht->bktSize; i++) {
		if (!ListEmpty(&ht->bkts[i])) {
			struct Node *node = NULL;
			LIST_FOR_EACH(node, &ht->bkts[i]) {
				struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
				//printf("[%d %c]", entry->key, entry->value);
				res += entry->key;
			}
			//printf("\n");
		}
	}

	HashDeinit(ht, node_free);
	return res;
}

/*
1156. 单字符重复子串的最大长度
难度中等34
如果字符串中的所有字符都相同，那么这个字符串是单字符重复的字符串。
给你一个字符串 text，你只能交换其中两个字符一次或者什么都不做，然后得到一些单字符重复的子串。返回其中最长的子串的长度。

示例 1：
输入：text = "ababa"
输出：3
示例 2：
输入：text = "aaabaaa"
输出：6

*/
int maxRepOpt1(char * text)
   {
        int len = strlen(text);
        int cnt[26];//记录各个字符在text中出现的次数

	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < len; i++)
            cnt[text[i]-'a']++;
        //从左向右挨个字符遍历
        char cur_c = text[0];//当前单字符
        int cur_l = 1;//当前单字符串长度
        int idx = 1;//当前遍历到的字符索引
        int ans = -1;//答案
        while(idx < len){
            while(idx < len && text[idx] == cur_c){
                idx++;
                cur_l++;
            }
            if(cur_l < cnt[cur_c-'a']){//可以把某个位置的cur_c交换到idx位置，使单字符串得以延长
                cur_l++;
                int tmp = idx + 1;//继续向后延长单字符串
                while(tmp < len && text[tmp] == cur_c){
                    cur_l++;
                    tmp++;
                }
            }
            //当aaaba这种情况时，前"交换"的a会在继续延长时再次计数，所以要取min，达到去重的作用
            cur_l = fmin(cur_l, cnt[cur_c-'a']);
            ans = fmax(ans, cur_l);
            if(idx < len){//继续记录下一段单字符串
                cur_c = text[idx];
                cur_l = 1;
                idx++;
            }
        }
        return ans;
}
