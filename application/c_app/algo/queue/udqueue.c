/*
1438. ���Բ�������Ƶ������������
����һ���������� nums ����һ����ʾ���Ƶ����� limit�����㷵
�������������ĳ��ȣ����������е���������Ԫ��֮��
�ľ��Բ����С�ڻ��ߵ��� limit ��
������������������������飬�򷵻� 0 ��
ʾ�� 1��
���룺nums = [8,2,4,7], limit = 4
�����2
���ͣ��������������£�
[8] �����Բ� |8-8| = 0 <= 4.
[8,2] �����Բ� |8-2| = 6 > 4.
[8,2,4] �����Բ� |8-2| = 6 > 4.
[8,2,4,7] �����Բ� |8-2| = 6 > 4.
[2] �����Բ� |2-2| = 0 <= 4.
[2,4] �����Բ� |2-4| = 2 <= 4.
[2,4,7] �����Բ� |2-7| = 5 > 4.
[4] �����Բ� |4-4| = 0 <= 4.
[4,7] �����Բ� |4-7| = 3 <= 4.
[7] �����Բ� |7-7| = 0 <= 4.
��ˣ�����������������ĳ���Ϊ 2 ��
*/

#include <stdlib.h>
#include <stdio.h>

//���㷨˼·������ + �������С�
// 1.���������ݼ�¼�������Сֵ���ж��Ƿ��ڷ�Χ��
// 2.���������У���¼���ֵλ��
// 3.���������У���¼��Сֵλ��
// 4.����������ݳ�����Χ������н���
// 5.j��������ƶ���߽磬ֱ����Χ����Ҫ��
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

    //����Ԫ������
    inc_que[iq_w++] = 0;
    iq_size++;

    //����Ԫ������
    dec_que[dq_w++] = 0;
    dq_size++;

    int max_len = 1;

    int left = 0, right = 1;
    while(right < numsSize) {
        //��֦
        if(max_len >= numsSize - left) {
            break;
        }

        int minid = inc_que[iq_r];
        int maxid = dec_que[dq_r];
        int cur = nums[right];
        //printf("max = %d, min = %d\n", nums[maxid], nums[minid]);

        //�����������У���ǰ�������ڸ�ֵ������
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

        //�����½�����,��ǰ����С�ڸ�ֵ������
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

        //����ڷ�Χ֮��,���������
        if(abs(nums[right] - nums[maxid]) <= limit && abs(nums[right] - nums[minid]) <= limit ) {
            right++;
            continue;
        }

        //���ֳ�����Χ�����,���н���[left, right)
        //printf("FIND: left = %d, right = %d\n", left, right);
        max_len = fmax(max_len, right - left);

        //������߽�
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

            //�ж��Ƿ�����Ҫ��
            minid = inc_que[iq_r];
            maxid = dec_que[dq_r];
            if(abs(nums[right] - nums[maxid]) <= limit && abs(nums[right] - nums[minid]) <= limit ) {
                //����Ҫ�����˳�
                break;
            }

            continue;
        }

        //printf("ADJ: left = %d, right = %d\n", left, right);
        right++;
    }

    //����β������
    //printf("FIND: left = %d, right = %d\n", left, right);
    max_len = fmax(max_len, right - left);

    return max_len;
}

/*
����ͱ���ˣ��ҵ������㣬�� points[i] �� y(i) - x(i) ��
�� points[j] �� y(j) + x(j) �ĺ�������������ǣ�x(i) <= x(j) �������� k��

yi + yj + |xi - xj| = yi + yj + xj - xi = (xj + yj) + (yi - xi) ����j > x ʱ����xj�� (xj + yj) ��
֪�� ����� ���� |xi - xj| <= k(��ʵ����һ���̶����ȵĴ���) ��
���� (yi - xi)�����ֵ���������ڵ����ֵ �õ������С�
*/


int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize, int k)
{

	int res = INT_MIN;

//q ά������������ yi - xi�����ֵ���±�
	int dqueue[pointsSize]; //array idx
	int head = 0;
	int rear = 0;

	for (int j = 0; j < pointsSize; j++) {
		//�������ڳ��ȵľ� ����
		while(rear > head && (points[j][0] - points[dqueue[head]][0] > k))
			head++;

		//���㵱ǰ�����ڵ����ֵ
		if (rear > head) {
			res = fmax(res, points[j][0] + points[j][1] +
				points[dqueue[head]][1] - points[dqueue[head]][0]);
		}

		//ά���ݼ����У��������Ǵ��������� y-x ���±�
		while(rear > head && (points[j][1] - points[j][0] >
			points[dqueue[rear]][1] - points[dqueue[rear]][0])) {
			rear--;
		}

		dqueue[rear++] = j;
	}

	return res;
}
