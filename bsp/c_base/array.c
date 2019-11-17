/*
��ά������Ϊ�������ݸ�����
������������ʽ:
void Func(int array[3][10]);
void Func(int array[ ][10]);
void Func(int (*array)[10]);
*/

/*
����һ������ m �� n �����ӵ���壬ÿһ�����Ӷ����Կ�����һ��ϸ����ÿ��ϸ������һ����ʼ״̬ live��1����Ϊ��ϸ���� �� dead��0����Ϊ��ϸ����ÿ��ϸ������˸�����λ�ã�ˮƽ����ֱ���Խ��ߣ�
��ϸ������ѭ�����������涨�ɣ�

�����ϸ����Χ�˸�λ�õĻ�ϸ�����������������λ�û�ϸ��������
�����ϸ����Χ�˸�λ����������������ϸ�������λ�û�ϸ����Ȼ��
�����ϸ����Χ�˸�λ���г���������ϸ�������λ�û�ϸ��������
�����ϸ����Χ������������ϸ�������λ����ϸ�����
���ݵ�ǰ״̬��дһ�����������������ϸ������һ����һ�θ��º�ģ�״̬����һ��״̬��ͨ������������ͬʱӦ���ڵ�ǰ״̬�µ�ÿ��ϸ�����γɵģ�����ϸ���ĳ�����������ͬʱ�����ġ�
*/
void gameOfLife(int** board, int boardSize, int* boardColSize){
    int m = boardSize;
    int n = *boardColSize;
    int sum = 0;
    int midArr[m+2][n+2];

    for(int i = 0; i < (m +2); i++) {
        for(int j = 0; j < (n+2);j++) {
            midArr[i][j] = 0;
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n;j++) {
            midArr[i + 1][j + 1] = board[i][j];
        }
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int x = i + 1;
            int y = j + 1;
            sum = midArr[x - 1][y] + midArr[x + 1][y] + midArr[x][y - 1] + midArr[x][y + 1] + midArr[x - 1][y - 1] + midArr[x + 1][y + 1] + midArr[x + 1][y - 1] + midArr[x - 1][y + 1];
            if((sum == 3) || ((board[i][j] == 1) && (sum == 2))) {
                board[i][j] = 1;
            } else {
                board[i][j] = 0;
            }
        }
    }
}


#include <stdio.h>
/*
a+i == p+i
a[i] == p[i] == *(a+i) == *(p+i)
a[i][j] == p[i][j] == *(a[i]+j) == *(p[i]+j) == *(*(a+i)+j) == *(*(p+i)+j)
*/
int main(){
    int a[3][4]={0,1,2,3,4,5,6,7,8,9,10,11};
    int(*p)[4];
    int i,j;
    p=a;
    for(i=0; i<3; i++){
		for(j=0; j<4; j++)
			printf("%2d  ",*(*(p+i)+j));
		printf("\n");
	}
	return 0;
}

