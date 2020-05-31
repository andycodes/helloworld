#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../flag_type.h"
#include "../math/math.h"

void digit2Str_sprintf(char *str, int digit)
{
	sprintf(str, "%d", digit);
	sprintf(str, "%x", digit);
}
/*
isdigit

��������: isdigit

����ԭ��: int isdigit(char ch);

��������: ���ch�Ƿ�������(0-9)

��������: �Ƿ��ط�0,���򷵻�0
*/
int isdigit(char ch)
{
	if (ch < '0' || ch > '9')
		return 0;
	else
		return 1;
}

/*�ַ���ת����*/
int atoi(const char *str)
{
	int num = 0;
	int sign = 1;
	const int len = strlen(str);
	int i = 0;

	while (str[i] == ' ' && i < len)i++;

	if (str[i] == '+') i++;
	if (str[i] == '-') {
		sign = -1;
		i++;
	}

	for (; i < len; i++) {
		if (str[i] < '0' || str[i] > '9')
			break;
		if (num > INT_MAX / 10 ||  (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
			return sign == -1 ? INT_MIN : INT_MAX;
		}

		num = str[i] - '0' + num * 10;
	}
	return num * sign;
}

void str2digit_sscanf(char * str)
{
	int value;
	sscanf(str, "%x", &value);
	printf("0x%x\n",value);
}

void str2digit_strtol(char * str)
{
	char* p;
	long value = strtol(str, &p, 16);
	printf("0x%lx\n",value);
}

unsigned long str2digit(char *str, int len)
{
	unsigned long i, data = 0;

	for(i = 0; i < len; i++) {
		if (!isdigit(str[i]))
			return -1;
		data *= 10;
		data += str[i]-'0';
	}

	return data;
}



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
maxlen����ʾ���Ƶ��ַ�������
��c/c++�������ַ���source�е����ݣ��ַ������֡�����....��
���ַ���destinin�У����ƶ�����maxlen��ֵ������
���source��ǰn���ַ�����NULL�ַ���
����������NULL�ַ�������
���n<source�ĳ��ȣ�ֻ�ǽ�source��ǰn���ַ����Ƶ�
destinin��ǰn���ַ������Զ����'\0'��
Ҳ���ǽ��destinin������'\0'����Ҫ���ֶ����һ��'\0'��
���source�ĳ���С��n���ֽڣ�����NULL���
destininֱ��������n���ֽڡ�
source��destinin��ָ�ڴ����򲻿����ص���
destinin�������㹻�Ŀռ�������source���ַ�����+'\0'��
*/
/*
char *strncpy(char *destinin, char *source, int maxlen);
destinin[maxlen] = '\0';
*/

/*
��ȡ�ַ���
��src start λ����ȡ����Ϊlen���ַ�����dst
*/
void substr(char* dst, char* src, int start, int cpLen)
{
#if 0
    char* sc = src + start;
    int srcLen = strlen(sc);
    int i = 0;


    if (srcLen < cpLen) {
        cpLen = srcLen;
    }

    while (srcLen) {
        dst[i] = sc[i];
        srcLen--;
        i++;
    }
    dst[i] = '\0';
#else
	strncpy(dst, src + start, cpLen);
	dst[cpLen] = '\0';
#endif
}

char *strrpl(char *srcStr, char *dstStr, int dstSize, const char *oldSubStr, char *newSubStr)
{
	char *it = srcStr;
	unsigned int  len = dstSize - 1;

	if(oldSubStr == NULL ||newSubStr== NULL || srcStr == NULL || dstStr  == NULL || dstSize <= 0) {
		return NULL;
	}

	if((strcmp(srcStr, "") == 0) || (strcmp(oldSubStr, "") == 0)) {
		return NULL;
	}

	while(*it != '\0' && len > 0) {
		if(strncmp(it, oldSubStr, strlen(oldSubStr)) != 0) {
			int n = strlen(dstStr);
			dstStr[n] = *it;
			dstStr[n + 1] = '\0';
			it++;
			len--;
		} else {
			strcat(dstStr, newSubStr);
			it += strlen(oldSubStr);
			len -= strlen(newSubStr);
		}
	}

	return dstStr;
}

void strreplace(char *text, char *oldsubstr, char *newsubstr)
{
	int oldsublen = strlen(oldsubstr);
	int newsublen = strlen(newsubstr);
	char *temp = text;

	while ( (temp = strstr(temp, oldsubstr)) != NULL ) {
		memmove(temp + newsublen, temp + oldsublen, strlen(temp) - oldsublen + 1);
		memcpy(temp, newsubstr, newsublen);
		temp = temp + newsublen;
	}
}


/*
������
�����ַ��� s �� t ���ж� s �Ƿ�Ϊ t �������С�

�������Ϊ s �� t �н�����Ӣ��Сд��ĸ��
�ַ��� t ���ܻ�ܳ������� ~= 500,000����
�� s �Ǹ����ַ��������� <=100����

�ַ�����һ����������ԭʼ�ַ���ɾ��
һЩ��Ҳ���Բ�ɾ�����ַ������ı�ʣ
���ַ����λ���γɵ����ַ����������磬"ace"��"abcde"��һ
�������У���"aec"���ǣ���

ʾ�� 1:
s = "abc", t = "ahbgdc"

���� true.

ʾ�� 2:
s = "axc", t = "ahbgdc"

���� false.

*/
bool isSubsequence(char * s, char * t)
{
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

void trim(char *strIn, char *strOut)
{
    int i, j ;

    i = 0;
    j = strlen(strIn) - 1;

    while(strIn[i] == ' ')
        ++i;

    while(strIn[j] == ' ')
        --j;
    strncpy(strOut, strIn + i , j - i + 1);
    strOut[j - i + 1] = '\0';
}

void trim(char *strIn, char *strOut)
{

    char *start, *end, *temp;//����ȥ���ո���ַ�����ͷβָ��ͱ���ָ��
    temp = strIn;

    while (*temp == ' '){
        ++temp;
    }

    start = temp; //���ͷָ��
    temp = strIn + strlen(strIn) - 1; //�õ�ԭ�ַ������һ���ַ���ָ��(����'\0')
    printf("%c\n", *temp);
    while (*temp == ' '){
        --temp;
    }

    end = temp; //���βָ��


    for(strIn = start; strIn <= end; ){
        *strOut++ = *strIn++;
    }

    *strOut = '\0';
}

char* trim(char *a)
{
	char *p1 = a;
	char *p2 = a + strlen(a) - 1;

	while (p1 <= p2 && *p1 == ' ') {
		p1++;
	}
	while (p2 >= p1 && *p2 == ' ') {
		p2--;
	}

	*(++p2) = '\0';
	return p1;
}

char* trim(char *a)
{
	char *end, *p1, *p2;
	int len;
	p1 = a;
	end = a + strlen(a) - 1;
	p2 = end;
	while (p1 <= end && isspace(*p1)){
		p1++;
	}
	while (p2 >= p1 && isspace(*p2)){
		p2--;
	}
	len = (p2 < p1) ? 0 : (p2 - p1) + 1;//���ַ���ȫΪ�ո�p1���Ƶ�p2�ĺ��棬��ô���p1>p2�����ؿա�
	p1[len] = '\0';
	return p1;
}

void deblank(char string[])
{
    int i=0;
    int j=0;
    while(string[j]!='\0'){
        if(string[j]!=' '||string[j+1]!=' '){
            string[i]=string[j];
            i++;
            j++;
        }
        else
        {
            string[i]=string[j+1];
            j++;
        }
    }
    string[i]='\0';
}

char * deblank_trim(char * str)
{
    char * left = str;//ǰ���ָ�룬����ֵ
    char * right = str;//����Ѱ�ҷǿո��ַ���ָ��

    while (*right != '\0') {
        if (*right != ' ') {
            if (left < right) {
                *left = *right;
            }
            left++;
        }

        if (*right == ' ' && *(right + 1) != ' ')//Ѱ�ҵ���һ������ʱ����left�Ĳ���
        {
            *left = ' ';
            left++;
        }

        right++;
    }

    *left = '\0';
    return *str != ' ' ?str:(str + 1);//��ֹ�׵���֮ǰ�пո�����
}


void strrev_pos(char* s, int begin, int end)
{
	char* left = s + begin;
	char* right = s + end;

	if (begin == end)
		return;

	while(left < right) {
		swap(*left, *right);
		left++;
		right--;
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
void reverseWords(char* s, int sSize)
{
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
    if(to == NULL && from == NULL)
		return 0;

    char *p = to;
    while ((*p++ = *from++) != '\0')
    ;
    return to;
}


/*���û���� | �Ϳո�Ӣ���ַ�ת��ΪСд
('a' | ' ') = 'a'
('A' | ' ') = 'a'
*/

/*��������� & ���»��߽�Ӣ���ַ�ת��Ϊ��д
('b' & '_') = 'B'
('B' & '_') = 'B'
*/

/*
���������� ^ �Ϳո����Ӣ���ַ���Сд����
('d' ^ ' ') = 'D'
('D' ^ ' ') = 'd'

��Сд��ĸ���32,����Ϊ�����Ҫ����:����λ�ӷ�,
���Դ�д��ĸ��(1<<5)����ɱ��Сд��ĸ,
Сд��ĸ��(1<<5)����ɴ�д��ĸ*/
char *alpha_low_upper( char *Str )
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
	}else if(isdigit(*s)) {/*����������֧ȥ�����Ǵ������Ӵ�*/
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


/*
����ԭ�ͣ�char * strtok (char *str, const char * delimiters);
������str�����ָ���ַ�����c-string����
delimiters���ָ���ַ�����
�ú����������ַ����ָ��һ����Ƭ�Ρ�
����strָ�����ָ���ַ�����
����delimiters��Ϊ�ָ��ַ����а����������ַ���
��strtok()�ڲ���s��
�ַ����з��ֲ���delimiters�а����ķָ��ַ�ʱ��
��Ὣ���ַ���Ϊ\0 �ַ����ڵ�һ�ε���ʱ��
strtok()����������s�ַ�����
����ĵ����򽫲���s���ó�NULL��
ÿ�ε��óɹ��򷵻�ָ�򱻷ָ��Ƭ�ε�ָ�롣
��Ҫע����ǣ�ʹ�øú��������ַ����ָ�ʱ��
���ƻ����ֽ��ַ�����������
����ǰ�͵��ú��s�Ѿ���һ���ˡ�
��һ�ηָ�֮��
ԭ�ַ���str�Ƿָ����֮��ĵ�һ���ַ�����
ʣ����ַ����洢��һ����̬�����У�
��˶��߳�ͬʱ���ʸþ�̬����ʱ��
�����ִ���

strtok_r������linux�·ָ��ַ����İ�ȫ�����������������£�
char *strtok_r(char *str, const char *delim, char **saveptr);
�ú���Ҳ���ƻ����ֽ��ַ����������ԣ�
�����佫ʣ����ַ���������saveptr�����У���֤�˰�ȫ�ԡ�
���ӣ�
*/


/*
str һֱ��"ab"
iterator ��������Ա������"ab"/"cd"/"ef";iteratorֻȡ����Ч�ֶ�
p ʣ���Ӵ�������"cd,ef"/"ef"/"NULL"
*/
void strtok_test(void)
{
	char str[]="ab,cd,ef";
	char *iterator;
	char *p;
	iterator = strtok_r(str, ",", &p);
	while(iterator != NULL) {
		/*iterator*/
		iterator = strtok_r(NULL, ",", &p);
	}
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

