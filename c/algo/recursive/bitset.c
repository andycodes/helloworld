
int hammingWeight(unsigned int n)
{
    int sum = 0;
    while (n != 0) {
        sum++;
        n &= (n - 1);
    }
    return sum;
}



/*
������ö��:�����Ӽ�
����N��Ԫ�صļ��ϵ�һ���Ӽ��ĸ���Ϊ 2^n

	for (int i = 0; i < (1 << numsSize); i++) {  i Ϊ �����Ӽ�����״̬
		for (int j = 0; j < numsSize; j++) {//�����Ӽ�״̬�Ķ����Ƶ�ÿһλ
			if ((i & (1 << j)) != 0) { //Ϊ�棬ѡȡԭʼ�����еĳ�Ա
					A[j]
			}
		}

	}

*/


/*
1239. �����ַ�������󳤶�
�Ѷ��е�34
����һ���ַ������� arr���ַ��� s �ǽ� arr ĳһ�������ַ���
�������õ��ַ�������� s �е�ÿһ���ַ���ֻ���ֹ�һ�Σ�
��ô������һ�����н⡣
�뷵�����п��н� s ������ȡ�
ʾ�� 1��
���룺arr = ["un","iq","ue"]
�����4
���ͣ����п��ܵĴ�������� "","un","iq","ue","uniq" �� "ique"��
��󳤶�Ϊ 4��
ʾ�� 2��
���룺arr = ["cha","r","act","ers"]
�����6
���ͣ����ܵĽ���� "chaers" �� "acters"��
ʾ�� 3��
���룺arr = ["abcdefghijklmnopqrstuvwxyz"]
�����26
*/

/*
˼·����
����ÿ�������޷Ǿ����������ѡ���ⲻѡ��
���� arr �е�ÿ����������һ��������λ����ʾ����
Ϊ 1 ��ʾѡ��������ʣ�Ϊ 0 ��ʾ��ѡ��������ʡ�
��Ŀ���� 1 <= arr.length <= 16����һ�� int(38λ)���㹻��ʾ arr �е�
���е��ʡ�
���� arr ���� 5 �����ʣ����� int i; ��ö�ٶ� arr ������ѡ�������
�� i = 0; ʱ��i ������λ��Ϊ 0 ����ʾ������ǣ� arr �еĵ��ʶ���
ѡ��
�� i = (1 << 5) - 1 ʱ��i ��ǰ 5 λ��Ϊ 1����ʾ������ǣ�arr�еĵ���
��ѡ��
������ѡ������Ϳ�������ö�٣�
for (int i = 0; i < (1 << 5); i++) {
    // �õ���ÿ�� i �����Ա�ʾһ��ѡ�����
}
���� i ��ʾ���������ô֪��ĳ������ word ��ѡȡ״̬��
word �� arr �е����� j �ͱ�ʾ���� i �ĵڼ�λ��ʹ�� i & (1 << j) ��֪��
word ��ѡȡ״̬��
�� i & (1 << j) Ϊ 1 ʱ����ʾ word ��״̬Ϊѡ��
�� i & (1 << j) Ϊ 0 ʱ����ʾ word ��״̬Ϊ��ѡ��
ͬʱ������ʹ��λ��������ʾ�ַ����� 26 ��Ӣ��Сд��ĸ��
����������ڴ������� int m; �е� 26 λ������ʾ 26 ��Ӣ�ĵĳ�
��״̬��
*/

bool isUnique(char * str, int *bitmap)
{
	int i = 0;
	while(str[i] != '\0') {
		if (*bitmap & (1 << (str[i] - 'a'))) {
			return false;
		}

		*bitmap |= (1 << (str[i] - 'a'));
		i++;
	}

	return true;
}

int maxLength(char ** arr, int arrSize)
{
	if (arr == NULL || arrSize <= 0) {
		return 0;
	}

	if (arr != NULL && arrSize == 1) {
		return strlen(arr[0]);
	}

	int ans = 0;
	for (int i = 0; i < (1 << arrSize); i++) {
		int sum = 0;
		int bitmap = 0;
		for (int j = 0; j < arrSize; j++) {
			if ((i & (1 << j)) && isUnique(arr[j], &bitmap)) {
				sum += strlen(arr[j]);
			}
		}
		ans = fmax(ans, sum);
	}

	return ans;
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
char ** readBinaryWatch(int num, int* returnSize)
{
	char **res = (char **)calloc(1024, sizeof(char *));
	*returnSize = 0;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 60; j++) {
			if (hammingWeight(i) + hammingWeight(j) == num) {
				res[*returnSize] = (char *)calloc(6, sizeof(char));
				sprintf(res[*returnSize], "%d%02d", i, j);
				(*returnSize)++;
			}
		}
	}

	return res;
}


