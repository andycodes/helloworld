
#include <ctype.h>


/*
isalpha

��������: isalpha

����ԭ��:

��������: ���ch�Ƿ�����ĸ.

��������: ����ĸ���ط�0(��vs2015��Ϊ2) ,���򷵻� 0.
*/
int isalpha(char ch);


/*

iscntrl

��������: iscntrl

����ԭ��: int iscntrl(int ch);

��������: ���ch�Ƿ�����ַ�(��ASCII����0��0x1F֮��,��ֵΪ 0-31).

��������: �Ƿ��ط�0,���򷵻� 0.

����˵��:

*/

/*
isdigit

��������: isdigit

����ԭ��: int isdigit(char ch);

��������: ���ch�Ƿ�������(0-9)

��������: �Ƿ��ط�0,���򷵻�0
*/
int isdigit(char ch);
/*

isgraph

��������: isgraph

����ԭ��: int isgraph(int ch);

��������: ���ch�Ƿ����ʾ�ַ�(��ASCII����0x21��0x7E֮��),�������ո�

��������: �Ƿ��ط�0,���򷵻�0


islower

��������: islower

����ԭ��: int islower(int ch);

��������: ���ch�Ƿ�Сд��ĸ(a-z)

��������: �Ƿ��ط�0,���򷵻�0

����˵��:

�����ļ�: <ctype.h>

isupper

��������: isupper

����ԭ��: int isupper(int ch);

��������: ���ch�Ƿ��Ǵ�д��ĸ(A-Z)

��������: �Ƿ��ط�0,���򷵻�0


tolower

��������: tolower

����ԭ��: int tolower(int ch);

��������: ��ch�ַ�ת��ΪСд��ĸ

��������: ����ch��������ַ���Сд��ĸ


toupper

��������: toupper

����ԭ��: int toupper(int ch);

��������: ��ch�ַ�ת���ɴ�д��ĸ

��������: ��ch��Ӧ�Ĵ�д��ĸ

isalnum

��������: isalnum

����ԭ��: int isalnum(int ch);

��������: ���ch�Ƿ�����ĸ������

��������: ����ĸ�����ַ��ط�0,���򷵻�0


isprint

��������: isprint

����ԭ��: int isprint(int ch);

��������: ���ch�Ƿ��ǿɴ�ӡ�ַ�(�����ո�),��ASCII����0x20��0x7E֮��

��������: �Ƿ��ط�0,���򷵻�0

*/


/*

��������: ispunct

����ԭ��: int ispunct(int ch);

��������: ���ch�Ƿ��Ǳ���ַ�(�������ո�),
������ĸ,���ֺͿո���������пɴ�ӡ�ַ�

��������: �Ƿ��ط�0,���򷵻�0
*/
int ispunct(int ch);


/*
isspace

��������: isspace

����ԭ��: int isspace(int ch);

��������: ���ch�Ƿ��ǿո���������(�����ַ�)���з�

��������: �Ƿ��ط�0,���򷵻�0

����˵��:

�����ļ�: <ctype.h>

isxdigit

��������: isxdigit

����ԭ��: int isxdigit(int ch);

��������: ���ch�Ƿ���һ��16������ѧ�ַ�(��0-9,��A-F,��a-f)

��������: �Ƿ��ط�0,���򷵻�0

����˵��:

�����ļ�: <ctype.h>

isascii

��������: isascii

����ԭ��: int isascii(int ch)

��������: ���Բ����Ƿ���ASCII��0-127

��������: �Ƿ��ط�0,���򷵻�0

����˵��: ch-�������

*/
