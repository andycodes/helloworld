#include <iostream>

using std::cout;

using std::endl;

//����һ������ģ��,�����Ƚ������������ͬ�������͵Ĳ����Ĵ�С��classҲ���Ա�typename���棬

//T���Ա��κ���ĸ�������ִ��档

template <class T>

T min(T x,T y)

{ return(x<y)?x:y;}

int main( )
{

     int n1=2,n2=10;

     double d1=1.5,d2=5.6;

     cout<< "��С����:"<<min(n1,n2)<<endl;

     cout<< "��Сʵ��:"<<min(d1,d2)<<endl;

     system("PAUSE");
	return 0;
}