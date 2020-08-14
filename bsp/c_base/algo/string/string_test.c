

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
1065
�ַ�����������
���� �ַ��� text �� �ַ����б� words, �������е������� [i, j]
ʹ���������Է�Χ�ڵ����ַ��� text[i]...text[j]������ i �� j��
�����ַ����б� words��
ʾ�� 1:
����: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
���: [[3,7],[9,13],[10,17]]
ʾ�� 2:
����: text = "ababa", words = ["aba","ab"]
���: [[0,1],[0,2],[2,3],[2,4]]
����:
ע�⣬���ص���Կ����н��棬���磬"aba" ���� [0,2] ��Ҳ
�� [2,4] ��

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

int** indexPairs(char * text, char ** words, int wordsSize,
	int* returnSize, int** returnColumnSizes)
{
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
12. ����ת��������
�Ѷ��е�326
�������ְ������������ַ��� I�� V�� X�� L��C��D �� M��
�ַ�          ��ֵ
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
���磬 �������� 2 д�� II ����Ϊ�������е� 1��12 д�� XII ��
��Ϊ X + II �� 27 д��  XXVII, ��Ϊ XX + V + II ��
ͨ������£�����������С�������ڴ�����ֵ��ұߡ�
��Ҳ�������������� 4 ��д�� IIII������ IV������ 1 ������
5 ����ߣ�����ʾ�������ڴ��� 5 ��С�� 1 �õ�����ֵ 4 ��
ͬ���أ����� 9 ��ʾΪ IX���������Ĺ���ֻ����������
���������
"	I ���Է��� V (5) �� X (10) ����ߣ�����ʾ 4 �� 9��
"	X ���Է��� L (50) �� C (100) ����ߣ�����ʾ 40 �� 90��
"	C ���Է��� D (500) �� M (1000) ����ߣ�����ʾ 400 �� 900��
����һ������������תΪ�������֡�
����ȷ���� 1 �� 3999 �ķ�Χ�ڡ�
ʾ�� 1:
����: 3
���: "III"
ʾ�� 2:
����: 4
���: "IV"
ʾ�� 3:
����: 9
���: "IX"
ʾ�� 4:
����: 58
���: "LVIII"
����: L = 50, V = 5, III = 3.
ʾ�� 5:
����: 1994
���: "MCMXCIV"
����: M = 1000, CM = 900, XC = 90, IV = 4.

*/

struct Map {
	int num;
	char *lm;
};

char * intToRoman(int num)
{
	struct Map map[13];
	map[0].num = 1;
	map[0].lm = "I";
	map[1].num = 4;
	map[1].lm = "IV";
	map[2].num = 5;
	map[2].lm = "V";
	map[3].num = 9;
	map[3].lm = "IX";
	map[4].num = 10;
	map[4].lm = "X";
	map[5].num = 40;
	map[5].lm = "XL";
	map[6].num = 50;
	map[6].lm = "L";
	map[7].num = 90;
	map[7].lm = "XC";
	map[8].num = 100;
	map[8].lm = "C";
	map[9].num = 400;
	map[9].lm = "CD";
	map[10].num = 500;
	map[10].lm = "D";
	map[11].num = 900;
	map[11].lm = "CM";
	map[12].num = 1000;
	map[12].lm = "M";

	char *ret = (char *)calloc(1024, sizeof(char));
	for (int i = 0; i < 13; i++) {
		int cur = num / map[12 - i].num;
		while(cur--) {
			strcat(ret, map[12 - i].lm);
		}

		num %=  map[12 - i].num;
	}

	return ret;
}

/*
443. ѹ���ַ���
�Ѷȼ�119
����һ���ַ���ʹ��ԭ���㷨����ѹ����
ѹ����ĳ��ȱ���ʼ��С�ڻ����ԭ���鳤�ȡ�
�����ÿ��Ԫ��Ӧ���ǳ���Ϊ1 ���ַ������� int �������ͣ���
�����ԭ���޸���������󣬷���������³��ȡ�

���ף�
���ܷ��ʹ��O(1) �ռ������⣿

ʾ�� 1��
���룺
["a","a","b","b","c","c","c"]

�����
���� 6 �����������ǰ 6 ���ַ�Ӧ���ǣ�["a","2","b","2","c","3"]

˵����
"aa" �� "a2" �����"bb" �� "b2" �����"ccc" �� "c3" �����

*/
int compress(char* chars, int charsSize){
    int write = 0;
    char buf[1000];
    for(int read=0, anchor=0;read<charsSize;anchor=read)
    {
        while(read<charsSize&&chars[read]==chars[anchor])
            read++;
        chars[write++] = chars[anchor];
        if(read-anchor==1)
            continue;
        sprintf(buf,"%d",read-anchor);
        for(int i=0;i<strlen(buf);i++)
            chars[write++] = buf[i];
    }
    return write;
}

/*
271. �ַ����ı��������
�������һ���㷨�����Խ�һ�� �ַ����б� �����Ϊһ�� �ַ���������������ַ����ǿ���ͨ��������и�Ч���͵ģ����ҿ����ڽ��ն˱������ԭ�����ַ����б�

1 �Ż������ͷ��������º�����

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
2 �Ż������շ��������º�����

vector<string> decode(string s) {
  //... your code
  return strs;
}
1 �Ż������ͷ���ִ�У�

string encoded_string = encode(strs);
2 �Ż������շ���ִ�У�

vector<string> strs2 = decode(encoded_string);
��ʱ��2 �Ż������շ����� strs2 ��Ҫ�� 1 �Ż������ͷ����� strs ��ͬ��

������ʵ����� encode �� decode ������

ע�⣺

��Ϊ�ַ������ܻ���� 256 ���Ϸ� ascii �ַ��е��κ��ַ������������㷨����Ҫ�ܹ������κο��ܻ���ֵ��ַ���
����ʹ�� �����Ա������ȫ�ֱ����� �� ����̬������ ���洢��Щ״̬�����ı���ͽ����㷨Ӧ���Ƿ�״̬�����ġ�
�벻Ҫ�����κη����⣬���� eval �ֻ����� serialize ֮��ķ������������ּ����Ҫ���Լ�ʵ�� �����롱 �� �����롱 �㷨��
*/

/** Encodes a list of strings to a single string */
char* encode(char** strs, int strsSize) {
	char *out = (char *)calloc(102400, sizeof(char));
	for (int i = 0; i < strsSize; i++) {
		sprintf(out + strlen(out), "%08d%s", strlen(strs[i]), strs[i]);
	}
    //printf("[e]%s\n",out);
	return out;
}

/**
 * Decodes a single string to a list of strings.
 *
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//00000005Hello00000005World
char** decode(char* s, int* returnSize) {
	char *p = s;
	*returnSize = 0;
	char **out = (char **)calloc(1024, sizeof(char*));
	while(*p != '\0') {
		int len;
		char str[16];
		memset(str, 0, sizeof(str));
		strncpy(str, p, 8);//û�н�����
		len = atoi(str);
		out[*returnSize] = (char *)calloc(len + 1, sizeof(char));
		strncpy(out[*returnSize], p + 8, len);
		p += len + 8;
		(*returnSize)++;
	}

	return out;
}

// Your functions will be called as such:
// char* s = encode(strs, strsSize);
// decode(s, &returnSize);

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
����һ���ǿյ��ַ������ж����Ƿ����������һ���Ӵ��ظ���ι��ɡ��������ַ���ֻ����СдӢ����ĸ�����ҳ��Ȳ�����10000��
ʾ�� 1:
����: "abab"

���: True

����: �������ַ��� "ab" �ظ����ι��ɡ�
ʾ�� 2:
����: "aba"

���: False

*/

bool repeatedSubstringPattern(char * s){
    int len = strlen(s);
    char * c = (char *) malloc(sizeof(char) * (len * 2));
    memcpy(c, s + 1, len);
    strncat(c, s, len - 1);
    bool ret = strstr(c, s);
    free(c);
    return ret;
}

/*
1023. �շ�ʽƥ��
�Ѷ��е�17
������ǿ��Խ�Сд��ĸ����ģʽ�� pattern �õ�����ѯ�� query����ô����ѯ�������ģʽ��ƥ�䡣�����ǿ������κ�λ�ò���ÿ���ַ���Ҳ���Բ��� 0 ���ַ�����
��������ѯ�б� queries����ģʽ�� pattern�������ɲ���ֵ��ɵĴ��б� answer��ֻ���ڴ����� queries[i] ��ģʽ�� pattern ƥ��ʱ�� answer[i] ��Ϊ true������Ϊ false��

ʾ�� 1��
���룺queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
�����[true,false,true,true,false]
ʾ����
"FooBar" �����������ɣ�"F" + "oo" + "B" + "ar"��
"FootBall" �����������ɣ�"F" + "oot" + "B" + "all".
"FrameBuffer" �����������ɣ�"F" + "rame" + "B" + "uffer".
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool isMatch(const char* query, const char* pattern){
    while (*pattern != 0) {
        if (*query == *pattern) {
            query++;
            pattern++;
        } else {
            if (isupper(*query) || *query == 0)
                return false;
            query++;
        }
    }
    while (*query != 0) {
        if (isupper(*query))
            return false;
        query++;
    }
    return true;
}

bool* camelMatch(char ** queries, int queriesSize, char * pattern, int* returnSize){
    bool* matches = (bool*)calloc(sizeof(bool), queriesSize);
    for(int i = 0; i < queriesSize; i++){
        if (isMatch(queries[i], pattern))
            matches[i] = true;
    }
    *returnSize = queriesSize;
    return matches;
}

/*
67. ���������
�Ѷȼ�453
���������������ַ������������ǵĺͣ��ö����Ʊ�ʾ����
����Ϊ �ǿ� �ַ�����ֻ�������� 1 �� 0��

ʾ�� 1:
����: a = "11", b = "1"
���: "100"
ʾ�� 2:
����: a = "1010", b = "1011"
��

*/
char * addBinary(char * a, char * b)
{
	int alen = strlen(a);
	int blen = strlen(b);
	int rlen = fmax(alen, blen) + 2;

	char *res = (char *)calloc(rlen, sizeof(char));
	char *aptr = a + alen - 1;
	char *bptr = b + blen - 1;
	char *rptr = res + rlen - 2;
	char high = 0;
	while (aptr >= a && bptr >= b) {
		char ia = *aptr - '0';
		char ib = *bptr - '0';
		char sum = ia + ib + high;
		*rptr = sum % 2 + '0';
		high = sum / 2;
		aptr--;
		bptr--;
		rptr--;
	}

	if (aptr < a) {
		while(bptr >= b) {
			char ib = *bptr - '0';
			char sum = ib + high;
			*rptr = sum % 2 + '0';
			high = sum / 2;
			bptr--;
			rptr--;
		}
	} else if (bptr < b) {
		while(aptr >= a) {
			char ia = *aptr - '0';
			char sum = ia + high;
			*rptr = sum % 2 + '0';
			high = sum / 2;
			aptr--;
			rptr--;
		}
	}

	if (high) {
		*rptr = high + '0';
	}

	while(*res == 0) {
		res++;
	}

	return res;
}

char * addBinary(char * a, char * b)
{
	int alen = strlen(a);
	int blen = strlen(b);
	int rlen = fmax(alen, blen) + 2;

	char *res = (char *)calloc(rlen, sizeof(char));
	char *aptr = a + alen - 1;
	char *bptr = b + blen - 1;
	char *rptr = res + rlen - 2;
	char high = 0;

	while (rptr > res) {
		char ia = aptr >= a ? *aptr - '0' : 0;
		char ib = bptr >= b ? *bptr - '0' : 0;
		char sum = ia + ib + high;
		*rptr = sum % 2 + '0';
		high = sum / 2;
		aptr--;
		bptr--;
		rptr--;
	}

	if (high) {
		*rptr = '1';
	}

	while(*res == 0) {
		res++;
	}

	return res;
}

void reserve(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char t = s[i];
        s[i] = s[len - i - 1], s[len - i - 1] = t;
    }
}

char* addBinary(char* a, char* b) {
    reserve(a);
    reserve(b);

    int len_a = strlen(a), len_b = strlen(b);
    int n = fmax(len_a, len_b), carry = 0, len = 0;
    char* ans = (char*)malloc(sizeof(char) * (n + 2));
    for (int i = 0; i < n; ++i) {
        carry += i < len_a ? (a[i] == '1') : 0;
        carry += i < len_b ? (b[i] == '1') : 0;
        ans[len++] = carry % 2 + '0';
        carry /= 2;
    }

    if (carry) {
        ans[len++] = '1';
    }
    ans[len] = '\0';
    reserve(ans);

    return ans;
}

/*
415. �ַ������
�Ѷȼ�248
���������ַ�����ʽ�ķǸ����� num1 ��num2 ���������ǵĺ͡�

��ʾ��
1.	num1 ��num2 �ĳ��ȶ�С�� 5100
2.	num1 ��num2 ��ֻ�������� 0-9
3.	num1 ��num2 ���������κ�ǰ����
4.	�㲻��ʹ���κ΃Ƚ� BigInteger �⣬ Ҳ����ֱ�ӽ�������ַ���ת��Ϊ������ʽ
��: "10101"


*/

#define swap(a,b) ((a) ^= (b), (b) ^= (a) ,(a) ^= (b))
void strrevSelf_pos(char *s, int begin, int end)
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

void strrevSelf(char *s)
{
	strrevSelf_pos(s, 0, strlen(s) - 1);
}

char * addStrings(char * num1, char * num2)
{
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int lenr = fmax(len1, len2);
	char *res = (char *)calloc(lenr + 2, sizeof(char));

	strrevSelf(num1);
	strrevSelf(num2);
	int pos = 0;
	int i = 0;
	for (; i < lenr; i++) {
		int sum = 0;
		sum += pos;
		sum += i >= len1 ? 0 : num1[i] - '0';
		sum += i >= len2 ? 0 : num2[i] - '0';

		res[i] = sum % 10 + '0';
		pos = sum / 10;
	}

	 if (pos != 0) {
		res[i] = pos + '0';
		pos = 0;
	 }

	strrevSelf(res);
	return res;
}

char* addStrings(char* num1, char* num2) {
    int i = strlen(num1) - 1, j = strlen(num2) - 1, add = 0;
    char* ans = (char*)malloc(sizeof(char) * (fmax(i, j) + 3));
    int len = 0;
    while (i >= 0 || j >= 0 || add != 0) {
        int x = i >= 0 ? num1[i] - '0' : 0;
        int y = j >= 0 ? num2[j] - '0' : 0;
        int result = x + y + add;
        ans[len++] = '0' + result % 10;
        add = result / 10;
        i--, j--;
    }
    // �������Ժ�Ĵ���Ҫ��ת����
    for (int i = 0; 2 * i < len; i++) {
        int t = ans[i];
        ans[i] = ans[len - i - 1], ans[len - i - 1] = t;
    }
    ans[len++] = 0;
    return ans;
}

/*
214. ��̻��Ĵ�
�Ѷ�����176
����һ���ַ��� s�������ͨ�����ַ���ǰ������ַ�����ת��Ϊ���Ĵ����ҵ������ؿ��������ַ�ʽת������̻��Ĵ���
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
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a)  ((a) >= 0 ? (a) : -(a))
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