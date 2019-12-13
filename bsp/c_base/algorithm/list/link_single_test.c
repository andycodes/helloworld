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

