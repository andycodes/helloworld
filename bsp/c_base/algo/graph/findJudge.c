#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
法官不相信任何人
法官要被N-1个人相信
只有一个人是被N-1个相信
只有一个法官
*/
int findJudge(int N, int** trust, int trustSize, int* trustColSize){
    int *ret_val = (int *)calloc(N+2, sizeof(int));
    for (int i = 0; i < N+1; ++i)         ret_val[i] = 0;

	//记录被相信的次数
    for (int i = 0; i < trustSize; ++i) ++ret_val[trust[i][1]];

	//如果他相信别人，就对被相信的次数清零
    for (int i = 0; i < trustSize; ++i)   ret_val[trust[i][0]] = 0;

    int num = 0;
    int top = -1;
    for (int i = 1; i <= N; ++i) {
        if (ret_val[i] == N-1) {  //查找相信次数为N-1的人
            ++num;
            top = i;//记录下标
        }
    }

//如果有大于1个法官，就为-1，否则就为该下标
    return (num > 1 ? -1 : top);
}



int main()
{
}

