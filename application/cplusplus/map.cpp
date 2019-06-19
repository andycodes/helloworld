/*
2��map�Ĺ���

�Զ�����Key �� value�Ķ�Ӧ��key �� value��������������Ҫ�����͡�
����keyֵ���ٲ��Ҽ�¼�����ҵĸ��ӶȻ�����Log(N)�������1000����¼��������10�Σ�1,000,000����¼��������20�Ρ�
���ٲ���Key - Value ��¼��
����ɾ����¼
����Key �޸�value��¼��
�������м�¼��
*/

#include<map>
#include<iterator>
#include<string>
#include<iostream>
#include <algorithm>
#include<cstring>
using   namespace   std;

struct   itemstruct{
            int a;
            char b[20];
            itemstruct(int t,char*str){
			a=t;
			strcpy(b,str);
		}
  };

void testcase1_erase_find(void)
{
	  map<string,itemstruct>mymap;
	  mymap.insert(make_pair("a",itemstruct(10,"hanzhou")));
	  mymap.insert(make_pair("ab",itemstruct(20,"fuzhou")));
	  mymap.insert(make_pair("abc",itemstruct(30,"zhengzhou")));
	  mymap.insert(make_pair("abcd",itemstruct(200,"wuhan")));
	  mymap.insert(make_pair("abcde",itemstruct(150,"kunming")));
	  mymap.insert(make_pair("abcdef",itemstruct(50,"xiamen")));

	  for(map<string,   itemstruct>::iterator   it   =   mymap.begin();   it   !=   mymap.end();)
	  {
	          if(it->second.a   >   100)
	                  it   =   mymap.erase(it);
	          else
	                  ++it;
	  }

	 map<string,itemstruct>::iterator   it=mymap.begin();
	  while(it!=mymap.end()) {
		  cout<<it->first<<"   "<<(it->second).a<<"   "<<(it->second).b<<endl;
		  it++;
	  }

	it=mymap.begin();
	it = mymap.find("abc");
	if (it!=mymap.end()) {
		cout<<"find,the value is "<<(it->second).a<<endl;
		(it->second).a += 10;
		cout<<"modify value is "<<(it->second).a<<endl;
	}else {
		cout<<"do not find"<<endl;
	}
}

class map_finder
{
private:
	string m_string;
public:
	map_finder( string cmp_string ) : m_string(cmp_string) {}
	bool operator () (const map<int,string>::value_type pair)
	{
		return pair.second == m_string;
	}
};

void testcase2_find_if(void)
{
	map<int ,string> my_map;
	my_map.insert( make_pair(10,"china"));
	my_map.insert( make_pair(20,"usa"));
	my_map.insert( make_pair(30,"english"));
	my_map.insert( make_pair(40,"hongkong"));

	map<int,string>::iterator it = find_if(my_map.begin(),my_map.end(),map_finder("english"));
	if( it == my_map.end() )
		cout<<"not found!"<<endl;
	else
		cout<<"found key:"<<(*it).first<<", value:"<<(*it).second<<endl;
}

template<class T>
struct DisableCompare:public std::binary_function<T,T,bool>
{
		bool operator()(T lhs,T rhs)  const
		{
				return true;
		} 
};

void testcase3_nosort(void)
{
	cout<<"testcase3_nosort:"<<endl;
	std::map<double,int,DisableCompare<double> > sMap;
	sMap.insert(make_pair(10.9 ,1));
	sMap.insert(make_pair(3.5, 2));
	sMap.insert(make_pair(30.0,3));
	sMap.insert(make_pair(2.4,4));
	 map<double,int,DisableCompare<double> >::iterator it=sMap.begin();
	  while(it!=sMap.end()) {
		  cout<<it->first<<" "<<endl;
		  it++;
	  }	
}

int   main()
{
	testcase1_erase_find();
	testcase2_find_if();
	testcase3_nosort();
	return   0;
}