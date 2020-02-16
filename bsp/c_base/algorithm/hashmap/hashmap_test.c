/*************************
*** File main.c
*** test for MyHashMap
**************************/
#include <stdio.h>
#include <stdlib.h>
#include "myEqual.h"
#include "myHashCode.h"
#include "myHashMap.h"

#define S 10

char* strs[S]=
{
    "abc",
    "qq",
    "hello",
    "abc",
    "lmy",
    "ab",
    "qq",
    "lqw",
    "sww",
    "lqw"
};


int main()
{

    int*  data = malloc(sizeof(int)* S);
    for (int i=0; i<S; i++)
    {
        data[i]=i;
    }

    //����ӳ����Ҫָ������������hashCode������equal������
    MyHashMap * map = createMyHashMap(myHashCodeString, myEqualString);

    //��������
    for (int i=0; i<S; i++)
    {
        myHashMapPutData(map, strs[i], &data[i]);
    }

    //�����С
    printf("size=%d\n",myHashMapGetSize(map));

    //����ɾ��
    myHashMapRemoveDataByKey(map,"qq");
    myHashMapRemoveDataByKey(map,"ab");
    myHashMapRemoveDataByKey(map,"qwert");

    //�����С
    printf("after remove size=%d\n",myHashMapGetSize(map));

    //����
    MyHashMapEntryIterator * it = createMyHashMapEntryIterator(map);
    while(myHashMapEntryIteratorHasNext(it))
    {
        Entry * pp= myHashMapEntryIteratorNext(it);
        char * key = pp-> key;
        int * value = pp->value;
        printf("%s(%d)\n", key, *value);
    }
    //�ͷű�����
    freeMyHashMapEntryIterator(it);

    //�ͷ�ӳ��
    freeMyHashMap(map);

    //�ͷ�����
    free(data);
    return 0;
}

