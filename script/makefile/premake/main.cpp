#include <iostream>
using namespace std;

int main(void) {
  cout << "hello1" << endl;
}

/*
运行premake命令产生makefile
premake4 --file=config.lua --os=linux --platform=x64 gmake
premake4 --file=config.lua --os=linux --platform=x32 gmake

默认是Debug版本，现在运行命令，可以创建release版本。
make config=release all 

premake可以用来清理产生
premake4 --file=config.lua clean  

想要详细的看到编译的执行过程
make config=release verbose=1 all 

*/