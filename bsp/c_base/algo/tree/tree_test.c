
/*
�ڶ������У����ڵ�λ����� 0 ����ÿ�����Ϊ k �Ľڵ���ӽڵ�λ����� k+1 ����

����������������ڵ������ͬ�������ڵ㲻ͬ����������һ�����ֵܽڵ㡣

���Ǹ����˾���Ψһֵ�Ķ������ĸ��ڵ� root���Լ�����������ͬ�ڵ��ֵ x �� y��

ֻ����ֵ x �� y ��Ӧ�Ľڵ������ֵܽڵ�ʱ���ŷ��� true�����򣬷��� false

*/
struct TreeNode* x_f = NULL;
struct TreeNode* y_f = NULL;

int find_depth_x(struct TreeNode* f_node, struct TreeNode* root, int node_val)
{
    if (root == NULL)  return -1;
    if (root->val == node_val) {
        x_f = f_node;
        return 0;
    }
    int ret;
    if ((ret = find_depth_x(root, root->left,  node_val)) >= 0) return ret+1;
    if ((ret = find_depth_x(root, root->right, node_val)) >= 0) return ret+1;
    return -1;
}
int find_depth_y(struct TreeNode* f_node, struct TreeNode* root, int node_val)
{
    if (root == NULL)  return -1;
    if (root->val == node_val) {
        y_f = f_node;
        return 0;
    }
    int ret;
    if ((ret = find_depth_y(root, root->left,  node_val)) >= 0) return ret+1;
    if ((ret = find_depth_y(root, root->right, node_val)) >= 0) return ret+1;
    return -1;
}

bool isCousins(struct TreeNode* root, int x, int y){
    int x_depth = find_depth_x(NULL, root, x);
    int y_depth = find_depth_y(NULL, root, y);
    return (x_f != y_f && x_depth == y_depth);
}

/*
����һ�����������������дӸ��ڵ㵽Ҷ�ӽڵ��·����

˵��: Ҷ�ӽڵ���ָû���ӽڵ�Ľڵ㡣

ʾ��:

����:

   1
 /   \
2     3
 \
  5

���: ["1->2->5", "1->3"]

����: ���и��ڵ㵽Ҷ�ӽڵ��·��Ϊ: 1->2->5, 1->3

*/
void _binaryTreePaths(struct TreeNode* root, int* buf, int bufSize, char** res, int* returnSize){

	if(root == NULL) {
		return;
	}

	buf[bufSize++] = root->val;

	if((root->left == NULL) && (root->right == NULL)){
		res[*returnSize] = (char*)malloc(256);
		sprintf(res[*returnSize], "%d", buf[0]);
		for(int i = 1; i < bufSize; i++) {
			sprintf(res[*returnSize], "%s->%d", res[*returnSize], buf[i]);
		}
		(*returnSize)++;
		return;
	}

	_binaryTreePaths(root->left, buf, bufSize, res, returnSize);
	_binaryTreePaths(root->right, buf, bufSize, res, returnSize);
}

char ** binaryTreePaths(struct TreeNode* root, int* returnSize){
   char** res = (char**)malloc(sizeof(char*) * 256);
   *returnSize = 0;
   int buf[256];
   _binaryTreePaths(root, buf, 0, res, returnSize);

   return res;
}


/*
����һ�����������������е��ҽڵ�
Ҫô�Ǿ����ֵܽڵ㣨ӵ����ͬ���ڵ����ڵ㣩��Ҷ�ڵ㣬
ҪôΪ�գ����˶��������·�ת���������һ������
ԭ�����ҽڵ㽫ת������Ҷ�ڵ㡣�����µĸ���

����:

����: [1,2,3,4,5]

    1
   / \
  2   3
 / \
4   5

���: ���ض������ĸ� [4,5,2,#,#,3,1]

   4
  / \
 5   2
    / \
   3   1
˵��:

�� [4,5,2,#,#,3,1] �е�����? ������ϸ������鿴 ����������α����л��ġ�

�����������л���ѭ��α������򣬵�û�нڵ����ʱ��'#' ��ʾ·����ֹ����

������һ������:

   1
  / \
 2   3
    /
   4
    \
     5
����Ķ����������л�Ϊ [1,2,3,#,#,4,#,#,5].

*/
struct TreeNode* upsideDownBinaryTree(struct TreeNode* root){
	if (root == NULL || root->left == NULL)
		return root;

	struct TreeNode *left = root->left;
	struct TreeNode *right = root->right;

	root->left = NULL;
	root->right = NULL;

	struct TreeNode* res = upsideDownBinaryTree(left);
	left->left = right;
	left->right = root;
	return res;
}


/*
1145. ��������ɫ��Ϸ
�Ѷ��е�17
����λ������Ҳ�����һ������������ɫ������Ϸ����Ϸ�У������������ĸ��ڵ� root�������ܹ��� n ���ڵ㣬�� n Ϊ����������ÿ���ڵ��ϵ�ֵ�� 1 �� n ������ͬ��

��Ϸ�ӡ�һ�š���ҿ�ʼ����һ�š����Ϊ��ɫ�������š����Ϊ��ɫ�����ʼʱ��
��һ�š���Ҵ� [1, n] ��ȡһ��ֵ x��1 <= x <= n����
�����š����Ҳ�� [1, n] ��ȡһ��ֵ y��1 <= y <= n���� y != x��
��һ�š���Ҹ�ֵΪ x �Ľڵ�Ⱦ�Ϻ�ɫ���������š���Ҹ�ֵΪ y �Ľڵ�Ⱦ����ɫ��

֮����λ����������в�����ÿһ�غϣ����ѡ��һ����֮ǰͿ����ɫ�Ľڵ㣬����ѡ�ڵ�һ�� δ��ɫ ���ڽڵ㣨�������ӽڵ㡢�򸸽ڵ㣩����Ⱦɫ��
�����ǰ����޷��ҵ������Ľڵ���Ⱦɫʱ�����ĻغϾͻᱻ������
��������Ҷ�û�п���Ⱦɫ�Ľڵ�ʱ����Ϸ��������ɫ�ڵ�������λ��һ��ʤ�� ??��

���ڣ��������ǡ����š���ң����������������룬�������һ�� y ֵ����ȷ����Ӯ���ⳡ��Ϸ���򷵻� true�����޷���ʤ�����뷵�� false��

ʾ����

���룺root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
�����True
���ͣ��ڶ�����ҿ���ѡ��ֵΪ 2 �Ľڵ㡣

��ʾ��
"	�������ĸ��ڵ�Ϊ root�������� n ���ڵ㣬�ڵ��ϵ�ֵ�� 1 �� n ������ͬ��
"	n Ϊ������
"	1 <= x <= n <= 100

*/
int dfs(struct TreeNode* root, int mid, int x, bool *res)
{
	if (root == NULL)
		return 0;

	int l = dfs(root->left, mid, x, res);
	int r = dfs(root->right, mid, x, res);

       if (root->val == x) {
            // ��x������������������������������һ�룬��������x��������<=һ���ʱ�򣬽��Ϊtrue
            if (l > mid || r > mid || (l + r + 1 <= mid)) {
                *res = true;
                return;
            }
        }

        return l + r + 1;
}

bool btreeGameWinningMove(struct TreeNode* root, int n, int x)
{
	bool res = false;
	int mid = n >> 1;
	dfs(root, mid, x, &res);
	return res;
}

/*
������ 04.12. ���·��
����һ�ö�����������ÿ���ڵ㶼����һ��������ֵ
(��ֵ������)�����һ���㷨����ӡ�ڵ���ֵ�ܺ͵�
��ĳ������ֵ������·����������ע�⣬·����һ����
�ôӶ������ĸ��ڵ��Ҷ�ڵ㿪ʼ�������
�����䷽���������(ֻ�ܴӸ��ڵ�ָ���ӽڵ㷽��)��

ʾ��:
�������¶��������Լ�Ŀ��� sum = 22��

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
����:

3
���ͣ���Ϊ 22 ��·���У�[5,4,11,2], [5,8,4,5], [4,11,7]
��ʾ��

�ڵ����� <= 10000
*/
/*
��Ŀ��Ҫ����������е���sum��·����������������ÿ
һ���ڵ㶼�Ǹ��ڵ㣬�ٴ�ÿһ���ڵ�DFS�ҵ����м���
����sum��·����˼·��1����DFS�������еĽڵ㣻
2���Ե�һ���������ĵ�ǰ�ڵ�Ϊ���ڵ㣬
��DFS_Path�����м�������sum��·����
*/
void dfs_sum(struct TreeNode* root, int target, int *ret)
{
	if (target == 0) {
		(*ret)++;
	}

	if (root->left)
		dfs_sum(root->left, target - root->left->val, ret);
	if (root->right)
		dfs_sum(root->right, target - root->right->val, ret);
}


void dfs_for_each_node(struct TreeNode* root, int sum, int *ret)
{
	if (root == NULL)
		return;

	//dfs_sum(root, sum - root->val, ret);
	dfs_for_each_node(root->left, sum, ret);
	//dfs_sum(root, sum - root->val, ret);
	dfs_for_each_node(root->right, sum, ret);
	dfs_sum(root, sum - root->val, ret);
}

int pathSum(struct TreeNode* root, int sum)
{
	int ret = 0;
	dfs_for_each_node(root, sum, &ret);
	return ret;
}


/*
������ 04.08. �׸���ͬ����
�Ѷ��е�7
��Ʋ�ʵ��һ���㷨���ҳ���������ĳ�����ڵ�ĵ�һ����ͬ���ȡ����ý������Ľڵ�洢����������ݽṹ�С�ע�⣺�ⲻһ���Ƕ�����������
���磬�������¶�����: root = [3,5,1,6,2,0,8,null,null,7,4]
    3
   / \
  5   1
 / \ / \
6  2 0  8
  / \
 7   4
ʾ�� 1:
����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
����: 3
����: �ڵ� 5 �ͽڵ� 1 ��������������ǽڵ� 3��

*/

/*
˼·
����
���ڵ�ǰ�ĸ��ڵ�root
��rootΪ�գ�ֱ�ӷ���root����ʾû���ҵ�Ŀ��
��rootΪp��q
�����������������к�������һ��Ŀ��ڵ㣬��ôroot�������մ𰸣�����root
����ҲӦ������root����ʾ�ҵ�������һ��Ŀ��
����
�����������������ֱ���p��q�е�һ������ôroot�������մ𰸣�����root
����
���������к���p��q�е�һ�����������Ǹ��ڵ㣬��ʾ�ҵ�������һ��Ŀ��
���򷵻�nullptr����ʾû���ҵ�Ŀ��
����
�����������Ƿ���
��rootΪp��q�����������Ƿ�������һ��Ŀ�꣬��Ӧ�÷���root
���⣬�����������ľ�����Ŀ��ڵ�ʱ������root������ֻ�践���ҵ���Ŀ��ڵ���ָ��
�㷨
��rootΪ�ջ�root == p��root == q������root
�ֱ�root->left��root->right��Ϊ���ڵ㣬���������õ�����ֵleft��right
��left��Ϊ��
��right��Ϊ�գ�����root
���򷵻�left
���򷵻�right

*/
struct TreeNode* lowestCommonAncestor
	(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
	if (root == NULL)
		return NULL;

	struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
	struct TreeNode* right = lowestCommonAncestor(root->right, p, q);
	if (root == p || root == q)
		return root;
	else if (left != NULL && right != NULL)
		return root;
	else if (left != NULL)
		return left;
	else
		return right;
}

/*
116. ���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
����һ��������������������Ҷ�ӽڵ㶼��ͬһ�㣬ÿ�����ڵ㶼�������ӽڵ㡣�������������£�

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
�������ÿ�� next ָ�룬�����ָ��ָ������һ���Ҳ�ڵ㡣����Ҳ�����һ���Ҳ�ڵ㣬�� next ָ������Ϊ NULL��

��ʼ״̬�£����� next ָ�붼������Ϊ NULL��
*/
void dfs(struct Node* root, struct Node* next)
{
	if (root == NULL)
		return;

	root->next = next;
	dfs(root->left, root->right);
	dfs(root->right, root->next != NULL ? root->next->left : NULL);
}

struct Node* connect(struct Node* root)
{
	dfs(root, NULL);
	return root;
}

/*
654. ��������
����һ�������ظ�Ԫ�ص��������顣һ���Դ����鹹�������������������£�

�������ĸ��������е����Ԫ�ء�
��������ͨ�����������ֵ��߲��ֹ����������������
��������ͨ�����������ֵ�ұ߲��ֹ����������������
ͨ�����������鹹�������������������������ĸ��ڵ㡣
*/
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize)
{
	if (numsSize <= 0)
		return NULL;

	struct TreeNode*root = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
	int maxidx = 0;
	for (int i = 0; i < numsSize; i++)
		if (nums[i] > nums[maxidx])
			maxidx = i;

	root->val = nums[maxidx];
	root->left = constructMaximumBinaryTree(nums, maxidx);
	root->right = constructMaximumBinaryTree(nums + maxidx + 1, numsSize - maxidx - 1);
	return root;
}

/*
652. Ѱ���ظ�������
����һ�ö����������������ظ�������������ͬһ����ظ���������ֻ��Ҫ������������һ�õĸ���㼴�ɡ�

�������ظ���ָ���Ǿ�����ͬ�Ľṹ�Լ���ͬ�Ľ��ֵ��

ʾ�� 1��

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
�����������ظ���������

      2
     /
    4
��

    4
*/

char* dfs(struct TreeNode* root, struct HashTable *ht)
{
	if (root == NULL) {
		return "#";
	}

	char* string = calloc(20000, sizeof(char));
	sprintf(string, "%d ", root->val);
	strcat(string, dfs(root->left, ht));
	strcat(string, dfs(root->right, ht));

	struct DataEntry cmpEntry;
	cmpEntry.key = string;
	struct DataEntry *find = hashFind(ht, &cmpEntry);
	if (find == NULL) {
		struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		entry->key = string;
		entry->root = root;
		entry->value = 1;
		HashAdd(ht, &entry->node);
	} else {
		find->value++;
	}

	return string;
}

struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize)
{
	*returnSize = 0;

	if (root == NULL) {
		return NULL;
	}

	struct HashTable dht;
	struct HashTable *ht = &dht;
	HashInit(ht, 40960, hashequal_str, hashcode_str);

	dfs(root, ht);
    	struct TreeNode** recordData = calloc(40960, sizeof(struct TreeNode*));

	for (size_t i = 0; i < ht->bktSize; i++) {
		if (!ListEmpty(&ht->bkts[i])) {
			struct Node *node = NULL;
			LIST_FOR_EACH(node, &ht->bkts[i]) {
				struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
				if (entry->value > 1) {
					recordData[*returnSize] = entry->root;
					(*returnSize)++;
				}
			}
		}
	}

	return recordData;
}

/*
114. ������չ��Ϊ����
����һ����������ԭ�ؽ���չ��Ϊһ��������



���磬����������

    1
   / \
  2   5
 / \   \
3   4   6
����չ��Ϊ��

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
*/
// �ݹ�
void flatten(struct TreeNode* root)
{
	if (root == NULL) {
		return;
	}
	flatten(root->left);
	flatten(root->right);
	if (root->left != NULL) {
		struct TreeNode* lr = root->left;
		while (lr->right != NULL) {
			lr = lr->right;
		}
		lr->right = root->right;
		root->right = root->left;
		root->left = NULL;
	}
}
/*
105. ��ǰ��������������й��������
����һ������ǰ�������������������������

ע��:
����Լ�������û���ظ���Ԫ�ء�

���磬����

ǰ����� preorder = [3,9,20,15,7]
������� inorder = [9,3,15,20,7]
�������µĶ�������

    3
   / \
  9  20
    /  \
   15   7
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
    if ((preorderSize == 0) || (inorderSize == 0)) {
        return NULL;
    }
    struct TreeNode* res = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    res->val = *preorder;
    res->left = NULL;
    res->right = NULL;
    int posion = 0;
    for (int i = 0; i < preorderSize; i++) {
        if (*preorder == inorder[i]) {
            posion = i;
            break;
        }
    }
    res->left = buildTree(preorder + 1, posion, inorder, posion);
    res->right = buildTree(preorder + posion + 1, inorderSize - posion - 1,
                           inorder + posion + 1, inorderSize - posion - 1);
    return res;
}

/*
951. ��ת�ȼ۶�����
�Ѷ��е�41
���ǿ���Ϊ������ T ����һ����ת������������ʾ��ѡ������ڵ㣬Ȼ�󽻻���������������������
ֻҪ����һ�������ķ�ת��������ʹ X ���� Y�����Ǿͳƶ����� X ��ת�ȼ��ڶ����� Y��
��дһ���ж������������Ƿ��Ƿ�ת�ȼ۵ĺ�������Щ���ɸ��ڵ� root1 �� root2 ������

*/
bool flipEquiv(struct TreeNode* root1, struct TreeNode* root2)
{
	if (root1 == NULL && root2 == NULL) return true;

	if (root1 == NULL || root2 == NULL) return false;

	return (root1->val == root2->val) &&
		(flipEquiv(root1->right, root2->left) && flipEquiv(root1->left, root2->right) ||
		flipEquiv(root1->right, root2->right) && flipEquiv(root1->left, root2->left));
}

/*
1110. ɾ�����
�Ѷ��е�46
�����������ĸ��ڵ� root������ÿ���ڵ㶼��һ����ͬ��ֵ��
����ڵ�ֵ�� to_delete �г��֣����ǾͰѸýڵ������ɾȥ�����õ�һ��ɭ�֣�һЩ���ཻ�������ɵļ��ϣ���
����ɭ���е�ÿ����������԰�����˳����֯�𰸡�

ʾ����

���룺root = [1,2,3,4,5,6,7], to_delete = [3,5]
�����[[1,2,null,4],[6],[7]]

*/

#define MAX 1000
struct TreeNode **g_res;
int resIndex;

bool isDelete(struct TreeNode* root, int* to_delete, int to_deleteSize)
{
    for (int i = 0; i < to_deleteSize; i++) {
        if (root->val == to_delete[i]) {
            return true;
        }
    }
    return false;
}

void dfs(struct TreeNode* root, int* to_delete, int to_deleteSize)
{
    if (root == NULL) {
        return;
    }
    if(isDelete(root, to_delete, to_deleteSize)) {
        struct TreeNode* deleteNode = root;
        if (deleteNode->left != NULL) {
            g_res[resIndex] = deleteNode->left;
            resIndex++;
            dfs(deleteNode->left, to_delete, to_deleteSize);
        }
        if (deleteNode->right != NULL) {
            g_res[resIndex] = deleteNode->right;
            resIndex++;
            dfs(deleteNode->right, to_delete, to_deleteSize);
        }
        return;
    }
    if (root->left != NULL) {
        if(isDelete(root->left, to_delete, to_deleteSize)) {
            struct TreeNode* deleteNode = root->left;
            root->left = NULL;
            if (deleteNode->left != NULL) {
                g_res[resIndex] = deleteNode->left;
                resIndex++;
                dfs(deleteNode->left, to_delete, to_deleteSize);
            }
            if (deleteNode->right != NULL) {
                g_res[resIndex] = deleteNode->right;
                resIndex++;
                dfs(deleteNode->right, to_delete, to_deleteSize);
            }
        } else {
            dfs(root->left, to_delete, to_deleteSize);
        }
    }
    if (root->right != NULL) {
        if(isDelete(root->right, to_delete, to_deleteSize)) {
            struct TreeNode* deleteNode = root->right;
            root->right = NULL;
            if (deleteNode->left != NULL) {
                g_res[resIndex] = deleteNode->left;
                resIndex++;
                dfs(deleteNode->left, to_delete, to_deleteSize);
            }
            if (deleteNode->right != NULL) {
                g_res[resIndex] = deleteNode->right;
                resIndex++;
                dfs(deleteNode->right, to_delete, to_deleteSize);
            }
        } else {
            dfs(root->right, to_delete, to_deleteSize);
        }
    }
}

struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize)
{
    resIndex = 0;
    if (root == NULL) {
        return NULL;
    }
    if (to_delete == NULL) {
        return root;
    }
    g_res = (struct TreeNode** )malloc(sizeof(struct TreeNode *) * MAX);
    for (int i = 0; i < MAX; i++) {
        g_res[i] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    }
    g_res[resIndex++] = root;
    dfs(root, to_delete, to_deleteSize);
    // printf("right = %d ", g_res[0]->right->val);
    struct TreeNode **res = (struct TreeNode** )malloc(sizeof(struct TreeNode *) * resIndex);
    for (int i = 0; i < resIndex; i++) {
        res[i] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    }
    int fallyNum = 0;
    for (int i = 0; i < resIndex; i++)
    {
        if (isDelete(g_res[i], to_delete, to_deleteSize) == false) {
            res[fallyNum] = g_res[i];
            fallyNum++;
        }
    }
    *returnSize = fallyNum;
    return res;
}

/*
199. ������������ͼ
�Ѷ��е�271
����һ�ö������������Լ�վ�������Ҳ࣬���մӶ������ײ���˳�򣬷��ش��Ҳ����ܿ����Ľڵ�ֵ��
ʾ��:
����: [1,2,3,null,5,null,4]
���: [1, 3, 4]
����:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---

*/
#define MAX 1024 * 1024
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize)
{
	int *res = (int *)calloc(MAX, sizeof(int));
	*returnSize = 0;

	if (root == NULL)
		return res;

	struct TreeNode* queue[MAX];
	int head = 0;
	int rear = 0;

	queue[rear++] = root;

	while(head != rear) {
		int floorSize = rear - head;
		while(floorSize) {
			struct TreeNode* pop = queue[head++];

			if (floorSize == 1) {
				res[*returnSize] = pop->val;
				(*returnSize)++;
			}

			if (pop->left)
				queue[rear++] = pop->left;

			if (pop->right)
				queue[rear++] = pop->right;

			floorSize--;
		}
	}

	return res;
}

#define MAX 1024 * 1024
void dfs(struct TreeNode* root, int deep, int *res, int* returnSize)
{
	if (root == NULL)
		return;

	if (*returnSize == deep) {// �����鳤�ȵ��ڵ�ǰ ��� ʱ, �ѵ�ǰ��ֵ��������
		res[*returnSize] = root->val;
		(*returnSize)++;
	}

	dfs(root->right, deep + 1, res, returnSize); // �ȴ��ұ߿�ʼ, ���ұ�û��, ���ֵ����
	dfs(root->left, deep + 1, res, returnSize);
}

int* rightSideView(struct TreeNode* root, int* returnSize)
{
	int *res = (int *)calloc(MAX, sizeof(int));
	*returnSize = 0;

	if (root == NULL)
		return res;

	dfs(root, 0, res, returnSize);
	return res;
}

/*
863. �����������о���Ϊ K �Ľ��
����һ�������������и���� root���� һ��Ŀ���� target ����һ������ֵ K ��

���ص�Ŀ���� target ����Ϊ K �����н���ֵ���б� �𰸿������κ�˳�򷵻ء�



ʾ�� 1��

���룺root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
�����[7,4,1]
���ͣ�
������Ϊ��Ŀ���㣨ֵΪ 5������Ϊ 2 �Ľ�㣬
ֵ�ֱ�Ϊ 7��4���Լ� 1
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 /*
����ʹ�� DFS ������������Ϊÿ���ڵ㱣���丸��㣻
ʹ�� BFS �������������������ӡ��Һ��ӡ�����㣩���������� K ��ʱ�������е�ȫ����㼴Ϊ����

ע�⣺

BFS Ҫ�����ѷ��ʽ�㣻
ÿ�ζ�����ǰ������ȫ��Ԫ����������һ����㣻

 */
void dfs(struct List *listFather, struct TreeNode* root, struct TreeNode* father)
{
	if (root == NULL) {
		return;
	}

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->cur = root;
	entry->father = father;
	entry->visited = 0;
	ListAddTail(listFather, &entry->node);

	dfs(listFather, root->left, root);
	dfs(listFather, root->right, root);
}

void setVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			entry->visited = 1;
		}
	}
}

bool checkVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->visited;
		}
	}

	return false;
}

struct TreeNode* getFather(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->father;
		}
	}

	return NULL;
}


int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
	struct List dListFather;
	struct List *listFather = &dListFather;

	ListInit(listFather);
	dfs(listFather, root, NULL); //��¼�����

	struct List dqueue;
	struct List *queue = &dqueue;

	queue_init(queue);

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->cur = target;
	ListAddTail(queue, &entry->node);
	setVisited(listFather, target);

	while(!queue_empty(queue)) {
		if (K-- == 0) {
			*returnSize = 0;
			int *res = (int *)calloc(2048, sizeof(int));
			while(!queue_empty(queue)) {
				struct DataEntry *pop = queue_pop_entry(queue);
				res[*returnSize] = pop->cur->val;
				(*returnSize)++;
			}

			return res;
		}

		int qSize = queue_size(queue);
		for (int i = 0; i < qSize; i++) {
			struct DataEntry *pop = queue_pop_entry(queue);
			if (pop->cur->left && !checkVisited(listFather, pop->cur->left)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->left;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->left);
			}

			if (pop->cur->right && !checkVisited(listFather, pop->cur->right)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->right;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->right);
			}

			struct TreeNode* father = getFather(listFather, pop->cur);
			if (father != NULL && !checkVisited(listFather, father)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = father;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, father);
			}
		}
	}

	return NULL;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define MAXSIZE 510
struct TreeNode** parent_array;
int flag[MAXSIZE];
int count;

void get_parent(struct TreeNode* node, struct TreeNode** parent_array);
void dfs(struct TreeNode* node, int K, int dis, int* res);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
    if (root == NULL || target == NULL || K < 0 || K > 500) {
        *returnSize = 0;
        return NULL;
    }

    // ��������������ڴ�
    parent_array = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAXSIZE);
    memset(parent_array, 0, MAXSIZE * sizeof(struct TreeNode*));
    // flag�����ʼ�������ڱ�Ƿ��ʹ��Ľ��
    memset(flag, 0, MAXSIZE * sizeof(int));
    // �������Ҫ��Ľ��ֵ�Ľ������
    int *res = (int *)malloc(sizeof(int) * MAXSIZE);
    memset(res, -1, MAXSIZE * sizeof(int));

    // �����������ҵ�ÿ�����ĸ���㣬���ý���ֵ��Ϊparent_array����������parent_array�д�Ŷ�Ӧ�����
    get_parent(root, parent_array);

    // DFS����
    count = 0;
    flag[target->val] = 1;
    dfs(target, K, 0, res);

    // ���ؽ��
    *returnSize = count;
    return res;
}

void get_parent(struct TreeNode* node, struct TreeNode** parent_array)
{
    if (node->right != NULL) {
        parent_array[node->right->val] = node;
        get_parent(node->right, parent_array);
    }
    if (node->left != NULL) {
        parent_array[node->left->val] = node;
        get_parent(node->left, parent_array);
    }
}

void dfs(struct TreeNode* node, int K, int dis, int* res)
{
    if (dis == K) {
        res[count] = node->val;
        count++;
        return;
    }

    if (node->left != NULL && flag[node->left->val] != 1) {
        flag[node->left->val] = 1;
        dfs(node->left, K, dis + 1, res);
    }

    if (node->right != NULL && flag[node->right->val] != 1) {
        flag[node->right->val] = 1;
        dfs(node->right, K, dis + 1, res);
    }

    if (parent_array[node->val] != 0 && flag[parent_array[node->val]->val] != 1) {
        flag[parent_array[node->val]->val] = 1;
        dfs(parent_array[node->val], K, dis + 1, res);
    }
}


/*
106. �����������������й��������
����һ��������������������������������

ע��:
����Լ�������û���ظ���Ԫ�ء�

���磬����

������� inorder = [9,3,15,20,7]
������� postorder = [9,15,7,20,3]
�������µĶ�������

    3
   / \
  9  20
    /  \
   15   7
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */



struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    if(postorderSize == 0 || inorderSize == 0)return NULL;      //Ҷ�ӽ�����������Ϊ��

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize-1];                     //�����ֵΪ����������һλ

    int left;
    for(left=0;left<inorderSize;left++){
        if(inorder[left] == root->val)break;                    //�ҵ������б��еĸ���㣬������Ϊ������������
    }
    int right = inorderSize - left - 1;                         //����������������

    root->left = buildTree(inorder,left,postorder,left);        //�ݹ鹹����������
    root->right = buildTree(inorder+left+1,right,postorder+left,right);

    return root;
}


