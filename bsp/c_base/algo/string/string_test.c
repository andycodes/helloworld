int expandAroundCenter(char *s, int left, int right)
{
    int L = left, R = right;
    while (L >= 0 && R < strlen(s) && s[L] == s[R]) {
        L--;
        R++;
    }
    return R - L - 1;
}

/*������չ�㷨*/
char * longestPalindrome(char * s)
{
	if (s == NULL || strlen(s) < 1)
	return "";

	if (strlen(s) == 1)
		return s;

	int start = 0, end = 0;
	int mlen = 0;
	for (int i = 0; i < strlen(s); i++) {
		int len1 = expandAroundCenter(s, i, i);//һ��Ԫ��Ϊ����
		int len2 = expandAroundCenter(s, i, i + 1);//����Ԫ��Ϊ����
		mlen = fmax(fmax(len1, len2), mlen);
		if (mlen > end - start + 1) {
			start = i - (mlen - 1) / 2;
			end = i + mlen / 2;
		}
	}

	char *ret = strdup(s + start);
	ret[mlen] = '\0';
	return ret;
}

/*
670. ��󽻻�
�Ѷ��е�77
����һ���Ǹ���������������Խ���һ�������е�������λ��
�������ܵõ������ֵ��
ʾ�� 1 :
����: 2736
���: 7236
����: ��������2������7��
ʾ�� 2 :
����: 9973
���: 9973
����: ����Ҫ������

*/
static int cmp(const void *a, const void *b)
{
    return *((char*)b) - *((char*)a);
}

int maximumSwap(int num)
{
	if (num == 0) {
		return 0;
	}

	char str0[16] = {0};
	char sortstr[16] = {0};

	sprintf(str0, "%d", num);
	sprintf(sortstr, "%d", num);

	int len = (int) strlen(sortstr);

	qsort(sortstr, len, sizeof(char), cmp);

	for (int i = 0; i < len; i++) {
		if (sortstr[i] != str0[i]) {
			char *p = strrchr(&str0[i], sortstr[i]);
			*p = str0[i];
			str0[i] = sortstr[i];
			break;
		}
	}

	return atoi(str0);
}


/*
43. �ַ������
�Ѷ��е�329
�����������ַ�����ʽ��ʾ�ķǸ����� num1 �� num2��
���� num1 �� num2 �ĳ˻������ǵĳ˻�Ҳ��ʾΪ�ַ�����ʽ��
ʾ�� 1:
����: num1 = "2", num2 = "3"
���: "6"
ʾ�� 2:
����: num1 = "123", num2 = "456"
���: "56088"

*/
char * multiply(char * num1, char * num2)
{
	if (num1[0] == '0' || num2[0] == '0')
		return "0";

	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int dp[len1 + len2 + 1];
	memset(dp, 0, sizeof(dp));
	//�����λ��˵ĳ˻�ÿ��Ԫ�ص�����
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			dp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
		}
	}
/*
�������β����ʼ����������iλ�ĸ�λͨ��/�ۼӵ���i-1λ��
Ȼ��ͨ��%�����õ�ǰλ�����֡�
*/
	for (int i = len1 + len2; i > 0; i--) {
		if (dp[i] < 10)
			continue;
		dp[i - 1] += dp[i] / 10;
		dp[i] %= 10;
	}

	char *ret = (char *)calloc(1024, sizeof(char));
	for (int i = 0, j = 0;  i < len1 + len2; i++) {
		// �ų���ʼ��ʼ��'0'ֱ����һ����0����
		if ((j == 0) && (dp[i] == 0)) {
			continue;
		}
		ret[j++] = dp[i] + '0';
	}

	return ret;
}

/*
161. ���Ϊ 1 �ı༭����
�Ѷ��е�27
���������ַ��� s �� t���ж����ǵı༭�����Ƿ�Ϊ 1��
ע�⣺
����༭������� 1 �����ֿ��ܵ����Σ�
1.	�� s �в���һ���ַ��õ� t
2.	�� s ��ɾ��һ���ַ��õ� t
3.	�� s ���滻һ���ַ��õ� t
ʾ�� 1��
����: s = "ab", t = "acb"
���: true
����: ���Խ� 'c' �����ַ��� s ���õ� t��
*/
bool isOneEditDistance(char * s, char * t)
{
    int ns=strlen(s),nt=strlen(t);
    if(ns>nt)
        return isOneEditDistance(t,s);
    if(nt-ns>1)return 0;
    int replace=0;
    for(int i=0;i<ns;i++){
        if(s[i]!=t[i]){
            if(nt!=ns)
              //  return (s[i] ==t.substr(i+1));
			return !strcmp(s + i, t + i + 1);
            //else return (i==ns-1)||(s.substr(i+1)==t.substr(i+1));
		else return (i==ns-1)||(!strcmp(s + i+1, t +i+1));
        }
    }
    return nt!=ns;
}

/*
459. �ظ������ַ���
�Ѷȼ�243
����һ���ǿյ��ַ������ж����Ƿ����������һ���Ӵ���
����ι��ɡ��������ַ���ֻ����СдӢ����ĸ�����ҳ���
������10000��
ʾ�� 1:
����: "abab"
���: True
����: �������ַ��� "ab" �ظ����ι��ɡ�
ʾ�� 2:
����: "aba"
���: False
*/
bool repeatedSubstringPattern(char * s)
{
	int len = strlen(s);
	char cmp[len * 2];
	memset(cmp, 0, sizeof(cmp));

	memcpy(cmp, s + 1, len);
	strncat(cmp, s, len - 1);
	bool ret = strstr(cmp, s);
	return ret;
}

/*
214. ��̻��Ĵ�
�Ѷ�����176
����һ���ַ��� s�������ͨ�����ַ���ǰ������ַ�����ת
��Ϊ���Ĵ����ҵ������ؿ��������ַ�ʽת������̻��Ĵ���
ʾ�� 1:
����: "aacecaaa"
���: "aaacecaaa"
ʾ�� 2:
����: "abcd"
���: "dcbabcd"


*/
//�ж��Ƿ��ǻ��Ĵ�, �����ַ����ķ�Χ
bool isPalindromic(char *s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

char * shortestPalindrome(char * s)
{
	int slen = strlen(s);
	int end = slen - 1;
    //�ҵ����Ĵ��Ľ�β, �� end ���
    for (; end > 0; end--) {
        if (isPalindromic(s, 0, end)) {
            break;
        }
    }


    //��ĩβ�ļ�������Ȼ��ӵ�ԭ�ַ�����ͷ
	char *res = (char *)calloc(2 * slen + 1, sizeof(char));
	int j = 0;
	for (int i = slen - 1; i > end; i--) {
		res[j++] = s[i];
	}

	strcat(res, s);
	return res;
}

/*
564. Ѱ������Ļ�����
�Ѷ�����70
����һ������ n ������Ҫ�ҵ���������Ļ�������������������
"�����"����Ϊ����������ľ���ֵ��С��
ʾ�� 1:
����: "123"
���: "121"
ע��:
1.	n �����ַ�����ʾ�����������䳤�Ȳ�����18��
2.	����ж�������������С���Ǹ���
ͨ������2,444
�ύ����15,226
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE    18
typedef long long int64;

static int64 CalcHighHalfVal(char *n)
{
    char high_half[MAX_SIZE / 2 + 2];
    int  inputlen, halflen;

    inputlen = strlen(n);
    halflen = (inputlen + 1) / 2;
    strncpy(high_half, n, halflen);
    high_half[halflen] = '\0';

    return atoll(high_half);
}

/* �����������ֵĸ߰벿��hhalf������߰벿�ֵĻ������֡�lowhalflen��ʾ��Ҫ����ĵͰ벿�ֳ��� */
static int64 PalindByHighHalf(int64 hhalfval, int lowhalflen)
{
    int halflen, i;
    char buff[MAX_SIZE + 2];

    if (hhalfval == 0) {
        /* 10~19֮������֣���1��Ļ������̶ֹ�Ϊ9 */
        return 9;
    }

    snprintf(buff, sizeof(buff), "%lld", hhalfval);
    halflen = strlen(buff);

    if (lowhalflen <= halflen) {
        for (i = 0; i < lowhalflen; i++) {
            buff[halflen + lowhalflen - 1 - i] = buff[i];
        }
    } else {
        /* ����������Ϊ1000��ǰ�벿��Ϊ10���������1ʱ���9����ʱlowhalflenΪ2��halflenΪ1�����ֵͰ벿�ֳ��ȴ��ڸ߰벿�ֵ����
            ��ʱ����Ҫ�ԵͰ벿��ȫ�����9 */
        for (i = 0; i < lowhalflen; i++) {
            buff[halflen + i] = '9';
        }
    }
    buff[halflen + lowhalflen] = '\0';

    return atoll(buff);
}


static char strbuff[MAX_SIZE + 2];
char *nearestPalindromic(char *n)
{
    int64 inputval, outval, outval0, outval1;
    int64 halfval;
    int  inputlen, halflen;

    inputval = atoll(n);
    if (inputval <= 10) {
        outval = inputval - 1;
        snprintf(strbuff, sizeof(strbuff), "%lld", outval);
        return strbuff;
    }

    inputlen = strlen(n);
    halflen = (inputlen + 1) / 2;
    halfval = CalcHighHalfVal(n);

    outval1 = PalindByHighHalf(halfval, inputlen - halflen);
    if (outval1 > inputval) {
        outval0 = PalindByHighHalf(halfval - 1, inputlen - halflen);
    } else if (outval1 < inputval){
        outval0 = PalindByHighHalf(halfval + 1, inputlen - halflen);
    } else {
        outval0 = PalindByHighHalf(halfval - 1, inputlen - halflen);
        outval1 = PalindByHighHalf(halfval + 1, inputlen - halflen);
    }

    outval = ABS(inputval - outval0) < ABS(inputval - outval1) ? outval0 : outval1;
    outval = ABS(inputval - outval0) == ABS(inputval - outval1) ? MIN(outval0, outval1) : outval;

    snprintf(strbuff, sizeof(strbuff), "%lld", outval);
    return strbuff;
}

/*
696. �����������Ӵ�
����һ���ַ��� s�����������ͬ����0��1�ķǿ�(����)���ַ�����������������Щ���ַ����е�����0������1���������һ��ġ�

�ظ����ֵ��Ӵ�Ҫ�������ǳ��ֵĴ�����

ʾ�� 1 :

����: "00110011"
���: 6
����: ��6���Ӵ�������ͬ����������1��0����0011������01������1100������10������0011�� �� ��01����

��ע�⣬һЩ�ظ����ֵ��Ӵ�Ҫ�������ǳ��ֵĴ�����

���⣬��00110011��������Ч���Ӵ�����Ϊ���е�0����1��û�������һ��
*/
int countBinarySubstrings(char* s) {
    int n = strlen(s);
    int counts[n], counts_len = 0;
    memset(counts, 0, sizeof(counts));
    int ptr = 0;
    while (ptr < n) {
        char c = s[ptr];
        int count = 0;
        while (ptr < n && s[ptr] == c) {
            ++ptr;
            ++count;
        }
        counts[counts_len++] = count;
    }
    int ans = 0;
    for (int i = 1; i < counts_len; ++i) {
        ans += fmin(counts[i], counts[i - 1]);
    }
    return ans;
}

int countBinarySubstrings(char* s) {
    int ptr = 0, n = strlen(s), last = 0, ans = 0;
    while (ptr < n) {
        char c = s[ptr];
        int count = 0;
        while (ptr < n && s[ptr] == c) {
            ++ptr;
            ++count;
        }
        ans += fmin(count, last);
        last = count;
    }
    return ans;
}

/*
541. ��ת�ַ��� II
����һ���ַ��� s ��һ������ k������Ҫ�Դ��ַ�����ͷ�����ÿ�� 2k ���ַ���ǰ k ���ַ����з�ת��

���ʣ���ַ����� k ������ʣ���ַ�ȫ����ת��
���ʣ���ַ�С�� 2k �����ڻ���� k ������תǰ k ���ַ��������ַ�����ԭ����


ʾ��:

����: s = "abcdefg", k = 2
���: "bacdfeg"
*/
char * reverseStr(char * s, int k)
{
        for (int start = 0; start < strlen(s); start += 2 * k) {
            int i = start, j = fmin(start + k - 1, strlen(s) - 1);
            while (i < j) {
                char tmp = s[i];
                s[i++] = s[j];
                s[j--] = tmp;
            }
        }
        return s;
}

/*
38. �������
����һ�������� n �����������еĵ� n �

��������С���һ���������У������� 1 ��ʼ�������е�ÿһ��Ƕ�ǰһ���������

����Խ����������ɵݹ鹫ʽ����������ַ������У�

countAndSay(1) = "1"
countAndSay(n) �Ƕ� countAndSay(n-1) ��������Ȼ��ת������һ�������ַ�����
ǰ�������£�

1.     1
2.     11
3.     21
4.     1211
5.     111221
��һ�������� 1
����ǰһ�������� 1 �� �� һ �� 1 �������� "11"
����ǰһ�������� 11 �� �� �� �� 1 �� ������ "21"
����ǰһ�������� 21 �� �� һ �� 2 + һ �� 1 �� ������ "1211"
����ǰһ�������� 1211 �� �� һ �� 1 + һ �� 2 + �� �� 1 �� ������ "111221"
*/
/* β�ݹ� */
char *countHelper(char *s, int n)
{
    if (n == 1)
        return s;
    else
    {
        //����һ����
        int count;
        char ch[10000];
        char *p = ch;
        //һֱ����
        while (*s!='\0')
        {
            count = 1;
            //���һֱ��ͬһ����
            while (*s==*(s+1))
            {
                count++;
                s++;
            }
            //��һ��������
            *p++ = (char)(count+'0');
            *p++ = *s++;
        }
        return countHelper(ch, n - 1);
    }
}

char *countAndSay(int n)
{
    return countHelper("1", n);
}

/*
556. ��һ������Ԫ�� III
����һ��32λ������ n������Ҫ�ҵ���С��32λ���������� n �д��ڵ�λ����ȫ��ͬ��������ֵ����n�����������������32λ�������򷵻�-1��

ʾ�� 1:

����: 12
���: 21
ʾ�� 2:

����: 21
���: -1
*/
void Quick_sort(int *p, int left, int right){//��������--����--�ݹ��
	if(left < right){
		int l = left;
		int r = right;
		int key = p[l];
		while(l < r){//l == r ����ʱ����
			while(l < r && p[r] < key){//���������Ҵ���/����key����
				--r;
			}
			p[l] = p[r];
			while(l < r && p[l] >= key){//����������С��key����
				++l;
			}
			p[r] = p[l];
		}
		p[l] = key;
		Quick_sort(p, left, l - 1);//�ݹ����
		Quick_sort(p, r + 1, right);
    }
}

int nextGreaterElement(int n){
    const int over = 2147483647;//2^(31)-1
    int res = 0;
    int flag = -1;//��ת��
    int stack[32];//˳��ջ
    int top = -1;
    for (; n != 0; n /= 10){
        stack[++top] = n % 10;//����λ->��λ������ջ
    }
    for (int i = 0; i < top; ++i){
        if (stack[i+1] < stack[i]){//Ѱ���Ƿ���ڷ�ת��
            flag = i+1;//��ת��
            break;
        }
    }
    if (flag != -1){//�з�ת��
        for (int i = 0; i < flag; ++i){//������ת��֮ǰ�ĵ�λ
            if (stack[i] > stack[flag]){//�ҵ�һλ���ڷ�ת�����С������
                int tmp = stack[flag];//���߽���
                stack[flag] = stack[i];
                stack[i] = tmp;
                break;
            }
        }
        Quick_sort(stack, 0, flag-1);//����ת��֮ǰ�ĵ�λ->��ת���λ����������,�����С������
        for (; top > -1; --top){//ȫ����ջ����µ���
            if ( res > over/10 || (res == over/10 && stack[top] > 7) ){//��ֵ���
                return -1;//������������32λ����
            }
            res = stack[top] + res*10;
        }
    }
    else {//�޷�ת�㣬������λ->��λ������ģ��������з����������
        res = -1;
    }
    return res;
}

/*
385. �����﷨������
����һ�����ַ�����ʾ��������Ƕ���б�ʵ��һ�����������﷨��������

�б��е�ÿ��Ԫ��ֻ����������������Ƕ���б�

��ʾ������Լٶ���Щ�ַ������Ǹ�ʽ���õģ�

�ַ����ǿ�
�ַ����������ո�
�ַ���ֻ��������0-9��[��-��,��]


ʾ�� 1��

���� s = "324",

��Ӧ�÷���һ�� NestedInteger ��������ֻ��������ֵ 324��
*/
/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Initializes an empty nested list and return a reference to the nested integer.
 * struct NestedInteger *NestedIntegerInit();
 *
 * // Return true if this NestedInteger holds a single integer, rather than a nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Set this NestedInteger to hold a single integer.
 * void NestedIntegerSetInteger(struct NestedInteger *ni, int value);
 *
 * // Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 * void NestedIntegerAdd(struct NestedInteger *ni, struct NestedInteger *elem);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 */


// find number and return next char pointer
char *GetNum(char *s, int *num)
{
    *num = 0;
    int neg = 1;
    if (*s == '-') {
        neg = -1;
        ++s;
    }
    while (*s >= '0' && *s <= '9') {
        *num = *num * 10 + *s++ - '0';
    }
    *num *= neg;
    return s;
}

// find the corresponding ']' and return next char pointer, s starts with '['
char *FindBracket(char *s) {
    ++s;
    for (int i = 1; i > 0; ++s) {
        if (*s == '[')
            ++i;
        else if (*s == ']')
            --i;
    }
    return s;
}

struct NestedInteger *deserialize(char *s) {
    if (*s != '[') {
        int n;
        GetNum(s, &n);
        struct NestedInteger *nestInt = NestedIntegerInit();
        NestedIntegerSetInteger(nestInt, n);
        return nestInt;
    }
    int bracket = 1;
    ++s;
    struct NestedInteger *ret = NestedIntegerInit();
    while (*s != ']') {
        if (*s == ',') {
            ++s;
        } else if (*s == '-' || (*s >= '0' && *s <= '9')) {
            int n;
            s = GetNum(s, &n);
            struct NestedInteger *nestInt = NestedIntegerInit();
            NestedIntegerSetInteger(nestInt, n);
            NestedIntegerAdd(ret, nestInt);
        } else {
            struct NestedInteger *nestInt = deserialize(s);
            NestedIntegerAdd(ret, nestInt);
            s = FindBracket(s);
        }
    }
    return ret;
}
