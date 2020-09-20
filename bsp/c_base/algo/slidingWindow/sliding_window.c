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
11. ʢ���ˮ������
���� n ���Ǹ����� a1��a2��...��an��ÿ��������������
��һ���� (i, ai) ���������ڻ� n ����ֱ�ߣ�
��ֱ�� i �������˵�ֱ�Ϊ (i, ai) �� (i, 0)���ҳ����е������ߣ�
ʹ�������� x �Ṳͬ���ɵ�����������������ˮ��

˵�����㲻����б�������� n ��ֵ����Ϊ 2��

*/
int maxArea(int* height, int heightSize)
{
	int left  = 0;
	int right = heightSize - 1;

	int max = 0;
	while (left < right) {
		int cur = (right - left) * (fmin(height[left], height[right]));
		max = fmax(max, cur);
		if (height[left] > height[right]) {
			right--;
		} else {
			left++;
		}
	}

	return max;
}

/*
647. �����Ӵ�
�Ѷ��е�374
����һ���ַ�������������Ǽ�������ַ������ж��ٸ���
���Ӵ���
���в�ͬ��ʼλ�û����λ�õ��Ӵ�����ʹ������ͬ���ַ�
��ɣ�Ҳ�ᱻ������ͬ���Ӵ���

ʾ�� 1��
���룺"abc"
�����3
���ͣ����������Ӵ�: "a", "b", "c"
*/

/*
���������������졾ͨ����
˼·
�ڳ���Ϊ N ���ַ����У����ܵĻ��Ĵ�����λ���� 2N-1 ����
��ĸ����������ĸ�м䡣
��ÿһ�����Ĵ����Ŀ�ʼͳ�ƻ��Ĵ�������
�������� [a, b] ��ʾ S[a], S[a+1], ..., S[b] �ǻ��Ĵ���
���ݻ��Ĵ������֪ [a+1, b-1] Ҳ�ǻ������䡣
�㷨
����ÿ�����ܵĻ��Ĵ�����λ�ã�
�������������Ļ������� [left, right]��
�� left >= 0 and right < N and S[left] == S[right] ʱ��
�������䡣��ʱ���������ʾ�Ļ��Ĵ�Ϊ S[left], S[left+1], ..., S[right]��

*/
int countSubstrings(char * s)
{
	int size = strlen(s);
	int ans = 0;
	for (int center = 0; center < 2 * size -1; center++) {
		int left = center / 2;
		int right = left + center % 2;
		while(left >= 0 && right < size && s[left] == s[right]) {
			ans++;
			left--;
			right++;
		}
	}

	return ans;
}

/*
5. ������Ӵ�
����һ���ַ��� s���ҵ� s ����Ļ����Ӵ���
����Լ��� s ����󳤶�Ϊ 1000��

ʾ�� 1��

����: "babad"
���: "bab"
ע��: "aba" Ҳ��һ����Ч�𰸡�
ʾ�� 2��

����: "cbbd"
���: "bb"
*/
char * longestPalindrome(char * s)
{
	int slen = strlen(s);
	if (s == NULL || slen <= 1) {
		return s;
	}

	int max = 1;
	int save[2] = {0};
	for (int centor = 0; centor < 2 * slen - 1; centor++) {
		int left = centor / 2;
		int right = left + centor % 2;

		while(left >= 0 && right < slen && s[left] == s[right]) {
			if (right - left + 1 > max) {
				save[0] = left;
				save[1] = right;
				max = right - left + 1 ;
			}

			left--;
			right++;
		}
	}

	s[save[1]  + 1] = '\0';
	return s + save[0];
}



/*
1456. �����Ӵ���Ԫ���������Ŀ
�����ַ��� s ������ k ��

�뷵���ַ��� s �г���Ϊ k �ĵ������ַ����п��ܰ��������Ԫ����ĸ����

Ӣ���е� Ԫ����ĸ Ϊ��a, e, i, o, u����



ʾ�� 1��

���룺s = "abciiidef", k = 3
�����3
���ͣ����ַ��� "iii" ���� 3 ��Ԫ����ĸ��
*/
int is_vowel(char c)
{
	const char vowel[] = {'a', 'e', 'i', 'o', 'u'};

	int i = 0;
	while(i < 5) {
		if (c == vowel[i]) {
			return 1;
		}

		i++;
	}

	return 0;
}

int maxVowels(char * s, int k)
{
	int cnt = 0;
	int res = 0;

	for (int right = 0; right < strlen(s); right++) {
		cnt += is_vowel(s[right]);

		if (right >= k) {
			cnt -= is_vowel(s[right - k]);
		}

		res = fmax(res, cnt);
	}

	return res;
}

//a, e, i, o, u
bool isYuan(char c)
{
	int d[] = {'a', 'e', 'i', 'o', 'u'};
	for (int i = 0; i < 5; i++) {
		if (c == d[i]) {
			return true;
		}
	}

	return false;
}

int maxVowels(char * s, int k)
{
	int left = 0;
	int right = 0;
	int slen = strlen(s);
	int winCnt = 0;
	int max = 0;

	while(right < slen) {
		if (isYuan(s[right])) {
			winCnt++;
		}

		if (right - left + 1 < k) {
			right++;
			continue;
		}

		max = fmax(max, winCnt);

		if (isYuan(s[left])) {
			winCnt--;
		}
		left++;
		right++;
	}

	return max;
}

/*
457. ��������ѭ��
����һ�������������͸������Ļ������� nums�� ���ĳ�������е��� k Ϊ����������ǰ�ƶ� k ���������෴������Ǹ��� (-k)��������ƶ� k ����������Ϊ�����ǻ��εģ����Կ��Լ������һ��Ԫ�ص���һ��Ԫ���ǵ�һ��Ԫ�أ�����һ��Ԫ�ص�ǰһ��Ԫ�������һ��Ԫ�ء�

ȷ�� nums ���Ƿ����ѭ���������ڣ���ѭ����������ͬ����������ʼ�ͽ�������ѭ������ > 1�����⣬һ��ѭ���е������˶�����������ͬһ������С����仰˵��һ��ѭ���в���ͬʱ������ǰ���˶��������˶���


ʾ�� 1��

���룺[2,-1,1,2,2]
�����true
���ͣ�����ѭ���������� 0 -> 2 -> 3 -> 0 ��ѭ������Ϊ 3
*/
/*
��������������Ҫһ�� visited ���飬����¼���ʹ�������Ȼ�����Ǳ���ԭ���飬�����ǰ�����Ѿ����ʹ��ˣ�ֱ��������������Ե�ǰλ������Ϊ��ʼ�㿪ʼ���ң����� while ѭ����������һ��λ�ã����㷽���ǵ�ǰλ��������϶�Ӧ�����֣�������ѭ�����飬���Խ�����ܻᳬ������ĳ��ȣ���������Ҫ�����鳤��ȡ�ࡣ��Ȼ���������Ҳ�����Ǹ����������Ժ����Ҳ�Ǹ�����������ȡ��֮ǰ�����ٲ���һ��n��ʹ���Ϊ���������� ���������Զ����n�Ļ���ȡ��֮ǰֻ����һ��n�������ǲ����ģ�������ȷ�ķ�����Ӧ���ȶ�nȡ�࣬�ټ���n��Ϊ��ͬʱ�����������Ҳ�����������������ǵĴ��������ȶ�nȡ�࣬�ټ���n���ٶ�nȡ�࣬���������������Ǹ�������С��Σ������Գɹ�����ת��Ծ�ˡ�����ʱ�����жϣ���� fast �� slow ��ȣ�˵����ʱ��һ�����ֵ�ѭ�������������⣬���о��Ǽ����ߵķ���������������ʾ forward�����Ǹ�����ʾ backward����һ�� loop �б���ͬ����ͬ��������ֻҪ�ö�����ˣ��������Ǹ����Ļ���˵������ͬ��ֱ�� break ������ʱ��� fast �Ѿ���ӳ���ˣ�˵�������ҵ��˺Ϸ��� loop������ true��������һ��������ӳ�䣬�� fast λ���� visited �����б�� true������ѭ����
*/
bool circularArrayLoop(int* nums, int numsSize)
{
	if (nums == NULL || numsSize <= 1)
		return false;

	bool visited[numsSize];
	memset(visited, 0, sizeof(visited));
	for(int slow = 0; slow < numsSize; slow++) {
		if(visited[slow])
			continue;

		visited[slow] = true;
		int map[5001];
		memset(map, 0, sizeof(map));
		while(true) {
			int fast = ((slow+nums[slow])%numsSize+numsSize)%numsSize;
			if(fast == slow||nums[fast]*nums[slow] < 0)
				break;
			if (map[fast] != 0)
				return true;
			map[slow] = 1;
			visited[fast] = true;
			slow = fast;
		}
	}

	return false;
}


/*
567. �ַ���������
�Ѷ��е�140
���������ַ��� s1 �� s2��дһ���������ж� s2 �Ƿ���� s1 �����С�
���仰˵����һ���ַ���������֮һ�ǵڶ����ַ������Ӵ���
ʾ��1:
����: s1 = "ab" s2 = "eidbaooo"
���: True
����: s2 ���� s1 ������֮һ ("ba").

ʾ��2:
����: s1= "ab" s2 = "eidboaoo"
���: False

*/
bool checkInclusion(char * s1, char * s2){
        int mp[26] = {0};
	for (int i = 0; i < strlen(s1); i++) {
		mp[s1[i] - 'a']++;
	}

        int l = 0, r = 0;
        while (r < strlen(s2)){
            char c = s2[r++];
            mp[c - 'a']--; // �봰
            while (l < r && mp[c - 'a'] < 0){ // ����
                mp[s2[l++] - 'a'] ++;
            }
            if (r - l == strlen(s1)) return true;
        }
        return false;
}

bool checkMap(int *map1, int *map2)
{
	for (int i = 0; i < 26; i++) {
		if (map1[i] != map2[i]) {
			return false;
		}
	}

	return true;
}

bool checkInclusion(char * s1, char * s2)
{
	int map[26] = {0};
	int i = 0;
	int s1len = strlen(s1);

	while(i < s1len) {
		map[s1[i++] - 'a']++;
	}

	int map2[26] = {0};
	int left = 0;
	int right = 0;
	int s2len = strlen(s2);

	while(right < s2len) {

        map2[s2[right] - 'a']++;

		if (right - left + 1 < s1len) {
			right++;
			continue;
		}

		bool check = checkMap(map, map2);
		if (check == true) {
			return true;
		}

		map2[s2[left] - 'a']--;
		left++;
		right++;
	}

	return false;
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
			// ��������
			// mapt[d] == 0 ��ʶleft��ָԪ�طǹؼ�
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
		return;
	}
}

int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize)
{
	int numall = 0;
	for (int i = 0; i < numsSize; i++) {
		numall += numsColSize[i];
	}

	Info allNum[numall];

	int allNumSize = 0;
	for (int i = 0; i < numsSize; i++) {
		for (int j = 0; j < numsColSize[i]; j++) {
			allNum[allNumSize].value = nums[i][j];
			allNum[allNumSize].group = i;
			allNumSize++;
		}
	}

	int kCount[MAX_NUM] = { 0 };
	qsort(allNum, numall, sizeof(Info), cmpFun);
	int left = 0;
	int right = 0;
	int resBegin = -1;
	int resEnd = -1;
	while (right < numall) {

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
    for(int i=1;i<numsSize;i++){
        if(nums[i] == nums[i-1])
			flag++; //����
        else
			flag = 0;  //��������0
        if(flag>=2)
			temp++;  //��λ�����1

        nums[i-temp] = nums[i]; //��λ
    }
    return numsSize - temp;
}


/*
1176. ����ƻ�����
��ĺ�����һλ�������ߡ�ǰ�����ӣ������Լ��ƶ���һ�ݽ���ƻ��������������������һ����ݼƻ��Ƿ����

������һ�ݼƻ����ĵĿ�·������� calories[i] �����������λ�����ڵ� i ����Ҫ���ĵĿ�·��������

Ϊ�˸��õ�������ݼƻ������ڿ�·����е�ÿһ�죬�㶼��Ҫ������ ����һ���Լ�֮����������졹 ���� k �죩�����ĵ��ܿ�·�� T��

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
int dietPlanPerformance(int* calories, int caloriesSize, int k, int lower, int upper){
    int index = 0;
    int score = 0;
    int sum = 0;
    for (index; index < k; index++) {
        sum += calories[index];
    }
    for (index; ; index++) {
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
��һ���������޵������ϣ��� i ��ʯ�ӵ�λ��Ϊ stones[i]�����һ��ʯ�ӵ�λ����С/�����ô��ʯ�ӱ������˵�ʯ�ӡ�

ÿ���غϣ�����Խ�һ�Ŷ˵�ʯ�������ƶ���һ��δռ�õ�λ�ã�ʹ�ø�ʯ�Ӳ�����һ�Ŷ˵�ʯ�ӡ�

ֵ��ע����ǣ����ʯ���� stones = [1,2,5] �������㽫�޷��ƶ�λ��λ�� 5 �Ķ˵�ʯ�ӣ���Ϊ���۽����ƶ����κ�λ�ã����� 0 �� 3������ʯ�Ӷ���Ȼ���Ƕ˵�ʯ�ӡ�

�����޷������κ��ƶ�ʱ��������Щʯ�ӵ�λ������ʱ����Ϸ������

Ҫʹ��Ϸ�����������ִ�е���С������ƶ������ֱ��Ƕ��٣� �Գ���Ϊ 2 ��������ʽ���ش𰸣�answer = [minimum_moves, maximum_moves] ��



ʾ�� 1��

���룺[7,4,9]
�����[1,2]
���ͣ�
���ǿ����ƶ�һ�Σ�4 -> 8����Ϸ������
���ߣ����ǿ����ƶ����� 9 -> 5��4 -> 6����Ϸ������
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
1438. ���Բ�������Ƶ������������
����һ���������� nums ����һ����ʾ���Ƶ����� limit�����㷵�������������ĳ��ȣ����������е���������Ԫ��֮��ľ��Բ����С�ڻ��ߵ��� limit ��

������������������������飬�򷵻� 0 ��



ʾ�� 1��

���룺nums = [8,2,4,7], limit = 4
�����2
���ͣ��������������£�
[8] �����Բ� |8-8| = 0 <= 4.
[8,2] �����Բ� |8-2| = 6 > 4.
[8,2,4] �����Բ� |8-2| = 6 > 4.
[8,2,4,7] �����Բ� |8-2| = 6 > 4.
[2] �����Բ� |2-2| = 0 <= 4.
[2,4] �����Բ� |2-4| = 2 <= 4.
[2,4,7] �����Բ� |2-7| = 5 > 4.
[4] �����Բ� |4-4| = 0 <= 4.
[4,7] �����Բ� |4-7| = 3 <= 4.
[7] �����Բ� |7-7| = 0 <= 4.
��ˣ�����������������ĳ���Ϊ 2 ��
*/

#include <stdlib.h>
#include <stdio.h>

//���㷨˼·������ + �������С�
// 1.���������ݼ�¼�������Сֵ���ж��Ƿ��ڷ�Χ��
// 2.���������У���¼���ֵλ��
// 3.���������У���¼��Сֵλ��
// 4.����������ݳ�����Χ������н���
// 5.j��������ƶ���߽磬ֱ����Χ����Ҫ��
int longestSubarray(int* nums, int numsSize, int limit){
    if(numsSize == 1) {
        return 1;
    }

    int *inc_que = (int *)calloc(numsSize, sizeof(int));
    int iq_r = 0;
    int iq_w = 0;
    int iq_size = 0;

    int *dec_que = (int *)calloc(numsSize, sizeof(int));
    int dq_r = 0;
    int dq_w = 0;
    int dq_size = 0;

    //����Ԫ������
    inc_que[iq_w++] = 0;
    iq_size++;

    //����Ԫ������
    dec_que[dq_w++] = 0;
    dq_size++;

    int max_len = 1;

    int ll = 0, rr = 1;
    while(rr < numsSize) {
        //��֦
        if(max_len >= numsSize - ll) {
            break;
        }

        int minid = inc_que[iq_r];
        int maxid = dec_que[dq_r];
        int cur = nums[rr];
        //printf("max = %d, min = %d\n", nums[maxid], nums[minid]);

        //�����������У���ǰ�������ڸ�ֵ������
        while(iq_size > 0) {
            if(nums[inc_que[iq_w - 1]] > cur) {
                iq_w--;
                iq_size--;
            } else {
                break;
            }
        }
        inc_que[iq_w++] = rr;
        iq_size++;

        //�����½�����,��ǰ����С�ڸ�ֵ������
        while(dq_size > 0) {
            if(nums[dec_que[dq_w - 1]] < cur) {
                dq_w--;
                dq_size--;
            } else {
                break;
            }
        }
        dec_que[dq_w++] = rr;
        dq_size++;

        //����ڷ�Χ֮��,���������
        if(abs(nums[rr] - nums[maxid]) <= limit && abs(nums[rr] - nums[minid]) <= limit ) {
            rr++;
            continue;
        }

        //���ֳ�����Χ�����,���н���[ll, rr)
        //printf("FIND: ll = %d, rr = %d\n", ll, rr);
        max_len = fmax(max_len, rr - ll);

        //������߽�
        while(ll < rr) {
            if(ll != inc_que[iq_r] && ll != dec_que[dq_r]) {
                ll++;
                continue;
            }

            if(iq_size > 0 && ll == inc_que[iq_r]) {
                iq_r++;
                iq_size--;
            } else if(dq_size > 0 && ll == dec_que[dq_r]) {
                dq_r++;
                dq_size--;
            }
            ll++;

            //�ж��Ƿ�����Ҫ��
            minid = inc_que[iq_r];
            maxid = dec_que[dq_r];
            if(abs(nums[rr] - nums[maxid]) <= limit && abs(nums[rr] - nums[minid]) <= limit ) {
                //����Ҫ�����˳�
                break;
            }

            continue;
        }

        //printf("ADJ: ll = %d, rr = %d\n", ll, rr);
        rr++;
    }

    //����β������
    //printf("FIND: ll = %d, rr = %d\n", ll, rr);
    max_len = fmax(max_len, rr - ll);

    return max_len;
}

/*
1498. ������������������Ŀ
����һ���������� nums ��һ������ target ��

����ͳ�Ʋ����� nums ������������СԪ�������Ԫ�ص� �� С�ڻ���� target �� �ǿ� �����е���Ŀ��

���ڴ𰸿��ܴܺ��뽫����� 10^9 + 7 ȡ��󷵻ء�



ʾ�� 1��

���룺nums = [3,5,6,7], target = 9
�����4
���ͣ��� 4 �������������������
[3] -> ��СԪ�� + ���Ԫ�� <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)
*/

int numSubseq(int* nums, int numsSize, int target)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);
	if (nums[0] * 2 > target) {
		return 0;
	}

//��������������˷��б�
	int spow[numsSize];
	spow[0] = 1;
	for (int i = 1; i < numsSize; i++) {
		spow[i] = (spow[i-1] * 2) % (1000000000 + 7);
	}


	int left = 0;
	int right = numsSize - 1;
	int res = 0;
	while(left <= right) {
		if (nums[left] + nums[right] <= target) {
			res += spow[right - left];
			res %= (1000000000 + 7);
			left++;
		} else {
			right--;
		}
	}

	return res % (1000000000 + 7);
}
