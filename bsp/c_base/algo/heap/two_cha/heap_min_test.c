/*
编写一个程序，找出第 n 个丑数。

丑数就是只包含质因数 2, 3, 5 的正整数。

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:

1 是丑数。
n 不超过1690。

*/


/*
关键思路：找一下最小丑数

2、利用最小堆，先扔1进堆里。
然后每次拿堆顶最小的再乘一下2、3、5，
然后扔堆里。直到拿堆顶次数为n。
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

