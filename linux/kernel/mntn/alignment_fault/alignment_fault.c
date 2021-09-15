#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigbus_handler(int sno)
{
        printf("signal %d captured\n", sno);
        exit(1);
}

int main(int argc, char *argv[])
{
        char intarray[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
        signal(SIGBUS, sigbus_handler);
        printf("int1 = 0x%08x, int2 = 0x%08x, int3 = 0x%08x, int4 = 0x%08x\n",
                *((int *)(intarray + 1)),
                *((int *)(intarray + 2)),
                *((int *)(intarray + 3)),
                *((int *)(intarray + 4)));
        return 0;
}

