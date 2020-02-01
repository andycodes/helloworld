
/*
Interval Scheduling Çø¼äµ÷¶ÈÎÊÌâ

1) ÅÅĞò(ºÜ¶à³¡¾°)
2) µü´ú

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
1029. Á½µØµ÷¶È
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


int cmp_struct( const void *a , const void *b){
	struct obj *c = (struct obj *)a;
	struct obj *d = (struct obj *)b;

	return c->diff - d->diff;
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize){
        int i;
        struct obj ob[costsSize];
        int sum = 0;

        for(i = 0; i < costsSize; i++){
                ob[i].a = costs[i][0];
                ob[i].b = costs[i][1];
                ob[i].diff = ob[i].a - ob[i].b;
        }

	qsort(ob, costsSize, sizeof(struct obj), cmp_struct);
        for (i = 0;i<costsSize/2;i++){
            sum += ob[i].a;
        }

        for (i = costsSize/2;i<costsSize;i++){
            sum += ob[i].b;
        }

        return sum;
}


/*
121. ÂòÂô¹ÉÆ±µÄ×î¼ÑÊ±»ú
¸ø¶¨Ò»¸öÊı×é£¬
ËüµÄµÚ i ¸öÔªËØÊÇÒ»Ö§¸ø¶¨¹ÉÆ±µÚ i ÌìµÄ¼Û¸ñ¡£

Èç¹ûÄã×î¶àÖ»ÔÊĞíÍê³ÉÒ»±Ê½»Ò×£¨¼´ÂòÈëºÍÂô³öÒ»Ö§¹ÉÆ±£©£¬
Éè¼ÆÒ»¸öËã·¨À´¼ÆËãÄãËùÄÜ»ñÈ¡µÄ×î´óÀûÈó¡£

×¢ÒâÄã²»ÄÜÔÚÂòÈë¹ÉÆ±Ç°Âô³ö¹ÉÆ±¡£
ÊäÈë: [7,1,5,3,6,4]
Êä³ö: 5
½âÊÍ: ÔÚµÚ 2 Ìì£¨¹ÉÆ±¼Û¸ñ = 1£©µÄÊ±ºòÂòÈë£¬
ÔÚµÚ 5 Ìì£¨¹ÉÆ±¼Û¸ñ = 6£©µÄÊ±ºòÂô³ö£¬×î´óÀûÈó = 6-1 = 5 ¡£
     ×¢ÒâÀûÈó²»ÄÜÊÇ 7-1 = 6, ÒòÎªÂô³ö¼Û¸ñĞèÒª´óÓÚÂòÈë¼Û¸ñ¡£


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
1221. ·Ö¸îÆ½ºâ×Ö·û´®
ÔÚÒ»¸ö¡¸Æ½ºâ×Ö·û´®¡¹ÖĞ£¬'L' ºÍ 'R' ×Ö·ûµÄÊıÁ¿ÊÇÏàÍ¬µÄ¡£

¸ø³öÒ»¸öÆ½ºâ×Ö·û´® s£¬
ÇëÄã½«Ëü·Ö¸î³É¾¡¿ÉÄÜ¶àµÄÆ½ºâ×Ö·û´®¡£

·µ»Ø¿ÉÒÔÍ¨¹ı·Ö¸îµÃµ½µÄÆ½ºâ×Ö·û´®µÄ×î´óÊıÁ¿¡£

ÎÊÌâ·ÖÎö£º·Ö¸îÆ½ºâ´®£¬µÃµ½¾¡¿ÉÄÜ¶àµÄÆ½ºâ´®¡£
ÕâÊÇÒ»¸öÊÊÓÃÌ°ĞÄËã·¨µÄÎÊÌâ£¬
ÔÚÊÊµ±µÄÎ»ÖÃ½Ø¶ÏÔ´´®µÃµ½Æ½ºâ×Ó´®£¬
½Ø¶ÏºóÇ°ºó×Ó´®µÄ¼ÆÊı²»»¥ÏàÓ°Ïì£¨ÎŞºóĞ§ĞÔ£©£¬
ÇÒËùÓĞ¾Ö²¿×îÓÅÏà¼Ó¼´ÎªÕûÌåµÄ×îÓÅ½â¡£
½â¾öË¼Â·£º

ÉèÖÃÒ»¸ö'L'Óë'R'µÄ²îÖµ¼ÆÊıÆ÷diffCount£¬
ÉèÖÃÒ»¸öÆ½ºâ×Ó´®¼ÆÊıÆ÷count£»
Ë³Ğò±éÀúÔ´´®×Ö·û£¬ÓöLÔòdiffCount+1£¬Óöµ½RÔòdiffCount-1£»
Ã¿±éÀúÒ»¸ö×Ö·û¼ì²éÒ»´ÎdiffCountÊÇ·ñÎª0£¬ÈôÎª0Ôòcount+1
*/

int balancedStringSplit(char * s) {
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
¼ÙÉèÄãÊÇÒ»Î»ºÜ°ôµÄ¼Ò³¤£¬ÏëÒª¸øÄãµÄº¢×ÓÃÇÒ»Ğ©Ğ¡±ı¸É¡£
µ«ÊÇ£¬Ã¿¸öº¢×Ó×î¶àÖ»ÄÜ¸øÒ»¿é±ı¸É¡£¶ÔÃ¿¸öº¢×Ó i £¬
¶¼ÓĞÒ»¸öÎ¸¿ÚÖµ gi £¬ÕâÊÇÄÜÈÃº¢×ÓÃÇÂú×ãÎ¸¿ÚµÄ±ı¸É
µÄ×îĞ¡³ß´ç£»²¢ÇÒÃ¿¿é±ı¸É j £¬¶¼ÓĞÒ»¸ö³ß´ç sj ¡£
Èç¹û sj >= gi £¬
ÎÒÃÇ¿ÉÒÔ½«Õâ¸ö±ı¸É j ·ÖÅä¸øº¢×Ó i £¬
Õâ¸öº¢×Ó»áµÃµ½Âú×ã¡£
ÄãµÄÄ¿±êÊÇ¾¡¿ÉÄÜÂú×ãÔ½¶àÊıÁ¿µÄº¢×Ó£¬
²¢Êä³öÕâ¸ö×î´óÊıÖµ¡£

×¢Òâ£º

Äã¿ÉÒÔ¼ÙÉèÎ¸¿ÚÖµÎªÕı¡£
Ò»¸öĞ¡ÅóÓÑ×î¶àÖ»ÄÜÓµÓĞÒ»¿é±ı¸É¡£

Ê¾Àı 1:

ÊäÈë: [1,2,3], [1,1]

Êä³ö: 1

½âÊÍ:
ÄãÓĞÈı¸öº¢×ÓºÍÁ½¿éĞ¡±ı¸É£¬
3¸öº¢×ÓµÄÎ¸¿ÚÖµ·Ö±ğÊÇ£º1,2,3¡£
ËäÈ»ÄãÓĞÁ½¿éĞ¡±ı¸É£¬
ÓÉÓÚËûÃÇµÄ³ß´ç¶¼ÊÇ1£¬ÄãÖ»ÄÜÈÃÎ¸¿ÚÖµÊÇ1µÄº¢×ÓÂú×ã¡£
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


/*
870. ÓÅÊÆÏ´ÅÆ
¸ø¶¨Á½¸ö´óĞ¡ÏàµÈµÄÊı×é A ºÍ B£¬A Ïà¶ÔÓÚ
B µÄÓÅÊÆ¿ÉÒÔÓÃÂú×ã A[i] > B[i] µÄË÷Òı i µÄÊıÄ¿À´ÃèÊö¡£

·µ»Ø A µÄÈÎÒâÅÅÁĞ£¬Ê¹ÆäÏà¶ÔÓÚ B µÄÓÅÊÆ×î´ó»¯¡£



Ê¾Àı 1£º

ÊäÈë£ºA = [2,7,11,15], B = [1,10,4,11]
Êä³ö£º[2,11,7,15]

*/
struct obj {
	int data;
	int index;
};

int cmp_struct( const void *a , const void *b){
	struct obj *c = (struct obj *)a;
	struct obj *d = (struct obj *)b;

	return c->data- d->data;
}

int* advantageCount(int* A, int ASize, int* B, int BSize, int* returnSize){
    int l = 0;
    int r = ASize - 1;
	struct obj *ao = (struct obj *)malloc(sizeof(struct obj) * ASize);
	struct obj *bo = (struct obj *)malloc(sizeof(struct obj) * BSize);
	int *ret = (int *)malloc(sizeof(int) * ASize);

	for (int i = 0; i < ASize; i++) {
		ao[i].data = A[i];
		ao[i].index = i;

		bo[i].data = B[i];
		bo[i].index = i;
	}

	qsort(ao, ASize, sizeof(struct obj), cmp_struct);
	qsort(bo, ASize, sizeof(struct obj), cmp_struct);
    	int j = BSize - 1;
	for (int i = 0; i < ASize; i++) {
		if (ao[i].data > bo[l].data) {
			ret[bo[l].index] = ao[i].data;
            		l++;
		} else {
			ret[bo[r].index] = ao[i].data;
            		r--;
		}
	}

	*returnSize = ASize;
	return ret;
}

/*
1282. ÓÃ»§·Ö×é
ÓĞ n Î»ÓÃ»§²Î¼Ó»î¶¯£¬ËûÃÇµÄ ID ´Ó 0 µ½ n - 1£¬Ã¿Î»ÓÃ»§¶¼ Ç¡ºÃ ÊôÓÚÄ³Ò»ÓÃ»§×é¡£¸øÄãÒ»¸ö³¤¶ÈÎª n µÄÊı×é groupSizes£¬ÆäÖĞ°üº¬Ã¿Î»ÓÃ»§Ëù´¦µÄÓÃ»§×éµÄ´óĞ¡£¬ÇëÄã·µ»ØÓÃ»§·Ö×éÇé¿ö£¨´æÔÚµÄÓÃ»§×éÒÔ¼°Ã¿¸ö×éÖĞÓÃ»§µÄ ID£©¡£

Äã¿ÉÒÔÈÎºÎË³Ğò·µ»Ø½â¾ö·½°¸£¬ID µÄË³ĞòÒ²²»ÊÜÏŞÖÆ¡£´ËÍâ£¬ÌâÄ¿¸ø³öµÄÊı¾İ±£Ö¤ÖÁÉÙ´æÔÚÒ»ÖÖ½â¾ö·½°¸¡£



Ê¾Àı 1£º

ÊäÈë£ºgroupSizes = [3,3,3,3,3,1,3]
Êä³ö£º[[5],[0,1,2],[3,4,6]]
½âÊÍ£º
ÆäËû¿ÉÄÜµÄ½â¾ö·½°¸ÓĞ [[2,1,6],[5],[0,4,3]] ºÍ [[5],[0,6,2],[4,3,1]]¡£


·½·¨Ò»£º¹şÏ£Ó³Éä
¶ÔÓÚÁ½¸öÓÃ»§ x ºÍ y£¬Èç¹û groupSize[x] != groupSize[y]£¬ËüÃÇÓÃ»§×éµÄ´óĞ¡²»Í¬£¬ÄÇÃ´ËüÃÇÒ»¶¨²»ÔÚÍ¬Ò»¸öÓÃ»§×éÖĞ¡£Òò´ËÎÒÃÇ¿ÉÒÔÊ×ÏÈ¶ÔËùÓĞµÄÓÃ»§½øĞĞÒ»´Î¡¾´Ö·Ö×é¡¿£¬ÓÃÒ»¸ö¹şÏ£Ó³Éä£¨HashMap£©À´´æ´¢ËùÓĞµÄÓÃ»§¡£¹şÏ£Ó³ÉäÖĞ¼üÖµ¶ÔÎª (gsize, users)£¬ÆäÖĞ gsize ±íÊ¾ÓÃ»§×éµÄ´óĞ¡£¬users ±íÊ¾Âú×ãÓÃ»§×é´óĞ¡Îª gsize£¬¼´ groupSize[x] == gsize µÄËùÓĞÓÃ»§¡£ÕâÑùÒÔÀ´£¬ÎÒÃÇ¾Í°ÑËùÓĞÓÃ»§×é´óĞ¡ÏàÍ¬µÄÓÃ»§¶¼ÔİÊ±·ÅÔÚÁËÍ¬Ò»¸ö×éÖĞ¡£

ÔÚ½øĞĞÁË¡¾´Ö·Ö×é¡¿ºó£¬ÎÒÃÇ¿ÉÒÔ½«Ã¿¸ö¼üÖµ¶Ô (gsize, users) ÖĞµÄ users ½øĞĞ¡¾Ï¸·Ö×é¡¿¡£ÓÉÓÚÌâÄ¿±£Ö¤ÁË¸ø³öµÄÊı¾İÖÁÉÙ´æÔÚÒ»ÖÖ·½°¸£¬Òò´ËÎÒÃÇµÄ¡¾Ï¸·Ö×é¡¿¿ÉÒÔ±äµÃºÜ¼òµ¥£ºÖ»ÒªÃ¿´Î´Ó users ÖĞÈ¡³ö gsize ¸öÓÃ»§£¬°ÑËüÃÇ·ÅÔÚÒ»¸ö×éÖĞ¾Í¿ÉÒÔÁË¡£ÔÚ½øĞĞÍêËùÓĞµÄ¡¾Ï¸·Ö×é¡¿ºó£¬ÎÒÃÇ¾ÍµÃµ½ÁËÒ»ÖÖÂú×ãÌõ¼şµÄ·Ö×é·½°¸¡£

*/
struct bigcase {
	int cnt;
	int idx[1024];
};

int** groupThePeople(int* groupSizes, int groupSizesSize,
	int* returnSize, int** returnColumnSizes) {
	int ** res = (int **)calloc(1024, sizeof(int *));
	*returnSize = 0;

	*returnColumnSizes = (int *)calloc(1024, sizeof(int));

	struct bigcase array[groupSizesSize + 1];
	memset(array, 0, sizeof(array));

	for (int i = 0; i < groupSizesSize; i++) {
		int curSize = groupSizes[i];
		array[curSize].idx[array[curSize].cnt++] = i;
	}

	for (int i = 0; i < groupSizesSize + 1; i++) {
		int k = 0;
		while(array[i].cnt - k * i > 0) {
			res[*returnSize] = (int *)calloc(i, sizeof(int));
			for(int j = 0; j < i ; j++) {
				res[*returnSize][j] = array[i].idx[j + k * i];
			}
			(*returnColumnSizes)[*returnSize] = i;
			(*returnSize)++;
			k++;
		}
	}

	return res;
}
