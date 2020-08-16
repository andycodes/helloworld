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

/*
554. שǽ
�Ѷ��е�75�ղط����л�ΪӢ�Ĺ�ע����
�����ǰ��һ�·��εġ��ɶ���ש����ɵ�שǽ�� ��Щש��߶���ͬ���ǿ�Ȳ�ͬ��������Ҫ��һ���Զ����µġ���������ש��Ĵ��ߡ�
שǽ���е��б��ʾ�� ÿһ�ж���һ�������������ÿ��ש�Ŀ�ȵ������б�
����㻭����ֻ�Ǵ�ש��ı�Ե�������Ͳ��㴩�����ש������Ҫ�ҳ�����������ʹ�����ߴ�����ש���������٣����ҷ��ش�����ש��������
�㲻������ǽ��������ֱ��Ե֮һ���ߣ�������Ȼ��û�д���һ��ש�ġ�

ʾ����
����: [[1,2,2,1],
      [3,1,2],
      [1,3,2],
      [2,4],
      [3,1,2],
      [1,3,1,1]]

���: 2

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
781. ɭ���е�����
ɭ���У�ÿ�����Ӷ�����ɫ������һЩ���ӣ�������ȫ���������㻹�ж������������Ӻ��Լ�����ͬ����ɫ�����ǽ���Щ�ش���� answers �����

����ɭ�������ӵ�����������

ʾ��:
����: answers = [1, 1, 2]
���: 5
����:
��ֻ�ش��� "1" �����ӿ�������ͬ����ɫ����Ϊ��ɫ��
֮��ش��� "2" �����Ӳ����Ǻ�ɫ���������ǵĻش���໥ì�ܡ�
��ش��� "2" ������Ϊ��ɫ��
���⣬ɭ���л�Ӧ������ 2 ֻ��ɫ���ӵĻش�û�а����������С�
���ɭ�������ӵ����������� 5: 3 ֻ�ش�ĺ� 2 ֻû�лش�ġ�

����: answers = [10, 10, 10]
���: 11

����: answers = []
���: 0
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
1156. ���ַ��ظ��Ӵ�����󳤶�
�Ѷ��е�34
����ַ����е������ַ�����ͬ����ô����ַ����ǵ��ַ��ظ����ַ�����
����һ���ַ��� text����ֻ�ܽ������������ַ�һ�λ���ʲô��������Ȼ��õ�һЩ���ַ��ظ����Ӵ���������������Ӵ��ĳ��ȡ�

ʾ�� 1��
���룺text = "ababa"
�����3
ʾ�� 2��
���룺text = "aaabaaa"
�����6

*/
int maxRepOpt1(char * text)
   {
        int len = strlen(text);
        int cnt[26];//��¼�����ַ���text�г��ֵĴ���

	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < len; i++)
            cnt[text[i]-'a']++;
        //�������Ұ����ַ�����
        char cur_c = text[0];//��ǰ���ַ�
        int cur_l = 1;//��ǰ���ַ�������
        int idx = 1;//��ǰ���������ַ�����
        int ans = -1;//��
        while(idx < len){
            while(idx < len && text[idx] == cur_c){
                idx++;
                cur_l++;
            }
            if(cur_l < cnt[cur_c-'a']){//���԰�ĳ��λ�õ�cur_c������idxλ�ã�ʹ���ַ��������ӳ�
                cur_l++;
                int tmp = idx + 1;//��������ӳ����ַ���
                while(tmp < len && text[tmp] == cur_c){
                    cur_l++;
                    tmp++;
                }
            }
            //��aaaba�������ʱ��ǰ"����"��a���ڼ����ӳ�ʱ�ٴμ���������Ҫȡmin���ﵽȥ�ص�����
            cur_l = fmin(cur_l, cnt[cur_c-'a']);
            ans = fmax(ans, cur_l);
            if(idx < len){//������¼��һ�ε��ַ���
                cur_c = text[idx];
                cur_l = 1;
                idx++;
            }
        }
        return ans;
}

/*
432. ȫ O(1) �����ݽṹ
�Ѷ�����57
����ʵ��һ�����ݽṹ֧�����²�����
1.	Inc(key) - ����һ���µ�ֵΪ 1 �� key������ʹһ�����ڵ� key ����һ����֤ key ��Ϊ���ַ�����
2.	Dec(key) - ������ key ��ֵ�� 1����ô���������ݽṹ���Ƴ���������ʹһ�����ڵ� key ֵ��һ�������� key �����ڣ�������������κ����顣key ��֤��Ϊ���ַ�����
3.	GetMaxKey() - ���� key ��ֵ��������һ�������û��Ԫ�ش��ڣ�����һ�����ַ���"" ��
4.	GetMinKey() - ���� key ��ֵ��С������һ�������û��Ԫ�ش��ڣ�����һ�����ַ���""��

*/

typedef struct date{
	int n;
	char* key;
	struct date* pre;
	struct date* next;
	UT_hash_handle hh;
} AllOne;
struct date* users = NULL;
/** Initialize your data structure here. */
AllOne* allOneCreate() {
	struct date* obj = (struct date*)malloc(sizeof(struct date));
	struct date* tail = (struct date*)malloc(sizeof(struct date));
	obj->n = 0;
	obj->pre = tail;
	obj->next = tail;
	tail->n = INT_MAX;
	tail->pre = obj;
	tail->next = obj;
	return obj;
}
/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
void allOneInc(AllOne* obj, char * key) {
	struct date* node = NULL;
	HASH_FIND_STR(users, key, node);
	if (!node){
		node = (struct date*)malloc(sizeof(struct date));
		node->n = 1;
		node->key = key;
		node->pre = obj;
		node->next = obj->next;
		obj->next->pre = node;
		obj->next = node;
        HASH_ADD_STR(users, key, node);
	}
	else{
		node->n++;
		while (node->n > node->next->n){
			struct date* t = node->next;
            t->next->pre = node;
            node->pre->next = t;
			node->next = t->next;
			t->pre = node->pre;
			t->next = node;
			node->pre = t;
		}
	}
}
/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
void allOneDec(AllOne* obj, char * key) {
	struct date* node = NULL;
	HASH_FIND_STR(users, key, node);
	if (node){
		if (node->n > 1){
			node->n--;
			while (node->n < node->pre->n){
				struct date* t = node->pre;
                t->pre->next = node;
                node->next->pre = t;
				node->pre = t->pre;
				t->pre = node;
				t->next = node->next;
				node->next = t;
			}
		}
		else{
			node->pre->next = node->next;
			node->next->pre = node->pre;
			HASH_DEL(users, node);
			free(node);
		}
	}
}
/** Returns one of the keys with maximal value. */
char * allOneGetMaxKey(AllOne* obj) {
	if (obj->pre->pre->n)
		return obj->pre->pre->key;
	return "";
}
/** Returns one of the keys with Minimal value. */
char * allOneGetMinKey(AllOne* obj) {
	if (obj->next->n < INT_MAX)
		return obj->next->key;
	return "";
}
void allOneFree(AllOne* obj) {
	struct date *current_user, *tmp;
	HASH_ITER(hh, users, current_user, tmp) {
		HASH_DEL(users, current_user);
		free(current_user);
	}
	struct date *t = obj->pre;
	free(t);
    free(obj);
	obj = NULL;
}

/**
 * Your AllOne struct will be instantiated and called as such:
 * AllOne* obj = allOneCreate();
 * allOneInc(obj, key);

 * allOneDec(obj, key);

 * char * param_3 = allOneGetMaxKey(obj);

 * char * param_4 = allOneGetMinKey(obj);

 * allOneFree(obj);
*/

/*
30. �������е��ʵ��Ӵ�
�Ѷ�����317
����һ���ַ��� s ��һЩ������ͬ�ĵ��� words���ҳ� s ��ǡ�ÿ����� words �����е��ʴ����γɵ��Ӵ�����ʼλ�á�
ע���Ӵ�Ҫ�� words �еĵ�����ȫƥ�䣬�м䲻���������ַ���������Ҫ���� words �е��ʴ�����˳��

ʾ�� 1��
���룺
  s = "barfoothefoobarman",
  words = ["foo","bar"]
�����[0,9]
���ͣ�
������ 0 �� 9 ��ʼ���Ӵ��ֱ��� "barfoo" �� "foobar" ��
�����˳����Ҫ, [9,0] Ҳ����Ч�𰸡�
ʾ�� 2��
���룺
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
�����[]


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

    int *bitmap=calloc(g_wordsSize,sizeof(int));//����calloc�ܳ�ʼ����0�����ʣ�0����δʹ�ù�
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
    if(wordsSize==0||len==0||s==NULL||words==NULL){////ע��������������Բ��жϣ�����
        return out;
    }
    g_words=words;
    g_wordsSize=wordsSize;   ////�������ǿգ���ȫ�ֱ������ƻ�����쳣��������
    g_wordsLen=strlen(words[0]);
    for(int i=0;len-i>=wordsSize*g_wordsLen;i++){///ʣ����ƥ����ֶ�С��̫�̣��Ͳ�ѭ����
        if(isok(s,i,len)){
            out[*returnSize]=i;
            (*returnSize)++;
        }
    }
    return out;
}