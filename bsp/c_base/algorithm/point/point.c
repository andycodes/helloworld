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

