/*
Ħ��ͶƱ��
Ħ��ͶƱ����������һ����ʵ����һ�������ظ������������鳤�ȵ�һ�룬ÿ�ν���������ͬ����ɾ��������ʣ�µľ���Ҫ�ҵ�����
��ô�����O(n)��ʱ�临�Ӷȣ�ֻ����һ������ͰѲ�ͬ������ɾ���أ�Ħ��ͶƱ���Ĵ���ʵ���Ǿ��м����Եģ����������Ҫɾ�������������ֻ�ǰѱ������̵���һ��ɾ�����̡�
ʹ��һ�����������Ż�δ�Ͳ�ͬ����һ��ɾ���������������ֻ�������ɸ�ͬһ���֣������ܴ��ڲ�ͬ��������Ϊ������ڲ�ͬ�����ͻᱻɾȥ��������ŵ��������С�
�������������ǰԪ��ʱ������������Ϊ�գ��ͽ���ǰԪ�ؼӽ�ȥ������������ǿգ��ͱȽϵ�ǰԪ���Ƿ�����������е�Ԫ����ͬ�������ͬ��ɾȥ���������е�һ��Ԫ�أ�ͬʱ������ǰԪ��Ҳ��ɾ�������ű�����һԪ�أ��������൱��һ�Բ�ͬ�����ֱ�ɾ���������ͬ���Ͱѵ�ǰԪ�ؼӵ����������С����ձ��������飬���������е�Ԫ�ؾ���Ҫ�ҵ�Ԫ�ء�
��������������ֻ��������ɸ���ͬԪ�أ���ô���Խ�������������ʾ����������飬һ��������ֵ����һ��������Ÿ�����

*/

#include<stdio.h>
#define LEN 10
int main(){
    int a[] = {2,2,1,1,1,3,3,1,1,1};
    int x, cx = 0;//��ʾһ����������
    for(int i = 0; i < LEN; ++i){
        if(cx == 0) x = a[i], cx = 1;//��������Ϊ�գ����뵱ǰԪ��
        else if(x == a[i]) ++cx;//����ǿգ���ǰԪ������������Ԫ����ͬ�����뵱ǰԪ��
        else --cx;//����ǿգ���ǰԪ������������Ԫ�ز�ͬ��ɾ��һ�Բ���ͬ��Ԫ��
    }
    printf("����1/2�����ǣ�%d",x);
    return 0;
}