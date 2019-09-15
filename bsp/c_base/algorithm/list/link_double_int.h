
#ifndef _DOUBLE_LINK_H
#define _DOUBLE_LINK_H

// �½���˫���������ɹ������ر�ͷ�����򣬷���NULL
extern int create_dlink();
// ������˫���������ɹ�������0�����򣬷���-1
extern int destroy_dlink();

// ��˫�������Ƿ�Ϊ�ա���Ϊ�յĻ�����1�����򣬷���0��
extern int dlink_is_empty();
// ���ء�˫������Ĵ�С��
extern int dlink_size();

// ��ȡ��˫�������е�indexλ�õ�Ԫ�ص�ֵ�����ɹ������ؽڵ�ֵ�����򣬷���-1��
extern int dlink_get(int index);
// ��ȡ��˫�������е�1��Ԫ�ص�ֵ�����ɹ������ؽڵ�ֵ�����򣬷���-1��
extern int dlink_get_first();
// ��ȡ��˫�����������1��Ԫ�ص�ֵ�����ɹ������ؽڵ�ֵ�����򣬷���-1��
extern int dlink_get_last();

// ����value�����뵽indexλ�á��ɹ�������0�����򣬷���-1��
extern int dlink_insert(int index, int value);
// ����value�����뵽��ͷλ�á��ɹ�������0�����򣬷���-1��
extern int dlink_insert_first(int value);
// ����value�����뵽ĩβλ�á��ɹ�������0�����򣬷���-1��
extern int dlink_append_last(int value);

// ɾ����˫��������indexλ�õĽڵ㡱���ɹ�������0�����򣬷���-1
extern int dlink_delete(int index);
// ɾ����һ���ڵ㡣�ɹ�������0�����򣬷���-1
extern int dlink_delete_first();
// ɾ�����һ���ڵ㡣�ɹ�������0�����򣬷���-1
extern int dlink_delete_last();

// ��ӡ��˫������
extern void print_dlink();

#endif 

