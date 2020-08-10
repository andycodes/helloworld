/*

while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (Check mid) { // ����nums[mid]���ж�������벿�ֻ����Ұ벿��
        lb = mid;
    } else {
        ub = mid;
    }
}
// �������������lb����ub����ʱub == lb + 1
return nums[lb] >= target ? lb : ub;

��ά

int lb = 0; ub = row * col;

while (ub - lb > 1) {
	int mid = (lb + ub) / 2;
	int i = mid / width;
	int j = mid % width;
	if (matrix[i][j] <= target) {
		lb = mid;
	} else {
		ub = mid;
	}
}

return matrix[lb / width][lb % width] == target;
*/
int binary_find_recur(int a[],int key,int start,int end)
{
	int middle=(start+end)/2;
	if(a[middle]==key)
		return middle;
	if(start==middle)
		return -1;
        if(key<a[middle])
		binary_find_recur(a,key,start,middle);
	else
		binary_find_recur(a,key,middle,end);
}

/*bseach�÷�:
void *bsearch(const void *key, const void *base, size_t nelem, size_t width,
int(*fcmp)(const void *, const *));
������
keyָ����Ҫ���ҵ�Ԫ��.
��һ���ҵĹؼ��֡�
�ڶ�����Ҫ���ҵ����顣
��������ָ��������Ԫ�ص���Ŀ��
���ĸ���ÿ��Ԫ�صĳ��ȣ����ַ�Ϊ��λ����
�������ָ��ȽϺ�����ָ��.
*/

/*
1011. �� D �����ʹ����������
�Ѷ��е�75
���ʹ��ϵİ��������� D ���ڴ�һ���ۿ����͵���һ���ۿڡ�
���ʹ��ϵĵ� i ������������Ϊ weights[i]��ÿһ�죬���Ƕ��ᰴ����������˳�������ʹ���װ�ذ���������װ�ص��������ᳬ�������������������
�������� D ���ڽ����ʹ��ϵ����а����ʹ�Ĵ����������������

ʾ�� 1��
���룺weights = [1,2,3,4,5,6,7,8,9,10], D = 5
�����15
���ͣ�
����������� 15 ���ܹ��� 5 �����ʹ����а�����������ʾ��
�� 1 �죺1, 2, 3, 4, 5
�� 2 �죺6, 7
�� 3 �죺8
�� 4 �죺9
�� 5 �죺10

��ע�⣬������밴�ո�����˳��װ�ˣ����ʹ����������Ϊ 14 �Ĵ���������װ�ֳ� (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) �ǲ�����ġ�

*/
/*
 //1.�������������Ȼ���ڵ��������е����ֵ���������[max(weights), sum(weights)]        //2.Ҫע������D�조�ڡ���ɣ�������������Ҫ����С��ֻҪ����D��֮�ھͿ������ߣ�luke-9r���ӣ�https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/solution/c-er-fen-cha-zhao-jian-dan-shi-xian-dai-ma-by-luke/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
����һ�ҳ�����ΪK����˵�����Ǳ�Ȼ���ڲ��������������ǰ����̰�ĵ�����װ�ػ����������ʹ�����Ͱ��������ѵ�ʱ����̡�
������ڳ�����ΪK�������¿��������D�����ʹ������������ô�κγ���������K����������ȻҲ���������
���ǿ��������������K��max(weights)max(weights)��ʼ�������а�������������������������������������ǲ�����������񣩣������������K��ֱ��K������������D�����ʹ��������ʱK��Ϊ������Ҫ�����ͳ�������
�����������K�ķ���Ч�ʹ��ͣ��������ö��ֲ��ҵķ������Ż�����
*/
bool canShip(int* weights, int weightsSize, int D, int shipCapacity)
{
	int cur = shipCapacity ;
	for(int i = 0; i < weightsSize; i++) {
		if (weights[i] > shipCapacity )
			return false;
		if (cur < weights[i]) {
			cur = shipCapacity ;
			D--;
		}
		cur -= weights[i];
	}
	return D > 0;
}

int shipWithinDays(int* weights, int weightsSize, int D)
{
	int left = 0;
	int right = 0;

	for(int i = 0; i < weightsSize; i++) {
		left = fmax(left, weights[i]);
		right += weights[i];
	}

	while(left < right) {
		int mid = (right + left) / 2;
		if (canShip(weights, weightsSize, D, mid)) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	return left;
}

/*
378. ��������е�KС��Ԫ��
�Ѷ��е�245
����һ�� n x n ��������ÿ�к�ÿ��Ԫ�ؾ�����������
�ҵ������е� k С��Ԫ�ء�
��ע�⣬���������ĵ� k СԪ�أ�
�����ǵ� k ����ͬ��Ԫ�ء�

ʾ����
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

���� 13��

*/
/*
���ȵ�k����һ������[l, r]�У�����l = matrix[0][0], r = matrix[row - 1][col - 1].
���Ƕ���ֵ��[l, r]���䣬mid = (l + r) >> 1, ����mid�����Ǽ�������
�ж���Ԫ��С�ڵ���mid��
�Ǹ���Ϊcnt����ô�У�
1�����cnt < k, ��ô[l, mid]�а�������Ԫ�ظ���һ��С��k����ô
��kСԪ��һ������[l, mid]
�У��ض���[mid + 1, r]�У����Ը���l = mid + 1.
2������cnt >= k����ô[l, mid]�а�������Ԫ�ظ����ʹ��ڵ���k��
����kСԪ��һ����[l,mid]�����У�
����r = mid;

������ô�þ������ж���Ԫ��С�ڵ���k���������þ�����
���ʣ������½ǿ�ʼ����ö��
���ϣ�
�㷨ʱ�临�Ӷ�ΪO(n * log(m)), ����n = max(row, col)�������������
�����������ֵ,
 m�����������ĳ��ȣ����������ֵ����Сֵ�Ĳ
*/
int getLowerCnt(int **matrix, int row, int col, int mid)
{
    int i = row - 1, j = 0, cnt = 0;
    while (i >= 0 && j < col) {
        if (matrix[i][j] <= mid) {
            cnt = cnt + i + 1;
            j++;
        } else {
            i--;
        }
    }
    return cnt;
}

int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k)
{
	if (matrix == NULL || matrixColSize == NULL || matrixSize == 0)
		return -1;
	int row = matrixSize, col = matrixColSize[0];
	int l = matrix[0][0], r = matrix[row - 1][col - 1];
	while (l < r) {//ֵ��
		int mid = (l + r) >> 1;
		if (getLowerCnt(matrix, row, col, mid) < k) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	return l;
}

/*
������ 10.09. ����������
����M��N����ÿһ�С�ÿһ�ж����������У�
���д�����ҳ�ĳԪ�ء�

ʾ��:

���о��� matrix ���£�

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
���� target = 5������ true��
���� target = 20������ false��
*/

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target)
{
	int i = 0, j = matrixColSize-1;

	while(j >= 0 && i < matrixRowSize) {
		if(matrix[i][j] > target)
			j--;
		else if(matrix[i][j] < target)
			i++;
		else
			return true;
	}

	return false;
}

/*
1198. �ҳ�����������С����Ԫ��
�Ѷ��е�8
����һ������ mat������ÿһ�е�Ԫ�ض��Ѿ��� ���� ˳��
�ź��ˡ������æ�ҳ���������Щ���� ��С�Ĺ���Ԫ�ء�
���������û�������Ĺ���Ԫ�أ����뷵�� -1��

ʾ����
���룺
mat = [
[1,2,3,4,5],
[2,4,5,8,10],
[3,5,7,9,11],
[1,3,5,7,9]
]
�����5

*/
int smallestCommonElement(int** mat, int matSize, int* matColSize)
{
	int map[10001];

	memset(map, 0, sizeof(map));
	for (int i = 0; i < matSize; i++) {
		for (int j = 0; j < matColSize[i]; j++) {
			map[mat[i][j]]++;
		}
	}

	for (int i = 0; i < 10001; i++) {
		if (map[i] == matSize)
			return i;
	}

	return -1;
}
/*
mat = [
[1,2,3,4,5],
[2,4,5,8,10],
[3,5,7,9,11],
[1,3,5,7,9]
]
*/
int smallestCommonElement(int** mat, int matSize, int* matColSize)
{
	int map[10001];
	memset(map, 0, sizeof(map));

	int row = matSize;
	int col = matColSize[0];
	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			if (++map[mat[i][j]] == row) {
				return mat[i][j];
			}
		}
	}

	return -1;
}
/*
mat = [
[1,2,3,4,5],
[2,4,5,8,10],
[3,5,7,9,11],
[1,3,5,7,9]
]
*/
int smallestCommonElement(int** mat, int matSize, int* matColSize)
{
	int map[10001];
	memset(map, 0, sizeof(map));

	int fd;
	int row = matSize;
	int col = matColSize[0];
	int *find_num = NULL;

	for (int j = 0; j < col; j++) {
		for (int i = 1; i < row; i++) {
			find_num = bsearch(&mat[0][j], mat[i], col, sizeof(int), cmp_int);
			if (find_num == NULL) {
				break;
			}
		}

		if (find_num != NULL)
			return mat[0][j];
	}

	return -1;
}

/*
702. ��������δ֪����������
�Ѷ��е�11
����һ�������������飬дһ���������� nums ������ target��
��� target ���ڣ����������±꣬���򷵻� -1��ע�⣬�����
��Ĵ�С��δ֪�ġ���ֻ����ͨ�� ArrayReader �ӿڷ���������飬
ArrayReader.get(k) ���������е� k ��Ԫ�أ��±�� 0 ��ʼ����
�������Ϊ���������е�������С�� 10000��������������
Խ�磬ArrayReader.get �᷵�� 2147483647��
���� 1��
����: array = [-1,0,3,5,9,12], target = 9
���: 4
����: 9 ������ nums �У��±�Ϊ 4
*/
int search(struct ArrayReader* reader, int target)
{
	if (getElement(reader, 0) == target)
		return 0;

	// search boundaries
	int left = 0, right = 1;
	while (getElement(reader, right) < target) {
		left = right;
		right <<= 1;
	}

	// binary search
	int mid, seachValue;
	while (left <= right) {
		mid = (left + right) >> 1;
		seachValue = getElement(reader, mid);

		if (seachValue == target)
			return mid;
		if (seachValue > target)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}

/*
153. Ѱ����ת���������е���Сֵ
�Ѷ��е�208
���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת��
( ���磬���� [0,1,2,4,5,6,7] ���ܱ�Ϊ [4,5,6,7,0,1,2] )��
���ҳ�������С��Ԫ�ء�
����Լ��������в������ظ�Ԫ�ء�
ʾ�� 1:
����: [3,4,5,1,2]
���: 1

*/
int findMin(int* nums, int numsSize)
{
	int left = 0;
	int right = numsSize - 1;

	while(right - left > 1) {
		int mid= (left + right) >> 1;
		if(nums[mid] > nums[right])
			left = mid;
		else
			right = mid;
	}

	return fmin(nums[left], nums[right]);
}


/*
436. Ѱ��������
�Ѷ��е�41
����һ�����䣬����ÿһ������ i������Ƿ����һ������ j��
������ʼ����ڻ�������� i ���յ㣬����Գ�Ϊ j �� i
��"�Ҳ�"��
�����κ����䣬����Ҫ�洢���������������� j ����С������
����ζ������ j ����С����ʼ�����ʹ���Ϊ"�Ҳ�"���䡣
������� j �����ڣ������� i �洢Ϊ -1���������Ҫ���
һ��ֵΪ�洢������ֵ�����顣
ע��:
1.	����Լ���������յ����Ǵ���������ʼ�㡣
2.	����Լٶ���Щ���䶼��������ͬ����ʼ�㡣
ʾ�� 1:
����: [ [1,2] ]
���: [-1]

����:������ֻ��һ�����䣬�������-1��
ʾ�� 2:
����: [ [3,4], [2,3], [1,2] ]
���: [-1, 0, 1]

����:����[3,4]��û������������"�Ҳ�"���䡣
����[2,3]������[3,4]������С��"��"���;
����[1,2]������[2,3]������С��"��"��㡣
ʾ�� 3:
����: [ [1,4], [2,3], [3,4] ]
���: [-1, 2, -1]

*/

// ��ά��������
int MyCmp(const void *pa, const void *pb)
{
    return (*(int**)pa)[0] - (*(int**)pb)[0];
}

int BinarySerach(int **intervalsTmp, int intervalsSize, int left, int right, int target)
{
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        // ����������Ŀ��ֱ�ӷ���
        if (target == intervalsTmp[mid][0]) {
            return intervalsTmp[mid][1];
        } else if (target < intervalsTmp[mid][0]) {
            // Ŀ��С ����������right = mid - 1
            right = mid - 1;
        } else if (target > intervalsTmp[mid][0]){
            left = mid + 1;
        }
    }

    // �ߵ����� whileѭ������������ֻ��һ��left == right + 1 ����ʵ��left��Ҫ����1
    // ��һ����� leftԪ�� ����target �������� ֱ�ӷ���
    // �ڶ������ leftԪ�� С��target ��̽��left�Ƿ񳬹� ���߽� ��Խ��ֱ�ӷ���leftԪ�� Խ��˵���Ҳ�����target�����
    // ������� ͨͨ����-1
    if (intervalsTmp[left - 1][0] >= target) {
        return intervalsTmp[left - 1][1];
    } else if (left < intervalsSize) {
        return intervalsTmp[left][1];
    }

    return -1;
}

int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize,
	int* returnSize)
{
	*returnSize = 0;
	if (intervalsSize == 0) {
		return NULL;
	}

	int* retArray = (int*)malloc(sizeof(int) * intervalsSize);
	int** intervalsTmp = (int**)malloc(sizeof(int*) * intervalsSize);
	for (int i = 0; i < intervalsSize; i++) {
		intervalsTmp[i] = (int*)malloc(sizeof(int) * (*intervalsColSize));
		intervalsTmp[i][0] = intervals[i][0];
		intervalsTmp[i][1] = i;
	}

	qsort(intervalsTmp, intervalsSize, sizeof(int*), MyCmp);

	// ���ֲ���
	for (int i = 0; i < intervalsSize; i++) {
	retArray[i] = BinarySerach(intervalsTmp, intervalsSize, 0, intervalsSize - 1, intervals[i][1]);
	}
	*returnSize = intervalsSize;
	return retArray;
}

/*
33. ������ת��������
�Ѷ��е�840
���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת��
( ���磬���� [0,1,2,4,5,6,7] ���ܱ�Ϊ [4,5,6,7,0,1,2] )��
����һ��������Ŀ��ֵ����������д������Ŀ��ֵ���򷵻��������������򷵻� -1 ��
����Լ��������в������ظ���Ԫ�ء�
����㷨ʱ�临�Ӷȱ����� O(log n) ����
ʾ�� 1:
����: nums = [4,5,6,7,0,1,2], target = 0
���: 4
ʾ�� 2:
����: nums = [4,5,6,7,0,1,2], target = 3
���: -1

*/
int search(int* nums, int numsSize, int target)
{
        int l = 0;
        int r = numsSize - 1;
        int mid;
        while (l < r){
            mid = l + (r - l) / 2;
            if ((nums[0]> target) ^ (nums[mid] < nums[0]) ^ (nums[mid] < target))
                l = mid + 1;
            else
                r = mid;
        }
        return l == r && nums[l] == target? l:-1;
}

int search(int* nums, int numsSize, int target)
{
        int left=0,right=numsSize-1,mid;
        while(left<=right){
            mid=left+(right-left)/2;
            if(nums[0]>target){  //Ŀ������������
                if(nums[mid]>=nums[0]) left=mid+1; //�е�����������
                else{ //�е�����������
                    if(nums[mid]==target) return mid;
                    else if(nums[mid]<target) left=mid+1;
                    else right=mid-1;
                }
            }
            else {//Ŀ������������
                if(nums[mid]<nums[0]) right=mid-1;//�е�����������
                else{ //�е�����������
                    if(nums[mid]==target) return mid;
                    else if(nums[mid]<target) left=mid+1;
                    else right=mid-1;
                }
            }
        }
        return -1;
}

/*
4. Ѱ�����������������λ��
�Ѷ�����2980
����������СΪ m �� n �����򣨴�С�������� nums1 �� nums2��
�����ҳ������������������λ��������Ҫ���㷨��ʱ�临�Ӷ�Ϊ O(log(m + n))��
����Լ��� nums1 �� nums2 ����ͬʱΪ�ա�

ʾ�� 1:
nums1 = [1, 3]
nums2 = [2]

����λ���� 2.0
ʾ�� 2:
nums1 = [1, 2]
nums2 = [3, 4]

����λ���� (2 + 3)/2 = 2.5

*/
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int m = nums1Size;
    int n = nums2Size;
    int len = m + n;
    int left = -1, right = -1;
    int aStart = 0, bStart = 0;
    for (int i = 0; i <= len / 2; i++) {
        left = right;
        if (aStart < m && (bStart >= n || nums1[aStart] < nums2[bStart])) {
            right = nums1[aStart++];
        } else {
            right = nums2[bStart++];
        }
    }
    if ((len & 1) == 0)
        return (left + right) / 2.0;
    else
        return right;
}

double getNum(int* nums1, int nums1Size, int* nums2, int nums2Size, int k){
        int result[nums1Size + nums2Size];
        int i = 0, j = 0;
        int cur = 0;
        while(i < nums1Size && j <nums2Size && cur <= k){
            if(nums1[i] < nums2[j]) result[cur++] = nums1[i++];
            else result[cur++] = nums2[j++];
        }
        while(i < nums1Size && cur <=k) result[cur++] = nums1[i++];
        while(j < nums2Size && cur <=k) result[cur++] = nums2[j++];
        return result[cur-1];
    }

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
        int length = nums1Size + nums2Size;
        double result = 0;
        //�ֱ��������ż������
        if(length % 2 != 0){
            result = getNum(nums1,nums1Size, nums2, nums2Size, length/2);
        }else{
            result = getNum(nums1,nums1Size, nums2, nums2Size, length/2-1)/2 +
				getNum(nums1,nums1Size, nums2, nums2Size, length/2)/2;
        }
        return result;
}

/*
295. ����������λ��
�Ѷ�����227
��λ���������б��м����������б�����ż������λ�������м���������ƽ��ֵ��
���磬
[2,3,4] ����λ���� 3
[2,3] ����λ���� (2 + 3) / 2 = 2.5
���һ��֧���������ֲ��������ݽṹ��
"	void addNum(int num) - �������������һ�����������ݽṹ�С�
"	double findMedian() - ����Ŀǰ����Ԫ�ص���λ����
ʾ����
addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2
����:
1.	����������������������� 0 �� 100 ��Χ�ڣ��㽫����Ż�����㷨��
2.	����������� 99% ���������� 0 �� 100 ��Χ�ڣ��㽫����Ż�����㷨��
ͨ������19,813
*/
typedef struct {
	int size;
	int array[1024 * 1024];
} MedianFinder;

MedianFinder* medianFinderCreate() {
	return (MedianFinder*)calloc(1, sizeof(MedianFinder));
}

void medianFinderAddNum(MedianFinder* obj, int num) {
	//insert sort
	if (obj->size >= 3) {
		int left = 0;
		int right = obj->size - 1;

		while(left + 1 < right) {
			int mid = (left + right) / 2;
			if (num > obj->array[mid]) {
				left = mid;
			} else {
				right = mid;
			}
		}

		int move;
		if (num > obj->array[right]) {
			move = right + 1;
		} else if (num < obj->array[left]){
			move = left;
		} else {
			move = right;
		}

		for (int i = obj->size; i > move; i--) {
			obj->array[i] = obj->array[i - 1];
		}

		obj->array[move] = num;
		obj->size++;
	} else {
		obj->array[obj->size++] = num;
		qsort(obj->array, obj->size, sizeof(int), cmp_int);
	}
}

double medianFinderFindMedian(MedianFinder* obj) {
	if (obj->size % 2 == 0) {
		return (obj->array[obj->size / 2] + obj->array[obj->size / 2 - 1]) * 0.5;
	} else {
		return obj->array[obj->size / 2];
	}
}

void medianFinderFree(MedianFinder* obj) {
	free(obj);
	obj = NULL;
}

/*
167. ����֮�� II - ������������
�Ѷȼ�375
����һ���Ѱ����������� ���������飬�ҵ�������ʹ���������֮�͵���Ŀ������
����Ӧ�÷����������±�ֵ index1 �� index2������ index1 ����С�� index2��
˵��:
"	���ص��±�ֵ��index1 �� index2�����Ǵ��㿪ʼ�ġ�
"	����Լ���ÿ������ֻ��ӦΨһ�Ĵ𰸣������㲻�����ظ�ʹ����ͬ��Ԫ�ء�
ʾ��:
����: numbers = [2, 7, 11, 15], target = 9
���: [1,2]
����: 2 �� 7 ֮�͵���Ŀ���� 9 ����� index1 = 1, index2 = 2 ��


*/

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;

    for (int i = 0; i < numbersSize; ++i) {
        int low = i + 1, high = numbersSize - 1;
        while (low <= high) {
            int mid = (high - low) / 2 + low;
            if (numbers[mid] == target - numbers[i]) {
                ret[0] = i + 1, ret[1] = mid + 1;
                return ret;
            } else if (numbers[mid] > target - numbers[i]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
    }
    ret[0] = -1, ret[1] = -1;
    return ret;
}

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;

    int low = 0, high = numbersSize - 1;
    while (low < high) {
        int sum = numbers[low] + numbers[high];
        if (sum == target) {
            ret[0] = low + 1, ret[1] = high + 1;
            return ret;
        } else if (sum < target) {
            ++low;
        } else {
            --high;
        }
    }
    ret[0] = -1, ret[1] = -1;
    return ret;
}