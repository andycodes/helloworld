#include <boost/format.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;


/*
����boost�е�format��ȥʵ�֡����£�

cout << format( "%1% says \"%2%\" to %1%.\n" ) % "Yousen" % "Hello";
��仰���ڱ�׼����������Yousen says "Hello" to Yousen.��
��������˵��һ��format���÷����ڸ�ʽ���ַ����У���%1%��
���������ţ����ռλ������ʾ������ĵ�һ����������%2%���� ��ʾ�ڶ���
���Դ����ơ���ע�⣺ռλ���Ǵ�1��ʼ����������ġ�%����
format�����صĲ�������������ռλ���е��ַ�����
�ղ�˵�ˣ�format�Ǹ��࣬ȷ�е�˵format����������ģ�

typedef basic_format<char> format;
�������Ŷ��Ҫ����unicode�����ַ������format������wformat��

typedef basic_format<wchar_t> wformat;
*/

void testcase_format(void)
{
	 format fmt( "%2% says \"%1%\"." );
	 fmt % "Yousen";
	 fmt % "Hello";
	 string str = fmt.str();
	 cout << "string from fmt: " << str << endl;
	 cout << "fmt: " << fmt << endl;
}

int main()
{
	testcase_format();
}