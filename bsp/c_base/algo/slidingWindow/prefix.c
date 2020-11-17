/*
prefix
�������
ǰ���prefixSum  (�����Ӻ�)
������������;�����ʹ��ǰ׺�����Ż�
������A(i,j]�ĺ�Ϊsum[j] - sum[i]
��i��Ԫ�ص�ǰ׺�� = ǰi-1��Ԫ��֮�͡�
��Ԫ��û��ǰ׺���涨Ϊ0

int prefix[arrSize + 1];
prefix[0] = 0;
for (int i = 1; i <= arrSize; i++) {
	prefix[i] = prefix[i - 1] + arr[i - 1];
}

*/
/*
560. ��ΪK��������
����һ�����������һ������ k������Ҫ�ҵ��������к�Ϊ
k ��������������ĸ�����

ʾ�� 1 :

����:nums = [1,1,1], k = 2
���: 2 , [1,1] �� [1,1] Ϊ���ֲ�ͬ�������
˵�� :

����ĳ���Ϊ [1, 20,000]��
������Ԫ�صķ�Χ�� [-1000, 1000] �������� k �ķ�Χ�� [-1e7, 1e7]��
ͨ������25,598�ύ����57,201
*/
int subarraySum(int* nums, int numsSize, int k)
{
	int cnt = 0;
	int prefixSum[numsSize + 1];
	prefixSum[0] = 0;
	for (int i = 1; i <= numsSize; i++) {
		prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
	}

	for (int start = 0; start < numsSize; start++) {
		for (int end = start + 1; end <= numsSize; end++) {
			if (prefixSum[end] - prefixSum[start] == k)
				cnt++;
		}
	}

	return cnt;
}

/*
�м��� i��j ����ϣ����� prefixSum[j] - prefixSum[i - 1]==k��
ά��һ��ǰ׺��hash��ֻ�����һ�����顣ǰ׺�����飺�����i��Ԫ�ص�ǰ׺�;���a[0]+a[1]+......+a[i]����prefixSum[i]���������ŵ����������̵õ���������i��j, a[i]+.......a[j] = prefixSum[j] - prefixSum[i-1];��a[i]+.......a[j] = k; ��prefixSum[j] - prefixSum[i-1] = k;�������Ԫ��Xʱ�������prefixSum[x], ֻ��Ҫ���prefixSum[x]-k��ֵ�ڹ�ϣ�����м���ֵ��������xΪ���һ��Ԫ�ص�������ĸ������Ӷ��ڱ����������ۼӵõ������ʵ�ֹ��̰��������֣���дhash��ǰ׺�͵ļ��㡣���ߣ�dong-bei-zhang-da-shuai���ӣ�https://leetcode-cn.com/problems/subarray-sum-equals-k/solution/cyu-yan-shou-si-hashqian-zhui-he-tao-lu-si-lu-xian/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
struct hashNode {
    int key;
    int val;
    UT_hash_handle hh;
};
struct hashNode *g_users = NULL;
struct hashNode *findUser(int key) {
    struct hashNode *s;
    HASH_FIND_INT(g_users, &key, s);
    return s;
}
int getUserVal(int key) {
    struct hashNode *s;
    HASH_FIND_INT(g_users, &key, s);
    return s->val;
}
void addUser(int key) {
    struct hashNode *s;
    HASH_FIND_INT(g_users, &key, s);
    if (s == NULL) {
        struct hashNode *s = (struct hashNode *)malloc(sizeof(struct hashNode));
        s->key = key;
        s->val = 1;
        HASH_ADD_INT(g_users, key, s);
    } else {
        s->val++;
    }
}
int subarraySum(int* nums, int numsSize, int k){
    int sum = 0, cnt = 0;
    g_users = NULL;
    addUser(0);
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (findUser(sum - k)) {
            cnt += getUserVal(sum-k);
        }
        addUser(sum);
    }
    return cnt;
}


/*
974. �Ϳɱ� K ������������
�Ѷ��е�170
����һ���������� A����������Ԫ��֮�Ϳɱ� K �����ģ��������ǿգ����������Ŀ��

ʾ����
���룺A = [4,5,0,-2,-3,1], K = 5
�����7
���ͣ�
�� 7 ��������������Ԫ��֮�Ϳɱ� K = 5 ������
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

*/

/*
������ʱ
����:
(prefix[j] - prefix[i]) % K == 0
�ȼ�
prefix[j] %k == prefix[i] % k
 map[i] * (map[i] - 1) / 2;
*/

int subarraysDivByK(int* A, int ASize, int K)
{
	int prefix[ASize + 1];
	prefix[0] = 0;
	for (int i = 1; i <= ASize; i++) {
		prefix[i] = prefix[i - 1] + A[i - 1];
	}

	int cnt = 0;
	for (int i = 0; i < ASize; i++) {
		for (int j = i + 1; j <= ASize; j++) {
			if ((prefix[j] - prefix[i]) % K == 0) {
				cnt++;
			}
		}
	}

	return cnt;
}

int subarraysDivByK(int* A, int ASize, int K)
{
	if (K == 0 || ASize == 0) {
		return 0;
	}

	int prefix[ASize+1];
	prefix[0]=0;
	for(int i = 1; i <= ASize; i++) {
		prefix[i] = prefix[i - 1]+A[i - 1];
	}

	int map[K];
	memset(map,0,K*sizeof(int));
	for(int i = 0;i<ASize+1;i++){
		map[(prefix[i]%K +K)%K]++;
	}

	int count=0;
	for(int i=0;i<K;i++){
		count+=(map[i]*(map[i]-1))/2;
	}
	return count;
}


/*
42. ����ˮ
�Ѷ�����1499
���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴
�����е����ӣ�����֮���ܽӶ�����ˮ��

������������ [0,1,0,2,1,0,1,3,2,1,2,1] ��ʾ�ĸ߶�ͼ������������£�
���Խ� 6 ����λ����ˮ����ɫ���ֱ�ʾ��ˮ����
��л Marcos ���״�ͼ��
ʾ��:
����: [0,1,0,2,1,0,1,3,2,1,2,1]
���: 6
*/

int trap(int* height, int heightSize)
{
	int ans = 0;
	for (int i = 1; i < heightSize - 1; i++) {
		int max_left = 0, max_right = 0;
		for (int j = i; j >= 0; j--) { //Search the left part for max bar heightSize
			max_left = fmax(max_left, height[j]);
		}
		for (int j = i; j < heightSize; j++) { //Search the right part for max bar heightSize
			max_right = fmax(max_right, height[j]);
		}
		ans += fmin(max_left, max_right) - height[i];
	}
	return ans;
}

int trap(int* height, int heightSize)
{
	if(height == NULL || heightSize <= 0)
		return 0;
	int ans = 0;
	int left_max[heightSize];
	int right_max[heightSize];

	left_max[0] = height[0];
	for (int i = 1; i < heightSize; i++) {
		left_max[i] = fmax(height[i], left_max[i - 1]);
	}

	right_max[heightSize - 1] = height[heightSize - 1];
	for (int i = heightSize - 2; i >= 0; i--) {
		right_max[i] = fmax(height[i], right_max[i + 1]);
	}

	for (int i = 1; i < heightSize - 1; i++) {
		ans += fmin(left_max[i], right_max[i]) - height[i];
	}
	return ans;
}

int trap(int* height, int heightSize)
{
	int left = 0, right = heightSize - 1;
	int ans = 0;
	int left_max = 0, right_max = 0;

	while (left < right) {
		if (height[left] < height[right]) {
			if (height[left] >= left_max)
				left_max = height[left];
			else
				ans += (left_max - height[left]);

			++left;
		} else {
			if (height[right] >= right_max) {
				right_max = height[right];
			} else
				ans += (right_max - height[right]);

			--right;
		}
	}

	return ans;
}

/*
1423. �ɻ�õ�������
���ſ��� �ų�һ�У�ÿ�ſ��ƶ���һ����Ӧ�ĵ�����
�������������� cardPoints ������
ÿ���ж�������Դ��еĿ�ͷ����ĩβ��һ�ſ��ƣ�
��������������� k �ſ��ơ�
��ĵ����������õ����е����п��Ƶĵ���֮�͡�
����һ���������� cardPoints ������ k�����㷵�ؿ��Ի�õ�
��������
ʾ�� 1��

���룺cardPoints = [1,2,3,4,5,6,1], k = 3
�����12
���ͣ���һ���ж��������������ƣ���ĵ������� 1 ��
���ǣ��������ұߵĿ��ƽ��������Ŀɻ�õ�����
���Ų��������ұߵ������ƣ����յ���Ϊ 1 + 6 + 5 = 12 ��
ʾ�� 2��

���룺cardPoints = [2,2,2], k = 2
�����4
���ͣ����������������ſ��ƣ��ɻ�õĵ������� 4 ��
ʾ�� 3��

���룺cardPoints = [9,7,7,9,7,7,9], k = 7
�����55
���ͣ�������������п��ƣ����Ի�õĵ���Ϊ���п��Ƶĵ���֮�͡�
ʾ�� 4��

���룺cardPoints = [1,1000,1], k = 1
�����1
���ͣ����޷��õ��м����ſ��ƣ����Կ��Ի�õ�������
Ϊ 1 ��
ʾ�� 5��

���룺cardPoints = [1,79,80,1,1,1,200,1], k = 3
�����202
*/
int maxScore(int* cardPoints, int cardPointsSize, int k)
{
	int prefixSum[cardPointsSize + 1];
	prefixSum[0] = 0;
	for (int i = 1; i < cardPointsSize + 1; i++) {
		prefixSum[i] = prefixSum[i - 1] + cardPoints[i - 1];
	}

	int ans = INT_MAX;
	int t = cardPointsSize - k;
	for (int j = t;  j <= cardPointsSize; j++) {
		ans = fmin(ans, prefixSum[j] - prefixSum[j - t]);
	}

	return prefixSum[cardPointsSize] - ans;
}

/*
525. ��������
����һ������������, �ҵ�������ͬ������ 0 �� 1 ������������飨�ĳ��ȣ���



ʾ�� 1:

����: [0,1]
���: 2
˵��: [0, 1] �Ǿ�����ͬ����0��1������������顣
ʾ�� 2:

����: [0,1,0]
���: 2
˵��: [0, 1] (�� [1, 0]) �Ǿ�����ͬ����0��1������������顣
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MMAX(a, b)        ((a) > (b)? (a) : (b))
#define MMIN(a, b)        ((a) < (b)? (a) : (b))

typedef struct _hash_st {
    int key;
    int sid;
    int eid;
    UT_hash_handle hh;
}hash_st;

//���㷨˼·������+hash�������01���⣬��0ת��Ϊ-1��
// ����ת��Ϊ������к�Ϊ0,ʹ��hash�����
int findMaxLength(int* nums, int numsSize){
    if(numsSize <= 1) {
        return 0;
    }

    hash_st *head = NULL;
    int max = 0;

    //0 -> -1 && ���� && ����hash
    int sum = 0;
    for(int i = 0; i < numsSize; i++) {
        //0ת-1������
        sum += nums[i] == 0? -1 : 1;

        if(sum == 0) {
            //��sumΪ0��ֱ��Ϊ���
            max = MMAX(max, i + 1);
        } else {
            int key = sum;

            hash_st *tmph;
            HASH_FIND(hh, head, &key, sizeof(key), tmph);
            if(tmph == NULL) {
                tmph = (hash_st *)calloc(1, sizeof(hash_st));
                tmph->key = key;
                tmph->sid = i;

                HASH_ADD_KEYPTR(hh, head, &tmph->key, sizeof(tmph->key), tmph);
            }

            tmph->eid = i;
            max = MMAX(max, i - tmph->sid);
        }
    }

    return max;
}


