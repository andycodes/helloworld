/*
��������
һ����ָ��left��һ����ָ��right��
���ִ��ڻ�����ʽ��


�Ӵ�������������

right
sum += nums[right++];
right ָ��δ����ĵ�Ԫ
*/


/*
209. ������С��������
�Ѷ��е�261
����һ������ n ���������������һ�������� s ���ҳ�������
��������� �� s �ĳ�����С�����������飬�������䳤�ȡ�
��������ڷ������������������飬���� 0��
ʾ��:
����: s = 7, nums = [2,3,1,2,4,3]
���: 2
����: ������ [4,3] �Ǹ������µĳ�����С�����������顣
����:
*/
int minSubArrayLen(int s, int* nums, int numsSize)
{
	int left = 0;
	int right = 0;
	int sum = 0;
	int res = INT_MAX;

	for (int i = 0; i < numsSize; i++) {
		sum += nums[i];
	}

	if (sum < s) {
		return 0;
	}

	sum = 0;
	while(right < numsSize) {
		sum += nums[right++];
		if (sum < s) {
			continue;
		}

		while(sum - nums[left] >= s) {
			sum -= nums[left++];
		}

		res = fmin(res, right - left);
	}

	return res;
}


int minSubArrayLen(int s, int* nums, int numsSize)
{
	int leftidx = 0;
	int sum = 0;
	int minret = INT_MAX;

	for (int i = 0; i < numsSize; i++) {
		sum += nums[i];
		while(sum >= s) {
			minret = fmin(minret, i + 1 - leftidx);
			sum -= nums[leftidx++];
		}
	}

	return minret == INT_MAX ? 0 : minret;
}


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
Ȼ������ά��һ��window�����ϼ��㲻Ϊc���ַ��ĸ���counter��
���counter����n��˵��������ô�滻Ҳ�����ˣ����Ǿ�Ҫ��start
��ǰŲһ�񣬷���һֱŲend��
ÿ��Ų��end֮��Ҫ�ǵø�����һ�ֵ���󳤶�
ÿ���ַ�cѭ����Ҫ��������res��
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
		maxCnt = fmax(maxCnt, map[s[right] - 'A']);//��ǰ�����ڵ�����ַ��ĸ���
/*
��Ҫ�滻���ַ��������ǵ�ǰ���ڵĴ�С��ȥ������������
����ַ�������
*/
		if (right - left + 1 -maxCnt > k) {
			map[s[left] - 'A']--;//��С����
			left++;
		}
/*
�������ڿ��滻���ַ���С�ڵ���kʱ��������Ҫ���ݸô���
������ȷ���Ƿ����result
*/
		ans = fmax(ans, right-left+1);
		right++;
	}

	return ans;
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
	int sSize = strlen(s);
	if (sSize <= 2)
		return sSize;

	int left = 0;
	int max = 0;

	while( left + max < sSize) {
		int tempLeft = left;

		while(left < sSize && s[left] == s[tempLeft]) {
			left++;
		}

		int right = left;
		int tempRight = right;

		while(right < sSize && (s[right] == s[tempRight] || s[right] == s[tempLeft] )) {
			right++;
		}

		max = max > (right - tempLeft) ? max :(right - tempLeft);
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

int cmp_int(const void *a, const void *b)
{
	return *((int *)a) - *((int *)b);
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
�и��ں����ʵĳ����ı��ļ������������������ʣ��ҳ�������ļ������������ʵ���̾���(���������)�����Ѱ�ҹ���������ļ��л��ظ���Σ���ÿ��Ѱ�ҵĵ��ʲ�ͬ�����ܶԴ��Ż���?
ʾ����
���룺words = ["I","am","a","student","from","a","university","in","a","city"], word1 = "a", word2 = "student"
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
see hashmap
*/
struct it{
	int num;
	int idx;
};

int cmp_struct(const int *a, const int *b)
{
	struct it * c = (struct it *)a;
	struct it * d = (struct it *)b;
	return c->num - d->num;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	int* res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	struct it obj[numsSize];
	for (int i = 0; i < numsSize; i++) {
		obj[i].num = nums[i];
		obj[i].idx = i;
	}

	qsort(obj, numsSize, sizeof(obj[0]), cmp_struct);
	int left = 0;
	int right = numsSize -1;
	int sum;
	while(1) {
		sum = obj[left].num + obj[right].num;
		if (sum > target) {
			right--;
		}else if(sum < target) {
			left++;
		}else {
			break;
		}
	}

	res[0] = obj[left].idx;
	res[1] = obj[right].idx;
	return res;
}

/*
18. ����֮��
����һ������ n ������������ nums ��һ��Ŀ��ֵ target���ж� nums ���Ƿ�����ĸ�Ԫ�� a��b��c �� d ��ʹ�� a + b + c + d ��ֵ�� target ��ȣ��ҳ��������������Ҳ��ظ�����Ԫ�顣

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
/*������ɢ����*/
char * longestPalindrome(char * s)
{
	if(strlen(s)==0||strlen(s)==1)
		return s;

	int i,start,left,right,count,len;
	start = len =0;

	for(i = 0; s[i] != '\0'; i += count) {
		count = 1;
		left= i - 1;
		right = i + 1;
		while(s[right] != '\0' && s[i] == s[right]) { //�����ظ��ַ���
			right++;
			count++;
		}

		while(left >= 0 && s[right] != '\0' && s[left] == s[right]) {
			left--;
			right++;
		}

		if(right-left-1>len) {
			start = left+1;
			len = right-left-1;
		}
	}

	s[start + len] = '\0';      // ԭ���޸ķ���
	return s + start;
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

    bool circularArrayLoop(int* nums, int numsSize) {
	if (nums == NULL || numsSize <= 1)
		return false;

	int n=numsSize;
        bool visited[n];
	memset(visited, 0, sizeof(visited));
        for(int slow=0;slow<n;slow++)
        {
            if(visited[slow])
				continue;

            visited[slow]=true;
			int map[5000 *2];
			memset(map, 0, sizeof(map));
            while(true)
            {
                int fast=((slow+nums[slow])%n+n)%n;
                if(fast==slow||nums[fast]*nums[slow]<0)
                	break;
		   if (map[fast] != 0)
					return true;
		map[slow] = 1;
		visited[fast]=true;

		slow=fast;
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

/*
713. �˻�С��K��������
�Ѷ��е�135
����һ������������ nums��
�ҳ��������ڳ˻�С�� k ��������������ĸ�����
ʾ�� 1:
����: nums = [10,5,2,6], k = 100
���: 8
����: 8���˻�С��100��������ֱ�Ϊ: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]��
��Ҫע����� [10,5,2] �����ǳ˻�С��100�������顣
˵��:
"	0 < nums.length <= 50000
"	0 < nums[i] < 1000
"	0 <= k < 10^6

*/
int numSubarrayProductLessThanK(int* nums, int numsSize, int k)
{
        if (k <= 1) return 0;
        int prod = 1, ans = 0, left = 0;
        for (int right = 0; right < numsSize; right++) {
            prod *= nums[right];
            while (prod >= k) prod /= nums[left++];
            ans += right - left + 1;
        }
        return ans;
}

/*
76. ��С�����Ӵ�
�Ѷ�����695
����һ���ַ��� S��һ���ַ��� T ���������һ���㷨�������� O(n) ��ʱ�临�Ӷ��ڣ����ַ��� S �����ҳ������� T �����ַ�����С�Ӵ���

ʾ����
���룺S = "ADOBECODEBANC", T = "ABC"
�����"BANC"

*/
char * minWindow(char * s, char * t){
    if (s == NULL || t == NULL) {
        return NULL;
    }

    int len = (int)strlen(s);
    int lent = (int)strlen(t);

    char *out = (char *)malloc(len + 1);
    if (out == NULL) {
        return NULL;
    }

    int outLen = 0;
    memset(out, 0, len + 1);
    if (len < lent || lent == 0) {
        return out;
    }

    int map[128] = {0};
    int mapt[128] = {0};
    int cnt = 0;
    /* 1. ��ʼ�����Ƕ̴����ȣ� �ȱ���һ�� �õ���������ƥ�䵽�̴����ַ����� */
    for (int i = 0; i < lent; i++) {
        mapt[t[i]]++;
        map[s[i]]++;
    }
    for (int i = 0; i < 128; i++) {
        if (mapt[i] > 0) {
            /* �ٽ�㣬ֻҪ <= �̴� ������Ч����, �ٴ���Ƕ������ */
            cnt += (map[i] >= mapt[i]? mapt[i] : map[i]);
        }
    }

    /* 2. ���������ڶ̴����Ⱦ������������� */
    if (cnt == lent) {
        outLen = lent;
        memcpy(out, s, outLen);
        return out;
    }

    /* 3. �������� */
    int l = 0;
    int r = lent;
    for (; r < len; r++) {
        if (mapt[s[r]] == 0) {
            continue;
        }

        map[s[r]]++;
        if (map[s[r]] <= mapt[s[r]]) {
            /* �ٽ�㣬ֻҪ <= �̴� ������Ч����, �ٴ���Ƕ������ */
            cnt++;
        }

        if (cnt == lent) {
            /* ����࿪ʼУ�� �ҵ��ٽ�㣨map[s[l]] == mapt[s[l]]��ɾ���������� */
            while (mapt[s[l]] == 0 || map[s[l]] > mapt[s[l]]) {
                map[s[l++]]--;
            }

            int cpLen = r - l + 1;
            if (outLen == 0 ||  cpLen < outLen) {
                memset(out, 0, len + 1);
                memcpy(out, s + l, cpLen);
                outLen = cpLen;
            }

            /* �ٽ�� */
            cnt--;
            map[s[l++]]--;
        }
    }

    return out;
}

#define MAX_HASH_LEN 128
char * minWindow(char * s, char * t){
    int slen = strlen(s);
    int tlen = strlen(t);
    if (slen == 0 || tlen == 0 || slen < tlen) {
        return "";
    }
    int shash[MAX_HASH_LEN] = {0};
    int thash[MAX_HASH_LEN] = {0};
    int i;
    int left = 0, right = 0;
    int matchCnt = 0;
    int minLen = slen + 1; // Сϸ�� ��֤s��t��һ���ַ�Ҳ�ܴ���
    int minLeft = 0;
    int minRight = 0;
    int index = 0;
    char *res = (char*)malloc(sizeof(char) * (slen + 1));
    memset(res, 0, (slen + 1));

    for (i = 0; i < tlen; i++) {
        thash[t[i]]++;
    }

    while (right < slen) {
        char c = s[right];
        right++;
        // �������� tƥ�䲻����right����+1
        if (thash[c] == 0) {
            continue;
        }

        // ƥ�䵽�ˣ�sƥ�����tС matchCnt++
        // sƥ�����t��˵����item�ظ�������Ҫ�������
        // �����1
        if (shash[c] < thash[c]) {
            matchCnt++;
        }
        shash[c]++;

        while (matchCnt == tlen) {
            if (right - left < minLen) {
                // ���¼�¼
                minLeft = left;
                minRight = right;
                minLen = right - left;
            }

            char d = s[left];
            left++;
            // ��������
            // thash[d] == 0 ��ʶleft��ָԪ�طǹؼ�
            if (thash[d] == 0) {
                continue;
            }

            // shash�϶�����ֵ�ģ���Ҫ��1
            shash[d]--;
            // ������1 �Գ���д����
            // �����ԭ�����s��t��ƥ��ģ�sƥ�������t����ô����left�����ң�matchCnt��Ҫ��1
            if (shash[d] < thash[d]) {
                matchCnt--;
            }

        }
    }

    s[minRight] = '\0';
    return &s[minLeft];
}

/*
632. ��С����
�Ѷ�����230
���� k ���������е������б��ҵ�һ����С���䣬ʹ�� k ���б��е�ÿ���б�������һ�������������С�
���Ƕ������ b-a < d-c ������ b-a == d-c ʱ a < c�������� [a,b] �� [c,d] С��

ʾ����
���룺[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
�����[20,24]
���ͣ�
�б� 1��[4, 10, 15, 24, 26]��24 ������ [20,24] �С�
�б� 2��[0, 9, 12, 20]��20 ������ [20,24] �С�
�б� 3��[5, 18, 22, 30]��22 ������ [20,24] �С�
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define RETURN_SIZE 2
 #define MAX_NUM 3500
typedef struct tagInfo {
    int value;
    int index;
} Info;
int cmpFun(const void *a, const void *b)
{
    Info *temp1 = (Info *)a;
    Info *temp2 = (Info *)b;
    if (temp1->value > temp2->value) {
        return 1;
    } else if (temp1->value < temp2->value) {
        return -1;
    } else {
        return 0;
    }
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
void updateIndex(int begin, int end, int *resBegin, int *resEnd, Info *allNum)
{
    if ((*resBegin == -1) ||
        (allNum[end].value - allNum[begin].value < allNum[*resEnd].value - allNum[*resBegin].value) ||
        (allNum[end].value - allNum[begin].value == allNum[*resEnd].value - allNum[*resBegin].value &&
         begin < *resBegin)) {
        *resBegin = begin;
        *resEnd = end;
        return;
    }
}
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize){
    int numall = 0;
    for (int i = 0; i < numsSize; i++) {
        numall += numsColSize[i];
    }
    Info *allNum = NULL;
    allNum = (Info *) malloc(sizeof(Info) * numall);
    if (allNum == NULL) {
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsColSize[i]; j++) {
            allNum[index].value = nums[i][j];
            allNum[index].index = i;
            index++;
        }
    }
    int kCount[MAX_NUM] = { 0 };
    qsort(allNum, numall, sizeof(Info), cmpFun);
    int begin = 0;
    int end = 0;
    int resBegin = -1;
    int resEnd = -1;
    while (end < numall) {
        kCount[allNum[end++].index]++;
        while (isCover(kCount, numsSize)) {
            updateIndex(begin, (end - 1), &resBegin, &resEnd, allNum);
            kCount[allNum[begin++].index]--;
        }
    }
    int *res = (int *)malloc(sizeof(int) * RETURN_SIZE);
    res[0] = allNum[resBegin].value;
    res[1] = allNum[resEnd].value;
    free(allNum);
    *returnSize = RETURN_SIZE;
    return res;
}

/*
80. ɾ�����������е��ظ��� II
�Ѷ��е�271�ղط����л�ΪӢ�Ĺ�ע����
����һ���������飬����Ҫ��ԭ��ɾ���ظ����ֵ�Ԫ�أ�ʹ��ÿ��Ԫ�����������Σ������Ƴ���������³��ȡ�
��Ҫʹ�ö��������ռ䣬�������ԭ���޸��������鲢��ʹ�� O(1) ����ռ����������ɡ�
ʾ�� 1:
���� nums = [1,1,1,2,2,3],

����Ӧ�����³��� length = 5, ����ԭ�����ǰ���Ԫ�ر��޸�Ϊ 1, 1, 2, 2, 3 ��

�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�


*/

int removeDuplicates(int* nums, int numsSize){
    int flag = 0, temp = 0;
    for(int i=1;i<numsSize;i++){
        if(nums[i] == nums[i-1])flag++; //����
        else flag = 0;  //��������0
        if(flag>=2)temp++;  //��λ�����1
        nums[i-temp] = nums[i]; //��λ
    }
    return numsSize - temp;
}
