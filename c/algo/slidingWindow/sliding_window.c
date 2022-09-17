/*
��������⼸��˼·���ο���
1���������ڣ�˫ָ�룩
2��ǰ׺�͵Ĳ�
*/

/*
�Ӵ�������������

1) ����
	right
	sum += nums[right++];
2)right++
	ָ��δ�����ĵ�Ԫ


��������һ����ָ��left��һ����ָ��right��
���ִ��ڻ�����ʽ��
while(right < slen) {
	do {
		what
	}

	right++ or continue;

	����������ѡ����
	left++;
}


for (int right = 0; right < slen; right++) {
		do {
			what
		}
		��������ѡ����
		left++;
}
*/


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
��ָ�뿪ʼ���ƣ����󴰿ڣ�ֱ�������ڳ��˳��ִ������
���ַ�����������ַ������ﵽk
��ָ�����ƶ��ᳬ��kʱ����ָ�뿪ʼͬʱ�ƶ�����ʱ����
����֮ǰ�Ĵ�С��ʼ������Ȼ����ָ������ƶ�ֱ������
�ַ��������ٴγ���k�����ƣ���ָ���ֿ�ʼͬʱ�ƶ������
ѭ����ȥֱ����ָ���ƶ����ַ����յ㡣
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
1176. �����ƻ�����
��ĺ�����һλ���������ߡ�ǰ�����ӣ������Լ��ƶ���һ
�ݽ����ƻ��������������������һ����ݼƻ��Ƿ������
������һ�ݼƻ����ĵĿ�·��������� calories[i] �����������
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
978. �����������
�� A �������� A[i], A[i+1], ..., A[j] ������������ʱ��
���ǳ���Ϊ���������飺
�� i <= k < j���� k Ϊ����ʱ�� A[k] > A[k+1]���ҵ� k Ϊż��ʱ��
A[k] < A[k+1]��
�� �� i <= k < j���� k Ϊż��ʱ��A[k] > A[k+1] ���ҵ� k Ϊ����ʱ��
A[k] < A[k+1]��
Ҳ����˵������ȽϷ������������е�ÿ������Ԫ�ض�֮��
��ת����������������������顣
���� A ���������������ĳ��ȡ�
ʾ�� 1��
���룺[9,4,2,10,7,8,8,1,9]
�����5
���ͣ�(A[1] > A[2] < A[3] > A[4] < A[5])
*/
int cmp(int a,int b)
{
	if(a > b) {
		return 1;
	} else if(a < b) {
		return -1;
	} else {
		return 0;
	}
}

int maxTurbulenceSize(int* A, int ASize)
{
	int ans = 1;
	int left = 0;

	for(int right = 1; right < ASize; right++) {
		int c = cmp(A[right-1], A[right]);

		if(right == ASize - 1 || c * cmp(A[right], A[right+1]) != -1) {
			if(c != 0) {
				ans = fmax(ans, right - left + 1);
			}
			left = right;
		}
	}
	return ans;
}

/*
480. ����������λ��
��λ���������������м���Ǹ�����������еĴ�С��ż����
��û�����м��������ʱ��λ�������м����������ƽ������
���磺
[2,3,4]����λ���� 3
[2,3]����λ���� (2 + 3) / 2 = 2.5
����һ������ nums����һ����СΪ k �Ĵ��ڴ�����˻�������
�Ҷˡ��������� k ������ÿ�δ��������ƶ� 1 λ�����������
�ҳ�ÿ�δ����ƶ���õ����´�����Ԫ�ص���λ���������
��������ɵ����顣
ʾ����
���� nums = [1,3,-1,-3,5,3,6,7]���Լ� k = 3��
*/
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
�����ַ��� S and T���ҳ� S ����̵ģ��������Ӵ� W ��ʹ�� T ��
W �� ������ ��
��� S ��û�д��ڿ��԰��� T �е������ַ������ؿ��ַ��� ""��
����в�ֹһ����̳��ȵĴ��ڣ����ؿ�ʼλ�������Ǹ���
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
	if(S == T)
		return S;
	int start = 0;
	int end = strlen(S) - 1;
	int s = 0,t = 0;
	while(s < strlen(S)){
		if(S[s] == T[t]) {
			t++;
		}

		if(t == strlen(T)) {
			int right = s;
			t--;
			while(t >= 0) {
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
��һ���������ͬ��������<=K���������������������ͬ��
������<=K - 1�����������������������
*/
int subarraysLessThanKDistinct(int* A, int ASize, int K)
{
	int m[ASize + 1];
	memset(m, 0, sizeof(m));
	int left = 0;
	int right = 0;
	int res = 0;
	int count = 0; //��ͬ�����ĸ���
	while(right < ASize) {
		m[A[right]]++;
		if(m[A[right]] == 1)
			count++;

		while(count > K){
			m[A[left]]--;
			if(!m[A[left]])  count--;
				left++;
		}
/*
ÿ�䶯һ��right�����ӵ�����������Ϊright - left + 1��right������
������
*/		res += right - left + 1;
		right++;
	}
	return res;
}

int subarraysWithKDistinct(int* A, int ASize, int K)
{
	return subarraysLessThanKDistinct(A, ASize, K) - subarraysLessThanKDistinct(A, ASize, K - 1);
}

/*
1156. ���ַ��ظ��Ӵ�����󳤶�
�Ѷ��е�34
����ַ����е������ַ�����ͬ����ô����ַ����ǵ��ַ�
�ظ����ַ�����
����һ���ַ��� text����ֻ�ܽ������������ַ�һ�λ���ʲô
��������Ȼ��õ�һЩ���ַ��ظ����Ӵ��������������
�Ӵ��ĳ��ȡ�

ʾ�� 1��
���룺text = "ababa"
�����3
ʾ�� 2��
���룺text = "aaabaaa"
�����6
*/

int maxRepOpt1(char * text)
{
	int len = strlen(text);
	int cnt[26] = {0};//��¼�����ַ���text�г��ֵĴ���

	for(int i = 0; i < len; i++)
		cnt[text[i]-'a']++;

	char cur_c = text[0];//��ǰ���ַ�
	int curSize = 1;//��ǰ���ַ�������
	int right = 1;//��ǰ���������ַ�����
	int ans = 0;

	while(right < len) {
		while(right < len && text[right] == cur_c){
			right++;
			curSize++;
		}
/*
���԰�ĳ��λ�õ�cur_c������rightλ�ã�ʹ���ַ��������ӳ�
*/
		if(curSize < cnt[cur_c-'a']) {
			curSize++;
			int tmp = right + 1;//��������ӳ����ַ���
			while(tmp < len && text[tmp] == cur_c){
				curSize++;
				tmp++;
			}
		}
/*
��aaaba�������ʱ��ǰ"����"��a���ڼ����ӳ�ʱ�ٴμ�����
����Ҫȡmin���ﵽȥ�ص�����
*/		curSize = fmin(curSize, cnt[cur_c-'a']);
		ans = fmax(ans, curSize);
		if(right < len) {//������¼��һ�ε��ַ���
			cur_c = text[right];
			curSize = 1;
			right++;
		}
	}
	return ans;
}
