#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#include "../../flag_type.h"
/*
#include <string.h>
�������ַ���
����Ϊ �ж�str2�Ƿ�Ϊstr1���ִ���
�����򷵻�str2��str1���״γ��ֵ�ָ��λ�ã�
�����Ƿ���NULL��
*/
char *strstr(const char *str1, const char *str2);


/*
�����ַ�
����˵����
str�������ҵ��ַ�����
c��Ҫ���ҵ��ַ���

strchr() ���������μ����ַ��� str �е�ÿһ���ַ���
ֱ�������ַ� c�����ߵ����ַ���ĩβ������\0����

����ֵ���������ַ��� str �е�һ�γ����ַ� c ��λ�ã�
���δ�ҵ����ַ� c �򷵻� NULL��
*/
char* strchr(const char* str, int c);





/*
2. string/array to int/float
C/C++�����ṩ�˼�����׼�⺯�������Խ��ַ���ת��Ϊ��������(���͡������͡������͵�)��
�� atof()�����ַ���ת��Ϊ˫���ȸ�����ֵ��
�� atoi()�����ַ���ת��Ϊ����ֵ��
�� atol()�����ַ���ת��Ϊ������ֵ��
�� strtod()�����ַ���ת��Ϊ˫���ȸ�����ֵ�������治�ܱ�ת��������ʣ�����֡�
�� strtol()�����ַ���ת��Ϊ����ֵ�������治�ܱ�ת��������ʣ�����֡�
�� strtoul()�����ַ���ת��Ϊ�޷��ų�����ֵ�������治�ܱ�ת��������ʣ�����֡�
*/

/*
��ȡ�ַ���
��src start λ����ȡ����Ϊlen���ַ�����dst
*/
void substr(char dst[], char src[],int start,int len)
{
	char* sc = src+start;
	int n = strlen(sc);
	int i = 0;
	int **ret=NULL;
	//assert(dst != NULL );
	//assert(src != NULL );
    if(n < len)
    {
        len = n;
    }
    while(len)
    {
        dst[i] = sc[i];
        len--;
        i++;
    }
    dst[i] = '\0';
}


//�ַ����滻����
// ����˵��:
// in�� Դ�ַ���
// out, �����������ַ���
// outlen��out���Ĵ�С
// src��Ҫ�滻���ַ���
// dst���滻��ʲô�ַ���
char *strrpl(char *in, char *out, int outlen, const char *src, char *dst)
{
    char *p = in;
    unsigned int  len = outlen - 1;

    // �⼸�μ������Ϸ���
    if((NULL == src) || (NULL == dst) || (NULL == in) || (NULL == out))
    {
        return NULL;
    }
    if((strcmp(in, "") == 0) || (strcmp(src, "") == 0))
    {
        return NULL;
    }
    if(outlen <= 0)
    {
        return NULL;
    }

    while((*p != '\0') && (len > 0))
    {
        if(strncmp(p, src, strlen(src)) != 0)
        {
            int n = strlen(out);

            out[n] = *p;
            out[n + 1] = '\0';

            p++;
            len--;
        }
        else
        {
            strcat(out, dst);
            p += strlen(src);
            len -= strlen(dst);
        }
    }

    return out;
}


void test_strrpl(void)
{
	char ss[] = "abcd";
	char out[32] = {'\0'};
	strrpl(ss,out,sizeof(out),"ab","ff");

	printf("%s\n",out);
}


/*
������
�����ַ��� s �� t ���ж� s �Ƿ�Ϊ t �������С�

�������Ϊ s �� t �н�����Ӣ��Сд��ĸ���ַ��� t ���ܻ�ܳ������� ~= 500,000������ s �Ǹ����ַ��������� <=100����

�ַ�����һ����������ԭʼ�ַ���ɾ��һЩ��Ҳ���Բ�ɾ�����ַ������ı�ʣ���ַ����λ���γɵ����ַ����������磬"ace"��"abcde"��һ�������У���"aec"���ǣ���

ʾ�� 1:
s = "abc", t = "ahbgdc"

���� true.

ʾ�� 2:
s = "axc", t = "ahbgdc"

���� false.

*/
bool isSubsequence(char * s, char * t){
	unsigned int i;
	unsigned int j;
	unsigned int s_size = strlen(s);
	unsigned int t_size = strlen(t);

    if(s_size == 0)
        return true;

	for(i = 0,j = 0; i< t_size;i++) {
		if(t[i] == s[j]){
			j++;
		}
        if(j == s_size) return true;
	}

	return false;
}


#define swap(a,b) (a^=b,b^=a,a^=b)
void strrev_pos(char* s, int begin, int end)
{
	char* h = s + begin;
	char* t = s + end;

	if (begin == end)
		return;

	while(h < t) {
		swap(*h, *t);
		h++;
		t--;
	}
}


void strrev(char* s)
{
	strrev_pos(s, 0, strlen(s) -1);
}

/*
����һ���ַ����������ת�ַ����е�ÿ�����ʡ�

ʾ����

����: ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
���: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
ע�⣺

���ʵĶ����ǲ������ո��һϵ���ַ�
�����ַ����в������ǰ�û�β��Ŀո�
�����뵥��֮����Զ���Ե����ո������

*/
void reverseWords(char* s, int sSize){
    	int len = 0;

	strrev_pos(s, 0, sSize -1);
	for (int i = 0; i < sSize; ) {
		len = 0;
		while ((i + len) < sSize && s[i + len] != ' ') {
			len++;
		}
		strrev_pos(s, i, i + len - 1);
		i = i + len + 1;
	}
}


size_t strlen(const char *str) {
	const char *s;
	for (s = str; *s; ++s) {}
	return(s - str);
}


char* strcpy(char *to, const char *from) {
    if(to == NULL && from == NULL) return 0;

    char *p = to;
    while ((*p++ = *from++) != '\0')
    ;
    return to;
}


/*
��һ���޷��Ŷ���������������
��˳��ת��Ϊ�����ֽ�˳��
*/
unsigned short ntohs(unsigned short s)
{
    return (s >> 8) | (s << 8);
}

/*
��һ���޷��ų���������
�����ֽ�˳��ת��Ϊ�����ֽ�˳��

*/
unsigned long ntohl(unsigned long l)
{
    return  ((l >> 24) & 0x000000ff) |
        ((l >>  8) & 0x0000ff00) |
        ((l <<  8) & 0x00ff0000) |
        ((l << 24) & 0xff000000);
}

/*

���������޷��Ŷ�������ת���������ֽ�˳��
*/
unsigned short htons(unsigned short s)
{
    return (s >> 8) | (s << 8);
}

/*
���������޷��ų�������ת���������ֽ�˳��

*/
unsigned long htonl(unsigned long l)
{
    return ntohl(l);
}


/*��Сд��ĸ���32,����Ϊ�����Ҫ����:����λ�ӷ�,
���Դ�д��ĸ��(1<<5)����ɱ��Сд��ĸ,
Сд��ĸ��(1<<5)����ɴ�д��ĸ*/
char *str_letter_big_little( char *Str )
{
    char *cp;
    cp = Str;

    while (*cp != 0)
    {
        *cp^=(1<<5);
        cp++;
    }

    return Str;
}


unsigned long strtobcd(char *s)
{
    unsigned long ret;
    int i;

    ret = 0;

    while (*s != '\0') {
        if (*s >= '0' && *s <= '9')
            i = *s - '0';
        else
            return -1;
        ret = (ret << 4) + i;
        s++;
    }

    return ret;
}

unsigned long strtodec(char *str, int cnt)
{
    unsigned long i, data = 0;

    for(i=0; i<cnt; i++)
    {
        data *= 10;
        if(str[i]<'0'||str[i]>'9')
            return -1;
        data += str[i]-'0';
    }
    return data;
}

void ultostr(char *s, unsigned long data)
{
    int i;

    s[8] = 0;
    for(i=7; i>=0; i--, data >>=4)
    {
        if((data&0xf)<=9)
            s[i] = (data&0xf)+'0';
        else
            s[i] = (data&0xf)+'a'-0x0a;
    }
}

#define INT_MAX 2147483647
#define INT_MIN -2147483648
int atoi(const char *str) {
    int num = 0;
    int sign = 1;
    const int len = strlen(str);
    int i = 0;
    while (str[i] == ' ' && i < len) i++;
    if (str[i] == '+') i++;
    if (str[i] == '-') {
    sign = -1;
    i++;
    }
    for (; i < len; i++) {
        if (str[i] < '0' || str[i] > '9')
        break;
        if (num > INT_MAX / 10 ||
        (num == INT_MAX / 10 &&
        (str[i] - '0') > INT_MAX % 10)) {
            return sign == -1 ? INT_MIN : INT_MAX;
        }
        num = num * 10 + str[i] - '0';
    }
    return num * sign;
}


/* ���+-���� С������������ִ�*/
int max_num_in_string(char *inputstr, char *outputstr)
{
	int count=0;
	int numCnt = 0;
	int pointCnt = 0;
	//�ַ������������ָ��������ֵ
	int max=0;
	//����ȡ�����ֵ��ָ��
	char *mPos;
	char *s = inputstr;
	int i = 0;

    while(*s != '\0') {
	if (count == 0 && (*s == '+' || *s == '-')) {
		count++;
	} else if (*s == '.' && numCnt > 0 && pointCnt == 0) {
		count++;
		pointCnt = 1;
	}else if(*s >= '0' && *s <= '9') {/*����������֧ȥ�����Ǵ������Ӵ�*/
		count++;
		numCnt++;
	} else {
            if(count > max) {
                max = count;
		 /*s��ǰλ�û���count�ַ���max�Ӵ���ʼλ��*/
                mPos = s - count;
            }

		count = 0;
		numCnt = 0;
		pointCnt = 0;
        }

        s++;
    }

    //�п����ַ���ĩβȡ�����ֵ
    if(count>max) {
        max=count;
        mPos=s-max;
    }

#if 1
	memcpy(outputstr, mPos,max);
	outputstr[max] = '\0';
#else
	while(i<max) {
		*outputstr=*(mPos+i);
		outputstr++;
		i++;
	}

	*outputstr='\0';
#endif
    return max;
}


void max_num_in_string_test(void)
{
	char input[] = "q21u+231y-123.456789y-0.23";
	char output[1024];
	int ret = max_num_in_string(input,output);
	printf("%d:%s\n",ret,output);
}

/*
����һ���ַ��� s ���ҳ� ���� ����������ͬ�ַ�����Ӵ� t ��

ʾ�� 1:

����: "eceba"
���: 3
����: t �� "ece"������Ϊ3��
ʾ�� 2:

����: "ccaabbb"
���: 5
����: t �� "aabbb"������Ϊ5��

*/
int lengthOfLongestSubstringTwoDistinct(char * s){

	int sSize = strlen(s);
	if (sSize <= 2)
		return sSize;

	int left = 0;
	int max = 0;

	while( left + max < sSize) {
		int tempLeft = left;

		while(left < sSize && s[left] == s[tempLeft]) {
			left++;
		}

		int right = left;
		int tempRight = right;

		while(right < sSize && (s[right] == s[tempRight] || s[right] == s[tempLeft] )) {
			right++;
		}

		max = max > (right - tempLeft) ? max :(right - tempLeft);
		left = tempRight;
	}

	return max;
}



void str_to_hex_by_sscanf(char * str)
{
	int value;
	sscanf(str, "%x", &value);
	printf("0x%x\n",value);
}


void str_to_hex_by_strtol(char * str)
{
	char* p;
	long value = strtol(str, &p, 16);

	printf("0x%lx\n",value);
}

/*
����ԭ�ͣ�char * strtok (char *str, const char * delimiters);
������str�����ָ���ַ�����c-string����delimiters���ָ���ַ�����
�ú����������ַ����ָ��һ����Ƭ�Ρ�����strָ�����ָ���ַ�����
����delimiters��Ϊ�ָ��ַ����а����������ַ�����strtok()�ڲ���s��
�ַ����з��ֲ���delimiters�а����ķָ��ַ�ʱ��
��Ὣ���ַ���Ϊ\0 �ַ����ڵ�һ�ε���ʱ��
strtok()����������s�ַ���������ĵ����򽫲���s���ó�NULL��
ÿ�ε��óɹ��򷵻�ָ�򱻷ָ��Ƭ�ε�ָ�롣
��Ҫע����ǣ�ʹ�øú��������ַ����ָ�ʱ��
���ƻ����ֽ��ַ���������������ǰ�͵��ú��s�Ѿ���һ���ˡ�
��һ�ηָ�֮��ԭ�ַ���str�Ƿָ����֮��ĵ�һ���ַ�����
ʣ����ַ����洢��һ����̬�����У���˶��߳�ͬʱ���ʸþ�̬����ʱ��
�����ִ���

strtok_r������linux�·ָ��ַ����İ�ȫ�����������������£�
char *strtok_r(char *str, const char *delim, char **saveptr);
�ú���Ҳ���ƻ����ֽ��ַ����������ԣ�
�����佫ʣ����ַ���������saveptr�����У���֤�˰�ȫ�ԡ�
���ӣ�
*/

void strtok_test(void)
{
    char str[]="ab,cd,ef";
    char *ptr;
    char *p;
    printf("before strtok:  str=%s\n",str);
    printf("begin:\n");
    ptr = strtok_r(str, ",", &p);
    while(ptr != NULL){
        printf("str=%s\n",str);
        printf("ptr=%s\n",ptr);
	printf("p=%s\n",p);
        ptr = strtok_r(NULL, ",", &p);
    }
}

/*
���� �ַ��� text �� �ַ����б� words, �������е������� [i, j] ʹ���������Է�Χ�ڵ����ַ��� text[i]...text[j]������ i �� j�������ַ����б� words��



ʾ�� 1:

����: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
���: [[3,7],[9,13],[10,17]]
ʾ�� 2:

����: text = "ababa", words = ["aba","ab"]
���: [[0,1],[0,2],[2,3],[2,4]]
����:
ע�⣬���ص���Կ����н��棬���磬"aba" ���� [0,2] ��Ҳ�� [2,4] ��

*/
int cmp(const void *a,const void *b)
{
    int *ap = *(int **)a;
    int *bp = *(int **)b;

    if(ap[0] == bp[0])
        return ap[1] - bp[1];
    else
        return ap[0] - bp[0];
}

int** indexPairs(char * text, char ** words, int wordsSize, int* returnSize, int** returnColumnSizes){
    int i, j;
    int** res = (int **)malloc(sizeof(int *) * 1000);
    int cnt = 0;
    int len1 = strlen(text);

    for (i = 0; i < wordsSize; i++) {
        int len2 = strlen(words[i]);
        if(len2 > len1)
		continue;

	for (j = 0; j < len1 - len2 + 1; j++) {
            if (strncmp(text + j, words[i], strlen(words[i])) == 0) {
                res[cnt] = (int *)malloc(sizeof(int) * 2);
                res[cnt][0] = j;
                res[cnt][1] = j + strlen(words[i]) - 1;
                cnt++;
                //printf("j = %d endIdx = %d cnt = %d\n", j, j + strlen(words[i]) - 1, cnt);
            }
        }
	}

    qsort(res, cnt, sizeof(res[0]), cmp); // ��ά��������
    *returnSize = cnt;
    returnColumnSizes[0] = (int *)malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; i++) {
        returnColumnSizes[0][i] = 2;
    }
    return res;
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("argc err\n");
		return -1;
	}

	switch(atoi(argv[1])) {
	case 1:
		str_to_hex_by_sscanf(argv[2]);
	break;
	case 2:
		str_to_hex_by_strtol(argv[2]);
	break;
	case 3:
		test_strrpl();
	break;
	case 4:
		strtok_test();
	break;
	case 5: max_num_in_string_test();
	break;
	default:
	break;
	}

	return 0;
}


