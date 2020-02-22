/*
void traverse(TreeNode root) {
    traverse(root.left)
    traverse(root.right)
}

*/

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
void hanoi(int n, char x, char y, char z)
{
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


int main()
{
	int n;
	scanf("%d", &n);
	printf("%d\n", (1 << n) - 1); /* �ܴ���*/
	hanoi(n, 'A', 'B', 'C');
	return 0;
}

/*
̩���������� Tn �������£�

T0 = 0, T1 = 1, T2 = 1, ���� n >= 0 �������� Tn+3 = Tn + Tn+1 + Tn+2

�������� n���뷵�ص� n ��̩�������� Tn ��ֵ��

*/

int tribonacci(int n){
	int ret;

	if (n == 0){
		ret = 0;
	}else if(n > 0 && n < 3){
		ret = 1;
	}else {
		ret = tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3);
	}

	return ret;
}


int mem[38];
int tribonacci(int n){
	int ret;
	mem[0] = 0;
	mem[1] = 1;
	mem[2] = 1;

	for(int i = 3; i <= n;i++){
		mem[i]= mem[i-1] + mem[i-2] +mem[i-3];
	}

	return mem[n];
}

int main()
{
	printf("%d\n",tribonacci(33));
	return 0;
}

