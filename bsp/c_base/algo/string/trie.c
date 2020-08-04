/*
�������ʣ�
���ڵ㲻�����ַ��������ڵ���ÿ���ڵ㶼ֻ����һ���ַ�
�Ӹ��ڵ㵽ĳһ�ڵ㣬·���Ͼ������ַ�����������Ϊ�ý�
���Ӧ���ַ���
ÿ���ڵ�������ӽڵ�������ַ�������ͬ

Trieһ��֧������������
1. Trie.insert(W)����һ�������ǲ��������
���ǽ�һ���ַ���W���뵽�����С�
2. Trie.find(S)���ڶ��������ǲ�ѯ������
���ǲ�ѯһ���ַ���S�ǲ����ڼ����С�
*/
struct trieNode{
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
		if(root->child[str[i]-'a'] == NULL) {
			root->child[str[i]-'a'] = (struct trieNode*)calloc(1, sizeof(struct trieNode));
		}
		root = root->child[str[i]-'a'];
		root->prefix++;
	}

	root->end++;
}


int find(struct trieNode *root, char * str)
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

	return root->end;
}

int findPrefix(struct trieNode *root, char * str)
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
	return root->prefix;
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
