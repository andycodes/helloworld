__attribute__ ((visibility("default"))) int sub(int a, int b)
{
	return a - b;
}

/*

attribute ((visibility(“hidden”)))
该修饰用于修饰符号的可见性为默认对外不可见。意思是通过该符号修饰的函数不可以在 so 文件外访问到,只能在 so 文件内部访问到。
*/