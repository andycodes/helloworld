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
	if (height == NULL ||heightSize <= 0)
		return 0;

	int right[heightSize];

	//right max
	right[heightSize - 1] = height[heightSize - 1];
	for (int i = heightSize - 2; i >= 0; i--) {
		right[i] = fmax(right[i + 1], height[i + 1]); //right max
	}

	int sum = 0;
	int leftmax = height[0];
	for (int i = 1; i < heightSize; i++) {
		leftmax = fmax(leftmax, height[i - 1]);
		int min = fmin(leftmax, right[i]);
		sum += min > height[i] ? min - height[i] : 0;
	}

	return sum;
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
typedef struct _hash_st {
	int key;
	int sumValueFirstIdx;
	UT_hash_handle hh;
}hash_st;

//���㷨˼·������+hash�������01���⣬��0ת��Ϊ-1��
// ����ת��Ϊ������к�Ϊ0,ʹ��hash�����
int findMaxLength(int* nums, int numsSize)
{
    if(numsSize <= 1) {
        return 0;
    }

    hash_st *hashmap = NULL;
    int max = 0;

    //0 -> -1 && ���� && ����hash
    int sum = 0;
    for(int i = 0; i < numsSize; i++) {
        //0ת-1������
        sum += nums[i] == 0? -1 : 1;

        if(sum == 0) {
            //��sumΪ0��ֱ��Ϊ���
            max = fmax(max, i + 1);
        } else {
            int target = sum;

            hash_st *find = NULL;
            //HASH_FIND(hh, hashmap, &key, sizeof(key), find);
            HASH_FIND_INT(hashmap, &target, find);
            if(find == NULL) {
                find = (hash_st *)calloc(1, sizeof(hash_st));
                find->key = target;
                find->sumValueFirstIdx = i;

                //HASH_ADD_KEYPTR(hh, hashmap, &find->key, sizeof(find->key), find);
                HASH_ADD_INT(hashmap, key, find);
            } else {
		max = fmax(max, i - find->sumValueFirstIdx);
	}
        }
    }

    return max;
}
