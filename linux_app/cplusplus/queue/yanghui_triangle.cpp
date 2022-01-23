#include <queue>
/**
* @brief ��ӡ�������ϵ��.
**
���д�ӡ����ʽ(a+b)^n չ��ʽ��ϵ�����������һ��
* ϵ����ͬʱ��������һ�е�ϵ��Ԥ�ȼ���ã���������С�
* �ڸ���ϵ��֮�����һ��0��
**
@param[in] n (a+b)^n
* @return ��
*/
void yanghui_triangle(const int n) {
queue<int> q;
/* Ԥ�ȷ����һ�е�1 */
q.push(1);
for(int i = 0; i <= n; i++) { /* ���д���*/
int s = 0;
q.push(s); /* �ڸ��м����һ��0*/
/* �����i �е�i+2 ��ϵ��������һ��0��*/
for(int j = 0; j < i+2; j++) {
int t;
int tmp;
t = q.front(); /* ��ȡһ��ϵ��������t*/
q.pop();
tmp = s + t; /* ������һ��ϵ������������*/
q.push(tmp);
s = t; /* ��ӡһ��ϵ������i+2 ����0*/
if(j != i+1) {
printf("%d ",s);
}
}
printf("\n");
}
}