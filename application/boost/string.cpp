#include <boost/format.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;


/*
利用boost中的format类去实现。如下：

cout << format( "%1% says \"%2%\" to %1%.\n" ) % "Yousen" % "Hello";
这句话将在标准输出上输出“Yousen says "Hello" to Yousen.”
接下来简单说明一下format的用法。在格式化字符串中，“%1%”
（不带引号，后称占位符）表示后面跟的第一个参数，“%2%”则 表示第二个
，以此类推——注意：占位符是从1开始计数。后面的“%”是
format类重载的操作符，用来跟占位符中的字符串。
刚才说了，format是个类，确切的说format是这样定义的：

typedef basic_format<char> format;
看清楚了哦，要想用unicode（宽字符）版的format，就用wformat。

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