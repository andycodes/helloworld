/*
211. ������������� - ���ݽṹ���
�Ѷ��е�142
���һ��֧���������ֲ��������ݽṹ��
void addWord(word)
bool search(word)
search(word) �����������ֻ�������ʽ�ַ������ַ���ֻ������ĸ . �� a-z �� . ���Ա�ʾ�κ�һ����ĸ��
ʾ��:
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
˵��:
����Լ������е��ʶ�����Сд��ĸ a-z ��ɵġ�

*/

typedef struct trieNode{
	int prefix;
	int count;
	struct trieNode* next[26];
} WordDictionary;

/** Initialize your data structure here. */

WordDictionary* wordDictionaryCreate() {
	return (WordDictionary*)calloc(1, sizeof(WordDictionary));
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary* obj, char * word) {
	struct trieNode *root = obj;
	char *str = word;
	int slen = strlen(str);
	if(root == NULL||slen == 0) {
		return;
	}

	for(int i = 0;i < slen; i++) {
		if(root->next[str[i]-'a'] == NULL) {
			root->next[str[i]-'a'] = (struct trieNode*)calloc(1, sizeof(struct trieNode));
		}
		root = root->next[str[i]-'a'];
		root->prefix++;
	}

	//�Ըýڵ��β�ĵ�����+1
	root->count++;

}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary* obj, char * word) {
    /* �����㷨������.�Ž��б������� */
    while (*word) {
        if (*word != '.' && !obj->next[(*word)-97]) return false;  // ��ƥ���Ҳ���.һ��Ϊ��
        else if (*word == '.') {  // ��.�Ž���26��ĸ��������
            for (int i = 0; i < 26; i++) {
                if (obj->next[i] && wordDictionarySearch(obj->next[i], word+1))
                    return true;  // ֻҪһ��Ϊ�漴�ɣ�������
            }
            return false;  // ����26�����꣬��û�ҵ���һ��Ϊ��
        }
        obj = obj->next[(*word++)-97];  // ��������ƥ��obj�����Ľ���
    }
    return !!obj->count;  // ����ַ������ˣ���Ҫ�ж��ֵ����ڴ˽ڵ����Ƿ��и�bool��ǽ���
}


void wordDictionaryFree(WordDictionary* obj) {
	if (obj == NULL)
		return;

	for (int i = 0; i < 26; i++) {
		if (obj->next[i] != NULL) {
			wordDictionaryFree(obj->next[i] );
		}
	}

	free(obj);
}

/*
676. ʵ��һ��ħ���ֵ�
�Ѷ��е�54
ʵ��һ������buildDict, �Լ� search������ħ���ֵ䡣
����buildDict�������㽫������һ�����ظ��ĵ���������һ���ֵ䡣
����search�������㽫������һ�����ʣ������ж��ܷ�ֻ�����������һ����ĸ������һ����ĸ��ʹ�����γɵ��µ��ʴ������㹹�����ֵ��С�
ʾ�� 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
ע��:
1.	����Լ����������붼��Сд��ĸ a-z��
2.	Ϊ�˱��ھ������������õ���������С��������ھ��������󣬿��Ǹ���Ч���㷨��
3.	���ס����MagicDictionary�������������������Ϊ��̬/��������ڶ�����������б����� ����������˽�������顣

*/
#define MAX_LETTER 26

typedef struct trie{
    struct trie* next[MAX_LETTER];
    bool isEnd;
} MagicDictionary;

/** Initialize your data structure here. */
MagicDictionary* magicDictionaryCreate() {
    MagicDictionary *node = (MagicDictionary*)calloc(1, sizeof(MagicDictionary));
    return node;
}

/** Build a dictionary through a list of words */
void magicDictionaryBuildDict(MagicDictionary* obj, char** dict, int dictSize) {
    MagicDictionary *node = NULL;
    for (int i = 0; i < dictSize; i++) {
        node = obj;
        for (int j = 0; dict[i][j] != '\0'; j++) {
            char c = dict[i][j];
            if (node->next[c - 'a'] == NULL) {
                node->next[c - 'a'] = magicDictionaryCreate();
            }

            node = node->next[c - 'a'];
        }
        node->isEnd = true;
    }
}

/* ����ʣ�µ�word��ʣ�µ��ֵ����Ƿ�ƥ�� */
bool checkLeftWord(MagicDictionary* obj, char* leftWord)
{
    MagicDictionary* leftNode = obj;
    for (int i = 0; leftWord[i] != '\0'; i++) {
        char c = leftWord[i];
        if (leftNode->next[c - 'a'] == NULL) {
            return false;
        }

        leftNode = leftNode->next[c - 'a'];
    }

    return leftNode->isEnd;
}

/** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
bool magicDictionarySearch(MagicDictionary* obj, char* word)
{
    MagicDictionary* node = obj;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        /* ÿ����ĸ����һ��ȥ��������������Ƿ�һ�� */
        for (int j = 0; j < 26; j++) {
            if (node->next[j] != NULL && j != word[i] - 'a') {
                if (checkLeftWord(node->next[j], word + i + 1) == true) {
                    return true;
                }
            }
        }

        /* ֻ���滻һ�εĻ���, �´��ٲ�һ�����˳� */
        if (node->next[c - 'a'] == NULL) {
            break;
        }

        node = node->next[c - 'a'];
    }

    return false;
}

void magicDictionaryFree(MagicDictionary* obj)
{
    MagicDictionary *node = obj;
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < MAX_LETTER; i++) {
        if (node->next[i] != NULL) {
            magicDictionaryFree(node->next[i]);
        }
    }

    free(node);
}

/*
421. ��������������������ֵ
�Ѷ��е�150
����һ���ǿ����飬������Ԫ��Ϊ a0, a1, a2, �� , an-1������
0 �� ai < 231 ��
�ҵ� ai ��aj ������� (XOR) ������������0 �� i,  j < n ��
������O(n)��ʱ�������������
ʾ��:
����: [3, 10, 5, 25, 2, 8]
���: 28
����: ���Ľ���� 5 ^ 25 = 28.
*/

/*
0 ��������� x ��������� x ����
���a��b����ֵ��ͬ�������Ϊ0
�ֵ�����ÿ�����ڵ㵽Ҷ�ڵ��·���������� nums �е�
һ����������������ʽ��
�ֵ����ǳ��ʺ������洢�����Ķ�������ʽ
�ֵ����и�������������ֵ
Ϊ��������ֵ����Ҫ��ÿһ���ҵ���ǰ����ֵ�Ļ���
����ֵ
�����ǰ����ֵ���ڻ�������ֵ�����ʾ��л�������ֵ�ĺ�
�ӽڵ㣬�������ֵ���Ҳ฽��һ�� 1��
��������ڣ�ֱ�ӷ��ʾ��е�ǰ����ֵ�ĺ��ӽڵ㣬������
��ֵ���Ҳ฽��һ�� 0��
*/
struct trieNode {
	int prefix;
	int end;
	int val;
	struct trieNode *child[2];
};

    void insert(struct trieNode *root, int* nums, int numsSize) {
        for (int i = 0; i < numsSize; ++ i) {
            struct trieNode* cur = root;
            for (int j = 31; j >= 0; -- j) {
                int index = (nums[i] >> j) & 1;
                if (cur->child[index] == NULL)
                    cur->child[index] = (struct trieNode *)calloc(1, sizeof(struct trieNode));
                cur = cur->child[index];
            }
            cur->val = nums[i];
        }
    }

    int search(struct trieNode *root, int* nums, int numsSize)
{
        int res = 0;
        for (int i = 0; i < numsSize; ++ i) {
            struct trieNode* cur = root;
            for (int j = 31; j >= 0; -- j) {
                int index = (nums[i] >> j) & 1;
                int orindex = 1 - index;
                if (cur->child[orindex] != NULL)
                    cur = cur->child[orindex];
                else
                    cur = cur->child[index];
            }
            res = fmax(res, nums[i] ^ (cur->val));
        }
        return res;
}

int findMaximumXOR(int* nums, int numsSize)
{
	struct trieNode *root = (struct trieNode *)calloc(1, sizeof(struct trieNode));
	insert(root, nums, numsSize);
	return search(root, nums, numsSize);
}

/*
336. ���Ķ�
����һ�� ������ͬ �ĵ��ʣ� �ҳ����в�ͬ ��������(i, j)��ʹ
���б��е��������ʣ� words[i] + words[j] ����ƴ�ӳɻ��Ĵ���
ʾ�� 1��
���룺["abcd","dcba","lls","s","sssll"]
�����[[0,1],[1,0],[3,2],[2,4]]
���ͣ���ƴ�ӳɵĻ��Ĵ�Ϊ ["dcbaabcd","abcddcba","slls","llssssll"]
*/

struct node {
    int ch[26];
    int flag;
} tree[100001];
int tree_len;

void reset(struct node* p) {
    memset(p->ch, 0, sizeof(int) * 26);
    p->flag = -1;
}

void insert(char* s, int id) {
    int len = strlen(s), add = 0;
    for (int i = 0; i < len; i++) {
        int x = s[i] - 'a';
        if (!tree[add].ch[x]) {
            tree_len++;
            reset(&tree[tree_len - 1]);
            tree[add].ch[x] = tree_len - 1;
        }
        add = tree[add].ch[x];
    }
    tree[add].flag = id;
}

int findWord(char* s, int left, int right)
{
	int add = 0;
	for (int i = right; i >= left; i--) {
		int x = s[i] - 'a';
		if (!tree[add].ch[x]) {
			return -1;
		}
		add = tree[add].ch[x];
	}
	return tree[add].flag;
}

bool isPalindrome(char* s, int left, int right)
{
	int len = right - left + 1;
	for (int i = 0; i < len / 2; i++) {
		if (s[left + i] != s[right - i]) {
			return false;
		}
	}
	return true;
}

int** palindromePairs(char** words, int wordsSize, int* returnSize, int** returnColumnSizes)
{
	reset(&tree[0]);
	tree_len = 1;
	for (int i = 0; i < wordsSize; i++) {
		insert(words[i], i);
	}

	int** ret = malloc(sizeof(int*) * 10001);
	(*returnColumnSizes) = malloc(sizeof(int) * 10001);
	for (int i = 0; i < 10001; i++) {
		ret[i] = malloc(sizeof(int) * 2);
		(*returnColumnSizes)[i] = 2;
	}

	int ret_len = 0;
	for (int i = 0; i < wordsSize; i++) {
		int m = strlen(words[i]);
		for (int j = 0; j <= m; j++) {
			if (isPalindrome(words[i], j, m - 1)) {
				int left_id = findWord(words[i], 0, j - 1);
				if (left_id != -1 && left_id != i) {
					ret_len++;
					ret[ret_len - 1][0] = i;
					ret[ret_len - 1][1] = left_id;
				}
			}

			if (j && isPalindrome(words[i], 0, j - 1)) {
				int right_id = findWord(words[i], j, m - 1);
				if (right_id != -1 && right_id != i) {
					ret_len++;
					ret[ret_len - 1][0] = right_id;
					ret[ret_len - 1][1] = i;
				}
			}
		}
	}

	(*returnSize) = ret_len;
	return ret;
}

/*
212. �������� II
����һ����ά���� board ��һ���ֵ��еĵ����б� words���ҳ�
����ͬʱ�ڶ�ά������ֵ��г��ֵĵ��ʡ�
���ʱ��밴����ĸ˳��ͨ�����ڵĵ�Ԫ���ڵ���ĸ���ɣ�
���С����ڡ���Ԫ������Щˮƽ���ڻ�ֱ���ڵĵ�Ԫ��
ͬһ����Ԫ���ڵ���ĸ��һ�������в������ظ�ʹ�á�
ʾ��:
����:
words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
���: ["eat","oath"]
˵��:
����Լ����������붼��Сд��ĸ a-z ��ɡ�
*/

typedef struct TrieNode{
	bool isEnd;
	struct TrieNode* map[26];
} Trie;

Trie* trieCreate()
{
	Trie *obj = (Trie *)malloc(sizeof(Trie));
	obj->isEnd = false;

	for (int i = 0; i < 26; i++)
		obj->map[i] = NULL;

	return obj;
}

void trieInsert(Trie* obj, char * word)
{
	int len = strlen(word);

	for (int i = 0; i < len; i++) {
		if (obj->map[word[i] - 'a'] == NULL)
			obj->map[word[i] - 'a'] = trieCreate();

		obj = obj->map[word[i] - 'a'];
	}

	obj->isEnd = true;
}

bool trieSearch(Trie* obj, char * word)
{
	for (int i = 0; word[i]; i++) {
		if (obj->map[word[i] - 'a'] == NULL)
			return false;

		obj = obj->map[word[i] - 'a'];
	}

/* ����ط��и�*С�Ķ�*��ÿ��������һ�����ʣ��Ͱ�������ʴ� */
/* ǰ׺����ɾ�����ѽ������Ľ�����־ȡ���������������Ա����ظ� */
	if (obj->isEnd) {
		obj->isEnd = false;
		return true;
	}
	return false;
}

bool trieStartsWith(Trie* obj, char * prefix)
{
	for (int i = 0; prefix[i]; i++) {
		if (obj->map[prefix[i] - 'a'] == NULL)
			return false;

		obj = obj->map[prefix[i] - 'a'];
	}

	return true;
}

void trieFree(Trie* obj) {
    for (int i = 0; i < 26; i++)
        if (obj->map[i] != NULL)
            trieFree(obj->map[i]);

    free(obj);
}

/* ����һЩȫ�ֱ�������Ȼ��������ڲ�����ܶ� */
bool visited[500][500];
int row, col;
char *prefix;
Trie* trieTree;

/* ��ڲ���"pos"����������prefix�� */
void traceBack(int r, int c, int pos, char **board, int* returnSize, char **res)
{
/* ��ǰ׺���ɵĵ������ֵ����еĵ��ʣ���prefix��ӵ�res�� */
	if (trieSearch(trieTree, prefix)) {
		res[*returnSize] = malloc(sizeof(char) * (strlen(prefix) + 1));
		strcpy(res[(*returnSize)++], prefix);
	}

    int dr[] = {1, 0, -1, 0};       /* dr,dc���鹲ͬ��ɵ�����¡����ҡ����ϡ����� */
    int dc[] = {0, 1, 0, -1};
    int di = 0;                     /* diΪ��������� */
    visited[r][c] = true;              /* �����ڣ�r��c������㣬��visited[r][c]��Ϊtrue */

    for (int di = 0; di < 4; di++) {
        int rr = r + dr[di];
        int cc = c + dc[di];
        if (rr >= 0 && rr < row && cc >= 0 && cc < col && !visited[rr][cc]) {
            prefix[pos] = board[rr][cc];
            if (trieStartsWith(trieTree, prefix))
                traceBack(rr, cc, pos + 1, board, returnSize, res);
        }

    }

/* ���ݷ��ǳ���Ҫ��һ������һ���ͽ�״̬��ԭΪԭ�������� */
    prefix[pos] = '\0';
    visited[r][c] = false;
    return;
}

char ** findWords(char** board, int boardSize, int* boardColSize,
	char ** words, int wordsSize, int* returnSize)
{
	row = boardSize, col = *boardColSize;

	memset(visited, 0, sizeof(visited));
	char **res = (char **)malloc(sizeof(char *) * wordsSize);
	*returnSize = 0;

	trieTree = (Trie *)malloc(sizeof(Trie));
	trieTree->isEnd = false;

	for (int i = 0; i < 26; i++)
		trieTree->map[i] = NULL;

	for (int i = 0; i < wordsSize; i++)
		trieInsert(trieTree, words[i]);

/*
* prefixΪ���������й��ɵ�ǰ׺��ÿ����һ����prefix����һ��
* ����prefix���Է��������ǰ׺������غ������м�֦
*/
	prefix = (char *)calloc(sizeof(char), row * col + 1);

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++) {
			prefix[0] = board[i][j];

			if (trieStartsWith(trieTree, prefix) == false)
				continue;

			traceBack(i, j, 1, board, returnSize, res);
	}

	trieFree(trieTree);

	return res;
}


/*
425. ���ʷ���
����һ�����ʼ��� ��û���ظ������ҳ��������е� ���ʷ��� ��
һ�����������γ���һ����Ч�ĵ��ʷ������˼��ָ�ӵ� k ��
�͵� k �� (0 �� k < max(����, ����)) ����������ͬ���ַ�����

���磬�������� ["ball","area","lead","lady"] �γ���һ�����ʷ��飬��Ϊ
ÿ�����ʴ�ˮƽ���򿴺ʹ���ֱ���򿴶�����ͬ�ġ�
b a l l
a r e a
l e a d
l a d y
ע�⣺
���ʸ������ڵ��� 1 �Ҳ����� 500��
���еĵ��ʳ��ȶ���ͬ��
���ʳ��ȴ��ڵ��� 1 �Ҳ����� 5��
ÿ������ֻ����СдӢ����ĸ a-z��
*/

struct TrieNode {
    bool isEnd;
    struct TrieNode *next[26];
};

inline struct TrieNode *getNode()
{
	struct TrieNode *ret = (struct TrieNode *)malloc(sizeof(struct TrieNode));
	ret->isEnd = false;
	memset(ret->next, 0, sizeof(ret->next));
	return ret;
}

inline void insert(struct TrieNode *dest, char *val)
{
    if (dest == NULL)
        return;
    while (*val)
    {
        if (dest->next[*val - 'a'] == NULL)
            dest->next[*val - 'a'] = getNode();
        dest = dest->next[*(val++) - 'a'];
    }
    dest->isEnd = true;
}
inline bool havePrefix(struct TrieNode *dest, char *val)
{
    while (*val && dest)
        dest = dest->next[*(val++) - 'a'];
    if (dest == NULL)
        return NULL;
    bool ret = dest->isEnd;
    for (int i = 0; !ret && i < 26; i++)
        ret = ret || dest->next[i] != NULL;
    return ret;
}

void dfs(struct TrieNode *wordsTree, struct TrieNode *result,
    char ****ret, int *returnSize, int *maxSize, char **curGrid, int curX, int curY, int len)
{
	int i = 0, j = 0;
	bool flag = false;

	if (curX == len) {
		if (*returnSize == *maxSize - 1)
		*ret = (char ***)realloc(*ret, sizeof(char **) * (*maxSize *= 2));
		(*ret)[*returnSize] = (char **)malloc(sizeof(char *) * len);
		for (i = 0; i < len; i++)
		{
		(*ret)[*returnSize][i] = (char *)malloc(sizeof(char) * (len + 1));
		strcpy((*ret)[*returnSize][i], curGrid[i]);
		}
		(*returnSize)++;
		return;
	}
	for (i = 0; i < 26; i++, flag = false)
	{
	curGrid[curX][curY] = (char)i + 'a';
	curGrid[curY][curX] = (char)i + 'a';
	for (j = 0; !flag && j < len; j++)
	flag = flag || !havePrefix(wordsTree, curGrid[j]);
	if (!flag)
	{
	if (curY < len - 1)
	dfs(wordsTree, result, ret, returnSize, maxSize, curGrid, curX, curY + 1, len);
	else
	dfs(wordsTree, result, ret, returnSize, maxSize, curGrid, curX + 1, curX + 1, len);
	}
	curGrid[curX][curY] = 0;
	curGrid[curY][curX] = 0;
	}
}

char *** wordSquares(char ** words, int wordsSize, int* returnSize, int** returnColumnSizes)
{
	int i = 0, len = strlen(words[0]), maxSize = 1;
	struct TrieNode *wordTree = getNode(), *resultTree = getNode();
	char **current = (char **)malloc(sizeof(char *) * len),
	***retList = (char ***)malloc(sizeof(char **)),
	****ret = &retList;
	for (i = 0; i < len; i++)
		current[i] = (char *)memset(malloc(sizeof(char) * (len + 1)), 0, sizeof(char) * (len + 1));

	for (i = 0; i < wordsSize; i++)
		insert(wordTree, words[i]);

	*returnSize = 0;
	dfs(wordTree, resultTree, ret, returnSize, &maxSize, current, 0, 0, len);

	*returnColumnSizes = (int *)malloc(sizeof(int) * *returnSize);
	for (i = 0; i < *returnSize; i++)
		(*returnColumnSizes)[i] = len;
	return *ret;
}

/*
1032. �ַ���
������Ҫ��ʵ�� StreamChecker �ࣺ

StreamChecker(words)�����캯�����ø������ִʳ�ʼ�����ݽṹ��
query(letter)���������ĳЩ k >= 1�������ò�ѯ����� k���ַ������Ӿɵ���˳�򣬰����ող�ѯ����ĸ��ƴд�������ִʱ��е�ĳһ�ִ�ʱ������ true�����򣬷��� false��


ʾ����

StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // ��ʼ���ֵ�
streamChecker.query('a');          // ���� false
streamChecker.query('b');          // ���� false
streamChecker.query('c');          // ���� false
streamChecker.query('d');          // ���� true����Ϊ 'cd' ���ִʱ���
streamChecker.query('e');          // ���� false
streamChecker.query('f');          // ���� true����Ϊ 'f' ���ִʱ���
streamChecker.query('g');          // ���� false
streamChecker.query('h');          // ���� false
streamChecker.query('i');          // ���� false
streamChecker.query('j');          // ���� false
streamChecker.query('k');          // ���� false
streamChecker.query('l');          // ���� true����Ϊ 'kl' ���ִʱ��С�
*/

struct trieNode {
    int flag;
    int ch[26];
};

typedef struct {
    struct trieNode tree[100001];
    int len;
    char buff[40001];
    int count;
} StreamChecker;

void insert(StreamChecker *obj, char *s)
{
    int addr = 0;
    for(int i = strlen(s) - 1; i >= 0; i-- )
    {
        int k = s[i] - 'a';
        if(obj->tree[addr].ch[k] == 0)
        {
            obj->len++;
            obj->tree[addr].ch[k] = obj->len - 1;
        }
        addr = obj->tree[addr].ch[k];
    }
    obj->tree[addr].flag = true;
}

bool findWord(StreamChecker *obj)
{
    int addr = 0;
    for(int i = obj->count - 1; i >= 0; i--)
    {
        int k = obj->buff[i] - 'a';
        if(obj->tree[addr].ch[k] == 0)
            return false;
        else
        {
            addr = obj->tree[addr].ch[k];
            if(obj->tree[addr].flag == true)
                return true;
        }
    }

    return obj->tree[addr].flag;
}

StreamChecker* streamCheckerCreate(char ** words, int wordsSize) {
    StreamChecker *obj = (StreamChecker *)calloc(1, sizeof(StreamChecker));
    obj->len = 1;

    for(int i = 0; i < wordsSize; i++)
        insert(obj, words[i]);
    return obj;
}

bool streamCheckerQuery(StreamChecker* obj, char letter) {
    obj->buff[obj->count++] = letter;
    return findWord(obj);
}

void streamCheckerFree(StreamChecker* obj) {
    free(obj);
}

