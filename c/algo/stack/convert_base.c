const int MAXN = 64; // ջ����󳤶�
int stack[MAXN];
int top = -1;

/**
* @brief ����ת������һ��10 ��������ת��Ϊd ���ƣ�
d<=16�����Ż��İ汾.
�������Ԥ��ջ�����ռ䣬����������ģ��ջ��
��ʱ���õ�һ�����ɡ�
* ���ջ����󳤶��Ƕ��٣�����CPU ��64 λ��
������������2^64������������СΪ2��
����������£�����λ�����
�����ջ����󳤶ȣ��Ϊ64��
@param[in] n ����n
* @param[in] d d ����
* @return ��
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
* @brief ����ת������һ��d ��������ת��Ϊ10 ���ƣ�d<=16.
* @param[in] s d ��������
* @param[in] d d ����
* @return 10 ��������
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

