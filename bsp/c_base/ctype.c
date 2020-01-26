
#include <ctype.h>


/*
isalpha

函数名称: isalpha

函数原型:

函数功能: 检查ch是否是字母.

函数返回: 是字母返回非0(在vs2015中为2) ,否则返回 0.
*/
int isalpha(char ch);


/*

iscntrl

函数名称: iscntrl

函数原型: int iscntrl(int ch);

函数功能: 检查ch是否控制字符(其ASCII码在0和0x1F之间,数值为 0-31).

函数返回: 是返回非0,否则返回 0.

参数说明:

*/

/*
isdigit

函数名称: isdigit

函数原型: int isdigit(char ch);

函数功能: 检查ch是否是数字(0-9)

函数返回: 是返回非0,否则返回0
*/
int isdigit(char ch);
/*

isgraph

函数名称: isgraph

函数原型: int isgraph(int ch);

函数功能: 检查ch是否可显示字符(其ASCII码在0x21到0x7E之间),不包括空格

函数返回: 是返回非0,否则返回0


islower

函数名称: islower

函数原型: int islower(int ch);

函数功能: 检查ch是否小写字母(a-z)

函数返回: 是返回非0,否则返回0

参数说明:

所属文件: <ctype.h>

isupper

函数名称: isupper

函数原型: int isupper(int ch);

函数功能: 检查ch是否是大写字母(A-Z)

函数返回: 是返回非0,否则返回0


tolower

函数名称: tolower

函数原型: int tolower(int ch);

函数功能: 将ch字符转换为小写字母

函数返回: 返回ch所代表的字符的小写字母


toupper

函数名称: toupper

函数原型: int toupper(int ch);

函数功能: 将ch字符转换成大写字母

函数返回: 与ch相应的大写字母

isalnum

函数名称: isalnum

函数原型: int isalnum(int ch);

函数功能: 检查ch是否是字母或数字

函数返回: 是字母或数字返回非0,否则返回0


isprint

函数名称: isprint

函数原型: int isprint(int ch);

函数功能: 检查ch是否是可打印字符(包括空格),其ASCII码在0x20到0x7E之间

函数返回: 是返回非0,否则返回0

*/


/*

函数名称: ispunct

函数原型: int ispunct(int ch);

函数功能: 检查ch是否是标点字符(不包括空格),
即除字母,数字和空格以外的所有可打印字符

函数返回: 是返回非0,否则返回0
*/
int ispunct(int ch);


/*
isspace

函数名称: isspace

函数原型: int isspace(int ch);

函数功能: 检查ch是否是空格符和跳格符(控制字符)或换行符

函数返回: 是返回非0,否则返回0

参数说明:

所属文件: <ctype.h>

isxdigit

函数名称: isxdigit

函数原型: int isxdigit(int ch);

函数功能: 检查ch是否是一个16进制数学字符(即0-9,或A-F,或a-f)

函数返回: 是返回非0,否则返回0

参数说明:

所属文件: <ctype.h>

isascii

函数名称: isascii

函数原型: int isascii(int ch)

函数功能: 测试参数是否是ASCII码0-127

函数返回: 是返回非0,否则返回0

参数说明: ch-被测参数

*/
