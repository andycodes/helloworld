/*
void traverse(TreeNode root) {
    traverse(root.left)
    traverse(root.right)
}

*/

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
void hanoi(int n, char x, char y, char z)
{
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


int main()
{
	int n;
	scanf("%d", &n);
	printf("%d\n", (1 << n) - 1); /* 总次数*/
	hanoi(n, 'A', 'B', 'C');
	return 0;
}

/*
泰波那契序列 Tn 定义如下：

T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2

给你整数 n，请返回第 n 个泰波那契数 Tn 的值。

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

