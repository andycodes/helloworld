#pragma warning(disable:4786)
#include <map>
#include <iostream>
using namespace std;

int main()
{
    multimap<int, char> mm;
    // 打印元素个数：0
    cout << mm.size() << endl;  
    mm.insert(pair<int, char>(3, 'a'));
    mm.insert(pair<int, char>(3, 'c'));
    mm.insert(pair<int, char>(4, 'd'));
    mm.insert(pair<int, char>(5, 'e'));
    // 打印键值为 3 的元素个数
    cout << mm.count(3) << endl;
    // 打印元素个数
    cout << mm.size() << endl;

    return 0;
}
