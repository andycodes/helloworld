/*
��дһ�������ҳ��� n ��������

��������ֻ���������� 2, 3, 5 ����������

ʾ��:

����: n = 10
���: 12
����: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 ��ǰ 10 ��������
˵��:

1 �ǳ�����
n ������1690��

*/


/*
�ؼ�˼·����һ����С����

2��������С�ѣ�����1�����
Ȼ��ÿ���öѶ���С���ٳ�һ��2��3��5��
Ȼ���Ӷ��ֱ���öѶ�����Ϊn��
*/
int b[] = {2,3,5};
int nthUglyNumber(int n){

	minHeap *H = minheap_init(16900);
	minHeapPush(H,1);
	long int res = 0;

	for (long int i = 0; i < n;i++) {
		res = minHeapPop(H);
		for (long int j = 0;  j < sizeof(b)/sizeof(int); j++) {
			long int a = res * b[j];
			if (minHeapGetIndex(H, a) == -1)
				minHeapPush(H, a);
		}
	}

	return res;
}

