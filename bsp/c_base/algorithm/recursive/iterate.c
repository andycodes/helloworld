
/*
void traverse(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
        // ���� arr[i]
    }
}
*/



/*
�����޵�ƽ���ϣ����������λ�� (0, 0) �����泯�����������˿��Խ�����������ָ��֮һ��

"G"��ֱ�� 1 ����λ
"L"����ת 90 ��
"R"����ת 90 ��
�����˰�˳��ִ��ָ�� instructions����һֱ�ظ����ǡ�

ֻ����ƽ���д��ڻ�ʹ�û�������Զ�޷��뿪ʱ������ true�����򣬷��� false��



ʾ�� 1��

���룺"GGLLGG"
�����true
���ͣ�
�����˴� (0,0) �ƶ��� (0,2)��ת 180 �ȣ�Ȼ��ص� (0,0)��
�ظ���Щָ������˽���������ԭ��Ϊ���ģ�2 Ϊ�뾶�Ļ��н����ƶ���

*/

/*
�ܼ򵥵�ԭ��
1�����յ���������һ�£��򷵻�true��
2�����յ㲻һ�£���ʱ�ж�������յ�ķ����ϵ��
��1����һ�£���һ�����������޴�ִ��ָ���ص�ԭ�㣬����true��
��2��һ�£�������Զ����㣬����false��

һ������һ�����⣬һ��ָ��֮��λ�ô�(0,0)����(x,y)����ʵ���԰�����ָ���һ��(0,0)->(x,y)
�������ڶ���ָ�����ô���أ��ܼ򵥣����(x,y)����(0,0)����ô�൱������λ��Ϊ0����Ȼ�ǻ�ȥ�ˣ�������������ֵ�һ�ֲ���λ�Ƶĳ��ȣ�������4��:
�����ʼ���������ϣ����ڱ����������ô����λ�Ƶķ�������ƫת���������������"GL"
������ڱ�����ң���������ƫת������GR"
������ڱ�����£�������ת180�ȣ�����"GRR"��ֱ����һ�ξ��߻�ȥ�ˣ����������������ܻ�ȥ
�������ڷ��������ϣ���ô�ͱ���λ�Ʒ��򲻱䣬�������������"GG"һ����һȥ������
���ԣ��ܶ���֮��һ��ָ��֮��ֻ��(x,y)����ԭ�㣬���ҷ����ԭ���ķ���һ�£����Żز�ȥ

*/

bool isRobotBounded(char* instructions) {
    //if (!(instructions.size() >= 1 && instructions.size() <= 100)) return false;
    int d = 0;  //�ĸ����� 0��1��2��3��  ��������Ϊ������ d+1��������ת d+3��������ת
    int dx[] = { 0, 1, 0, -1 };//�����ͷ����Ӧ
    int dy[] = { 1, 0, -1, 0 };
    int x = 0;
    int y = 0;

    for (unsigned int i = 0; i < strlen(instructions); i++) {
        switch (instructions[i]) {
        case 'R':
            d += 1;
            break;
        case 'L':
            d += 3; //����d-=1 ����Ϊ��d��ɸ�����ʱ��ȡmod�����
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
401. �������ֱ�
�������ֱ����� 4 �� LED ����Сʱ��0-11����
�ײ��� 6 �� LED ������ӣ�0-59����
ÿ�� LED ����һ�� 0 �� 1�����λ���Ҳࡣ

���磬����Ķ������ֱ��ȡ "3:25"��

����һ���Ǹ����� n ����ǰ LED ���ŵ�������
�������п��ܵ�ʱ�䡣

����:

����: n = 1
����: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
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
456. 132ģʽ
����һ���������У�a1, a2, ..., an��һ��132ģʽ��
������ ai, aj, ak ������Ϊ���� i < j < k ʱ��ai < ak < aj��
���һ���㷨���������� n �����ֵ�����ʱ��
��֤����������Ƿ���132ģʽ�������С�

ע�⣺n ��ֵС��15000��

ʾ��1:

����: [1, 2, 3, 4]

���: False

����: �����в�����132ģʽ�������С�

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


