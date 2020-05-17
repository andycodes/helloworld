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

