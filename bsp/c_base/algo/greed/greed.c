
/*
Interval Scheduling Çø¼äµ÷¶ÈÎÊÌâ
Ì°ĞÄËã·¨Ò»°ãÓÃÀ´½â¾öĞèÒª ¡°ÕÒµ½Òª×öÄ³ÊÂµÄ×îĞ¡ÊıÁ¿¡±
»ò ¡°ÕÒµ½ÔÚÄ³Ğ©Çé¿öÏÂÊÊºÏµÄ×î´óÎïÆ·ÊıÁ¿¡± µÄÎÊÌâ£¬
ÇÒÌá¹©µÄÊÇÎŞĞòµÄÊäÈë¡£
1) ÅÅĞò(ºÜ¶à³¡¾°)
2) µü´ú

*/

/*
1029. Á½µØµ÷¶È
ÄÑ¶È¼òµ¥122
¹«Ë¾¼Æ»®ÃæÊÔ 2N ÈË¡£µÚ i ÈË·ÉÍù A ÊĞµÄ·ÑÓÃÎª costs[i][0]£¬
·ÉÍù B ÊĞµÄ·ÑÓÃÎª costs[i][1]¡£
·µ»Ø½«Ã¿¸öÈË¶¼·Éµ½Ä³×ù³ÇÊĞµÄ×îµÍ·ÑÓÃ£¬ÒªÇóÃ¿¸ö³ÇÊĞ¶¼
ÓĞ N ÈËµÖ´ï¡£
Ê¾Àı£º
ÊäÈë£º[[10,20],[30,200],[400,50],[30,20]]
Êä³ö£º110
½âÊÍ£º
µÚÒ»¸öÈËÈ¥ A ÊĞ£¬·ÑÓÃÎª 10¡£
µÚ¶ş¸öÈËÈ¥ A ÊĞ£¬·ÑÓÃÎª 30¡£
µÚÈı¸öÈËÈ¥ B ÊĞ£¬·ÑÓÃÎª 50¡£
µÚËÄ¸öÈËÈ¥ B ÊĞ£¬·ÑÓÃÎª 20¡£

×îµÍ×Ü·ÑÓÃÎª 10 + 30 + 50 + 20 = 110£¬Ã¿¸ö³ÇÊĞ¶¼ÓĞÒ»°ëµÄÈËÔÚÃæÊÔ¡£

*/
/*°´ÕÕÃ¿¸öÖ°Ô±Á½¸öµØ·½µÄ·ÑÓÃ²îÖµÅÅĞò*/
int cmp_doublePoint(const void *a, const void *b)
{
	int ** aa =  (int **)a;
	int ** bb = (int **)b;

	return (aa[0][0] - aa[0][1]) - (bb[0][0] - bb[0][1]);
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize)
{
	qsort(costs, costsSize, sizeof(costs[0]), cmp_doublePoint);
	int sum = 0;

	for (int i = 0; i < costsSize / 2 ; i++) {
		sum += costs[i][0];
	}

	for (int i = costsSize / 2; i < costsSize; i++) {
		sum += costs[i][1];
	}

	return sum;
}

/*
121. ÂòÂô¹ÉÆ±µÄ×î¼ÑÊ±»ú
ÄÑ¶È¼òµ¥1126
¸ø¶¨Ò»¸öÊı×é£¬ËüµÄµÚ i ¸öÔªËØÊÇÒ»Ö§¸ø¶¨¹ÉÆ±µÚ i ÌìµÄ¼Û¸ñ¡£
Èç¹ûÄã×î¶àÖ»ÔÊĞíÍê³ÉÒ»±Ê½»Ò×£¨¼´ÂòÈëºÍÂô³öÒ»Ö§¹ÉÆ±Ò»´Î£©£¬Éè¼ÆÒ»¸öËã·¨À´¼ÆËãÄãËùÄÜ»ñÈ¡µÄ×î´óÀûÈó¡£
×¢Òâ£ºÄã²»ÄÜÔÚÂòÈë¹ÉÆ±Ç°Âô³ö¹ÉÆ±¡£
Ê¾Àı 1:
ÊäÈë: [7,1,5,3,6,4]
Êä³ö: 5
½âÊÍ: ÔÚµÚ 2 Ìì£¨¹ÉÆ±¼Û¸ñ = 1£©µÄÊ±ºòÂòÈë£¬ÔÚµÚ 5 Ìì£¨¹ÉÆ±¼Û¸ñ = 6£©µÄÊ±ºòÂô³ö£¬×î´óÀûÈó = 6-1 = 5 ¡£
     ×¢ÒâÀûÈó²»ÄÜÊÇ 7-1 = 6, ÒòÎªÂô³ö¼Û¸ñĞèÒª´óÓÚÂòÈë¼Û¸ñ£»Í¬Ê±£¬Äã²»ÄÜÔÚÂòÈëÇ°Âô³ö¹ÉÆ±¡£
Ê¾Àı 2:
ÊäÈë: [7,6,4,3,1]
Êä³ö: 0
½âÊÍ: ÔÚÕâÖÖÇé¿öÏÂ, Ã»ÓĞ½»Ò×Íê³É, ËùÒÔ×î´óÀûÈóÎª 0¡£
*/
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
int maxProfit(int* prices, int pricesSize)
{
	int profit = 0;
	for (int i = 1; i <pricesSize; i++) {
		int tmp = prices[i] - prices[i - 1];
		if (tmp > 0)
			profit += tmp;
	}

	return profit;
}
int maxProfit(int* prices, int pricesSize)
{
	int minprice = INT_MAX;
	int maxprofix = 0;

	for (int i = 0; i < pricesSize; i++) {
		maxprofix = fmax(maxprofix, prices[i] - minprice);
		minprice = fmin(minprice, prices[i]);
	}

	return maxprofix;
}

/*
1221. ·Ö¸îÆ½ºâ×Ö·û´®
ÄÑ¶È¼òµ¥60
ÔÚÒ»¸ö¡¸Æ½ºâ×Ö·û´®¡¹ÖĞ£¬'L' ºÍ 'R' ×Ö·ûµÄÊıÁ¿ÊÇÏàÍ¬µÄ¡£
¸ø³öÒ»¸öÆ½ºâ×Ö·û´® s£¬ÇëÄã½«Ëü·Ö¸î³É¾¡¿ÉÄÜ¶àµÄÆ½ºâ×Ö·û´®¡£
·µ»Ø¿ÉÒÔÍ¨¹ı·Ö¸îµÃµ½µÄÆ½ºâ×Ö·û´®µÄ×î´óÊıÁ¿¡£
Ê¾Àı 1£º
ÊäÈë£ºs = "RLRRLLRLRL"
Êä³ö£º4
½âÊÍ£ºs ¿ÉÒÔ·Ö¸îÎª "RL", "RRLL", "RL", "RL", Ã¿¸ö×Ó×Ö·û´®ÖĞ¶¼°üº¬ÏàÍ¬ÊıÁ¿µÄ 'L' ºÍ 'R'¡£
Ê¾Àı 2£º
ÊäÈë£ºs = "RLLLLRRRLR"
Êä³ö£º3
½âÊÍ£ºs ¿ÉÒÔ·Ö¸îÎª "RL", "LLLRRR", "LR", Ã¿¸ö×Ó×Ö·û´®ÖĞ¶¼°üº¬ÏàÍ¬ÊıÁ¿µÄ 'L' ºÍ 'R
*/
/*
½â¾öË¼Â·£º
ÉèÖÃÒ»¸ö'L'Óë'R'µÄ²îÖµ¼ÆÊıÆ÷diffCount£¬
ÉèÖÃÒ»¸öÆ½ºâ×Ó´®¼ÆÊıÆ÷count£»
Ë³Ğò±éÀúÔ´´®×Ö·û£¬ÓöLÔòdiffCount+1£¬Óöµ½RÔòdiffCount-1£»
Ã¿±éÀúÒ»¸ö×Ö·û¼ì²éÒ»´ÎdiffCountÊÇ·ñÎª0£¬ÈôÎª0Ôòcount+1
*/
int balancedStringSplit(char * s)
{
	int diffCnt = 0;
	int count = 0;

	if (s == NULL)
		return 0;

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'L')
			diffCnt++;
		else
			diffCnt--;

/*
RLRRLL diffCnt = 0
RL diffCnt = 0
RRLL diffCnt = 0
*/
		if (diffCnt == 0)
			count++;
	}

	return count;
}

/*
455. ·Ö·¢±ı¸É
ÄÑ¶È¼òµ¥187
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

½âÊÍ:
ÄãÓĞÁ½¸öº¢×ÓºÍÈı¿éĞ¡±ı¸É£¬2¸öº¢×ÓµÄÎ¸¿ÚÖµ·Ö±ğÊÇ1,2¡£
ÄãÓµÓĞµÄ±ı¸ÉÊıÁ¿ºÍ³ß´ç¶¼×ãÒÔÈÃËùÓĞº¢×ÓÂú×ã¡£
ËùÒÔÄãÓ¦¸ÃÊä³ö2.
 '¡£
*/
int findContentChildren(int* g, int gSize, int* s, int sSize)
{
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
1005. K ´ÎÈ¡·´ºó×î´ó»¯µÄÊı×éºÍ
ÄÑ¶È¼òµ¥52
¸ø¶¨Ò»¸öÕûÊıÊı×é A£¬ÎÒÃÇÖ»ÄÜÓÃÒÔÏÂ·½·¨ĞŞ¸Ä¸ÃÊı×é£ºÎÒÃÇÑ¡ÔñÄ³¸öË÷Òı i ²¢½« A[i] Ìæ»»Îª -A[i]£¬È»ºó×Ü¹²ÖØ¸´Õâ¸ö¹ı³Ì K ´Î¡££¨ÎÒÃÇ¿ÉÒÔ¶à´ÎÑ¡ÔñÍ¬Ò»¸öË÷Òı i¡££©
ÒÔÕâÖÖ·½Ê½ĞŞ¸ÄÊı×éºó£¬·µ»ØÊı×é¿ÉÄÜµÄ×î´óºÍ¡£
Ê¾Àı 1£º
ÊäÈë£ºA = [4,2,3], K = 1
Êä³ö£º5
½âÊÍ£ºÑ¡ÔñË÷Òı (1,) £¬È»ºó A ±äÎª [4,-2,3]¡£
Ê¾Àı 2£º
ÊäÈë£ºA = [3,-1,0,2], K = 3
Êä³ö£º6
½âÊÍ£ºÑ¡ÔñË÷Òı (1, 2, 2) £¬È»ºó A ±äÎª [3,1,0,2]¡£
*/

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

int largestSumAfterKNegations(int* A, int ASize, int K)
{
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
			ret[bo[l].index] = ao[i].data; // Èç¹ûAÊı×éµÄÖµ´óÓÚBÊı×éµÄÖµÔò°ÑA[i]µÄÖµ¸³¸ølistÊı×éÖĞµÄBÊı×éµÄË÷Òı¡£
            		l++;
		} else {
			ret[bo[r].index] = ao[i].data;// Èç¹ûÊÇĞ¡ÓÚµÈÓÚÔò°ÑA[i]µÄÖµ·ÅÔÚlistÊı×éÖĞBÊı×é×î´óµÄË÷ÒıÎ»ÖÃ¡£
            		r--;
		}
	}

	*returnSize = ASize;
	return ret;
}

/*
1282. ÓÃ»§·Ö×é
ÓĞ n Î»ÓÃ»§²Î¼Ó»î¶¯£¬ËûÃÇµÄ ID ´Ó 0 µ½ n - 1£¬Ã¿Î»ÓÃ»§¶¼ Ç¡ºÃ
ÊôÓÚÄ³Ò»ÓÃ»§×é¡£¸øÄãÒ»¸ö³¤¶ÈÎª n µÄÊı×é groupSizes£¬ÆäÖĞ°üº¬
Ã¿Î»ÓÃ»§Ëù´¦µÄÓÃ»§×éµÄ´óĞ¡£¬ÇëÄã·µ»ØÓÃ»§·Ö×éÇé¿ö£¨´æÔÚ
µÄÓÃ»§×éÒÔ¼°Ã¿¸ö×éÖĞÓÃ»§µÄ ID£©¡£
Äã¿ÉÒÔÈÎºÎË³Ğò·µ»Ø½â¾ö·½°¸£¬ID µÄË³ĞòÒ²²»ÊÜÏŞÖÆ¡£´ËÍâ£¬
ÌâÄ¿¸ø³öµÄÊı¾İ±£Ö¤ÖÁÉÙ´æÔÚÒ»ÖÖ½â¾ö·½°¸¡£
Ê¾Àı 1£º
ÊäÈë£ºgroupSizes = [3,3,3,3,3,1,3]
Êä³ö£º[[5],[0,1,2],[3,4,6]]
½âÊÍ£º
ÆäËû¿ÉÄÜµÄ½â¾ö·½°¸ÓĞ [[2,1,6],[5],[0,4,3]] ºÍ [[5],[0,6,2],[4,3,1]]¡£
*/
/*
·½·¨Ò»£º¹şÏ£Ó³Éä
¶ÔÓÚÁ½¸öÓÃ»§ x ºÍ y£¬Èç¹û groupSize[x] != groupSize[y]£¬ËüÃÇÓÃ»§×éµÄ
´óĞ¡²»Í¬£¬ÄÇÃ´ËüÃÇÒ»¶¨²»ÔÚÍ¬Ò»¸öÓÃ»§×éÖĞ¡£Òò´ËÎÒÃÇ¿É
ÒÔÊ×ÏÈ¶ÔËùÓĞµÄÓÃ»§½øĞĞÒ»´Î¡¾´Ö·Ö×é¡¿£¬ÓÃÒ»¸ö¹şÏ£Ó³Éä£¨
HashMap£©À´´æ´¢ËùÓĞµÄÓÃ»§¡£¹şÏ£Ó³ÉäÖĞ¼üÖµ¶ÔÎª (gsize, users)£¬
ÆäÖĞ gsize ±íÊ¾ÓÃ»§×éµÄ´óĞ¡£¬users ±íÊ¾Âú×ãÓÃ»§×é´óĞ¡Îª gsize£¬
¼´ groupSize[x] == gsize µÄËùÓĞÓÃ»§¡£ÕâÑùÒÔÀ´£¬ÎÒÃÇ¾Í°ÑËùÓĞÓÃ»§
×é´óĞ¡ÏàÍ¬µÄÓÃ»§¶¼ÔİÊ±·ÅÔÚÁËÍ¬Ò»¸ö×éÖĞ¡£

ÔÚ½øĞĞÁË¡¾´Ö·Ö×é¡¿ºó£¬ÎÒÃÇ¿ÉÒÔ½«Ã¿¸ö¼üÖµ¶Ô (gsize, users) ÖĞ
µÄ users ½øĞĞ¡¾Ï¸·Ö×é¡¿¡£ÓÉÓÚÌâÄ¿±£Ö¤ÁË¸ø³öµÄÊı¾İÖÁÉÙ´æ
ÔÚÒ»ÖÖ·½°¸£¬Òò´ËÎÒÃÇµÄ¡¾Ï¸·Ö×é¡¿¿ÉÒÔ±äµÃºÜ¼òµ¥£ºÖ»Òª
Ã¿´Î´Ó users ÖĞÈ¡³ö gsize ¸öÓÃ»§£¬°ÑËüÃÇ·ÅÔÚÒ»¸ö×éÖĞ¾Í¿ÉÒÔÁË¡£
ÔÚ½øĞĞÍêËùÓĞµÄ¡¾Ï¸·Ö×é¡¿ºó£¬ÎÒÃÇ¾ÍµÃµ½ÁËÒ»ÖÖÂú×ãÌõ¼ş
µÄ·Ö×é·½°¸¡£
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

/*
1094. Æ´³µ
ÄÑ¶ÈÖĞµÈ22
¼ÙÉèÄãÊÇÒ»Î»Ë³·ç³µË¾»ú£¬³µÉÏ×î³õÓĞ capacity ¸ö¿Õ×ùÎ»¿ÉÒÔÓÃ
À´ÔØ¿Í¡£ÓÉÓÚµÀÂ·µÄÏŞÖÆ£¬³µ Ö»ÄÜ ÏòÒ»¸ö·½ÏòĞĞÊ»£¨Ò²¾ÍÊÇ
Ëµ£¬²»ÔÊĞíµôÍ·»ò¸Ä±ä·½Ïò£¬Äã¿ÉÒÔ½«ÆäÏëÏóÎªÒ»¸öÏòÁ¿£©¡£
Õâ¶ùÓĞÒ»·İĞĞ³Ì¼Æ»®±í trips[][]£¬ÆäÖĞ trips[i] = [num_passengers, start_location,
end_location] °üº¬ÁËÄãµÄµÚ i ´ÎĞĞ³ÌĞÅÏ¢£º
"	±ØĞë½ÓËÍµÄ³Ë¿ÍÊıÁ¿£»
"	³Ë¿ÍµÄÉÏ³µµØµã£»
"	ÒÔ¼°³Ë¿ÍµÄÏÂ³µµØµã¡£
ÕâĞ©¸ø³öµÄµØµãÎ»ÖÃÊÇ´ÓÄãµÄ ³õÊ¼ ³ö·¢Î»ÖÃÏòÇ°ĞĞÊ»µ½ÕâĞ©
µØµãËùĞèµÄ¾àÀë£¨ËüÃÇÒ»¶¨ÔÚÄãµÄĞĞÊ»·½ÏòÉÏ£©¡£
ÇëÄã¸ù¾İ¸ø³öµÄĞĞ³Ì¼Æ»®±íºÍ³µ×ÓµÄ×ùÎ»Êı£¬À´ÅĞ¶ÏÄãµÄ³µ
ÊÇ·ñ¿ÉÒÔË³ÀûÍê³É½ÓËÍËùÓÃ³Ë¿ÍµÄÈÎÎñ£¨µ±ÇÒ½öµ±Äã¿ÉÒÔÔÚ
ËùÓĞ¸ø¶¨µÄĞĞ³ÌÖĞ½ÓËÍËùÓĞ³Ë¿ÍÊ±£¬·µ»Ø true£¬·ñÔòÇë·µ»Ø false£©¡£
Ê¾Àı 1£º
ÊäÈë£ºtrips = [[2,1,5],[3,3,7]], capacity = 4
Êä³ö£ºfalse
Ê¾Àı 2£º
ÊäÈë£ºtrips = [[2,1,5],[3,3,7]], capacity = 5
Êä³ö£ºtrue

*/
bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
	int map[1024] = {{0}};

	for (int i = 0; i < tripsSize; i++) {
		map[trips[i][1]] += trips[i][0];
		map[trips[i][2]] -= trips[i][0];
	}

	int curStateTotal = 0;
	for (int i = 0; i < 1024; i++) {
		curStateTotal += map[i];
		if(curStateTotal > capacity)
			return false;
	}

	return true;
}

/*
991. »µÁËµÄ¼ÆËãÆ÷
ÄÑ¶ÈÖĞµÈ57
ÔÚÏÔÊ¾×ÅÊı×ÖµÄ»µ¼ÆËãÆ÷ÉÏ£¬ÎÒÃÇ¿ÉÒÔÖ´ĞĞÒÔÏÂÁ½ÖÖ²Ù×÷£º
"	Ë«±¶£¨Double£©£º½«ÏÔÊ¾ÆÁÉÏµÄÊı×Ö³Ë 2£»
"	µİ¼õ£¨Decrement£©£º½«ÏÔÊ¾ÆÁÉÏµÄÊı×Ö¼õ 1 ¡£
×î³õ£¬¼ÆËãÆ÷ÏÔÊ¾Êı×Ö X¡£
·µ»ØÏÔÊ¾Êı×Ö Y ËùĞèµÄ×îĞ¡²Ù×÷Êı¡£
Ê¾Àı 1£º
ÊäÈë£ºX = 2, Y = 3
Êä³ö£º2
½âÊÍ£ºÏÈ½øĞĞË«±¶ÔËËã£¬È»ºóÔÙ½øĞĞµİ¼õÔËËã {2 -> 4 -> 3}.

*/
/*
Áé¸ĞÀ´×ÔÊ¾Àı£¬Ê×ÏÈÓÉÓÚ¼ÆËãÆ÷Ö»ÄÜË«±¶»òµİ¼õ£¬XYÓÖ¶¼ÎªÕûÊı£¬Òò´Ë£¬µ±X > YÊ±£¬Ö»ÄÜµİ¼õX-Y´Î´ïµ½Ä¿µÄ¡£µ±X = Y £¬ÎŞĞè²Ù×÷£¬¿ÉÒÔºÍÉÏÒ»¸öÌõ¼şÒ»ÆğÅĞ¶Ï¡£
µ±Y > XÊ±£¬Èç¹ûYÊÇÒ»¸öÆæÊı£¬ÄÇÃ´µÃµ½ËüµÄ×îºóÒ»²½±ØÈ»ÊÇµİ¼õ¡£Èç¹ûYÊÇÒ»¸öÅ¼Êı£¬Èç¹ûµÃµ½ËüµÄ×îºóÒ»²½ÊÇµİ¼õ£¬ÄÇÃ´µ¹ÊıµÚ¶ş²½Ò²Ó¦¸ÃÊÇµİ¼õ£¬µ«YÊÇÒ»¸ö´óÓÚXµÄÊı£¬Òò´ËX±ä³ÉYÊ±Ò»¶¨¾­¹ıÁËË«±¶£¬ÄÇÃ´ÓëÆäË«±¶ºó½øĞĞµİ¼õ£¬²»ÈçÏÈµİ¼õÔÙË«±¶£¬»¨·ÑµÄ²½ÊıÓ¦¸Ã»á¸üÉÙ£¬ÖÁÉÙÄÜ³ÖÆ½¡£
ÄÇÃ´ÎÊÌâ¾Í±ä³ÉÁËµİ¹éÎÊÌâ¡£µ±Y > XÊ±ÇÒYÊÇÆæÊıÊ±£¬½«Ëü¼ÓÒ»±ä³ÉÅ¼Êı£¬²¢ÇÒ×Ü²½ÊıµÈÓÚ1 + brokenCalc(X,(Y+1))£¬µ±YÊÇÅ¼ÊıÊ±£¬×Ü²½ÊıµÈÓÚ1 + brokenCalc(X,Y/2)¡£

*/
int brokenCalc(int X, int Y)
{
	if (Y <= X)
		return X - Y;
	if (Y % 2 == 0) {
		return 1 + brokenCalc(X , Y /2);
	} else
		return 1 + brokenCalc(X , Y + 1);
}

/*
946. ÑéÖ¤Õ»ĞòÁĞ see stack
·½·¨Ò»£º Ì°ĞÄ
Ë¼Â·
ËùÓĞµÄÔªËØÒ»¶¨ÊÇ°´Ë³Ğò push ½øÈ¥µÄ£¬ÖØÒªµÄÊÇÔõÃ´ pop ³öÀ´£¿
¼ÙÉèµ±Ç°Õ»¶¥ÔªËØÖµÎª 2£¬Í¬Ê±¶ÔÓ¦µÄ popped ĞòÁĞÖĞÏÂÒ»¸öÒª
pop µÄÖµÒ²Îª 2£¬ÄÇ¾Í±ØĞëÁ¢¿Ì°ÑÕâ¸öÖµ pop ³öÀ´¡£ÒòÎªÖ®ºóµÄ
push ¶¼»áÈÃÕ»¶¥ÔªËØ±ä³É²»Í¬ÓÚ 2 µÄÆäËûÖµ£¬ÕâÑùÔÙ pop ³öÀ´
µÄÊı popped ĞòÁĞ¾Í²»¶ÔÓ¦ÁË¡£
Ëã·¨
½« pushed ¶ÓÁĞÖĞµÄÃ¿¸öÊı¶¼ push µ½Õ»ÖĞ£¬Í¬Ê±¼ì²éÕâ¸öÊıÊÇ²»
ÊÇ popped ĞòÁĞÖĞÏÂÒ»¸öÒª pop µÄÖµ£¬Èç¹ûÊÇ¾Í°ÑËü pop ³öÀ´¡£
×îºó£¬¼ì²é²»ÊÇËùÓĞµÄ¸Ã pop ³öÀ´µÄÖµ¶¼ÊÇ pop ³öÀ´ÁË¡£
*/
bool validateStackSequences(int* pushed, int pushedSize,
	int* popped, int poppedSize)
{
	if (pushed == NULL || popped == NULL) {
		return false;
	}

	struct astack *stack = astack_init(pushedSize);
	int j = 0;
	for (int i = 0; i < pushedSize; i++) {
		struct astack_load load;
		load.data = pushed[i];
		astack_push(stack, load);

		while(!astack_empty(stack) && j < pushedSize) {
			struct astack_load load = astack_top(stack);
			if (load.data == popped[j]) {
				astack_pop(stack);
				j++;
			} else {
				break;
			}
		}
	}

	return j == pushedSize;
}

/*
55. ÌøÔ¾ÓÎÏ·
ÄÑ¶ÈÖĞµÈ761
¸ø¶¨Ò»¸ö·Ç¸ºÕûÊıÊı×é£¬Äã×î³õÎ»ÓÚÊı×éµÄµÚÒ»¸öÎ»ÖÃ¡£
Êı×éÖĞµÄÃ¿¸öÔªËØ´ú±íÄãÔÚ¸ÃÎ»ÖÃ¿ÉÒÔÌøÔ¾µÄ×î´ó³¤¶È¡£
ÅĞ¶ÏÄãÊÇ·ñÄÜ¹»µ½´ï×îºóÒ»¸öÎ»ÖÃ¡£
Ê¾Àı 1:
ÊäÈë: [2,3,1,1,4]
Êä³ö: true
½âÊÍ: ÎÒÃÇ¿ÉÒÔÏÈÌø 1 ²½£¬´ÓÎ»ÖÃ 0 µ½´ï Î»ÖÃ 1, È»ºóÔÙ´ÓÎ»ÖÃ
1 Ìø 3 ²½µ½´ï×îºóÒ»¸öÎ»ÖÃ¡£
Ê¾Àı 2:
ÊäÈë: [3,2,1,0,4]
Êä³ö: false
½âÊÍ: ÎŞÂÛÔõÑù£¬Äã×Ü»áµ½´ïË÷ÒıÎª 3 µÄÎ»ÖÃ¡£µ«¸ÃÎ»ÖÃµÄ×î
´óÌøÔ¾³¤¶ÈÊÇ 0 £¬ ËùÒÔÄãÓÀÔ¶²»¿ÉÄÜµ½´ï×îºóÒ»¸öÎ»ÖÃ¡£
*/
bool canJump(int* nums, int numsSize)
{
	int rightmost = 0;

	for (int i = 0; i < numsSize; ++i) {
		if (i <= rightmost) {
			rightmost = fmax(rightmost, i + nums[i]);
			if (rightmost >= numsSize - 1) {
				return true;
			}
		}
	}

	return false;
}

/*
45. ÌøÔ¾ÓÎÏ· II
ÄÑ¶ÈÀ§ÄÑ649
¸ø¶¨Ò»¸ö·Ç¸ºÕûÊıÊı×é£¬Äã×î³õÎ»ÓÚÊı×éµÄµÚÒ»¸öÎ»ÖÃ¡£
Êı×éÖĞµÄÃ¿¸öÔªËØ´ú±íÄãÔÚ¸ÃÎ»ÖÃ¿ÉÒÔÌøÔ¾µÄ×î´ó³¤¶È¡£
ÄãµÄÄ¿±êÊÇÊ¹ÓÃ×îÉÙµÄÌøÔ¾´ÎÊıµ½´ïÊı×éµÄ×îºóÒ»¸öÎ»ÖÃ¡£
Ê¾Àı:
ÊäÈë: [2,3,1,1,4]
Êä³ö: 2
½âÊÍ: Ìøµ½×îºóÒ»¸öÎ»ÖÃµÄ×îĞ¡ÌøÔ¾ÊıÊÇ 2¡£
*/

/*
ÎÒÃÇµÄÄ¿±êÊÇµ½´ïÊı×éµÄ×îºóÒ»¸öÎ»ÖÃ£¬Òò´ËÎÒÃÇ¿ÉÒÔ¿¼ÂÇ×îºóÒ»²½ÌøÔ¾Ç°ËùÔÚµÄÎ»ÖÃ£¬¸ÃÎ»ÖÃÍ¨¹ıÌøÔ¾ÄÜ¹»µ½´ï×îºóÒ»¸öÎ»ÖÃ¡£Èç¹ûÓĞ¶à¸öÎ»ÖÃÍ¨¹ıÌøÔ¾¶¼ÄÜ¹»µ½´ï×îºóÒ»¸öÎ»ÖÃ£¬ÄÇÃ´ÎÒÃÇÓ¦¸ÃÈçºÎ½øĞĞÑ¡ÔñÄØ£¿Ö±¹ÛÉÏÀ´¿´£¬ÎÒÃÇ¿ÉÒÔ¡¸Ì°ĞÄ¡¹µØÑ¡Ôñ¾àÀë×îºóÒ»¸öÎ»ÖÃ×îÔ¶µÄÄÇ¸öÎ»ÖÃ£¬Ò²¾ÍÊÇ¶ÔÓ¦ÏÂ±ê×îĞ¡µÄÄÇ¸öÎ»ÖÃ¡£Òò´Ë£¬ÎÒÃÇ¿ÉÒÔ´Ó×óµ½ÓÒ±éÀúÊı×é£¬Ñ¡ÔñµÚÒ»¸öÂú×ãÒªÇóµÄÎ»ÖÃ¡£ÕÒµ½×îºóÒ»²½ÌøÔ¾Ç°ËùÔÚµÄÎ»ÖÃÖ®ºó£¬ÎÒÃÇ¼ÌĞøÌ°ĞÄµØÑ°ÕÒµ¹ÊıµÚ¶ş²½ÌøÔ¾Ç°ËùÔÚµÄÎ»ÖÃ£¬ÒÔ´ËÀàÍÆ£¬Ö±µ½ÕÒµ½Êı×éµÄ¿ªÊ¼Î»ÖÃ¡£×÷Õß£ºLeetCode-SolutionÁ´½Ó£ºhttps://leetcode-cn.com/problems/jump-game-ii/solution/tiao-yue-you-xi-ii-by-leetcode-solution/À´Ô´£ºÁ¦¿Û£¨LeetCode£©Öø×÷È¨¹é×÷ÕßËùÓĞ¡£ÉÌÒµ×ªÔØÇëÁªÏµ×÷Õß»ñµÃÊÚÈ¨£¬·ÇÉÌÒµ×ªÔØÇë×¢Ã÷³ö´¦¡£
*/
int jump(int* nums, int numsSize)
{
	int position = numsSize - 1;
	int steps = 0;
	while (position > 0) {
		for (int i = 0; i < position; i++) {
			if (i + nums[i] >= position) {
				position = i;
				steps++;
				break;
			}
		}
	}
	return steps;
}

/*
406. ¸ù¾İÉí¸ßÖØ½¨¶ÓÁĞ
ÄÑ¶ÈÖĞµÈ424
¼ÙÉèÓĞ´òÂÒË³ĞòµÄÒ»ÈºÈËÕ¾³ÉÒ»¸ö¶ÓÁĞ¡£ Ã¿¸öÈËÓÉÒ»¸öÕûÊı¶Ô(h, k)±íÊ¾£¬ÆäÖĞhÊÇÕâ¸öÈËµÄÉí¸ß£¬kÊÇÅÅÔÚÕâ¸öÈËÇ°ÃæÇÒÉí¸ß´óÓÚ»òµÈÓÚhµÄÈËÊı¡£ ±àĞ´Ò»¸öËã·¨À´ÖØ½¨Õâ¸ö¶ÓÁĞ¡£
×¢Òâ£º
×ÜÈËÊıÉÙÓÚ1100ÈË¡£
Ê¾Àı
ÊäÈë:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Êä³ö:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int compare(const void *a,const void *b){
    const int* pa = *(const int **)a;
    const int* pb = *(const int **)b;
    return pa[0] == pb[0]?pa[1] - pb[1]:pb[0] - pa[0];
}

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes){
    int **res = NULL;
    res = (int **)malloc(sizeof(int *) * peopleSize);
    int i;
    int pos;
    //for(i = 0;i < peopleSize;i++){
        //res[i] = (int *)malloc(sizeof(int) * 2);
   // }

    qsort(people, peopleSize, sizeof(int *), compare);
    //for(i = 0;i < peopleSize;i++)
        //printf("%d\t%d\n",people[i][0],people[i][1]);
    for(i = 0;i < peopleSize;i++){
        pos = people[i][1];
        //printf("people i1 is %d\n",people[i][1]);
        memmove(&res[pos + 1], &res[pos], (i - pos) *sizeof(int *));
        res[pos] = (int *)malloc(sizeof(int) * 2);
        res[pos][0] = people[i][0];
        res[pos][1] = people[i][1];
    }

    *returnSize = peopleSize;
    *returnColumnSizes = peopleColSize;
    return res;
}

/*
135. ·Ö·¢ÌÇ¹û
ÄÑ¶ÈÀ§ÄÑ239
ÀÏÊ¦Ïë¸øº¢×ÓÃÇ·Ö·¢ÌÇ¹û£¬ÓĞ N ¸öº¢×ÓÕ¾³ÉÁËÒ»ÌõÖ±Ïß£¬ÀÏÊ¦»á¸ù¾İÃ¿¸öº¢×ÓµÄ±íÏÖ£¬Ô¤ÏÈ¸øËûÃÇÆÀ·Ö¡£
ÄãĞèÒª°´ÕÕÒÔÏÂÒªÇó£¬°ïÖúÀÏÊ¦¸øÕâĞ©º¢×Ó·Ö·¢ÌÇ¹û£º
"	Ã¿¸öº¢×ÓÖÁÉÙ·ÖÅäµ½ 1 ¸öÌÇ¹û¡£
"	ÏàÁÚµÄº¢×ÓÖĞ£¬ÆÀ·Ö¸ßµÄº¢×Ó±ØĞë»ñµÃ¸ü¶àµÄÌÇ¹û¡£
ÄÇÃ´ÕâÑùÏÂÀ´£¬ÀÏÊ¦ÖÁÉÙĞèÒª×¼±¸¶àÉÙ¿ÅÌÇ¹ûÄØ£¿
Ê¾Àı 1:
ÊäÈë: [1,0,2]
Êä³ö: 5
½âÊÍ: Äã¿ÉÒÔ·Ö±ğ¸øÕâÈı¸öº¢×Ó·Ö·¢ 2¡¢1¡¢2 ¿ÅÌÇ¹û¡£

*/
int candy(int* ratings, int ratingsSize)
{
        int sum = 0;
        int left2right[ratingsSize];
        int right2left[ratingsSize];
	for (int i = 0; i < ratingsSize; i++) {
		left2right[i] = right2left[i] = 1;
	}

        for (int i = 1; i < ratingsSize; i++) {
            if (ratings[i] > ratings[i - 1]) {
                left2right[i] = left2right[i - 1] + 1;
            }
        }
        for (int i = ratingsSize - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                right2left[i] = right2left[i + 1] + 1;
            }
        }
        for (int i = 0; i < ratingsSize; i++) {
            sum += fmax(left2right[i], right2left[i]);
        }
        return sum;
}

int candy(int* ratings, int ratingsSize)
{
        int candies[ratingsSize];
	for (int i = 0; i < ratingsSize; i++) {
		candies[i] = 1;
	}

        for (int i = 1; i < ratingsSize; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        int sum = candies[ratingsSize - 1];
        for (int i = ratingsSize - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = fmax(candies[i], candies[i + 1] + 1);
            }
            sum += candies[i];
        }
        return sum;
}

/*
452. ÓÃ×îÉÙÊıÁ¿µÄ¼ıÒı±¬ÆøÇò
ÄÑ¶ÈÖĞµÈ162ÊÕ²Ø·ÖÏíÇĞ»»ÎªÓ¢ÎÄ¹Ø×¢·´À¡
ÔÚ¶şÎ¬¿Õ¼äÖĞÓĞĞí¶àÇòĞÎµÄÆøÇò¡£¶ÔÓÚÃ¿¸öÆøÇò£¬Ìá¹©µÄÊäÈëÊÇË®Æ½·½ÏòÉÏ£¬ÆøÇòÖ±¾¶µÄ¿ªÊ¼ºÍ½áÊø×ø±ê¡£ÓÉÓÚËüÊÇË®Æ½µÄ£¬ËùÒÔy×ø±ê²¢²»ÖØÒª£¬Òò´ËÖ»ÒªÖªµÀ¿ªÊ¼ºÍ½áÊøµÄx×ø±ê¾Í×ã¹»ÁË¡£¿ªÊ¼×ø±ê×ÜÊÇĞ¡ÓÚ½áÊø×ø±ê¡£Æ½ÃæÄÚ×î¶à´æÔÚ104¸öÆøÇò¡£
Ò»Ö§¹­¼ı¿ÉÒÔÑØ×ÅxÖá´Ó²»Í¬µãÍêÈ«´¹Ö±µØÉä³ö¡£ÔÚ×ø±êx´¦Éä³öÒ»Ö§¼ı£¬ÈôÓĞÒ»¸öÆøÇòµÄÖ±¾¶µÄ¿ªÊ¼ºÍ½áÊø×ø±êÎª xstart£¬xend£¬ ÇÒÂú×ã  xstart ¡Ü x ¡Ü xend£¬Ôò¸ÃÆøÇò»á±»Òı±¬¡£¿ÉÒÔÉä³öµÄ¹­¼ıµÄÊıÁ¿Ã»ÓĞÏŞÖÆ¡£ ¹­¼ıÒ»µ©±»Éä³öÖ®ºó£¬¿ÉÒÔÎŞÏŞµØÇ°½ø¡£ÎÒÃÇÏëÕÒµ½Ê¹µÃËùÓĞÆøÇòÈ«²¿±»Òı±¬£¬ËùĞèµÄ¹­¼ıµÄ×îĞ¡ÊıÁ¿¡£
Example:
ÊäÈë:
[[10,16], [2,8], [1,6], [7,12]]

Êä³ö:
2

½âÊÍ:
¶ÔÓÚ¸ÃÑùÀı£¬ÎÒÃÇ¿ÉÒÔÔÚx = 6£¨Éä±¬[2,8],[1,6]Á½¸öÆøÇò£©ºÍ x = 11£¨Éä±¬ÁíÍâÁ½¸öÆøÇò£©¡£

*/
int cmp_doublePoint(const void *a, const void *b)
{
	int * aa = *((int **)a);
	int * bb = *((int **)b);

	return aa[1] - bb[1];
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize)
{
    if (pointsSize == 0) return 0;

	qsort(points, pointsSize, sizeof(points[0]), cmp_doublePoint);

    int arrows = 1;
    int xStart, xEnd, firstEnd = points[0][1];
    for (int i = 0; i < pointsSize; i++) {
      xStart = points[i][0];
      xEnd = points[i][1];
      // if the current balloon starts after the end of another one,
      // one needs one more arrow
      if (firstEnd < xStart) {
        arrows++;
        firstEnd = xEnd;
      }
    }
    return arrows;
  }

/*
56. ºÏ²¢Çø¼ä
ÄÑ¶ÈÖĞµÈ545
¸ø³öÒ»¸öÇø¼äµÄ¼¯ºÏ£¬ÇëºÏ²¢ËùÓĞÖØµşµÄÇø¼ä¡£
Ê¾Àı 1:
ÊäÈë: [[1,3],[2,6],[8,10],[15,18]]
Êä³ö: [[1,6],[8,10],[15,18]]
½âÊÍ: Çø¼ä [1,3] ºÍ [2,6] ÖØµş, ½«ËüÃÇºÏ²¢Îª [1,6].
Ê¾Àı 2:
ÊäÈë: [[1,4],[4,5]]
Êä³ö: [[1,5]]
½âÊÍ: Çø¼ä [1,4] ºÍ [4,5] ¿É±»ÊÓÎªÖØµşÇø¼ä¡£

*/
int cmp_doublePoint(const void *a, const void *b)
{
	int **aa = (int **)a;
	int **bb = (int **)b;

	if (aa[0][0] == bb[0][0]) {
		return aa[0][1] - bb[0][1];
	} else {
		return aa[0][0] - bb[0][0];
	}
}
//[[1,3],[2,6],[8,10],[15,18]]
//[[1,4],[4,5]]
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
	int* returnSize, int** returnColumnSizes)
{
	if (intervals == NULL || intervalsSize <= 0 || intervalsColSize == NULL) {
		*returnSize = 0;
		return NULL;
	}

	qsort(intervals, intervalsSize, sizeof(intervals[0]), cmp_doublePoint);
	int **res = (int **)calloc(intervalsSize, sizeof(int *));
	*returnColumnSizes = (int *)calloc(intervalsSize, sizeof(int));
	for (int i = 0; i < intervalsSize; i++) {
		res[i] = (int *)calloc(2, sizeof(int));
		(*returnColumnSizes)[i] = 2;
	}

	res[0][0] = intervals[0][0];
	res[0][1] = intervals[0][1];
	*returnSize = 1;
	for (int i = 1; i < intervalsSize; i++) {
		if (intervals[i][0] > res[*returnSize - 1][1]) {
			res[*returnSize][0] = intervals[i][0];
			res[*returnSize][1] = intervals[i][1];
			(*returnSize)++;
		} else {
			res[*returnSize - 1][1] = fmax(res[*returnSize - 1][1] , intervals[i][1]);
		}
	}

	return res;
}

/*
376. °Ú¶¯ĞòÁĞ
ÄÑ¶ÈÖĞµÈ229ÊÕ²Ø·ÖÏíÇĞ»»ÎªÓ¢ÎÄ¹Ø×¢·´À¡
Èç¹ûÁ¬ĞøÊı×ÖÖ®¼äµÄ²îÑÏ¸ñµØÔÚÕıÊıºÍ¸ºÊıÖ®¼ä½»Ìæ£¬ÔòÊı×ÖĞòÁĞ³ÆÎª°Ú¶¯ĞòÁĞ¡£µÚÒ»¸ö²î£¨Èç¹û´æÔÚµÄ»°£©¿ÉÄÜÊÇÕıÊı»ò¸ºÊı¡£ÉÙÓÚÁ½¸öÔªËØµÄĞòÁĞÒ²ÊÇ°Ú¶¯ĞòÁĞ¡£
ÀıÈç£¬ [1,7,4,9,2,5] ÊÇÒ»¸ö°Ú¶¯ĞòÁĞ£¬ÒòÎª²îÖµ (6,-3,5,-7,3) ÊÇÕı¸º½»Ìæ³öÏÖµÄ¡£Ïà·´, [1,4,7,2,5] ºÍ [1,7,4,5,5] ²»ÊÇ°Ú¶¯ĞòÁĞ£¬µÚÒ»¸öĞòÁĞÊÇÒòÎªËüµÄÇ°Á½¸ö²îÖµ¶¼ÊÇÕıÊı£¬µÚ¶ş¸öĞòÁĞÊÇÒòÎªËüµÄ×îºóÒ»¸ö²îÖµÎªÁã¡£
¸ø¶¨Ò»¸öÕûÊıĞòÁĞ£¬·µ»Ø×÷Îª°Ú¶¯ĞòÁĞµÄ×î³¤×ÓĞòÁĞµÄ³¤¶È¡£ Í¨¹ı´ÓÔ­Ê¼ĞòÁĞÖĞÉ¾³ıÒ»Ğ©£¨Ò²¿ÉÒÔ²»É¾³ı£©ÔªËØÀ´»ñµÃ×ÓĞòÁĞ£¬Ê£ÏÂµÄÔªËØ±£³ÖÆäÔ­Ê¼Ë³Ğò¡£
Ê¾Àı 1:
ÊäÈë: [1,7,4,9,2,5]
Êä³ö: 6
½âÊÍ: Õû¸öĞòÁĞ¾ùÎª°Ú¶¯ĞòÁĞ¡£
Ê¾Àı 2:
ÊäÈë: [1,17,5,10,13,15,10,5,16,8]
Êä³ö: 7
½âÊÍ: Õâ¸öĞòÁĞ°üº¬¼¸¸ö³¤¶ÈÎª 7 °Ú¶¯ĞòÁĞ£¬ÆäÖĞÒ»¸ö¿ÉÎª[1,17,10,13,10,16,8]¡£
Ê¾Àı 3:
ÊäÈë: [1,2,3,4,5,6,7,8,9]
Êä³ö: 2

*/
int calculate(int *nums, int numsSize, int index, bool isUp)
{
        int maxcount = 0;
        for (int i = index + 1; i < numsSize; i++) {
            if ((isUp && nums[i] > nums[index]) || (!isUp && nums[i] < nums[index]))
                maxcount = fmax(maxcount, 1 + calculate(nums, numsSize, i, !isUp));
        }
        return maxcount;
 }

int wiggleMaxLength(int* nums, int numsSize)
{
        if (numsSize < 2)
            return numsSize;
        return 1 + fmax(calculate(nums, numsSize, 0, true), calculate(nums, numsSize, 0, false));
}

int wiggleMaxLength(int* nums, int numsSize)
{
    int down = 1, up = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i - 1])
            up = down + 1;
        else if (nums[i] < nums[i - 1])
            down = up + 1;
    }
    return numsSize == 0 ? 0 : fmax(down, up);
}

/*
738. µ¥µ÷µİÔöµÄÊı×Ö
ÄÑ¶ÈÖĞµÈ65ÊÕ²Ø·ÖÏíÇĞ»»ÎªÓ¢ÎÄ¹Ø×¢·´À¡
¸ø¶¨Ò»¸ö·Ç¸ºÕûÊı N£¬ÕÒ³öĞ¡ÓÚ»òµÈÓÚ N µÄ×î´óµÄÕûÊı£¬Í¬Ê±Õâ¸öÕûÊıĞèÒªÂú×ãÆä¸÷¸öÎ»ÊıÉÏµÄÊı×ÖÊÇµ¥µ÷µİÔö¡£
£¨µ±ÇÒ½öµ±Ã¿¸öÏàÁÚÎ»ÊıÉÏµÄÊı×Ö x ºÍ y Âú×ã x <= y Ê±£¬ÎÒÃÇ³ÆÕâ¸öÕûÊıÊÇµ¥µ÷µİÔöµÄ¡££©
Ê¾Àı 1:
ÊäÈë: N = 10
Êä³ö: 9
Ê¾Àı 2:
ÊäÈë: N = 1234
Êä³ö: 1234

*/

//Ì°ĞÄËã·¨£¬±éÀúÊı×ÖÃ¿Ò»Î»£¬µ±Ç°Î»µÄÊı×Ö±ÈÏÂÒ»Î»µÄÊı×Ö´ó£¬Ôò½«¸ÃÎ»Êı×Ö¼õĞ¡1£¬È»ºóÖ®ºóÎ»µÄÊı×ÖÈ«²¿±äÎª9
int monotoneIncreasingDigits(int N)
{
        char num[1024] = {0};
		sprintf(num, "%d", N);
        int t = strlen(num);
        for(int i=strlen(num)-1;i>=1;i--){
            if(num[i]<num[i-1]){
                t=i;
                num[i-1]--;
            }
        }
        while(t<strlen(num))
            num[t++]='9';

        return atoi(num);
}

//Ì°ĞÄËã·¨£¬±éÀúÊı×ÖÃ¿Ò»Î»£¬µ±Ç°Î»µÄÊı×Ö±ÈÏÂÒ»Î»µÄÊı×Ö´ó£¬Ôò½«¸ÃÎ»Êı×Ö¼õĞ¡1£¬È»ºóÖ®ºóÎ»µÄÊı×ÖÈ«²¿±äÎª9
//Ì°ĞÄËã·¨£¬±éÀúÊı×ÖÃ¿Ò»Î»£¬µ±Ç°Î»µÄÊı×Ö±ÈÏÂÒ»Î»µÄÊı×Ö´ó£¬Ôò½«¸ÃÎ»Êı×Ö¼õĞ¡1£¬È»ºóÖ®ºóÎ»µÄÊı×ÖÈ«²¿±äÎª9
int monotoneIncreasingDigits(int N)
{
        char s[1024] = {0};
	sprintf(s, "%d", N);
        int p=0;
        for(int i=strlen(s)-1;i>=1;i--)
        {
            if(s[i]<s[i-1])
            {
                p=i;
                s[i-1]--;
                while(p<strlen(s))
                {
                    s[p++]='9';
                }
            }
        }
        return atoi(s);
    }

//Ì°ĞÄËã·¨£¬±éÀúÊı×ÖÃ¿Ò»Î»£¬µ±Ç°Î»µÄÊı×Ö±ÈÏÂÒ»Î»µÄÊı×Ö´ó£¬Ôò½«¸ÃÎ»Êı×Ö¼õĞ¡1£¬È»ºóÖ®ºóÎ»µÄÊı×ÖÈ«²¿±äÎª9
//Ì°ĞÄËã·¨£¬±éÀúÊı×ÖÃ¿Ò»Î»£¬µ±Ç°Î»µÄÊı×Ö±ÈÏÂÒ»Î»µÄÊı×Ö´ó£¬Ôò½«¸ÃÎ»Êı×Ö¼õĞ¡1£¬È»ºóÖ®ºóÎ»µÄÊı×ÖÈ«²¿±äÎª9
int monotoneIncreasingDigits(int N)
{
        char s[1024] = {0};
	sprintf(s, "%d", N);
        int p=0;
        for(int i=strlen(s)-1;i>=1;i--)
        {
            if(s[i]<s[i-1])
            {
                p=i;
                s[i-1]--;
                while(p<strlen(s))
                {
                    s[p++]='9';
                }
            }
        }
        return atoi(s);
    }

/*
659. ·Ö¸îÊı×éÎªÁ¬Ğø×ÓĞòÁĞ
¸øÄãÒ»¸ö°´ÉıĞòÅÅĞòµÄÕûÊıÊı×é num£¨¿ÉÄÜ°üº¬ÖØ¸´Êı×Ö£©£¬ÇëÄã½«ËüÃÇ·Ö¸î³ÉÒ»¸ö»ò¶à¸ö×ÓĞòÁĞ£¬ÆäÖĞÃ¿¸ö×ÓĞòÁĞ¶¼ÓÉÁ¬ĞøÕûÊı×é³ÉÇÒ³¤¶ÈÖÁÉÙÎª 3 ¡£

Èç¹û¿ÉÒÔÍê³ÉÉÏÊö·Ö¸î£¬Ôò·µ»Ø true £»·ñÔò£¬·µ»Ø false ¡£



Ê¾Àı 1£º

ÊäÈë: [1,2,3,3,4,5]
Êä³ö: True
½âÊÍ:
Äã¿ÉÒÔ·Ö¸î³öÕâÑùÁ½¸öÁ¬Ğø×ÓĞòÁĞ :
1, 2, 3
3, 4, 5
*/
int nc[10000];
int tail[10002];
bool isPossible(int* nums, int numsSize){
    int i, pos;
    int base = 0;
    memset(nc, 0, sizeof(nc));
    memset(tail, 0, sizeof(tail));
    if (nums[0] < 0) {
        base = abs(nums[0]);
    }
    for (i = 0; i < numsSize; i++) {
        pos = base + nums[i];
        nc[pos]++;
    }

    for (i = 0; i < numsSize; i++) {
        pos = base + nums[i];
        if (nc[pos] == 0) {
            continue;
        } else if (pos > 0 && nc[pos] > 0 && tail[pos-1] > 0) {
            nc[pos]--;
            tail[pos-1]--;
            tail[pos]++;
        } else if (nc[pos] > 0 && nc[pos+1] > 0 && nc[pos+2] > 0) {
            nc[pos]--;
            nc[pos+1]--;
            nc[pos+2]--;
            tail[pos+2]++;
        } else {
            return false;
        }
    }
    return true;
}