#include <stdio.h>

#define PR(...) printf(__VA_ARGS__)
int main()
{
    int wt=1,sp=2;
    PR("hello\n");
    PR("weight = %d, shipping = %d\n",wt,sp);
    return 0;
}

