/*
211. 添加与搜索单词 - 数据结构设计
难度中等142
设计一个支持以下两种操作的数据结构：
void addWord(word)
bool search(word)
search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母 . 或 a-z 。 . 可以表示任何一个字母。
示例:
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
说明:
你可以假设所有单词都是由小写字母 a-z 组成的。

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

	//以该节点结尾的单词数+1
	root->count++;

}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary* obj, char * word) {
    /* 回溯算法，遇到.号进行暴力回溯 */
    while (*word) {
        if (*word != '.' && !obj->next[(*word)-97]) return false;  // 不匹配且不是.一定为假
        else if (*word == '.') {  // 是.号进行26字母暴力回溯
            for (int i = 0; i < 26; i++) {
                if (obj->next[i] && wordDictionarySearch(obj->next[i], word+1))
                    return true;  // 只要一个为真即可，立马返回
            }
            return false;  // 否者26个过完，还没找到，一定为假
        }
        obj = obj->next[(*word++)-97];  // 这是正常匹配obj交换的进行
    }
    return !!obj->count;  // 最后字符串完了，需要判断字典树在此节点是是否有个bool标记结束
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
676. 实现一个魔法字典
难度中等54
实现一个带有buildDict, 以及 search方法的魔法字典。
对于buildDict方法，你将被给定一串不重复的单词来构建一个字典。
对于search方法，你将被给定一个单词，并且判定能否只将这个单词中一个字母换成另一个字母，使得所形成的新单词存在于你构建的字典中。
示例 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
注意:
1.	你可以假设所有输入都是小写字母 a-z。
2.	为了便于竞赛，测试所用的数据量很小。你可以在竞赛结束后，考虑更高效的算法。
3.	请记住重置MagicDictionary类中声明的类变量，因为静态/类变量会在多个测试用例中保留。 请参阅这里了解更多详情。

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

/* 查找剩下的word和剩下的字典树是否匹配 */
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
        /* 每个字母尝试一遍去掉这个单词其他是否一致 */
        for (int j = 0; j < 26; j++) {
            if (node->next[j] != NULL && j != word[i] - 'a') {
                if (checkLeftWord(node->next[j], word + i + 1) == true) {
                    return true;
                }
            }
        }

        /* 只有替换一次的机会, 下次再不一样就退出 */
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
421. 数组中两个数的最大异或值
难度中等150
给定一个非空数组，数组中元素为 a0, a1, a2, … , an-1，其中
0 ≤ ai < 231 。
找到 ai 和aj 最大的异或 (XOR) 运算结果，其中0 ≤ i,  j < n 。
你能在O(n)的时间解决这个问题吗？
示例:
输入: [3, 10, 5, 25, 2, 8]
输出: 28
解释: 最大的结果是 5 ^ 25 = 28.
*/

/*
0 和任意比特 x 异或结果还是 x 本身。
如果a，b两个值相同，异或结果为0
字典树中每条根节点到叶节点的路径都代表了 nums 中的
一个整数（二进制形式）
字典树非常适合用来存储整数的二进制形式
字典树中给定数的最大异或值
为了最大化异或值，需要在每一步找到当前比特值的互补
比特值
如果当前比特值存在互补比特值，访问具有互补比特值的孩
子节点，并在异或值最右侧附加一个 1。
如果不存在，直接访问具有当前比特值的孩子节点，并在异
或值最右侧附加一个 0。
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
336. 回文对
给定一组 互不相同 的单词， 找出所有不同 的索引对(i, j)，使
得列表中的两个单词， words[i] + words[j] ，可拼接成回文串。
示例 1：
输入：["abcd","dcba","lls","s","sssll"]
输出：[[0,1],[1,0],[3,2],[2,4]]
解释：可拼接成的回文串为 ["dcbaabcd","abcddcba","slls","llssssll"]
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
212. 单词搜索 II
给定一个二维网格 board 和一个字典中的单词列表 words，找出
所有同时在二维网格和字典中出现的单词。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母在一个单词中不允许被重复使用。
示例:
输入:
words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
输出: ["eat","oath"]
说明:
你可以假设所有输入都由小写字母 a-z 组成。
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

/* 这个地方有个*小改动*，每次搜索到一个单词，就把这个单词从 */
/* 前缀树中删除（把结束结点的结束标志取消），这样做可以避免重复 */
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

/* 定义一些全局变量，不然函数的入口参数会很多 */
bool visited[500][500];
int row, col;
char *prefix;
Trie* trieTree;

/* 入口参数"pos"是用来更新prefix的 */
void traceBack(int r, int c, int pos, char **board, int* returnSize, char **res)
{
/* 该前缀构成的单词是字典树中的单词，将prefix添加到res中 */
	if (trieSearch(trieTree, prefix)) {
		res[*returnSize] = malloc(sizeof(char) * (strlen(prefix) + 1));
		strcpy(res[(*returnSize)++], prefix);
	}

    int dr[] = {1, 0, -1, 0};       /* dr,dc数组共同完成点的向下、向右、向上、向左 */
    int dc[] = {0, 1, 0, -1};
    int di = 0;                     /* di为方向控制器 */
    visited[r][c] = true;              /* 现在在（r，c）这个点，将visited[r][c]置为true */

    for (int di = 0; di < 4; di++) {
        int rr = r + dr[di];
        int cc = c + dc[di];
        if (rr >= 0 && rr < row && cc >= 0 && cc < col && !visited[rr][cc]) {
            prefix[pos] = board[rr][cc];
            if (trieStartsWith(trieTree, prefix))
                traceBack(rr, cc, pos + 1, board, returnSize, res);
        }

    }

/* 回溯法非常重要的一步，退一步就将状态还原为原来的样子 */
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
* prefix为搜索过程中构成的前缀，每搜索一步，prefix更新一下
* 引入prefix可以方便的利用前缀树的相关函数进行剪枝
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
425. 单词方块
给定一个单词集合 （没有重复），找出其中所有的 单词方块 。
一个单词序列形成了一个有效的单词方块的意思是指从第 k 行
和第 k 列 (0 ≤ k < max(行数, 列数)) 来看都是相同的字符串。

例如，单词序列 ["ball","area","lead","lady"] 形成了一个单词方块，因为
每个单词从水平方向看和从竖直方向看都是相同的。
b a l l
a r e a
l e a d
l a d y
注意：
单词个数大于等于 1 且不超过 500。
所有的单词长度都相同。
单词长度大于等于 1 且不超过 5。
每个单词只包含小写英文字母 a-z。
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
1032. 字符流
按下述要求实现 StreamChecker 类：

StreamChecker(words)：构造函数，用给定的字词初始化数据结构。
query(letter)：如果存在某些 k >= 1，可以用查询的最后 k个字符（按从旧到新顺序，包括刚刚查询的字母）拼写出给定字词表中的某一字词时，返回 true。否则，返回 false。


示例：

StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // 初始化字典
streamChecker.query('a');          // 返回 false
streamChecker.query('b');          // 返回 false
streamChecker.query('c');          // 返回 false
streamChecker.query('d');          // 返回 true，因为 'cd' 在字词表中
streamChecker.query('e');          // 返回 false
streamChecker.query('f');          // 返回 true，因为 'f' 在字词表中
streamChecker.query('g');          // 返回 false
streamChecker.query('h');          // 返回 false
streamChecker.query('i');          // 返回 false
streamChecker.query('j');          // 返回 false
streamChecker.query('k');          // 返回 false
streamChecker.query('l');          // 返回 true，因为 'kl' 在字词表中。
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

