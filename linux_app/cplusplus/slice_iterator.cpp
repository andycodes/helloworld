#ifndef SLICE_ITERATOR_H
#define SLICE_ITERATOR_H
#include <stdlib.h>
#define MAX_COORD_NUM 10

typedef struct
{
	unsigned long start;//起始下标
	unsigned long end; //结束下标
}CoordSlice;

typedef struct
{
	int* first_element_of_orignal_array;//原始数组的第一个元素指针
	unsigned long coord_num; //维度个数，最大取值为MAX_COORD_NUM，值为10
	//原始数组从左到右各维度下标属性表示如下(从0到coord_num-1):
	unsigned long coord_spec[MAX_COORD_NUM];//原始数组每个维度下标的最大取值
	CoordSlice coord_slice[MAX_COORD_NUM];//切片在每个维度上的起止下标
}SliceDesc;

typedef struct
{
	//结构内容由考生自行设计定义
	int* first_element_of_orignal_array;//原始数组的第一个元素指针
	unsigned long coord_num; //维度个数，最大取值为MAX_COORD_NUM，值为10
	//原始数组从左到右各维度下标属性表示如下(从0到coord_num-1):
	CoordSlice coord_slice[MAX_COORD_NUM];//切片在每个维度上的起止下标
	unsigned long size[MAX_COORD_NUM];//每一维度下面填满后的大小。
	unsigned long curr[MAX_COORD_NUM];//指针所对应的每一维度的下标
}SliceIterator;

int SliceIteratorInit (const SliceDesc* slice_desc, SliceIterator* slice_iterator);
int* SliceIteratorGetCurr(const SliceIterator* slice_iterator);
void SliceIteratorNext(SliceIterator* slice_iterator);
int SliceIteratorEnd(const SliceIterator* slice_iterator);
int CopySlice (const SliceDesc* slice_desc,int** first_element_of_slice_array,unsigned long* slice_element_num);

#endif
#include "SliceIterator.h"

/******************************************************************************
功能：初始化一个切片迭代器，使其指向切片内的第一个元素
输入：
	  slice_desc    ： 切片描述符指针（合法性由考生检查）
	  slice_iterator： 切片迭代器指针
输出：
	  slice_iterator： 初始化后的切片迭代器的指针
返回：
	  0：成功，-1：失败

说明：
1）SliceIterator结构需要由考生自行设计和定义
2）迭代器内存由调用者申请，大小仅为sizeof(SliceIterator)，函数内部不得额外申请动态内存
3）用例保证其他接口的输入不会是未初始化过的迭代器指针
******************************************************************************/
int SliceIteratorInit (const SliceDesc* slice_desc, SliceIterator* slice_iterator)

{
	/* 在这里实现功能 */
	//检测切片描述指针是否正确。
	if(slice_desc == 0)//不为空
		return -1;
	if(slice_desc->coord_num < 1 || slice_desc->coord_num > 10)//coord_num在1 - 10
		return -1;
	for(int i =0 ;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_spec[i] < 0 )//维度下标最大值不能小于0
			return -1;
	for(int i =0;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_slice[i].start < 0 || slice_desc->coord_slice[i].end > slice_desc->coord_spec[i]|| slice_desc->coord_slice[i].start > slice_desc->coord_slice[i].end)//检测。。。
			return -1;

	slice_iterator->first_element_of_orignal_array = slice_desc->first_element_of_orignal_array;
	slice_iterator->coord_num = slice_desc->coord_num;
	for(int i = 0;i < slice_desc->coord_num;i++){
		slice_iterator->coord_slice[i] = slice_desc->coord_slice[i];
		slice_iterator->curr[i] = slice_desc->coord_slice[i].start;
	}
	for(int i =0;i < slice_desc->coord_num;i++){
		slice_iterator->size[i] = 1;
		for(int j = i+1;j < slice_desc->coord_num;j++)
			slice_iterator->size[i] *= (slice_desc->coord_spec[j]+1) ;
	}

	return 0;
}

/******************************************************************************
功能：获取当前元素指针
输入：
	  slice_iterator：迭代器指针
输出：无
返回：指向当前元素的指针。若迭代结束，应返回空指针。
******************************************************************************/
int* SliceIteratorGetCurr(const SliceIterator* slice_iterator)
{
	/* 在这里实现功能 */

	if(SliceIteratorEnd(slice_iterator))
		return 0;
	else{
		int i, t = 0;
		for(i = slice_iterator->coord_num-1; i > -1;i--)//unsigned真是坑。。。。
			t += slice_iterator->size[i] * slice_iterator->curr[i];
		return &slice_iterator->first_element_of_orignal_array[t];
	}
	return 0;
}

/******************************************************************************
功能：移动到下一个元素
输入：
	  slice_iterator  迭代器指针
输出：
	  slice_iterator  更新后的迭代器
返回：无
******************************************************************************/
void SliceIteratorNext(SliceIterator* slice_iterator)
{
	/* 在这里实现功能 */
	slice_iterator->curr[slice_iterator->coord_num-1] ++;
	for(int i = slice_iterator->coord_num-1; i > 0;i--)
		if(slice_iterator->curr[i] > slice_iterator->coord_slice[i].end){
			slice_iterator->curr[i-1] ++;
			slice_iterator->curr[i] = slice_iterator->coord_slice[i].start;
		}
	return;
}

/******************************************************************************
功能：迭代是否结束
输入：
	  slice_iterator:   迭代器指针
输出：无
返回：1: 迭代已结束; 0:迭代未结束
******************************************************************************/
int SliceIteratorEnd(const SliceIterator* slice_iterator)
{
	/* 在这里实现功能 */
	if(slice_iterator->curr[0] > slice_iterator->coord_slice[0].end)
		return 1;
	else
		return 0;
}

/******************************************************************************
功能：创建一个数组切片的拷贝
输入：slice_desc:  切片描述符指针（合法性由考生检查）
输出：
	  first_element_of_slice_array:新的切片数组的第一个元素指针
	  slice_element_num:新的切片数组中元素个数
返回：0：成功，-1:失败

说明：first_element_of_slice_array内存在函数内申请，调用者释放
******************************************************************************/
int CopySlice(const SliceDesc* slice_desc,int** first_element_of_slice_array, unsigned long* slice_element_num)
{
	/* 在这里实现功能 */
	//检测切片描述指针是否正确。
	if(slice_desc == 0)//不为空
		return -1;
	if(slice_desc->coord_num < 1 || slice_desc->coord_num > 10)//coord_num在1 - 10
		return -1;
	for(int i =0 ;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_spec[i] < 0 )//维度下标最大值不能小于0
			return -1;
	for(int i =0;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_slice[i].start < 0 || slice_desc->coord_slice[i].end > slice_desc->coord_spec[i]|| slice_desc->coord_slice[i].start > slice_desc->coord_slice[i].end)//检测。。。
			return -1;

	SliceIterator si;
	SliceIteratorInit(slice_desc,&si);
	int i = 0;
	while(SliceIteratorEnd(&si) != 1){
		i++;
		SliceIteratorNext(&si);
	}
	*slice_element_num = i;
	*first_element_of_slice_array = (int*)malloc(sizeof(int)*i);
	int *q = *first_element_of_slice_array;
	for(i = 0;i < slice_desc->coord_num;i++){
		si.curr[i] = slice_desc->coord_slice[i].start;
	}
	while(	SliceIteratorEnd(&si) != 1){
		**first_element_of_slice_array= *SliceIteratorGetCurr(&si);
		(*first_element_of_slice_array)++;
		SliceIteratorNext(&si);
	}
	*first_element_of_slice_array = q;
	return 0;
}