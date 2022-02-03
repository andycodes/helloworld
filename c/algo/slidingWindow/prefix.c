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



