/*
454. 四数相加 II
给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组
(i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。
为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且
0 ≤ N ≤ 500 。所有整数的范围在 -228 到 228 - 1 之间，最终结果
不会超过 231 - 1 。
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
面试题 16.21. 交换和
难度中等5
给定两个整数数组，请交换一对数值（每个数组中取一个数
值），使得两个数组所有元素的和相等。
返回一个数组，第一个元素是第一个数组中要交换的元素，
第二个元素是第二个数组中要交换的元素。若有多个答案，
返回任意一个均可。若无满足条件的数值，返回空数组。
示例:
输入: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
输出: [1, 3]
示例:
输入: array1 = [1, 2, 3], array2 = [4, 5, 6]
输出: []
*/
/*
先求两个数组的差值diff = sum(a)-sum(b), 如果为奇数直接return [], 因为
交换任何数得到的diff一定是两个数字差值的2倍
然后将数组b作为集合, 遍历数组a, 判断其每个元素-diff//2是否
在b集合中, 在的话即为所求
交换的两个数的差值一定是2d = (sum(A) - sum(B))
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
820. 单词的压缩编码
难度中等165
给定一个单词列表，我们将这个列表编码成一个索引字符串
S 与一个索引列表 A。
例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示
为 S = "time#bell#" 和 indexes = [0, 2, 5]。
对于每一个索引，我们可以通过从字符串 S 中索引的位置开
始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。
那么成功对给定单词列表进行编码的最小字符串长度是多少
呢？
示例：
输入: words = ["time", "me", "bell"]
输出: 10
说明: S = "time#bell#" ， indexes = [0, 2, 5] 。
提示：
1.	1 <= words.length <= 2000
2.	1 <= words[i].length <= 7
3.	每个单词都是小写字母 。
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
	for (i = 0; i < 60000; i++){
		maxGap = fmax(maxGap, xgap[i]);
	}

    return wallSize - maxGap;
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
int countPrimes(int n)
{
	int count = 0;
	if (n == 0) {
		return 0;
	}

	bool map[n];
	//初始默认所有数为质数
	for (int i = 0; i < n; i++) {
		map[i] = true;
	}

	for (int i = 2; i < n; i++) {
		if (map[i]) {
			count++;
			for (int j = i + i; j < n; j += i) {
				//排除不是质数的数
				map[j] = false;
			}
		}
	}

	return count;
}

/*
290. 单词规律
给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:

输入: pattern = "abba", str = "dog cat cat dog"
输出: true
示例 2:

输入:pattern = "abba", str = "dog cat cat fish"
输出: false
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
219. 存在重复元素 II
给定一个整数数组和一个整数 k，判断数组中是否存在两个不
同的索引 i 和 j，使得 nums [i] = nums [j]，并且 i 和 j 的差的 绝对值 至
多为 k。
示例 1:
输入: nums = [1,2,3,1], k = 3
输出: true
示例 2:
输入: nums = [1,0,1,1], k = 1
输出: true
示例 3:
输入: nums = [1,2,3,1,2,3], k = 2
输出: false
*/
typedef struct hash{
    int key;  // 键
    int index;  // 索引值
    UT_hash_handle hh; // 让结构体哈希柄
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
594. 最长和谐子序列
和谐数组是指一个数组里元素的最大值和最小值之间的差别正好是1。

现在，给定一个整数数组，你需要在所有可能的子序列中找到最长的和谐子序列的长度。

示例 1:

输入: [1,3,2,2,5,2,3,7]
输出: 5
原因: 最长的和谐数组是：[3,2,2,2,3].
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
652. 寻找重复的子树
给定一棵二叉树，返回所有重复的子树。对于同一类的重复子
树，你只需要返回其中任意一棵的根结点即可。
两棵树重复是指它们具有相同的结构以及相同的结点值。
示例 1：

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
下面是两个重复的子树：

      2
     /
    4
和

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
726. 原子的数量
给定一个化学式formula（作为字符串），返回每种原子的数量。
原子总是以一个大写字母开始，接着跟随0个或任意个小写字
母，表示原子的名字。
如果数量大于 1，原子后会跟着数字表示原子的数量。如果
数量等于 1 则不会跟数字。例如，H2O 和 H2O2 是可行的，但
H1O2 这个表达是不可行的。
两个化学式连在一起是新的化学式。例如 H2O2He3Mg4 也是化学
式。
一个括号中的化学式和数字（可选择性添加）也是化学式。
例如 (H2O2) 和 (H2O2)3 是化学式。
给定一个化学式，输出所有原子的数量。格式为：第一个（
按字典序）原子的名子，跟着它的数量（如果数量大于 1），
然后是第二个原子的名字（按字典序），跟着它的数量（如
果数量大于 1），以此类推。
示例 1:
输入:
formula = "H2O"
输出: "H2O"
解释:
原子的数量是 {'H': 2, 'O': 1}。
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
        sum = 1;  /* 这个地方可能get不到数字，那就是1倍，但长度要返回0 */
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
                stack1[top1++] = ch;  /* push进stack1 */
                ch = stack[--top];    /* 从stack中继续pop */
            }
            Name ch1 = {0};
            if (top > 0) {
                while (top1 > 0) {  /* 如果stack中还有字符，继续push进stack */
                    ch1 = stack1[--top1];
                    stack[top++] = ch1;
                }
            } else {
                while (top1 > 0) { /* 如果stack没有字符，直接保存 */
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
    HASH_SORT(map, Cmp); /* 将hash表排序然后输出 */
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
432. 全 O(1) 的数据结构
难度困难57
请你实现一个数据结构支持以下操作：
1.	Inc(key) - 插入一个新的值为 1 的 key。或者使一个存在的 key
增加一，保证 key 不为空字符串。
2.	Dec(key) - 如果这个 key 的值是 1，那么把他从数据结构中移
除掉。否则使一个存在的 key 值减一。如果这个 key 不存在，这个函数不做任何事情。key 保证不为空字符串。
3.	GetMaxKey() - 返回 key 中值最大的任意一个。如果没有元素
存在，返回一个空字符串"" 。
4.	GetMinKey() - 返回 key 中值最小的任意一个。如果没有元素
存在，返回一个空字符串""。
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
138. 复制带随机指针的链表
给定一个链表，每个节点包含一个额外增加的随机指针，
该指针可以指向链表中的任何节点或空节点。
要求返回这个链表的 深拷贝。
我们用一个由 n 个节点组成的链表来表示输入/输出中的链
表。每个节点用一个 [val, random_index] 表示：
val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；
如果不指向任何节点，则为  NULL 。
示例 1：
输入：head = [[7,NULL],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,NULL],[13,0],[11,4],[10,2],[1,0]]
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
560. 和为K的子数组
给定一个整数数组和一个整数 k，你需要找到该数组中和为
k 的连续的子数组的个数。

示例 1 :

输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
说明 :

数组的长度为 [1, 20,000]。
数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。
通过次数25,598提交次数57,201
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
有几种 i、j 的组合，满足 prefixSum[j] - prefixSum[i - 1]==k。
维护一个前缀和hash表，只需遍历一次数组。前缀和数组：数组第i个元素的前缀和就是a[0]+a[1]+......+a[i]记作prefixSum[i]，可以随着迭代遍历过程得到。则任意i，j, a[i]+.......a[j] = prefixSum[j] - prefixSum[i-1];若a[i]+.......a[j] = k; 则prefixSum[j] - prefixSum[i-1] = k;设遍历到元素X时，计算出prefixSum[x], 只需要求出prefixSum[x]-k的值在哈希表中有几个值，就是以x为最后一个元素的子数组的个数。从而在遍历过程中累加得到结果。实现过程包括两部分：手写hash，前缀和的计算。作者：dong-bei-zhang-da-shuai链接：https://leetcode-cn.com/problems/subarray-sum-equals-k/solution/cyu-yan-shou-si-hashqian-zhui-he-tao-lu-si-lu-xian/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
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
525. 连续数组
给定一个二进制数组, 找到含有相同数量的 0 和 1 的最长连续子数组（的长度）。



示例 1:

输入: [0,1]
输出: 2
说明: [0, 1] 是具有相同数量0和1的最长连续子数组。
示例 2:

输入: [0,1,0]
输出: 2
说明: [0, 1] (或 [1, 0]) 是具有相同数量0和1的最长连续子数组。
*/
typedef struct _hash_st {
	int key;
	int sumValueFirstIdx;
	UT_hash_handle hh;
}hash_st;

//【算法思路】积分+hash。经典的01问题，将0转化为-1。
// 问题转换为最长子序列和为0,使用hash表求解
int findMaxLength(int* nums, int numsSize)
{
    if(numsSize <= 1) {
        return 0;
    }

    hash_st *hashmap = NULL;
    int max = 0;

    //0 -> -1 && 积分 && 填入hash
    int sum = 0;
    for(int i = 0; i < numsSize; i++) {
        //0转-1并积分
        sum += nums[i] == 0? -1 : 1;

        if(sum == 0) {
            //当sum为0则直接为结果
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
面试题 17.18. 最短超串
难度中等5
假设你有两个数组，一个长一个短，短的元素均不相同。找
到长数组中包含短数组所有的元素的最短子数组，其出现顺
序无关紧要。
返回最短子数组的左端点和右端点，如有多个满足条件的子
数组，返回左端点最小的一个。若不存在，返回空数组。
示例 1:
输入:
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
输出: [7,10]
示例 2:
输入:
big = [1,2,3]
small = [4]
输出: []
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
面试题 17.07. 婴儿名字
难度中等0
每年，政府都会公布一万个最常见的婴儿名字和它们出现
的频率，也就是同名婴儿的数量。有些名字有多种拼法，
例如，John 和 Jon 本质上是相同的名字，但被当成了两个名字
公布出来。给定两个列表，一个是名字及对应的频率，
另一个是本质相同的名字对。设计一个算法打印出每个
真实名字的实际频率。注意，如果 John 和 Jon 是相同的，
并且 Jon 和 Johnny 相同，则 John 与 Johnny 也相同，即它们有传递
和对称性。
在结果列表中，选择字典序最小的名字作为真实名字。
示例：
输入：
names = ["John(15)","Jon(12)","Chris(13)","Kris(4)","Christopher(19)"],
synonyms = ["(Jon,John)","(John,Johnny)","(Chris,Kris)","(Chris,Christopher)"]
输出：["John(27)","Chris(36)"]

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

	if (strcmp(sun0->name, sun1->name) < 0) { //连接边，字典序小的作为根节点
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

		HASH_FIND_INT(newChildMap, &rootIndex, newNode); // 以序号为键值，新建哈希表
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

