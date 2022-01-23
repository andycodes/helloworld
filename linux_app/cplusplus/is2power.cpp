#include <iostream>
using namespace std;

bool Is2Power(int nNum)
{
    return nNum > 0 ? ((nNum & (~nNum + 1)) == nNum ? true : false) : false;
}

int main()
{
		bool ret = Is2Power(32);
		cout<<ret<<endl;
		return 0;
}
