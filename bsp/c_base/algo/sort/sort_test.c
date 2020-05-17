
/*
324. �ڶ����� II
����һ����������� nums�������������г� nums[0] < nums[1] > nums[2] < nums[3]... ��˳��

ʾ�� 1:

����: nums = [1, 5, 1, 1, 6, 4]
���: һ�����ܵĴ��� [1, 4, 1, 5, 1, 6]

��С���ݷ�2��+С���齵�����������+��С���黥�ഩ��
*/
void wiggleSort(int* nums, int numsSize){
	if (nums == NULL || numsSize < 2)
		return;

	qsort(nums, numsSize, sizeof(int), cmp_int);

	int big_count = 0, small_count = 0;

	if (numsSize % 2 == 1) {
		big_count = numsSize / 2;
		small_count = numsSize / 2 + 1;
	} else {
		big_count = numsSize / 2;
		small_count = numsSize / 2;
	}

	int big[big_count];
	int small[small_count];

	for (int i = 0; i < small_count; i++) {
		 small[small_count-i-1] = nums[i];
	}

	for(int i = small_count; i < numsSize; i++){
            big[i-small_count] = nums[i];
        }

	int small_index = 0, big_index = big_count-1;
        for(int i=0;i<numsSize;i++){
            if(i % 2 == 0){
                nums[i] = small[small_index];
                small_index++;
            }else{
                nums[i] = big[big_index];
                big_index--;
            }
        }
}

/*
853. ����
�Ѷ��е�47
N  ��������һ������ʻ��λ�� target Ӣ��֮��Ĺ�ͬĿ�ĵء�
ÿ���� i �Ժ㶨���ٶ� speed[i] ��Ӣ��/Сʱ�����ӳ�ʼλ�� position[i] ��Ӣ� �س���ʻ��Ŀ�ĵء�
һ������Զ���ᳬ��ǰ�����һ��������������׷��ȥ������ǰ������ͬ���ٶȽ�������ʻ��
��ʱ�����ǻ������������֮��ľ��룬Ҳ����˵�����Ǳ��ٶ�������ͬ��λ�á�
���� ��һЩ����ʻ����ͬλ�á�������ͬ�ٶȵĳ���ɵķǿռ��ϡ�ע�⣬һ����Ҳ������һ�����ӡ�
����һ������Ŀ�ĵزŸ�����һ�����ӣ�������Ȼ�ᱻ������ͬһ�����ӡ�

���ж��ٳ��ӵ���Ŀ�ĵ�?

ʾ����
���룺target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
�����3
���ͣ�
�� 10 �� 8 ��ʼ�ĳ������һ�����ӣ������� 12 ��������
�� 0 ����ʼ�ĳ��޷�׷�����������������Լ�����һ�����ӡ�
�� 5 �� 3 ��ʼ�ĳ������һ�����ӣ������� 6 ��������
��ע�⣬�ڵ���Ŀ�ĵ�֮ǰû����������������Щ���ӣ����Դ��� 3��

*/

struct Car {
    int pos;
    int speed;
};

int cmp_struct(const void *a, const void *b)
{
    struct Car *c = (struct Car *)a;
     struct Car *d = (struct Car *)b;

     return c->pos - d->pos;
}

bool isMeet(struct Car  curCar, struct Car  nextCar, int target)
{
        if (curCar.speed <= nextCar.speed) {
            return false;
        }

        double t = (nextCar.pos - curCar.pos) * 1.0 / (curCar.speed - nextCar.speed);
        return curCar.speed * t + curCar.pos <= target;
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize)
{
    if (position == NULL || positionSize <= 0 || speed == NULL || speedSize <= 0) {
        return 0;
    }

    struct Car *car = (struct Car *)calloc(positionSize, sizeof(struct Car *));
    for (int i = 0; i < positionSize; i++) {
        car[i].pos = position[i];
        car[i].speed = speed[i];
    }

    qsort(car, positionSize, sizeof(car[0]), cmp_struct);

    int group = 1;
    struct Car nextCar = car[positionSize - 1];
    for (int i = positionSize - 2; i >= 0; i--) {
        if(!isMeet(car[i], nextCar, target)) {
            group++;
            nextCar = car[i];
        }
    }

    return group;
}

/*
������ 16.16. ��������
����һ���������飬��дһ���������ҳ�����m��n��ֻҪ����������[m,n]��Ԫ���ź������������������ġ�ע�⣺n-m������С��Ҳ����˵���ҳ�����������������С���������ֵΪ[m,n]����������������m��n��������������������ģ����뷵��[-1,-1]��

ʾ����

���룺 [1,2,4,7,10,11,7,12,6,7,16,18,19]
����� [3,9]
��ʾ��

0 <= len(array) <= 1000000
*/

/*
array��ĳ������������ǰ��λ�ò��䣬������������������
1. ǰ��û�б��Լ�С�����֣�
2.����û�б��Լ�������֡�
����dp���������������Ϣ�� dp[i]=true��ʾarray[i]������ǰ��λ�ò��䣬dp[i]=false����ʾ������ǰ��array[i]λ�÷����仯��
��ǰ���ɨ�����飬���ϸ���ɨ�赽�����ֵ���ȿ����жϵ�ǰarray[i]֮ǰ�Ƿ���ڱ��Լ�С�����֣����������dp[i]��Ϊfalse;
�Ӻ���ǰɨ�����飬���ϸ���ɨ�赽����Сֵ���ȿ����жϵ�ǰarray[i]֮���Ƿ���ڱ��Լ�С�����֣����������dp[i]��Ϊfalse;
�ҵ�dp[i]Ϊfalse����С������i����ΪҪ���ص�����
*/

int* subSort(int* array, int arraySize, int* returnSize){
     int *ret = (int *)calloc(2, sizeof(int));
     ret[0] = -1;
    ret[1] = -1;
    *returnSize = 2;
    if (arraySize <= 0 || arraySize == NULL ) {
        return ret;
    }

    int dp[arraySize];
    memset(dp, 0, sizeof(dp));
    int maxval = array[0];
    for (int i = 0; i < arraySize; i++) {
        if (array[i] < maxval) {
            dp[i] = 1;
        } else {
            maxval = array[i];
        }
    }

    int minval = array[arraySize - 1];
    int rmax = -1;
    int rmin = arraySize;
    for(int i = arraySize - 1; i >= 0; i--) {
        if (array[i] > minval) {
            dp[i] = 1;
        } else {
            minval = array[i];
        }

        if(dp[i] == 1) {
                rmax = fmax(rmax, i);
                rmin = fmin(rmin, i);
        }
    }

    if (rmax != -1) {
        ret[0] = rmin;
        ret[1] = rmax;
    }

    return ret;
}

/*
1366. ͨ��ͶƱ���Ŷ�����
�Ѷ��е�18
������һ�����������ϵͳ�����ݲ����Ŷ���ͶƱ�����еĴ������������ÿ��ͶƱ�߶���Ҫ���Ӹߵ��͵�˳��Բ��������������Ŷӽ�����λ��
�����������£�
"	�����Ŷӵ���������������������λ��һ����Ʊ�Ķ��پ�����������ڶ���ŶӲ��е�����������������䡸��λ�ڶ�����Ʊ���������Դ����ƣ�ֱ�����ٴ��ڲ��е������
"	����ڿ���������ͶƱ�������Ȼ���ֲ�������������Ŷ���ĸ����ĸ˳�����������
����һ���ַ������� votes ����ȫ��ͶƱ�߸�������λ����������������������������в����Ŷӽ���������
���㷵���ܱ�ʾ������ϵͳ ����� �������Ŷ��������ַ�����

ʾ�� 1��
���룺votes = ["ABC","ACB","ABC","ACB","ACB"]
�����"ACB"
���ͣ�A �ӻ����Ʊ����λ��һ����û�������ӻ�á���λ��һ�������� A ��������һ��
B �ӻ����Ʊ����λ�ڶ�������Ʊ����λ��������
C �ӻ����Ʊ����λ�ڶ�������Ʊ����λ��������
���� C �ӡ���λ�ڶ�����Ʊ���϶࣬���� C ���ŵڶ���B ���ŵ�����
ʾ�� 2��
���룺votes = ["WXYZ","XYZW"]
�����"XWYZ"
���ͣ�X ���ڲ��н��ִ��ƺ��Ϊ������һ���Ŷӡ�X �Ӻ� W �ӵġ���λ��һ��Ʊ��һ�������� X ����һƱ����λ�ڶ������� W û�л�á���λ�ڶ�����
ʾ�� 3��
���룺votes = ["ZMNAGUEDSJYLBOPHRQICWFXTVK"]
�����"ZMNAGUEDSJYLBOPHRQICWFXTVK"
���ͣ�ֻ��һ��ͶƱ�ߣ�����������ȫ����������Ը��
ʾ�� 4��
���룺votes = ["BCA","CAB","CBA","ABC","ACB","BAC"]
�����"ABC"
���ͣ�
A �ӻ����Ʊ����λ��һ������Ʊ����λ�ڶ�������Ʊ����λ��������
B �ӻ����Ʊ����λ��һ������Ʊ����λ�ڶ�������Ʊ����λ��������
C �ӻ����Ʊ����λ��һ������Ʊ����λ�ڶ�������Ʊ����λ��������
��ȫ���У�����������Ҫ������ĸ����������

*/

struct Sort {
	char c;
	int cnt[26];
	int flag;
};

int cmp_struct(const void *a, const void *b)
{
	struct Sort *c = (struct Sort *)a;
	struct Sort *d = (struct Sort *)b;


	for (int i = 0; i < 26; i++){
		if (c->cnt[i] != d->cnt[i]) {
			return d->cnt[i] - c->cnt[i];
		}
	}

	return c->c - d->c;
}

char * rankTeams(char ** votes, int votesSize)
{
	struct Sort hash[26];
	memset(hash, 0, sizeof(hash));

	for (int i = 0; i < 26; i++) {
		hash[i].c = 'A' + i;
	}

	for(int i = 0; i < votesSize; i++) {
		int j = 0;
		while(votes[i][j] != '\0') {
			hash[votes[i][j] - 'A'].cnt[j]++;
			hash[votes[i][j] - 'A'].flag = 1;
			j++;
		}
	}

	qsort(hash, 26, sizeof(hash[0]), cmp_struct);
	char *ret = (char *)calloc(27, sizeof(char));
	int retCnt = 0;
	for(int i = 0; i < 26; i++) {
		if (hash[i].flag == 1)
			ret[retCnt++] = hash[i].c;
	}

	return ret;
}

/*
������45. �������ų���С����
�Ѷ��е�33
����һ�����������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ���������������С��һ����

ʾ�� 1:
����: [10,2]
���: "102"
ʾ�� 2:
����: [3,30,34,5,9]
���: "3033459"

*/

int cmp_str(const void *a, const void *b)
{
	char e[101] = {{0}};
	char f[101] = {{0}};
	sprintf(e, "%d", *((int *)a));
	sprintf(f, "%d", *((int *)b));

	char c[101] = {{0}};
	char d[101] = {{0}};
	strcat(c, e);
	strcat(c, f);

	strcat(d, f);
	strcat(d, e);

	return strcmp(c, d);
}

char* minNumber(int* nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(int), cmp_str);
	char *ret = (char *)calloc(1024 * 100, sizeof(char));
	for (int i = 0; i < numsSize; i++) {
		char tmpstr[101];
		memset(tmpstr, 0, sizeof(tmpstr));
		sprintf(tmpstr, "%d", nums[i]);
		strcat(ret, tmpstr);
	}

	return ret;
}

/*
31. ��һ������
�Ѷ��е�461
ʵ�ֻ�ȡ��һ�����еĺ������㷨��Ҫ���������������������г��ֵ�������һ����������С�
�����������һ����������У��������������г���С�����У����������У���
����ԭ���޸ģ�ֻ����ʹ�ö��ⳣ���ռ䡣
������һЩ���ӣ�����λ������У�����Ӧ���λ���Ҳ��С�
1,2,3 �� 1,3,2
3,2,1 �� 1,2,3
1,1,5 �� 1,5,1
*/
/*
1���Ӻ���ǰ�������ҵ���һ��nums[i] < nums[i + 1]����λ��i;
2��ͨ������1֪��i�Ժ��λ�ö��ǵ����ݼ��ģ���˺����������ҵ���һ�������������λ��Ϊj��
3������λ��i��λ��j�������������
4����i+1λ�ÿ�ʼ������������յ����������յĽ������Ҫ�ҵ�����һ���ȵ�ǰ���������

���������ҵ��� 1 ���������� a[i]>a[i+1]
�� a[i] �Ҳ���������ҵ��� 1 ������ a[i] ������������ a[i] ����ֵ��(������������Ϊ������һ��֮����������������������������ҵ��ұ߱� a[i] ���ҽӽ� a[i] ����)
����ֵ�󣬶� a[i] �ұߵ�ֵ�������򣬱�֤��˳��ֵ��С��

*/

static int comp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void nextPermutation(int* nums, int numsSize){
    if (NULL == nums || 0 == numsSize)
    {
        return;
    }

    int left = numsSize - 2; // �ӵ����ڶ�����ʼ
    int right;
    int temp = 0;

    while (left >= 0 && nums[left] >= nums[left + 1])
    {
        left--;
    }

    if (-1 == left) // ����������������
    {
        return qsort(nums, numsSize, sizeof(int), comp);
    }

    for (right = left + 1; right <= numsSize - 1 && nums[left] < nums[right]; right++);

    temp = nums[left];
    nums[left] = nums[right - 1];
    nums[right - 1] = temp;

    qsort(nums + left + 1, numsSize - 1 - left, sizeof(int), comp);
}

/*
539. ��Сʱ���
����һ�� 24 Сʱ�ƣ�Сʱ:���ӣ���ʱ���б��ҳ��б�����������ʱ�����Сʱ���Է�������ʾ��


ʾ�� 1��

����: ["23:59","00:00"]
���: 1

��ע:

�б���ʱ������ 2~20000 ֮�䡣
*/
int str2min(char * str)
{
	int hour;
	int min;
	sscanf(str, "%d:%d", &hour, &min);
	return hour * 60 + min;
}

int findMinDifference(char ** timePoints, int timePointsSize)
{
	int mins[timePointsSize];
	for (int i = 0; i < timePointsSize; i++) {
		mins[i] = str2min(timePoints[i]);
	}

	qsort(mins, timePointsSize, sizeof(mins[0]), cmp_int);
	int ret = 1440;
	for (int i = 1; i < timePointsSize; i++) {
		ret = fmin(ret, mins[i] - mins[i - 1]);
	}

	ret = fmin(ret, mins[0] + 1440 - mins[timePointsSize - 1]);

	return ret;
}


