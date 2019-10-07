#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void reverseString(int front, int tail, char *str) {
        while (front < tail) {
            str[front] ^= str[tail];
            str[tail] ^= str[front];
            str[front++] ^= str[tail--];
        }
}


char * reverseWords(char * s){
        int front = 0;
        for (int i = 0; i < strlen(s); i++) {
            if (s[i] == ' ') {
                reverseString(front, i - 1, s);
                front = i + 1;
            }
        }
        reverseString(front,strlen(s) - 1, s);
        return s;
}


int main()
{
    char ss[] = "Let's take LeetCode contest";

    printf("[%s]\n",reverseWords(ss));
    return 0;
}

