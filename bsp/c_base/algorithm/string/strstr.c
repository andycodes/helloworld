#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*暴力算法的复杂度是O(m  n)*/
char *strstr(const char *haystack, const char *needle) {
// if needle is empty return the full string
if (!*needle) return (char*) haystack;
const char *p1;
const char *p2;
const char *p1_advance = haystack;
for (p2 = &needle[1]; *p2; ++p2) {
p1_advance++; // advance p1_advance M-1 times
}
for (p1 = haystack; *p1_advance; p1_advance++) {
char *p1_old = (char*) p1;
p2 = needle;
while (*p1 && *p2 && *p1 == *p2) {
p1++;
p2++;
}
if (!*p2) return p1_old;
p1 = p1_old + 1;
}
return NULL;
}
/////////////////////////////////////////


/*
* @brief 计算部分匹配表，即next 数组.
**
@param[in] pattern 模式串
* @param[out] next next 数组
* @return 无
*/
void compute_prefix(const char *pattern, int next[]) {
int i;
int j = -1;
const int m = strlen(pattern);
next[0] = j;
for (i = 1; i < m; i++) {
while (j > -1 && pattern[j + 1] != pattern[i]) j = next[j];
if (pattern[i] == pattern[j + 1]) j++;
next[i] = j;
}
}

/*
* @brief KMP 算法.
* @param[in] text 文本
* @param[in] pattern 模式串
* @return 成功则返回第一次匹配的位置，失败则返回-1
*/
int kmp(const char *text, const char *pattern) {
int i;
int j = -1;
const int n = strlen(text);
const int m = strlen(pattern);
if (n == 0 && m == 0) return 0; /* "","" */
if (m == 0) return 0; /* "a","" */
int *next = (int*)malloc(sizeof(int) * m);
compute_prefix(pattern, next);
for (i = 0; i < n; i++) {
while (j > -1 && pattern[j + 1] != text[i]) j = next[j];
if (text[i] == pattern[j + 1]) j++;
if (j == m - 1) {
free(next);
return i-j;
}
}
free(next);
return -1;
}

int main(int argc, char *argv[]) {
char text[] = "ABC ABCDAB ABCDABCDABDE";
char pattern[] = "ABCDABD";
char *ch = text;
int i = kmp(text, pattern);
if (i >= 0) printf("matched @: %s\n", ch + i);
return 0;
}

///////////////////////////////////////////////////
#define ASIZE 256 /* ASCII 字母的种类*/
/*
* @brief 预处理，计算每个字母最靠右的位置.
**
@param[in] pattern 模式串
* @param[out] right 每个字母最靠右的位置
* @return 无
*/
static void pre_right(const char *pattern, int right[]) {
int i;
const int m = strlen(pattern);
for (i = 0; i < ASIZE; ++i) right[i] = -1;
for (i = 0; i < m; ++i) right[(unsigned char)pattern[i]] = i;
}
static void suffixes(const char *pattern, int suff[]) {
int f, g, i;
const int m = strlen(pattern);
suff[m - 1] = m;
g = m - 1;
for (i = m - 2; i >= 0; --i) {
if (i > g && suff[i + m - 1 - f] < i - g)
suff[i] = suff[i + m - 1 - f];
else {
if (i < g)
g = i;
f = i;
while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
--g;
suff[i] = f - g;
}
}
}

/*
* @brief 预处理，计算好后缀的后移位置.
**
@param[in] pattern 模式串
* @param[out] gs 好后缀的后移位置
* @return 无
*/
static void pre_gs(const char pattern[], int gs[]) {
int i, j;
const int m = strlen(pattern);
int *suff = (int*)malloc(sizeof(int) * (m + 1));
suffixes(pattern, suff);
for (i = 0; i < m; ++i) gs[i] = m;
j = 0;
for (i = m - 1; i >= 0; --i) if (suff[i] == i + 1)
for (; j < m - 1 - i; ++j) if (gs[j] == m)
gs[j] = m - 1 - i;
for (i = 0; i <= m - 2; ++i)
gs[m - 1 - suff[i]] = m - 1 - i;
free(suff);
}
/**
* @brief Boyer-Moore 算法.
**
@param[in] text 文本
* @param[in] pattern 模式串
* @return 成功则返回第一次匹配的位置，失败则返回-1
*/
int boyer_moore(const char *text, const char *pattern) {
int i, j;
int right[ASIZE]; /* bad-character shift */
const int n = strlen(text);
const int m = strlen(pattern);
int *gs = (int*)malloc(sizeof(int) * (m + 1)); /* good-suffix shift */
/* Preprocessing */
pre_right(pattern, right);
pre_gs(pattern, gs);
/* Searching */
j = 0;
while (j <= n - m) {
for (i = m - 1; i >= 0 && pattern[i] == text[i + j]; --i);
if (i < 0) { /* 找到一个匹配*/
/* printf("%d ", j);
j += bmGs[0]; */
free(gs);
return j;
} else {
const int max = gs[i] > right[(unsigned char)text[i + j]] -
m + 1 + i ? gs[i] : i - right[(unsigned char)text[i + j]];
j += max;
}
}
free(gs);
return -1;
}
int main() {
const char *text="HERE IS A SIMPLE EXAMPLE";
const char *pattern = "EXAMPLE";
const int pos = boyer_moore(text, pattern);
printf("%d\n", pos); /* 17 */
return 0;
}
////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
const int R = 256; /** ASCII 字母表的大小，R 进制*/
/** 哈希表的大小，选用一个大素数，这里用16 位整数范围内最大的素数*/
const long Q = 0xfff1;
/*
* @brief 哈希函数.
**
@param[in] key 待计算的字符串
* @param[int] M 字符串的长度
* @return 长度为M 的子字符串的哈希值
*/
static long hash(const char key[], const int M) {
int j;
long h = 0;
for (j = 0; j < M; ++j) h = (h * R + key[j]) % Q;
return h;
}
/*
* @brief 计算新的hash.
* @param[in] first 长度为M 的子串的第一个字符
* @param[in] next 长度为M 的子串的下一个字符
* @param[int] RM R^(M-1) % Q
* @return 起始于位置i+1 的M 个字符的子字符串所对应的哈希值
*/
static long rehash(const long h, const char first, const char next,
const long RM) {
long newh = (h + Q - RM * first % Q) % Q;
newh = (newh * R + next) % Q;
return newh;
}
/*
* @brief 用蒙特卡洛算法，判断两个字符串是否相等.
**
@param[in] pattern 模式串
* @param[in] substring 原始文本长度为M 的子串
* @return 两个字符串相同，返回1，否则返回0
*/
static int check(const char *pattern, const char substring[]) {
return 1;
}
/**
* @brief Rabin-Karp 算法.
**
@param[in] text 文本
* @param[in] n 文本的长度
* @param[in] pattern 模式串
* @param[in] m 模式串的长度
* @return 成功则返回第一次匹配的位置，失败则返回-1
*/
int rabin_karp(const char *text, const char *pattern) {
int i;
const int n = strlen(text);
const int m = strlen(pattern);
const long pattern_hash = hash(pattern, m);
long text_hash = hash(text, m);
int RM = 1;
for (i = 0; i < m - 1; ++i) RM = (RM * R) % Q;
for (i = 0; i <= n - m; ++i) {
if (text_hash == pattern_hash) {
if (check(pattern, &text[i])) return i;
}
text_hash = rehash(text_hash, text[i], text[i + m], RM);
}
return -1;
}
int main() {
	const char *text = "HERE IS A SIMPLE EXAMPLE";
const char *pattern = "EXAMPLE";
const int pos = rabin_karp(text, pattern);
printf("%d\n", pos); /* 17 */
return 0;
}