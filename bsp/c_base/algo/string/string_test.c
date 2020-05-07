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

