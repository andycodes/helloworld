#include <stack>
#include <cstdio>
/**
* @brief ����ת������һ��10 ��������ת��Ϊd ���ƣ�d<=16.
* @param[in] n ����n
* @param[in] d d ����
* @return ��
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