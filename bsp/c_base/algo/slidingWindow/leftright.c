/*
647. 回文子串
难度中等374
给定一个字符串，你的任务是计算这个字符串中有多少个回
文子串。
具有不同开始位置或结束位置的子串，即使是由相同的字符
组成，也会被视作不同的子串。

示例 1：
输入："abc"
输出：3
解释：三个回文子串: "a", "b", "c"
*/

/*
从中心往两侧延伸【通过】
思路
在长度为 N 的字符串中，可能的回文串中心位置有 2N-1 个：
字母，或两个字母中间。
从每一个回文串中心开始统计回文串数量。
回文区间 [a, b] 表示 S[a], S[a+1], ..., S[b] 是回文串，
根据回文串定义可知 [a+1, b-1] 也是回文区间。
算法
对于每个可能的回文串中心位置，
尽可能扩大它的回文区间 [left, right]。
当 left >= 0 and right < N and S[left] == S[right] 时，
扩大区间。此时回文区间表示的回文串为 S[left], S[left+1], ..., S[right]。

*/
int countSubstrings(char * s)
{
	int size = strlen(s);
	int ans = 0;
	for (int center = 0; center < 2 * size -1; center++) {
		int left = center / 2;
		int right = left + center % 2;
		while(left >= 0 && right < size && s[left] == s[right]) {
			ans++;
			left--;
			right++;
		}
	}

	return ans;
}

/*
5. 最长回文子串
给定一个字符串 s，找到 s 中最长的回文子串。
你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"
*/
char * longestPalindrome(char * s)
{
	int slen = strlen(s);
	if (s == NULL || slen <= 1) {
		return s;
	}

	int max = 1;
	int save[2] = {0};
	for (int centor = 0; centor < 2 * slen - 1; centor++) {
		int left = centor / 2;
		int right = left + centor % 2;

		while(left >= 0 && right < slen && s[left] == s[right]) {
			if (right - left + 1 > max) {
				save[0] = left;
				save[1] = right;
				max = right - left + 1 ;
			}

			left--;
			right++;
		}
	}

	s[save[1]  + 1] = '\0';
	return s + save[0];
}

