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


/*
642. 设计搜索自动补全系统
为搜索引擎设计一个搜索自动补全系统。用户会输入一条语句（最少包含一个字母，以特殊字符 '#' 结尾）。除 '#' 以外用户输入的每个字符，返回历史中热度前三并以当前输入部分为前缀的句子。下面是详细规则：

一条句子的热度定义为历史上用户输入这个句子的总次数。
返回前三的句子需要按照热度从高到低排序（第一个是最热门的）。如果有多条热度相同的句子，请按照 ASCII 码的顺序输出（ASCII 码越小排名越前）。
如果满足条件的句子个数少于 3，将它们全部输出。
如果输入了特殊字符，意味着句子结束了，请返回一个空集合。
你的工作是实现以下功能：

构造函数：

AutocompleteSystem(String[] sentences, int[] times): 这是构造函数，输入的是历史数据。 Sentences 是之前输入过的所有句子，Times 是每条句子输入的次数，你的系统需要记录这些历史信息。

现在，用户输入一条新的句子，下面的函数会提供用户输入的下一个字符：

List<String> input(char c): 其中 c 是用户输入的下一个字符。字符只会是小写英文字母（'a' 到 'z' ），空格（' '）和特殊字符（'#'）。输出历史热度前三的具有相同前缀的句子。



样例 ：
操作 ： AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2])
系统记录下所有的句子和出现的次数：
"i love you" : 5 次
"island" : 3 次
"ironman" : 2 次
"i love leetcode" : 2 次
现在，用户开始新的键入：


输入 ： input('i')
输出 ： ["i love you", "island","i love leetcode"]
解释 ：
有四个句子含有前缀 "i"。其中 "ironman" 和 "i love leetcode" 有相同的热度，由于 ' ' 的 ASCII 码是 32 而 'r' 的 ASCII 码是 114，所以 "i love leetcode" 在 "ironman" 前面。同时我们只输出前三的句子，所以 "ironman" 被舍弃。

输入 ： input(' ')
输出 ： ["i love you","i love leetcode"]
解释:
只有两个句子含有前缀 "i "。

输入 ： input('a')
输出 ： []
解释 ：
没有句子有前缀 "i a"。

输入 ： input('#')
输出 ： []
解释 ：

用户输入结束，"i a" 被存到系统中，后面的输入被认为是下一次搜索。



注释 ：

输入的句子以字母开头，以 '#' 结尾，两个字母之间最多只会出现一个空格。
即将搜索的句子总数不会超过 100。每条句子的长度（包括已经搜索的和即将搜索的）也不会超过 100。
即使只有一个字母，输出的时候请使用双引号而不是单引号。
请记住清零 AutocompleteSystem 类中的变量，因为静态变量、类变量会在多组测试数据中保存之前结果。详情请看这里。

*/

struct TrieNode
{
    bool isEnd;
    int hot;
    struct TrieNode *next[27];
};

// 获得一个新的前缀树节点
struct TrieNode *getNode()
{
    struct TrieNode *ret = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    ret->isEnd = false;
    ret->hot = 0;
    memset(ret->next, 0, sizeof(ret->next));
    return ret;
}
// 向前缀树中插入键值
void insert(struct TrieNode *dest, char *val, int hot)
{
    if (dest == NULL)
        return;
    if (*val == 0)
    {
        dest->isEnd = true;
        dest->hot += hot;
    }
    else
    {
        int pos = *val == ' ' ? 26 : *val - 'a';
        if (dest->next[pos] == NULL)
            dest->next[pos] = getNode();
        insert(dest->next[pos], val + 1, hot);
    }
}

typedef struct {
    struct TrieNode *master;    // 存储前缀树的根节点
    struct TrieNode *current;   // 当前查找到的位置
    int totalCnt;               // 字符串的总数
    int currentCnt;             // 可能的结果数目
    int currentPos;             // 已经查找（填入prefix字段）的所有字符数量
    char prefix[101];           // 查找到的字符串
} AutocompleteSystem;

AutocompleteSystem* autocompleteSystemCreate(char ** sentences, int sentencesSize, int* times, int timesSize) {
    AutocompleteSystem *ret = (AutocompleteSystem *)malloc(sizeof(AutocompleteSystem));
    ret->totalCnt = sentencesSize;
    ret->currentCnt = ret->totalCnt;
    ret->master = getNode();
    ret->current = ret->master;
    ret->currentPos = 0;
    memset(ret->prefix, 0, sizeof(ret->prefix));
    int i = 0;
    for (i = 0; i < sentencesSize; i++)
        insert(ret->master, sentences[i], times[i]);
    return ret;
}

struct retForm
{
    char *str;
    int hot;
};

void dfs(struct TrieNode *dest, struct retForm *ret, char *prefix, int *retSize, int curPos)
{
    if (dest == NULL)
        return;
    for (int i = 0; i < 27; i++)
    {
        prefix[curPos] = i == 26 ? ' ' : (char)i + 'a';
        dfs(dest->next[i], ret, prefix, retSize, curPos + 1);
    }
    prefix[curPos] = 0;
    if (dest->isEnd == true)
    {
        ret[*retSize].str = (char *)memset(malloc(sizeof(char) * (strlen(prefix) + 1)), 0, sizeof(char) * (strlen(prefix) + 1));
        ret[*retSize].hot = dest->hot;
        strcpy(ret[(*retSize)++].str, prefix);
    }
}

#define SIG(x) (x > 0 ? 1 : x == 0 ? 0 : -1)

int comp(struct retForm *a, struct retForm *b)
{
    int x = strcmp(a->str, b->str);
    return -(a->hot - b->hot) * 2 + SIG(x);
}

void swap(struct retForm **a, struct retForm **b)
{
    struct retForm *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

char ** autocompleteSystemInput(AutocompleteSystem* obj, char c, int* retSize) {
    if (obj == NULL)
    {
        *retSize = 0;
        return NULL;
    }
    // 非结束字符
    if (c != '#')
    {
        char **ret = (char **)malloc(sizeof(char *) * 3);
        struct retForm *hotret = (struct retForm *)malloc(sizeof(struct retForm) * obj->currentCnt),
               *hot3[4] = {NULL};
        int pos = c == ' ' ? 26 : c - 'a', i = 0, j = 0;
        obj->prefix[obj->currentPos++] = c;
        if (obj->current->next[pos] == NULL)
            obj->current->next[pos] = getNode(); // 插入节点
        obj->current = obj->current->next[pos];
        *retSize = 0;
        if (obj->currentCnt != 0)
        {
            dfs(obj->current, hotret, obj->prefix, retSize, obj->currentPos);
            obj->currentCnt = *retSize;
            for (i = 0; i < *retSize; i++)
            {
                hot3[3] = hotret + i; // 替换最后一个元素，进行冒泡排序
                for (j = 3; j >= 1; j--)
                    if (hot3[j - 1] == NULL || comp(hot3[j], hot3[j - 1]) < 0)
                        swap(hot3 + j, hot3 + j - 1);
            }
            *retSize = *retSize >= 3 ? 3 : *retSize;
            for (i = 0; i < *retSize; i++)
                ret[i] = hot3[i]->str;
        }
        return ret;
    }
    // 结束字符
    else
    {
        obj->current->isEnd = true;
        obj->current->hot++;
        obj->totalCnt++;
        memset(obj->prefix, 0, sizeof(obj->prefix));
        obj->current = obj->master;
        obj->currentCnt = obj->totalCnt;
        obj->currentPos = 0;
        *retSize = 0;
        return NULL;
    }
}

void delTrie(struct TrieNode *dest)
{
    if (dest == NULL)
        return;
    for (int i = 0; i < 27; i++)
        delTrie(dest->next[i]);
    free(dest);
}

void autocompleteSystemFree(AutocompleteSystem* obj) {
    free(obj->master);
    free(obj);
}


/*
472. 连接词
给定一个不含重复单词的列表，编写一个程序，返回给定单词列表中所有的连接词。

连接词的定义为：一个字符串完全是由至少两个给定数组中的单词组成的。

示例:

输入: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

输出: ["catsdogcats","dogcatsdog","ratcatdogcat"]

解释: "catsdogcats"由"cats", "dog" 和 "cats"组成;
     "dogcatsdog"由"dog", "cats"和"dog"组成;
     "ratcatdogcat"由"rat", "cat", "dog"和"cat"组成。
说明:

给定数组的元素总数不超过 10000。
给定数组中元素的长度总和不超过 600000。
所有输入字符串只包含小写字母。
不需要考虑答案输出的顺序。
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* 字典树 */
struct DictTree {
    struct DictTree *childs[26];    // 当前节点收到一个字母ch后往childs[ch - 'a']走
    int IsWord; // 当前节点是一个单词？
};

void InitDictTree(struct DictTree **node)   // 初始化一个节点
{
    *node = malloc(sizeof(struct DictTree));
    for (int i = 0; i < 26; i++) {
        ((*node)->childs)[i] = NULL;
    }
    (*node)->IsWord = 0;
}

void InsertWord(struct DictTree *root, char *words) // 将一个词插入字典树
{
    struct DictTree *p;
    p = root;
    for (int i = 0; words[i] != '\0'; i++) {
        if ((p->childs)[words[i] - 'a'] == NULL) {
            InitDictTree(&((p->childs)[words[i] - 'a'])); // 不存在字母，新建一个
        }
        p = (p->childs)[words[i] - 'a'];
        if (words[i + 1] == '\0') { // 是单词
            p->IsWord = 1;
        }
    }
}


// 搜索一个单词是否能够分成2个或以上的单词，且都在字典树中
int SearchWord(struct DictTree *root, char *words, int start, int deep)
{
    if (start == strlen(words)) {   // 搜索结束
        if (deep > 2) {             // 如果deep > 2，说明words被拆成了2份以上，每一份都在字典树中
            return 1;
        }
        return 2;
    }

    struct DictTree *p =root;
    for (int i = start; words[i] != '\0'; i++) {
        p = (p->childs)[words[i] - 'a'];
        if (p == NULL) {
            return 0;
        }
        if (p->IsWord == 1) {   // 单词的前i个字母可以组成一个单词，且该单词存在字典树中，所以可以拆分
            int ret = SearchWord(root, words, i + 1, deep + 1);
            if (ret > 0) { // 将
                return ret;
            }
        }
    }
    return 0;
}

char ** findAllConcatenatedWordsInADict(char ** words, int wordsSize, int* returnSize){
    struct DictTree *root;
    InitDictTree(&root);
    char **ret;
    ret = malloc(sizeof(char *) * 1000);
    *returnSize = 0;

    // 初始化字典树
    for (int i = 0; i < wordsSize; i++) {
        InsertWord(root, words[i]);
    }

    // 搜索每一个词
    for (int i = 0; i < wordsSize; i++) {
        if (SearchWord(root, words[i], 0, 1) == 1) {
            ret[*returnSize] = words[i];
            (*returnSize)++;
        }
    }

    return ret;
}


