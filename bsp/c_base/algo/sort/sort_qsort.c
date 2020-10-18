#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_int ( const void *a , const void *b)
{
        return *(int *)a > *(int *)b; //*(int *)a - *(int *)b;
}
int cmp_char( const void *a , const void *b)
{
        return *(char *)a > *(char *)b;
}
int cmp_double( const void *a , const void *b){
        return *(double *)a > *(double *)b ? 1 : -1;
}
//qsort(num,sizeof(num)/sizeof(num[0]),sizeof(num[0]),cmp_int);

/*int a[100][2];*/
int comp_array(const void *a,const void *b)
{
	if (((int *)a)[0] != ((int *)b)[0]) {
		return ((int *)a)[0]-((int *)b)[0];//first cow
	} else {
		return ((int *)a)[1]-((int *)b)[1];//Second column
	}
}

/*int **a = (int **)malloc(100 * sizeof(int *));*/
int cmp_point_array(const void *a,const void *b)
{
    int *ap = *(int **)a;
    int *bp = *(int **)b;

    if(ap[0] == bp[0])
        return ap[1] - bp[1];
    else
        return ap[0] - bp[0];
}

//["w","wo","wor","worl", "world"]
int cmp_str(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

