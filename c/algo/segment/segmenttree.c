/*
307. 区域和检索 - 数组可修改
难度中等156
给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。
update(i, val) 函数可以通过将下标为 i 的数值更新为 val，从而对数列进行修改。
示例:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
说明:
1.	数组仅可以在 update 函数下进行修改。
2.	你可以假设 update 函数与 sumRange 函数的调用次数是均匀分布的。
通过次数13,

*/

/*
我们将使用一种非常有效的自下而上的方法来构建线段树。
从上面我们已经知道，如果某个节点 pp 包含范围 [i\ldots j][i…j] 的
和，那么其左、右子节点分别包含范围 [i \ldots \frac{i + j}{2}][i… 2i+j?	 ]
和 [\frac{i + j}{2} + 1, j][ 2i+j?	 +1,j] 上的和。因此，为了找到节点 pp 的和
，我们需要提前计算其左、右子节点的和。
我们从叶节点开始，用输入数组的元素 a[0,1,\ldots,n-1]a[0,1,…,n?1] 初
始化它们。然后我们逐步向上移动到更高一层来计算父节点
的和，直到最后到达线段树的根节点。
复杂度分析时间复杂度：O(n)O(n)。因为我们在 for 循环的每次迭
代中计算一个节点的和。而一个线段树中大约有 2n2n 个节点。
这可以通过以下方式证明：具有 nn 个元素的数组线段树有 nn
个叶节点（数组元素本身）。每一层中的节点数是下面一层
中节点数的一半。因此，如果我们按层对节点数求和，我们
将得到：n + n/2 + n/4 + n/8 + \ldots + 1 \approx 2nn+n/2+n/4+n/8+…+1≈2n空间
复杂度：O(n)O(n)，我们用了 2n2n 的额外空间来存储整个线段树。
更新线段树 :当我们更新数组中某个索引 ii 处的元素时，
我们需要重建线段树，因为一些树节点上的和值也会随之
产生变化。我们将再次使用自下而上的方法。首先更新存
储 a[i]a[i] 元素的叶节点。从那里我们将一路向上，直到根节
点，并用其子节点值的总和来更新每个父节点的值。
*/

typedef struct {
	int *nums;
	int numsSize;
	int *tree;
} NumArray;


void buildTree(NumArray* obj)
{
	//原始数据填充后半数组
	for (int i = obj->numsSize, j = 0; i < obj->numsSize * 2; i++, j++) {
		obj->tree[i] = obj->nums[j];
	}

	//生成前半数组数据
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
