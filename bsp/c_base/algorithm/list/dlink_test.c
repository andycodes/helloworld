
#include <stdio.h>
#include "double_link.h"

/**
 * C ����ʵ�ֵ�˫������Ĳ��Գ���
 *
 * (01) int_test()
 *      ��ʾ��˫�����������int���ݡ���
 * (02) string_test()
 *      ��ʾ��˫������������ַ������ݡ���
 * (03) object_test()
 *      ��ʾ��˫��������������󡱡�
 *
 */

// ˫���������int����
void int_test()
{
	int iarr[4] = {10, 20, 30, 40};

	printf("\n----%s----\n", __func__);
	ListHead_t* plist_head = create_dlink();		// ����˫������

	dlink_insert(plist_head,0, &iarr[0]);	// ��˫������ı�ͷ��������
	dlink_insert(plist_head,0, &iarr[1]);	// ��˫������ı�ͷ��������
	dlink_insert(plist_head,0, &iarr[2]);	// ��˫������ı�ͷ��������

	printf("dlink_is_empty()=%d\n", dlink_is_empty(plist_head));	// ˫�������Ƿ�Ϊ��
	printf("dlink_size()=%d\n", dlink_size(plist_head));			// ˫������Ĵ�С

	// ��ӡ˫�������е�ȫ������
	int i;
	int *p;
	int sz = dlink_size(plist_head);
	for (i=0; i<sz; i++)
	{
		p = (int *)dlink_get(plist_head,i);
		printf("dlink_get(%d)=%d\n", i, *p);
	}

	destroy_dlink(plist_head);
}

void string_test()
{
	char* sarr[4] = {"ten", "twenty", "thirty", "forty"};

	printf("\n----%s----\n", __func__);
	ListHead_t* plist_head = create_dlink();	// ����˫������

	dlink_insert(plist_head,0, sarr[0]);	// ��˫������ı�ͷ��������
	dlink_insert(plist_head,0, sarr[1]);	// ��˫������ı�ͷ��������
	dlink_insert(plist_head,0, sarr[2]);	// ��˫������ı�ͷ��������

	printf("dlink_is_empty()=%d\n", dlink_is_empty(plist_head));	// ˫�������Ƿ�Ϊ��
	printf("dlink_size()=%d\n", dlink_size(plist_head));			// ˫������Ĵ�С

	// ��ӡ˫�������е�ȫ������
	int i;
	char *p;
	int sz = dlink_size(plist_head);
	for (i=0; i<sz; i++)
	{
		p = (char *)dlink_get(plist_head,i);
		printf("dlink_get(%d)=%s\n", i, p);
	}

	destroy_dlink(plist_head);
}

typedef struct tag_stu
{
	int id;
	char name[20];
}stu;

static stu arr_stu[] =
{
	{10, "sky"},
	{20, "jody"},
	{30, "vic"},
	{40, "dan"},
};
#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )

void object_test()
{
	printf("\n----%s----\n", __func__);
	ListHead_t* plist_head = create_dlink();	// ����˫������

	dlink_insert(plist_head, 0, &arr_stu[0]);	// ��˫������ı�ͷ��������
	dlink_insert(plist_head,0, &arr_stu[1]);	// ��˫������ı�ͷ��������
	dlink_insert(plist_head,0, &arr_stu[2]);	// ��˫������ı�ͷ��������

	printf("dlink_is_empty()=%d\n", dlink_is_empty(plist_head));	// ˫�������Ƿ�Ϊ��
	printf("dlink_size()=%d\n", dlink_size(plist_head));			// ˫������Ĵ�С

	// ��ӡ˫�������е�ȫ������
	int i;
	int sz = dlink_size(plist_head);
	stu *p;
	for (i=0; i<sz; i++)
	{
		p = (stu *)dlink_get(plist_head,i);
		printf("dlink_get(%d)=[%d, %s]\n", i, p->id, p->name);
	}

	destroy_dlink(plist_head);
}

int main()
{
	int_test();		// ��ʾ��˫�����������int���ݡ���
	string_test();	// ��ʾ��˫������������ַ������ݡ���
	object_test();	// ��ʾ��˫��������������󡱡�

	return 0;
}

