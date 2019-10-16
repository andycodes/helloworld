/*规定：如果将二维数组作为参数传递给函数，
那么在函数的参数声明中必须指明数组的列数
void Func(int array[3][10]);

void Func(int array[ ][10]);

因为数组的行数无关紧要，所以还可以写成如下形式：

void Func(int (*array)[10]);  注意*array需要用括号括起来
*/
