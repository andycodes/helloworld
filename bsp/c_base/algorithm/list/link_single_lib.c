typedef  struct ListNode {
      int val;
      struct ListNode *next;
}MyLinkedList;


/*
��������������ϲ�Ϊһ���µ������������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�?

ʾ����

���룺1->2->4, 1->3->4
�����1->1->2->3->4->4
*/

/*
���� 1���ݹ�
�뷨

���ǿ������µݹ�ض���������������� merge ���������Ա߽���������������ȣ���

\left\{ \begin{array}{ll} list1[0] + merge(list1[1:], list2) & list1[0] < list2[0] \\ list2[0] + merge(list1, list2[1:]) & otherwise \end{array} \right.
{
list1[0]+merge(list1[1:],list2)
list2[0]+merge(list1,list2[1:])
?

list1[0]<list2[0]
otherwise
?


Ҳ����˵����������ͷ����С��һ����ʣ��Ԫ�ص� merge ��������ϲ���

�㷨
����ֱ�ӽ����ϵݹ���̽�ģ�����ȿ��Ǳ߽������
����ģ���� l1 ���� l2 һ��ʼ���� null ����ôû���κβ�����Ҫ�ϲ�����������ֻ��Ҫ���طǿ�������������Ҫ�ж� l1 �� l2 ��һ����ͷԪ�ظ�С��Ȼ��ݹ�ؾ�����һ����ӵ�������ֵ��������������ǿյģ���ô������ֹ�����Եݹ��������һ������ֹ��

*/

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
        if (l1 == NULL) {
            return l2;
        }
        else if (l2 == NULL) {
            return l1;
        }
        else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
}


/*
����һ�������ж��������Ƿ��л���

Ϊ�˱�ʾ���������еĻ���
����ʹ������ pos ����ʾ����β���ӵ���
���е�λ�ã������� 0 ��ʼ����
��� pos �� -1�����ڸ�������û�л���
*/
bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    struct ListNode *slow = head;
    struct ListNode *fast = head->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}


/** Initialize your data structure here. */
MyLinkedList* myLinkedListCreate() {
    MyLinkedList* head = malloc(sizeof(MyLinkedList));
    head->next = NULL;
    return head;
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) {
    int i = 0;
    MyLinkedList* entry = obj;

    while(entry->next != NULL){
        if(i++ == index){
            return entry->next->val;
        }
        entry = entry->next;
    }
    return -1;
}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    MyLinkedList* tmp = obj;

    MyLinkedList* newNode = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    newNode->val = val;

    newNode->next = obj->next;

    obj->next = newNode;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* tmp = obj;
    MyLinkedList* newNode = (MyLinkedList*)malloc(sizeof(MyLinkedList));
     newNode->val = val;
     newNode->next = NULL;

    while (tmp) {
        if (tmp->next == NULL) {
            tmp->next = newNode;
            return;
        }
        tmp = tmp->next;
    }
}

/** Add a node of value val before the index-th node in the linked list.
If index equals to the length of linked list,
the node will be appended to the end of linked list.
If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    int i = 0;

    if(index < 0){
        myLinkedListAddAtHead(obj,val);
        return;
    }

    MyLinkedList* newNode = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    newNode->val = val;

    MyLinkedList* entry = obj;

    while(entry !=  NULL){
            if(i++ == index){
                newNode->next = entry->next;
                entry->next = newNode;
                break;
            }
            entry = entry->next;
    }
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
        int i = 0;
        MyLinkedList* list = obj;
        while(list->next!=NULL){
            if(i++ == index){
                list->next = list->next->next;
                break;
            }
            list = list->next;
        }
}

void myLinkedListFree(MyLinkedList* obj) {

}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);

 * myLinkedListAddAtHead(obj, val);

 * myLinkedListAddAtTail(obj, val);

 * myLinkedListAddAtIndex(obj, index, val);

 * myLinkedListDeleteAtIndex(obj, index);

 * myLinkedListFree(obj);
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/*
���ж�һ�������Ƿ�Ϊ��������

ʾ�� 1:

����: 1->2
���: false
ʾ�� 2:

����: 1->2->2->1
���: true
*/
bool isPalindrome(struct ListNode* head){
    // ����������ų�
    if(head == NULL || head->next == NULL)
        return true;
    if(head->next->next == NULL){
        if(head->val == head->next->val)
            return true;
        else
            return false;
    }

    struct ListNode *fastp, *slowp;
    fastp = head->next->next;
    slowp = head->next;

    // ����ָ���ҵ�β�����в�λ��
/*
���ǿ���ָ��һ����ָ��ÿ���������������ƣ�
��ָ��ÿ����һ���������ƣ���������ָ���ߵ�β��ʱ��
��ָ��պ��ߵ��в�
*/
    while(fastp && fastp->next != NULL){
        fastp = fastp->next->next;
        slowp = slowp->next;
    }

//�������ǿ��Է�ת�в�֮ǰ�������Ա��ں����Ƚϡ�
    // ��ת�в�ǰ��������
    struct ListNode *prep, *nextp;
    prep = nextp = NULL;
    while(head != slowp){
        nextp = head->next;
        head->next = prep;
        prep = head;
        head = nextp;
    }

    // ��������Ϊ�������������м���
    if(fastp != NULL && fastp->next == NULL)
        slowp = slowp->next;

    // ����ƥ��Ƚ�
    while(prep != NULL){
        if(prep->val != slowp->val)
            return false;
        prep = prep->next;
        slowp = slowp->next;
    }
    return true;
}


struct ListNode* removeElements(struct ListNode* head, int val){
       //ɾ��ֵ��ͬ��ͷ���󣬿����µ�ͷ���Ҳֵ��ȣ���ѭ�����
        while(head!=NULL&&head->val==val){
            head=head->next;
        }
        if(head==NULL)
            return head;
        struct ListNode *prev=head;
        //ȷ����ǰ�����н��
        while(prev->next!=NULL){
            if(prev->next->val==val){
                prev->next=prev->next->next;
            }else{
                prev=prev->next;
            }
        }
        return head;

}


/*
����һ����������ɾ�������ظ���Ԫ�أ�ʹ��ÿ��Ԫ��ֻ����һ�Ρ�

ʾ�� 1:

����: 1->1->2
���: 1->2
ʾ�� 2:

����: 1->1->2->3->3
���: 1->2->3

*/
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->next->val == current->val) {
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
    return head;
}

//��дһ�������ҵ������������ཻ����ʼ�ڵ㡣
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) return NULL;
    struct ListNode *pA = headA, *pB = headB;
    while (pA != pB) {
        pA = pA == NULL ? headB : pA->next;
        pB = pB == NULL ? headA : pB->next;
    }
    return pA;
}


int main()
{
    MyLinkedList* obj = myLinkedListCreate();

    myLinkedListAddAtHead(obj,1);
    myLinkedListAddAtTail(obj,3);
    myLinkedListAddAtIndex(obj,1,2);
    int ret = myLinkedListGet(obj,1);
    printf("%d\n",ret);
    myLinkedListDeleteAtIndex(obj,1);
    ret = myLinkedListGet(obj,1);
    printf("%d\n",ret);
}

