/*
面试题 17.17. 多次搜索
难度中等5
给定一个较长字符串big和一个包含较短字符串的数组smalls，
设计一个方法，根据smalls中的每一个较短字符串，
对big进行搜索。输出smalls中的字符串在big里出现的所有位置
positions，其中positions[i]为smalls[i]出现的所有位置。
示例：
输入：
big = "mississippi"
smalls = ["is","ppi","hi","sis","i","ssippi"]
输出： [[1,4],[8],[],[3],[1,4,7,10],[5]]

*/


typedef struct node{
    int id;
    int num;
    bool isend;
    struct node* next[26];
}st_node;

void find(char* big, int start, st_node* root,int** res, int* size)
{
	for(int i =start;i<strlen(big);i++){
		if(root->next[big[i]-'a'] == NULL) {
			return;
		}

		root = root->next[big[i]-'a'];
		if(root->isend) {
			res[root->id][root->num] = start;//记录启始位置
			root->num++;
			size[root->id] = root->num;
		}
	}
}

void insert(char* smalls, st_node* root, int idx)
{
	for(int i=0;i<strlen(smalls);i++){
		if(root->next[smalls[i]-'a'] == NULL) {
			root->next[smalls[i]-'a'] =(st_node*)calloc(1,sizeof(st_node));
		}

		root = root->next[smalls[i]-'a'];
	}

	root->isend = true;
	root->id = idx;
	root->num = 0;
}

void triefree(st_node* root){

    for(int i=0;i<26;i++){
        if(root->next[i] == NULL) {
            continue;
        }
        free(root->next[i]);

    }
    free(root);
}

st_node* create(){
    st_node* root;
    root = (st_node*)calloc(1,sizeof(st_node));
    return root;
}

int** multiSearch(char* big, char** smalls, int smallsSize,
	int* returnSize, int** returnColumnSizes)
{
	st_node* head=create();

	for(int i=0;i<smallsSize;i++){
		insert(smalls[i], head, i);
	}

	int** res =(int**)calloc(smallsSize,sizeof(int*));
	for(int i=0;i<smallsSize;i++){
		res[i]=(int*)calloc(strlen(big),sizeof(int));
	}
	(*returnColumnSizes) = (int*)calloc(smallsSize,sizeof(int));

	for(int i=0;i<strlen(big);i++){
		find(big, i, head, res, (*returnColumnSizes));
	}

	triefree(head);

	*returnSize = smallsSize;
	return res;
}

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

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
*/

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
给定一个非空数组，数组中元素为 a0, a1, a2, … , an-1，其中 0 ≤ ai < 231 。
找到 ai 和aj 最大的异或 (XOR) 运算结果，其中0 ≤ i,  j < n 。
你能在O(n)的时间解决这个问题吗？
示例:
输入: [3, 10, 5, 25, 2, 8]

输出: 28

解释: 最大的结果是 5 ^ 25 = 28.

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

