#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
ÎÒÃÇÕâÑùÀ´¿´Õâ¸öÎÊÌâ£¬
¹«Ë¾Ê×ÏÈ½«Õâ 2N ¸öÈËÈ«¶¼°²ÅÅ·ÉÍù B ÊĞ£¬
ÔÙÑ¡³ö N ¸öÈË¸Ä±äËüÃÇµÄĞĞ³Ì£¬ÈÃËûÃÇ·ÉÍù A ÊĞ¡£
Èç¹ûÑ¡Ôñ¸Ä±äÒ»¸öÈËµÄĞĞ³Ì£¬
ÄÇÃ´¹«Ë¾½«»á¶îÍâ¸¶³ö price_A - price_B µÄ·ÑÓÃ£¬
Õâ¸ö·ÑÓÃ¿ÉÕı¿É¸º¡£


Òò´Ë×îÓÅµÄ·½°¸ÊÇ£¬Ñ¡³ö price_A - price_B ×îĞ¡µÄ N ¸öÈË£¬
ÈÃËûÃÇ·ÉÍù A ÊĞ£¬ÆäÓàÈË·ÉÍù B ÊĞ¡£
Ëã·¨°´ÕÕ price_A - price_B ´ÓĞ¡µ½´óÅÅĞò£»
½«Ç° N ¸öÈË·ÉÍù A ÊĞ£¬ÆäÓàÈË·ÉÍù B ÊĞ£¬
²¢¼ÆËã³ö×Ü·ÑÓÃ¡£
*/

struct obj{
    int a;
    int b;
    int diff;
};

void bubble_sort(struct obj  *data,int size)
{
    for (int i=size;i>0;i--)
    {
        for (int j=0;j<(i-1);j++)
            {
                if (data[j].diff >data[j+1].diff)
                    {
                        struct obj  tmp;
                        tmp=data[j];
                        data[j]=data[j+1];
                        data[j+1]=tmp;
                    }
            }
       }
}



int twoCitySchedCost(int costs[][2], int costsSize, int* costsColSize){
        int i;
        struct obj ob[100];
        int sum = 0;

        for(i = 0; i < costsSize; i++){
                ob[i].a = costs[i][0];
                ob[i].b = costs[i][1];
                ob[i].diff = ob[i].a - ob[i].b;
        }

        bubble_sort(ob,costsSize);

        for (i = 0;i<costsSize/2;i++){
            sum += ob[i].a;
        }

        for (i = costsSize/2;i<costsSize;i++){
            sum += ob[i].b;
        }

        return sum;
}


int main()
{
    int a[][2] = {{259,770},{448,54},{926,667},{184,139},{840,118},{577,469}};
    int b;
    printf("%d\n",twoCitySchedCost(a,6,&b));
    return 0;
}


/*
½âÌâË¼Â·£º ¹ÉÆ±ÂòÂô²ßÂÔ£º
µ¥¶À½»Ò×ÈÕ£ºÉè½ñÌì¼Û¸ñ p1¡¢Ã÷Ìì¼Û¸ñ p2£¬Ôò½ñÌìÂòÈë¡¢
Ã÷ÌìÂô³ö¿É×¬È¡½ğ¶î p2-p1£¨¸ºÖµ´ú±í¿÷Ëğ£©¡£
Á¬ĞøÉÏÕÇ½»Ò×ÈÕ£º Éè´ËÉÏÕÇ½»Ò×ÈÕ¹ÉÆ±¼Û¸ñ·Ö±ğÎª
p1,p2,.....pn£¬ÔòµÚÒ»ÌìÂò×îºóÒ»ÌìÂôÊÕÒæ×î´ó£¬¼
pn-p1£»µÈ¼ÛÓÚÃ¿Ìì¶¼ÂòÂô£¬¼
pn-p1=(p2-p1)+(p3-p2)+(p4-p3)+....+(pn-P(n-1))¡£
Á¬ĞøÏÂ½µ½»Ò×ÈÕ£º Ôò²»ÂòÂôÊÕÒæ×î´ó£¬¼´²»»á¿÷Ç®¡£
Ëã·¨Á÷³Ì£º  ±éÀúÕû¸ö¹ÉÆ±½»Ò×ÈÕ¼Û¸ñÁĞ±í price£¬
²ßÂÔÊÇËùÓĞÉÏÕÇ½»Ò×ÈÕ¶¼ÂòÂô£¨×¬µ½ËùÓĞÀûÈó£©£¬
ËùÓĞÏÂ½µ½»Ò×ÈÕ¶¼²»ÂòÂô£¨ÓÀ²»¿÷Ç®£©¡£
Éè tmp ÎªµÚ i-1 ÈÕÂòÈëÓëµÚ i ÈÕÂô³ö×¬È¡µÄÀûÈó£¬
¼´ tmp = prices[i] - prices[i - 1] £» µ±¸ÃÌìÀûÈóÎªÕı tmp > 0£¬
Ôò½«ÀûÈó¼ÓÈë×ÜÀûÈó profit£»µ±ÀûÈóÎª 00 »òÎª¸º£¬
ÔòÖ±½ÓÌø¹ı£» ±éÀúÍê³Éºó£¬·µ»Ø×ÜÀûÈó profit¡£

*/
int maxProfit(int* prices, int pricesSize){
        int profit = 0;
        for (int i = 1; i <pricesSize; i++) {
            int tmp = prices[i] - prices[i - 1];
            if (tmp > 0) profit += tmp;
        }
        return profit;
}


/*
ÔÚÒ»¸ö¡¸Æ½ºâ×Ö·û´®¡¹ÖĞ£¬'L' ºÍ 'R' ×Ö·ûµÄÊıÁ¿ÊÇÏàÍ¬µÄ¡£

¸ø³öÒ»¸öÆ½ºâ×Ö·û´® s£¬ÇëÄã½«Ëü·Ö¸î³É¾¡¿ÉÄÜ¶àµÄÆ½ºâ×Ö·û´®¡£

·µ»Ø¿ÉÒÔÍ¨¹ı·Ö¸îµÃµ½µÄÆ½ºâ×Ö·û´®µÄ×î´óÊıÁ¿¡£

ÎÊÌâ·ÖÎö£º·Ö¸îÆ½ºâ´®£¬µÃµ½¾¡¿ÉÄÜ¶àµÄÆ½ºâ´®¡£ÕâÊÇÒ»¸öÊÊÓÃÌ°ĞÄËã·¨µÄÎÊÌâ£¬ÔÚÊÊµ±µÄÎ»ÖÃ½Ø¶ÏÔ´´®µÃµ½Æ½ºâ×Ó´®£¬½Ø¶ÏºóÇ°ºó×Ó´®µÄ¼ÆÊı²»»¥ÏàÓ°Ïì£¨ÎŞºóĞ§ĞÔ£©£¬ÇÒËùÓĞ¾Ö²¿×îÓÅÏà¼Ó¼´ÎªÕûÌåµÄ×îÓÅ½â¡£
½â¾öË¼Â·£º

ÉèÖÃÒ»¸ö'L'Óë'R'µÄ²îÖµ¼ÆÊıÆ÷diffCount£¬ÉèÖÃÒ»¸öÆ½ºâ×Ó´®¼ÆÊıÆ÷count£»
Ë³Ğò±éÀúÔ´´®×Ö·û£¬ÓöLÔòdiffCount+1£¬Óöµ½RÔòdiffCount-1£»
Ã¿±éÀúÒ»¸ö×Ö·û¼ì²éÒ»´ÎdiffCountÊÇ·ñÎª0£¬ÈôÎª0Ôòcount+1

*/

int balancedStringSplit(char * s){
	int diffCnt = 0;
	int count = 0;

	if (s == NULL)
		return 0;

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'L')
			diffCnt++;
		else
			diffCnt--;

		if (diffCnt == 0)
			count++;
	}

	return count;
}

/*
¼ÙÉèÄãÊÇÒ»Î»ºÜ°ôµÄ¼Ò³¤£¬ÏëÒª¸øÄãµÄº¢×ÓÃÇÒ»Ğ©Ğ¡±ı¸É¡£µ«ÊÇ£¬Ã¿¸öº¢×Ó×î¶àÖ»ÄÜ¸øÒ»¿é±ı¸É¡£¶ÔÃ¿¸öº¢×Ó i £¬¶¼ÓĞÒ»¸öÎ¸¿ÚÖµ gi £¬ÕâÊÇÄÜÈÃº¢×ÓÃÇÂú×ãÎ¸¿ÚµÄ±ı¸ÉµÄ×îĞ¡³ß´ç£»²¢ÇÒÃ¿¿é±ı¸É j £¬¶¼ÓĞÒ»¸ö³ß´ç sj ¡£Èç¹û sj >= gi £¬ÎÒÃÇ¿ÉÒÔ½«Õâ¸ö±ı¸É j ·ÖÅä¸øº¢×Ó i £¬Õâ¸öº¢×Ó»áµÃµ½Âú×ã¡£ÄãµÄÄ¿±êÊÇ¾¡¿ÉÄÜÂú×ãÔ½¶àÊıÁ¿µÄº¢×Ó£¬²¢Êä³öÕâ¸ö×î´óÊıÖµ¡£

×¢Òâ£º

Äã¿ÉÒÔ¼ÙÉèÎ¸¿ÚÖµÎªÕı¡£
Ò»¸öĞ¡ÅóÓÑ×î¶àÖ»ÄÜÓµÓĞÒ»¿é±ı¸É¡£

Ê¾Àı 1:

ÊäÈë: [1,2,3], [1,1]

Êä³ö: 1

½âÊÍ:
ÄãÓĞÈı¸öº¢×ÓºÍÁ½¿éĞ¡±ı¸É£¬3¸öº¢×ÓµÄÎ¸¿ÚÖµ·Ö±ğÊÇ£º1,2,3¡£
ËäÈ»ÄãÓĞÁ½¿éĞ¡±ı¸É£¬ÓÉÓÚËûÃÇµÄ³ß´ç¶¼ÊÇ1£¬ÄãÖ»ÄÜÈÃÎ¸¿ÚÖµÊÇ1µÄº¢×ÓÂú×ã¡£
ËùÒÔÄãÓ¦¸ÃÊä³ö1¡£
Ê¾Àı 2:

ÊäÈë: [1,2], [1,2,3]

Êä³ö: 2

*/

int cmp_int ( const void *a , const void *b){
        return *(int *)a - *(int *)b;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){

	int ig = 0;
	int is = 0;
	int out = 0;

	qsort(g,gSize,sizeof(int),cmp_int);
	qsort(s,sSize,sizeof(int),cmp_int);

	while((ig < gSize) && (is < sSize)) {
		if (g[ig] <= s[is]) {
			out++;
			ig++;
			is++;
		}else {
			is++;
		}
	}

	return out;
}

/*
¸ø¶¨Ò»¸öÕûÊıÊı×é A£¬ÎÒÃÇÖ»ÄÜÓÃÒÔÏÂ·½·¨ĞŞ
¸Ä¸ÃÊı×é£ºÎÒÃÇÑ¡ÔñÄ³¸ö¸öË÷Òı i ²¢½« A[i] Ìæ»»Îª -A[i]£¬
È»ºó×Ü¹²ÖØ¸´Õâ¸ö¹ı³Ì K ´Î¡£
£¨ÎÒÃÇ¿ÉÒÔ¶à´ÎÑ¡ÔñÍ¬Ò»¸öË÷Òı i¡££©

ÒÔÕâÖÖ·½Ê½ĞŞ¸ÄÊı×éºó£¬·µ»ØÊı×é¿ÉÄÜµÄ×î´óºÍ¡£

*/
int cmp_int ( const void *a , const void *b){
        return *(int *)a - *(int *)b;
}

/*µÚÒ»ÖÖ£ºÃ¿´ÎÈ¡·´Ç°£¬½«Êı×éÅÅĞò£¬
È¡·´×îĞ¡Öµ£¬ËÙ¶È×îÂı*/
int largestSumAfterKNegations(int* A, int ASize, int K){
	int sum = 0;
	int tmp;

	if (A == NULL || ASize <= 0)
		return 0;

	for (int i = 0; i < K; i++) {
		qsort(A,ASize,sizeof(int),cmp_int);
		A[0] = -A[0];
	}

	for (int i = 0; i < ASize; i++) {
		sum += A[i];
	}

	return sum;
}

/*
¶ÔK×ö·ÖÎö£¬·Ö3ÖÖÇé¿ö£º
1£¬kĞ¡ÓÚ¸ºÊıµÄ¸öÊı£ºÖ±½Ó½«×îĞ¡µÄ¸ºÊıÈ¡·´
2£¬k¶àÓÚ¸ºÊı¸öÊı£¬µ«ÊÇ¶à³öÀ´µÄ²¿·ÖÊÇÅ¼Êı£º
ËùÓĞ¸ºÊıÈ¡·´ºó£¬Ö±½Ó·µ»ØºÍ
3£¬¶à³ö¸ºÊıµÄ²¿·ÖÊÇÆæÊı£º
½«·Ç¸ºÊıÊı×ÖÅÅĞò£¬°Ñ×îĞ¡Êı×ÖÈ¡·´£¬·µ»ØºÍ
*/

#define m_sum()\
	for (int i = 0; i < ASize; i++) {\
		sum += A[i];\
	}\

int largestSumAfterKNegations(int* A, int ASize, int K){
	int tmp;
	int sum = 0;
	int i = 0;

	if (A == NULL || ASize <= 0)
		return 0;

	qsort(A,ASize,sizeof(int),cmp_int);

	if (A[K -1] <= 0) {
		for (; i < K;i++) {
			A[i] = -A[i];
		}

		m_sum();
		return sum;
	}

	for (i = 0; i < K && A[i] < 0; i++) {
			A[i] = -A[i];
	}

	if ((K -i)%2 == 0) {
		m_sum();
		return sum;
	}

	qsort(A,ASize,sizeof(int),cmp_int);
	A[0] = -A[0];

	m_sum();
	return sum;
}


