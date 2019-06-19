#include <iostream>
#include <set>

using namespace std;
/*vector��װ���飬list��װ������
map��set��װ�˶�������

��set��ÿ��Ԫ�ص�ֵ��Ψһ��
����ϵͳ�ܸ���Ԫ�ص�ֵ�Զ���������*/
int main()
{
	set<int> s;
	int a[] = {5,6,4};
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(1);
	cout<<s.size()<<endl;
	cout<<s.max_size()<<endl;
	cout<<*s.begin()<<endl;
	cout<<*s.end()<<endl;
	/*Searches the container for elements equivalent to val and returns the number of matches.
	Because all elements in a set container are unique, the function can only return 1
	(if the element is found) or zero (otherwise).*/
	cout<<"Searches the container: "<<s.count(2)<<endl;

	s.insert(a,a+3);
	set<int>::const_iterator iter;
	for(iter = s.begin() ; iter != s.end() ; ++iter)
		cout<<*iter<<" ";

	cout<<endl;
	s.erase(s.begin());
	cout<<endl;
	for(iter = s.begin() ; iter != s.end() ; ++iter)
		cout<<*iter<<" ";

	cout<<endl;
	if((iter = s.find(2)) != s.end())
		cout<<*iter<<endl;

	s.clear();
	if(s.empty())
		cout<<"empty"<<endl;
	cout<<s.size()<<endl;
	cout<<s.max_size()<<endl;
	return 0;
}