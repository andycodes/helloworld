#include<iostream>

using namespace std;

/**
	 * fibonacciÊıÁĞ
	 * @param n
	 * @return
	 */
static long fibonacci(int n) {
	if((0 == n) || (1 == n)) {
		return n;
	}else {
		return fibonacci(n-1) + fibonacci(n-2);
	}
}

int main(void)
{
	cout<<fibonacci(3)<<endl;
	return 0;
}
