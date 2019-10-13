typedef  struct ListNode {
      int val;
      struct ListNode *next;
}MyLinkedList;


/*
将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。?

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
*/

/*
方法 1：递归
想法

我们可以如下递归地定义在两个链表里的 merge 操作（忽略边界情况，比如空链表等）：

\left\{ \begin{array}{ll} list1[0] + merge(list1[1:], list2) & list1[0] < list2[0] \\ list2[0] + merge(list1, list2[1:]) & otherwise \end{array} \right.
{
list1[0]+merge(list1[1:],list2)
list2[0]+merge(list1,list2[1:])
?

list1[0]<list2[0]
otherwise
?


也就是说，两个链表头部较小的一个与剩下元素的 merge 操作结果合并。

算法
我们直接将以上递归过程建模，首先考虑边界情况。
特殊的，如果 l1 或者 l2 一开始就是 null ，那么没有任何操作需要合并，所以我们只需要返回非空链表。否则，我们要判断 l1 和 l2 哪一个的头元素更小，然后递归地决定下一个添加到结果里的值。如果两个链表都是空的，那么过程终止，所以递归过程最终一定会终止。

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
给定一个链表，判断链表中是否有环。

为了表示给定链表中的环，
我们使用整数 pos 来表示链表尾连接到链
表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。
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
请判断一个链表是否为回文链表。

示例 1:

输入: 1->2
输出: false
示例 2:

输入: 1->2->2->1
输出: true
*/
bool isPalindrome(struct ListNode* head){
    // 特殊情况的排除
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

    // 快慢指针找到尾部及中部位置
/*
我们可以指定一个快指针每次以两个步长后移，
慢指针每次以一个步长后移，这样当快指针走到尾部时，
慢指针刚好走到中部
*/
    while(fastp && fastp->next != NULL){
        fastp = fastp->next->next;
        slowp = slowp->next;
    }

//而后我们可以翻转中部之前的链表，以便于后续比较。
    // 翻转中部前链表序列
    struct ListNode *prep, *nextp;
    prep = nextp = NULL;
    while(head != slowp){
        nextp = head->next;
        head->next = prep;
        prep = head;
        head = nextp;
    }

    // 若结点个数为奇数，则舍弃中间结点
    if(fastp != NULL && fastp->next == NULL)
        slowp = slowp->next;

    // 回文匹配比较
    while(prep != NULL){
        if(prep->val != slowp->val)
            return false;
        prep = prep->next;
        slowp = slowp->next;
    }
    return true;
}


struct ListNode* removeElements(struct ListNode* head, int val){
       //删除值相同的头结点后，可能新的头结点也值相等，用循环解决
        while(head!=NULL&&head->val==val){
            head=head->next;
        }
        if(head==NULL)
            return head;
        struct ListNode *prev=head;
        //确保当前结点后还有结点
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
给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

示例 1:

输入: 1->1->2
输出: 1->2
示例 2:

输入: 1->1->2->3->3
输出: 1->2->3

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

//编写一个程序，找到两个单链表相交的起始节点。
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

