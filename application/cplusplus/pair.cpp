#include<iostream>
#include<string>
#include<vector>
#include<utility>
using namespace std;

int main()
{
pair<int, double> p1;  //使用默认构造函数
pair<int, double> p2(1, 2.4);  //用给定值初始化
pair<int, double> p3(p2);  //拷贝构造函数


p1.first = 1;
p1.second = 2.5;
cout << p1.first << ' ' << p1.second << endl;
p1 = make_pair(1, 1.2);
cout << p1.first << ' ' << p1.second << endl;
}
