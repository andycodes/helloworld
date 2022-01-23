
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
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
			g_res[resIndex++] = deleteNode->left;
			dfs(deleteNode->left, to_delete, to_deleteSize);
		}

		if (deleteNode->right != NULL) {
			g_res[resIndex++] = deleteNode->right;
			dfs(deleteNode->right, to_delete, to_deleteSize);
		}
		return;
	}

	if (root->left != NULL) {
		if(isDelete(root->left, to_delete, to_deleteSize)) {
			struct TreeNode* deleteNode = root->left;
			root->left = NULL;
			if (deleteNode->left != NULL) {
				g_res[resIndex++] = deleteNode->left;
				dfs(deleteNode->left, to_delete, to_deleteSize);
			}
			if (deleteNode->right != NULL) {
				g_res[resIndex++] = deleteNode->right;
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
				g_res[resIndex++] = deleteNode->left;
				dfs(deleteNode->left, to_delete, to_deleteSize);
			}
			if (deleteNode->right != NULL) {
				g_res[resIndex++] = deleteNode->right;
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
	if (root == NULL || to_delete == NULL) {
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
	for (int i = 0; i < resIndex; i++) {
		if (isDelete(g_res[i], to_delete, to_deleteSize) == false) {
			res[fallyNum] = g_res[i];
			fallyNum++;
		}
	}

	*returnSize = fallyNum;
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MAXSIZE 510
struct TreeNode** parent;   //���ڱ���ڵ�ĸ��ڵ������
int flag[MAXSIZE];          //���ڱ���Ƿ��ѷ��ʵ����飺ֵΪ0��ʾδ���ʣ�ֵδ1��ʾ�ѷ���
int cnt;                    //���ڼ�¼�������Ľڵ����

//�����������������нڵ�ĸ��ڵ�洢��parent������
void get_parent(struct TreeNode* p, struct TreeNode** parent)
{
    //�����ǰ�ڵ�p������
    if(p->left != NULL)
    {
        parent[p->left->val] = p;      //������ֵλ�õ�parent����ֵ��Ϊp
        get_parent(p->left, parent);   //�ݹ������ǰ�ڵ������
    }
    //�����ǰ�ڵ�p���Һ���
    if(p->right != NULL)
    {
        parent[p->right->val] = p;    //���Һ���ֵλ�õ�parent����ֵ��Ϊp
        get_parent(p->right, parent); //�ݹ������ǰ�ڵ���Һ���
    }
}
//�ú����Ľ�����ǣ���ǰ�ڵ�ֵΪi����parent[i]���ǵ�ǰ�ڵ�ĸ��ڵ�


//�������������������p�ĸ��ڵ㡢���ӡ��Һ��� ���������������
void dfs(struct TreeNode*p, int K, int curdis, int* res)
{
    //�����ǰ����ΪK����ýڵ����Ҫ�ҵĽڵ�
    if(curdis == K)
    {
        res[cnt] = p->val;   //���ڵ�ֵ�洢�ڽ��������
        cnt++;               //cnt++����������һ���ڵ��Ѱ��
        return;
    }

    //���p�����Ӵ��ڣ������ӻ�δ�����ʹ�
    if(p->left!=NULL  &&  flag[p->left->val]!=1)
    {
        flag[p->left->val] = 1;            //����p������Ϊ�ѷ���
        dfs(p->left, K, curdis+1, res);    //�ݹ����p������
    }
    //���p���Һ��Ӵ��ڣ����Һ��ӻ�δ�����ʹ�
    if(p->right!=NULL  &&  flag[p->right->val]!=1)
    {
        flag[p->right->val] = 1;           //����p���Һ���Ϊ�ѷ���
        dfs(p->right, K, curdis+1, res);   //�ݹ����p���Һ���
    }

    //���p�ĸ��ڵ���ڣ��Ҹ��ڵ㻹δ�����ʹ�
    if(parent[p->val]!=0  &&  flag[parent[p->val]->val]!=1)
    {
        flag[parent[p->val]->val] = 1;        //����p�ĸ��ڵ�Ϊ�ѷ���
        dfs(parent[p->val], K, curdis+1, res);//�ݹ����p�ĸ��ڵ�
    }
}


int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
    //���⴦��
    if(root==NULL || target==NULL || K<0 || K>100)
    {
        *returnSize = 0;
        return NULL;
    }

    //��parent�������붯̬�ڴ沢��ʼ��
    parent = malloc(sizeof(struct TreeNode*) * MAXSIZE);
    memset(parent, 0, sizeof(struct TreeNode*)*MAXSIZE);

    //��ʼ��flag����
    memset(flag, 0, sizeof(int)*MAXSIZE);

    //����һ��������鲢���붯̬�ڴ棬��ʼ��
    int* res = malloc(sizeof(int)*MAXSIZE);
    memset(res, -1, sizeof(int)*MAXSIZE);

    //�������еĽڵ㣬������ڵ��ǵĸ��ڵ�
    get_parent(root, parent);

    cnt = 0;
    flag[target->val] = 1;   //��target�ڵ���Ϊ�ѷ���
    dfs(target, K, 0, res);  //����

    *returnSize = cnt;
    return res;
}

// ����һ��ָ��ǰ�ڵ㸸�׵Ĺ�ϣ�� father[5] = 3 C������ô�����ڵ㰡
void dfs(struct TreeNode* root, struct TreeNode** father, struct TreeNode* pre) {
    if (root != NULL) {
        father[root->val] = pre;
        dfs(root->left, father, root);
        dfs(root->right, father, root);
    }
}
int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize) {
    struct TreeNode* father[501];
    int visit[501] = {0};
    dfs(root, father, NULL);

    struct TreeNode* queue[501];
    int front = 0;
    int rear = 1;
    queue[front] = target;
    while (front < rear) {
        if (K-- == 0) {
            printf("  ");
            int *res = (int *)malloc(sizeof(int) * 501);
            *returnSize = 0;
            for (int i = front; i < rear; i++) {
                res[*returnSize] = queue[i]->val;
                (*returnSize)++;
            }
            return res;
        }
        int len =  rear - front;
        for (int j = 0; j < len; j++) {
            if (father[queue[front]->val] != NULL && visit[queue[front]->val] == 0) {
                queue[rear] = father[queue[front]->val];
                visit[queue[front]->val] = 1;
                rear++;
            }
            if (queue[front]->left != NULL && visit[queue[front]->left->val] == 0) {
                queue[rear] = queue[front]->left;
                visit[queue[front]->left->val] = 1;
                rear++;
            }
            if (queue[front]->right != NULL && visit[queue[front]->right->val] == 0) {
                queue[rear] = queue[front]->right;
                visit[queue[front]->right->val] = 1;
                rear++;
            }
            front++;
        }

    }
    *returnSize = 0;
    return NULL;
}


/*
337. ��ҽ��� III
���ϴδ����һ���ֵ�֮���һȦ���ݺ�С͵�ַ�����һ���µĿ����Եĵ������������ֻ��һ����ڣ����ǳ�֮Ϊ�������� ���ˡ�����֮�⣬ÿ����������ֻ��һ��������������֮������һ�����֮�󣬴�����С͵��ʶ��������ط������з��ݵ�����������һ�ö��������� �������ֱ�������ķ�����ͬһ�����ϱ���٣����ݽ��Զ�������

�����ڲ���������������£�С͵һ���ܹ���ȡ����߽�

ʾ�� 1:

����: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \
     3   1

���: 7
����: С͵һ���ܹ���ȡ����߽�� = 3 + 3 + 1 = 7.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int rob(struct TreeNode *root)
{
    if (root == NULL) return 0;

    int money = root->val;
    if (root->left != NULL) {
        money += (rob(root->left->left) + rob(root->left->right));
    }

    if (root->right != NULL) {
        money += (rob(root->right->left) + rob(root->right->right));
    }

    return fmax(money, rob(root->left) + rob(root->right));
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct SubtreeStatus {
    int selected;
    int notSelected;
};

struct SubtreeStatus dfs(struct TreeNode *root) {
    if (!root) {
        return (struct SubtreeStatus){0, 0};
    }
    struct SubtreeStatus l = dfs(root->left);
    struct SubtreeStatus r = dfs(root->right);
    int selected = root->val + l.notSelected + r.notSelected;
    int notSelected = fmax(l.selected, l.notSelected) + fmax(r.selected, r.notSelected);
    return (struct SubtreeStatus){selected, notSelected};
}

int rob(struct TreeNode *root) {
    struct SubtreeStatus rootStatus = dfs(root);
    return fmax(rootStatus.selected, rootStatus.notSelected);
}

/*
563. ���������¶�
����һ�������������� ������ ���¶� ��

һ������ �ڵ���¶� ���弴Ϊ���ýڵ��������Ľڵ�֮�ͺ��������ڵ�֮�͵� ��ľ���ֵ �����û���������Ļ����������Ľڵ�֮��Ϊ 0 ��û���������Ļ�Ҳ��һ�����ս����¶��� 0 ��

������ ���¶Ⱦ��������нڵ���¶�֮�͡�
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int tilt=0;
int traverse(struct TreeNode * root)
    {
        if(root==NULL )
            return 0;
        int left=traverse(root->left);
        int right=traverse(root->right);
        tilt+=fabs(left-right);
        return left+right+root->val;
    }

int findTilt(struct TreeNode * root)
{
	tilt = 0;
	traverse(root);
        return tilt;
}