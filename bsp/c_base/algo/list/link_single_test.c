/*
��һ�� �ǿ� ����������ʾһ���Ǹ�������Ȼ�����������һ��

����Լ�������������� 0 ����û���κ�ǰ���� 0��

��������ĸ�����λ���� ��λ������ͷ������λ������β�� ��˳�����С�

ʾ��:

����: [1,2,3]
���: [1,2,4]

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
���һ���绰Ŀ¼����ϵͳ������֧�����¹��ܣ�

get: ������û�һ��δ��ʹ�õĵ绰���룬��ȡʧ���뷵�� -1
check: ���ָ���ĵ绰�����Ƿ�ʹ��
release: �ͷŵ�һ���绰���룬ʹ���ܹ����±�����
ʾ��:

// ��ʼ���绰Ŀ¼������ 3 ���绰���룺0��1 �� 2��
PhoneDirectory directory = new PhoneDirectory(3);

// ���Է�������δ����ĺ��룬�������Ǽ��������� 0��
directory.get();

// ���裬�������� 1��
directory.get();

// ���� 2 δ���䣬���Է���Ϊ true��
directory.check(2);

// ���� 2�������ֻʣһ������δ�����䡣
directory.get();

// ��ʱ������ 2 �Ѿ������䣬���Է��� false��
directory.check(2);

// �ͷź��� 2�����ú�����δ����״̬��
directory.release(2);

// ���� 2 ������δ����״̬�����Է��� true��
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
