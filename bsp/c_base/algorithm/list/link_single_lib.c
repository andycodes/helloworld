  struct ListNode {
      int val;
      struct ListNode *next;
  };


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


