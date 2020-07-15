

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