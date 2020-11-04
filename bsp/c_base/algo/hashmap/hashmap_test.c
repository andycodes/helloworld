/*
454. ������� II
�����ĸ����������������б� A , B , C , D ,�����ж��ٸ�Ԫ��
(i, j, k, l) ��ʹ�� A[i] + B[j] + C[k] + D[l] = 0��
Ϊ��ʹ����򵥻������е� A, B, C, D ������ͬ�ĳ��� N����
0 �� N �� 500 �����������ķ�Χ�� -228 �� 228 - 1 ֮�䣬���ս��
���ᳬ�� 231 - 1 ��
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
������ 16.21. ������
�Ѷ��е�5
���������������飬�뽻��һ����ֵ��ÿ��������ȡһ����
ֵ����ʹ��������������Ԫ�صĺ���ȡ�
����һ�����飬��һ��Ԫ���ǵ�һ��������Ҫ������Ԫ�أ�
�ڶ���Ԫ���ǵڶ���������Ҫ������Ԫ�ء����ж���𰸣�
��������һ�����ɡ�����������������ֵ�����ؿ����顣
ʾ��:
����: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
���: [1, 3]
ʾ��:
����: array1 = [1, 2, 3], array2 = [4, 5, 6]
���: []
*/
/*
������������Ĳ�ֵdiff = sum(a)-sum(b), ���Ϊ����ֱ��return [], ��Ϊ
�����κ����õ���diffһ�����������ֲ�ֵ��2��
Ȼ������b��Ϊ����, ��������a, �ж���ÿ��Ԫ��-diff//2�Ƿ�
��b������, �ڵĻ���Ϊ����
�������������Ĳ�ֵһ����2d = (sum(A) - sum(B))
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
820. ���ʵ�ѹ������
�Ѷ��е�165
����һ�������б����ǽ�����б�����һ�������ַ���
S ��һ�������б� A��
���磬�������б��� ["time", "me", "bell"]�����ǾͿ��Խ����ʾ
Ϊ S = "time#bell#" �� indexes = [0, 2, 5]��
����ÿһ�����������ǿ���ͨ�����ַ��� S ��������λ�ÿ�
ʼ��ȡ�ַ�����ֱ�� "#" ���������ָ�����֮ǰ�ĵ����б�
��ô�ɹ��Ը��������б���б������С�ַ��������Ƕ���
�أ�
ʾ����
����: words = ["time", "me", "bell"]
���: 10
˵��: S = "time#bell#" �� indexes = [0, 2, 5] ��
��ʾ��
1.	1 <= words.length <= 2000
2.	1 <= words[i].length <= 7
3.	ÿ�����ʶ���Сд��ĸ ��
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
	for (i = 0; i < 60000; i++){
		maxGap = fmax(maxGap, xgap[i]);
	}

    return wallSize - maxGap;
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
int countPrimes(int n)
{
	int count = 0;
	if (n == 0) {
		return 0;
	}

	bool map[n];
	//��ʼĬ��������Ϊ����
	for (int i = 0; i < n; i++) {
		map[i] = true;
	}

	for (int i = 2; i < n; i++) {
		if (map[i]) {
			count++;
			for (int j = i + i; j < n; j += i) {
				//�ų�������������
				map[j] = false;
			}
		}
	}

	return count;
}

/*
290. ���ʹ���
����һ�ֹ��� pattern ��һ���ַ��� str ���ж� str �Ƿ���ѭ��ͬ�Ĺ��ɡ�

����� ��ѭ ָ��ȫƥ�䣬���磬 pattern ���ÿ����ĸ���ַ��� str �е�ÿ���ǿյ���֮�������˫�����ӵĶ�Ӧ���ɡ�

ʾ��1:

����: pattern = "abba", str = "dog cat cat dog"
���: true
ʾ�� 2:

����:pattern = "abba", str = "dog cat cat fish"
���: false
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
219. �����ظ�Ԫ�� II
����һ�����������һ������ k���ж��������Ƿ����������ͬ������ i �� j��ʹ�� nums [i] = nums [j]������ i �� j �Ĳ�� ����ֵ ����Ϊ k��



ʾ�� 1:

����: nums = [1,2,3,1], k = 3
���: true
ʾ�� 2:

����: nums = [1,0,1,1], k = 1
���: true
ʾ�� 3:

����: nums = [1,2,3,1,2,3], k = 2
���: false
*/
typedef struct hash{
    int key;  // ��
    int index;  // ����ֵ
    UT_hash_handle hh; // �ýṹ���ϣ��
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
594. ���г������
��г������ָһ��������Ԫ�ص����ֵ����Сֵ֮��Ĳ��������1��

���ڣ�����һ���������飬����Ҫ�����п��ܵ����������ҵ���ĺ�г�����еĳ��ȡ�

ʾ�� 1:

����: [1,3,2,2,5,2,3,7]
���: 5
ԭ��: ��ĺ�г�����ǣ�[3,2,2,2,3].
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
652. Ѱ���ظ�������
����һ�ö����������������ظ�������������ͬһ����ظ���������ֻ��Ҫ������������һ�õĸ���㼴�ɡ�

�������ظ���ָ���Ǿ�����ͬ�Ľṹ�Լ���ͬ�Ľ��ֵ��

ʾ�� 1��

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
�����������ظ���������

      2
     /
    4
��

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