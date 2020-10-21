
/*
Interval Scheduling Çø¼äµ÷¶ÈÎÊÌâ
Ì°ĞÄËã·¨Ò»°ãÓÃÀ´½â¾öĞèÒª ¡°ÕÒµ½Òª×öÄ³ÊÂµÄ×îĞ¡ÊıÁ¿¡±
»ò ¡°ÕÒµ½ÔÚÄ³Ğ©Çé¿öÏÂÊÊºÏµÄ×î´óÎïÆ·ÊıÁ¿¡± µÄÎÊÌâ£¬
ÇÒÌá¹©µÄÊÇÎŞĞòµÄÊäÈë¡£
1) ÅÅĞò(ºÜ¶à³¡¾°)
2) µü´ú

*/

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

/*
358. K ¾àÀë¼ä¸ôÖØÅÅ×Ö·û´®
¸øÄãÒ»¸ö·Ç¿ÕµÄ×Ö·û´® s ºÍÒ»¸öÕûÊı k£¬ÄãÒª½«Õâ¸ö×Ö·û´®ÖĞµÄ×ÖÄ¸½øĞĞÖØĞÂÅÅÁĞ£¬Ê¹µÃÖØÅÅºóµÄ×Ö·û´®ÖĞÏàÍ¬×ÖÄ¸µÄÎ»ÖÃ¼ä¸ô¾àÀëÖÁÉÙÎª k¡£

ËùÓĞÊäÈëµÄ×Ö·û´®¶¼ÓÉĞ¡Ğ´×ÖÄ¸×é³É£¬Èç¹ûÕÒ²»µ½¾àÀëÖÁÉÙÎª k µÄÖØÅÅ½á¹û£¬Çë·µ»ØÒ»¸ö¿Õ×Ö·û´® ""¡£

Ê¾Àı 1£º

ÊäÈë: s = "aabbcc", k = 3
Êä³ö: "abcabc"
½âÊÍ: ÏàÍ¬µÄ×ÖÄ¸ÔÚĞÂµÄ×Ö·û´®ÖĞ¼ä¸ôÖÁÉÙ 3 ¸öµ¥Î»¾àÀë¡£
Ê¾Àı 2:

ÊäÈë: s = "aaabc", k = 3
Êä³ö: ""
½âÊÍ: Ã»ÓĞ°ì·¨ÕÒµ½¿ÉÄÜµÄÖØÅÅ½á¹û¡£
*/
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

typedef struct letterCnt {
    int letterVal;
    int letterCnt;
    int prePos;
}LETTER_CNT;

char findNextChar(LETTER_CNT *letterCnt, int curPos, int k)
{
    char nextChar = 0;
    int i = 0;
    for (; i < 27; i++) {
        if (letterCnt[i].letterCnt == 0) {
            continue;
        }

        if (letterCnt[i].prePos == -1  ||  (curPos - letterCnt[i].prePos) >= k) {
            letterCnt[i].prePos = curPos;
            letterCnt[i].letterCnt -= 1;
            nextChar =  letterCnt[i].letterVal;
            break;
        }
    }

    return nextChar;
}
int compareLetterCnt(const void *elm1, const void *elm2) {
    return ((LETTER_CNT *)elm2)->letterCnt - ((LETTER_CNT *)elm1)->letterCnt;
}

char * rearrangeString(char * s, int k)
{
    LETTER_CNT letterCnt[27] = { 0 };
    int letterPrePos[27] = { 0 };
    int maxDupLetter = 0;

    if (s == NULL) {
        return "";
    }

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        letterCnt[s[i] - 'a'].letterVal = s[i];
        letterCnt[s[i] - 'a'].letterCnt += 1;
        letterCnt[s[i] - 'a'].prePos = -1;
        maxDupLetter = MAX(maxDupLetter, letterCnt[s[i] - 'a'].letterCnt);
    }

    if ((maxDupLetter - 1) * k + 1 > len) {
        return "";
    }

    qsort(letterCnt, 27, sizeof(LETTER_CNT),  compareLetterCnt);

    char *pNewStr = (char *)malloc(len + 1);
    memset(pNewStr, 0, len + 1);
    int i  = 0;
    for (i = 0; i < len; i++) {
        char c  =  findNextChar(letterCnt, i, k);
        qsort(letterCnt, 27, sizeof(LETTER_CNT),  compareLetterCnt); // È¡ÍêÖØĞÂÅÅĞòÒ»ÏÂ ±£Ö¤ÓÅÏÈÈ¡×î¶àµÄ×Ö·û
        if (c == 0) {
            break;
        }
        pNewStr[i] = c;
    }

    if (i != len) {
        free(pNewStr);
        return "";
    }

    return pNewStr;
}

/*
502. IPO
¼ÙÉè Á¦¿Û£¨LeetCode£©¼´½«¿ªÊ¼Æä IPO¡£ÎªÁËÒÔ¸ü¸ßµÄ¼Û¸ñ½«¹ÉÆ±Âô¸ø·çÏÕÍ¶×Ê¹«Ë¾£¬Á¦¿Û Ï£ÍûÔÚ IPO Ö®Ç°¿ªÕ¹Ò»Ğ©ÏîÄ¿ÒÔÔö¼ÓÆä×Ê±¾¡£ ÓÉÓÚ×ÊÔ´ÓĞÏŞ£¬ËüÖ»ÄÜÔÚ IPO Ö®Ç°Íê³É×î¶à k ¸ö²»Í¬µÄÏîÄ¿¡£°ïÖú Á¦¿Û Éè¼ÆÍê³É×î¶à k ¸ö²»Í¬ÏîÄ¿ºóµÃµ½×î´ó×Ü×Ê±¾µÄ·½Ê½¡£

¸ø¶¨Èô¸É¸öÏîÄ¿¡£¶ÔÓÚÃ¿¸öÏîÄ¿ i£¬Ëü¶¼ÓĞÒ»¸ö´¿ÀûÈó Pi£¬²¢ÇÒĞèÒª×îĞ¡µÄ×Ê±¾ Ci À´Æô¶¯ÏàÓ¦µÄÏîÄ¿¡£×î³õ£¬ÄãÓĞ W ×Ê±¾¡£µ±ÄãÍê³ÉÒ»¸öÏîÄ¿Ê±£¬Äã½«»ñµÃ´¿ÀûÈó£¬ÇÒÀûÈó½«±»Ìí¼Óµ½ÄãµÄ×Ü×Ê±¾ÖĞ¡£

×Ü¶øÑÔÖ®£¬´Ó¸ø¶¨ÏîÄ¿ÖĞÑ¡Ôñ×î¶à k ¸ö²»Í¬ÏîÄ¿µÄÁĞ±í£¬ÒÔ×î´ó»¯×îÖÕ×Ê±¾£¬²¢Êä³ö×îÖÕ¿É»ñµÃµÄ×î¶à×Ê±¾¡£

Ê¾Àı 1:

ÊäÈë: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

Êä³ö: 4

½âÊÍ:
ÓÉÓÚÄãµÄ³õÊ¼×Ê±¾Îª 0£¬Äã¾¡¿ÉÒÔ´Ó 0 ºÅÏîÄ¿¿ªÊ¼¡£
ÔÚÍê³Éºó£¬Äã½«»ñµÃ 1 µÄÀûÈó£¬ÄãµÄ×Ü×Ê±¾½«±äÎª 1¡£
´ËÊ±Äã¿ÉÒÔÑ¡Ôñ¿ªÊ¼ 1 ºÅ»ò 2 ºÅÏîÄ¿¡£
ÓÉÓÚÄã×î¶à¿ÉÒÔÑ¡ÔñÁ½¸öÏîÄ¿£¬ËùÒÔÄãĞèÒªÍê³É 2 ºÅÏîÄ¿ÒÔ»ñµÃ×î´óµÄ×Ê±¾¡£
Òò´Ë£¬Êä³ö×îºó×î´ó»¯µÄ×Ê±¾£¬Îª 0 + 1 + 3 = 4¡£
*/
typedef struct {
	int p; // profit
	int c; // capital
} node_t;

typedef int (*cmp_fn)(const void *,const void *);

int cmpc(const void*a, const void*b)
{ // ¶Ô³É±¾cost½øĞĞÅÅĞò£¬´ÓĞ¡µ½´ó
	node_t* n1 = (node_t*)a;
	node_t* n2 = (node_t*)b;
	return (n1->c - n2->c);
}

int cmpp(const void*a, const void*b)
{ // ¶ÔÊÕÒæprofit½øĞĞÅÅĞò£¬´ÓĞ¡µ½´ó£¬´ó¶¥¶Ñ
	node_t* n1 = (node_t*)a;
	node_t* n2 = (node_t*)b;
	return (n1->p - n2->p);
}

void swap(node_t *a, node_t *b)
{ // ½»»»Á½¸öÔªËØ
    node_t t = *a;
    *a = *b;
    *b = t;
}

bool HeadNodeDown(node_t *a, int n, cmp_fn cmp, int i)
{ // ½ÚµãÔªËØi½øĞĞÏÂ³Á
    if (a == NULL || n < 0 || i > n ) {
        return false;
    }
	int dad = i; // ·ÇÒ¶×Ó½Úµã£¬¼´¸¸½ÚµãµÄ±àºÅ
    int k = n / 2 - 1; // ·ÇÒ¶×Ó½ÚµãµÄ×î´óÎ»ÖÃ
	while (dad <= k) { // ¸¸½Úµã£¬ÈÔÈ»ÊÇ·ÇÒ¶×Ó½Úµã
		int son = dad * 2 + 1; // ×ó×Ó½ÚµãµÄ±àºÅ
		if (son + 1 < n && cmp(&a[son], &a[son + 1]) < 0) {
		    son = son + 1;  // ÓÒ×Ó½Úµã¸ü´ó£¬Ñ¡ÓÒ±ß
		}
		if (cmp(&a[son], &a[dad]) <= 0) { // ×Ó½Úµã¶¼±È½ÏĞ¡
		    break; // ²»ÓÃÔÙÏÂ³ÁÁË
		}
		swap(&a[son], &a[dad]);
		dad = son;
	}
    return true;
}

bool HeadNodeUp(node_t *a, int n, cmp_fn cmp, int i)
{ // ½ÚµãÔªËØi½øĞĞÉÏ¸¡
    if (a == NULL || n < 0 || i > n ) {
        return false;
    }
	int son = i; // Ò¶×Ó½Úµã£¬¼´×Ó½ÚµãµÄ±àºÅ
	while (son > 0) { // ×Ó½Úµã£¬ÈÔÈ»ÊÇÕı³£½Úµã
		int dad = (son - 1) / 2; // ¸¸½ÚµãµÄ±àºÅ
		if (cmp(&a[son], &a[dad]) <= 0) { // ×Ó½Úµã±È½ÏĞ¡
		    break; // ²»ÓÃÔÙÉÏ¸¡ÁË
		}
		swap(&a[son], &a[dad]);
		son = dad;
	}
    return true;
}

bool HeadNodePush(node_t *a, int *n, cmp_fn cmp, node_t *t)
{ // ÔÚ¶ÑÖĞÑ¹ÈëÒ»¸ö½ÚµãÔªËØ£¬´ÓÎ²²¿Ìí¼Ó
	if (a == NULL || n == NULL || *n < 0 || t == NULL) {
        return false;
    }
	a[*n] = *t;
    (*n)++;
    HeadNodeUp(a, *n, cmp, *n-1);
    return true;
}

bool HeadNodePop(node_t *a, int *n, cmp_fn cmp, node_t *t)
{ // ÔÚ¶ÑÖĞµ¯³öÒ»¸ö½ÚµãÔªËØ£¬´Ó¶¥²¿µ¯³ö
	if (a == NULL || n == NULL || *n < 0 || t == NULL) {
        return false;
    }
    swap(&a[0], &a[*n - 1]);
    *t = a[*n - 1];
    memset(&a[*n - 1], 0, sizeof(node_t));
    (*n)--;
    HeadNodeDown(a, *n, cmp, 0);
    return true;
}

bool HeadCreate(node_t *a, int n, cmp_fn cmp)
{ // ¶ÑµÄ·ÇÒ¶×Ó½ÚµãµÄµ÷Õû
    if (a == NULL || n < 0) {
        return false;
    }
    int k = n / 2 - 1; // ·ÇÒ¶×Ó½ÚµãµÄ×î´óÎ»ÖÃ
    for (int i = k; i >= 0; i--) { // ±éÀúËùÓĞ·ÇÒ¶×Ó½Úµã
    	HeadNodeDown(a, n, cmp, i); // Öğ¸öÅĞ¶ÏÊÇ·ñ¿ÉÒÔÏÂ³Á
    }
    return true;
}

bool HeapSort(node_t *a, int n)
{ // ¶ÑÅÅĞò£¬´ó¶¥¶Ñ£¬´ÓĞ¡µ½´ó
    if (a == NULL || n < 0) {
        return false;
    }
    for (int i = n; i > 0; i--) {
        HeadCreate(a, i, cmpp);
        swap(&a[0], &a[i - 1]);
    }
    return true;
}

int gd(int k, int w, node_t*a, int n)
{ // Ì°ĞÄgreedyËã·¨£¬Ã¿´Î¶¼Ñ¡ÔñÊÕÒæ×î´óµÄÄÇ¸ö
    if (k == 0 || w < 0 || a == NULL || n <= 0) {
        return 0;
    }
    node_t c[n];
    memset(c, 0, sizeof(c));
	qsort(a, n, sizeof(node_t), cmpc);
	for (int ai = 0, ci = 0; k > 0; k--) {
		while (ai < n && a[ai].c <= w) { // ¶¼¿ÉÑ¡
			HeadNodePush(c, &ci, cmpp, &a[ai]);
			ai++;
		}
		if (ci > 0) { // »¹ÓĞÔªËØ¿ÉÑ¡
			node_t t; // ÁÙÊ±±äÁ¿
			HeadNodePop(c, &ci, cmpp, &t);
			w += t.p;
		}
	}
    return w;
}

int findMaximizedCapital(int k, int w, int*p, int pn, int*c, int cn)
{
    if (k == 0 || w < 0 || p == NULL || pn <= 0 || c == NULL || cn <= 0) {
        return 0;
    }
    node_t a[pn];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < pn; i++) {
    	a[i].p = p[i];
    	a[i].c = c[i];
	}
    return gd(k, w, a, pn);
}