#include<iostream>
#include<sstream>
#include <vector>

using namespace std;


void testcase_ostringstream_number2string(void)
{
	ostringstream s1;
	int i = 22;
	float j = 3.4;
	s1 << "Hello " << i << j << endl;
	string s2 = s1.str();
	cout << s2 << endl;
	for (string::iterator it =s2.begin(); it != s2.end(); ++it) {
		if ( *it == 'l')
			s2.erase(it);
	}

	cout << s2 << endl;

	s2.push_back('L');
	s2.push_back('K');/*用来在字符串尾部添加一个字符*/
	cout << s2 << endl;
}

void testcase_compare(void)
{
	string a = "b";
	cout<<a.compare("a")<<" "<<a.compare("b")<<" "<<a.compare("c")<<endl;// 1 0 -1
}

//字符串分割函数
std::vector<std::string> split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

void testcase_split(void)
{
    std::string str;
    std::cout<<"Please input str:"<<std::endl;
    //std::cin>>str;
    getline(std::cin,str);
    std::string pattern;
    std::cout<<"Please input pattern:"<<std::endl;
    //std::cin>>pattern;
    getline(std::cin,pattern);//用于获取含空格的字符串
    std::vector<std::string> result=split(str,pattern);
    std::cout<<"The result:"<<std::endl;
    for(int i=0; i<result.size(); i++)
    {
        std::cout<<result[i]<<std::endl;
    }

    std::cin.get();
    std::cin.get();
}

string& trim(string& s) {
  if (s.empty()) {
    return s;
  }

  string::iterator c;
  // Erase whitespace before the string
  for (c = s.begin(); c != s.end() && iswspace(*c++););
    s.erase(s.begin(), --c);

  // Erase whitespace after the string
  for (c = s.end(); c != s.begin() && iswspace(*--c););
    s.erase(++c, s.end());

  return s;
}

void testcase_trim(void) {
  string s = "   Hello World!!   ";
  cout << s << " size:" << s.size() << endl;
  cout << trim(s) << " size:" << trim(s).size() << endl;
}


int main(void)
{
	testcase_ostringstream_number2string();
	testcase_compare();
	testcase_split();
	testcase_trim();
	return 0;
}