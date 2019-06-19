#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
����ԭ�ͣ�char * strtok (char *str, const char * delimiters);
������str�����ָ���ַ�����c-string����delimiters���ָ���ַ�����
�ú����������ַ����ָ��һ����Ƭ�Ρ�����strָ�����ָ���ַ�����
����delimiters��Ϊ�ָ��ַ����а����������ַ�����strtok()�ڲ���s��
�ַ����з��ֲ���delimiters�а����ķָ��ַ�ʱ��
��Ὣ���ַ���Ϊ\0 �ַ����ڵ�һ�ε���ʱ��
strtok()����������s�ַ���������ĵ����򽫲���s���ó�NULL��
ÿ�ε��óɹ��򷵻�ָ�򱻷ָ��Ƭ�ε�ָ�롣
��Ҫע����ǣ�ʹ�øú��������ַ����ָ�ʱ��
���ƻ����ֽ��ַ���������������ǰ�͵��ú��s�Ѿ���һ���ˡ�
��һ�ηָ�֮��ԭ�ַ���str�Ƿָ����֮��ĵ�һ���ַ�����
ʣ����ַ����洢��һ����̬�����У���˶��߳�ͬʱ���ʸþ�̬����ʱ��
�����ִ���

strtok_r������linux�·ָ��ַ����İ�ȫ�����������������£�
char *strtok_r(char *str, const char *delim, char **saveptr);
�ú���Ҳ���ƻ����ֽ��ַ����������ԣ�
�����佫ʣ����ַ���������saveptr�����У���֤�˰�ȫ�ԡ�
���ӣ�
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
