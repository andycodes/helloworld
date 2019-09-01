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
/* �����Ϊn ��Բ�̴�x �Ƶ�z */
printf("%d from %c to %c\n", n, x, z);
return;
} else {
/* ��x �ϱ��1 ��n-1 ��Բ���Ƶ�y��z ��������*/
hanoi(n-1, x, z, y);
/* �����Ϊn ��Բ�̴�x �Ƶ�z */
printf("%d from %c to %c\n", n, x, z);
/* ��y �ϱ��1 ��n-1 ��Բ���Ƶ�z��x ��������*/
hanoi(n-1, y, x, z);
}
}
int main() {
int n;
scanf("%d", &n);
printf("%d\n", (1 << n) - 1); /* �ܴ���*/
hanoi(n, 'A', 'B', 'C');
return 0;
}