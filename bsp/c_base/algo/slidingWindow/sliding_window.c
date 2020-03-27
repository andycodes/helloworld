/*
��������˼�룺
�٣�����������ָ�빹�ɣ�һ����ָ��left��һ����ָ��right��Ȼ��[left,right]��ʾ��������Χ��һ�������ˡ�

�ڣ���ָ��right�Ĺ�����������չ���ڣ��������ڵ�����û�дﵽ��ĿҪ��ʱ��������Ҫ�����ƶ���ָ��rightֱ�������ڵ�������һ��������ĿҪ��Ϊֹ��

�ۣ���ָ��left�Ĺ�����������С���ڵģ��������ڵ�������������Ŀ�����������Ŀ����ʱ�������������������С���ڣ�Ҳ������ָ��left��Ҫ����ֱ����������������Ϊֹ����ʱ��������Ҫ��¼��ǰ���ڵĴ�С��������ĿǰΪֹ������������С���ڼ�¼��֮���ٴ���չ��ָ��right��ʹ�ô���������Ŀ��������

ע��������������������������һ��������������������ʣ����ȵȣ�����ģ�����ָ�붼��ʼ��ԭ�㣬��һǰһ�����յ�ǰ����

�������ţ�left���䣬right++
���ڻ�����left++, right++
*/



/*
������59 - II. ���е����ֵ
�붨��һ�����в�ʵ�ֺ��� max_value �õ�����������ֵ��Ҫ����max_value��push_back �� pop_front ��ʱ�临�Ӷȶ���O(1)��

������Ϊ�գ�pop_front �� max_value ��Ҫ���� -1

ʾ�� 1��

����:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
���: [null,null,null,2,1,2]
ʾ�� 2��

����:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
���: [null,-1,-1]

*/

/*
����ά��һ�������Ķ���queue������push_back, pop_front ֱ�Ӳ����������м��ɡ�

�������������O(1)O(1) ʱ�� ʵ��max_value? ���ǵ��뷨��ά��һ���ݼ���˫�˶���deque��

ÿ��queue����е�ʱ������dequeҲ����У������֮ǰ���������β�ı���ӵ�Ԫ��С��Ԫ�ء� һ�仰��˵�����ǵ�Ŀ�ľ���ά�� deque���ֵݼ����ʲ���
ÿ��queue pop��ʱ�����ǵ�deque��һ��ҲҪ�����С����ҽ���deque�Ķ���Ԫ�غ�queue����Ԫ��һ��ʱ�����ǲ���Ҫִ��deque�ĳ����еĲ���
����max_value����ֻ��Ҫ����deque�Ķ���Ԫ�ؼ��ɣ�������������ʵ����$O(1)$ ʱ�� ʵ��max_value

*/
typedef struct {
	struct ListNode *head;
	struct ListNode *mhead;
} MaxQueue;

MaxQueue* maxQueueCreate() {
	MaxQueue * queue = (MaxQueue *)malloc(sizeof(MaxQueue));
	queue->head = slink_init();
	queue->mhead = slink_init();
	return queue;
}

int maxQueueMax_value(MaxQueue* obj) {
	if(slink_empty(obj->mhead))
		return -1;

	return slink_get_first(obj->mhead);
}

void maxQueuePush_back(MaxQueue* obj, int value) {
	slink_push_last(obj->head, value);
	while(!slink_empty(obj->mhead) && value > slink_get_last(obj->mhead)) {
		slink_pop_last(obj->mhead);
	}

	slink_push_last(obj->mhead, value);
}

int maxQueuePop_front(MaxQueue* obj) {
	if (slink_empty(obj->head))
		return -1;
	int ret = slink_pop_first(obj->head);
	if (ret == slink_get_first(obj->mhead)) {
		slink_pop_first(obj->mhead);
	}

	return ret;
}

void maxQueueFree(MaxQueue* obj) {
	free(obj->head);
	free(obj->mhead);
	free(obj);
}

/*
������48. ������ظ��ַ������ַ���
�Ѷ��е�6
����ַ������ҳ�һ����Ĳ������ظ��ַ������ַ��������������ַ����ĳ��ȡ�

ʾ�� 1:
����: "abcabcbb"
���: 3
����: ��Ϊ���ظ��ַ�����Ӵ��� "abc"�������䳤��Ϊ 3��
ʾ�� 2:
����: "bbbbb"
���: 1
����: ��Ϊ���ظ��ַ�����Ӵ��� "b"�������䳤��Ϊ 1��
ʾ�� 3:
����: "pwwkew"
���: 3
����: ��Ϊ���ظ��ַ�����Ӵ��� "wke"�������䳤��Ϊ 3��
     ��ע�⣬��Ĵ𰸱����� �Ӵ� �ĳ��ȣ�"pwke" ��һ�������У������Ӵ���

*/

int lengthOfLongestSubstring(char* s)
{
	if (s == NULL || strlen(s) == 0)
		return 0;
	if (strlen(s) == 1)
		return 1;

	struct ListNode* slink = slink_init();

	int max = 0;
	int left = 0;
	int right = 0;
	while(right < strlen(s)) {
		while(slink_get_idx_by_val(slink, s[right])  != -1) {
			slink_pop_first(slink);
			left++;
		}

		slink_push_last(slink, s[right]);
		right++;
		max = fmax(right - left, max);
	}

	return max;
}



/*
1004. �������1�ĸ��� III
�Ѷ��е�41
����һ�������� 0 �� 1 ��ɵ����� A�����������Խ� K ��ֵ�� 0 ��� 1 ��
���ؽ����� 1 �����������������ĳ��ȡ�

ʾ�� 1��
���룺A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
�����6
���ͣ�
[1,1,1,0,0,1,1,1,1,1,1]
�������ִ� 0 ��ת�� 1����������鳤��Ϊ 6��


*/

int longestOnes(int* A, int ASize, int K)
{
	//cnt����ͳ�ƴ�����0�ĸ���
	int left=0,right=0, cnt=0,res=0,size=ASize;
	while(right < size) {
		cnt += (A[right] == 0);
		while (cnt > K) {////��������0�ĸ�������Kʱ����Ҫ��С����
			cnt -= (A[left] == 0);
			left++;
		}
		////������0�ĸ���С�ڵ���kʱ��Ҳ���ǿ��Ըô����ڵ�0�������滻�����ݸô��ڳ�����ȷ���Ƿ����res
		res = fmax(res, right-left+1);
		right++;
	}

	return res;
}

/*
424. �滻�����ظ��ַ�
�Ѷ��е�73
����һ�����ɴ�дӢ����ĸ��ɵ��ַ���������Խ�����λ���ϵ��ַ��滻��������ַ����ܹ�������滻 k �Ρ���ִ�������������ҵ������ظ���ĸ����Ӵ��ĳ��ȡ�
ע��:
�ַ������� �� k ���ᳬ�� 104��
ʾ�� 1:
����:
s = "ABAB", k = 2

���:
4

����:
������'A'�滻Ϊ����'B',��֮��Ȼ��

*/
/*
����26����д��ĸ��ӳ�䣬���ڼ�¼�������ַ����ֵĴ�������A�浽�����0���±��λ��
��ʼ����ָ��left��right��Ϊ0���ƶ�right�����󴰿ڣ�ͬʱ���µ�ǰ��ظ��ַ��ĳ��ȡ�ֱ�����ڳ��ȹ�����������ͨ���滻k���γ��ظ��ַ�ʱ����������(��ʱ����ͨ��k+1���滻����)��left++������������Բ��ظ���max_count����Ϊ�������ҵ�max_count֮�󣬾�һ�����ҵ�һ������Ϊd������ʹ��max_count + k = d������ֻ��Ҫ����������������d����(����ͨ��right-left+1����)��
һֱ���µ�ǰ��ظ��ַ��ĳ��ȣ�ֱ��rightָ��������ַ���s

# ���ֵ䱣����ĸ���ֵĴ�������Ҫ�滻���ַ���Ŀ�������ַ���Ŀ�����������ַ���Ŀ

�������¼�µ�ǰ���ڸ�����ĸ�������͵�ǰ�����г��ִ���������ĸ������
�������ڴ�С > (�����ĸ��-k)ʱ�����ƶ����ڣ��������Ŵ���
�������ƶ����ַ���ĩ�˺��������Ϊ��󴰿ڵĴ�С

��1����������˼·��һ���Ҷ����뵽��
��2�������������ַ��ĸ�����ȥ����ַ��ĸ������С�ڵ���k�����滻��϶��������������ǿ����ٽ��������ڵ��ұ߽������ƶ�һ�£����Ǳ�����Ĺؼ���


�������������滻����ַ����Ǹ��ַ���c����ô��Ŀ����ת�������һ�����⣬��һ��window���棬�����k����Ϊc���ַ���������������������

��ô�������ַ�c����Щ�أ�����������set(s)�������Щ�ַ���

Ȼ������ά��һ��window�����ϼ��㲻Ϊc���ַ��ĸ���counter�����counter����n��˵��������ô�滻Ҳ�����ˣ����Ǿ�Ҫ��start��ǰŲһ�񣬷���һֱŲend��
ÿ��Ų��end֮��Ҫ�ǵø�����һ�ֵ���󳤶�

ÿ���ַ�cѭ����Ҫ��������res��

*/
int characterReplacement(char * s, int k){
	int left = 0;
	int right = 0;
	int max = 0;
	int ans = 0;
	int le[26] = {{0}};

	while(right < strlen(s)) {
		int idx = s[right] - 'A';
		le[idx]++;
		max = fmax(max, le[idx]);//��ǰ�����ڵ�����ַ��ĸ���
		if (right - left + 1 -max > k) {//��Ҫ�滻���ַ��������ǵ�ǰ���ڵĴ�С��ȥ���������������ַ�������
			le[s[left] - 'A']--;//��С����
			left++;
		}
		ans = fmax(ans, right-left+1);//�������ڿ��滻���ַ���С�ڵ���kʱ��������Ҫ���ݸô��ڳ�����ȷ���Ƿ����result
		right++;
	}

	return ans;
}
/*
������ 17.18. ��̳���
�Ѷ��е�5
���������������飬һ����һ���̣��̵�Ԫ�ؾ�����ͬ���ҵ��������а������������е�Ԫ�ص���������飬�����˳���޹ؽ�Ҫ��
����������������˵���Ҷ˵㣬���ж�����������������飬������˵���С��һ�����������ڣ����ؿ����顣
ʾ�� 1:
����:
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
���: [7,10]
ʾ�� 2:
����:
big = [1,2,3]
small = [4]
���: []

*/
int* shortestSeq(int* big, int bigSize, int* small, int smallSize, int* returnSize)
{
	if (big == NULL || small == NULL || bigSize <= 0 || smallSize <= 0 || smallSize > bigSize) {
		*returnSize = 0;
		return NULL;
	}

	struct HashTable ht;
	int ret = HashInit(&ht, smallSize, hashequal_int, hashcode_int);

	for (int i = 0; i < smallSize; i++) {
		hashPushKey(&ht, small[i]);
	}

	int left = 0, right = 0, count = 0, minLen= INT_MAX;
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	while(right < bigSize) {
		struct DataEntry *curEntry = hashFindKey(&ht, big[right]);
		if(curEntry != NULL) {
			if (curEntry->value == 0) {
				count++;
			}

			curEntry->value++;
		}

		while(count == smallSize) {
			struct DataEntry *entry;
			entry = hashFindKey(&ht, big[left]);
			if (entry == NULL) {
				left++;
			} else if (entry->value > 1) {
				left++;
				entry->value--;
			} else {//value == 1
				if (minLen > right-left + 1) {
					minLen = right-left + 1;
					res[0] = left;
					res[1] = right;
				}

				entry->value--;
				left++;
				count--;
			}
		}

		right++;
	}

	if (minLen == INT_MAX) {
		*returnSize = 0;
		return NULL;
	}

	return res;
}

