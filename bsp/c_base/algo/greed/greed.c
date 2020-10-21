
/*
Interval Scheduling �����������
̰���㷨һ�����������Ҫ ���ҵ�Ҫ��ĳ�µ���С������
�� ���ҵ���ĳЩ������ʺϵ������Ʒ������ �����⣬
���ṩ������������롣
1) ����(�ܶೡ��)
2) ����

*/

/*
121. ������Ʊ�����ʱ��
�Ѷȼ�1126
����һ�����飬���ĵ� i ��Ԫ����һ֧������Ʊ�� i ��ļ۸�
��������ֻ�������һ�ʽ��ף������������һ֧��Ʊһ�Σ������һ���㷨�����������ܻ�ȡ���������
ע�⣺�㲻���������Ʊǰ������Ʊ��
ʾ�� 1:
����: [7,1,5,3,6,4]
���: 5
����: �ڵ� 2 �죨��Ʊ�۸� = 1����ʱ�����룬�ڵ� 5 �죨��Ʊ�۸� = 6����ʱ��������������� = 6-1 = 5 ��
     ע���������� 7-1 = 6, ��Ϊ�����۸���Ҫ��������۸�ͬʱ���㲻��������ǰ������Ʊ��
ʾ�� 2:
����: [7,6,4,3,1]
���: 0
����: �����������, û�н������, �����������Ϊ 0��
*/
/*
����˼·�� ��Ʊ�������ԣ�
���������գ������۸� p1������۸� p2����������롢
����������׬ȡ��� p2-p1����ֵ������𣩡�
�������ǽ����գ� ������ǽ����չ�Ʊ�۸�ֱ�Ϊ
p1,p2,.....pn�����һ�������һ����������󣬼
pn-p1���ȼ���ÿ�춼�������
pn-p1=(p2-p1)+(p3-p2)+(p4-p3)+....+(pn-P(n-1))��
�����½������գ� ������������󣬼������Ǯ��
�㷨���̣�  ����������Ʊ�����ռ۸��б� price��
�������������ǽ����ն�������׬���������󣩣�
�����½������ն���������������Ǯ����
�� tmp Ϊ�� i-1 ��������� i ������׬ȡ������
�� tmp = prices[i] - prices[i - 1] �� ����������Ϊ�� tmp > 0��
��������������� profit��������Ϊ 00 ��Ϊ����
��ֱ�������� ������ɺ󣬷��������� profit��
*/
int maxProfit(int* prices, int pricesSize)
{
	int profit = 0;
	for (int i = 1; i <pricesSize; i++) {
		int tmp = prices[i] - prices[i - 1];
		if (tmp > 0)
			profit += tmp;
	}

	return profit;
}
int maxProfit(int* prices, int pricesSize)
{
	int minprice = INT_MAX;
	int maxprofix = 0;

	for (int i = 0; i < pricesSize; i++) {
		maxprofix = fmax(maxprofix, prices[i] - minprice);
		minprice = fmin(minprice, prices[i]);
	}

	return maxprofix;
}

/*
1221. �ָ�ƽ���ַ���
�Ѷȼ�60
��һ����ƽ���ַ������У�'L' �� 'R' �ַ�����������ͬ�ġ�
����һ��ƽ���ַ��� s�����㽫���ָ�ɾ����ܶ��ƽ���ַ�����
���ؿ���ͨ���ָ�õ���ƽ���ַ��������������
ʾ�� 1��
���룺s = "RLRRLLRLRL"
�����4
���ͣ�s ���Էָ�Ϊ "RL", "RRLL", "RL", "RL", ÿ�����ַ����ж�������ͬ������ 'L' �� 'R'��
ʾ�� 2��
���룺s = "RLLLLRRRLR"
�����3
���ͣ�s ���Էָ�Ϊ "RL", "LLLRRR", "LR", ÿ�����ַ����ж�������ͬ������ 'L' �� 'R
*/
/*
���˼·��
����һ��'L'��'R'�Ĳ�ֵ������diffCount��
����һ��ƽ���Ӵ�������count��
˳�����Դ���ַ�����L��diffCount+1������R��diffCount-1��
ÿ����һ���ַ����һ��diffCount�Ƿ�Ϊ0����Ϊ0��count+1
*/
int balancedStringSplit(char * s)
{
	int diffCnt = 0;
	int count = 0;

	if (s == NULL)
		return 0;

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'L')
			diffCnt++;
		else
			diffCnt--;

/*
RLRRLL diffCnt = 0
RL diffCnt = 0
RRLL diffCnt = 0
*/
		if (diffCnt == 0)
			count++;
	}

	return count;
}


/*
870. ����ϴ��
����������С��ȵ����� A �� B��A �����
B �����ƿ��������� A[i] > B[i] ������ i ����Ŀ��������
���� A ���������У�ʹ������� B ��������󻯡�
ʾ�� 1��
���룺A = [2,7,11,15], B = [1,10,4,11]
�����[2,11,7,15]
*/
struct obj {
	int data;
	int index;
};

int cmp_struct( const void *a , const void *b){
	struct obj *c = (struct obj *)a;
	struct obj *d = (struct obj *)b;

	return c->data- d->data;
}

int* advantageCount(int* A, int ASize, int* B, int BSize, int* returnSize){
    int l = 0;
    int r = ASize - 1;
	struct obj *ao = (struct obj *)malloc(sizeof(struct obj) * ASize);
	struct obj *bo = (struct obj *)malloc(sizeof(struct obj) * BSize);
	int *ret = (int *)malloc(sizeof(int) * ASize);

	for (int i = 0; i < ASize; i++) {
		ao[i].data = A[i];
		ao[i].index = i;

		bo[i].data = B[i];
		bo[i].index = i;
	}

	qsort(ao, ASize, sizeof(struct obj), cmp_struct);
	qsort(bo, ASize, sizeof(struct obj), cmp_struct);
    	int j = BSize - 1;
	for (int i = 0; i < ASize; i++) {
		if (ao[i].data > bo[l].data) {
			ret[bo[l].index] = ao[i].data; // ���A�����ֵ����B�����ֵ���A[i]��ֵ����list�����е�B�����������
            		l++;
		} else {
			ret[bo[r].index] = ao[i].data;// �����С�ڵ������A[i]��ֵ����list������B������������λ�á�
            		r--;
		}
	}

	*returnSize = ASize;
	return ret;
}

/*
991. ���˵ļ�����
�Ѷ��е�57
����ʾ�����ֵĻ��������ϣ����ǿ���ִ���������ֲ�����
"	˫����Double��������ʾ���ϵ����ֳ� 2��
"	�ݼ���Decrement��������ʾ���ϵ����ּ� 1 ��
�������������ʾ���� X��
������ʾ���� Y �������С��������
ʾ�� 1��
���룺X = 2, Y = 3
�����2
���ͣ��Ƚ���˫�����㣬Ȼ���ٽ��еݼ����� {2 -> 4 -> 3}.

*/
/*
�������ʾ�����������ڼ�����ֻ��˫����ݼ���XY�ֶ�Ϊ��������ˣ���X > Yʱ��ֻ�ܵݼ�X-Y�δﵽĿ�ġ���X = Y ��������������Ժ���һ������һ���жϡ�
��Y > Xʱ�����Y��һ����������ô�õ��������һ����Ȼ�ǵݼ������Y��һ��ż��������õ��������һ���ǵݼ�����ô�����ڶ���ҲӦ���ǵݼ�����Y��һ������X���������X���Yʱһ��������˫������ô����˫������еݼ��������ȵݼ���˫�������ѵĲ���Ӧ�û���٣������ܳ�ƽ��
��ô����ͱ���˵ݹ����⡣��Y > Xʱ��Y������ʱ��������һ���ż���������ܲ�������1 + brokenCalc(X,(Y+1))����Y��ż��ʱ���ܲ�������1 + brokenCalc(X,Y/2)��

*/
int brokenCalc(int X, int Y)
{
	if (Y <= X)
		return X - Y;
	if (Y % 2 == 0) {
		return 1 + brokenCalc(X , Y /2);
	} else
		return 1 + brokenCalc(X , Y + 1);
}

/*
55. ��Ծ��Ϸ
�Ѷ��е�761
����һ���Ǹ��������飬�����λ������ĵ�һ��λ�á�
�����е�ÿ��Ԫ�ش������ڸ�λ�ÿ�����Ծ����󳤶ȡ�
�ж����Ƿ��ܹ��������һ��λ�á�
ʾ�� 1:
����: [2,3,1,1,4]
���: true
����: ���ǿ������� 1 ������λ�� 0 ���� λ�� 1, Ȼ���ٴ�λ��
1 �� 3 ���������һ��λ�á�
ʾ�� 2:
����: [3,2,1,0,4]
���: false
����: �������������ܻᵽ������Ϊ 3 ��λ�á�����λ�õ���
����Ծ������ 0 �� ��������Զ�����ܵ������һ��λ�á�
*/
bool canJump(int* nums, int numsSize)
{
	int rightmost = 0;

	for (int i = 0; i < numsSize; ++i) {
		if (i <= rightmost) {
			rightmost = fmax(rightmost, i + nums[i]);
			if (rightmost >= numsSize - 1) {
				return true;
			}
		}
	}

	return false;
}

/*
45. ��Ծ��Ϸ II
�Ѷ�����649
����һ���Ǹ��������飬�����λ������ĵ�һ��λ�á�
�����е�ÿ��Ԫ�ش������ڸ�λ�ÿ�����Ծ����󳤶ȡ�
���Ŀ����ʹ�����ٵ���Ծ����������������һ��λ�á�
ʾ��:
����: [2,3,1,1,4]
���: 2
����: �������һ��λ�õ���С��Ծ���� 2��
*/

/*
���ǵ�Ŀ���ǵ�����������һ��λ�ã�������ǿ��Կ������һ����Ծǰ���ڵ�λ�ã���λ��ͨ����Ծ�ܹ��������һ��λ�á�����ж��λ��ͨ����Ծ���ܹ��������һ��λ�ã���ô����Ӧ����ν���ѡ���أ�ֱ�������������ǿ��ԡ�̰�ġ���ѡ��������һ��λ����Զ���Ǹ�λ�ã�Ҳ���Ƕ�Ӧ�±���С���Ǹ�λ�á���ˣ����ǿ��Դ����ұ������飬ѡ���һ������Ҫ���λ�á��ҵ����һ����Ծǰ���ڵ�λ��֮�����Ǽ���̰�ĵ�Ѱ�ҵ����ڶ�����Ծǰ���ڵ�λ�ã��Դ����ƣ�ֱ���ҵ�����Ŀ�ʼλ�á����ߣ�LeetCode-Solution���ӣ�https://leetcode-cn.com/problems/jump-game-ii/solution/tiao-yue-you-xi-ii-by-leetcode-solution/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
int jump(int* nums, int numsSize)
{
	int position = numsSize - 1;
	int steps = 0;
	while (position > 0) {
		for (int i = 0; i < position; i++) {
			if (i + nums[i] >= position) {
				position = i;
				steps++;
				break;
			}
		}
	}
	return steps;
}

/*
406. ��������ؽ�����
�Ѷ��е�424
�����д���˳���һȺ��վ��һ�����С� ÿ������һ��������(h, k)��ʾ������h������˵���ߣ�k�����������ǰ������ߴ��ڻ����h�������� ��дһ���㷨���ؽ�������С�
ע�⣺
����������1100�ˡ�
ʾ��
����:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

���:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int compare(const void *a,const void *b){
    const int* pa = *(const int **)a;
    const int* pb = *(const int **)b;
    return pa[0] == pb[0]?pa[1] - pb[1]:pb[0] - pa[0];
}

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes){
    int **res = NULL;
    res = (int **)malloc(sizeof(int *) * peopleSize);
    int i;
    int pos;
    //for(i = 0;i < peopleSize;i++){
        //res[i] = (int *)malloc(sizeof(int) * 2);
   // }

    qsort(people, peopleSize, sizeof(int *), compare);
    //for(i = 0;i < peopleSize;i++)
        //printf("%d\t%d\n",people[i][0],people[i][1]);
    for(i = 0;i < peopleSize;i++){
        pos = people[i][1];
        //printf("people i1 is %d\n",people[i][1]);
        memmove(&res[pos + 1], &res[pos], (i - pos) *sizeof(int *));
        res[pos] = (int *)malloc(sizeof(int) * 2);
        res[pos][0] = people[i][0];
        res[pos][1] = people[i][1];
    }

    *returnSize = peopleSize;
    *returnColumnSizes = peopleColSize;
    return res;
}

/*
135. �ַ��ǹ�
�Ѷ�����239
��ʦ��������Ƿַ��ǹ����� N ������վ����һ��ֱ�ߣ���ʦ�����ÿ�����ӵı��֣�Ԥ�ȸ��������֡�
����Ҫ��������Ҫ�󣬰�����ʦ����Щ���ӷַ��ǹ���
"	ÿ���������ٷ��䵽 1 ���ǹ���
"	���ڵĺ����У����ָߵĺ��ӱ����ø�����ǹ���
��ô������������ʦ������Ҫ׼�����ٿ��ǹ��أ�
ʾ�� 1:
����: [1,0,2]
���: 5
����: ����Էֱ�����������ӷַ� 2��1��2 ���ǹ���

*/
int candy(int* ratings, int ratingsSize)
{
        int sum = 0;
        int left2right[ratingsSize];
        int right2left[ratingsSize];
	for (int i = 0; i < ratingsSize; i++) {
		left2right[i] = right2left[i] = 1;
	}

        for (int i = 1; i < ratingsSize; i++) {
            if (ratings[i] > ratings[i - 1]) {
                left2right[i] = left2right[i - 1] + 1;
            }
        }
        for (int i = ratingsSize - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                right2left[i] = right2left[i + 1] + 1;
            }
        }
        for (int i = 0; i < ratingsSize; i++) {
            sum += fmax(left2right[i], right2left[i]);
        }
        return sum;
}

int candy(int* ratings, int ratingsSize)
{
        int candies[ratingsSize];
	for (int i = 0; i < ratingsSize; i++) {
		candies[i] = 1;
	}

        for (int i = 1; i < ratingsSize; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        int sum = candies[ratingsSize - 1];
        for (int i = ratingsSize - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = fmax(candies[i], candies[i + 1] + 1);
            }
            sum += candies[i];
        }
        return sum;
}

/*
452. �����������ļ���������
�Ѷ��е�162�ղط����л�ΪӢ�Ĺ�ע����
�ڶ�ά�ռ�����������ε����򡣶���ÿ�������ṩ��������ˮƽ�����ϣ�����ֱ���Ŀ�ʼ�ͽ������ꡣ��������ˮƽ�ģ�����y���겢����Ҫ�����ֻҪ֪����ʼ�ͽ�����x������㹻�ˡ���ʼ��������С�ڽ������ꡣƽ����������104������
һ֧������������x��Ӳ�ͬ����ȫ��ֱ�������������x�����һ֧��������һ�������ֱ���Ŀ�ʼ�ͽ�������Ϊ xstart��xend�� ������  xstart �� x �� xend���������ᱻ��������������Ĺ���������û�����ơ� ����һ�������֮�󣬿������޵�ǰ�����������ҵ�ʹ����������ȫ��������������Ĺ�������С������
Example:
����:
[[10,16], [2,8], [1,6], [7,12]]

���:
2

����:
���ڸ����������ǿ�����x = 6���䱬[2,8],[1,6]�������򣩺� x = 11���䱬�����������򣩡�

*/
int cmp_doublePoint(const void *a, const void *b)
{
	int * aa = *((int **)a);
	int * bb = *((int **)b);

	return aa[1] - bb[1];
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize)
{
    if (pointsSize == 0) return 0;

	qsort(points, pointsSize, sizeof(points[0]), cmp_doublePoint);

    int arrows = 1;
    int xStart, xEnd, firstEnd = points[0][1];
    for (int i = 0; i < pointsSize; i++) {
      xStart = points[i][0];
      xEnd = points[i][1];
      // if the current balloon starts after the end of another one,
      // one needs one more arrow
      if (firstEnd < xStart) {
        arrows++;
        firstEnd = xEnd;
      }
    }
    return arrows;
  }

/*
56. �ϲ�����
�Ѷ��е�545
����һ������ļ��ϣ���ϲ������ص������䡣
ʾ�� 1:
����: [[1,3],[2,6],[8,10],[15,18]]
���: [[1,6],[8,10],[15,18]]
����: ���� [1,3] �� [2,6] �ص�, �����Ǻϲ�Ϊ [1,6].
ʾ�� 2:
����: [[1,4],[4,5]]
���: [[1,5]]
����: ���� [1,4] �� [4,5] �ɱ���Ϊ�ص����䡣

*/
int cmp_doublePoint(const void *a, const void *b)
{
	int **aa = (int **)a;
	int **bb = (int **)b;

	if (aa[0][0] == bb[0][0]) {
		return aa[0][1] - bb[0][1];
	} else {
		return aa[0][0] - bb[0][0];
	}
}
//[[1,3],[2,6],[8,10],[15,18]]
//[[1,4],[4,5]]
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
	int* returnSize, int** returnColumnSizes)
{
	if (intervals == NULL || intervalsSize <= 0 || intervalsColSize == NULL) {
		*returnSize = 0;
		return NULL;
	}

	qsort(intervals, intervalsSize, sizeof(intervals[0]), cmp_doublePoint);
	int **res = (int **)calloc(intervalsSize, sizeof(int *));
	*returnColumnSizes = (int *)calloc(intervalsSize, sizeof(int));
	for (int i = 0; i < intervalsSize; i++) {
		res[i] = (int *)calloc(2, sizeof(int));
		(*returnColumnSizes)[i] = 2;
	}

	res[0][0] = intervals[0][0];
	res[0][1] = intervals[0][1];
	*returnSize = 1;
	for (int i = 1; i < intervalsSize; i++) {
		if (intervals[i][0] > res[*returnSize - 1][1]) {
			res[*returnSize][0] = intervals[i][0];
			res[*returnSize][1] = intervals[i][1];
			(*returnSize)++;
		} else {
			res[*returnSize - 1][1] = fmax(res[*returnSize - 1][1] , intervals[i][1]);
		}
	}

	return res;
}

/*
376. �ڶ�����
�Ѷ��е�229�ղط����л�ΪӢ�Ĺ�ע����
�����������֮��Ĳ��ϸ���������͸���֮�佻�棬���������г�Ϊ�ڶ����С���һ���������ڵĻ���������������������������Ԫ�ص�����Ҳ�ǰڶ����С�
���磬 [1,7,4,9,2,5] ��һ���ڶ����У���Ϊ��ֵ (6,-3,5,-7,3) ������������ֵġ��෴, [1,4,7,2,5] �� [1,7,4,5,5] ���ǰڶ����У���һ����������Ϊ����ǰ������ֵ�����������ڶ�����������Ϊ�������һ����ֵΪ�㡣
����һ���������У�������Ϊ�ڶ����е�������еĳ��ȡ� ͨ����ԭʼ������ɾ��һЩ��Ҳ���Բ�ɾ����Ԫ������������У�ʣ�µ�Ԫ�ر�����ԭʼ˳��
ʾ�� 1:
����: [1,7,4,9,2,5]
���: 6
����: �������о�Ϊ�ڶ����С�
ʾ�� 2:
����: [1,17,5,10,13,15,10,5,16,8]
���: 7
����: ������а�����������Ϊ 7 �ڶ����У�����һ����Ϊ[1,17,10,13,10,16,8]��
ʾ�� 3:
����: [1,2,3,4,5,6,7,8,9]
���: 2

*/
int calculate(int *nums, int numsSize, int index, bool isUp)
{
        int maxcount = 0;
        for (int i = index + 1; i < numsSize; i++) {
            if ((isUp && nums[i] > nums[index]) || (!isUp && nums[i] < nums[index]))
                maxcount = fmax(maxcount, 1 + calculate(nums, numsSize, i, !isUp));
        }
        return maxcount;
 }

int wiggleMaxLength(int* nums, int numsSize)
{
        if (numsSize < 2)
            return numsSize;
        return 1 + fmax(calculate(nums, numsSize, 0, true), calculate(nums, numsSize, 0, false));
}

int wiggleMaxLength(int* nums, int numsSize)
{
    int down = 1, up = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i - 1])
            up = down + 1;
        else if (nums[i] < nums[i - 1])
            down = up + 1;
    }
    return numsSize == 0 ? 0 : fmax(down, up);
}

/*
738. ��������������
�Ѷ��е�65�ղط����л�ΪӢ�Ĺ�ע����
����һ���Ǹ����� N���ҳ�С�ڻ���� N ������������ͬʱ���������Ҫ���������λ���ϵ������ǵ���������
�����ҽ���ÿ������λ���ϵ����� x �� y ���� x <= y ʱ�����ǳ���������ǵ��������ġ���
ʾ�� 1:
����: N = 10
���: 9
ʾ�� 2:
����: N = 1234
���: 1234

*/

//̰���㷨����������ÿһλ����ǰλ�����ֱ���һλ�����ִ��򽫸�λ���ּ�С1��Ȼ��֮��λ������ȫ����Ϊ9
int monotoneIncreasingDigits(int N)
{
        char num[1024] = {0};
		sprintf(num, "%d", N);
        int t = strlen(num);
        for(int i=strlen(num)-1;i>=1;i--){
            if(num[i]<num[i-1]){
                t=i;
                num[i-1]--;
            }
        }
        while(t<strlen(num))
            num[t++]='9';

        return atoi(num);
}

//̰���㷨����������ÿһλ����ǰλ�����ֱ���һλ�����ִ��򽫸�λ���ּ�С1��Ȼ��֮��λ������ȫ����Ϊ9
//̰���㷨����������ÿһλ����ǰλ�����ֱ���һλ�����ִ��򽫸�λ���ּ�С1��Ȼ��֮��λ������ȫ����Ϊ9
int monotoneIncreasingDigits(int N)
{
        char s[1024] = {0};
	sprintf(s, "%d", N);
        int p=0;
        for(int i=strlen(s)-1;i>=1;i--)
        {
            if(s[i]<s[i-1])
            {
                p=i;
                s[i-1]--;
                while(p<strlen(s))
                {
                    s[p++]='9';
                }
            }
        }
        return atoi(s);
    }

//̰���㷨����������ÿһλ����ǰλ�����ֱ���һλ�����ִ��򽫸�λ���ּ�С1��Ȼ��֮��λ������ȫ����Ϊ9
//̰���㷨����������ÿһλ����ǰλ�����ֱ���һλ�����ִ��򽫸�λ���ּ�С1��Ȼ��֮��λ������ȫ����Ϊ9
int monotoneIncreasingDigits(int N)
{
        char s[1024] = {0};
	sprintf(s, "%d", N);
        int p=0;
        for(int i=strlen(s)-1;i>=1;i--)
        {
            if(s[i]<s[i-1])
            {
                p=i;
                s[i-1]--;
                while(p<strlen(s))
                {
                    s[p++]='9';
                }
            }
        }
        return atoi(s);
    }

/*
659. �ָ�����Ϊ����������
����һ��������������������� num�����ܰ����ظ����֣������㽫���Ƿָ��һ�����������У�����ÿ�������ж���������������ҳ�������Ϊ 3 ��

���������������ָ�򷵻� true �����򣬷��� false ��



ʾ�� 1��

����: [1,2,3,3,4,5]
���: True
����:
����Էָ�������������������� :
1, 2, 3
3, 4, 5
*/
int nc[10000];
int tail[10002];
bool isPossible(int* nums, int numsSize){
    int i, pos;
    int base = 0;
    memset(nc, 0, sizeof(nc));
    memset(tail, 0, sizeof(tail));
    if (nums[0] < 0) {
        base = abs(nums[0]);
    }
    for (i = 0; i < numsSize; i++) {
        pos = base + nums[i];
        nc[pos]++;
    }

    for (i = 0; i < numsSize; i++) {
        pos = base + nums[i];
        if (nc[pos] == 0) {
            continue;
        } else if (pos > 0 && nc[pos] > 0 && tail[pos-1] > 0) {
            nc[pos]--;
            tail[pos-1]--;
            tail[pos]++;
        } else if (nc[pos] > 0 && nc[pos+1] > 0 && nc[pos+2] > 0) {
            nc[pos]--;
            nc[pos+1]--;
            nc[pos+2]--;
            tail[pos+2]++;
        } else {
            return false;
        }
    }
    return true;
}

/*
358. K �����������ַ���
����һ���ǿյ��ַ��� s ��һ������ k����Ҫ������ַ����е���ĸ�����������У�ʹ�����ź���ַ�������ͬ��ĸ��λ�ü����������Ϊ k��

����������ַ�������Сд��ĸ��ɣ�����Ҳ�����������Ϊ k �����Ž�����뷵��һ�����ַ��� ""��

ʾ�� 1��

����: s = "aabbcc", k = 3
���: "abcabc"
����: ��ͬ����ĸ���µ��ַ����м������ 3 ����λ���롣
ʾ�� 2:

����: s = "aaabc", k = 3
���: ""
����: û�а취�ҵ����ܵ����Ž����
*/
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

typedef struct letterCnt {
    int letterVal;
    int letterCnt;
    int prePos;
}LETTER_CNT;

char findNextChar(LETTER_CNT *letterCnt, int curPos, int k)
{
    char nextChar = 0;
    int i = 0;
    for (; i < 27; i++) {
        if (letterCnt[i].letterCnt == 0) {
            continue;
        }

        if (letterCnt[i].prePos == -1  ||  (curPos - letterCnt[i].prePos) >= k) {
            letterCnt[i].prePos = curPos;
            letterCnt[i].letterCnt -= 1;
            nextChar =  letterCnt[i].letterVal;
            break;
        }
    }

    return nextChar;
}
int compareLetterCnt(const void *elm1, const void *elm2) {
    return ((LETTER_CNT *)elm2)->letterCnt - ((LETTER_CNT *)elm1)->letterCnt;
}

char * rearrangeString(char * s, int k)
{
    LETTER_CNT letterCnt[27] = { 0 };
    int letterPrePos[27] = { 0 };
    int maxDupLetter = 0;

    if (s == NULL) {
        return "";
    }

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        letterCnt[s[i] - 'a'].letterVal = s[i];
        letterCnt[s[i] - 'a'].letterCnt += 1;
        letterCnt[s[i] - 'a'].prePos = -1;
        maxDupLetter = MAX(maxDupLetter, letterCnt[s[i] - 'a'].letterCnt);
    }

    if ((maxDupLetter - 1) * k + 1 > len) {
        return "";
    }

    qsort(letterCnt, 27, sizeof(LETTER_CNT),  compareLetterCnt);

    char *pNewStr = (char *)malloc(len + 1);
    memset(pNewStr, 0, len + 1);
    int i  = 0;
    for (i = 0; i < len; i++) {
        char c  =  findNextChar(letterCnt, i, k);
        qsort(letterCnt, 27, sizeof(LETTER_CNT),  compareLetterCnt); // ȡ����������һ�� ��֤����ȡ�����ַ�
        if (c == 0) {
            break;
        }
        pNewStr[i] = c;
    }

    if (i != len) {
        free(pNewStr);
        return "";
    }

    return pNewStr;
}

/*
502. IPO
���� ���ۣ�LeetCode��������ʼ�� IPO��Ϊ���Ը��ߵļ۸񽫹�Ʊ��������Ͷ�ʹ�˾������ ϣ���� IPO ֮ǰ��չһЩ��Ŀ���������ʱ��� ������Դ���ޣ���ֻ���� IPO ֮ǰ������ k ����ͬ����Ŀ������ ���� ��������� k ����ͬ��Ŀ��õ�������ʱ��ķ�ʽ��

�������ɸ���Ŀ������ÿ����Ŀ i��������һ�������� Pi��������Ҫ��С���ʱ� Ci ��������Ӧ����Ŀ����������� W �ʱ����������һ����Ŀʱ���㽫��ô����������󽫱���ӵ�������ʱ��С�

�ܶ���֮���Ӹ�����Ŀ��ѡ����� k ����ͬ��Ŀ���б�����������ʱ�����������տɻ�õ�����ʱ���

ʾ�� 1:

����: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

���: 4

����:
������ĳ�ʼ�ʱ�Ϊ 0���㾡���Դ� 0 ����Ŀ��ʼ��
����ɺ��㽫��� 1 ������������ʱ�����Ϊ 1��
��ʱ�����ѡ��ʼ 1 �Ż� 2 ����Ŀ��
������������ѡ��������Ŀ����������Ҫ��� 2 ����Ŀ�Ի�������ʱ���
��ˣ���������󻯵��ʱ���Ϊ 0 + 1 + 3 = 4��
*/
typedef struct {
	int p; // profit
	int c; // capital
} node_t;

typedef int (*cmp_fn)(const void *,const void *);

int cmpc(const void*a, const void*b)
{ // �Գɱ�cost�������򣬴�С����
	node_t* n1 = (node_t*)a;
	node_t* n2 = (node_t*)b;
	return (n1->c - n2->c);
}

int cmpp(const void*a, const void*b)
{ // ������profit�������򣬴�С���󣬴󶥶�
	node_t* n1 = (node_t*)a;
	node_t* n2 = (node_t*)b;
	return (n1->p - n2->p);
}

void swap(node_t *a, node_t *b)
{ // ��������Ԫ��
    node_t t = *a;
    *a = *b;
    *b = t;
}

bool HeadNodeDown(node_t *a, int n, cmp_fn cmp, int i)
{ // �ڵ�Ԫ��i�����³�
    if (a == NULL || n < 0 || i > n ) {
        return false;
    }
	int dad = i; // ��Ҷ�ӽڵ㣬�����ڵ�ı��
    int k = n / 2 - 1; // ��Ҷ�ӽڵ�����λ��
	while (dad <= k) { // ���ڵ㣬��Ȼ�Ƿ�Ҷ�ӽڵ�
		int son = dad * 2 + 1; // ���ӽڵ�ı��
		if (son + 1 < n && cmp(&a[son], &a[son + 1]) < 0) {
		    son = son + 1;  // ���ӽڵ����ѡ�ұ�
		}
		if (cmp(&a[son], &a[dad]) <= 0) { // �ӽڵ㶼�Ƚ�С
		    break; // �������³���
		}
		swap(&a[son], &a[dad]);
		dad = son;
	}
    return true;
}

bool HeadNodeUp(node_t *a, int n, cmp_fn cmp, int i)
{ // �ڵ�Ԫ��i�����ϸ�
    if (a == NULL || n < 0 || i > n ) {
        return false;
    }
	int son = i; // Ҷ�ӽڵ㣬���ӽڵ�ı��
	while (son > 0) { // �ӽڵ㣬��Ȼ�������ڵ�
		int dad = (son - 1) / 2; // ���ڵ�ı��
		if (cmp(&a[son], &a[dad]) <= 0) { // �ӽڵ�Ƚ�С
		    break; // �������ϸ���
		}
		swap(&a[son], &a[dad]);
		son = dad;
	}
    return true;
}

bool HeadNodePush(node_t *a, int *n, cmp_fn cmp, node_t *t)
{ // �ڶ���ѹ��һ���ڵ�Ԫ�أ���β�����
	if (a == NULL || n == NULL || *n < 0 || t == NULL) {
        return false;
    }
	a[*n] = *t;
    (*n)++;
    HeadNodeUp(a, *n, cmp, *n-1);
    return true;
}

bool HeadNodePop(node_t *a, int *n, cmp_fn cmp, node_t *t)
{ // �ڶ��е���һ���ڵ�Ԫ�أ��Ӷ�������
	if (a == NULL || n == NULL || *n < 0 || t == NULL) {
        return false;
    }
    swap(&a[0], &a[*n - 1]);
    *t = a[*n - 1];
    memset(&a[*n - 1], 0, sizeof(node_t));
    (*n)--;
    HeadNodeDown(a, *n, cmp, 0);
    return true;
}

bool HeadCreate(node_t *a, int n, cmp_fn cmp)
{ // �ѵķ�Ҷ�ӽڵ�ĵ���
    if (a == NULL || n < 0) {
        return false;
    }
    int k = n / 2 - 1; // ��Ҷ�ӽڵ�����λ��
    for (int i = k; i >= 0; i--) { // �������з�Ҷ�ӽڵ�
    	HeadNodeDown(a, n, cmp, i); // ����ж��Ƿ�����³�
    }
    return true;
}

bool HeapSort(node_t *a, int n)
{ // �����򣬴󶥶ѣ���С����
    if (a == NULL || n < 0) {
        return false;
    }
    for (int i = n; i > 0; i--) {
        HeadCreate(a, i, cmpp);
        swap(&a[0], &a[i - 1]);
    }
    return true;
}

int gd(int k, int w, node_t*a, int n)
{ // ̰��greedy�㷨��ÿ�ζ�ѡ�����������Ǹ�
    if (k == 0 || w < 0 || a == NULL || n <= 0) {
        return 0;
    }
    node_t c[n];
    memset(c, 0, sizeof(c));
	qsort(a, n, sizeof(node_t), cmpc);
	for (int ai = 0, ci = 0; k > 0; k--) {
		while (ai < n && a[ai].c <= w) { // ����ѡ
			HeadNodePush(c, &ci, cmpp, &a[ai]);
			ai++;
		}
		if (ci > 0) { // ����Ԫ�ؿ�ѡ
			node_t t; // ��ʱ����
			HeadNodePop(c, &ci, cmpp, &t);
			w += t.p;
		}
	}
    return w;
}

int findMaximizedCapital(int k, int w, int*p, int pn, int*c, int cn)
{
    if (k == 0 || w < 0 || p == NULL || pn <= 0 || c == NULL || cn <= 0) {
        return 0;
    }
    node_t a[pn];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < pn; i++) {
    	a[i].p = p[i];
    	a[i].c = c[i];
	}
    return gd(k, w, a, pn);
}