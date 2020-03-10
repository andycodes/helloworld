#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
qsort����������<stdlib.h>��ͷ�ļ��

qsort�����������£�
void qsort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));

����˵�����£�
base: Ҫ���������
nmemb: �����е�Ԫ����Ŀ
size: ÿ������Ԫ��ռ���ڴ�ռ䣬��ʹ��sizeof���
compar: �Ƚ���������Ԫ�صıȽϺ�����
���ȽϺ�����
��һ������ֵС�ڡ����ڡ����ڵڶ�����ֵʱ��
���ȽϺ����ķ���ֵӦ�ֱ�С�ڡ����ڡ������㡣

Ҳ��˵��Ҫʵ��һ�������ĺ��������򣩣�
int cmp(const void *a, const void *b)
���a > b������>0
���a == b, ����0
���a < b������<0
�����a��b�Ĺ�ϵ�������߼��ϵģ�������ֵ�Ƚϣ���������Ŀ��Բ����������֣����������ַ���


< ���������ǲ��õĴ�С��������>
һ����int������������
*/

int cmp_int ( const void *a , const void *b){
        return *(int *)a - *(int *)b;
}

void qsort_int_test(void)
{
	int num[100];
	for(int i =0;i < 100;i++){
		num[i] = 100 -i;
	}

	qsort(num,sizeof(num)/sizeof(num[0]),sizeof(num[0]),cmp_int);

	for(int i =0;i < 100;i++){
		printf("%d \n",num[i]);
	}
}


int comp_array(const void *a,const void *b)
{
	if (((int *)a)[0] != ((int *)b)[0]) {
		return ((int *)a)[0]-((int *)b)[0];//first cow
	} else {
		return ((int *)a)[1]-((int *)b)[1];//Second column
	}
}


void qsort_array_test(void)
{
	int a[100][2];
	for(int i =0;i < 50; i++){
		a[i][0] = 100 -i;
		a[i][1] = 200 -i;
	}

	for(int i = 50;i < 100; i++){
		a[i][0] = 100;
		a[i][1] = 200 -i;
	}

	qsort(a,100,sizeof(int)*2,comp_array);

	for(int i =0;i < 100;i++){
		printf("%d %d\n",a[i][0],a[i][1]);
	}
}


int cmp_point_array(const void *a,const void *b)
{
    int *ap = *(int **)a;
    int *bp = *(int **)b;

    if(ap[0] == bp[0])
        return ap[1] - bp[1];
    else
        return ap[0] - bp[0];
}


void qsort_point_array(void)
{
	int **a = (int **)malloc(100 * sizeof(int *));
	for (int i = 0; i < 100; i++) {
		a[i] = malloc(2 * sizeof(int));

		a[i][0] = rand()%100;
		a[i][1] = rand()%100;
	}

	qsort(a, 100, sizeof(a[0]), cmp_point_array);

	for (int i = 0; i < 100; i++) {
		printf("%d %d\n", a[i][0], a[i][1]);
	}

	//free
}

/*
������char������������ͬint���ͣ�

char word[100];
Sample:
int cmp( const void *a , const void *b){
        return *(char *)a - *(char *)b;
}
qsort(word,100,sizeof(word[0]),cmp);

*/
int cmp_char( const void *a , const void *b){
        return *(char *)a - *(char *)b;
}

void qsort_char_test(void)
{
	char word[100];
	for(int i =0;i < 100;i++){
		word[i] = 100 -i;
	}
	qsort(word,100,sizeof(word[0]),cmp_char);
	for(int i =0;i < 100;i++){
		printf("%d \n",word[i]);
	}
}


/*������double�������������ر�Ҫע�⣩*/
int cmp_double( const void *a , const void *b){
        return *(double *)a > *(double *)b ? 1 : -1;
}

void qsort_double_test(void)
{
	double num[100];
	for(int i =0;i < 100;i++){
		num[i] = 100.5 -i;
	}
	qsort(num,100,sizeof(num[0]),cmp_double);
	for(int i =0;i < 100;i++){
		printf("%f \n",num[i]);
	}
}


struct St{
int x;
int y;
}ss[100];

int cmp_struct( const void *a , const void *b){
	struct St *c = (struct St *)a;
	struct St *d = (struct St *)b;

//����x��С�������򣬵�x���ʱ����y�Ӵ�С����
	if(c->x != d->x)
		return c->x - d->x;
	else
		return d->y - c->y;
}


void qsort_struct_test(void)
{
	for(int i =0;i < 50;i++){
		ss[i].x = 100 -i;
		ss[i].y = 200 -i;
	}

	for(int i =50;i < 100;i++){
		ss[i].x = 100;
		ss[i].y = 200 -i;
	}

	qsort(ss,100,sizeof(ss[0]),cmp_struct);
	for(int i =0;i < 100;i++){
		printf("%d %d \n",ss[i].x,ss[i].y);
	}
}


/*
�������ַ�����������
struct In{
int data;
char str[100];
}s[100];

//���սṹ�����ַ���str���ֵ�˳������

int cmp ( const void *a , const void *b){
        return strcmp( (*(In *)a).str , (*(In *)b).str);
}
qsort(s,100,sizeof(s[0]),cmp);
*/
struct Str{
	int data;
	char str[1024];
}str[5];

int cmp_str ( const void *a , const void *b){
        return strcmp( (*(struct Str *)a).str , (*(struct Str *)b).str);
}

void qsort_string_test(void)
{
	strcpy(str[0].str , "aa");
	strcpy(str[1].str , "bb");
	strcpy(str[2].str , "gg");
	strcpy(str[3].str , "dd");
	strcpy(str[4].str , "ee");

	qsort(str,5,sizeof(str[0]),cmp_str);
	for(int i =0;i < 5;i++){
		printf("%s \n",str[i].str);
	}
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("argc err\n");
		return -1;
	}

	switch(atoi(argv[1])) {
	case 1:
		qsort_struct_test();
	break;
	case 2:
		qsort_array_test();
	break;
	case 3:
		qsort_point_array();
	break;
	case 4:
	default:
	break;
	}

	return 0;
}


