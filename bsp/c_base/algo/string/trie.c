/*
基本性质：
根节点不包含字符，除根节点外每个节点都只包含一个字符
从根节点到某一节点，路径上经过的字符连接起来，为该节
点对应的字符串
每个节点的所有子节点包含的字符都不相同

Trie一般支持两个操作：
1. Trie.insert(W)：第一个操作是插入操作，
就是将一个字符串W加入到集合中。
2. Trie.search(S)：第二个操作是查询操作，
就是查询一个字符串S是不是在集合中。
*/
struct trie {
	int nex[100000][26];
	int cnt;
	bool exist[100000];  // 该结点结尾的字符串是否存在

	memset(nex, 0, sizeof(nex));
	memset(exist, 0, sizeof(exist));

	void insert(char *s, int l) {  // 插入字符串
		int p = 0;
		for (int i = 0; i < l; i++) {
			int c = s[i] - 'a';
			if (!nex[p][c])
				nex[p][c] = ++cnt;  // 如果没有，就添加结点

			p = nex[p][c];
		}

		exist[p] = 1;
	}

	bool find(char *s, int l) {  // 查找字符串
		int p = 0;
		for (int i = 0; i < l; i++) {
			int c = s[i] - 'a';
			if (!nex[p][c])
				return 0;
			p = nex[p][c];
		}
		return exist[p];
	}
};

/////////////////////////
    static class TrieNode {

        /**
         * 当前节点要存储的字符
         */
        char val;

        /**
         * 标记节点，用来标记当前的节点是否为要存储节点的最后一个字符
         */
        boolean isEnd;

        /**
         *  存储树的下一个节点，因为这次只考虑到小写，因此
         *  只开辟了26个数组空间
         *
         *  //如果trie树的节点远大于26个的话，可以使用Map来作为next
         *  TreeMap<Character,TrieNode> = new TreeMap()
         */
        TrieNode[] next = new TrieNode[26];

        public TrieNode() {
        }

        public TrieNode(char val) {
            this.val = val;
        }
    }

public class Trie {

    /**
     * Trie树的根节点
     */
    TrieNode root;

    /**
     * 初始化Trie数据结构
     */
    public Trie() {
        root = new TrieNode();
        root.val = ' ';
    }

    /**
     * 插入一个单词到Trie树中
     *
     */
    public void insert(String word) {
        TrieNode currentNode = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            // 将当前的字符作为节点插入到Trie树中
            // 但是插入之前首先做一次检查
            if (currentNode.next[c - 'a'] == null) {
                currentNode.next[c - 'a'] = new TrieNode(c);
            }
            currentNode = currentNode.next[c - 'a'];
        }
        // 现在标识已经走到单词末尾了
        currentNode.isEnd = true;
    }

    /**
     * 判断某个单词是否在Trie树之中
     */
    public boolean search(String word) {
        TrieNode currentNode = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            // 在单词还未走完的时候发现已经不匹配了
            if (currentNode.next[c - 'a'] == null){
                return false;
            }
            currentNode = currentNode.next[c - 'a'];
        }
        // 在每个单词的末尾都有设置为true
        // 如果当前是false，那么代表未存储这个单词
        return currentNode.isEnd;
    }

    /**
     * 判断当前的单词是否为Trie树种某个单词的前缀，注意这里的逻辑与查询是相同的，唯一不同的是
     * 匹配完前缀之后返回true
     */
    public boolean startsWith(String prefix) {
        TrieNode currentNode = root;
        for (int i = 0; i < prefix.length(); i++) {
            char c = prefix.charAt(i);
            if (currentNode.next[c - 'a'] == null){
                return false;
            }
            currentNode = currentNode.next[c - 'a'];
        }
        return true;
    }
}

///////////////////////////////////
//插入一个新单词
	public static void insert(TrieNode root,String str){
		if(root==null||str.length()==0){
			return;
		}
		char[] c=str.toCharArray();
		for(int i=0;i<str.length();i++){
			//如果该分支不存在，创建一个新节点
			if(root.nextNode[c[i]-'a']==null){
				root.nextNode[c[i]-'a']=new TrieNode();
			}
			root=root.nextNode[c[i]-'a'];
			root.prefix++;//注意，应该加在后面
			}

		//以该节点结尾的单词数+1
		root.count++;
	}

 //查找该单词是否存在，如果存在返回数量，不存在返回-1
	public static int search(TrieNode root,String str){
		if(root==null||str.length()==0){
			return -1;
		}
		char[] c=str.toCharArray();
		for(int i=0;i<str.length();i++){
			//如果该分支不存在，表名该单词不存在
			if(root.nextNode[c[i]-'a']==null){
				return -1;
			}
			//如果存在，则继续向下遍历
			root=root.nextNode[c[i]-'a'];
		}

		//如果count==0,也说明该单词不存在
		if(root.count==0){
			return -1;
		}
		return root.count;
	}

	//查询以str为前缀的单词数量
	public static int searchPrefix(TrieNode root,String str){
		if(root==null||str.length()==0){
			return -1;
		}
		char[] c=str.toCharArray();
		for(int i=0;i<str.length();i++){
			//如果该分支不存在，表名该单词不存在
			if(root.nextNode[c[i]-'a']==null){
				return -1;
			}
			//如果存在，则继续向下遍历
			root=root.nextNode[c[i]-'a'];
		}
		return root.prefix;
	}




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
			res[root->id][root->num] = start;
			root->num++;
			size[root->id] = root->num;
		}
	}
}

void insert(char* smalls, st_node* root, int start)
{
	for(int i=0;i<strlen(smalls);i++){
		if(root->next[smalls[i]-'a'] == NULL) {
			root->next[smalls[i]-'a'] =(st_node*)calloc(1,sizeof(st_node));
		}

		root = root->next[smalls[i]-'a'];
	}

	root->isend = true;
	root->id = start;
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


