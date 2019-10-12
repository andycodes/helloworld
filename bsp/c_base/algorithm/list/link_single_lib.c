  struct ListNode {
      int val;
      struct ListNode *next;
  };


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


