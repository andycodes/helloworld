/*
������ n �����࣬���Ƿֱ�� 1 �� n ���б�š�

���������һ�ݺ���Ԥ�������е� i ��Ԥ����¼ bookings[i] = [i, j, k] ��ζ�������ڴ� i �� j ��ÿ��������Ԥ���� k ����λ��

���㷵��һ������Ϊ n ������ answer����������˳�򷵻�ÿ��������Ԥ������λ����



ʾ����

���룺bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
�����[10,55,45,25,25]


��a[i]��ʾ��i������Ԥ������λ����

����һ���������tag[]��tag[i]��ʾ��i���������i-1������Ԥ����λ�Ĳ��tag[i] = a[i] - a[i - 1]��

����������ÿ��ɨ�赽[i, j, k]����ֻ��Ҫ��tag[i]����k��tag[j + 1]����k���ɡ�

��󣬼���a[i] = a[i - 1] + tag[i]������a���ɡ�

*/
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize){
	int *diff = malloc(20001 * sizeof(int));
	memset((void*)diff,0,20001*sizeof(int));

	for(int i = 0; i < bookingsSize; i++){
		diff[bookings[i][0]-1] += bookings[i][2];
		diff[bookings[i][1]]   -= bookings[i][2];
	}

	for(int i = 1; i < n; i++) {
		diff[i] += diff[i -1];
	}

	*returnSize = n;
	return diff;
}

