#include <stdio.h>
/*
* @brief ������x �ϰ�ֱ����С���������϶��±��
* Ϊ1 ��n ��n ��Բ�̰�����ᵽ����z �ϣ�y ��������������.
* @param[in] n Բ�̸���
* @param[in] x Դ����
* @param[in] y ��������
* @param[in] z Ŀ������
* @return ��
*/
void hanoi(int n, char x, char y, char z) {
if(n == 1) {
/* 将编号为n 的圆盘从x 移到z */
printf("%d from %c to %c\n", n, x, z);
return;
} else {
/* 将x 上编号1 至n-1 的圆盘移到y，z 作辅助塔*/
hanoi(n-1, x, z, y);
/* 将编号为n 的圆盘从x 移到z */
printf("%d from %c to %c\n", n, x, z);
/* 将y 上编号1 至n-1 的圆盘移到z，x 作辅助塔*/
hanoi(n-1, y, x, z);
}
}
int main() {
int n;
scanf("%d", &n);
printf("%d\n", (1 << n) - 1); /* 总次数*/
hanoi(n, 'A', 'B', 'C');
return 0;
}