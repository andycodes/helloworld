/*
�Ӵ�������������

1) ����
	right
	sum += nums[right++];
2)right++
	ָ��δ����ĵ�Ԫ


��������һ����ָ��left��һ����ָ��right��
���ִ��ڻ�����ʽ��
while(right < slen) {
	do---
	right++ or continue;

	����������ѡ����
	left++;
}


for (int right = 0; right < slen; right++) {
		do--
		��������ѡ����
		left++;
}


*/

/*
3. ���ظ��ַ�����Ӵ�
�Ѷ��е�6
����ַ������ҳ�һ����Ĳ������ظ��ַ������ַ�����
���������ַ����ĳ��ȡ�

ʾ�� 1:
����: "abcabcbb"
���: 3
����: ��Ϊ���ظ��ַ�����Ӵ��� "abc"�������䳤��Ϊ 3��
ʾ�� 2:
����: "bbbbb"
���: 1
����: ��Ϊ���ظ��ַ�����Ӵ��� "b"�������䳤��Ϊ 1��
ʾ�� 3:
����: "pwwkew"
���: 3
����: ��Ϊ���ظ��ַ�����Ӵ��� "wke"�������䳤��Ϊ 3��
     ��ע�⣬��Ĵ𰸱����� �Ӵ� �ĳ��ȣ�
"pwke" ��һ�������У������Ӵ���

*/
int lengthOfLongestSubstring(char* s)
{
	int left = 0;
	int right = 0;
	int slen = strlen(s);

	if (s == NULL) {
		return 0;
	}

	int map[128] = {0};
	int ret = 0;
	while(right < slen) {
		if (map[s[right]] == 0) {
			map[s[right++]] = 1;
			ret = fmax(ret, right - left);
			continue;
		}

		map[s[left++]]--;
	}

	return ret;
}


/*
1004. �������1�ĸ��� III
�Ѷ��е�41
����һ�������� 0 �� 1 ��ɵ����� A�����������Խ� K ��ֵ��
0 ��� 1 ��
���ؽ����� 1 �����������������ĳ��ȡ�
ʾ�� 1��
���룺A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
�����6
���ͣ�
[1,1,1,0,0,1,1,1,1,1,1]
�������ִ� 0 ��ת�� 1����������鳤��Ϊ 6��
*/
int longestOnes(int* A, int ASize, int K)
{
	int left = 0;
	int right = 0;
	int res = 0;

	while(right < ASize) {
		if (A[right] == 1) {
			right++;
			res = fmax(res, right - left);
			continue;
		}

		if (A[right] == 0 && K > 0) {
			right++;
			K--;
			res = fmax(res, right - left);
			continue;
		}

		if(A[left++] == 0) {
			K++;
		}
	}

	return res;
}

int longestOnes(int* A, int ASize, int K)
{
	//cnt����ͳ�ƴ�����0�ĸ���
	int left=0,right=0, cnt=0,res=0,size=ASize;
	while(right < size) {
		cnt += (A[right] == 0);
		while (cnt > K) {////��������0�ĸ�������Kʱ����Ҫ��С����
			cnt -= (A[left] == 0);
			left++;
		}
		////������0�ĸ���С�ڵ���kʱ��Ҳ���ǿ��Ըô����ڵ�0�������滻�����ݸô��ڳ�����ȷ���Ƿ����res
		res = fmax(res, right-left+1);
		right++;
	}

	return res;
}

/*
424. �滻�����ظ��ַ�
�Ѷ��е�73
����һ�����ɴ�дӢ����ĸ��ɵ��ַ���������Խ�����λ
���ϵ��ַ��滻��������ַ����ܹ�������滻 k �Ρ���ִ��
�����������ҵ������ظ���ĸ����Ӵ��ĳ��ȡ�
ע��:
�ַ������� �� k ���ᳬ�� 104��
ʾ�� 1:
����:
s = "ABAB", k = 2

���:
4

����:
������'A'�滻Ϊ����'B',��֮��Ȼ��

*/

/*
��ָ�뿪ʼ���ƣ����󴰿ڣ�ֱ�������ڳ��˳��ִ��������ַ�����������ַ������ﵽk
��ָ�����ƶ��ᳬ��kʱ����ָ�뿪ʼͬʱ�ƶ�����ʱ���ڰ���֮ǰ�Ĵ�С��ʼ������Ȼ����ָ������ƶ�ֱ�������ַ��������ٴγ���k�����ƣ���ָ���ֿ�ʼͬʱ�ƶ������ѭ����ȥֱ����ָ���ƶ����ַ����յ㡣���ߣ�seerjjj���ӣ�https://leetcode-cn.com/problems/longest-repeating-character-replacement/solution/hua-dong-chuang-kou-suan-fa-cban-by-seerjjj/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
int characterReplacement(char * s, int k)
{
	int left = 0;
	int right = 0;
	int maxCnt = 0;
	int ans = 0;
	int map[26] = {0};

	while(right < strlen(s)) {
		map[s[right] - 'A']++;
		maxCnt = fmax(maxCnt, map[s[right] - 'A']);
		if (right - left + 1 > maxCnt + k) {
			map[s[left] - 'A']--;
			left++;
		}
		ans = fmax(ans, right-left+1);
		right++;
	}

	//return ans;
	return strlen(s) - left;
}

/*
������ 17.18. ��̳���
�Ѷ��е�5
���������������飬һ����һ���̣��̵�Ԫ�ؾ�����ͬ����
���������а������������е�Ԫ�ص���������飬�����˳
���޹ؽ�Ҫ��
����������������˵���Ҷ˵㣬���ж��������������
���飬������˵���С��һ�����������ڣ����ؿ����顣
ʾ�� 1:
����:
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
���: [7,10]
ʾ�� 2:
����:
big = [1,2,3]
small = [4]
���: []
*/
int* shortestSeq(int* big, int bigSize, int* small, int smallSize, int* returnSize)
{
	if (big == NULL || small == NULL || bigSize <= 0 || smallSize <= 0 || smallSize > bigSize) {
		*returnSize = 0;
		return NULL;
	}

	struct HashTable ht;
	int ret = HashInit(&ht, smallSize, hashequal_int, hashcode_int);

	for (int i = 0; i < smallSize; i++) {
		hashPushKey(&ht, small[i]);
	}

	int left = 0, right = 0, winCnt = 0, minLen= INT_MAX;
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	while(right < bigSize) {
		struct DataEntry *curEntry = hashFindKey(&ht, big[right]);
		if(curEntry != NULL) {
			if (curEntry->value == 0) {
				winCnt++;
			}

			curEntry->value++;
		}

		while(winCnt == smallSize) {
			struct DataEntry *entry = hashFindKey(&ht, big[left]);
			if (entry == NULL) {
				left++;
			} else if (entry->value > 1) {
				entry->value--;
				left++;
			} else {//value == 1
				if (minLen > right-left + 1) {
					minLen = right-left + 1;
					res[0] = left;
					res[1] = right;
				}

				entry->value--;
				left++;
				winCnt--;
			}
		}

		right++;
	}

	if (minLen == INT_MAX) {
		*returnSize = 0;
		return NULL;
	}

	return res;
}


/*
159. �������������ͬ�ַ�����Ӵ�
����һ���ַ��� s ���ҳ� ���� ��������
��ͬ�ַ�����Ӵ� t ��
ʾ�� 1:
����: "eceba"
���: 3
����: t �� "ece"������Ϊ3��
ʾ�� 2:
����: "ccaabbb"
���: 5
����: t �� "aabbb"������Ϊ5��
*/
int lengthOfLongestSubstringTwoDistinct(char * s)
{
	int slen = strlen(s);
	if (slen <= 2)
		return slen;

	int left = 0;
	int max = 0;

	while( left + max < slen) {
		int tempLeft = left;

		while(left < slen && s[left] == s[tempLeft]) {
			left++;
		}

		int right = left;
		int tempRight = right;

		while(right < slen && (s[right] == s[tempRight] || s[right] == s[tempLeft] )) {
			right++;
		}

		max = fmax(max, right - tempLeft);
		left = tempRight;
	}

	return max;
}


/*
658. �ҵ� K ����ӽ���Ԫ��
�Ѷ��е�84
����һ������õ����飬�������� k �� x�����������ҵ��
�� x������֮����С���� k ���������صĽ������Ҫ�ǰ�����
�źõġ�������������� x �Ĳ�ֵһ��������ѡ����ֵ��С
���Ǹ�����
ʾ�� 1:
����: [1,2,3,4,5], k=4, x=3
���: [1,2,3,4]

ʾ�� 2:
����: [1,2,3,4,5], k=4, x=-1
���: [1,2,3,4]
*/
int gX;
int cmp_int1(const void *a, const void *b)
{
	int aa = *((int *)a);
	int bb = *((int *)b);

	if (abs(aa - gX) == abs(bb - gX)) {
		return aa - bb;
	}

	return abs(aa - gX) > abs(bb - gX);
}

int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
	gX = x;
	*returnSize = k;
	qsort(arr, arrSize, sizeof(arr[0]), cmp_int1);
	qsort(arr, k, sizeof(arr[0]), cmp_int);
	return arr;
}

/*
�ų�����˫ָ�룩
��� x ��ֵ���ڳ���Ϊ size �����ڣ���һ����ȣ���Ҫ�õ�
size - 1 �������������ӽ���Ԫ�أ���ʱ�����ұ߽磺
1�������߽��� x �Ĳ�ֵ�ľ���ֵ��С��ɾ���ұ߽磻
2������ұ߽��� x �Ĳ�ֵ�ľ���ֵ��С��ɾ����߽磻
3��������ұ߽��� x �Ĳ�ֵ�ľ���ֵ��ȣ�ɾ���ұ߽硣
*/
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
	int left = 0;
	int right = arrSize - 1;
	*returnSize = k;

	while(right - left >= k) {
		if (x - arr[left] <= arr[right] - x) {// 2 *x <= arr[left] + arr[right]
			right--;
		} else {
			left++;
		}
	}

	return arr + left;
}


/*
������ 17.11. ���ʾ���
�Ѷ��е�2
�и��ں����ʵĳ����ı��ļ������������������ʣ��ҳ���
����ļ������������ʵ���̾���(���������)�����Ѱ��
����������ļ��л��ظ���Σ���ÿ��Ѱ�ҵĵ��ʲ�ͬ��
���ܶԴ��Ż���?
ʾ����
���룺words = ["I","am","a","student","from","a","university","in","a","city"], word1 = "a",
word2 = "student"
�����1

*/
int findClosest(char** words, int wordsSize, char* word1, char* word2)
{
	int min = wordsSize;
	int w1Idx = wordsSize;
	int w2Idx = wordsSize;
	for (int i = 0; i < wordsSize; i++) {
		if (strcmp(words[i], word1) == 0) {
			w1Idx = i;
		}

		if (strcmp(words[i], word2) == 0) {
			w2Idx = i;
		}

		if (w1Idx != wordsSize && w2Idx != wordsSize) {
			min = fmin(min, abs(w1Idx - w2Idx));
		}

	}

	return min;
}

/*
18. ����֮��
����һ������ n ������������ nums ��һ��Ŀ��ֵ target��
�ж� nums ���Ƿ�����ĸ�Ԫ�� a��b��c �� d ��ʹ�� a + b + c + d ��
ֵ�� target ��ȣ��ҳ��������������Ҳ��ظ�����Ԫ�顣
ע�⣺
���в����԰����ظ�����Ԫ�顣
ʾ����
�������� nums = [1, 0, -1, 0, -2, 2]���� target = 0��
����Ҫ�����Ԫ�鼯��Ϊ��
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/


int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){

	int **ret = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	for (int a = 0; a < numsSize - 3; a++) {
		if(a > 0 && nums[a] == nums[a - 1])
			continue;

		if(nums[a]+nums[a+1]+nums[a+2]+nums[a+3]>target) break;
		if(nums[a]+nums[numsSize-3]+nums[numsSize-2]+nums[numsSize-1]<target) continue;
		for (int b = a + 1; b < numsSize - 2; b++) {
			if(nums[a]+nums[b]+nums[b+1]+nums[b+2]>target) break;
			 if(nums[a]+nums[b]+nums[numsSize-2]+nums[numsSize-1]<target) continue;
			if(b > a + 1 && nums[b] == nums[b -1])
				continue;

			int c = b + 1;
			int d = numsSize - 1;

			while(c < d) {
				int sum = nums[a] + nums[b] + nums[c] + nums[d];
				if (sum < target) {
					c++;
				} else if (sum > target) {
					d--;
				} else {
					ret[*returnSize] = (int *)calloc(4, sizeof(int));
					ret[*returnSize][0] = nums[a];
					ret[*returnSize][1] = nums[b];
					ret[*returnSize][2] = nums[c];
					ret[*returnSize][3] = nums[d];
					(*returnColumnSizes)[*returnSize] = 4;
					(*returnSize)++;
					while(c<d&&nums[c+1]==nums[c])
	        				    c++;
	        			while(c<d&&nums[d-1]==nums[d])
	        				    d--;

					c++;
					d--;
				}
			}
		}
	}

	return ret;
}


/*
713. �˻�С��K��������
�Ѷ��е�135
����һ������������ nums��
�ҳ��������ڳ˻�С�� k ��������������ĸ�����
ʾ�� 1:
����: nums = [10,5,2,6], k = 100
���: 8
����: 8���˻�С��100��������ֱ�Ϊ:
[10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]��
��Ҫע����� [10,5,2] �����ǳ˻�С��100�������顣
˵��:
"	0 < nums.length <= 50000
"	0 < nums[i] < 1000
"	0 <= k < 10^6

*/
int numSubarrayProductLessThanK(int* nums, int numsSize, int k)
{
        if (k <= 1)
			return 0;

        int prod = 1, ans = 0, left = 0;
        for (int right = 0; right < numsSize; right++) {
            prod *= nums[right];
            while (prod >= k) {
				prod /= nums[left++];
            }
/*��ָ��ÿ����һλ������ָ��Ϊ�����������飬
[5,2]��6������[6]��[2,6]��[5,2,6]��������ΪR - L+ 1*/
            ans += right - left + 1;
        }
        return ans;
}


/*
76. ��С�����Ӵ�
�Ѷ�����695
����һ���ַ��� S��һ���ַ��� T ���������һ���㷨������
�� O(n) ��ʱ�临�Ӷ��ڣ����ַ��� S �����ҳ������� T ������
������С�Ӵ���

ʾ����
���룺S = "ADOBECODEBANC", T = "ABC"
�����"BANC"

*/
#define MAX_HASH_LEN 128
char * minWindow(char * s, char * t)
{
	int slen = strlen(s);
	int tlen = strlen(t);
	if (slen == 0 || tlen == 0 || slen < tlen) {
		return "";
	}

	int maps[MAX_HASH_LEN] = {0};
	int mapt[MAX_HASH_LEN] = {0};
	int i;
	int left = 0, right = 0;
	int matchSize = 0;
	int minLen = slen + 1; // Сϸ�� ��֤s��t��һ���ַ�Ҳ�ܴ���
	int minLeft = 0;
	int minRight = 0;
	int index = 0;

	for (i = 0; i < tlen; i++) {
		mapt[t[i]]++;
	}

	while (right < slen) {
		char c = s[right];
		right++;
		// �������� tƥ�䲻����right����+1
		if (mapt[c] == 0) {
			continue;
		}

		if (maps[c] < mapt[c]) {
			matchSize++;  /*����С��t�ַ������ۼ�������Ч*/
		}

		maps[c]++;

		while (matchSize == tlen) {/*���� T �����ַ� ��ʼ����С*/
			if (right - left < minLen) {
				// ���¼�¼
				minLeft = left;
				minRight = right;
				minLen = right - left;
			}

			char d = s[left];
			left++;
			// ��������mapt[d] == 0 ��ʶleft��ָԪ�طǹؼ�
			if (mapt[d] == 0) {
				continue;
			}

			maps[d]--;
			if (maps[d] < mapt[d]) {
				matchSize--;
			}
		}
	}

	s[minRight] = '\0';
	return &s[minLeft];
}


/*
632. ��С����
�Ѷ�����230
���� k ���������е������б��ҵ�һ����С���䣬ʹ�� k ��
�б��е�ÿ���б�������һ�������������С�
���Ƕ������ b-a < d-c ������ b-a == d-c ʱ a < c�������� [a,b] �� [c,d] С��

ʾ����
���룺[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
�����[20,24]
���ͣ�
�б� 1��[4, 10, 15, 24, 26]��24 ������ [20,24] �С�
�б� 2��[0, 9, 12, 20]��20 ������ [20,24] �С�
�б� 3��[5, 18, 22, 30]��22 ������ [20,24] �С�
*/
#define RETURN_SIZE 2
#define MAX_NUM 3500

typedef struct tagInfo {
	int value;
	int group;
} Info;

int cmpFun(const void *a, const void *b)
{
	Info *temp1 = (Info *)a;
	Info *temp2 = (Info *)b;

	return temp1->value > temp2->value;
}

int isCover(int *kCount, int k)
{
	for (int i = 0; i < k; i++) {
		if (kCount[i] == 0) {
			return 0;
		}
	}
	return 1;
}

void updateIndex(int left, int right, int *resBegin, int *resEnd, Info *allNum)
{
	if ((*resBegin == -1) ||
		(allNum[right].value - allNum[left].value < allNum[*resEnd].value - allNum[*resBegin].value) ||
		(allNum[right].value - allNum[left].value == allNum[*resEnd].value - allNum[*resBegin].value &&
		left < *resBegin)) {
		*resBegin = left;
		*resEnd = right;
	}
}

int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize)
{
	int numTotalSize = 0;
	for (int i = 0; i < numsSize; i++) {
		numTotalSize += numsColSize[i];
	}

	Info allNum[numTotalSize];

	int allNumSize = 0;
	for (int i = 0; i < numsSize; i++) {
		for (int j = 0; j < numsColSize[i]; j++) {
			allNum[allNumSize].value = nums[i][j];
			allNum[allNumSize].group = i;
			allNumSize++;
		}
	}

	int kCount[MAX_NUM] = { 0 };
	qsort(allNum, numTotalSize, sizeof(Info), cmpFun);
	int left = 0;
	int right = 0;
	int resBegin = -1;
	int resEnd = -1;
	while (right < numTotalSize) {

		kCount[allNum[right].group]++;

		while (isCover(kCount, numsSize)) {//��������С
			updateIndex(left, right, &resBegin, &resEnd, allNum);
			kCount[allNum[left++].group]--;
		}

		right++;
	}

	int *res = (int *)malloc(sizeof(int) * RETURN_SIZE);
	res[0] = allNum[resBegin].value;
	res[1] = allNum[resEnd].value;
	*returnSize = RETURN_SIZE;
	return res;
}

/*
80. ɾ�����������е��ظ��� II
�Ѷ��е�271�ղط����л�ΪӢ�Ĺ�ע����
����һ���������飬����Ҫ��ԭ��ɾ���ظ����ֵ�Ԫ�أ�
ʹ��ÿ��Ԫ�����������Σ������Ƴ���������³��ȡ�
��Ҫʹ�ö��������ռ䣬�������ԭ���޸��������鲢��
ʹ�� O(1) ����ռ����������ɡ�
ʾ�� 1:
���� nums = [1,1,1,2,2,3],
����Ӧ�����³��� length = 5, ����ԭ�����ǰ���Ԫ�ر��޸�
Ϊ 1, 1, 2, 2, 3 ��
�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�
*/
//��̬������λ����
int removeDuplicates(int* nums, int numsSize)
{
	int flag = 0, temp = 0;
	for(int i = 1;i < numsSize; i++) {
		if(nums[i] == nums[i-1])
			flag++; //����
		else
			flag = 0;  //��������0

		if(flag >= 2)
			temp++;  //��λ�����1

		nums[i - temp] = nums[i]; //��λ
	}

	return numsSize - temp;
}


/*
1176. ����ƻ�����
��ĺ�����һλ�������ߡ�ǰ�����ӣ������Լ��ƶ���һ
�ݽ���ƻ��������������������һ����ݼƻ��Ƿ����
������һ�ݼƻ����ĵĿ�·������� calories[i] �����������
λ�����ڵ� i ����Ҫ���ĵĿ�·��������
Ϊ�˸��õ�������ݼƻ������ڿ�·����е�ÿһ�죬�㶼
��Ҫ������ ����һ���Լ�֮����������졹 ���� k �죩����
�ĵ��ܿ�·�� T��
��� T < lower����ô��ݼƻ������⣬��ʧȥ 1 �֣�
��� T > upper����ô��ݼƻ�������㣬����� 1 �֣�
������ݼƻ�����ͨͨ����ֵ�����䶯��
�뷵��ͳ�������� calories.length ���õ����ܷ���Ϊ���������
ע�⣺�ֿܷ����Ǹ�����
ʾ�� 1��
���룺calories = [1,2,3,4,5], k = 1, lower = 3, upper = 3
�����0
���ͣ�calories[0], calories[1] < lower �� calories[3], calories[4] > upper, �ܷ� = 0.
*/
int dietPlanPerformance(int* calories, int caloriesSize, int k, int lower, int upper)
{
	int index = 0;
	int score = 0;
	int sum = 0;

	for (; index < k; index++) {
		sum += calories[index];
	}

	for (; ; index++) {
		if (sum < lower) {
			score--;
		} else if (sum > upper) {
			score++;
		}

		if (index == caloriesSize) {
			break;
		}

		sum += calories[index] - calories[index - k];
	}
	return score;
}


/*
1040. �ƶ�ʯ��ֱ������ II
��һ���������޵������ϣ��� i ��ʯ�ӵ�λ��Ϊ stones[i]�����
һ��ʯ�ӵ�λ����С/�����ô��ʯ�ӱ������˵�ʯ�ӡ�
ÿ���غϣ�����Խ�һ�Ŷ˵�ʯ�������ƶ���һ��δռ��
��λ�ã�ʹ�ø�ʯ�Ӳ�����һ�Ŷ˵�ʯ�ӡ�
ֵ��ע����ǣ����ʯ���� stones = [1,2,5] �������㽫�޷��ƶ�
λ��λ�� 5 �Ķ˵�ʯ�ӣ���Ϊ���۽����ƶ����κ�λ�ã���
�� 0 �� 3������ʯ�Ӷ���Ȼ���Ƕ˵�ʯ�ӡ�
�����޷������κ��ƶ�ʱ��������Щʯ�ӵ�λ������ʱ����
Ϸ������
Ҫʹ��Ϸ�����������ִ�е���С������ƶ������ֱ��Ƕ�
�٣� �Գ���Ϊ 2 ��������ʽ���ش𰸣�
answer = [minimum_moves, maximum_moves] ��
ʾ�� 1��
���룺[7,4,9]
�����[1,2]
���ͣ�
���ǿ����ƶ�һ�Σ�4 -> 8����Ϸ������
���ߣ����ǿ����ƶ����� 9 -> 5��4 -> 6����Ϸ������
*/
/*
�ٸ����ӣ���ʼʱ�� 8 ��ʯ�ӣ��������ϵ���ʯ�ӵĿ̶�Ϊ��
4��6��8��9��15��16��19��20���ֵ��ⷽ����ʯ�ӿ��Է��õ�
�ռ䣬������������ʯ��֮���δռ��λ�á��������У�һ
���� 20-4+1-8 ��λ�á�ʯ�Ӹ��ǵ��߶γ����� 20-4 ��������һ
���˵��λ�ü� 20-4+1���ټ�ȥ�Ѿ�ռ�õ� 8 ��λ�á��ù�ʽ
��ʾΪ��s1=stones[n-1]-stones[0]+1-ns1=stones[n?1]?stones[0]+1?n�����ǵ�һ��
�ƶ�����˵���Ҷ˵��ʯ�Ӻ�����ƶ���ʯ�Ӻ�������
���ǿ�ʯ��֮��Ŀռ䣬����Ͳ��ܱ������ˣ���Ϊ������
�ڵ��Ǹ����Ϊ�˵㣬����֮���λ�ò����Ա������ˡ���
���һ���ƶ��� 4����ô 5 ���λ�þͲ����ܷ���ʯ���ˡ�
����Ҫ���㲻�ܱ����ʵĿռ�
s2=min(stones[n-1]-stones[n-2]-1, stones[1]-stones[0] -1)s2=min(stones[n?1]?stones[n?2]?1,stones[1]?stones[0]?1)��
���ֵΪ s1-s2����Ϊ�ں���Ĳ�������Ƕ�����������
�ԣ���ÿһ�����Ҷ˵�Ĳ�ֵֻ�� 1����Сֵ��ⷽ����
��������Ϸ��������ôһ���� nn ���������������ʯ�ӡ�
�������Ҫ�ƶ����٣��ض�Ҫ��һ��ʯ�����У�ʹ���� nn ��
С�����������ڣ���ʼʱ������ʯ�ӡ������и����ӣ���
���� nn ���̶ȵ㣬���������������ʯ�Ӵ�����ߵ����ұ�
�ƶ���ÿ��һ�ζ��鿴���ڳ��ӷ�Χ���� mm ��ʯ�ӣ���ôҪ
ʹ�����������������Ҫ�ƶ� n-mn?m �Ρ�ֻҪ�ڳ����ⲿ��ʯ
�ӣ����в������������ڵġ���Щ��������С�ľ�Ϊ���ٴ�
����������һ��������1��2��3��4��7���� 1-4 ����õ����У�
���� 7 �����ƶ����˵㣬ֻ�� 1 ���ƶ��� 6��Ȼ�� 7 �ƶ��� 5 ��
�����������Ҫ�� 2 �������ǳ����ڵ�ʯ�Ӷ��������ģ���
��û�ն���ֻ�ڱ����пգ�Ҫ�� 2 �Ρ�
*/
int* numMovesStonesII(int* stones, int stonesSize, int* returnSize)
{
        qsort(stones, stonesSize, sizeof(stones[0]), cmp_int);

        int minMove=stonesSize;

        for(int i=0,j=0;j<stonesSize;++j)
        {
            //��ǰ���ڵĴ�С����n
            while(stones[j]-stones[i]+1>stonesSize)i++;

            //��ǰ���ڵ�ʯ�Ӹ���
            int already_stone=(j-i+1);

            //ǰn-1��ʯ�ӵ�˳�����������һ��ʯ�Ӳ���������Ҫ�ƶ�2����
            //����3 4 5 6 10�����ǲ���ֱ�ӽ�10��Ϊ2�����ǽ�3��Ϊ8��Ȼ��10��Ϊ7���ƶ�
            if (already_stone==stonesSize-1&&stones[j]-stones[i]+1==stonesSize-1)
                minMove=fmin(minMove,2);
            else
                minMove=fmin(minMove,stonesSize-already_stone);

        }

	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;
	res[0] = minMove;
	res[1] = fmax(stones[stonesSize-1]-stones[1]-stonesSize+2, stones[stonesSize-2]-stones[0]-stonesSize+2);

        return res;
}


/*
1100. ����Ϊ K �����ظ��ַ��Ӵ�
����һ���ַ��� S���ҳ����г���Ϊ K �Ҳ����ظ��ַ����Ӵ���
���㷵��ȫ������Ҫ����Ӵ��� ��Ŀ��
ʾ�� 1��
���룺S = "havefunonleetcode", K = 5
�����6
���ͣ�
������ 6 ������������Ӵ����ֱ��ǣ�
'havef','avefu','vefun','efuno','etcod','tcode'��
*/
// ����
int numKLenSubstrNoRepeats(char * S, int K){
    // �洢�ַ�����Ƶ��
    int fre[256] = {0};
    // ��������ָ��
    int l, r;
    l = r = 0;
    // S����
    int len = strlen(S);
    // �����ڲ�ͬ�ַ�����
    int count = 0;
    // ��ǰ���ڿ��
    int width = 0;
    // result
    int res = 0;
    while(r < len){
        // һ��ʼ����չ���ڵ����ΪK
        if(width < K){
            // Ƶ��Ϊ0��˵���봰�����µ��ַ���Ƶ�� + 1 �� ��ͬ�ַ����� + 1
            if(fre[S[r++]]++ == 0) count++;
            // ��� + 1
            width++;
        }else{ // ���ΪK��̶���Ȼ�������
            // �ַ����������޸��ַ��� ��ͬ�ַ����� - 1
            if(--fre[S[l++]] == 0) count--;
            if(fre[S[r++]]++ == 0) count++;
        }
        // ��ͬ�ַ����� == K�� ���������� res++
        if(count == K) res++;

    }
    return res;
}

/*
978. �����������
�� A �������� A[i], A[i+1], ..., A[j] ������������ʱ�����ǳ���Ϊ���������飺

�� i <= k < j���� k Ϊ����ʱ�� A[k] > A[k+1]���ҵ� k Ϊż��ʱ��A[k] < A[k+1]��
�� �� i <= k < j���� k Ϊż��ʱ��A[k] > A[k+1] ���ҵ� k Ϊ����ʱ�� A[k] < A[k+1]��
Ҳ����˵������ȽϷ������������е�ÿ������Ԫ�ض�֮�䷭ת����������������������顣

���� A ���������������ĳ��ȡ�



ʾ�� 1��

���룺[9,4,2,10,7,8,8,1,9]
�����5
���ͣ�(A[1] > A[2] < A[3] > A[4] < A[5])
*/
#define max(a,b) ((a) > (b) ? (a) : (b))
int cmp(int a,int b) {
    if(a > b) {
        return 1;
    } else if(a < b) {
        return -1;
    } else {
        return 0;
    }
}

int maxTurbulenceSize(int* A, int ASize){
    int ans = 1;
    int anchor = 0;

    for(int i = 1;i < ASize;i++) {
        int c = cmp(A[i-1],A[i]);
        if(i == ASize - 1 || c * cmp(A[i],A[i+1]) != -1) {
            if(c != 0) {
                ans = max(ans,i - anchor + 1);
            }
            anchor = i;
        }
    }
    return ans;
}

/*
239. �����������ֵ
����һ������ nums����һ����СΪ k �Ļ������ڴ������������ƶ�����������Ҳࡣ��ֻ���Կ����ڻ��������ڵ� k �����֡���������ÿ��ֻ�����ƶ�һλ��

���ػ��������е����ֵ��



���ף�

����������ʱ�临�Ӷ��ڽ��������



ʾ��:

����: nums = [1,3,-1,-3,5,3,6,7], �� k = 3
���: [3,3,5,5,6,7]
*/
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
    if (nums == NULL || returnSize == NULL) {
        return NULL;
    }
    int outLen = numsSize - k + 1;
    int *result = (int *)malloc(sizeof(int) * outLen);
    int *deque = (int *)malloc(sizeof(int) * numsSize);
    int start = 0;
    int end = 0;
    int i = 0, j = 0;
    while (i < numsSize) {
        //���ұ߳�Ա��ֵС�ڼ�����ӵ�ֵ���ʹ��ұ����γ���
        while (start != end && nums[i] > nums[deque[end - 1]]) {
            end--;
        }
        //���ұ����
        deque[end++] = i;
        //�������K�Σ���Ҫ��ʼ��¼��ǰ�������ֵ
        if (i >= k - 1) {
            result[i - k + 1] = nums[deque[start]];
            if (start != end && deque[start] <= i - k + 1) {
                //���ֵ�ѳ����ڣ���߳���
                start++;
            }
        }
        i++;
    }
    free(deque);
    *returnSize = outLen;
    return result;
}

/*
480. ����������λ��
��λ���������������м���Ǹ�����������еĴ�С��ż������û�����м��������ʱ��λ�������м����������ƽ������

���磺

[2,3,4]����λ���� 3
[2,3]����λ���� (2 + 3) / 2 = 2.5
����һ������ nums����һ����СΪ k �Ĵ��ڴ�����˻��������Ҷˡ��������� k ������ÿ�δ��������ƶ� 1 λ������������ҳ�ÿ�δ����ƶ���õ����´�����Ԫ�ص���λ�����������������ɵ����顣



ʾ����

���� nums = [1,3,-1,-3,5,3,6,7]���Լ� k = 3��
*/

#if 1
void dqueue_push(int *dqueue, int dqueueSize, int data)
{
    int i;
    for (i = 0; i < dqueueSize - 1; i++) {
        if (data > dqueue[i]) {
            break;
        }
    }

    for (int j = dqueueSize - 1; j > i; j--) {
        dqueue[j] = dqueue[j - 1];
    }

    dqueue[i] = data;
}

void dqueue_del(int *dqueue, int dqueueSize, int data)
{
    int i;
    for (i = 0; i < dqueueSize; i++) {
        if (data == dqueue[i]) {
            break;
        }
    }

    for (int j = i; j < dqueueSize - 1; j++) {
        dqueue[j] = dqueue[j + 1];
    }
}
#else

void dqueue_replace(int *dqueue, int dqueueSize, int oldData, int newData)
{
	for (int i = 0; i < dqueueSize; i++) {
		if (dqueue[i] == oldData) {
			dqueue[i] = newData;
			return;
		}
	}
}
#endif

double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
	*returnSize = 0;
    if (nums == NULL || numsSize <= 0) {
        return NULL;
    }

    double *res = (int *)calloc(numsSize, sizeof(double));
	int dqueue[k];
	memcpy(dqueue, nums, sizeof(int) * k);
	qsort(dqueue, k, sizeof(dqueue[0]), cmp_int);
	res[0] = k % 2 == 1 ? dqueue[k / 2] : (dqueue[k / 2] * 0.5 + dqueue[k / 2 - 1] * 0.5);
	(*returnSize) = 1;

	for (int i = 0; i < numsSize - k; i++) {
		dqueue_del(dqueue, k, nums[i]);
		dqueue_push(dqueue, k, nums[i + k]);
		res[*returnSize] = k % 2 ==1 ? dqueue[k / 2] : (dqueue[k / 2] * 0.5 + dqueue[k / 2 - 1] * 0.5);
		(*returnSize)++;
	}

	return res;
}

/*
727. ��С����������
�����ַ��� S and T���ҳ� S ����̵ģ��������Ӵ� W ��ʹ�� T �� W �� ������ ��

��� S ��û�д��ڿ��԰��� T �е������ַ������ؿ��ַ��� ""������в�ֹһ����̳��ȵĴ��ڣ����ؿ�ʼλ�������Ǹ���

ʾ�� 1��

���룺
S = "abcdebdde", T = "bde"
�����"bcde"
���ͣ�
"bcde" �Ǵ𰸣���Ϊ������ͬ���ȵ��ַ��� "bdde" ����֮ǰ��
"deb" ����һ
*/
char * minWindow(char * S, char * T)
{
    if(S == T) return S;
    int start = 0;
    int end = strlen(S) - 1;
    int s = 0,t = 0;
    while(s < strlen(S)){
        if(S[s] == T[t]){
            t++;
        }
        if(t == strlen(T)){
            int right = s;
            t--;
            while(t >= 0){
                if(S[s] == T[t]){
                    t--;
                }
                s--;
            }
            s++;
            if(right - s + 1 < end - start + 1){
                start = s;
                end = right;
            }
            t = 0;
        }
        s++;
    }

	if (end - start + 1 == strlen(S))
		return "";

	char *res = (char *)calloc(20000, sizeof(char));
	strncpy(res, S + start, end - start + 1);
	return res;
}

/*
992. K ����ͬ������������
����һ������������ A����� A ��ĳ���������в�ͬ�����ĸ���ǡ��Ϊ K����� A �������������һ��������������Ϊ�������顣

�����磬[1,2,3,1,2] ���� 3 ����ͬ��������1��2���Լ� 3����

���� A �к����������Ŀ��



ʾ�� 1��

���룺A = [1,2,1,2,3], K = 2
�����7
���ͣ�ǡ���� 2 ����ͬ������ɵ������飺[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
*/

/*
��һ���������ͬ��������<=K���������������������ͬ��������<=K - 1�����������������������
*/
	int subarraysLessThanKDistinct(int* A, int ASize, int K){  //��ͬ����С�ڵ���K������������
        int m[ASize + 1];
		memset(m, 0, sizeof(m));
        int start = 0;
        int end = 0;
        int res = 0;
        int count = 0; //��ͬ�����ĸ���
        while(end < ASize){
            m[A[end]]++;
            if(m[A[end]] == 1)  count++;
            while(count > K){
                m[A[start]]--;
                if(!m[A[start]])  count--;
                start++;
            }
            res += end - start + 1;//ÿ�䶯һ��end�����ӵ�����������Ϊend - start + 1��end������������
            end++;
        }
        return res;
    }

int subarraysWithKDistinct(int* A, int ASize, int K)
{
	return subarraysLessThanKDistinct(A, ASize, K) - subarraysLessThanKDistinct(A, ASize, K - 1);
}

