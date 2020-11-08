/*¿ÆÑ§¼ÆÊı·¨
1e-6
*/

/*ÅĞ¶ÏÁ½¸öÊıÊÇ·ñÒìºÅ*/
int x = -1, y = 2;
bool f = ((x ^ y) < 0); // true

int x = 3, y = 2;
bool f = ((x ^ y) < 0); // false

int abs(int);
double fabs(double x);

/* sqrt() ÓÃÀ´Çó¸ø¶¨ÖµµÄÆ½·½¸ù */
double sqrt(double x);
/*pow() º¯ÊıÓÃÀ´Çó x µÄ y ´ÎÃİ£¨´Î·½£©*/
double pow(double x, double y);

void num(void)
{
	if (isdigit(s[i])) {
		num = num * 10 + s[i] - '0';
	}
}

/*
1010. ×Ü³ÖĞøÊ±¼ä¿É±» 60 Õû³ıµÄ¸èÇú
ÔÚ¸èÇúÁĞ±íÖĞ£¬µÚ i Ê×¸èÇúµÄ³ÖĞøÊ±¼äÎª time[i] Ãë¡£
·µ»ØÆä×Ü³ÖĞøÊ±¼ä£¨ÒÔÃëÎªµ¥Î»£©¿É±» 60 Õû³ıµÄ¸èÇú¶ÔµÄÊıÁ¿¡£
ĞÎÊ½ÉÏ£¬ÎÒÃÇÏ£ÍûË÷ÒıµÄÊı×Ö  i < j ÇÒÓĞ (time[i] + time[j]) % 60 == 0¡£
1 <= time[i] <= 500

Ê¾Àı 1£º
ÊäÈë£º[30,20,150,100,40]
Êä³ö£º3
½âÊÍ£ºÕâÈı¶ÔµÄ×Ü³ÖĞøÊ±¼ä¿É±» 60 ÕûÊı£º
(time[0] = 30, time[2] = 150): ×Ü³ÖĞøÊ±¼ä 180
(time[1] = 20, time[3] = 100): ×Ü³ÖĞøÊ±¼ä 120
(time[1] = 20, time[4] = 40): ×Ü³ÖĞøÊ±¼ä 60

1)Ê×ÏÈËùÓĞ¶ÔÏó%60
2)×éºÏµÄ¿ÉÄÜĞÔ
*/
int numPairsDivisibleBy60(int* time, int timeSize)
{
	int result = 0;
	int mod[60];

	memset((void*)mod, 0, sizeof(mod));
	for(int i = 0; i < timeSize; i++) {
		mod[time[i] % 60]++;
	}

	for (int i = 1; i < 30; i++) {
		result += mod[i] * mod[60 - i];
	}

	result += (mod[0] * (mod[0] - 1) + mod[30] * (mod[30] - 1)) / 2;

	return result;
}

/*
ÊıÑ§¶¨Àí:

1)
Èç¹ûÒ»¸öÊı×éºÍ´óÓÚ0
ÁîÆä×÷Îª»·ĞÎ£¬ÄÇÃ´Ò»¶¨¿ÉÒÔÕÒµ½Ò»¸öÆğµã£¬
´Ó´ËÆğµã¿ªÊ¼×ªÒ»È¦£¨±éÀú£©£¬Á¬ĞøºÍ´óÓÚÁã
*/

/*
60. µÚk¸öÅÅÁĞ
¸ø³ö¼¯ºÏ [1,2,3,¡­,n]£¬ÆäËùÓĞÔªËØ¹²ÓĞ n! ÖÖÅÅÁĞ¡£
°´´óĞ¡Ë³ĞòÁĞ³öËùÓĞÅÅÁĞÇé¿ö£¬²¢Ò»Ò»±ê¼Ç£¬
µ± n = 3 Ê±, ËùÓĞÅÅÁĞÈçÏÂ£º
"123"
"132"
"213"
"231"
"312"
"321"
¸ø¶¨ n ºÍ k£¬·µ»ØµÚ k ¸öÅÅÁĞ¡£
ËµÃ÷£º
¸ø¶¨ n µÄ·¶Î§ÊÇ [1, 9]¡£
¸ø¶¨ k µÄ·¶Î§ÊÇ[1,  n!]¡£
Ê¾Àı 1:
ÊäÈë: n = 3, k = 3
Êä³ö: "213"
*/

/*
ÀıÈç£º n = 6, k = 373
³õÊ¼»¯Êı×é nums = [1, 2, 3, 4, 5, 6];
Ê×ÏÈÓ¦¸ÃÃ÷°×£¬ÒÔ 1 ¿ªÍ·µÄÈ«ÅÅÁĞÓĞ 5! ¸ö£¬
ÒÔ 2 ¿ªÍ·µÄÈ«ÅÅÁĞÓĞ 5! ¸ö ¡­¡­
¹² 5! * 6 = 6! ¸ö£»
¹Ê k = 373 Ê±£¬
È«ÅÅÁĞµÄµÚÒ»¸öÊı×ÖÓ¦¸ÃÊÇ nums[ k / 5! ] = 4 ;
Êı×éÉ¾³ı 4, ´ËÊ± nums = [1, 2, 3, 5, 6]; k %= 5! = 12 ;
½ÓÏÂÀ´¾ÍÊÇÔÚ nums ÖĞÕÒµÚ 12 ¸öÈ«ÅÅÁĞ£¬ÖØ¸´ 1£¬2 ²½¼´¿É ¡£
*/

//½×³Ë(n!)
int factorial(int n)
{
	int num = 1;
	while (n > 0)
		num *= n--;
	return num;
}


void deleteItem(int *nums, int pos, int moveSize)
{
	while (pos < moveSize - 1)
		nums[pos++] = nums[pos + 1];
}

char *getPermutation(int n, int k)
{
	int i, j = 0, nums[n], factor;
	char *res = (char *)calloc(10, sizeof(char));

	for (i = 0; i < n; i++)  //³õÊ¼»¯Ò»¸ö [1,2,3,¡­¡­,n] Êı×é
		nums[i] = i + 1;
	for (i = 0, k--; i < n; i++) {  //kÒªÏÈ¼õÈ¥1   ¸ø¶¨ k µÄ·¶Î§ÊÇ[1,  n!]¡£
		factor = factorial(n - i - 1);
		res[j++] = nums[k  / factor] + '0';
		deleteItem(nums, k / factor, n - i);  //È¡³öÒ»¸öÔªËØ
		k %= factor;
	}
	return res;
}

/*
LCP 03. »úÆ÷ÈË´óÃ°ÏÕ
Á¦¿ÛÍÅ¶ÓÂòÁËÒ»¸ö¿É±à³Ì»úÆ÷ÈË£¬
»úÆ÷ÈË³õÊ¼Î»ÖÃÔÚÔ­µã(0, 0)¡£Ğ¡»ï°éÊÂÏÈ¸ø»úÆ÷ÈËÊäÈëÒ»´®Ö¸
Áîcommand£¬»úÆ÷ÈË¾Í»áÎŞÏŞÑ­»·ÕâÌõÖ¸ÁîµÄ²½Öè½øĞĞÒÆ¶¯¡£
Ö¸ÁîÓĞÁ½ÖÖ£º
U: ÏòyÖáÕı·½ÏòÒÆ¶¯Ò»¸ñ
R: ÏòxÖáÕı·½ÏòÒÆ¶¯Ò»¸ñ¡£
²»ĞÒµÄÊÇ£¬ÔÚ xy Æ½ÃæÉÏ»¹ÓĞÒ»Ğ©ÕÏ°­Îï£¬
ËûÃÇµÄ×ø±êÓÃobstacles±íÊ¾¡£»úÆ÷ÈËÒ»µ©Åöµ½ÕÏ°­Îï¾Í»á±»Ëğ»Ù¡£
¸ø¶¨ÖÕµã×ø±ê(x, y)£¬·µ»Ø»úÆ÷ÈËÄÜ·ñÍêºÃµØµ½´ïÖÕµã¡£
Èç¹ûÄÜ£¬·µ»Øtrue£»·ñÔò·µ»Øfalse¡
Ê¾Àı 1£º

ÊäÈë£ºcommand = "URR", obstacles = [], x = 3, y = 2
Êä³ö£ºtrue
½âÊÍ£ºU(0, 1) -> R(1, 1) -> R(2, 1) -> U(2, 2) -> R(3, 2)¡£
Ê¾Àı 2£º

ÊäÈë£ºcommand = "URR", obstacles = [[2, 2]], x = 3, y = 2
Êä³ö£ºfalse
½âÊÍ£º»úÆ÷ÈËÔÚµ½´ïÖÕµãÇ°»áÅöµ½(2, 2)µÄÕÏ°­Îï¡£

*/
void lower(int *x, int *y, int numR, int numU)
{
	int p1 = *x /numR;
	int p2 = *y /numU;
	int min = p1 > p2 ? p2 : p1;
	*x = *x - min * numR;
	*y = *y - min * numU;
}

bool isOk(char * command, int newCntR, int newCntU)
{
	int i=0;
	while(newCntR>=0 && newCntU>=0) {
		if(newCntR==0&&newCntU==0)
			return true;
		if(*(command+i)=='U') {
			newCntU--;
		}else  {
			newCntR--;
		}
		i++;
	}

	if(newCntR==0&&newCntU==0)
	return true;
		else
	return false;
}

bool robot(char * command, int** obstacles, int obstaclesSize, int* obstaclesColSize, int x, int y)
{
	int newCntR = x, newCntU = y;
	int numU=0,numR=0;

	for(int i=0; i<strlen(command); i++) {
		if(*(command+i)=='U') {
			numU++;
		}else{
			numR++;
		}
	}

	lower(&newCntR,&newCntU,numR,numU);
	if(!isOk(command,newCntR,newCntU))
		return false;

	for(int i=0; i<obstaclesSize; i++) {
		if(obstacles[i][0]>x||obstacles[i][1]>y)
			continue;
		newCntR=obstacles[i][0];
		newCntU=obstacles[i][1];

		lower(&newCntR,&newCntU,numR,numU);
		if(isOk(command,newCntR,newCntU))
			return false;
	}

	return true;
}


/*
313. ³¬¼¶³óÊı
ÄÑ¶ÈÖĞµÈ80
±àĞ´Ò»¶Î³ÌĞòÀ´²éÕÒµÚ n ¸ö³¬¼¶³óÊı¡£
³¬¼¶³óÊıÊÇÖ¸ÆäËùÓĞÖÊÒòÊı¶¼ÊÇ³¤¶ÈÎª k µÄÖÊÊıÁĞ±í primes ÖĞµÄÕıÕûÊı¡£
Ê¾Àı:
ÊäÈë: n = 12, primes = [2,7,13,19]
Êä³ö: 32
½âÊÍ: ¸ø¶¨³¤¶ÈÎª 4 µÄÖÊÊıÁĞ±í primes = [2,7,13,19]£¬Ç° 12 ¸ö³¬¼¶³óÊıĞòÁĞÎª£º[1,2,4,7,8,13,14,16,19,26,28,32] ¡£
ËµÃ÷:
"	1 ÊÇÈÎºÎ¸ø¶¨ primes µÄ³¬¼¶³óÊı¡£
"	 ¸ø¶¨ primes ÖĞµÄÊı×ÖÒÔÉıĞòÅÅÁĞ¡£
"	0 < k ¡Ü 100, 0 < n ¡Ü 106, 0 < primes[i] < 1000 ¡£
*/

/*
 * @lc app=leetcode.cn id=313 lang=c
 *
 * [313] ³¬¼¶³óÊı
 */
int nthSuperUglyNumber(int n, int* primes, int primesSize)
{
	if(n == 1) {
		return 1;
	}

	int *res = (int *)calloc(n, sizeof(int));
	int rsize = 0;

	int *pids = (int *)calloc(primesSize, sizeof(int));

	res[rsize++] = 1;

	while(rsize < n) {
		// Ñ¡Ôñ×îĞ¡µÄ(ËØÊı*res[pid])£¬¸üĞÂÆäpid
		int min = INT_MAX;
		int id = 0;

		for(int i = 0; i < primesSize; i++) {
			int tmin = primes[i] * res[ pids[i] ];

			if(tmin < min) {
				min = tmin;
				id = i;
			} else if(tmin == min){
				pids[i]++; // È¥³ıÖØ¸´
			}
		}

		res[rsize++] = min;
		pids[id]++;
	}

	return res[n - 1];
}

/*
1371. Ã¿¸öÔªÒô°üº¬Å¼Êı´ÎµÄ×î³¤×Ó×Ö·û´®
ÄÑ¶ÈÖĞµÈ245
¸øÄãÒ»¸ö×Ö·û´® s £¬ÇëÄã·µ»ØÂú×ãÒÔÏÂÌõ¼şµÄ×î³¤×Ó×Ö·û´®µÄ
³¤¶È£ºÃ¿¸öÔªÒô×ÖÄ¸£¬¼´ 'a'£¬'e'£¬'i'£¬'o'£¬'u' £¬ÔÚ×Ó×Ö·û´®ÖĞ¶¼Ç¡
ºÃ³öÏÖÁËÅ¼Êı´Î¡£

Ê¾Àı 1£º
ÊäÈë£ºs = "eleetminicoworoep"
Êä³ö£º13
½âÊÍ£º×î³¤×Ó×Ö·û´®ÊÇ "leetminicowor" £¬Ëü°üº¬ e£¬i£¬o ¸÷ 2 ¸ö£¬ÒÔ
¼° 0 ¸ö a£¬u ¡£
Ê¾Àı 2£º
ÊäÈë£ºs = "leetcodeisgreat"
Êä³ö£º5
½âÊÍ£º×î³¤×Ó×Ö·û´®ÊÇ "leetc" £¬ÆäÖĞ°üº¬ 2 ¸ö e ¡£
Ê¾Àı 3£º
ÊäÈë£ºs = "bcbcbc"
Êä³ö£º6
½âÊÍ£ºÕâ¸öÊ¾ÀıÖĞ£¬×Ö·û´® "bcbcbc" ±¾Éí¾ÍÊÇ×î³¤µÄ£¬ÒòÎªËùÓĞ
µÄÔªÒô a£¬e£¬i£¬o£¬u ¶¼³ö
*/
/*
0 ´ú±í³öÏÖÁËÅ¼Êı´Î£¬1 ´ú±í³öÏÖÁËÆæÊı´Î
00000 ~ 11111 Ò»¹²2^5£¬32ÖĞ×´Ì¬£¬0±íÊ¾³öÏÖÅ¼Êı£¬1±íÊ¾³öÏÖÆæÊı
*/
int findTheLongestSubstring(char * s)
{
	int n = strlen(s);
	int pos[32] = {-1};
	int status = 0;
	int ans = 0;

	for (int i = 0; i < 32; i++) {
		pos[i] = -1;
	}

	pos[0] = 0;

	for (int i = 0; i < n; i ++) {
            if (s[i] == 'a') {
                status ^= 1<<0;
            } else if (s[i] == 'e') {
                status ^= 1<<1;
            } else if (s[i] == 'i') {
                status ^= 1<<2;
            } else if (s[i] == 'o') {
                status ^= 1<<3;
            } else if (s[i] == 'u') {
                status ^= 1<<4;
            }
            if (pos[status] != -1) {
                ans = fmax(ans, i + 1 - pos[status]);
            } else {
                pos[status] = i + 1;
            }
	}

        return ans;
}

/*
1296. »®·ÖÊı×éÎªÁ¬ĞøÊı×ÖµÄ¼¯ºÏ
ÄÑ¶ÈÖĞµÈ25
¸øÄãÒ»¸öÕûÊıÊı×é nums ºÍÒ»¸öÕıÕûÊı k£¬ÇëÄãÅĞ¶ÏÊÇ·ñ¿ÉÒÔ°Ñ
Õâ¸öÊı×é»®·Ö³ÉÒ»Ğ©ÓÉ k ¸öÁ¬ĞøÊı×Ö×é³ÉµÄ¼¯ºÏ¡£
Èç¹û¿ÉÒÔ£¬Çë·µ»Ø True£»·ñÔò£¬·µ»Ø False¡£

Ê¾Àı 1£º
ÊäÈë£ºnums = [1,2,3,3,4,4,5,6], k = 4
Êä³ö£ºtrue
½âÊÍ£ºÊı×é¿ÉÒÔ·Ö³É [1,2,3,4] ºÍ [3,4,5,6]¡£

*/
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
bool isPossibleDivide(int* nums, int numsSize, int k){
    int min, cnt, j;
    if (numsSize % k != 0) {
        return false;
    }
    qsort(nums, numsSize, sizeof(int), cmp);
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            min = nums[i];
            cnt = 0;
            for (j = i; (j < numsSize) && (cnt < k); j++) {
                if (nums[j] == min){
                    cnt++;
                    min++;
                    nums[j] = 0;
                }
            }
            if (cnt < k) {
                return false;
            }
        }
    }
    return true;
}

/*
442. Êı×éÖĞÖØ¸´µÄÊı¾İ
ÄÑ¶ÈÖĞµÈ205
¸ø¶¨Ò»¸öÕûÊıÊı×é a£¬ÆäÖĞ1 ¡Ü a[i] ¡Ü n £¨nÎªÊı×é³¤¶È£©, ÆäÖĞÓĞ
Ğ©ÔªËØ³öÏÖÁ½´Î¶øÆäËûÔªËØ³öÏÖÒ»´Î¡£
ÕÒµ½ËùÓĞ³öÏÖÁ½´ÎµÄÔªËØ¡£
Äã¿ÉÒÔ²»ÓÃµ½ÈÎºÎ¶îÍâ¿Õ¼ä²¢ÔÚO(n)Ê±¼ä¸´ÔÓ¶ÈÄÚ½â¾öÕâ¸ö
ÎÊÌâÂğ£¿
Ê¾Àı£º
ÊäÈë:
[4,3,2,7,8,2,3,1]

Êä³ö:
[2,3]

*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDuplicates(int* nums, int numsSize, int* returnSize)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);

	int *res = (int *)calloc(numsSize, sizeof(int));
	*returnSize = 0;
	if (numsSize <= 1)
		return res;

	for(int i = 0; i < numsSize - 1; i++) {
		if (nums[i] == nums[i + 1]) {
			res[*returnSize] = nums[i];
			(*returnSize)++;
			i++;
		}
	}

	return res;
}

/*
ÃæÊÔÌâ 16.11. ÌøË®°å
ÄãÕıÔÚÊ¹ÓÃÒ»¶ÑÄ¾°å½¨ÔìÌøË®°å¡£ÓĞÁ½ÖÖÀàĞÍµÄÄ¾°å£¬ÆäÖĞ³¤¶È½Ï¶ÌµÄÄ¾°å³¤¶ÈÎªshorter£¬³¤¶È½Ï³¤µÄÄ¾°å³¤¶ÈÎªlonger¡£Äã±ØĞëÕıºÃÊ¹ÓÃk¿éÄ¾°å¡£±àĞ´Ò»¸ö·½·¨£¬Éú³ÉÌøË®°åËùÓĞ¿ÉÄÜµÄ³¤¶È¡£

·µ»ØµÄ³¤¶ÈĞèÒª´ÓĞ¡µ½´óÅÅÁĞ¡£

Ê¾Àı 1

ÊäÈë£º
shorter = 1
longer = 2
k = 3
Êä³ö£º [3,4,5,6]
½âÊÍ£º
¿ÉÒÔÊ¹ÓÃ 3 ´Î shorter£¬µÃµ½½á¹û 3£»Ê¹ÓÃ 2 ´Î shorter ºÍ 1 ´Î longer£¬µÃµ½½á¹û 4 ¡£ÒÔ´ËÀàÍÆ£¬µÃµ½×îÖÕ½á¹û¡£
*/

int* divingBoard(int shorter, int longer, int k, int* returnSize) {
    if (k == 0) {
        *returnSize = 0;
        return NULL;
    }
    if (shorter == longer) {
        int* p = (int*)malloc(sizeof(int));
        *p = shorter * k;
        *returnSize = 1;
        return p;
    }
    *returnSize = k + 1;
    int* lengths = (int*)malloc(sizeof(int) * (k + 1));
    for (int i = 0; i <= k; ++i) {
        lengths[i] = shorter * (k - i) + longer * i;
    }
    return lengths;
}

/*
625. ×îĞ¡ÒòÊ½·Ö½â
¸ø¶¨Ò»¸öÕıÕûÊı a£¬ÕÒ³ö×îĞ¡µÄÕıÕûÊı b Ê¹µÃ b µÄËùÓĞÊıÎ»Ïà³ËÇ¡ºÃµÈÓÚ a¡£

Èç¹û²»´æÔÚÕâÑùµÄ½á¹û»òÕß½á¹û²»ÊÇ 32 Î»ÓĞ·ûºÅÕûÊı£¬·µ»Ø 0¡£



ÑùÀı 1

ÊäÈë£º

48
Êä³ö£º

68s
*/

int smallestFactorization(int a)
{
        if (a <= 1) return a;
        long b = 0;
        long tmp = 1;   // È¨Öµ,1 ±íÊ¾¸öÎ»£¬10±íÊ¾Ê®Î»£¬100±íÊ¾°ÙÎ»
        // b ÊÇµ¥µ÷²»¼õµÄ£¬¼ÙÈçÉÏÒ»Î»ÊÇ³ıÒÔ 8 µÄ£¬ÄÇÏÂÒ»Î»¾ÍµÃ´Ó 8 ¿ªÊ¼ÍùÏÂÕÒ
        for (int i = 9; i >= 2; i--) {  // ×¢Òâ i ²»ÄÜÈ¡µ½ 1£¬·ñÔò»ØËÀÑ­»·
            while (a % i == 0) {    // ÄÜ²»ÄÜ±» i Õû³ı
                a /= i; // ÕÒµ½Ò»¸ö¿ÉÒÔÕû³ı a µÄ i£¬¸üĞÂ a Îª a/i
                b = tmp * i + b;    // ĞÂÌíĞÂÈ·¶¨µÄÎ»
                tmp *= 10;
            }
        }
        // µ½×îºóÈç¹û a ²»Îª 1£¬ËµÃ÷´ËÊ±µÄ a ¿Ï¶¨ÊÇÖÊÊı
        return a == 1 && b <= INT_MAX ? (int) b : 0;
}

/*
1498. Âú×ãÌõ¼şµÄ×ÓĞòÁĞÊıÄ¿
¸øÄãÒ»¸öÕûÊıÊı×é nums ºÍÒ»¸öÕûÊı target ¡£
ÇëÄãÍ³¼Æ²¢·µ»Ø nums ÖĞÄÜÂú×ãÆä×îĞ¡ÔªËØÓë×î´óÔªËØµÄ ºÍ Ğ¡
ÓÚ»òµÈÓÚ target µÄ ·Ç¿Õ ×ÓĞòÁĞµÄÊıÄ¿¡£
ÓÉÓÚ´ğ°¸¿ÉÄÜºÜ´ó£¬Çë½«½á¹û¶Ô 10^9 + 7 È¡Óàºó·µ»Ø¡£
Ê¾Àı 1£º
ÊäÈë£ºnums = [3,5,6,7], target = 9
Êä³ö£º4
½âÊÍ£ºÓĞ 4 ¸ö×ÓĞòÁĞÂú×ã¸ÃÌõ¼ş¡£
[3] -> ×îĞ¡ÔªËØ + ×î´óÔªËØ <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)
*/
/*°üº¬×ó¶Ëµã i µÄÂú×ãÌõ¼şµÄ×ÓĞòÁĞ¸öÊıÎª£º2^{j-i} ¸ö*/
/* minµ½maxÖ®¼äËùÓĞµÄ×Ó¼¯¶¼ÊÇÂú×ãÒªÇóµÄ¡£¸öÊıÎª2 ^ (maxIdx - minIdx). */
int numSubseq(int* nums, int numsSize, int target)
{
	qsort(nums, numsSize, sizeof(nums[0]), cmp_int);
	if (nums[0] * 2 > target) {
		return 0;
	}

//´óÊıÒç³ö£¬½¨Á¢³Ë·½ÁĞ±í
	int spow[numsSize];
	spow[0] = 1;
	for (int i = 1; i < numsSize; i++) {
		spow[i] = (spow[i-1] * 2) % (1000000000 + 7);
	}


	int left = 0;
	int right = numsSize - 1;
	int res = 0;
	while(left <= right) {
		if (nums[left] + nums[right] <= target) {
			res += spow[right - left];
			res %= (1000000000 + 7);
			left++;
		} else {
			right--;
		}
	}

	return res % (1000000000 + 7);
}

/*
447. »ØĞıïÚµÄÊıÁ¿
¸ø¶¨Æ½ÃæÉÏ n ¶Ô²»Í¬µÄµã£¬¡°»ØĞıïÚ¡± ÊÇÓÉµã±íÊ¾µÄÔª×é (i, j, k) £¬ÆäÖĞ i ºÍ j Ö®¼äµÄ¾àÀëºÍ i ºÍ k Ö®¼äµÄ¾àÀëÏàµÈ£¨ĞèÒª¿¼ÂÇÔª×éµÄË³Ğò£©¡£

ÕÒµ½ËùÓĞ»ØĞıïÚµÄÊıÁ¿¡£Äã¿ÉÒÔ¼ÙÉè n ×î´óÎª 500£¬ËùÓĞµãµÄ×ø±êÔÚ±ÕÇø¼ä [-10000, 10000] ÖĞ¡£

Ê¾Àı:

ÊäÈë:
[[0,0],[1,0],[2,0]]

Êä³ö:
2

½âÊÍ:
Á½¸ö»ØĞıïÚÎª [[1,0],[0,0],[2,0]] ºÍ [[1,0],[2,0],[0,0]]
*/
int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize)
{
	int* Distances = (int*)malloc(sizeof(int) * pointsSize);
	int Num_Boo = 0;

	for(int i = 0; i < pointsSize; i++){
		for(int j = 0; j < pointsSize; j++) {
			Distances[j] = pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2);
		}

		qsort(Distances, pointsSize, sizeof(int), cmp_int);
		int Count = 1;
		for(int j = 1; j < pointsSize; j++){
			if(Distances[j] == Distances[j - 1]){
				Count++;
			}else if(Count > 1){
				Num_Boo += Count * (Count - 1);
				Count = 1;
			}else{
				continue;
			}
		}
		Num_Boo += Count * (Count - 1);
	}

	free(Distances);
	return Num_Boo;
}


/*
357. ¼ÆËã¸÷¸öÎ»Êı²»Í¬µÄÊı×Ö¸öÊı
¸ø¶¨Ò»¸ö·Ç¸ºÕûÊı n£¬¼ÆËã¸÷Î»Êı×Ö¶¼²»Í¬µÄÊı×Ö x µÄ¸öÊı£¬
ÆäÖĞ 0 ¡Ü x < 10n ¡£
Ê¾Àı:
ÊäÈë: 2
Êä³ö: 91
½âÊÍ: ´ğ°¸Ó¦Îª³ıÈ¥ 11,22,33,44,55,66,77,88,99 Íâ£¬ÔÚ [0,100) Çø¼äÄÚµÄËù
ÓĞÊı×Ö¡£
*/
int countNumbersWithUniqueDigits(int n)
{
        if (n == 0)
			return 1;
        int res = 10, k = 9, temp = 9;
        for (int i = 2; i <= fmin(n, 10); ++i){
            temp *= k;
            k--;
            res += temp;
        }
        return res;
}

int randomInt(int min, int max)
{
	int ret = rand() % (max - min + 1) + min;
	return ret;
}

