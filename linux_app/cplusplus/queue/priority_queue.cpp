#include <iostream>
#include <queue>

using namespace std;


struct node{
	int idx;
	int key;
	node(int a=0, int b=0):idx(a), key(b){}
};

struct cmp{
	bool operator()(node a, node b){
		return a.key > b.key;
	}
};

void priority_queue_test0(void)
{
/*
���ȶ����Ƕ��е�һ�֣�
���������԰����Զ����һ�ַ�ʽ�����ݵ����ȼ���
���Զ����е����ݽ��ж�̬������
priority_queue<Type, Container, Functional>
����Type Ϊ�������ͣ�
Container Ϊ�������ݵ�������
Functional ΪԪ�رȽϷ�ʽ��
*/
	priority_queue<node, vector<node>, cmp> q;
	q.push(node(0, 0));
	q.push(node(1, 5));
	q.push(node(2, 3));
	q.push(node(3, 4));
	q.push(node(4, 2));

	while(!q.empty()){
		cout<<q.top().key<<endl;
		q.pop();
	}
	cout<<"priority_queue_test0 FIN"<<endl;
}

void priority_queue_test1()
{
/*��׼��Ĭ��ʹ��Ԫ�����͵�<��������ȷ������֮
������ȼ���ϵ��

ͨ��<��������֪��������Ԫ�ش�����ȼ��ߡ�*/
	priority_queue<int> pq;
	pq.push(5);
	pq.push(3);
	pq.push(2);
	pq.push(4);
	pq.push(6);
	while(!pq.empty()){
		cout<<pq.top()<<endl;
		pq.pop();
	}
	cout<<"priority_queue_test1 FIN"<<endl;
}

int main()
{
	priority_queue_test0();
	priority_queue_test1();
	return 0;
}
