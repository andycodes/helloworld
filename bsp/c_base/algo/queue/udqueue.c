/*
1438. 绝对差不超过限制的最长连续子数组
给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返
回最长连续子数组的长度，该子数组中的任意两个元素之间
的绝对差必须小于或者等于 limit 。
如果不存在满足条件的子数组，则返回 0 。
示例 1：
输入：nums = [8,2,4,7], limit = 4
输出：2
解释：所有子数组如下：
[8] 最大绝对差 |8-8| = 0 <= 4.
[8,2] 最大绝对差 |8-2| = 6 > 4.
[8,2,4] 最大绝对差 |8-2| = 6 > 4.
[8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
[2] 最大绝对差 |2-2| = 0 <= 4.
[2,4] 最大绝对差 |2-4| = 2 <= 4.
[2,4,7] 最大绝对差 |2-7| = 5 > 4.
[4] 最大绝对差 |4-4| = 0 <= 4.
[4,7] 最大绝对差 |4-7| = 3 <= 4.
[7] 最大绝对差 |7-7| = 0 <= 4.
因此，满足题意的最长子数组的长度为 2 。
*/

#include <stdlib.h>
#include <stdio.h>

//【算法思路】滑窗 + 单调队列。
// 1.滑窗，根据记录的最大最小值，判断是否在范围内
// 2.单调增队列，记录最大值位置
// 3.按掉减队列，记录最小值位置
// 4.如果新增数据超出范围，则进行结算
// 5.j结算过后，移动左边界，直至范围满足要求
int longestSubarray(int* nums, int numsSize, int limit)
{
    if(numsSize == 1) {
        return 1;
    }

    int *inc_que = (int *)calloc(numsSize, sizeof(int));
    int iq_r = 0;
    int iq_w = 0;
    int iq_size = 0;

    int *dec_que = (int *)calloc(numsSize, sizeof(int));
    int dq_r = 0;
    int dq_w = 0;
    int dq_size = 0;

    //将首元素填入
    inc_que[iq_w++] = 0;
    iq_size++;

    //将首元素填入
    dec_que[dq_w++] = 0;
    dq_size++;

    int max_len = 1;

    int left = 0, right = 1;
    while(right < numsSize) {
        //剪枝
        if(max_len >= numsSize - left) {
            break;
        }

        int minid = inc_que[iq_r];
        int maxid = dec_que[dq_r];
        int cur = nums[right];
        //printf("max = %d, min = %d\n", nums[maxid], nums[minid]);

        //更新上升队列，向前挤掉大于该值的数据
        while(iq_size > 0) {
            if(nums[inc_que[iq_w - 1]] > cur) {
                iq_w--;
                iq_size--;
            } else {
                break;
            }
        }
        inc_que[iq_w++] = right;
        iq_size++;

        //更新下降队列,向前挤掉小于该值的数据
        while(dq_size > 0) {
            if(nums[dec_que[dq_w - 1]] < cur) {
                dq_w--;
                dq_size--;
            } else {
                break;
            }
        }
        dec_que[dq_w++] = right;
        dq_size++;

        //如果在范围之内,则继续访问
        if(abs(nums[right] - nums[maxid]) <= limit && abs(nums[right] - nums[minid]) <= limit ) {
            right++;
            continue;
        }

        //出现超出范围的情况,进行结算[left, right)
        //printf("FIND: left = %d, right = %d\n", left, right);
        max_len = fmax(max_len, right - left);

        //更新左边界
        while(left < right) {
            if(left != inc_que[iq_r] && left != dec_que[dq_r]) {
                left++;
                continue;
            }

            if(iq_size > 0 && left == inc_que[iq_r]) {
                iq_r++;
                iq_size--;
            } else if(dq_size > 0 && left == dec_que[dq_r]) {
                dq_r++;
                dq_size--;
            }
            left++;

            //判断是否满足要求
            minid = inc_que[iq_r];
            maxid = dec_que[dq_r];
            if(abs(nums[right] - nums[maxid]) <= limit && abs(nums[right] - nums[minid]) <= limit ) {
                //满足要求，则退出
                break;
            }

            continue;
        }

        //printf("ADJ: left = %d, right = %d\n", left, right);
        right++;
    }

    //处理尾部数据
    //printf("FIND: left = %d, right = %d\n", left, right);
    max_len = fmax(max_len, right - left);

    return max_len;
}

/*
问题就变成了，找到两个点，点 points[i] 的 y(i) - x(i) 和
点 points[j] 的 y(j) + x(j) 的和最大。限制条件是，x(i) <= x(j) 且最大相差 k。

yi + yj + |xi - xj| = yi + yj + xj - xi = (xj + yj) + (yi - xi) ，当j > x 时遍历xj， (xj + yj) 已
知， 因此求 满足 |xi - xj| <= k(其实就是一个固定长度的窗口) 窗
口内 (yi - xi)的最大值。滑动窗口的最大值 用单调队列。
*/


int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize, int k)
{

	int res = INT_MIN;

//q 维护滑动窗口内 yi - xi的最大值的下标
	int dqueue[pointsSize]; //array idx
	int head = 0;
	int rear = 0;

	for (int j = 0; j < pointsSize; j++) {
		//超出窗口长度的就 弹出
		while(rear > head && (points[j][0] - points[dqueue[head]][0] > k))
			head++;

		//计算当前窗口内的最大值
		if (rear > head) {
			res = fmax(res, points[j][0] + points[j][1] +
				points[dqueue[head]][1] - points[dqueue[head]][0]);
		}

		//维护递减队列，队首总是窗口内最大的 y-x 的下标
		while(rear > head && (points[j][1] - points[j][0] >
			points[dqueue[rear]][1] - points[dqueue[rear]][0])) {
			rear--;
		}

		dqueue[rear++] = j;
	}

	return res;
}
