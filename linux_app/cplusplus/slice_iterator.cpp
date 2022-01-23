#ifndef SLICE_ITERATOR_H
#define SLICE_ITERATOR_H
#include <stdlib.h>
#define MAX_COORD_NUM 10

typedef struct
{
	unsigned long start;//��ʼ�±�
	unsigned long end; //�����±�
}CoordSlice;

typedef struct
{
	int* first_element_of_orignal_array;//ԭʼ����ĵ�һ��Ԫ��ָ��
	unsigned long coord_num; //ά�ȸ��������ȡֵΪMAX_COORD_NUM��ֵΪ10
	//ԭʼ��������Ҹ�ά���±����Ա�ʾ����(��0��coord_num-1):
	unsigned long coord_spec[MAX_COORD_NUM];//ԭʼ����ÿ��ά���±�����ȡֵ
	CoordSlice coord_slice[MAX_COORD_NUM];//��Ƭ��ÿ��ά���ϵ���ֹ�±�
}SliceDesc;

typedef struct
{
	//�ṹ�����ɿ���������ƶ���
	int* first_element_of_orignal_array;//ԭʼ����ĵ�һ��Ԫ��ָ��
	unsigned long coord_num; //ά�ȸ��������ȡֵΪMAX_COORD_NUM��ֵΪ10
	//ԭʼ��������Ҹ�ά���±����Ա�ʾ����(��0��coord_num-1):
	CoordSlice coord_slice[MAX_COORD_NUM];//��Ƭ��ÿ��ά���ϵ���ֹ�±�
	unsigned long size[MAX_COORD_NUM];//ÿһά������������Ĵ�С��
	unsigned long curr[MAX_COORD_NUM];//ָ������Ӧ��ÿһά�ȵ��±�
}SliceIterator;

int SliceIteratorInit (const SliceDesc* slice_desc, SliceIterator* slice_iterator);
int* SliceIteratorGetCurr(const SliceIterator* slice_iterator);
void SliceIteratorNext(SliceIterator* slice_iterator);
int SliceIteratorEnd(const SliceIterator* slice_iterator);
int CopySlice (const SliceDesc* slice_desc,int** first_element_of_slice_array,unsigned long* slice_element_num);

#endif
#include "SliceIterator.h"

/******************************************************************************
���ܣ���ʼ��һ����Ƭ��������ʹ��ָ����Ƭ�ڵĵ�һ��Ԫ��
���룺
	  slice_desc    �� ��Ƭ������ָ�루�Ϸ����ɿ�����飩
	  slice_iterator�� ��Ƭ������ָ��
�����
	  slice_iterator�� ��ʼ�������Ƭ��������ָ��
���أ�
	  0���ɹ���-1��ʧ��

˵����
1��SliceIterator�ṹ��Ҫ�ɿ���������ƺͶ���
2���������ڴ��ɵ��������룬��С��Ϊsizeof(SliceIterator)�������ڲ����ö������붯̬�ڴ�
3��������֤�����ӿڵ����벻����δ��ʼ�����ĵ�����ָ��
******************************************************************************/
int SliceIteratorInit (const SliceDesc* slice_desc, SliceIterator* slice_iterator)

{
	/* ������ʵ�ֹ��� */
	//�����Ƭ����ָ���Ƿ���ȷ��
	if(slice_desc == 0)//��Ϊ��
		return -1;
	if(slice_desc->coord_num < 1 || slice_desc->coord_num > 10)//coord_num��1 - 10
		return -1;
	for(int i =0 ;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_spec[i] < 0 )//ά���±����ֵ����С��0
			return -1;
	for(int i =0;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_slice[i].start < 0 || slice_desc->coord_slice[i].end > slice_desc->coord_spec[i]|| slice_desc->coord_slice[i].start > slice_desc->coord_slice[i].end)//��⡣����
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
���ܣ���ȡ��ǰԪ��ָ��
���룺
	  slice_iterator��������ָ��
�������
���أ�ָ��ǰԪ�ص�ָ�롣������������Ӧ���ؿ�ָ�롣
******************************************************************************/
int* SliceIteratorGetCurr(const SliceIterator* slice_iterator)
{
	/* ������ʵ�ֹ��� */

	if(SliceIteratorEnd(slice_iterator))
		return 0;
	else{
		int i, t = 0;
		for(i = slice_iterator->coord_num-1; i > -1;i--)//unsigned���ǿӡ�������
			t += slice_iterator->size[i] * slice_iterator->curr[i];
		return &slice_iterator->first_element_of_orignal_array[t];
	}
	return 0;
}

/******************************************************************************
���ܣ��ƶ�����һ��Ԫ��
���룺
	  slice_iterator  ������ָ��
�����
	  slice_iterator  ���º�ĵ�����
���أ���
******************************************************************************/
void SliceIteratorNext(SliceIterator* slice_iterator)
{
	/* ������ʵ�ֹ��� */
	slice_iterator->curr[slice_iterator->coord_num-1] ++;
	for(int i = slice_iterator->coord_num-1; i > 0;i--)
		if(slice_iterator->curr[i] > slice_iterator->coord_slice[i].end){
			slice_iterator->curr[i-1] ++;
			slice_iterator->curr[i] = slice_iterator->coord_slice[i].start;
		}
	return;
}

/******************************************************************************
���ܣ������Ƿ����
���룺
	  slice_iterator:   ������ָ��
�������
���أ�1: �����ѽ���; 0:����δ����
******************************************************************************/
int SliceIteratorEnd(const SliceIterator* slice_iterator)
{
	/* ������ʵ�ֹ��� */
	if(slice_iterator->curr[0] > slice_iterator->coord_slice[0].end)
		return 1;
	else
		return 0;
}

/******************************************************************************
���ܣ�����һ��������Ƭ�Ŀ���
���룺slice_desc:  ��Ƭ������ָ�루�Ϸ����ɿ�����飩
�����
	  first_element_of_slice_array:�µ���Ƭ����ĵ�һ��Ԫ��ָ��
	  slice_element_num:�µ���Ƭ������Ԫ�ظ���
���أ�0���ɹ���-1:ʧ��

˵����first_element_of_slice_array�ڴ��ں��������룬�������ͷ�
******************************************************************************/
int CopySlice(const SliceDesc* slice_desc,int** first_element_of_slice_array, unsigned long* slice_element_num)
{
	/* ������ʵ�ֹ��� */
	//�����Ƭ����ָ���Ƿ���ȷ��
	if(slice_desc == 0)//��Ϊ��
		return -1;
	if(slice_desc->coord_num < 1 || slice_desc->coord_num > 10)//coord_num��1 - 10
		return -1;
	for(int i =0 ;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_spec[i] < 0 )//ά���±����ֵ����С��0
			return -1;
	for(int i =0;i < slice_desc->coord_num;i++)
		if(slice_desc->coord_slice[i].start < 0 || slice_desc->coord_slice[i].end > slice_desc->coord_spec[i]|| slice_desc->coord_slice[i].start > slice_desc->coord_slice[i].end)//��⡣����
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