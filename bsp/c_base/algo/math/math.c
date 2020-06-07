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
����һ���������tag[]��
tag[i]��ʾ��i���������i-1������Ԥ����λ�Ĳ
��tag[i] = a[i] - a[i - 1]��
����������ÿ��ɨ�赽[i, j, k]��
��ֻ��Ҫ��tag[i]����k��tag[j + 1]����k���ɡ�
��󣬼���a[i] = a[i - 1] + tag[i]������a���ɡ�
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
1010. �ܳ���ʱ��ɱ� 60 �����ĸ���
�ڸ����б��У��� i �׸����ĳ���ʱ��Ϊ time[i] �롣
�������ܳ���ʱ�䣨����Ϊ��λ���ɱ� 60 �����ĸ����Ե�������
��ʽ�ϣ�����ϣ������������  i < j ���� (time[i] + time[j]) % 60 == 0��
ʾ�� 1��
���룺[30,20,150,100,40]
�����3
���ͣ������Ե��ܳ���ʱ��ɱ� 60 ������
(time[0] = 30, time[2] = 150): �ܳ���ʱ�� 180
(time[1] = 20, time[3] = 100): �ܳ���ʱ�� 120
(time[1] = 20, time[4] = 40): �ܳ���ʱ�� 60
*/
int numPairsDivisibleBy60(int* time, int timeSize)
{
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

/*
��ѧ����:

1)
���һ������ʹ���0
������Ϊ���Σ���ôһ�������ҵ�һ����㣬
�Ӵ���㿪ʼתһȦ���������������ʹ�����
*/

/*
60. ��k������
�������� [1,2,3,��,n]��������Ԫ�ع��� n! �����С�
����С˳���г����������������һһ��ǣ�
�� n = 3 ʱ, �����������£�
"123"
"132"
"213"
"231"
"312"
"321"
���� n �� k�����ص� k �����С�
˵����
���� n �ķ�Χ�� [1, 9]��
���� k �ķ�Χ��[1,  n!]��
ʾ�� 1:
����: n = 3, k = 3
���: "213"
*/

/*
���磺 n = 6, k = 373
��ʼ������ nums = [1, 2, 3, 4, 5, 6];
����Ӧ�����ף��� 1 ��ͷ��ȫ������ 5! ����
�� 2 ��ͷ��ȫ������ 5! �� ����
�� 5! * 6 = 6! ����
�� k = 373 ʱ��
ȫ���еĵ�һ������Ӧ���� nums[ k / 5! ] = 4 ;
����ɾ�� 4, ��ʱ nums = [1, 2, 3, 5, 6]; k %= 5! = 12 ;
������������ nums ���ҵ� 12 ��ȫ���У��ظ� 1��2 ������ ��
*/

//�׳�(n!)
int factorial(int n)
{
	int num = 1;
	while (n > 0)
		num *= n--;
	return num;
}

void deleteItem(int *nums, int numsSize, int in)
{
	while (in < numsSize - 1)
		nums[in++] = nums[in + 1];
}

char *getPermutation(int n, int k)
{
	int i, j = 0, nums[n], factor;
	char *res = (char *)calloc(10, sizeof(char));

	for (i = 0; i < n; i++)  //��ʼ��һ�� [1,2,3,����,n] ����
		nums[i] = i + 1;
	for (i = 0, k--; i < n; i++) {  //kҪ�ȼ�ȥ1
		factor = factorial(n - i - 1);
		res[j++] = nums[k / factor] + '0';
		deleteItem(nums, n - i, k / factor);  //ȡ��һ��Ԫ��
		k %= factor;
	}
	return res;
}

/*
LCP 03. �����˴�ð��
�����Ŷ�����һ���ɱ�̻����ˣ�
�����˳�ʼλ����ԭ��(0, 0)��С������ȸ�����������һ��ָ
��command�������˾ͻ�����ѭ������ָ��Ĳ�������ƶ���
ָ�������֣�
U: ��y���������ƶ�һ��
R: ��x���������ƶ�һ��
���ҵ��ǣ��� xy ƽ���ϻ���һЩ�ϰ��
���ǵ�������obstacles��ʾ��������һ�������ϰ���ͻᱻ��١�
�����յ�����(x, y)�����ػ������ܷ���õص����յ㡣
����ܣ�����true�����򷵻�false�
ʾ�� 1��

���룺command = "URR", obstacles = [], x = 3, y = 2
�����true
���ͣ�U(0, 1) -> R(1, 1) -> R(2, 1) -> U(2, 2) -> R(3, 2)��
ʾ�� 2��

���룺command = "URR", obstacles = [[2, 2]], x = 3, y = 2
�����false
���ͣ��������ڵ����յ�ǰ������(2, 2)���ϰ��

*/
void lower(int *x, int *y, int d1, int d2)
{
	int p1 = *x /d1;
	int p2 = *y /d2;
	int min = p1 > p2 ? p2 : p1;
	*x = *x - min * d1;
	*y = *y - min * d2;
}

bool isOk(char * command, int x, int y)
{
	int i=0;
	while(x>=0 && y>=0) {
		if(x==0&&y==0)
			return true;
		if(*(command+i)=='U') {
			y--;
		}else  {
			x--;
		}
		i++;
	}

	if(x==0&&y==0)
	return true;
		else
	return false;
}

bool robot(char * command, int** obstacles, int obstaclesSize, int* obstaclesColSize, int x, int y)
{
	int nx = x, ny = y;
	int numU=0,numR=0;

	for(int i=0; i<strlen(command); i++) {
		if(*(command+i)=='U') {
			numU++;
		}else{
			numR++;
		}
	}

	lower(&nx,&ny,numR,numU);
	if(!isOk(command,nx,ny))
		return false;

	for(int i=0; i<obstaclesSize; i++) {
		if(obstacles[i][0]>x||obstacles[i][1]>y)
			continue;
		nx=obstacles[i][0];
		ny=obstacles[i][1];

		lower(&nx,&ny,numR,numU);
		if(isOk(command,nx,ny))
			return false;
	}

	return true;
}

/*
313. ��������
�Ѷ��е�80
��дһ�γ��������ҵ� n ������������
����������ָ���������������ǳ���Ϊ k �������б� primes �е���������
ʾ��:
����: n = 12, primes = [2,7,13,19]
���: 32
����: ��������Ϊ 4 �������б� primes = [2,7,13,19]��ǰ 12 ��������������Ϊ��[1,2,4,7,8,13,14,16,19,26,28,32] ��
˵��:
"	1 ���κθ��� primes �ĳ���������
"	 ���� primes �е��������������С�
"	0 < k �� 100, 0 < n �� 106, 0 < primes[i] < 1000 ��
*/

/*
 * @lc app=leetcode.cn id=313 lang=c
 *
 * [313] ��������
 */

// @lc code=start

//���㷨˼·����ѧ�������Ĺ��췽����
int nthSuperUglyNumber(int n, int* primes, int primesSize){
    if(n == 1)
    {
        return 1;
    }

    int *res = (int *)calloc(n, sizeof(int));
    int rsize = 0;

    int *pids = (int *)calloc(primesSize, sizeof(int));

    res[rsize++] = 1;

    while(rsize < n)
    {
        // ѡ����С��(����*res[pid])��������pid
        int min = INT_MAX;
        int id = 0;

        for(int i = 0; i < primesSize; i++)
        {
            int tmin = primes[i] * res[ pids[i] ];

            if(tmin < min)
            {
                min = tmin;
                id = i;
            }
            // ȥ���ظ�
            else if(tmin == min)
            {
                pids[i]++;
            }
        }

        res[rsize++] = min;
        pids[id]++;
    }

    return res[n - 1];
}

