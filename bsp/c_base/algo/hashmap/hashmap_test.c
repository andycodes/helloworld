/*
454. ������� II
�����ĸ����������������б� A , B , C , D ,�����ж��ٸ�Ԫ�� (i, j, k, l) ��ʹ�� A[i] + B[j] + C[k] + D[l] = 0��

Ϊ��ʹ����򵥻������е� A, B, C, D ������ͬ�ĳ��� N���� 0 �� N �� 500 �����������ķ�Χ�� -228 �� 228 - 1 ֮�䣬���ս�����ᳬ�� 231 - 1 ��

����:

����:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

���:
2

����:
����Ԫ������:
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
500. ������
����һ�������б�ֻ���ؿ���ʹ���ڼ���ͬһ�е���ĸ��
ӡ�����ĵ��ʡ���������ͼ��ʾ��
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
204. ��������
ͳ������С�ڷǸ����� n ��������������



ʾ�� 1��

���룺n = 10
�����4
���ͣ�С�� 10 ������һ���� 4 ��, ������ 2, 3, 5, 7 ��
ʾ�� 2��

���룺n = 0
�����0
ʾ�� 3��

���룺n = 1
�����0
*/


int countPrimes(int n) {
    int count = 0;
    //��ʼĬ��������Ϊ����
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
                //�ų�������������
                signs[j] = false;
            }
        }
    }
    return count;
}

