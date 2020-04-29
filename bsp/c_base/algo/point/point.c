#include<stdio.h>
#include<stdlib.h>



/*
����ָ������ö����������ָ�������õĶ���
�����ðѶ�������Ϊȫ�ֿɷ��ʣ�
Ҫ��ĳ���������޸����ݣ�
��Ҫ��ָ�봫�����ݣ�����������Ҫ�޸� ��ָ���ʱ��
��Ҫ����ָ���ָ�룬���ݲ���������ָ�룩��ʱ��
���ݵ������ǵ�ֵ��Ҳ����˵��
���ݸ��������ǲ���ֵ��һ������
*/

#include<stdio.h>

int test_point_swap()
{
    int m, n;
    m = 5;
    n = 10;
    printf("m=%d, n=%d\n",m, n);
    swap(&m, &n);
    printf("m=%d, n=%d\n",m, n);
    return 0;
}

/*
����ָ������ָ��
����ָ������ָ����C�г��õļ�����Ч�ʺܸߣ�
��Ϊ����ĳ������¸��ƴ����ڴ棬
�����ϣ�����ݱ��޸ģ���Ҫ����ָ������ָ��
���ǲ����޸�ͨ��ָ������ָ�봫������ֵ
*/

#include<stdio.h>
void passconstant(const int* num1, int*num2)
{
    *num2 = *num1;
}
int test_const_data_point()
{
    const int a = 100;
    int b = 5;
    printf("a=%d, b=%d\n",a, b);
    passconstant(&a, &b);
    printf("a=%d, b=%d\n",a, b);
    return 0;
}
/*
#include<stdio.h>
void passconstant1(const int* num1, int* num2)
{
    *num1 = 100;
    *num2 = 200;
}
int test_const_data_point_err()
{
    const int limit = 100;
    passconstant1(&limit, &limit);
    return 0;
}
*/

/*
����ָ��
int **p;

����ָ��һ���õĳ��ϣ�

(1)����ָ��ָ��һ��ָ��ĵ�ַ��

(2)����ָ��ָ��ָ������ĵ�ַ��

(3)ʵ���ж���ָ���õñȽ��٣�
��������Ǻ�ָ������һ���õġ�

(4)ʵ�ʱ��ʱ��ʱ�ں�������ʱ��
Ϊ��ͨ�������ڲ��ı��ⲿ��ָ�������ͨ���ö���ָ�롣

*/


void allocateArray(int **arr, int size, int value)
{
//arr ��ָ��ָ���ָ��
//*arr ��int���͵�ָ��
    *arr = (int*)malloc(size * sizeof(int));
    if(arr != NULL) {
        for(int i = 0; i < size; i++) {
            *(*arr + i) = value;
        }
    }
}

int test_double_point_pass_fun(void)
{
    int* vector = NULL;
    allocateArray(&vector, 5, 45);
    for(int i = 0; i < 5; i++) {
        printf("%d\n", vector[i]);
    }
    free(vector);
    return 0;
}

void test_double_point()
{
	int i;
	int b[5] = {1,2,3,4,5};
	//ָ��������������Ƕ���ָ��
	char *c[5] = {"abc","efg","hij","lmn","opg"};
	char **d;
	d = c;

	for (i = 0; i < 5; i++){
		printf("i num is %s\n", *(d+i));
	}

	int *p;
	p = b;
	printf("p = %p\n",p);

	int (*p1)[5];
	p1 = &b;
	printf("p1 = %p\n",p1);
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("argc err\n");
		return -1;
	}

	switch(atoi(argv[1])) {
	case 1:
		test_point_swap();
	break;
	case 2:
		test_const_data_point();
	case 3:
		test_double_point_pass_fun();
	break;
	case 4:
		test_double_point();
	break;
	default:
	break;
	}

	return 0;
}


/*
11. ʢ���ˮ������
���� n ���Ǹ����� a1��a2��...��an��ÿ��������������
��һ���� (i, ai) ���������ڻ� n ����ֱ�ߣ�
��ֱ�� i �������˵�ֱ�Ϊ (i, ai) �� (i, 0)���ҳ����е������ߣ�
ʹ�������� x �Ṳͬ���ɵ�����������������ˮ��

˵�����㲻����б�������� n ��ֵ����Ϊ 2��

*/
int maxArea(int* height, int heightSize){
	if (height == NULL || heightSize <= 0) {
		return 0;
	}

	int area = INT_MIN;
	for(int i = 1; i < heightSize; i++) {
		for (int j = 0; j < i; j++) {
			area = fmax(area, fmin(height[i], height[j]) * (i - j));
		}
	}

	return area;
}
/*
˫ָ�뷨
������ǿ���������Χ�����߶ι��ɵ�����
���ڣ�Ϊ��ʹ�����󻯣�
������Ҫ���Ǹ����������߶�֮�������
���������ͼ��ָ��ϳ��߶ε�ָ�����ڲ��ƶ���
�������������������ڽ϶̵��߶ζ��������κ����ӡ�
���ǣ���ͬ���������£�
�ƶ�ָ��϶��߶ε�ָ�뾡������˾��ο�ȵļ�С��
��ȴ���ܻ������������������Ϊ�ƶ��϶��߶ε�
ָ���õ�һ����Խϳ����߶Σ�
����Կ˷��ɿ�ȼ�С������������С��
*/
int maxArea(int* height, int heightSize){
	if (height == NULL || heightSize <= 0) {
		return 0;
	}

	int area = INT_MIN;
	int l = 0, r = heightSize - 1;
        while (l < r) {
            area = fmax(area, fmin(height[l], height[r]) * (r - l));
            if (height[l] < height[r])
                l++;
            else
                r--;
        }
        return area;
}

/*
������ 17.11. ���ʾ���
�Ѷ��е�2
�и��ں����ʵĳ����ı��ļ������������������ʣ��ҳ�������ļ������������ʵ���̾���(���������)�����Ѱ�ҹ���������ļ��л��ظ���Σ���ÿ��Ѱ�ҵĵ��ʲ�ͬ�����ܶԴ��Ż���?
ʾ����
���룺words = ["I","am","a","student","from","a","university","in","a","city"], word1 = "a", word2 = "student"
�����1

*/

int findClosest(char** words, int wordsSize, char* word1, char* word2)
{
	int min = INT_MAX;
	int w1Idx = -1;
	int w2Idx = -2;
	for (int i = 0; i < wordsSize; i++) {
		if (strcmp(words[i], word1) == 0) {
			w1Idx = i;
		}

		if (strcmp(words[i], word2) == 0) {
			w2Idx = i;
		}

		if (w1Idx >= 0 && w2Idx >= 0) {
			min = fmin(min, abs(w1Idx - w2Idx));
		}

	}

	return min;
}

/*
see hashmap
*/
struct it{
	int num;
	int idx;
};

int cmp_struct(const int *a, const int *b)
{
	struct it * c = (struct it *)a;
	struct it * d = (struct it *)b;
	return c->num - d->num;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	int* res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	struct it obj[numsSize];
	for (int i = 0; i < numsSize; i++) {
		obj[i].num = nums[i];
		obj[i].idx = i;
	}

	qsort(obj, numsSize, sizeof(obj[0]), cmp_struct);
	int left = 0;
	int right = numsSize -1;
	int sum;
	while(1) {
		sum = obj[left].num + obj[right].num;
		if (sum > target) {
			right--;
		}else if(sum < target) {
			left++;
		}else {
			break;
		}
	}

	res[0] = obj[left].idx;
	res[1] = obj[right].idx;
	return res;
}

/*
18. ����֮��
����һ������ n ������������ nums ��һ��Ŀ��ֵ target���ж� nums ���Ƿ�����ĸ�Ԫ�� a��b��c �� d ��ʹ�� a + b + c + d ��ֵ�� target ��ȣ��ҳ��������������Ҳ��ظ�����Ԫ�顣

ע�⣺

���в����԰����ظ�����Ԫ�顣

ʾ����

�������� nums = [1, 0, -1, 0, -2, 2]���� target = 0��

����Ҫ�����Ԫ�鼯��Ϊ��
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/


int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){

	int **ret = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	for (int a = 0; a < numsSize - 3; a++) {
		if(a > 0 && nums[a] == nums[a - 1])
			continue;

		if(nums[a]+nums[a+1]+nums[a+2]+nums[a+3]>target) break;
		if(nums[a]+nums[numsSize-3]+nums[numsSize-2]+nums[numsSize-1]<target) continue;
		for (int b = a + 1; b < numsSize - 2; b++) {
			if(nums[a]+nums[b]+nums[b+1]+nums[b+2]>target) break;
			 if(nums[a]+nums[b]+nums[numsSize-2]+nums[numsSize-1]<target) continue;
			if(b > a + 1 && nums[b] == nums[b -1])
				continue;

			int c = b + 1;
			int d = numsSize - 1;

			while(c < d) {
				int sum = nums[a] + nums[b] + nums[c] + nums[d];
				if (sum < target) {
					c++;
				} else if (sum > target) {
					d--;
				} else {
					ret[*returnSize] = (int *)calloc(4, sizeof(int));
					ret[*returnSize][0] = nums[a];
					ret[*returnSize][1] = nums[b];
					ret[*returnSize][2] = nums[c];
					ret[*returnSize][3] = nums[d];
					(*returnColumnSizes)[*returnSize] = 4;
					(*returnSize)++;
					while(c<d&&nums[c+1]==nums[c])
	        				    c++;
	        			while(c<d&&nums[d-1]==nums[d])
	        				    d--;

					c++;
					d--;
				}
			}
		}
	}

	return ret;
}

