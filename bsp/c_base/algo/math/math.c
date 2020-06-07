/*ÅĞ¶ÏÁ½¸öÊıÊÇ·ñÒìºÅ*/
int x = -1, y = 2;
bool f = ((x ^ y) < 0); // true

int x = 3, y = 2;
bool f = ((x ^ y) < 0); // false



/*¾ø¶ÔÖµ*/
int abs(int);

/* sqrt() ÓÃÀ´Çó¸ø¶¨ÖµµÄÆ½·½¸ù */
double sqrt(double x);

/*pow() º¯ÊıÓÃÀ´Çó x µÄ y ´ÎÃİ£¨´Î·½£©*/
double pow(double x, double y);

/*
1109. º½°àÔ¤¶©Í³¼Æ
ÕâÀïÓĞ n ¸öº½°à£¬ËüÃÇ·Ö±ğ´Ó 1 µ½ n ½øĞĞ±àºÅ¡£
ÎÒÃÇÕâ¶ùÓĞÒ»·İº½°àÔ¤¶©±í£¬
±íÖĞµÚ i ÌõÔ¤¶©¼ÇÂ¼ bookings[i] = [i, j, k] ÒâÎ¶×ÅÎÒÃÇÔÚ´Ó i µ½ j µÄ
Ã¿¸öº½°àÉÏÔ¤¶©ÁË k ¸ö×ùÎ»¡£
ÇëÄã·µ»ØÒ»¸ö³¤¶ÈÎª n µÄÊı×é answer£¬
°´º½°à±àºÅË³Ğò·µ»ØÃ¿¸öº½°àÉÏÔ¤¶©µÄ×ùÎ»Êı¡£
Ê¾Àı£º

ÊäÈë£ºbookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Êä³ö£º[10,55,45,25,25]


Éèa[i]±íÊ¾µÚi¸öº½°àÔ¤¶©µÄ×ùÎ»Êı¡£
¶¨ÒåÒ»¸ö²î·ÖÊı×étag[]£¬
tag[i]±íÊ¾µÚi¸öº½°àÓëµÚi-1¸öº½°àÔ¤¶©×ùÎ»µÄ²î£¬
¼´tag[i] = a[i] - a[i - 1]¡£
ÕâÑù£¬ÎÒÃÇÃ¿´ÎÉ¨Ãèµ½[i, j, k]£¬
¾ÍÖ»ĞèÒª½«tag[i]Ôö¼Ók£¬tag[j + 1]¼õÉÙk¼´¿É¡£
×îºó£¬¼ÆËãa[i] = a[i - 1] + tag[i]£¬·µ»Øa¼´¿É¡£
*/
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize,
int n, int* returnSize){
	int *diff = malloc(20001 * sizeof(int));
	memset((void*)diff,0,20001*sizeof(int));

	for(int i = 0; i < bookingsSize; i++){
		diff[bookings[i][0]-1] += bookings[i][2]; //µÈ²î¿ªÊ¼¼ÓÉÏµÈ²îÖµ
		diff[bookings[i][1]]   -= bookings[i][2]; //µÈ²î½áÊø ¼õµôµÈ²îÖµ
	}

	for(int i = 1; i < n; i++) {
		diff[i] += diff[i -1];//ÍÆµ¼Ô­Ê¼Öµ
	}

	*returnSize = n;
	return diff;
}

/*
1010. ×Ü³ÖĞøÊ±¼ä¿É±» 60 Õû³ıµÄ¸èÇú
ÔÚ¸èÇúÁĞ±íÖĞ£¬µÚ i Ê×¸èÇúµÄ³ÖĞøÊ±¼äÎª time[i] Ãë¡£
·µ»ØÆä×Ü³ÖĞøÊ±¼ä£¨ÒÔÃëÎªµ¥Î»£©¿É±» 60 Õû³ıµÄ¸èÇú¶ÔµÄÊıÁ¿¡£
ĞÎÊ½ÉÏ£¬ÎÒÃÇÏ£ÍûË÷ÒıµÄÊı×Ö  i < j ÇÒÓĞ (time[i] + time[j]) % 60 == 0¡£
Ê¾Àı 1£º
ÊäÈë£º[30,20,150,100,40]
Êä³ö£º3
½âÊÍ£ºÕâÈı¶ÔµÄ×Ü³ÖĞøÊ±¼ä¿É±» 60 ÕûÊı£º
(time[0] = 30, time[2] = 150): ×Ü³ÖĞøÊ±¼ä 180
(time[1] = 20, time[3] = 100): ×Ü³ÖĞøÊ±¼ä 120
(time[1] = 20, time[4] = 40): ×Ü³ÖĞøÊ±¼ä 60
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

void deleteItem(int *nums, int numsSize, int in)
{
	while (in < numsSize - 1)
		nums[in++] = nums[in + 1];
}

char *getPermutation(int n, int k)
{
	int i, j = 0, nums[n], factor;
	char *res = (char *)calloc(10, sizeof(char));

	for (i = 0; i < n; i++)  //³õÊ¼»¯Ò»¸ö [1,2,3,¡­¡­,n] Êı×é
		nums[i] = i + 1;
	for (i = 0, k--; i < n; i++) {  //kÒªÏÈ¼õÈ¥1
		factor = factorial(n - i - 1);
		res[j++] = nums[k / factor] + '0';
		deleteItem(nums, n - i, k / factor);  //È¡³öÒ»¸öÔªËØ
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
void lower(int *x, int *y, int d1, int d2)
{
	int p1 = *x /d1;
	int p2 = *y /d2;
	int min = p1 > p2 ? p2 : p1;
	*x = *x - min * d1;
	*y = *y - min * d2;
}

bool isOk(char * command, int x, int y)
{
	int i=0;
	while(x>=0 && y>=0) {
		if(x==0&&y==0)
			return true;
		if(*(command+i)=='U') {
			y--;
		}else  {
			x--;
		}
		i++;
	}

	if(x==0&&y==0)
	return true;
		else
	return false;
}

bool robot(char * command, int** obstacles, int obstaclesSize, int* obstaclesColSize, int x, int y)
{
	int nx = x, ny = y;
	int numU=0,numR=0;

	for(int i=0; i<strlen(command); i++) {
		if(*(command+i)=='U') {
			numU++;
		}else{
			numR++;
		}
	}

	lower(&nx,&ny,numR,numU);
	if(!isOk(command,nx,ny))
		return false;

	for(int i=0; i<obstaclesSize; i++) {
		if(obstacles[i][0]>x||obstacles[i][1]>y)
			continue;
		nx=obstacles[i][0];
		ny=obstacles[i][1];

		lower(&nx,&ny,numR,numU);
		if(isOk(command,nx,ny))
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

// @lc code=start

//¡¾Ëã·¨Ë¼Â·¡¿ÊıÑ§¡£³óÊıµÄ¹¹Ôì·½·¨¡£
int nthSuperUglyNumber(int n, int* primes, int primesSize){
    if(n == 1)
    {
        return 1;
    }

    int *res = (int *)calloc(n, sizeof(int));
    int rsize = 0;

    int *pids = (int *)calloc(primesSize, sizeof(int));

    res[rsize++] = 1;

    while(rsize < n)
    {
        // Ñ¡Ôñ×îĞ¡µÄ(ËØÊı*res[pid])£¬¸üĞÂÆäpid
        int min = INT_MAX;
        int id = 0;

        for(int i = 0; i < primesSize; i++)
        {
            int tmin = primes[i] * res[ pids[i] ];

            if(tmin < min)
            {
                min = tmin;
                id = i;
            }
            // È¥³ıÖØ¸´
            else if(tmin == min)
            {
                pids[i]++;
            }
        }

        res[rsize++] = min;
        pids[id]++;
    }

    return res[n - 1];
}

