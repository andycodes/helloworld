#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*�����㷨�ĸ��Ӷ���O(m  n)*/
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
* @brief ���㲿��ƥ�����next ����.
**
@param[in] pattern ģʽ��
* @param[out] next next ����
* @return ��
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
* @brief KMP �㷨.
* @param[in] text �ı�
* @param[in] pattern ģʽ��
* @return �ɹ��򷵻ص�һ��ƥ���λ�ã�ʧ���򷵻�-1
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
