#include <iostream>
using namespace std;
int main()
{
	char str[8];
	int a,b;
	cin.getline(str, 5);
	cout<<str<<endl;
	cin.getline(str, 5);
	cout<<str<<endl;
	/*
	输入：2[回车]3[回车]
	输出：5
	注意:>> 是会过滤掉不可见字符（如 空格 回车，TAB 等）
	cin>>noskipws>>input[j];//不想略过空白字符，那就使用 noskipws 流控制*/
	cin>>a>>b;
	cout<<a<<endl;
	cout<<a+b<<endl;

	return 0;
}