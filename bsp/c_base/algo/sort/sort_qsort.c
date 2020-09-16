#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_int ( const void *a , const void *b)
{
        return *(int *)a > *(int *)b;
}
int cmp_char( const void *a , const void *b)
{
        return *(char *)a > *(char *)b;
}
int cmp_double( const void *a , const void *b){
        return *(double *)a > *(double *)b ? 1 : -1;
}
//qsort(num,sizeof(num)/sizeof(num[0]),sizeof(num[0]),cmp_int);

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
}


struct St{
int x;
int y;
}ss[100];

int cmp_struct( const void *a , const void *b){
	struct St *c = (struct St *)a;
	struct St *d = (struct St *)b;

//按照x从小到大排序，当x相等时按照y从大到小排序
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

//["w","wo","wor","worl", "world"]
int cmp_str(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}
