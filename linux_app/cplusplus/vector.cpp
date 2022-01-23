#include<stdio.h>
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;


void test_case0_iterator(void)
{
	vector<int> ivec;
	for(vector<int>::size_type ix=0; ix!=10;++ix){
		ivec.push_back(ix);
		cout<<ivec[ix]<<' ';
	}

	cout<<endl<<"After *2 the elements are:"<<endl;
	for(vector<int>::iterator iter=ivec.begin(); iter!=ivec.end();++iter) {
		*iter*=2;
		cout<<*iter<<' ';
	}
	cout<<endl;
}


typedef struct rect
{
	int id;
	int length;
	int width;

	//对于向量元素是结构体的，可在结构体内部定义比较函数，下面按照id,length,width升序排序。
	bool operator< (const rect &a)  const {
		if(id!= a.id)
			return id < a.id;
		else {
			if(length != a.length)
				return length < a.length;
			else
				return width < a.width;
		}
	}
}Rect;

void test_case1_operator(void)
{
	vector<Rect> vec;
	Rect rect;
	rect.id=1;
	rect.length=2;
	rect.width=3;
	vec.push_back(rect);
	vector<Rect>::iterator it=vec.begin();
	cout<<(*it).id<<' '<<(*it).length<<' '<<(*it).width<<endl;
}


/*
为什么会这样呢？比较时sort函数根据comp函数进行
判断输的大小，系统默认a<b时返回真，
于是从小到大排，而我的comp函数设定为a>b时返回为真，
那么最终得到的排序结果也相应的从小到大变成
从大到小。简单吧~~
*/
bool comp(const int &a,const int &b)
{
    return a>b;
}

struct ss
{
    int a,b;
};
bool comp_s(const ss &a,const ss &b)
{
    return a.a<b.a;
}

void test_case2_sort(void)
{
	vector<int> v;
	v.push_back(13);
	v.push_back(23);
	v.push_back(03);
	v.push_back(233);
	v.push_back(113);

	cout<<"sort org"<<endl;
	sort(v.begin(),v.end());
	for(int i=0;i<5;i++)
		cout<<v[i]<<' ';
	cout<<endl;

	cout<<"sort comp"<<endl;
	sort(v.begin(),v.end(),comp);
	for(int i=0;i<5;i++)
		cout<<v[i]<<' ';
	cout<<endl;


	vector<ss> v1;
	ss s1,s2,s3,s4,s5,s6;
	s1.a=4;s1.b=23;
	s2.a=1;s2.b=213;
	s3.a=2;s3.b=231;
	s4.a=5;s4.b=123;
	s5.a=3;s5.b=223;
	s6.a=3;s6.b=200;
	v1.push_back(s1);
	v1.push_back(s2);
	v1.push_back(s3);
	v1.push_back(s4);
	v1.push_back(s5);
	v1.push_back(s6);
	sort(v1.begin(),v1.end(),comp_s);
	for(int i=0;i<5;i++)
		cout<<v1[i].a<<" "<<v1[i].b<<endl;

}

void test_case3_find(void)
{
	vector<int> array(100);
	array[20]=50;
	vector<int>::iterator s=find(array.begin(),array.end(),50);
	if( s !=array.end())
		cout<<*s<<endl;
	else
		cout<<"not find!"<<endl;
}

struct value_t
{
	int a;
	int b;
};

class vector_finder
{
private:
	int m_v_a;
	int m_v_b;
public:
	vector_finder( const int a, const int b ) :m_v_a(a),m_v_b(b){}
	bool operator ()( vector<struct value_t>::value_type &value)
	{
		return (value.a==m_v_a)&&(value.b = m_v_b);
	}
};

void test_case4_find_if(void)
{
	vector<value_t> my_vector;
	value_t my_value;

	my_value.a = 11; my_value.b = 1001;
	my_vector.push_back(my_value);

	my_value.a = 12; my_value.b = 1002;
	my_vector.push_back(my_value);

	my_value.a = 13; my_value.b = 1003;
	my_vector.push_back(my_value);

	my_value.a = 14; my_value.b = 1004;
	my_vector.push_back(my_value);

	vector<value_t>::iterator it = find_if( my_vector.begin(), my_vector.end(), vector_finder(13,1003));
	if( it == my_vector.end() )
		cout<<"not found!"<<endl;
	else
		cout<<"found value a:"<<(*it).a <<", b:"<<(*it).b<<endl;
}

int main(void)
{
	test_case0_iterator();
	test_case1_operator();
	test_case2_sort();
	test_case3_find();
	test_case4_find_if();
	return 0;
}

