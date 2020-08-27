
/*
1109. ����Ԥ��ͳ��
������ n �����࣬���Ƿֱ�� 1 �� n ���б�š�
���������һ�ݺ���Ԥ����
���е� i ��Ԥ����¼ bookings[i] = [i, j, k] ��ζ�������ڴ� i �� j ��
ÿ��������Ԥ���� k ����λ��
���㷵��һ������Ϊ n ������ answer��
��������˳�򷵻�ÿ��������Ԥ������λ����
ʾ����

���룺bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
�����[10,55,45,25,25]


��a[i]��ʾ��i������Ԥ������λ����
����һ���������diff[]��
diff[i]��ʾ��i���������i-1������Ԥ����λ�Ĳ
��diff[i] = a[i] - a[i - 1]��
����������ÿ��ɨ�赽[i, j, k]��
��ֻ��Ҫ��diff[i]����k��diff[j + 1]����k���ɡ�
��󣬼���a[i] = a[i - 1] + diff[i]������a���ɡ�
*/
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize,
int n, int* returnSize){
	int *diff = malloc(20001 * sizeof(int));
	memset((void*)diff,0,20001*sizeof(int));

	for(int i = 0; i < bookingsSize; i++){
		diff[bookings[i][0]-1] += bookings[i][2]; //�Ȳʼ���ϵȲ�ֵ
		diff[bookings[i][1]]   -= bookings[i][2]; //�Ȳ���� �����Ȳ�ֵ
	}

	for(int i = 1; i < n; i++) {
		diff[i] += diff[i -1];//�Ƶ�ԭʼֵ
	}

	*returnSize = n;
	return diff;
}

/*
1343. ��СΪ K ��ƽ��ֵ���ڵ�����ֵ����������Ŀ
����һ���������� arr ���������� k �� threshold ��

���㷵�س���Ϊ k ��ƽ��ֵ���ڵ��� threshold ����������Ŀ��



ʾ�� 1��

���룺arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
�����3
���ͣ������� [2,5,5],[5,5,5] �� [5,5,8] ��ƽ��ֵ�ֱ�Ϊ 4��5 �� 6 ����������Ϊ 3 ���������ƽ��ֵ��С�� 4 ��threshold ��ֵ)��
*/
int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
    int preSum[arrSize + 1];
    memset(preSum,0,sizeof(int) * (arrSize + 1));
    preSum[0] = arr[0];
    for (int i = 1; i <= arrSize; i++) {
        preSum[i] += arr[i - 1] + preSum[i - 1];
    }
    int retNum = 0;
    for(int i = k ; i <= arrSize; i++) {
        int sum = preSum[i] - preSum[i - k];
        if(sum / k >= threshold) {
            retNum++;
        }
    }
    return retNum;
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
int subarraysDivByK(int* A, int ASize, int K){
    int hash[K];
    memset(hash,0,sizeof(hash));
    for(int i=1;i<ASize;i++)//ǰ׺��
    {
        A[i]=A[i-1]+A[i];
    }
    for(int i=0;i<ASize;i++)//����Ϊ���Ĺ�ϣ��
    {
       hash[(A[i]%K+K)%K]++;//��������
    }
    int sum=0;
    for(int i=0;i<K;i++)//ͳ����ͬ��������Ҫ�����Ŀ
    {
        sum+=hash[i]*(hash[i]-1)/2;
    }
    return sum+hash[0];//���ϵ�����������Ϊ�����Ŀ
}

int subarraysDivByK(int* A, int ASize, int K)
{
        int map[K];
		memset(map, 0, sizeof(map));
		map[0] = 1;

        int PreSum=0;
        int Count=0;
        for(int i=0;i<ASize;i++){
            PreSum=PreSum+A[i];//��ǰ���ǰ׺�� = ��һ���ǰ׺�� + ��ǰ��
            int remain=PreSum%K;//��ǰ��ǰ׺��%K�Ľ��

            //%K���Ϊ�����������Ҫ����
            if(remain<0) remain=remain+K;

            if(map[remain]){
                Count+=map[remain];//����remain֮ǰ���ڣ�������ڵĵ�ǰ�������map[remain]����Ͽ���
                map[remain]++;//����remain֮ǰ���ֵĴ�����Ҫ����
            }
            else{
                map[remain]=1;//����remain֮ǰ������
            }
        }

        return Count;

}

int subarraysDivByK(int* A, int ASize, int K){
    if (K == 0 || ASize == 0) {
        return 0;
    }
    int ans=0;
    int *presum=(int*)malloc(sizeof(int)*(ASize+1));
    presum[0]=0;
    for(int i=0;i<ASize;i++){
        presum[i+1]=presum[i]+A[i];
    }
    int *arr=(int*)malloc(sizeof(int)*K);
    memset(arr,0,K*sizeof(int));
    for(int i=0;i<ASize+1;i++){
        arr[(presum[i]%K +K)%K]++;
    }
    int count=0;
    for(int i=0;i<K;i++){
        count+=(arr[i]*(arr[i]-1))/2;

    }
    return count;
}

int subarraysDivByK(int* A, int ASize, int K){
    if (K == 0 || ASize == 0 || A == NULL) {
        return 0;
    }

    int *map = (int *)calloc(K, sizeof(int));
    map[0] = 1;
    int sum = 0;
    int count = 0;

    for (int i = 0; i < ASize; i++) {
        sum += A[i];
        int key = (sum % K + K) % K;
        count += map[key];
        map[key]++;
    }

    free(map);
    return count;
}

/*
42. ����ˮ
�Ѷ�����1499
���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ��

������������ [0,1,0,2,1,0,1,3,2,1,2,1] ��ʾ�ĸ߶�ͼ������������£����Խ� 6 ����λ����ˮ����ɫ���ֱ�ʾ��ˮ���� ��л Marcos ���״�ͼ��
ʾ��:
����: [0,1,0,2,1,0,1,3,2,1,2,1]
���: 6

*/
int trap(int* height, int heightSize)
{
    int ans = 0;
    int size = heightSize;
    for (int i = 1; i < size - 1; i++) {
        int max_left = 0, max_right = 0;
        for (int j = i; j >= 0; j--) { //Search the left part for max bar size
            max_left = fmax(max_left, height[j]);
        }
        for (int j = i; j < size; j++) { //Search the right part for max bar size
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
	int size = heightSize;
	int left_max[size];
	int right_max[size];
    left_max[0] = height[0];
    for (int i = 1; i < size; i++) {
        left_max[i] = fmax(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = fmax(height[i], right_max[i + 1]);
    }
    for (int i = 1; i < size - 1; i++) {
        ans += fmin(left_max[i], right_max[i]) - height[i];
    }
    return ans;

}

int trap(int* height, int heightSize)
{
	if (height == NULL || heightSize <= 0)
		return 0;

	int ans = 0, current = 0;
	int stackSize = fmax(heightSize, 1024);
	int stack[stackSize];
	int top = -1;

	while (current < heightSize) {
		while (top > -1 && height[current] > height[stack[top]]) {
			int low = stack[top--];
			if (top < 0)
				break;
			int distance = current - stack[top] - 1;
			int bounded_height = fmin(height[current], height[stack[top]]) - height[low];
			ans += distance * bounded_height;
		}

		stack[++top] = current++;
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

/*ǰ���prefixSum  (�����Ӻ�)
������������;�����ʹ��ǰ׺�����Ż�
������A(i,j]�ĺ�Ϊsum[j] - sum[i]
��i��Ԫ�ص�ǰ׺�� = ǰi-1��Ԫ��֮�͡�
��Ԫ��û��ǰ׺���涨Ϊ0��
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
	for (int i = 0; i < cardPointsSize; i++) {
		prefixSum[i + 1] = prefixSum[i] + cardPoints[i];
	}

	int max = -1;
	for (int i = 0; i <=  k; i++) {
		max = fmax(max, prefixSum[i] + prefixSum[cardPointsSize] - prefixSum[cardPointsSize - k + i]);
	}

	return max;
}

/*
��������˼ȡ��ȡ�ҵ����ֵ���������������м�����
������ú���С,����Ҫȡ k ���ƣ�
���Է������������м��������ĳ���Ϊ len(carPoints)-k ��
������ʹ�����С���������ƶ� k �Σ�
���ϸ��»����ܵõ��͵���Сֵ��
�������������ĺͼ�ȥ�����Сֵ���ǽ����
��һ�Ÿ��Դ��� index��
�ڶ��д����Ӧλ�õ���ֵ,�õ������е�һ��������
*/
int maxScore(int* cardPoints, int cardPointsSize, int k)
{
	int prefixSum[cardPointsSize + 1];
	prefixSum[0] = 0;
	for (int i = 0; i < cardPointsSize; i++) {
		prefixSum[i + 1] = prefixSum[i] + cardPoints[i];
	}

	int ans = 0x3f3f3f3f;
	int t = cardPointsSize - k;
	for (int j = t;  j <= cardPointsSize; j++) {
		ans = fmin(ans, prefixSum[j] - prefixSum[j - t]);
	}

	return prefixSum[cardPointsSize] - ans;
}