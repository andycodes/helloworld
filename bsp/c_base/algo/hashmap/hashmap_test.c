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

struct DataEntry {
    int key;
    int value;
    struct Node node;
};

static bool DataEntryEqual(const struct Node *a, const struct Node *b)
{
    struct DataEntry *d1 = NODE_ENTRY(a, struct DataEntry, node);
    struct DataEntry *d2 = NODE_ENTRY(b, struct DataEntry, node);
    return d1->key == d2->key;
}

static size_t DataEntryKey(const struct Node *node, size_t bktSize)
{
    struct DataEntry *e = NODE_ENTRY(node, struct DataEntry, node);
    return e->key % bktSize;
}


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

