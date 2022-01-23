#include <iostream>
#include <bitset>

using namespace std;

int main(){
    //bitset ʹ��������ʼ��bitset
    bitset<3> bs(7);
    //���bs����λ��ֵ
    cout<<"bs[0] is "<<bs[0]<<endl;
    cout<<"bs[1] is "<<bs[1]<<endl;
    cout<<"bs[2] is "<<bs[2]<<endl;
    //����������׳�outofindexexception
    //cout<<"bs[3] is "<<bs[3]<<endl;

    //ʹ���ַ�����ʼ��bitset
    //ע�⣺ʹ��string��ʼ��ʱ�������������³�ʼ���ĸ���λ��ֵ����110������011
    string strVal("011");
    bitset<3> bs1(strVal);
    //�����λ
    cout<<"bs1[0] is "<<bs1[0]<<endl;
    cout<<"bs1[1] is "<<bs1[1]<<endl;
    cout<<"bs1[2] is "<<bs1[2]<<endl;
    //cout���ʱҲ�Ǵ��ұ���������
    cout<<bs1<<endl;

    //bitset�ķ���
    //any()���������һλΪ1���򷵻�1
    cout<<"bs1.any() = "<<bs1.any()<<endl;

    //none()�����������һ��Ϊ1none�򷵻�0�����ȫΪ0�򷵻�1
    bitset<3> bsNone;
    cout<<"bsNone.none() = " <<bsNone.none()<<endl;

    //count()���ؼ���λΪ1
    cout<<"bs1.count() = "<<bs1.count()<<endl;

    //size()����λ��
    cout<<"bs1.size() = "<<bs1.size()<<endl;

    //test()����ĳһλ�Ƿ�Ϊ1
    //flip()��λȡ��
    bitset<3> bsFlip = bs1.flip();
    cout<<"bsFlip = "<<bsFlip<<endl;
    //flip(int)��ĳһλȡ��

    //reset()����������λ��ֵ������Ϊ0

	//to_ulong
	bitset<3> bs2(7);
	unsigned long val = bs2.to_ulong();
	cout<<"to_ulong = "<<val<<endl;

	string s_out = bs2.to_string();
	cout<<"to_string = "<<s_out<<endl;

	string s_src = "0000000111111";
/*bitset<n> b(s, pos, num);
b��s�д�λ��pos��ʼ��num��λ�ĸ���,���num<n,��ǰ��Ŀ�λ�Զ����0;*/
	bitset<16> bit_out(s_src, 7,12);
	cout<<"bit_out = "<<bit_out<<endl;
}