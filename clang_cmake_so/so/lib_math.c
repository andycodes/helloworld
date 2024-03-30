__attribute__ ((visibility("default"))) int sub(int a, int b)
{
	return a - b;
}

__attribute__ ((visibility("“hidden”"))) int add(int a, int b)
{
	return a + b;
}

/*
限制符号可见性的原因：从动态库中尽可能少地输出符号是一个好的实践经验。输出一个受限制的符号会提高程序的模块性，并隐藏实现的细节。
动态库装载和识别的符号越少，程序启动和运行的速度就越快。导出所有符号会减慢程序速度，并耗用大量内存。
“default”：用它定义的符号将被导出，动态库中的函数默认是可见的。”hidden”：用它定义的符号将不被导出，并且不能从其它对象进行使用，
动态库中的函数是被隐藏的。default意味着该方法对其它模块是可见的。而hidden表示该方法符号不会被放到动态符号表里，
所以其它模块(可执行文件或者动态库)不可以通过符号表访问该方法。

attribute ((visibility(“hidden”)))
该修饰用于修饰符号的可见性为默认对外不可见。意思是通过该符号修饰的函数不可以在 so 文件外访问到,只能在 so 文件内部访问到。

    20: 0000000000000000    32 FUNC    GLOBAL DEFAULT     2 sub
    21: 0000000000000020    32 FUNC    GLOBAL HIDDEN      2 add
*/