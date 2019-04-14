#include <stdio.h>
#include "josephlist.h" 

void print_item(link p)
{
    printf("%d\n",p->item);
}

#if 0
int main()
{
    printf("joseph(6,5)\n");
    joseph_number(6,5);
    printf("joseph(6,3)\n");
    joseph_number(6,3);
    printf("joseph(6,4)\n");
    joseph_number(6,4);
    
    return 0;
}
#endif

/*
1,
1,3
1,3,5,7
1,3,5,7,9,11,13,15,
...
*/
int main()
{
    int total=25;
    int result_people[26];
    for (int i=1;i<=total;i++) {
        result_people[i]=joseph_number(i,2);
    }
    for(int i=1;i<=total;i++) 
    {
        printf("%d\t",i);
    }
        printf("\n");
    for(int i=1;i<=total;i++) 
    {
        printf("%d\t",result_people[i]);
    }
        printf("\n");
   
    return 0;
}

