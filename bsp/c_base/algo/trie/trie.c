/*
基本性质：
根节点不包含字符，除根节点外每个节点都只包含一个字符
从根节点到某一节点，路径上经过的字符连接起来，为该节
点对应的字符串
每个节点的所有子节点包含的字符都不相同

Trie一般支持两个操作：
1. Trie.insert(W)：第一个操作是插入操作，
就是将一个字符串W加入到集合中。
2. Trie.find(S)：第二个操作是查询操作，
就是查询一个字符串S是不是在集合中。
*/
struct trieNode {
	int prefix;
	int end;
	struct trieNode* child[26];
};

void push(struct trieNode *root, char * str)
{
	int slen = strlen(str);
	if(root == NULL||slen == 0) {
		return;
	}

	for(int i = 0;i < slen; i++) {
		int idx = str[i]-'a';

		if(root->child[idx] == NULL) {
			root->child[idx] = (struct trieNode*)calloc(1, sizeof(struct trieNode));
		}

		root = root->child[idx];
		root->prefix++;
	}

	root->end++;
}

struct trieNode * find(struct trieNode *root, char * str)
{
	int slen = strlen(str);

	if(root == NULL||slen == 0) {
		return 0;
	}

	for(int i = 0; i < slen; i++) {
		if(root->child[str[i]-'a'] == NULL) {
			return 0;
		}
		root = root->child[str[i]-'a'];
	}

	return root;
}


int findStr(struct trieNode *root, char * str)
{
	struct trieNode *node = find(root, str);
	return node->end;
}

int findPrefix(struct trieNode *root, char * str)
{
	struct trieNode *node = find(root, str);
	return node->prefix;
}

void trieFree(struct trieNode *root)
{
	for (int i = 0; i < 26; i++) {
		if (root->next[i] != NULL)
			trieFree(root->next[i]);
	}

	free(root);
	root = NULL;
}

