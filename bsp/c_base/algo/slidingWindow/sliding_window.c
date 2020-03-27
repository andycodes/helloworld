/*
滑动窗口思想：
①）窗口由两个指针构成，一个左指针left，一个右指针right，然后[left,right]表示的索引范围是一个窗口了。

②）右指针right的功能是用来扩展窗口：当窗口内的条件没有达到题目要求时，我们需要不断移动右指针right直到窗口内的条件第一次满足题目要求为止。

③）左指针left的功能是用来缩小窗口的：当窗口内的条件已满足题目条件或多于题目条件时（窗口溢出），我们缩小窗口，也就是左指针left需要右移直到窗口条件不满足为止。这时，我们需要记录当前窗口的大小，并更新目前为止满足条件的最小窗口记录。之后，再次扩展右指针right，使得窗口满足题目的条件。

注：滑动窗口用来处理连续满足一定条件的连续区间的性质（长度等）问题的，两个指针都起始于原点，并一前一后向终点前进。

窗口扩张：left不变，right++
窗口滑动：left++, right++
*/



/*
面试题59 - II. 队列的最大值
请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1

示例 1：

输入:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出: [null,null,null,2,1,2]
示例 2：

输入:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出: [null,-1,-1]

*/

/*
我们维护一个正常的队列queue，这样push_back, pop_front 直接操作正常队列即可。

问题在于如何在O(1)O(1) 时间 实现max_value? 我们的想法是维护一个递减的双端队列deque。

每次queue入队列的时候，我们deque也入队列，入队列之前我们清除队尾的比入队的元素小的元素。 一句话来说，我们的目的就是维持 deque保持递减性质不变
每次queue pop的时候，我们的deque不一定也要出队列。当且仅当deque的队首元素和queue队首元素一致时候，我们才需要执行deque的出队列的操作
这样max_value我们只需要返回deque的队首元素即可，至此我们终于实现了$O(1)$ 时间 实现max_value

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
面试题48. 最长不含重复字符的子字符串
难度中等6
请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

示例 1:
输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

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
1004. 最大连续1的个数 III
难度中等41
给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。
返回仅包含 1 的最长（连续）子数组的长度。

示例 1：
输入：A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释：
[1,1,1,0,0,1,1,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 6。


*/

int longestOnes(int* A, int ASize, int K)
{
	//cnt用来统计窗口中0的个数
	int left=0,right=0, cnt=0,res=0,size=ASize;
	while(right < size) {
		cnt += (A[right] == 0);
		while (cnt > K) {////当窗口内0的个数大于K时，需要缩小窗口
			cnt -= (A[left] == 0);
			left++;
		}
		////窗口内0的个数小于等于k时，也就是可以该窗口内的0都可以替换，根据该窗口长度来确定是否更新res
		res = fmax(res, right-left+1);
		right++;
	}

	return res;
}

/*
424. 替换后的最长重复字符
难度中等73
给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。
注意:
字符串长度 和 k 不会超过 104。
示例 1:
输入:
s = "ABAB", k = 2

输出:
4

解释:
用两个'A'替换为两个'B',反之亦然。

*/
/*
建立26个大写字母的映射，用于记录窗口中字符出现的次数，将A存到数组的0号下标的位置
初始窗口指针left，right都为0，移动right，增大窗口，同时更新当前最长重复字符的长度。直到窗口长度过长，即不能通过替换k次形成重复字符时，收缩窗口(此时可以通过k+1次替换满足)，left++。但是这里可以不必更新max_count，因为当我们找到max_count之后，就一定能找到一个长度为d的区间使得max_count + k = d。我们只需要算出这个满足条件的d即可(这里通过right-left+1计算)。
一直更新当前最长重复字符的长度，直到right指针遍历完字符串s

# 用字典保存字母出现的次数，需要替换的字符数目＝窗口字符数目－数量最多的字符数目

用数组记录下当前窗口各个字母的总数和当前窗口中出现次数最多的字母的数量
当：窗口大小 > (最大字母数-k)时扩张移动窗口，否则扩张窗口
当窗口移动到字符串末端后结束，答案为最后窗口的大小

（1）滑动窗口思路，一般大家都能想到；
（2）窗口内所有字符的个数减去最多字符的个数如果小于等于k，即替换后肯定满足条件，我们可以再将滑动窗口的右边界往右移动一下，这是本问题的关键；


假设我们用来替换别的字符的那个字符是c，那么题目可以转变成这样一个问题，在一个window里面，最多有k个不为c的字符，这样才是满足条件的

那么这样的字符c有哪些呢？毫无疑问是set(s)里面的这些字符。

然后我们维护一个window，不断计算不为c的字符的个数counter，如果counter大于n了说明我们怎么替换也不行了，我们就要将start往前挪一格，否则一直挪end。
每次挪完end之后都要记得更新这一轮的最大长度

每个字符c循环后都要更新最终res。

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
		max = fmax(max, le[idx]);//当前窗口内的最多字符的个数
		if (right - left + 1 -max > k) {//需要替换的字符个数就是当前窗口的大小减去窗口中数量最多的字符的数量
			le[s[left] - 'A']--;//缩小窗口
			left++;
		}
		ans = fmax(ans, right-left+1);//当窗口内可替换的字符数小于等于k时，我们需要根据该窗口长度来确定是否更新result
		right++;
	}

	return ans;
}
/*
面试题 17.18. 最短超串
难度中等5
假设你有两个数组，一个长一个短，短的元素均不相同。找到长数组中包含短数组所有的元素的最短子数组，其出现顺序无关紧要。
返回最短子数组的左端点和右端点，如有多个满足条件的子数组，返回左端点最小的一个。若不存在，返回空数组。
示例 1:
输入:
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
输出: [7,10]
示例 2:
输入:
big = [1,2,3]
small = [4]
输出: []

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

