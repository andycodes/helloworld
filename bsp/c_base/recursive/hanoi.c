#include <stdio.h>
/*
* @brief ½«Ëş×ùx ÉÏ°´Ö±¾¶ÓĞĞ¡µ½´óÇÒ×ÔÉÏ¶øÏÂ±àºÅ
* Îª1 ÖÁn µÄn ¸öÔ²ÅÌ°´¹æÔò°áµ½Ëş×ùz ÉÏ£¬y ¿ÉÓÃ×ö¸¨ÖúËş×ù.
* @param[in] n Ô²ÅÌ¸öÊı
* @param[in] x Ô´Ëş×ù
* @param[in] y ¸¨ÖúËş×ù
* @param[in] z Ä¿±êËş×ù
* @return ÎŞ
*/
void hanoi(int n, char x, char y, char z) {
if(n == 1) {
/* å°†ç¼–å·ä¸ºn çš„åœ†ç›˜ä»x ç§»åˆ°z */
printf("%d from %c to %c\n", n, x, z);
return;
} else {
/* å°†x ä¸Šç¼–å·1 è‡³n-1 çš„åœ†ç›˜ç§»åˆ°yï¼Œz ä½œè¾…åŠ©å¡”*/
hanoi(n-1, x, z, y);
/* å°†ç¼–å·ä¸ºn çš„åœ†ç›˜ä»x ç§»åˆ°z */
printf("%d from %c to %c\n", n, x, z);
/* å°†y ä¸Šç¼–å·1 è‡³n-1 çš„åœ†ç›˜ç§»åˆ°zï¼Œx ä½œè¾…åŠ©å¡”*/
hanoi(n-1, y, x, z);
}
}
int main() {
int n;
scanf("%d", &n);
printf("%d\n", (1 << n) - 1); /* æ€»æ¬¡æ•°*/
hanoi(n, 'A', 'B', 'C');
return 0;
}