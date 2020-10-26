/*
454. ������� II
�����ĸ����������������б� A , B , C , D ,�����ж��ٸ�Ԫ��
(i, j, k, l) ��ʹ�� A[i] + B[j] + C[k] + D[l] = 0��
Ϊ��ʹ����򵥻������е� A, B, C, D ������ͬ�ĳ��� N����
0 �� N �� 500 �����������ķ�Χ�� -228 �� 228 - 1 ֮�䣬���ս��
���ᳬ�� 231 - 1 ��
����:
����:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]
���:
2
����:
����Ԫ������:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
*/

typedef struct hash{
    int key;
    int count;
    UT_hash_handle hh;
}*hash_;

int fourSumCount(int* A, int ASize, int* B, int BSize, int* C, int CSize, int* D, int DSize)
{
    hash_ p1 = NULL,t = NULL,p2 = NULL;
    for(int i = 0;i < ASize;i++)
        for(int j = 0; j < ASize;j++){
            int tar = A[i]+B[j];
            HASH_FIND_INT(t, &tar, p1);
            if(!p1){
                p1 = (hash_)malloc(sizeof(*p1));
                p1->key = tar;
                p1->count = 0;
                HASH_ADD_INT(t, key, p1);
            }
            p1->count++;
        }
    int count = 0;
    for(int i = 0;i < ASize;i++)
        for(int j = 0; j < ASize;j++){
            int tar = -(C[i]+D[j]);
            HASH_FIND_INT(t, &tar, p2);
            if(p2)
                count += p2->count;
        }
    return count;
}

/*
������ 16.21. ������
�Ѷ��е�5
���������������飬�뽻��һ����ֵ��ÿ��������ȡһ����
ֵ����ʹ��������������Ԫ�صĺ���ȡ�
����һ�����飬��һ��Ԫ���ǵ�һ��������Ҫ������Ԫ�أ�
�ڶ���Ԫ���ǵڶ���������Ҫ������Ԫ�ء����ж���𰸣�
��������һ�����ɡ�����������������ֵ�����ؿ����顣
ʾ��:
����: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
���: [1, 3]
ʾ��:
����: array1 = [1, 2, 3], array2 = [4, 5, 6]
���: []
*/
/*
������������Ĳ�ֵdiff = sum(a)-sum(b), ���Ϊ����ֱ��return [], ��Ϊ
�����κ����õ���diffһ�����������ֲ�ֵ��2��
Ȼ������b��Ϊ����, ��������a, �ж���ÿ��Ԫ��-diff//2�Ƿ�
��b������, �ڵĻ���Ϊ����
�������������Ĳ�ֵһ����2d = (sum(A) - sum(B))
*/

struct Hashmap {
    int value;
    UT_hash_handle hh;
};

int* findSwapValues(int* array1, int array1Size,
int* array2, int array2Size, int* returnSize)
{
	int sum1 = 0;
	int sum2 = 0;
	struct Hashmap *hashmap = NULL;
	struct Hashmap *find = NULL;
	struct Hashmap *s, *tmp;


	*returnSize = 0;

	for (int i = 0; i < array1Size; i++) {
		sum1 += array1[i];
	}

	for (int i = 0; i < array2Size; i++) {
		sum2 += array2[i];
		struct Hashmap *node = (struct Hashmap *)calloc(1, sizeof(struct Hashmap));
		node->value = array2[i];
		HASH_ADD_INT(hashmap, value, node);
	}

	int diff = sum1 - sum2;
	if (diff % 2) {
		return NULL;
	}

	for (int i = 0; i < array1Size; i++) {
		int target = array1[i] - (sum1 - sum2) / 2;
		HASH_FIND_INT(hashmap, &target, find);
		if (find != NULL) {
			int *res = (int *)calloc(2, sizeof(int));
			res[0] = array1[i];
			res[1] = target;
			*returnSize = 2;
			return res;
		}
	}

	HASH_ITER(hh, hashmap, s, tmp) {
		HASH_DEL(hashmap, s);
		free(s);
	}

	return NULL;
}


/*
820. ���ʵ�ѹ������
�Ѷ��е�165
����һ�������б����ǽ�����б�����һ�������ַ���
S ��һ�������б� A��
���磬�������б��� ["time", "me", "bell"]�����ǾͿ��Խ����ʾ
Ϊ S = "time#bell#" �� indexes = [0, 2, 5]��
����ÿһ�����������ǿ���ͨ�����ַ��� S ��������λ�ÿ�
ʼ��ȡ�ַ�����ֱ�� "#" ���������ָ�����֮ǰ�ĵ����б�
��ô�ɹ��Ը��������б���б������С�ַ��������Ƕ���
�أ�
ʾ����
����: words = ["time", "me", "bell"]
���: 10
˵��: S = "time#bell#" �� indexes = [0, 2, 5] ��
��ʾ��
1.	1 <= words.length <= 2000
2.	1 <= words[i].length <= 7
3.	ÿ�����ʶ���Сд��ĸ ��
*/
int cmp_w(const void *a, const void *b)
{
	char *str1 = *((char **)a);
	char *str2 = *((char **)b);

	return strlen(str2) - strlen(str1);
}

int minimumLengthEncoding(char ** words, int wordsSize)
{
	qsort(words, wordsSize, sizeof(words[0]), cmp_w);
	char *s = (char *)calloc(102400, sizeof(char));
	char tmp[102400];
	for (int i = 0;i < wordsSize; i++) {
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, words[i]);
		strcat(tmp, "#");
		if (strstr(s, tmp) == NULL) {
			strcat(s, tmp);
		}
	}

	return strlen(s);
}

/*
554. שǽ
�����ǰ��һ�·��εġ��ɶ���ש����ɵ�שǽ�� ��Щש��
�߶���ͬ���ǿ�Ȳ�ͬ��������Ҫ��һ���Զ����µġ�����
����ש��Ĵ��ߡ�
שǽ���е��б��ʾ�� ÿһ�ж���һ�������������ÿ��ש
�Ŀ�ȵ������б�
����㻭����ֻ�Ǵ�ש��ı�Ե�������Ͳ��㴩�����ש��
����Ҫ�ҳ�����������ʹ�����ߴ�����ש���������٣�����
���ش�����ש��������
�㲻������ǽ��������ֱ��Ե֮һ���ߣ�������Ȼ��û�д�
��һ��ש�ġ�

ʾ����
����: [[1,2,2,1],
      [3,1,2],
      [1,3,2],
      [2,4],
      [3,1,2],
      [1,3,1,1]]

���: 2

*/
int leastBricks(int** wall, int wallSize, int* wallColSize)
{
	short xgap[60000] = {0}; /*���� ��϶λ��*/
	int i, j, gappos;
	int row = wallSize;

	for (i = 0; i < row; i++) {
		gappos = 0;
		for (j = 0; j < wallColSize[i] - 1; j++) {
			gappos += wall[i][j];
			xgap[gappos]++; /* ÿ���ۼ���λ�÷�϶���� */
		}
	}

	int maxGap = 0;
	for (i = 0; i < 60000; i++){
		maxGap = fmax(maxGap, xgap[i]);
	}

    return wallSize - maxGap;
}

/*
204. ��������
ͳ������С�ڷǸ����� n ��������������
ʾ�� 1��
���룺n = 10
�����4
���ͣ�С�� 10 ������һ���� 4 ��, ������ 2, 3, 5, 7 ��
ʾ�� 2��
���룺n = 0
�����0
ʾ�� 3��
���룺n = 1
�����0
*/
int countPrimes(int n)
{
	int count = 0;
	if (n == 0) {
		return 0;
	}

	bool map[n];
	//��ʼĬ��������Ϊ����
	for (int i = 0; i < n; i++) {
		map[i] = true;
	}

	for (int i = 2; i < n; i++) {
		if (map[i]) {
			count++;
			for (int j = i + i; j < n; j += i) {
				//�ų�������������
				map[j] = false;
			}
		}
	}

	return count;
}

