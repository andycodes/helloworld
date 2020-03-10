/********************************************
                                sscanf
从一个字符串中读进与指定格式相符的数据

函数原型:

Int  sscanf( string str, string fmt, mixed var1, mixed var2 ... );

int  scanf( const char *format [,argument]... );


说明：

sscanf与scanf类似，都是用于输入的，
只是后者以屏幕(stdin)为输入源，
前者以固定字符串为输入源。
其中的format可以是一个或多个
{%[*] [width] [{h | l | I64 | L}]type | ‘ ‘ | ‘\t‘ | ‘\n‘ | 非%符号}


********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[512] = {0};
int a,b,c;

int sscanf_test(void)
{
        sscanf("123456","%s",buf);
        printf("%s\n",buf);

/*取指定长度的字符串。
如在下例中，取最大长度为
4字节的字符串。*/
        sscanf("123456 ", "%4s", buf);
        printf("%s\n",buf);

/* 取到指定字符为止的
字符串。如在下例中，
取遇到空格为止字符串。*/
        sscanf("123456 abcdedf", "%[^ ]", buf);
        printf("%s\n",buf);

/* 取仅包含指定字符集的
字符串。如在下例中，
取仅包含1到9和小写字母的字符串。*/
        sscanf("123456bcTedfBCDEF", "%[1-9a-z]", buf);
        printf("%s\n",buf);//123456bc

/*给定一个字符串iios/12DDWDFF@122，
获取 / 和 @ 之间的字符串，
先将 "iios/"过滤掉，
再将非'@'的一串内容送到buf中*/
        sscanf("iios/12DDWDFF@122", "%*[^/]/%[^@]", buf);
        printf("%s\n",buf);

/*给定一个字符串"hello, world"，
仅保留world。
（注意："，"之后有一空格，
%s遇空格停止，加*则是忽略第一
个读到的字符串）*/

/*%*s表示第一个匹配到的%s被过滤
掉，即hello被过滤了*/

/*如果没有空格则结果为NULL。*/
        sscanf("hello, world", "%*s%s", buf);
        printf("%s\n",buf);

        sscanf("2006:03:18", "%d:%d:%d", &a, &b, &c);
        printf("a %d b %d c %d\n",a,b,c);

/*取到指定字符为止的字符串。
如在下例中，取遇到空格为止字符串*/
        sscanf("123456 abcdedf", "%[^ ]", buf);
        printf("%s\n", buf);

/*取到指定字符集为止的字符串。
如在下例中，取遇到大写字母为止的字符串*/
        sscanf("123456abcdedfBCDEF", "%[^A-Z]", buf);
        printf("%s\n", buf);


}



int main()
{
    int a,b;
    while( scanf( "%d%d" , &a , &b ) != EOF )   //输入直到文件结尾
    {
        printf( "%d\n" , a+b );   //一行一个结果
    }

    return 0;
}

