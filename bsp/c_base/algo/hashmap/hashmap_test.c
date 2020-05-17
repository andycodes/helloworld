#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <hhash.h>
/*
1. ����֮��
�Ѷȼ�7810
����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ���� ���� ��
�������������ǵ������±ꡣ
����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ��㲻���ظ��������������ͬ����Ԫ�ء�
ʾ��:
���� nums = [2, 7, 11, 15], target = 9

��Ϊ nums[0] + nums[1] = 2 + 7 = 9
���Է��� [0, 1]

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
������ 16.21. ������
�Ѷ��е�5
���������������飬�뽻��һ����ֵ��ÿ��������ȡһ����ֵ����ʹ��������������Ԫ�صĺ���ȡ�
����һ�����飬��һ��Ԫ���ǵ�һ��������Ҫ������Ԫ�أ��ڶ���Ԫ���ǵڶ���������Ҫ������Ԫ�ء����ж���𰸣���������һ�����ɡ�����������������ֵ�����ؿ����顣
ʾ��:
����: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
���: [1, 3]
ʾ��:
����: array1 = [1, 2, 3], array2 = [4, 5, 6]
���: []

*/
/*
������������Ĳ�ֵdiff = sum(a)-sum(b), ���Ϊ����ֱ��return [], ��Ϊ�����κ����õ���diffһ�����������ֲ�ֵ��2��
Ȼ������b��Ϊ����, ��������a, �ж���ÿ��Ԫ��-diff//2�Ƿ���b������, �ڵĻ���Ϊ����

*/
/*
�������������Ĳ�ֵһ����d = (sum(A) - sum(B)) / 2
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
820. ���ʵ�ѹ������
�Ѷ��е�165
����һ�������б����ǽ�����б�����һ�������ַ��� S ��һ�������б� A��
���磬�������б��� ["time", "me", "bell"]�����ǾͿ��Խ����ʾΪ S = "time#bell#" �� indexes = [0, 2, 5]��
����ÿһ�����������ǿ���ͨ�����ַ��� S ��������λ�ÿ�ʼ��ȡ�ַ�����ֱ�� "#" ���������ָ�����֮ǰ�ĵ����б�
��ô�ɹ��Ը��������б���б������С�ַ��������Ƕ����أ�

ʾ����
����: words = ["time", "me", "bell"]
���: 10
˵��: S = "time#bell#" �� indexes = [0, 2, 5] ��

��ʾ��
1.	1 <= words.length <= 2000
2.	1 <= words[i].length <= 7
3.	ÿ�����ʶ���Сд��ĸ ��

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