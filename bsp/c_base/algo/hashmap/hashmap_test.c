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
781. ɭ���е�����
ɭ���У�ÿ�����Ӷ�����ɫ������һЩ���ӣ�������ȫ����
�����㻹�ж������������Ӻ��Լ�����ͬ����ɫ�����ǽ���
Щ�ش���� answers �����
����ɭ�������ӵ�����������
ʾ��:
����: answers = [1, 1, 2]
���: 5
����:
��ֻ�ش��� "1" �����ӿ�������ͬ����ɫ����Ϊ��ɫ��
֮��ش��� "2" �����Ӳ����Ǻ�ɫ���������ǵĻش���໥ì
�ܡ�
��ش��� "2" ������Ϊ��ɫ��
���⣬ɭ���л�Ӧ������ 2 ֻ��ɫ���ӵĻش�û�а�������
���С�
���ɭ�������ӵ����������� 5: 3 ֻ�ش�ĺ� 2 ֻû�лش�ġ�

����: answers = [10, 10, 10]
���: 11

����: answers = []
���: 0
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
�����ǰ��һ�·��εġ��ɶ���ש����ɵ�שǽ�� ��Щש��
�߶���ͬ���ǿ�Ȳ�ͬ��������Ҫ��һ���Զ����µġ�����
����ש��Ĵ��ߡ�
שǽ���е��б��ʾ�� ÿһ�ж���һ�������������ÿ��ש
�Ŀ�ȵ������б�
����㻭����ֻ�Ǵ�ש��ı�Ե�������Ͳ��㴩�����ש��
����Ҫ�ҳ�����������ʹ�����ߴ�����ש���������٣�����
���ش�����ש��������
�㲻������ǽ��������ֱ��Ե֮һ���ߣ�������Ȼ��û�д�
��һ��ש�ġ�

ʾ����
����: [[1,2,2,1],
      [3,1,2],
      [1,3,2],
      [2,4],
      [3,1,2],
      [1,3,1,1]]

���: 2

*/
int leastBricks(int** wall, int wallSize, int* wallColSize)
{
	short xgap[60000] = {0}; /*���� ��϶λ��*/
	int i, j, gappos;
	int row = wallSize;

	for (i = 0; i < row; i++) {
		gappos = 0;
		for (j = 0; j < wallColSize[i] - 1; j++) {
			gappos += wall[i][j];
			xgap[gappos]++; /* ÿ���ۼ���λ�÷�϶���� */
		}
	}

	int maxGap = 0;
	for (i = 0; i < 10000; i++){
		maxGap = fmax(maxGap, xgap[i]);
	}

    return wallSize - maxGap;
}


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

/*
447. �����ڵ�����
����ƽ���� n �Բ�ͬ�ĵ㣬�������ڡ� ���ɵ��ʾ��Ԫ�� (i, j, k) ������ i �� j ֮��ľ���� i �� k ֮��ľ�����ȣ���Ҫ����Ԫ���˳�򣩡�

�ҵ����л����ڵ�����������Լ��� n ���Ϊ 500�����е�������ڱ����� [-10000, 10000] �С�

ʾ��:

����:
[[0,0],[1,0],[2,0]]

���:
2

����:
����������Ϊ [[1,0],[0,0],[2,0]] �� [[1,0],[2,0],[0,0]]
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

    int distance[MAX_N] = {0};  // ��������
    int sum = 0;
    int i;	// ָ�룬ѡ��ê��
    int j;	// ָ�룬�������

    for (i = 0; i < pointsSize; i++) {
    	// ����ÿһ�㵽��i�ľ���
    	for (j = 0; j < pointsSize; j++) {
    		distance[j] = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) +
    					  (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
    	}

    	// �Ծ��밴��������
    	qsort(distance, pointsSize, sizeof(int), compare);

    	int currCount = 1;  // ��ǰ����

    	// ���������ľ��룬ͳ�Ƹ���
    	for (j = 1; j < pointsSize; j++) {
    		if (distance[j] != distance[j - 1]) {
    			sum += currCount * (currCount - 1);
    			currCount = 1;
    		} else {
    			currCount++;
    		}
    	}

    	// �ǵ�ͳ�����һ������
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
500. ������
����һ�������б�ֻ���ؿ���ʹ���ڼ���ͬһ�е���ĸ��ӡ�����ĵ��ʡ���������ͼ��ʾ��



American keyboard



ʾ����

����: ["Hello", "Alaska", "Dad", "Peace"]
���: ["Alaska", "Dad"]
*/
char ** findWords(char ** words, int wordsSize, int* returnSize){
    *returnSize = 0;
    if(words == NULL || wordsSize == 0){
        return NULL;
    }
    // 26����д��ĸ��Ӧ���кţ���Q�ڵ�1��
    //             A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
    int hash[26]= {2, 3, 3, 2, 1, 2, 2, 2, 1, 2, 2, 2, 3, 3, 1, 1, 1, 1, 2, 1, 1, 3, 1, 3, 1, 3};
    char **result = (char **)calloc(wordsSize, sizeof(char *));
    int i, j, len;
    int num = 0;//�ַ������к�

    for(i = 0; i < wordsSize; i++){
        len = strlen(words[i]);
        if(len == 0) continue;
        num = hash[toupper(words[i][0]) - 'A']; //��һ���ַ����к�
        for(j = 1; j < len; j++){
            if(num != hash[toupper(words[i][j]) - 'A']){
                break;
            }
        }
        if(j == len){//���������ַ���һ��
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
697. ����Ķ�
�Ѷȼ�115
����һ���ǿ���ֻ�����Ǹ������������� nums,
����ĶȵĶ�����ָ��������һԪ�س���Ƶ�������ֵ��
����������ҵ��� nums ӵ����ͬ��С�Ķȵ�������������飬
�����䳤�ȡ�
ʾ�� 1:
����: [1, 2, 2, 3, 1]
���: 2
����:
��������Ķ���2����ΪԪ��1��2�ĳ���Ƶ����󣬾�Ϊ2.
��������������ӵ����ͬ�ȵ���������ʾ:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
�������������[2, 2]�ĳ���Ϊ2�����Է���2.
ʾ�� 2:
����: [1,2,2,3,1,4,2]
���: 6

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

