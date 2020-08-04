/*
������ 17.17. �������
�Ѷ��е�5
����һ���ϳ��ַ���big��һ�������϶��ַ���������smalls��
���һ������������smalls�е�ÿһ���϶��ַ�����
��big�������������smalls�е��ַ�����big����ֵ�����λ��
positions������positions[i]Ϊsmalls[i]���ֵ�����λ�á�
ʾ����
���룺
big = "mississippi"
smalls = ["is","ppi","hi","sis","i","ssippi"]
����� [[1,4],[8],[],[3],[1,4,7,10],[5]]

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
			res[root->id][root->num] = start;//��¼��ʼλ��
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

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
*/

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
����һ���ǿ����飬������Ԫ��Ϊ a0, a1, a2, �� , an-1������ 0 �� ai < 231 ��
�ҵ� ai ��aj ������� (XOR) ������������0 �� i,  j < n ��
������O(n)��ʱ�������������
ʾ��:
����: [3, 10, 5, 25, 2, 8]

���: 28

����: ���Ľ���� 5 ^ 25 = 28.

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

