
#include "radix_tree.h"                                                                                                    

int main(void)
{
    char *test[] = {"abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz0",
                    "123", "456", "789", "zyx", "wvu", "tsr", "qpo", "nml", "kji"};
    int i = 0;
    int num = sizeof(test)/sizeof(*test);
    printf("num : %d\n", num);
    Pradix_tree_head head = radix_tree_head_new();
    radix_tree_initial(head);
    if(!head)
    {
        printf("alloc head failed\n");
    }

    for(i = 0; i < num; i++)
    {
        radix_tree_insert(head, i, test[i]);
    }

    for(i = 0; i < num; i++)
    {
        printf("%s\n",(char*) radix_tree_lookup(head, i));
    }
    for(i = 0; i < num; i++)
    {
        radix_tree_delete(head, i);
    }

    return 0;
}