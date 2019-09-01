#include <stack>
#include <cstdio>
/**
* @brief 进制转换，将一个10 进制整数转化为d 进制，d<=16.
* @param[in] n 整数n
* @param[in] d d 进制
* @return 无
*/
void convert_base(int n, const int d) {
	stack<int> s;
	int e;
	while(n != 0) {
	e = n % d;
	s.push(e);
	n /= d;
	}
	while(!s.empty()) {
	e = s.top();
	s.pop();
	printf("%X", e);
	}
	return;
}