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

