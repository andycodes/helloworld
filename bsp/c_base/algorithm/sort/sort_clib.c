#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
qsort函数包含在<stdlib.h>的头文件里。

qsort函数声明如下：
void qsort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));

参数说明如下：
base: 要排序的数组
nmemb: 数组中的元素数目
size: 每个数组元素占用内存空间，可使用sizeof获得
compar: 比较两个数组元素的比较函数。
本比较函数的
第一个参数值小于、等于、大于第二参数值时，
本比较函数的返回值应分别小于、等于、大于零。

也就说你要实现一个这样的函数（升序）：
int cmp(const void *a, const void *b)
如果a > b，返回>0
如果a == b, 返回0
如果a < b，返回<0
这里的a和b的关系仅仅是逻辑上的，并不是值比较，所以排序的可以不仅仅是数字，还可以是字符。


< 以下排序都是采用的从小到大排序>
一、对int类型数组排序
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
	qsort(num,100,sizeof(num[0]),cmp_int);
	for(int i =0;i < 100;i++){
		printf("%d \n",num[i]);
	}
}


/*对一个二维数组的进行排序：*/
int comp_array(const void *a,const void *b){
     return ((int *)a)[0]-((int *)b)[0];
}


void qsort_array_test(void)
{
	int a[100][2];
	for(int i =0;i < 100;i++){
		a[i][0] = 100 -i;
		a[i][1] = 200 -i;
	}
	qsort(a,100,sizeof(int)*2,comp_array);
	for(int i =0;i < 100;i++){
		printf("%d %d\n",a[i][0],a[i][1]);
	}
}



/*
二、对char类型数组排序（同int类型）

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


/*三、对double类型数组排序（特别要注意）*/
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


/*

四、对结构体一级排序
struct In{
double data;
int other;
}s[100]

//按照data的值从小到大将结构体排序,关于结构体内的排序关键数据data的类型可以很多种，参考上面的例子写

int cmp( const void *a ,const void *b){
        return (*(In *)a).data > (*(In *)b).data ? 1 : -1;
}
qsort(s,100,sizeof(s[0]),cmp);
*/
struct In{
double data;
int other;
}s[100];

int cmp_struct( const void *a ,const void *b){
        return (*(struct In *)a).data > (*(struct In *)b).data ? 1 : -1;
}


void qsort_struct_test(void)
{
	for(int i =0;i < 100;i++){
		s[i].data = 100.5 -i;
	}
	qsort(s,100,sizeof(s[0]),cmp_struct);
	for(int i =0;i < 100;i++){
		printf("%f \n",s[i].data);
	}
}


/*
五、对结构体二级排序
struct In{
int x;
int y;
}s[100];

//按照x从小到大排序，当x相等时按照y从大到小排序

int cmp( const void *a , const void *b){
struct In *c = (In *)a;
struct In *d = (In *)b;
if(c->x != d->x) return c->x - d->x;
else return d->y - c->y;
}
qsort(s,100,sizeof(s[0]),cmp);
*/
struct St{
int x;
int y;
}ss[100];

int cmp_strcut2( const void *a , const void *b){
	struct St *c = (struct St *)a;
	struct St *d = (struct St *)b;
	if(c->x != d->x)
		return c->x - d->x;
	else
		return d->y - c->y;
}


void qsort_struct2_test(void)
{
	for(int i =0;i < 50;i++){
		ss[i].x = 100 -i;
		ss[i].y = 200 -i;
	}

	for(int i =50;i < 100;i++){
		ss[i].x = 100;
		ss[i].y = 200 -i;
	}

	qsort(ss,100,sizeof(ss[0]),cmp_strcut2);
	for(int i =0;i < 100;i++){
		printf("%d %d \n",ss[i].x,ss[i].y);
	}
}


/*
六、对字符串进行排序
struct In{
int data;
char str[100];
}s[100];

//按照结构体中字符串str的字典顺序排序

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

	qsort(str,5,sizeof(s[0]),cmp_str);
	for(int i =0;i < 5;i++){
		printf("%s \n",str[i].str);
	}
}


int main()
{
	//qsort_int_test();
	//qsort_array_test();
	//qsort_char_test();
	//qsort_double_test();
	//qsort_struct_test();
	//qsort_struct2_test();
	qsort_string_test();
}

