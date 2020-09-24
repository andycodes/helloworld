/*
647. �����Ӵ�
�Ѷ��е�374
����һ���ַ�������������Ǽ�������ַ������ж��ٸ���
���Ӵ���
���в�ͬ��ʼλ�û����λ�õ��Ӵ�����ʹ������ͬ���ַ�
��ɣ�Ҳ�ᱻ������ͬ���Ӵ���

ʾ�� 1��
���룺"abc"
�����3
���ͣ����������Ӵ�: "a", "b", "c"
*/

/*
���������������졾ͨ����
˼·
�ڳ���Ϊ N ���ַ����У����ܵĻ��Ĵ�����λ���� 2N-1 ����
��ĸ����������ĸ�м䡣
��ÿһ�����Ĵ����Ŀ�ʼͳ�ƻ��Ĵ�������
�������� [a, b] ��ʾ S[a], S[a+1], ..., S[b] �ǻ��Ĵ���
���ݻ��Ĵ������֪ [a+1, b-1] Ҳ�ǻ������䡣
�㷨
����ÿ�����ܵĻ��Ĵ�����λ�ã�
�������������Ļ������� [left, right]��
�� left >= 0 and right < N and S[left] == S[right] ʱ��
�������䡣��ʱ���������ʾ�Ļ��Ĵ�Ϊ S[left], S[left+1], ..., S[right]��

*/
int countSubstrings(char * s)
{
	int size = strlen(s);
	int ans = 0;
	for (int center = 0; center < 2 * size -1; center++) {
		int left = center / 2;
		int right = left + center % 2;
		while(left >= 0 && right < size && s[left] == s[right]) {
			ans++;
			left--;
			right++;
		}
	}

	return ans;
}

/*
5. ������Ӵ�
����һ���ַ��� s���ҵ� s ����Ļ����Ӵ���
����Լ��� s ����󳤶�Ϊ 1000��

ʾ�� 1��

����: "babad"
���: "bab"
ע��: "aba" Ҳ��һ����Ч�𰸡�
ʾ�� 2��

����: "cbbd"
���: "bb"
*/
char * longestPalindrome(char * s)
{
	int slen = strlen(s);
	if (s == NULL || slen <= 1) {
		return s;
	}

	int max = 1;
	int save[2] = {0};
	for (int centor = 0; centor < 2 * slen - 1; centor++) {
		int left = centor / 2;
		int right = left + centor % 2;

		while(left >= 0 && right < slen && s[left] == s[right]) {
			if (right - left + 1 > max) {
				save[0] = left;
				save[1] = right;
				max = right - left + 1 ;
			}

			left--;
			right++;
		}
	}

	s[save[1]  + 1] = '\0';
	return s + save[0];
}


/*
457. ��������ѭ��
����һ�������������͸������Ļ������� nums�� ���ĳ����
���е��� k Ϊ����������ǰ�ƶ� k ���������෴������Ǹ�
�� (-k)��������ƶ� k ����������Ϊ�����ǻ��εģ����Կ���
�������һ��Ԫ�ص���һ��Ԫ���ǵ�һ��Ԫ�أ�����һ��Ԫ
�ص�ǰһ��Ԫ�������һ��Ԫ�ء�

ȷ�� nums ���Ƿ����ѭ���������ڣ���ѭ����������ͬ����
������ʼ�ͽ�������ѭ������ > 1�����⣬һ��ѭ���е�����
�˶�����������ͬһ������С����仰˵��һ��ѭ���в���
ͬʱ������ǰ���˶��������˶���


ʾ�� 1��

���룺[2,-1,1,2,2]
�����true
���ͣ�����ѭ���������� 0 -> 2 -> 3 -> 0 ��ѭ������Ϊ 3
*/
/*
����������Ҫһ�� visited ���飬����¼���ʹ�������Ȼ��
���Ǳ���ԭ���飬�����ǰ�����Ѿ����ʹ��ˣ�ֱ��������
������Ե�ǰλ������Ϊ��ʼ�㿪ʼ���ң����� while ѭ����
������һ��λ�ã����㷽���ǵ�ǰλ��������϶�Ӧ�����֣�
������ѭ�����飬���Խ�����ܻᳬ������ĳ��ȣ�������
��Ҫ�����鳤��ȡ�ࡣ��Ȼ���������Ҳ�����Ǹ���������
�Ժ����Ҳ�Ǹ�����������ȡ��֮ǰ�����ٲ���һ��n��ʹ��
��Ϊ���������� ���������Զ����n�Ļ���ȡ��֮ǰֻ����һ
��n�������ǲ����ģ�������ȷ�ķ�����Ӧ���ȶ�nȡ�࣬��
����n��Ϊ��ͬʱ�����������Ҳ�����������������ǵĴ���
�������ȶ�nȡ�࣬�ټ���n���ٶ�nȡ�࣬����������������
��������С��Σ������Գɹ�����ת��Ծ�ˡ�����ʱ������
�ϣ���� fast �� slow ��ȣ�˵����ʱ��һ�����ֵ�ѭ��������
�����⣬���о��Ǽ����ߵķ���������������ʾ forward��
���Ǹ�����ʾ backward����һ�� loop �б���ͬ����ͬ��������ֻ
Ҫ�ö�����ˣ��������Ǹ����Ļ���˵������ͬ��ֱ��
break ������ʱ��� fast �Ѿ���ӳ���ˣ�˵�������ҵ��˺Ϸ���
loop������ true��������һ��������ӳ�䣬�� fast λ���� visited
�����б�� true������ѭ����
*/
bool circularArrayLoop(int* nums, int numsSize)
{
	if (nums == NULL || numsSize <= 1)
		return false;

	bool visited[numsSize];
	memset(visited, 0, sizeof(visited));

	for(int slow = 0; slow < numsSize; slow++) {
		if(visited[slow])
			continue;

		visited[slow] = true;
		int map[5001];
		memset(map, 0, sizeof(map));
		while(true) {
			int fast = ((slow+nums[slow])%numsSize+numsSize)%numsSize;
			if(fast == slow||nums[fast]*nums[slow] < 0)
				break;
			if (map[fast] != 0)
				return true;
			map[slow] = 1;
			visited[fast] = true;
			slow = fast;
		}
	}

	return false;
}

