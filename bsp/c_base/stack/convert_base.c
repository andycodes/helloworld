const int MAXN = 64; // 栈的最大长度
int stack[MAXN];
int top = -1;

/**
* @brief 进制转换，将一个10 进制整数转化为d 进制，
d<=16，更优化的版本.
如果可以预估栈的最大空间，则用数组来模拟栈，
这时常用的一个技巧。
* 这里，栈的最大长度是多少？假设CPU 是64 位，
最大的整数则是2^64，由于数制最小为2，
在这个进制下，数的位数最长，
这就是栈的最大长度，最长为64。
@param[in] n 整数n
* @param[in] d d 进制
* @return 无
*/
void convert_base2(int n, const int d) {
	int e;
	while(n != 0) {
		e = n % d;
		stack[++top] = e; // push
		n /= d;
	}
	while(top >= 0) {
		e = stack[top--]; // pop
		printf("%X", e);
	}
	return;
}


/**
* @brief 进制转换，将一个d 进制整数转化为10 进制，d<=16.
* @param[in] s d 进制整数
* @param[in] d d 进制
* @return 10 进制整数
*/
int restore(const char s[MAXN], const int d) {
	int result = 0;
	int one;
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] >= '0' && s[i] <= '9') one = s[i] - '0';
		else if (s[i] >= 'A' && s[i] <= 'F') one = s[i] - 'A' + 10;
		else one = s[i] - 'a' + 10; /* (s[i] >= 'a' && s[i] <= 'f') */
		result = result * d + one;
	}
	return result;
}

