#include<iostream>
#include<stack>
using namespace std;
int main(void)
{
	stack<double>s;//����һ��ջ
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