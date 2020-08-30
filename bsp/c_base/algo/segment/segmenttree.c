/*
307. ����ͼ��� - ������޸�
�Ѷ��е�156
����һ����������  nums�������������� i �� j  (i �� j) ��Χ��Ԫ�ص��ܺͣ����� i,  j ���㡣
update(i, val) ��������ͨ�����±�Ϊ i ����ֵ����Ϊ val���Ӷ������н����޸ġ�
ʾ��:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
˵��:
1.	����������� update �����½����޸ġ�
2.	����Լ��� update ������ sumRange �����ĵ��ô����Ǿ��ȷֲ��ġ�
ͨ������13,

*/

/*
���ǽ�ʹ��һ�ַǳ���Ч�����¶��ϵķ����������߶�����
�����������Ѿ�֪�������ĳ���ڵ� pp ������Χ [i\ldots j][i��j] ��
�ͣ���ô�������ӽڵ�ֱ������Χ [i \ldots \frac{i + j}{2}][i�� 2i+j?	 ]
�� [\frac{i + j}{2} + 1, j][ 2i+j?	 +1,j] �ϵĺ͡���ˣ�Ϊ���ҵ��ڵ� pp �ĺ�
��������Ҫ��ǰ�����������ӽڵ�ĺ͡�
���Ǵ�Ҷ�ڵ㿪ʼ�������������Ԫ�� a[0,1,\ldots,n-1]a[0,1,��,n?1] ��
ʼ�����ǡ�Ȼ�������������ƶ�������һ�������㸸�ڵ�
�ĺͣ�ֱ����󵽴��߶����ĸ��ڵ㡣
���Ӷȷ���ʱ�临�Ӷȣ�O(n)O(n)����Ϊ������ for ѭ����ÿ�ε�
���м���һ���ڵ�ĺ͡���һ���߶����д�Լ�� 2n2n ���ڵ㡣
�����ͨ�����·�ʽ֤�������� nn ��Ԫ�ص������߶����� nn
��Ҷ�ڵ㣨����Ԫ�ر�����ÿһ���еĽڵ���������һ��
�нڵ�����һ�롣��ˣ�������ǰ���Խڵ�����ͣ�����
���õ���n + n/2 + n/4 + n/8 + \ldots + 1 \approx 2nn+n/2+n/4+n/8+��+1��2n�ռ�
���Ӷȣ�O(n)O(n)���������� 2n2n �Ķ���ռ����洢�����߶�����
�����߶��� :�����Ǹ���������ĳ������ ii ����Ԫ��ʱ��
������Ҫ�ؽ��߶�������ΪһЩ���ڵ��ϵĺ�ֵҲ����֮
�����仯�����ǽ��ٴ�ʹ�����¶��ϵķ��������ȸ��´�
�� a[i]a[i] Ԫ�ص�Ҷ�ڵ㡣���������ǽ�һ·���ϣ�ֱ������
�㣬�������ӽڵ�ֵ���ܺ�������ÿ�����ڵ��ֵ��
*/

typedef struct {
	int *nums;
	int numsSize;
	int *tree;
} NumArray;


void buildTree(NumArray* obj)
{
	//ԭʼ�������������
	for (int i = obj->numsSize, j = 0; i < obj->numsSize * 2; i++, j++) {
		obj->tree[i] = obj->nums[j];
	}

	//����ǰ����������
	for (int i = obj->numsSize - 1; i >= 0; i--) {
		obj->tree[i] = obj->tree[i * 2] + obj->tree[i * 2 + 1];
	}
}

NumArray* numArrayCreate(int* nums, int numsSize)
{
	NumArray* obj = (NumArray*)calloc(1, sizeof(NumArray));
	obj->nums = nums;
	obj->numsSize = numsSize;
	obj->tree = (int *)calloc(numsSize * 2, sizeof(int));
	buildTree(obj);
	return obj;
}

void numArrayUpdate(NumArray* obj, int i, int val)
{
        int pos = obj->numsSize+ i;
        obj->tree[pos] = val;

        while(pos > 0) {
		int left = pos % 2 == 0 ? pos : pos-1;
		int right = pos % 2 == 0 ?  pos + 1 : pos;
		obj->tree[pos / 2] = obj->tree[left] + obj->tree[right];
		pos /= 2;
        }
}

int numArraySumRange(NumArray* obj, int i, int j)
{
        int sum = 0;
        int l = obj->numsSize + i;
        int r = obj->numsSize + j;

        while(l <= r){
            if(l % 2 == 1){
                sum += obj->tree[l];
                l++;
            }

            if(r % 2 == 0){
                sum += obj->tree[r];
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
}

void numArrayFree(NumArray* obj) {

}
