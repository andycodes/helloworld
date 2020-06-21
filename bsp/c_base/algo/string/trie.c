/*
面试题 17.17. 多次搜索
难度中等5
给定一个较长字符串big和一个包含较短字符串的数组smalls，设计一个方法，根据smalls中的每一个较短字符串，对big进行搜索。输出smalls中的字符串在big里出现的所有位置positions，其中positions[i]为smalls[i]出现的所有位置。
示例：
输入：
big = "mississippi"
smalls = ["is","ppi","hi","sis","i","ssippi"]
输出： [[1,4],[8],[],[3],[1,4,7,10],[5]]

*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct node{
    int id;
    int num;
    bool isend;
    struct node* next[26];
}st_node;

void find(char* big, int start, st_node* root,int** res, int* size) {
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

void insert(char* smalls, st_node* root, int start) {
    for(int i=0;i<strlen(smalls);i++){
        if(root->next[smalls[i]-'a'] == NULL) {
            root->next[smalls[i]-'a'] =(st_node*)calloc(1,sizeof(st_node));
        }
            root=root->next[smalls[i]-'a'];
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

int** multiSearch(char* big, char** smalls, int smallsSize, int* returnSize, int** returnColumnSizes)
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