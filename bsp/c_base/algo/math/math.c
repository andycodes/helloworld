/*��ѧ������
1e-6
*/

/*�ж��������Ƿ����*/
int x = -1, y = 2;
bool f = ((x ^ y) < 0); // true

int x = 3, y = 2;
bool f = ((x ^ y) < 0); // false

int abs(int);
double fabs(double x);

/* sqrt() ���������ֵ��ƽ���� */
double sqrt(double x);
/*pow() ���������� x �� y ���ݣ��η���*/
double pow(double x, double y);

void num(void)
{
	if (isdigit(s[i])) {
		num = num * 10 + s[i] - '0';
	}
}

/*
1010. �ܳ���ʱ��ɱ� 60 �����ĸ���
�ڸ����б��У��� i �׸����ĳ���ʱ��Ϊ time[i] �롣
�������ܳ���ʱ�䣨����Ϊ��λ���ɱ� 60 �����ĸ����Ե�������
��ʽ�ϣ�����ϣ������������  i < j ���� (time[i] + time[j]) % 60 == 0��
1 <= time[i] <= 500

ʾ�� 1��
���룺[30,20,150,100,40]
�����3
���ͣ������Ե��ܳ���ʱ��ɱ� 60 ������
(time[0] = 30, time[2] = 150): �ܳ���ʱ�� 180
(time[1] = 20, time[3] = 100): �ܳ���ʱ�� 120
(time[1] = 20, time[4] = 40): �ܳ���ʱ�� 60

1)�������ж���%60
2)��ϵĿ�����
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


void deleteItem(int *nums, int pos, int moveSize)
{
	while (pos < moveSize - 1)
		nums[pos++] = nums[pos + 1];
}

char *getPermutation(int n, int k)
{
	int i, j = 0, nums[n], factor;
	char *res = (char *)calloc(10, sizeof(char));

	for (i = 0; i < n; i++)  //��ʼ��һ�� [1,2,3,����,n] ����
		nums[i] = i + 1;
	for (i = 0, k--; i < n; i++) {  //kҪ�ȼ�ȥ1   ���� k �ķ�Χ��[1,  n!]��
		factor = factorial(n - i - 1);
		res[j++] = nums[k  / factor] + '0';
		deleteItem(nums, k / factor, n - i);  //ȡ��һ��Ԫ��
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
void lower(int *x, int *y, int numR, int numU)
{
	int p1 = *x /numR;
	int p2 = *y /numU;
	int min = p1 > p2 ? p2 : p1;
	*x = *x - min * numR;
	*y = *y - min * numU;
}

bool isOk(char * command, int newCntR, int newCntU)
{
	int i=0;
	while(newCntR>=0 && newCntU>=0) {
		if(newCntR==0&&newCntU==0)
			return true;
		if(*(command+i)=='U') {
			newCntU--;
		}else  {
			newCntR--;
		}
		i++;
	}

	if(newCntR==0&&newCntU==0)
	return true;
		else
	return false;
}

bool robot(char * command, int** obstacles, int obstaclesSize, int* obstaclesColSize, int x, int y)
{
	int newCntR = x, newCntU = y;
	int numU=0,numR=0;

	for(int i=0; i<strlen(command); i++) {
		if(*(command+i)=='U') {
			numU++;
		}else{
			numR++;
		}
	}

	lower(&newCntR,&newCntU,numR,numU);
	if(!isOk(command,newCntR,newCntU))
		return false;

	for(int i=0; i<obstaclesSize; i++) {
		if(obstacles[i][0]>x||obstacles[i][1]>y)
			continue;
		newCntR=obstacles[i][0];
		newCntU=obstacles[i][1];

		lower(&newCntR,&newCntU,numR,numU);
		if(isOk(command,newCntR,newCntU))
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
int nthSuperUglyNumber(int n, int* primes, int primesSize)
{
	if(n == 1) {
		return 1;
	}

	int *res = (int *)calloc(n, sizeof(int));
	int rsize = 0;

	int *pids = (int *)calloc(primesSize, sizeof(int));

	res[rsize++] = 1;

	while(rsize < n) {
		// ѡ����С��(����*res[pid])��������pid
		int min = INT_MAX;
		int id = 0;

		for(int i = 0; i < primesSize; i++) {
			int tmin = primes[i] * res[ pids[i] ];

			if(tmin < min) {
				min = tmin;
				id = i;
			} else if(tmin == min){
				pids[i]++; // ȥ���ظ�
			}
		}

		res[rsize++] = min;
		pids[id]++;
	}

	return res[n - 1];
}

/*
1371. ÿ��Ԫ������ż���ε�����ַ���
�Ѷ��е�245
����һ���ַ��� s �����㷵��������������������ַ�����
���ȣ�ÿ��Ԫ����ĸ���� 'a'��'e'��'i'��'o'��'u' �������ַ����ж�ǡ
�ó�����ż���Ρ�

ʾ�� 1��
���룺s = "eleetminicoworoep"
�����13
���ͣ�����ַ����� "leetminicowor" �������� e��i��o �� 2 ������
�� 0 �� a��u ��
ʾ�� 2��
���룺s = "leetcodeisgreat"
�����5
���ͣ�����ַ����� "leetc" �����а��� 2 �� e ��
ʾ�� 3��
���룺s = "bcbcbc"
�����6
���ͣ����ʾ���У��ַ��� "bcbcbc" ���������ģ���Ϊ����
��Ԫ�� a��e��i��o��u ����
*/
/*
0 ���������ż���Σ�1 ���������������
00000 ~ 11111 һ��2^5��32��״̬��0��ʾ����ż����1��ʾ��������
*/
int findTheLongestSubstring(char * s)
{
	int n = strlen(s);
	int pos[32] = {-1};
	int status = 0;
	int ans = 0;

	for (int i = 0; i < 32; i++) {
		pos[i] = -1;
	}

	pos[0] = 0;

	for (int i = 0; i < n; i ++) {
            if (s[i] == 'a') {
                status ^= 1<<0;
            } else if (s[i] == 'e') {
                status ^= 1<<1;
            } else if (s[i] == 'i') {
                status ^= 1<<2;
            } else if (s[i] == 'o') {
                status ^= 1<<3;
            } else if (s[i] == 'u') {
                status ^= 1<<4;
            }
            if (pos[status] != -1) {
                ans = fmax(ans, i + 1 - pos[status]);
            } else {
                pos[status] = i + 1;
            }
	}

        return ans;
}

/*
1296. ��������Ϊ�������ֵļ���
�Ѷ��е�25
����һ���������� nums ��һ�������� k�������ж��Ƿ���԰�
������黮�ֳ�һЩ�� k ������������ɵļ��ϡ�
������ԣ��뷵�� True�����򣬷��� False��

ʾ�� 1��
���룺nums = [1,2,3,3,4,4,5,6], k = 4
�����true
���ͣ�������Էֳ� [1,2,3,4] �� [3,4,5,6]��

*/
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
bool isPossibleDivide(int* nums, int numsSize, int k){
    int min, cnt, j;
    if (numsSize % k != 0) {
        return false;
    }
    qsort(nums, numsSize, sizeof(int), cmp);
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            min = nums[i];
            cnt = 0;
            for (j = i; (j < numsSize) && (cnt < k); j++) {
                if (nums[j] == min){
                    cnt++;
                    min++;
                    nums[j] = 0;
                }
            }
            if (cnt < k) {
                return false;
            }
        }
    }
    return true;
}

/*
442. �������ظ�������
�Ѷ��е�205
����һ���������� a������1 �� a[i] �� n ��nΪ���鳤�ȣ�, ������
ЩԪ�س������ζ�����Ԫ�س���һ�Ρ�
�ҵ����г������ε�Ԫ�ء�
����Բ��õ��κζ���ռ䲢��O(n)ʱ�临�Ӷ��ڽ�����
������
ʾ����
����:
[4,3,2,7,8,2,3,1]

���:
[2,3]

*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDuplicates(int* nums, int numsSize, int* returnSize)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	int *res = (int *)calloc(numsSize, sizeof(int));
	*returnSize = 0;
	if (numsSize <= 1)
		return res;

	for(int i = 0; i < numsSize - 1; i++) {
		if (nums[i] == nums[i + 1]) {
			res[*returnSize] = nums[i];
			(*returnSize)++;
			i++;
		}
	}

	return res;
}

/*
������ 16.11. ��ˮ��
������ʹ��һ��ľ�彨����ˮ�塣���������͵�ľ�壬���г��Ƚ϶̵�ľ�峤��Ϊshorter�����Ƚϳ���ľ�峤��Ϊlonger�����������ʹ��k��ľ�塣��дһ��������������ˮ�����п��ܵĳ��ȡ�

���صĳ�����Ҫ��С�������С�

ʾ�� 1

���룺
shorter = 1
longer = 2
k = 3
����� [3,4,5,6]
���ͣ�
����ʹ�� 3 �� shorter���õ���� 3��ʹ�� 2 �� shorter �� 1 �� longer���õ���� 4 ���Դ����ƣ��õ����ս����
*/

int* divingBoard(int shorter, int longer, int k, int* returnSize) {
    if (k == 0) {
        *returnSize = 0;
        return NULL;
    }
    if (shorter == longer) {
        int* p = (int*)malloc(sizeof(int));
        *p = shorter * k;
        *returnSize = 1;
        return p;
    }
    *returnSize = k + 1;
    int* lengths = (int*)malloc(sizeof(int) * (k + 1));
    for (int i = 0; i <= k; ++i) {
        lengths[i] = shorter * (k - i) + longer * i;
    }
    return lengths;
}

/*
625. ��С��ʽ�ֽ�
����һ�������� a���ҳ���С�������� b ʹ�� b ��������λ���ǡ�õ��� a��

��������������Ľ�����߽������ 32 λ�з������������� 0��



���� 1

���룺

48
�����

68s
*/

int smallestFactorization(int a)
{
        if (a <= 1) return a;
        long b = 0;
        long tmp = 1;   // Ȩֵ,1 ��ʾ��λ��10��ʾʮλ��100��ʾ��λ
        // b �ǵ��������ģ�������һλ�ǳ��� 8 �ģ�����һλ�͵ô� 8 ��ʼ������
        for (int i = 9; i >= 2; i--) {  // ע�� i ����ȡ�� 1���������ѭ��
            while (a % i == 0) {    // �ܲ��ܱ� i ����
                a /= i; // �ҵ�һ���������� a �� i������ a Ϊ a/i
                b = tmp * i + b;    // ������ȷ����λ
                tmp *= 10;
            }
        }
        // �������� a ��Ϊ 1��˵����ʱ�� a �϶�������
        return a == 1 && b <= INT_MAX ? (int) b : 0;
}

/*
1498. ������������������Ŀ
����һ���������� nums ��һ������ target ��
����ͳ�Ʋ����� nums ������������СԪ�������Ԫ�ص� �� С
�ڻ���� target �� �ǿ� �����е���Ŀ��
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
/*������˵� i �����������������и���Ϊ��2^{j-i} ��*/
/* min��max֮�����е��Ӽ���������Ҫ��ġ�����Ϊ2 ^ (maxIdx - minIdx). */
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

/*
447. �����ڵ�����
����ƽ���� n �Բ�ͬ�ĵ㣬�������ڡ� ���ɵ��ʾ��Ԫ�� (i, j, k) ������ i �� j ֮��ľ���� i �� k ֮��ľ�����ȣ���Ҫ����Ԫ���˳�򣩡�

�ҵ����л����ڵ�����������Լ��� n ���Ϊ 500�����е�������ڱ����� [-10000, 10000] �С�

ʾ��:

����:
[[0,0],[1,0],[2,0]]

���:
2

����:
����������Ϊ [[1,0],[0,0],[2,0]] �� [[1,0],[2,0],[0,0]]
*/
int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize)
{
	int* Distances = (int*)malloc(sizeof(int) * pointsSize);
	int Num_Boo = 0;

	for(int i = 0; i < pointsSize; i++){
		for(int j = 0; j < pointsSize; j++) {
			Distances[j] = pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2);
		}

		qsort(Distances, pointsSize, sizeof(int), cmp_int);
		int Count = 1;
		for(int j = 1; j < pointsSize; j++){
			if(Distances[j] == Distances[j - 1]){
				Count++;
			}else if(Count > 1){
				Num_Boo += Count * (Count - 1);
				Count = 1;
			}else{
				continue;
			}
		}
		Num_Boo += Count * (Count - 1);
	}

	free(Distances);
	return Num_Boo;
}


/*
357. �������λ����ͬ�����ָ���
����һ���Ǹ����� n�������λ���ֶ���ͬ������ x �ĸ�����
���� 0 �� x < 10n ��
ʾ��:
����: 2
���: 91
����: ��ӦΪ��ȥ 11,22,33,44,55,66,77,88,99 �⣬�� [0,100) �����ڵ���
�����֡�
*/
int countNumbersWithUniqueDigits(int n)
{
        if (n == 0)
			return 1;
        int res = 10, k = 9, temp = 9;
        for (int i = 2; i <= fmin(n, 10); ++i){
            temp *= k;
            k--;
            res += temp;
        }
        return res;
}

int randomInt(int min, int max)
{
	int ret = rand() % (max - min + 1) + min;
	return ret;
}

