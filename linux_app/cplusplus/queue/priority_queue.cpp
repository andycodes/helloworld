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
优先队列是队列的一种，
不过它可以按照自定义的一种方式（数据的优先级）
来对队列中的数据进行动态的排序
priority_queue<Type, Container, Functional>
其中Type 为数据类型，
Container 为保存数据的容器，
Functional 为元素比较方式。
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
/*标准库默认使用元素类型的<操作符来确定它们之
间的优先级关系。

通过<操作符可知在整数中元素大的优先级高。*/
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
