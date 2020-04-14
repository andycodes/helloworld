/*
583. 两个字符串的删除操作
难度中等96
给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

示例：
输入: "sea", "eat"
输出: 2
解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"

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