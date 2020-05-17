/*
583. �����ַ�����ɾ������
�Ѷ��е�96
������������ word1 �� word2��
�ҵ�ʹ�� word1 �� word2 ��ͬ�������С������
ÿ������ɾ������һ���ַ����е�һ���ַ���

ʾ����
����: "sea", "eat"
���: 2
����: ��һ����"sea"��Ϊ"ea"���ڶ�����"eat"��Ϊ"ea"

*/
int minDistance(char * word1, char * word2)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);

	int dp[len1 + 1][len2 + 1];
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (word1[i -1] == word2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return len1 + len2 - 2 * dp[len1][len2];
}

/*
5. ������Ӵ�
����һ���ַ��� s���ҵ� s ����Ļ����Ӵ�������Լ��� s ����󳤶�Ϊ 1000��

ʾ�� 1��

����: "babad"
���: "bab"
ע��: "aba" Ҳ��һ����Ч�𰸡�
ʾ�� 2��

����: "cbbd"
���: "bb"
*/
/*������ɢ����*/
char * longestPalindrome(char * s){
    if(strlen(s)==0||strlen(s)==1) return s;
    int i,start,left,right,count,len;
    start = len =0;
    for(i=0;s[i]!='\0';i+=count){
        count = 1;
        left=i-1;
        right = i+1;
        while(s[right]!='\0'&&s[i]==s[right]){ //�����ظ��ַ���
            right++;
            count++;
        }
        while(left>=0 && s[right]!='\0' && s[left] == s[right]){
            left--;
            right++;
        }
        if(right-left-1>len){
            start = left+1;
            len = right-left-1;
        }
    }
    s[start + len] = '\0';      // ԭ���޸ķ���
    return s + start;
}

/*dp*/
char * longestPalindrome(char * s)
{
    if (s == NULL || strlen(s) < 1) return "";
	int length = strlen(s);
	bool dp[length][length];
	int maxlen = 0;
	char *ret = "";
	for (int len = 1; len <= length; len++) {
		for (int  start = 0; start < length; start++) {
			int end = start + len - 1;
			if (end >= length)
				break;

			dp[start][end] = (len == 1 || len == 2 || dp[start + 1][end - 1]) && s[start] == s[end];
			if (dp[start][end] && len > maxlen) {
				maxlen = len;
				ret = strdup(s + start);
				ret[len] = '\0';
			}
		}
	}

	return ret;
}

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
    if (s == NULL || strlen(s) < 1) return "";

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


/*
43. �ַ������
�Ѷ��е�329
�����������ַ�����ʽ��ʾ�ķǸ����� num1 �� num2������ num1 �� num2 �ĳ˻������ǵĳ˻�Ҳ��ʾΪ�ַ�����ʽ��
ʾ�� 1:
����: num1 = "2", num2 = "3"
���: "6"
ʾ�� 2:
����: num1 = "123", num2 = "456"
���: "56088"

*/
/*
������˵õ��ĳ˻��ĳ��Ȳ��ᳬ���������ֵĳ���֮�ͣ���num1����Ϊlength1��num2 ����Ϊlenght2���� num1 x num2 �ĳ��Ȳ��ᳬ�� length1 + length2
���о��ǳ˵�ʱ����Ҫ��λ��ԭ�򣬱���6 x 8�õ��� 48 ΪɶҪ��6 x 9�õ��� 54 ��λ��ӣ���Ϊ 8 ��ʮλ�ϵ����֣��䱾���൱��80�����Դ���һλʵ����ĩβ��Ҫ����0
num1 �� num2 ������λ�õ�����������ˣ��õ�����λ�������ս���е�λ����ȷ���ģ����� num1 ��λ��Ϊi�����ֳ��� num2 ��λ��Ϊj�����֣���ô�õ�����λ���ֵ�λ��Ϊ i+j �� i+j+1����Ҳ���ɴ�λ��������
���ȿ��������ռ䣬һ�������洢��λ��˵��м�����int���ͣ�����һ����Ϊ���շ��صĽ����char���͡���Ҫע����Ǻ�һ��ָ����Ҫ��totalLength��һ���ַ�������C���Ե���ָʾ�ַ�������Ľ���������int���͵��м�����ʼ��Ϊ0��

����Ҫ�Ӹ�λ�Ͽ�ʼ��ˣ����Դ� num1 �� num2 �ַ�����β����ʼ��ǰ�������ֱ���ȡ����Ӧλ���ϵ��ַ�������תΪ���ͺ���ˣ���num1[i]��num[j]��˵Ľ���ۼӴ洢��value[i+j+1]���У�ע���������ۼӡ�������� 89 x 76 Ϊ����num1[1] x num2[0]�Ľ�� 48 ����Ҫ��num1[0] x num2[1]�Ľ�� 63����Ժ�һ���洢��value[2]�����ٽ�����һ���Ĵ�����ġ�

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
// �������β����ʼ����������iλ�ĸ�λͨ��/�ۼӵ���i-1λ��Ȼ��ͨ��%�����õ�ǰλ�����֡�
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
���磬 �������� 2 д�� II ����Ϊ�������е� 1��12 д�� XII ����Ϊ X + II �� 27 д��  XXVII, ��Ϊ XX + V + II ��
ͨ������£�����������С�������ڴ�����ֵ��ұߡ���Ҳ�������������� 4 ��д�� IIII������ IV������ 1 ������ 5 ����ߣ�����ʾ�������ڴ��� 5 ��С�� 1 �õ�����ֵ 4 ��ͬ���أ����� 9 ��ʾΪ IX���������Ĺ���ֻ�������������������
"	I ���Է��� V (5) �� X (10) ����ߣ�����ʾ 4 �� 9��
"	X ���Է��� L (50) �� C (100) ����ߣ�����ʾ 40 �� 90��
"	C ���Է��� D (500) �� M (1000) ����ߣ�����ʾ 400 �� 900��
����һ������������תΪ�������֡�����ȷ���� 1 �� 3999 �ķ�Χ�ڡ�
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
712. �����ַ�������СASCIIɾ����
�Ѷ��е�93
���������ַ���s1, s2���ҵ�ʹ�����ַ����������ɾ���ַ���ASCIIֵ����С�͡�
ʾ�� 1:
����: s1 = "sea", s2 = "eat"
���: 231
����: �� "sea" ��ɾ�� "s" ���� "s" ��ֵ(115)�����ܺ͡�
�� "eat" ��ɾ�� "t" ���� 116 �����ܺ͡�
����ʱ�������ַ�����ȣ�115 + 116 = 231 ���Ƿ�����������С�͡�

*/

/*
������Ѱ��һ����ͬ�����У�
���ַ���s1��s2ɾ��Ϊ��������ʱ��ɾ��
��ASCII�ۺ���С���ȼ�����һ���ַ���s1
��s2��ASCII���ܺ����Ĺ�ͬ�����С�
��Ϊs1��s2���ܺ͹̶�������ͬ�����е�
�ܺ����ʱ��ɾ����Ϊ�������еĴ��۱�Ȼ
��С��
*/
int minimumDeleteSum(char * s1, char * s2){
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    int dp[len1 + 1][len2 + 1];
    memset(dp,0, sizeof(dp));

    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= len2; ++j)
        {
            if(s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + s1[i - 1];
            else
                dp[i][j] = fmax(dp[i - 1][j],dp[i][j - 1]);
        }

    int sum = 0;
    for (int i = 0; i < len1; ++i)
        sum += s1[i];
    for (int i = 0; i < len2; ++i)
        sum += s2[i];
    return sum - 2 * dp[len1][len2];

}


