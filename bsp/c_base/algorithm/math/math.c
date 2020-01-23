/*�ж��������Ƿ����*/
int x = -1, y = 2;
bool f = ((x ^ y) < 0); // true

int x = 3, y = 2;
bool f = ((x ^ y) < 0); // false



/*����ֵ*/
int abs(int);

/* sqrt() ���������ֵ��ƽ���� */
double sqrt(double x);

/*pow() ���������� x �� y ���ݣ��η���*/
double pow(double x, double y);

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

/*
1010. �ܳ���ʱ��ɱ� 60 �����ĸ���
�ڸ����б��У��� i �׸����ĳ���ʱ��Ϊ time[i] �롣

�������ܳ���ʱ�䣨����Ϊ��λ���ɱ� 60 �����ĸ����Ե���������ʽ�ϣ�����ϣ������������  i < j ���� (time[i] + time[j]) % 60 == 0��



ʾ�� 1��

���룺[30,20,150,100,40]
�����3
���ͣ������Ե��ܳ���ʱ��ɱ� 60 ������
(time[0] = 30, time[2] = 150): �ܳ���ʱ�� 180
(time[1] = 20, time[3] = 100): �ܳ���ʱ�� 120
(time[1] = 20, time[4] = 40): �ܳ���ʱ�� 60

*/

int numPairsDivisibleBy60(int* time, int timeSize){
	int result = 0;
	int mod[60];

	memset((void*)mod, 0, sizeof(mod));

	for(int i = 0; i < timeSize; i++) {
		mod[time[i] % 60]++;
	}

	for (int i = 1; i < 30; i++) {
		result += mod[i] * mod[60 - i];
	}

	result += (mod[0] * (mod[0] - 1) + mod[30] * (mod[30] - 1)) / 2;

	return result;
}

