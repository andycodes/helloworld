/*
1. ����֮��
�Ѷȼ�7810
����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ���� ���� ���������������ǵ������±ꡣ
����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ��㲻���ظ��������������ͬ����Ԫ�ء�
ʾ��:
���� nums = [2, 7, 11, 15], target = 9

��Ϊ nums[0] + nums[1] = 2 + 7 = 9
���Է��� [0, 1]

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

