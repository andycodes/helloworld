#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** 数组元素的类型*/
typedef int elem_t;
/**
* @brief 有序顺序表的折半查找算法.
**
@param[in] a 存放数据元素的数组，已排好序
* @param[in] n 数组的元素个数
* @param[in] x 要查找的元素
* @return 如果找到x，则返回其下标。如果找
* 不到x 且x 小于array 中的一个或多个元素，则为一个负数，该负数是大
* 于x 的第一个元素的索引的按位求补。如果找不到x 且x 大于array 中的
* 任何元素，则为一个负数，该负数是（最后一个元素的索引加1）的按位求补。
*/
int binary_search(const elem_t a[], const int n, const elem_t x) {
    int left = 0, right = n -1, mid;
    while(left <= right) {
        mid = left + (right - left) / 2;
        if(x > a[mid]) {
            left = mid + 1;
        } else if(x < a[mid]) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -(left+1);
}


int binary_find_recur(int a[],int key,int start,int end)
{
	int middle=(start+end)/2;
	if(a[middle]==key)
		return middle;
	if(start==middle)
		return -1;
        if(key<a[middle])
		binary_find_recur(a,key,start,middle);
	else
		binary_find_recur(a,key,middle,end);
}


int test_binary_find_recur()
{
    int a[]={1,2,3,4,5,6,7,8,9,10};
    printf("%d\n",binary_find_recur(a,10,0,10));
}


/*bseach用法:
void *bsearch(const void *key, const void *base,
size_t nelem, size_t width, int(*fcmp)(const void *, const *));
参数：
key指向所要查找的元素.
第一个找的关键字。
第二个：要查找的数组。
第三个：指定数组中元素的数目。
第四个：每个元素的长度（以字符为单位）。
第五个：指向比较函数的指针.
*/
#define LEN 5
void arr_init(int num[], int len)
{
	int i;

	srand(time(NULL));
	for(i = 0; i < len; i++){
		num[i] = rand()%50;
	}

}

void arr_print(int num[], int len)
{
	int i;

	for(i = 0; i < len; i++){
		printf("%d ", num[i]);
	}
	printf("\n");

}


void test_bsearch(void)
{
	int num[LEN];
	int fd;
	int *find_num;

	arr_init(num, LEN);
	arr_print(num, LEN);
	qsort(num, LEN, sizeof(int), cmp_int);
	arr_print(num, LEN);
	printf("enter search num:\n");
	scanf("%d", &fd);
	find_num = bsearch(&fd, num, LEN, sizeof(int), cmp_int);
	(find_num == NULL) ? printf("no find\n") : printf("find the num %d\n", fd);
}

/*
1011. 在 D 天内送达包裹的能力
难度中等75
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。

示例 1：
输入：weights = [1,2,3,4,5,6,7,8,9,10], D = 5
输出：15
解释：
船舶最低载重 15 就能够在 5 天内送达所有包裹，如下所示：
第 1 天：1, 2, 3, 4, 5
第 2 天：6, 7
第 3 天：8
第 4 天：9
第 5 天：10

请注意，货物必须按照给定的顺序装运，因此使用载重能力为 14 的船舶并将包装分成 (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) 是不允许的。

*/
/*
 //1.最低运载能力必然大于等于序列中的最大值；结果落在[max(weights), sum(weights)]        //2.要注意是在D天“内”完成，所以运载能力要尽量小，只要是在D天之内就可以作者：luke-9r链接：https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/solution/c-er-fen-cha-zhao-jian-dan-shi-xian-dai-ma-by-luke/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
对于一艘承载力为K船来说，我们必然会在不超过其承载力的前提下贪心地往上装载货物，这样才能使得运送包裹所花费的时间最短。
如果船在承载力为K的条件下可以完成在D天内送达包裹的任务，那么任何承载力大于K的条件下依然也能完成任务。
我们可以让这个承载力K从max(weights)max(weights)开始（即所有包裹中质量最大包裹的重量，低于这个重量我们不可能完成任务），逐渐增大承载力K，直到K可以让我们在D天内送达包裹。此时K即为我们所要求的最低承载力。
逐渐增大承载力K的方法效率过低，让我们用二分查找的方法来优化它。


*/

bool canShip(int* weights, int weightsSize, int D, int shipCapacity)
{
	int cur = shipCapacity ;
	for(int i = 0; i < weightsSize; i++) {
		if (weights[i] > shipCapacity )
			return false;
		if (cur < weights[i]) {
			cur = shipCapacity ;
			D--;
		}
		cur -= weights[i];
	}
	return D > 0;
}

int shipWithinDays(int* weights, int weightsSize, int D)
{
	int left = 0;
	int right = 0;

	for(int i = 0; i < weightsSize; i++) {
		left = fmax(left, weights[i]);
		right += weights[i];
	}

	while(left < right) {
		int mid = (right + left) / 2;
		if (canShip(weights, weightsSize, D, mid)) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	return left;
}


