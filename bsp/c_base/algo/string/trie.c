/*
�������ʣ�
���ڵ㲻�����ַ��������ڵ���ÿ���ڵ㶼ֻ����һ���ַ�
�Ӹ��ڵ㵽ĳһ�ڵ㣬·���Ͼ������ַ�����������Ϊ�ý�
���Ӧ���ַ���
ÿ���ڵ�������ӽڵ�������ַ�������ͬ

Trieһ��֧������������
1. Trie.insert(W)����һ�������ǲ��������
���ǽ�һ���ַ���W���뵽�����С�
2. Trie.search(S)���ڶ��������ǲ�ѯ������
���ǲ�ѯһ���ַ���S�ǲ����ڼ����С�
*/
struct trie {
	int nex[100000][26];
	int cnt;
	bool exist[100000];  // �ý���β���ַ����Ƿ����

	memset(nex, 0, sizeof(nex));
	memset(exist, 0, sizeof(exist));

	void insert(char *s, int l) {  // �����ַ���
		int p = 0;
		for (int i = 0; i < l; i++) {
			int c = s[i] - 'a';
			if (!nex[p][c])
				nex[p][c] = ++cnt;  // ���û�У�����ӽ��

			p = nex[p][c];
		}

		exist[p] = 1;
	}

	bool find(char *s, int l) {  // �����ַ���
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
         * ��ǰ�ڵ�Ҫ�洢���ַ�
         */
        char val;

        /**
         * ��ǽڵ㣬������ǵ�ǰ�Ľڵ��Ƿ�ΪҪ�洢�ڵ�����һ���ַ�
         */
        boolean isEnd;

        /**
         *  �洢������һ���ڵ㣬��Ϊ���ֻ���ǵ�Сд�����
         *  ֻ������26������ռ�
         *
         *  //���trie���Ľڵ�Զ����26���Ļ�������ʹ��Map����Ϊnext
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
     * Trie���ĸ��ڵ�
     */
    TrieNode root;

    /**
     * ��ʼ��Trie���ݽṹ
     */
    public Trie() {
        root = new TrieNode();
        root.val = ' ';
    }

    /**
     * ����һ�����ʵ�Trie����
     *
     */
    public void insert(String word) {
        TrieNode currentNode = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            // ����ǰ���ַ���Ϊ�ڵ���뵽Trie����
            // ���ǲ���֮ǰ������һ�μ��
            if (currentNode.next[c - 'a'] == null) {
                currentNode.next[c - 'a'] = new TrieNode(c);
            }
            currentNode = currentNode.next[c - 'a'];
        }
        // ���ڱ�ʶ�Ѿ��ߵ�����ĩβ��
        currentNode.isEnd = true;
    }

    /**
     * �ж�ĳ�������Ƿ���Trie��֮��
     */
    public boolean search(String word) {
        TrieNode currentNode = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            // �ڵ��ʻ�δ�����ʱ�����Ѿ���ƥ����
            if (currentNode.next[c - 'a'] == null){
                return false;
            }
            currentNode = currentNode.next[c - 'a'];
        }
        // ��ÿ�����ʵ�ĩβ��������Ϊtrue
        // �����ǰ��false����ô����δ�洢�������
        return currentNode.isEnd;
    }

    /**
     * �жϵ�ǰ�ĵ����Ƿ�ΪTrie����ĳ�����ʵ�ǰ׺��ע��������߼����ѯ����ͬ�ģ�Ψһ��ͬ����
     * ƥ����ǰ׺֮�󷵻�true
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
//����һ���µ���
	public static void insert(TrieNode root,String str){
		if(root==null||str.length()==0){
			return;
		}
		char[] c=str.toCharArray();
		for(int i=0;i<str.length();i++){
			//����÷�֧�����ڣ�����һ���½ڵ�
			if(root.nextNode[c[i]-'a']==null){
				root.nextNode[c[i]-'a']=new TrieNode();
			}
			root=root.nextNode[c[i]-'a'];
			root.prefix++;//ע�⣬Ӧ�ü��ں���
			}

		//�Ըýڵ��β�ĵ�����+1
		root.count++;
	}

 //���Ҹõ����Ƿ���ڣ�������ڷ��������������ڷ���-1
	public static int search(TrieNode root,String str){
		if(root==null||str.length()==0){
			return -1;
		}
		char[] c=str.toCharArray();
		for(int i=0;i<str.length();i++){
			//����÷�֧�����ڣ������õ��ʲ�����
			if(root.nextNode[c[i]-'a']==null){
				return -1;
			}
			//������ڣ���������±���
			root=root.nextNode[c[i]-'a'];
		}

		//���count==0,Ҳ˵���õ��ʲ�����
		if(root.count==0){
			return -1;
		}
		return root.count;
	}

	//��ѯ��strΪǰ׺�ĵ�������
	public static int searchPrefix(TrieNode root,String str){
		if(root==null||str.length()==0){
			return -1;
		}
		char[] c=str.toCharArray();
		for(int i=0;i<str.length();i++){
			//����÷�֧�����ڣ������õ��ʲ�����
			if(root.nextNode[c[i]-'a']==null){
				return -1;
			}
			//������ڣ���������±���
			root=root.nextNode[c[i]-'a'];
		}
		return root.prefix;
	}




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


