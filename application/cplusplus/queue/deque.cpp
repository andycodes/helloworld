//˫����� deque
#include <deque>
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	deque<int> ideq(20); //Create a deque ideq with 20 elements of default value 0
	deque<int>::iterator pos;
	int i;

	//ʹ��assign()��ֵ  assign�ڼ�����о��Ǹ�ֵ����˼
	for (i = 0; i < 20; ++i)
		ideq[i] = i;

	//���deque
	for (i = 0; i < 20; ++i)
		printf("%d ", ideq[i]);
	putchar('\n');

	ideq.push_back(100);
	ideq.push_front(i);

	//���deque
	for (pos = ideq.begin(); pos != ideq.end(); pos++)
		printf("%d ", *pos);
	putchar('\n');

	//����
	const int FINDNUMBER = 19;
	pos = find(ideq.begin(), ideq.end(), FINDNUMBER);
	if (pos != ideq.end())
		printf("find %d success\n", *pos);
	else
		printf("find failed\n");

	//��ͷβɾ������
	ideq.pop_back();
	ideq.pop_front();

	//���deque
	for (pos = ideq.begin(); pos != ideq.end(); pos++)
		printf("%d ", *pos);
	putchar('\n');
	return 0;
}