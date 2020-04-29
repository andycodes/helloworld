#include<stdio.h>
#include<stdlib.h>



/*
传递指针可以让多个函数访问指针所引用的对象，
而不用把对象声明为全局可访问，
要在某个函数中修改数据，
需要用指针传递数据，当数据是需要修改 的指针的时候，
就要传递指针的指针，传递参数（包括指针）的时候，
传递的是它们的值，也就是说，
传递给函数的是参数值的一个副本
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
传递指向常量的指针
传递指向常量的指针是C中常用的技术，效率很高，
因为避免某种情况下复制大量内存，
如果不希望数据被修改，就要传递指向常量的指针
我们不能修改通过指向常量的指针传进来的值
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
二重指针
int **p;

二重指针一般用的场合：

(1)二重指针指向一重指针的地址。

(2)二重指针指向指针数组的地址。

(3)实践中二重指针用得比较少，
大多数都是和指针数组一起用的。

(4)实际编程时有时在函数传参时，
为了通过函数内部改变外部的指针变量，通常用二重指针。

*/


void allocateArray(int **arr, int size, int value)
{
//arr 是指向指针的指针
//*arr 是int类型的指针
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
	//指针数组的数组名是二重指针
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
11. 盛最多水的容器
给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中
的一个点 (i, ai) 。在坐标内画 n 条垂直线，
垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，
使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器，且 n 的值至少为 2。

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
双指针法
最初我们考虑由最外围两条线段构成的区域。
现在，为了使面积最大化，
我们需要考虑更长的两条线段之间的区域。
如果我们试图将指向较长线段的指针向内侧移动，
矩形区域的面积将受限于较短的线段而不会获得任何增加。
但是，在同样的条件下，
移动指向较短线段的指针尽管造成了矩形宽度的减小，
但却可能会有助于面积的增大。因为移动较短线段的
指针会得到一条相对较长的线段，
这可以克服由宽度减小而引起的面积减小。
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
面试题 17.11. 单词距离
难度中等2
有个内含单词的超大文本文件，给定任意两个单词，找出在这个文件中这两个单词的最短距离(相隔单词数)。如果寻找过程在这个文件中会重复多次，而每次寻找的单词不同，你能对此优化吗?
示例：
输入：words = ["I","am","a","student","from","a","university","in","a","city"], word1 = "a", word2 = "student"
输出：1

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
18. 四数之和
给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：

答案中不可以包含重复的四元组。

示例：

给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

满足要求的四元组集合为：
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

