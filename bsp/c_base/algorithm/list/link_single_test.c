/*
用一个 非空 单链表来表示一个非负整数，然后将这个整数加一。

你可以假设这个整数除了 0 本身，没有任何前导的 0。

这个整数的各个数位按照 高位在链表头部、低位在链表尾部 的顺序排列。

示例:

输入: [1,2,3]
输出: [1,2,4]

*/
int Plus(struct ListNode* head){
    if (head->next == NULL || Plus(head->next) == 1) {
        head->val++;
        if (head->val == 10) {
            head->val -= 10;
            return 1;
        }
    }
    return 0;
}
struct ListNode* plusOne(struct ListNode* head){
    if (head == NULL) {
        return head;
    }
    if (Plus(head) == 1) {
        struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = 1;
        node->next = head;
        head = node;
     }
     return head;
}

/*
设计一个电话目录管理系统，让它支持以下功能：

get: 分配给用户一个未被使用的电话号码，获取失败请返回 -1
check: 检查指定的电话号码是否被使用
release: 释放掉一个电话号码，使其能够重新被分配
示例:

// 初始化电话目录，包括 3 个电话号码：0，1 和 2。
PhoneDirectory directory = new PhoneDirectory(3);

// 可以返回任意未分配的号码，这里我们假设它返回 0。
directory.get();

// 假设，函数返回 1。
directory.get();

// 号码 2 未分配，所以返回为 true。
directory.check(2);

// 返回 2，分配后，只剩一个号码未被分配。
directory.get();

// 此时，号码 2 已经被分配，所以返回 false。
directory.check(2);

// 释放号码 2，将该号码变回未分配状态。
directory.release(2);

// 号码 2 现在是未分配状态，所以返回 true。
directory.check(2);
*/
typedef struct {
	MyLinkedList *head;
	int maxNumbers;
} PhoneDirectory;

/** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */


void phoneDirectoryRelease(PhoneDirectory* obj, int number);
PhoneDirectory* phoneDirectoryCreate(int maxNumbers) {

	PhoneDirectory* pD = (PhoneDirectory*)malloc(sizeof(PhoneDirectory));
	if (pD == NULL) {
		return NULL;
	}

	pD->head = link_single_init_head();

	for (int i = 0; i < maxNumbers; i++) {
		phoneDirectoryRelease(pD,i);
	}

	pD->maxNumbers = maxNumbers;

	return pD;
}

/** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
int phoneDirectoryGet(PhoneDirectory* obj) {
	int res = -1;

	if (obj == NULL)
		return res;

	if (obj->head == NULL)
		return res;

	if (obj->head->next != NULL) {
		res = obj->head->next->val;
		link_single_del_node(obj->head, obj->head->next);
	}

	return res;
}


/** Check if a number is available or not. */
bool phoneDirectoryCheck(PhoneDirectory* obj, int number) {
	if (obj == NULL)
		return false;
	MyLinkedList *tmp = obj->head->next;
	while(tmp != NULL) {
		if (tmp->val == number)
			return true;
		tmp = tmp->next;
	}

	return false;
}

void phoneDirectoryRelease(PhoneDirectory* obj, int number) {
	if (obj == NULL)
		return ;

	bool b = phoneDirectoryCheck(obj, number);

	if(b == false)
		link_single_push_new_tail(obj->head,number);
}

void phoneDirectoryFree(PhoneDirectory* obj) {
	if (obj == NULL)
		return ;

	free(obj);
	obj = NULL;
}
