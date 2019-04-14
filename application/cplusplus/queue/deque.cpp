//双向队列 deque
#include <deque>
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	deque<int> ideq(20); //Create a deque ideq with 20 elements of default value 0
	deque<int>::iterator pos;
	int i;

	//使用assign()赋值  assign在计算机中就是赋值的意思
	for (i = 0; i < 20; ++i)
		ideq[i] = i;

	//输出deque
	for (i = 0; i < 20; ++i)
		printf("%d ", ideq[i]);
	putchar('\n');

	ideq.push_back(100);
	ideq.push_front(i);

	//输出deque
	for (pos = ideq.begin(); pos != ideq.end(); pos++)
		printf("%d ", *pos);
	putchar('\n');

	//查找
	const int FINDNUMBER = 19;
	pos = find(ideq.begin(), ideq.end(), FINDNUMBER);
	if (pos != ideq.end())
		printf("find %d success\n", *pos);
	else
		printf("find failed\n");

	//在头尾删除数据
	ideq.pop_back();
	ideq.pop_front();

	//输出deque
	for (pos = ideq.begin(); pos != ideq.end(); pos++)
		printf("%d ", *pos);
	putchar('\n');
	return 0;
}