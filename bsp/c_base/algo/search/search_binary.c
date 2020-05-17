#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** ����Ԫ�ص�����*/
typedef int elem_t;
/**
* @brief ����˳�����۰�����㷨.
**
@param[in] a �������Ԫ�ص����飬���ź���
* @param[in] n �����Ԫ�ظ���
* @param[in] x Ҫ���ҵ�Ԫ��
* @return ����ҵ�x���򷵻����±ꡣ�����
* ����x ��x С��array �е�һ������Ԫ�أ���Ϊһ���������ø����Ǵ�
* ��x �ĵ�һ��Ԫ�ص������İ�λ�󲹡�����Ҳ���x ��x ����array �е�
* �κ�Ԫ�أ���Ϊһ���������ø����ǣ����һ��Ԫ�ص�������1���İ�λ�󲹡�
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


/*bseach�÷�:
void *bsearch(const void *key, const void *base,
size_t nelem, size_t width, int(*fcmp)(const void *, const *));
������
keyָ����Ҫ���ҵ�Ԫ��.
��һ���ҵĹؼ��֡�
�ڶ�����Ҫ���ҵ����顣
��������ָ��������Ԫ�ص���Ŀ��
���ĸ���ÿ��Ԫ�صĳ��ȣ����ַ�Ϊ��λ����
�������ָ��ȽϺ�����ָ��.
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

