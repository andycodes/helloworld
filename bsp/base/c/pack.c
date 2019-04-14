
#include<stdio.h>

#pragma pack(8)
struct S1
{
    char a;
    long b;
};

struct S2
{
    char c;
    struct S1 d;
    long long e;
};
#pragma pack()

int main(void)
{
   struct A
   {
      char a;
      short b;
      int c;
   };

   struct B
   {
      short b;
      int c;
      char a;
   };

   struct C
     {
         char c1;
         int c2;
         short c3;
         double c4;
     };

   printf("A %lu\n",sizeof(struct A));
   printf("B %lu\n",sizeof(struct B));
   printf("C %lu\n",sizeof(struct C));/*GCC默认是按照4字对齐*/
   printf("S1 %lu\n",sizeof(struct S1));
   return 0;

}

