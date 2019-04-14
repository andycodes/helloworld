#include<iostream>
#include<stack>
using namespace std;
int main(void)
{
	stack<double>s;//定义一个栈
	for(int i=0;i<10;i++)
		s.push(i);
	while(!s.empty())
	{
		printf("%lf\n",s.top());
		s.pop();
	}
	cout<<"size:"<<s.size()<<endl;
	return 0;
}