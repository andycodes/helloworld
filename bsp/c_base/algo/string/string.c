
void delChar(char *s, int num)
{
	char *p = s;
	char *q = s;
	for (int i = 0; i < strlen(s); i++) {
		if (i == num) {
			q++;
		}
		*(p++) = *(q++);
	}

	*p = '\0';
}

/*
memset��ͷ�ļ���<string.h>  why ?
int array[10];
memset(array,1,10);//����memset(array,1,sizeof(array))�����ǲ��Եģ�

memset����ʹ��˵�����ᵽ���ǰ���byte����䡣
char arr[10]; memset(arr,'a',10);
����charֻռһ���ֽ�(byte)����˺����Ľ���ǽ�������10���ֽڶ����Ϊ'a'�������������ڴ��Ľ����
*/
void * memset(void *s, int c, size_t n);

/*
(1) �����ʽ������ַ������� < size��
�򽫴��ַ���ȫ�����Ƶ�str�У�
����������һ���ַ���������('\0')��
(2) �����ʽ������ַ������� >= size��
��ֻ�����е�(size-1)���ַ����Ƶ�str�У�
����������һ���ַ���������('\0')��
����ֵΪ��д����ַ������ȡ�
����ֵΪ�ַ�������ʵ���ȡ�

һ����'\0';��󿽱�size -1�����û�����
*/
int snprintf ( char * str, size_t size, const char * format, ... );


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
int atoi(char * str){
	long int num = 0;
	int sign = 1;
	const int len = strlen(str);
	int i = 0;

	while (str[i] == ' ' && i < len)
		i++;

	if (str[i] == '+')
		i++;
	else if (str[i] == '-') {
		sign = -1;
		i++;
	}

	for (; i < len; i++) {
		if (str[i] < '0' || str[i] > '9')//if (!isdigit(str[i]))
			break;
		//if (num > INT_MAX / 10 ||  (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
		//	return sign == -1 ? INT_MIN : INT_MAX;
		//}

		num = num * 10 + str[i] - '0';
		if ((int)num != num) {
			return sign == -1 ? INT_MIN : INT_MAX;
		}
	}

	return (int)(num * sign);

}
long int atol(char * str);//���ַ���ת��Ϊ������ֵ��
float atof(char * str);//���ַ���ת��Ϊ˫���ȸ�����ֵ��

void str2digit_sscanf(char * str)
{
	int value;
	sscanf(str, "%x", &value);
	printf("0x%x\n",value);
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

char *strrpl(char *dstStr, int dstSize, char *srcStr, const char *oldSubStr, char *newSubStr)
{
	char *it = srcStr;
	unsigned int  len = dstSize - 1;

	if(oldSubStr == NULL ||newSubStr == NULL || srcStr == NULL
		|| dstStr  == NULL || dstSize <= 0) {
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


/*
392. �ж�������
�����ַ��� s �� t ���ж� s �Ƿ�Ϊ t �������С�
�������Ϊ s �� t �н�����Ӣ��Сд��ĸ��
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


/*ɾ����β�ո�*/
char* trim(char *a)
{
	char *p1 = a;
	char *p2 = a + strlen(a) - 1;
	int len;

	while (p1 <= p2 && *p1 == ' ') {
		p1++;
	}
	while (p2 >= p1 && *p2 == ' ') {
		p2--;
	}
/* ���ַ���ȫΪ�ո�
p1���Ƶ�p2�ĺ��棬��ô���p1>p2�����ؿա�*/
	len = (p2 < p1) ? 0 : (p2 - p1) + 1;
	p1[len] = '\0';
	return p1;
}
/*ɾ������ո�*/
char * deblank(char * str)
{
    char *left = str;//ǰ���ָ�룬����ֵ
    char *right = str;//����Ѱ�ҷǿո��ַ���ָ��

    while (*right != '\0') {
        if (*right != ' ') {
            if (left < right) {
                *left = *right;
            }
            left++;
        }

//Ѱ�ҵ���һ������ʱ����left�Ĳ���
        if (*right == ' ' && *(right + 1) != ' ') {
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


size_t strlen(const char *str)
{
	const char *s;
	for (s = str; *s; ++s) {}
	return(s - str);
}


char* strcpy(char *dest, const char *src)
{
    if(dest == NULL || src == NULL)
		return NULL;

    char *p = dest;
    while ((*p++ = *src++) != '\0');
    return dest;
}
/*��src len ����maxlen ��ضϸ���maxlen��dest,
destβ��û�н�����'\0
dest[maxlen] = '\0''*/
char *strncpy(char *dest, char *src, int maxlen);
/*
��ȡ�ַ���
��src start λ����ȡ����Ϊlen���ַ�����dst
*/
void substr(char* dst, char* src, int start, int cpLen)
{
	strncpy(dst, src + start, cpLen);
	dst[cpLen] = '\0';
}

char * strncat(char *dest, const char *src, size_t n);

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

/*
isalpha
��������: isalpha
����ԭ��:
��������: ���ch�Ƿ�����ĸ.
��������: ����ĸ���ط�0(��vs2015��Ϊ2) ,���򷵻� 0.
*/
int isalpha(char ch);
/*
islower
��������: islower
����ԭ��: int islower(int ch);
��������: ���ch�Ƿ�Сд��ĸ(a-z)
��������: �Ƿ��ط�0,���򷵻�0
����˵��:
�����ļ�: <ctype.h>
*/
int islower(int ch);
/*
isupper
��������: isupper
����ԭ��: int isupper(int ch);
��������: ���ch�Ƿ��Ǵ�д��ĸ(A-Z)
��������: �Ƿ��ط�0,���򷵻�0
*/
int isupper(int ch);
/*
tolower
��������: tolower
����ԭ��: int tolower(int ch);
��������: ��ch�ַ�ת��ΪСд��ĸ
��������: ����ch��������ַ���Сд��ĸ
*/
int tolower(int ch);
/*
toupper
��������: toupper
����ԭ��: int toupper(int ch);
��������: ��ch�ַ�ת���ɴ�д��ĸ
��������: ��ch��Ӧ�Ĵ�д��ĸ
*/
int toupper(int ch);
/*
isalnum
��������: isalnum
����ԭ��: int isalnum(int ch);
��������: ���ch�Ƿ�����ĸ������
��������: ����ĸ�����ַ��ط�0,���򷵻�0
*/
int isalnum(int ch);
/*
isspace
��������: isspace
����ԭ��: int isspace(int ch);
��������: ���ch�Ƿ��ǿո���������(�����ַ�)���з�
��������: �Ƿ��ط�0,���򷵻�0
����˵��:
�����ļ�: <ctype.h>
*/
 int isspace(int ch);
 /*
isxdigit
��������: isxdigit
����ԭ��: int isxdigit(int ch);
��������: ���ch�Ƿ���һ��16������ѧ�ַ�(��0-9,��A-F,��a-f)
��������: �Ƿ��ط�0,���򷵻�0
����˵��:
�����ļ�: <ctype.h>
*/
int isxdigit(int ch);
 /*
isascii
��������: isascii
����ԭ��: int isascii(int ch)
��������: ���Բ����Ƿ���ASCII��0-127
��������: �Ƿ��ط�0,���򷵻�0
����˵��: ch-�������
*/
int isascii(int ch);

/*
������ĸ��ʮ�����������������ͼ���ַ����ᱻ�ж�Ϊ�����ţ�
*/
int ispunct ( int c );

