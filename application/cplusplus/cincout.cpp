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
	���룺2[�س�]3[�س�]
	�����5
	ע��:>> �ǻ���˵����ɼ��ַ����� �ո� �س���TAB �ȣ�
	cin>>noskipws>>input[j];//�����Թ��հ��ַ����Ǿ�ʹ�� noskipws ������*/
	cin>>a>>b;
	cout<<a<<endl;
	cout<<a+b<<endl;

	return 0;
}