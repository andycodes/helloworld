#include <stdio.h>
/*
* @brief 将塔座x 上按直径有小到大且自上而下编号
* 为1 至n 的n 个圆盘按规则搬到塔座z 上，y 可用做辅助塔座.
* @param[in] n 圆盘个数
* @param[in] x 源塔座
* @param[in] y 辅助塔座
* @param[in] z 目标塔座
* @return 无
*/
void hanoi(int n, char x, char y, char z) {
if(n == 1) {
/* 灏嗙紪鍙蜂负n 鐨勫渾鐩樹粠x 绉诲埌z */
printf("%d from %c to %c\n", n, x, z);
return;
} else {
/* 灏唜 涓婄紪鍙�1 鑷硁-1 鐨勫渾鐩樼Щ鍒皔锛寊 浣滆緟鍔╁*/
hanoi(n-1, x, z, y);
/* 灏嗙紪鍙蜂负n 鐨勫渾鐩樹粠x 绉诲埌z */
printf("%d from %c to %c\n", n, x, z);
/* 灏唝 涓婄紪鍙�1 鑷硁-1 鐨勫渾鐩樼Щ鍒皕锛寈 浣滆緟鍔╁*/
hanoi(n-1, y, x, z);
}
}
int main() {
int n;
scanf("%d", &n);
printf("%d\n", (1 << n) - 1); /* 鎬绘鏁�*/
hanoi(n, 'A', 'B', 'C');
return 0;
}