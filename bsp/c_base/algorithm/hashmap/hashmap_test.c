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

    //创建映射需要指定两个函数，hashCode函数和equal函数。
    MyHashMap * map = createMyHashMap(myHashCodeString, myEqualString);

    //插入数据
    for (int i=0; i<S; i++)
    {
        myHashMapPutData(map, strs[i], &data[i]);
    }

    //输出大小
    printf("size=%d\n",myHashMapGetSize(map));

    //测试删除
    myHashMapRemoveDataByKey(map,"qq");
    myHashMapRemoveDataByKey(map,"ab");
    myHashMapRemoveDataByKey(map,"qwert");

    //输出大小
    printf("after remove size=%d\n",myHashMapGetSize(map));

    //遍历
    MyHashMapEntryIterator * it = createMyHashMapEntryIterator(map);
    while(myHashMapEntryIteratorHasNext(it))
    {
        Entry * pp= myHashMapEntryIteratorNext(it);
        char * key = pp-> key;
        int * value = pp->value;
        printf("%s(%d)\n", key, *value);
    }
    //释放遍历器
    freeMyHashMapEntryIterator(it);

    //释放映射
    freeMyHashMap(map);

    //释放数据
    free(data);
    return 0;
}

