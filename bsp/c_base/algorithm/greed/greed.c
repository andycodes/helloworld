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

