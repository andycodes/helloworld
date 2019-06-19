#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;

int main()
{
	string s = "sss/ddd,ggg";
	vector<string> vStr;
	boost::split(vStr, s, boost::is_any_of( ",/" ), boost::token_compress_on);
	for( vector<string>::iterator it = vStr.begin(); it != vStr.end(); ++ it )
		cout << *it << endl;
	return 0;
}