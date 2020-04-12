
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