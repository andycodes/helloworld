/*
1. 两数之和
难度简单7810
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
示例:
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

*/
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	HashMap *hashmap = hashmap_init(numsSize, hashcode_int, hashequal_int);
	int* res = (int *)calloc(2, sizeof(int));

	for (int i = 0; i < numsSize; i++) {
		int diff = target - nums[i];
		DataType entry;
		entry.key = diff;
		hashmap_getValue(hashmap, &entry);
		if (entry.id == -1) {
			DataType push;
			push.key = nums[i];
			push.val = i;
			hashmap_push(hashmap, push);
		} else {
				*returnSize = 2;
				res[0] = i;
				res[1] = entry.val;
				break;
		}
	}

	return res;
}

