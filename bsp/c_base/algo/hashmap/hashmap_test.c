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

struct Hashmap {
	int key;
	int count;
	UT_hash_handle hh;
};

int fourSumCount(int* A, int ASize, int* B, int BSize, int* C, int CSize, int* D, int DSize)
{
    struct Hashmap *find = NULL;
    struct Hashmap *hashmap = NULL;
    struct Hashmap *p2 = NULL;
    for(int i = 0;i < ASize;i++)
        for(int j = 0; j < ASize;j++){
            int target = A[i]+B[j];
            HASH_FIND_INT(hashmap, &target, find);
            if(!find){
                find = (struct Hashmap *)malloc(sizeof(*find));
                find->key = target;
                find->count = 0;
                HASH_ADD_INT(hashmap, key, find);
            }
            find->count++;
        }
    int count = 0;
    for(int i = 0;i < ASize;i++)
        for(int j = 0; j < ASize;j++){
            int target = -(C[i]+D[j]);
            HASH_FIND_INT(hashmap, &target, p2);
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
		hash_add_int(hashmap, array2[i]);
	}

	int diff = sum1 - sum2;
	if (diff % 2) {
		return NULL;
	}

	for (int i = 0; i < array1Size; i++) {
		int target = array1[i] - (sum1 - sum2) / 2;
		find = hash_find_int(hashmap, target);
		if (find != NULL) {
			int *res = (int *)calloc(2, sizeof(int));
			res[0] = array1[i];
			res[1] = target;
			*returnSize = 2;
			return res;
		}
	}

	hash_free_int(hashmap);
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
����һ�����������һ������ k���ж��������Ƿ����������
ͬ������ i �� j��ʹ�� nums [i] = nums [j]������ i �� j �Ĳ�� ����ֵ ��
��Ϊ k��
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

bool containsNearbyDuplicate(int* nums, int numsSize, int k)
{
	hash_ptr p=NULL, tables=NULL;
	for(int i=0;i<numsSize;i++) {
		if(tables)
			HASH_FIND_INT(tables, &(nums[i]), p);

		if(p&&(i-p->index)<=k)
			return true;

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
����һ�ö����������������ظ�������������ͬһ����ظ���
������ֻ��Ҫ������������һ�õĸ���㼴�ɡ�
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

/*
726. ԭ�ӵ�����
����һ����ѧʽformula����Ϊ�ַ�����������ÿ��ԭ�ӵ�������
ԭ��������һ����д��ĸ��ʼ�����Ÿ���0���������Сд��
ĸ����ʾԭ�ӵ����֡�
����������� 1��ԭ�Ӻ��������ֱ�ʾԭ�ӵ����������
�������� 1 �򲻻�����֡����磬H2O �� H2O2 �ǿ��еģ���
H1O2 �������ǲ����еġ�
������ѧʽ����һ�����µĻ�ѧʽ������ H2O2He3Mg4 Ҳ�ǻ�ѧ
ʽ��
һ�������еĻ�ѧʽ�����֣���ѡ������ӣ�Ҳ�ǻ�ѧʽ��
���� (H2O2) �� (H2O2)3 �ǻ�ѧʽ��
����һ����ѧʽ���������ԭ�ӵ���������ʽΪ����һ����
���ֵ���ԭ�ӵ����ӣ�������������������������� 1����
Ȼ���ǵڶ���ԭ�ӵ����֣����ֵ��򣩣�����������������
���������� 1�����Դ����ơ�
ʾ�� 1:
����:
formula = "H2O"
���: "H2O"
����:
ԭ�ӵ������� {'H': 2, 'O': 1}��
*/

typedef struct a {
    char c[4];
    int cnt;
} Name;
typedef struct b {
    char c[4];
    int cnt;
    UT_hash_handle hh;
} Node;
Node *map;
Name stack[1000];
Name stack1[1000];
int top, top1;
int GetNum(char *formula, int *cnt)
{
    int i = 0, sum = 0;
    while ((formula[i] != '\0') && (formula[i] <= '9') && (formula[i] >= '0')) {
        sum = sum * 10 + (formula[i] - '0');
        i++;
    }
    if (sum == 0) {
        sum = 1;  /* ����ط�����get�������֣��Ǿ���1����������Ҫ����0 */
    }
    *cnt = sum;
    return i;
}
int GetString(char *formula, Name *ch)
{
    int i = 0;
    memset(ch->c, 0, 4);
    ch->c[i] = formula[i];
    i++;
    while ((formula[i] != '\0') && (formula[i] <= 'z') && (formula[i] >= 'a')) {
        ch->c[i] = formula[i];
        i++;
    }
    i += GetNum(&formula[i], &ch->cnt);
    return i;
}
void Save(Name *ch)
{
    Node *s = NULL;
    HASH_FIND_STR(map, ch->c, s);
    if (s == NULL) {
        s = calloc(1, sizeof(Node));
        strcpy(s->c, ch->c);
        s->cnt = ch->cnt;
        HASH_ADD_STR(map, c, s);
    } else {
        s->cnt += ch->cnt;
    }
}
int Cmp(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}
char * countOfAtoms(char * formula)
{
    map =  NULL;
    top = 0;
    top1 = 0;
    int len = strlen(formula);
    int i = 0;
    Name ch = {0};
    while (i < len) {
        if (formula[i] == '(') {
            ch.cnt = 0;
            stack[top++] = ch;
            i++;
            continue;
        }
        if ((top > 0) && (formula[i] != ')')) {
            int len1 = GetString(&formula[i], &ch);
            stack[top++] = ch;
            i += len1;
            continue;
        }
        if (formula[i] == ')') {
            i++;
            int sum = 0;
            int len2 = GetNum(&formula[i], &sum);
            i += len2;
            ch = stack[--top];
            while ((top > 0) && (ch.cnt > 0)) {
                ch.cnt *= sum;
                stack1[top1++] = ch;  /* push��stack1 */
                ch = stack[--top];    /* ��stack�м���pop */
            }
            Name ch1 = {0};
            if (top > 0) {
                while (top1 > 0) {  /* ���stack�л����ַ�������push��stack */
                    ch1 = stack1[--top1];
                    stack[top++] = ch1;
                }
            } else {
                while (top1 > 0) { /* ���stackû���ַ���ֱ�ӱ��� */
                    ch1 = stack1[--top1];
                    Save(&ch1);
                }
            }
            continue;
        }
        if (i < len) {
            int len3 = GetString(&formula[i], &ch);
            Save(&ch);
            i += len3;
        }
    }
    HASH_SORT(map, Cmp); /* ��hash������Ȼ����� */
    char *res = calloc(1001, sizeof(char));
    Node *s, *tmp;
    HASH_ITER(hh, map, s, tmp) {
        strcat(res, s->c);
        if (s->cnt > 1) {
            char tmp[1000] = {0};
            sprintf(tmp, "%d", s->cnt);
            strcat(res, tmp);
        }
    }
    return res;
}

/*
432. ȫ O(1) �����ݽṹ
�Ѷ�����57
����ʵ��һ�����ݽṹ֧�����²�����
1.	Inc(key) - ����һ���µ�ֵΪ 1 �� key������ʹһ�����ڵ� key
����һ����֤ key ��Ϊ���ַ�����
2.	Dec(key) - ������ key ��ֵ�� 1����ô���������ݽṹ����
����������ʹһ�����ڵ� key ֵ��һ�������� key �����ڣ�������������κ����顣key ��֤��Ϊ���ַ�����
3.	GetMaxKey() - ���� key ��ֵ��������һ�������û��Ԫ��
���ڣ�����һ�����ַ���"" ��
4.	GetMinKey() - ���� key ��ֵ��С������һ�������û��Ԫ��
���ڣ�����һ�����ַ���""��
*/

typedef struct date{
	int n;
	char* key;
	struct date* prev;
	struct date* next;
	UT_hash_handle hh;
} AllOne;

struct date* hashmap = NULL;
AllOne* allOneCreate() {
	struct date* obj = (struct date*)malloc(sizeof(struct date));
	struct date* tail = (struct date*)malloc(sizeof(struct date));
	obj->n = 0;
	obj->prev = tail;
	obj->next = tail;
	tail->n = INT_MAX;
	tail->prev = obj;
	tail->next = obj;
	return obj;
}

/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
void allOneInc(AllOne* obj, char * key)
{
	struct date* find = NULL;
	HASH_FIND_STR(hashmap, key, find);
	if (!find){
		find = (struct date*)malloc(sizeof(struct date));
		find->n = 1;
		find->key = key;
		find->prev = obj;
		find->next = obj->next;
		obj->next->prev = find;
		obj->next = find;
		HASH_ADD_STR(hashmap, key, find);
	} else{
		find->n++;
		while (find->n > find->next->n) {
			struct date* t = find->next;
			t->next->prev = find;
			find->prev->next = t;
			find->next = t->next;
			t->prev = find->prev;
			t->next = find;
			find->prev = t;
		}
	}
}

/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
void allOneDec(AllOne* obj, char * key)
{
	struct date* node = NULL;
	HASH_FIND_STR(hashmap, key, node);
	if (node == NULL)
		return;

	if (node->n > 1){
		node->n--;
		while (node->n < node->prev->n){
			struct date* t = node->prev;
			t->prev->next = node;
			node->next->prev = t;
			node->prev = t->prev;
			t->prev = node;
			t->next = node->next;
			node->next = t;
		}
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		HASH_DEL(hashmap, node);
		free(node);
	}
}

/** Returns one of the keys with maximal value. */
char * allOneGetMaxKey(AllOne* obj) {
	if (obj->prev->prev->n)
		return obj->prev->prev->key;

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
	HASH_ITER(hh, hashmap, current_user, tmp) {
		HASH_DEL(hashmap, current_user);
		free(current_user);
	}
	struct date *t = obj->prev;
	free(t);
    free(obj);
	obj = NULL;
}

/*
138. ���ƴ����ָ�������
����һ������ÿ���ڵ����һ���������ӵ����ָ�룬
��ָ�����ָ�������е��κνڵ��սڵ㡣
Ҫ�󷵻��������� �����
������һ���� n ���ڵ���ɵ���������ʾ����/����е���
��ÿ���ڵ���һ�� [val, random_index] ��ʾ��
val��һ����ʾ Node.val ��������
random_index�����ָ��ָ��Ľڵ���������Χ�� 0 �� n-1����
�����ָ���κνڵ㣬��Ϊ  NULL ��
ʾ�� 1��
���룺head = [[7,NULL],[13,0],[11,4],[10,2],[1,0]]
�����[[7,NULL],[13,0],[11,4],[10,2],[1,0]]
*/

typedef struct __hash_entry
{
	void *key;
	void *data;
	UT_hash_handle hh;
}hash_entry_t;

hash_entry_t *htbl = NULL;

void delete_all_htbl(void)
{
    hash_entry_t *elem, *tmp;

    HASH_ITER(hh, htbl, elem, tmp) {
        HASH_DEL(htbl,elem);
        free(elem);
    }
}

struct Node* copyRandomList(struct Node* head)
{
	struct Node* phead = head;
	struct Node* new_head = NULL;
	struct Node* prev;

	if (!head)
		return NULL;

	while (phead != NULL) {
		hash_entry_t *elem;
		struct Node *node;
		HASH_FIND_PTR(htbl, &phead, elem);
		if (elem) {
			node = (struct Node*)elem->data;
		} else {
			node = malloc(sizeof(struct Node));
			node->val = phead->val;
			elem = malloc(sizeof(hash_entry_t));
			elem->key = (void *)phead;
			elem->data = (void *)node;
			HASH_ADD_PTR(htbl, key, elem);
		}

		if (phead->random) {
			hash_entry_t *h;
			HASH_FIND_PTR(htbl, &phead->random, h);
			if (h) {
				node->random = (struct Node*)h->data;
			} else {
				struct Node* r_node = malloc(sizeof(struct Node));
				r_node->val = phead->random->val;
				node->random = r_node;
				h = malloc(sizeof(hash_entry_t));
				h->key = (void *)phead->random;
				h->data = (void *)r_node;
				HASH_ADD_PTR(htbl, key, h);
			}
		} else {
			node->random = NULL;
		}

		if (new_head == NULL) {
			new_head = node;
			prev = new_head;
		} else {
			prev->next = node;
			prev = node;
		}
		phead = phead->next;
	}

	prev->next = NULL;
	delete_all_htbl();
	return new_head;
}

/*
560. ��ΪK��������
����һ�����������һ������ k������Ҫ�ҵ��������к�Ϊ
k ��������������ĸ�����

ʾ�� 1 :

����:nums = [1,1,1], k = 2
���: 2 , [1,1] �� [1,1] Ϊ���ֲ�ͬ�������
˵�� :

����ĳ���Ϊ [1, 20,000]��
������Ԫ�صķ�Χ�� [-1000, 1000] �������� k �ķ�Χ�� [-1e7, 1e7]��
ͨ������25,598�ύ����57,201
*/
int subarraySum(int* nums, int numsSize, int k)
{
	int cnt = 0;
	int prefixSum[numsSize + 1];
	prefixSum[0] = 0;
	for (int i = 1; i <= numsSize; i++) {
		prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
	}

	for (int start = 0; start < numsSize; start++) {
		for (int end = start + 1; end <= numsSize; end++) {
			if (prefixSum[end] - prefixSum[start] == k)
				cnt++;
		}
	}

	return cnt;
}

/*
�м��� i��j ����ϣ����� prefixSum[j] - prefixSum[i - 1]==k��
ά��һ��ǰ׺��hash��ֻ�����һ�����顣ǰ׺�����飺�����i��Ԫ�ص�ǰ׺�;���a[0]+a[1]+......+a[i]����prefixSum[i]���������ŵ����������̵õ���������i��j, a[i]+.......a[j] = prefixSum[j] - prefixSum[i-1];��a[i]+.......a[j] = k; ��prefixSum[j] - prefixSum[i-1] = k;�������Ԫ��Xʱ�������prefixSum[x], ֻ��Ҫ���prefixSum[x]-k��ֵ�ڹ�ϣ�����м���ֵ��������xΪ���һ��Ԫ�ص�������ĸ������Ӷ��ڱ����������ۼӵõ������ʵ�ֹ��̰��������֣���дhash��ǰ׺�͵ļ��㡣���ߣ�dong-bei-zhang-da-shuai���ӣ�https://leetcode-cn.com/problems/subarray-sum-equals-k/solution/cyu-yan-shou-si-hashqian-zhui-he-tao-lu-si-lu-xian/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
struct hashNode {
    int key;
    int val;
    UT_hash_handle hh;
};
struct hashNode *g_users = NULL;
struct hashNode *findUser(int key) {
    struct hashNode *s;
    HASH_FIND_INT(g_users, &key, s);
    return s;
}
int getUserVal(int key) {
    struct hashNode *s;
    HASH_FIND_INT(g_users, &key, s);
    return s->val;
}
void addUser(int key) {
    struct hashNode *s;
    HASH_FIND_INT(g_users, &key, s);
    if (s == NULL) {
        struct hashNode *s = (struct hashNode *)malloc(sizeof(struct hashNode));
        s->key = key;
        s->val = 1;
        HASH_ADD_INT(g_users, key, s);
    } else {
        s->val++;
    }
}
int subarraySum(int* nums, int numsSize, int k){
    int sum = 0, cnt = 0;
    g_users = NULL;
    addUser(0);
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (findUser(sum - k)) {
            cnt += getUserVal(sum-k);
        }
        addUser(sum);
    }
    return cnt;
}

/*
525. ��������
����һ������������, �ҵ�������ͬ������ 0 �� 1 ������������飨�ĳ��ȣ���



ʾ�� 1:

����: [0,1]
���: 2
˵��: [0, 1] �Ǿ�����ͬ����0��1������������顣
ʾ�� 2:

����: [0,1,0]
���: 2
˵��: [0, 1] (�� [1, 0]) �Ǿ�����ͬ����0��1������������顣
*/
typedef struct _hash_st {
	int key;
	int sumValueFirstIdx;
	UT_hash_handle hh;
}hash_st;

//���㷨˼·������+hash�������01���⣬��0ת��Ϊ-1��
// ����ת��Ϊ������к�Ϊ0,ʹ��hash�����
int findMaxLength(int* nums, int numsSize)
{
    if(numsSize <= 1) {
        return 0;
    }

    hash_st *hashmap = NULL;
    int max = 0;

    //0 -> -1 && ���� && ����hash
    int sum = 0;
    for(int i = 0; i < numsSize; i++) {
        //0ת-1������
        sum += nums[i] == 0? -1 : 1;

        if(sum == 0) {
            //��sumΪ0��ֱ��Ϊ���
            max = fmax(max, i + 1);
        } else {
            int target = sum;

            hash_st *find = NULL;
            //HASH_FIND(hh, hashmap, &key, sizeof(key), find);
            HASH_FIND_INT(hashmap, &target, find);
            if(find == NULL) {
                find = (hash_st *)calloc(1, sizeof(hash_st));
                find->key = target;
                find->sumValueFirstIdx = i;

                //HASH_ADD_KEYPTR(hh, hashmap, &find->key, sizeof(find->key), find);
                HASH_ADD_INT(hashmap, key, find);
            } else {
		max = fmax(max, i - find->sumValueFirstIdx);
	}
        }
    }

    return max;
}

/*
������ 17.18. ��̳���
�Ѷ��е�5
���������������飬һ����һ���̣��̵�Ԫ�ؾ�����ͬ����
���������а������������е�Ԫ�ص���������飬�����˳
���޹ؽ�Ҫ��
����������������˵���Ҷ˵㣬���ж��������������
���飬������˵���С��һ�����������ڣ����ؿ����顣
ʾ�� 1:
����:
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
���: [7,10]
ʾ�� 2:
����:
big = [1,2,3]
small = [4]
���: []
*/

struct Hashmap {
	int key;
	int cnt;
	UT_hash_handle hh;
};

int* shortestSeq(int* big, int bigSize, int* small, int smallSize, int* returnSize)
{
	if (big == NULL || small == NULL || bigSize <= 0 || smallSize <= 0 || smallSize > bigSize) {
		*returnSize = 0;
		return NULL;
	}

	struct Hashmap *hashmap = NULL;

	for (int i = 0; i < smallSize; i++) {
		struct Hashmap *node = (struct Hashmap *)calloc(1, sizeof(struct Hashmap));
		node->key = small[i];
		HASH_ADD_INT(hashmap, key, node);
	}

	int left = 0, right = 0, winCnt = 0, minLen= INT_MAX;
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	while(right < bigSize) {
		struct Hashmap *find = NULL;
		HASH_FIND_INT(hashmap, big + right, find);
		if(find != NULL) {
			if (find->cnt == 0) {
				winCnt++;
			}

			find->cnt++;
		}

		while(winCnt == smallSize) {
			struct Hashmap *findleft = NULL;
			HASH_FIND_INT(hashmap, big + left, findleft);
			if (findleft == NULL) {
				left++;
			} else if (findleft->cnt > 1) {
				findleft->cnt--;
				left++;
			} else {//cnt == 1
				if (minLen > right-left + 1) {
					minLen = right-left + 1;
					res[0] = left;
					res[1] = right;
				}

				findleft->cnt--;
				left++;
				winCnt--;
			}
		}

		right++;
	}

	if (minLen == INT_MAX) {
		*returnSize = 0;
		return NULL;
	}

	return res;
}

/*
������ 17.07. Ӥ������
�Ѷ��е�0
ÿ�꣬�������ṫ��һ��������Ӥ�����ֺ����ǳ���
��Ƶ�ʣ�Ҳ����ͬ��Ӥ������������Щ�����ж���ƴ����
���磬John �� Jon ����������ͬ�����֣�������������������
�������������������б�һ�������ּ���Ӧ��Ƶ�ʣ�
��һ���Ǳ�����ͬ�����ֶԡ����һ���㷨��ӡ��ÿ��
��ʵ���ֵ�ʵ��Ƶ�ʡ�ע�⣬��� John �� Jon ����ͬ�ģ�
���� Jon �� Johnny ��ͬ���� John �� Johnny Ҳ��ͬ���������д���
�ͶԳ��ԡ�
�ڽ���б��У�ѡ���ֵ�����С��������Ϊ��ʵ���֡�
ʾ����
���룺
names = ["John(15)","Jon(12)","Chris(13)","Kris(4)","Christopher(19)"],
synonyms = ["(Jon,John)","(John,Johnny)","(Chris,Kris)","(Chris,Christopher)"]
�����["John(27)","Chris(36)"]

*/
#define MAX 101
typedef struct {
	char name[MAX];
	int index;
	int count;
	UT_hash_handle hh;
} Hashmap;

struct UnionFind {
	int edgeCnt;
	int *root;
	int *rank;
};

void uf_init(struct UnionFind *uf, size_t size)
{
	uf->edgeCnt = size;
	uf->root = (int *)calloc(size, sizeof(int));
	uf->rank = (int *)calloc(size, sizeof(int));
	memset(uf->rank, 0, sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		uf->root[i] = i;
	}
}

int uf_findRoot(struct UnionFind* uf, int sun)
{
	if (sun == uf->root[sun]) {
		return sun;
	}

        return uf->root[sun] = uf_findRoot(uf, uf->root[sun]);
}

bool uf_isOneUnion(struct UnionFind* uf, int sun0, int sun1)
{
	 return uf_findRoot(uf, sun0) == uf_findRoot(uf, sun1);
}

void uf_union(struct UnionFind* uf, Hashmap *sun0, Hashmap *sun1)
{
	if (sun0 == NULL || sun1 == NULL) {
		return;
	}

	int root1 = uf_findRoot(uf, sun0->index);
	int root2 = uf_findRoot(uf, sun1->index);
	if (root1 == root2) {
		return;
	}

	if (strcmp(sun0->name, sun1->name) < 0) { //���ӱߣ��ֵ���С����Ϊ���ڵ�
		uf->root[root2] = root1;
	} else {
		uf->root[root1] = root2;
	}
}

int cmp_str (Hashmap *p1, Hashmap *p2)
{
	return strcmp(p1->name, p2->name);
}

char** trulyMostPopular(char** names, int namesSize, char** synonyms, int synonymsSize, int* returnSize)
{
	Hashmap *hashmap = NULL;
	Hashmap *node;

	for (int i = 0; i < namesSize; i++) {
		node = malloc(sizeof(Hashmap));
		char *split;
		split = strtok(names[i], "(");
		strcpy(node->name, split);
		split = strtok(NULL, ")");
		node->count = atoi(split);
		node->index = i;
		HASH_ADD_STR(hashmap, name, node);
	}

	HASH_SORT(hashmap, cmp_str);

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, namesSize);

	for (int i = 0; i < synonymsSize; i++) {
		Hashmap *names1, *names2;
		char *split;
		split = strtok(synonyms[i], "(,");
		HASH_FIND_STR(hashmap, split, names1);
		split = strtok(NULL, ")");
		HASH_FIND_STR(hashmap, split, names2);
		uf_union(uf, names1, names2);
	}

	Hashmap *newChildMap = NULL;
	Hashmap *newNode, *temp;
	HASH_ITER(hh, hashmap, node, temp) {
		int rootIndex = uf_findRoot(uf, node->index);

		HASH_FIND_INT(newChildMap, &rootIndex, newNode); // �����Ϊ��ֵ���½���ϣ��
		if (newNode == NULL) {
			newNode = malloc(sizeof(Hashmap));
			newNode->count = node->count;
			newNode->index = rootIndex;
			strcpy(newNode->name, node->name);
			HASH_ADD_INT(newChildMap, index, newNode);
		} else {
			newNode->count += node->count;
		}
	}

	char **strRes = malloc(HASH_COUNT(newChildMap) * sizeof(char *));

	int index = 0;
	HASH_ITER(hh, newChildMap, newNode, temp) {
		strRes[index] = malloc(MAX);
		sprintf(strRes[index], "%s(%d)", newNode->name, newNode->count);
		index++;
	}

	*returnSize = index;

	return strRes;
}

