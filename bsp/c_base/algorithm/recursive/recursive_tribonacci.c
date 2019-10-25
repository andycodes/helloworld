#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

