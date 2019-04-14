#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
函数原型：char * strtok (char *str, const char * delimiters);
参数：str，待分割的字符串（c-string）；delimiters，分割符字符串。
该函数用来将字符串分割成一个个片段。参数str指向欲分割的字符串，
参数delimiters则为分割字符串中包含的所有字符。当strtok()在参数s的
字符串中发现参数delimiters中包涵的分割字符时，
则会将该字符改为\0 字符。在第一次调用时，
strtok()必需给予参数s字符串，往后的调用则将参数s设置成NULL。
每次调用成功则返回指向被分割出片段的指针。
需要注意的是，使用该函数进行字符串分割时，
会破坏被分解字符串的完整，调用前和调用后的s已经不一样了。
第一次分割之后，原字符串str是分割完成之后的第一个字符串，
剩余的字符串存储在一个静态变量中，因此多线程同时访问该静态变量时，
则会出现错误

strtok_r函数是linux下分割字符串的安全函数，函数声明如下：
char *strtok_r(char *str, const char *delim, char **saveptr);
该函数也会破坏带分解字符串的完整性，
但是其将剩余的字符串保存在saveptr变量中，保证了安全性。
例子：
*/
int main()
{
    char str[]="ab,cd,ef";
    char *ptr;
    char *p;
    printf("before strtok:  str=%s\n",str);
    printf("begin:\n");
    ptr = strtok_r(str, ",", &p);
    while(ptr != NULL){
        printf("str=%s\n",str);
        printf("ptr=%s\n",ptr);
	printf("p=%s\n",p);
        ptr = strtok_r(NULL, ",", &p);
    }
    return 0;
}
