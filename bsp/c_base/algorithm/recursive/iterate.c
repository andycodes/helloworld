
/*
void traverse(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
        // 访问 arr[i]
    }
}
*/



/*
在无限的平面上，机器人最初位于 (0, 0) 处，面朝北方。机器人可以接受下列三条指令之一：

"G"：直走 1 个单位
"L"：左转 90 度
"R"：右转 90 度
机器人按顺序执行指令 instructions，并一直重复它们。

只有在平面中存在环使得机器人永远无法离开时，返回 true。否则，返回 false。



示例 1：

输入："GGLLGG"
输出：true
解释：
机器人从 (0,0) 移动到 (0,2)，转 180 度，然后回到 (0,0)。
重复这些指令，机器人将保持在以原点为中心，2 为半径的环中进行移动。

*/

/*
很简单的原理：
1、若终点和起点坐标一致，则返回true；
2、若终点不一致，此时判断起点与终点的方向关系：
（1）不一致，则一定可以在有限次执行指令后回到原点，返回true；
（2）一致，则无限远离起点，返回false；

一起来简化一下问题，一顿指令之后，位置从(0,0)到了(x,y)，其实可以把整个指令看成一步(0,0)->(x,y)
接下来第二次指令会怎么走呢，很简单，如果(x,y)等于(0,0)，那么相当于整体位移为0，自然是回去了，其余情况，保持第一轮操作位移的长度，方向有4种:
如果初始方向是向上，现在变成了向左，那么整体位移的方向向左偏转，就像例子里面的"GL"
如果现在变成向右，整体向右偏转，就像GR"
如果现在变成向下，整体旋转180度，就像"GRR"，直接下一次就走回去了，这三种情况，最后都能回去
而当现在方向变成向上，那么就保持位移方向不变，就像例子里面的"GG"一样，一去不复返
所以，总而言之，一次指令之后，只有(x,y)不是原点，并且方向和原来的方向一致，最后才回不去

*/

bool isRobotBounded(char* instructions) {
    //if (!(instructions.size() >= 1 && instructions.size() <= 100)) return false;
    int d = 0;  //四个方向 0上1右2下3左  这样定是为了满足 d+1就是向左转 d+3就是向右转
    int dx[] = { 0, 1, 0, -1 };//索引和方向对应
    int dy[] = { 1, 0, -1, 0 };
    int x = 0;
    int y = 0;

    for (unsigned int i = 0; i < strlen(instructions); i++) {
        switch (instructions[i]) {
        case 'R':
            d += 1;
            break;
        case 'L':
            d += 3; //不用d-=1 是因为当d变成负数的时候，取mod会出错
            break;
        case 'G':
            d = d % 4;
            x = x + dx[d];
            y = y + dy[d];
            break;
        }
    }
    return ((x == 0 && y == 0) || d % 4 != 0);

}


/*
401. 二进制手表
二进制手表顶部有 4 个 LED 代表小时（0-11），
底部的 6 个 LED 代表分钟（0-59）。
每个 LED 代表一个 0 或 1，最低位在右侧。

例如，上面的二进制手表读取 "3:25"。

给定一个非负整数 n 代表当前 LED 亮着的数量，
返回所有可能的时间。

案例:

输入: n = 1
返回: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** readBinaryWatch(int num, int* returnSize){
/*calloc,malloc,alloc*/
	char **res = (char **)calloc(1024, sizeof(char *));
	int resSize = 0;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 60; j++) {
			if (num == hammingWeight(i) + hammingWeight(j)) {
				res[resSize] = (char *)calloc(10, sizeof(char));
				sprintf(res[resSize],"%d:%02d",i,j);
				resSize++;
			}
		}
	}

	*returnSize = resSize;
	return res;
}

/*
456. 132模式
给定一个整数序列：a1, a2, ..., an，一个132模式的
子序列 ai, aj, ak 被定义为：当 i < j < k 时，ai < ak < aj。
设计一个算法，当给定有 n 个数字的序列时，
验证这个序列中是否含有132模式的子序列。

注意：n 的值小于15000。

示例1:

输入: [1, 2, 3, 4]

输出: False

解释: 序列中不存在132模式的子序列。

*/

bool find132pattern(int* nums, int numsSize) {

    if (nums == NULL || numsSize < 3 || numsSize >= 15000)
        return false;

	int min[numsSize];

	min[0] = nums[0];
	for (int i = 1; i < numsSize; i++) {
		min[i] = fmin(min[i - 1], nums[i]);
	}

	for (int j = 1; j < numsSize; j++) {
		if (min[j] >=  nums[j])
			continue;
		for (int k = j + 1; k < numsSize; k++) {
			if (min[j] < nums[k] && nums[k] < nums[j]) {
				return true;
			}
		}
	}

	return false;
}


bool find132pattern(int* nums, int numsSize){

	if (nums == NULL || numsSize <= 0 || numsSize >= 15000)
		return false;

	int min = nums[0];

	for (int j = 1; j < numsSize; j++) {
		if (nums[j] > min) {
			for (int k = j + 1; k < numsSize; k++) {
				if (min < nums[k] && nums[k] < nums[j]) {
					return true;
				}
			}
		} else {
			min = nums[j];
		}
	}

	return false;
}


