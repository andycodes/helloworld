#include <stdio.h>

/*


一维数组的两种访问方式。
以int b[10]为例, int *p = b;。
b[0] 等同于 *(p+0);
b[9] 等同于 *(p+9);
b[i] 等同于 *(p+i)


二维数组作为参数传递给函数
有以下三种形式:
void Func(int array[3][10]);
void Func(int array[ ][10]);
void Func(int (*array)[10]);
*/




/*
二维数组指针
指向数组     的     指针
*/
int two_dimensional_array_point_access(void)
{
    int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};

/*括号中的*表明 p 是一个指针，它指向一个数组，
数组的类型为int [4]，
这正是 a 所包含的每个一维数组的类型。

p 指向的数据类型是int [4]，那么p+1就前进 4×4 = 16 个字节，
p-1就后退 16 个字节，这正好是数组 a 所包含的每
个一维数组的长度。也就是说，
p+1会使得指针指向二维数组的下一行，
p-1会使得指针指向数组的上一行。
数组名 a 在表达式中也会被转换为和 p 等价的指针！

a+i == p+i
a[i] == p[i] == *(a+i) == *(p+i)
a[i][j] == p[i][j] == *(a[i]+j) == *(p[i]+j) == *(*(a+i)+j) == *(*(p+i)+j)
*/
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


/*
储存指针的数组
int *(p1[5]);  //指针数组，可以去掉括号直接写作 int *p1[5];
*/






/*
变长数组(variable-length array,VLA)(C99）
C99标准引入了变长数组，它允许使用变量定义数组各维
int quarters = 4;
int regions = 5;
double sales[quarters][regions]; //一个变长数组VAL

变长数组有一些限制：变长数组必须是自动存储类的，
意味着它们必须在函数内部或作为函数参数声明，
而且声明时不可以进行初始化。

C99标准规定，可以省略函数原型中的名称，
但是如果省略名称，则需要用星号来代替省略的维数:
int sum2d(int , int, int ar[*][*]);

6.7.5.2 Array declarators
Array objects declared with the static or extern storage-class specifier
cannot have a variable length array (VLA) type
*/
void array_vla(int tmp)
    {
            int a;

            scanf("%d", &a);
            int b[tmp];
            int c[a];
            printf ("size(b) = %lu, size(c) = %lu\n", sizeof(b)/sizeof(int), sizeof(c)/sizeof(int));
    }


/*
给定一个数组 A，将其划分为两个不相交（没有公共元素）的连续子数组 left 和 right， 使得：

left 中的每个元素都小于或等于 right 中的每个元素。
left 和 right 都是非空的。
left 要尽可能小。
在完成这样的分组后返回 left 的长度。可以保证存在这样的划分方法。
*/
int partitionDisjoint(int* A, int ASize){
	int *left_max = malloc(ASize * sizeof(int));
	int *right_min = malloc(ASize * sizeof(int));

	int tmp = A[0];
	for (int i = 0; i < ASize; i++) {
		tmp = tmp > A[i] ? tmp : A[i];
		left_max[i] = tmp;
	}

	tmp = A[ASize - 1];
	for (int i = ASize -1; i >= 0; i--) {
		tmp = tmp < A[i] ? tmp : A[i];
		right_min[i] = tmp;
	}

	for (int i = 1; i < ASize; i++){
		if (left_max[i -1] <= right_min[i])
			return i;
	}

	return ASize;
}


/*
给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞具有一个初始状态 live（1）即为活细胞， 或 dead（0）即为死细胞。每个细胞与其八个相邻位置（水平，垂直，对角线）
的细胞都遵循以下四条生存定律：

如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
根据当前状态，写一个函数来计算面板上细胞的下一个（一次更新后的）状态。下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。
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


int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("argc err\n");
		return -1;
	}

	switch(atoi(argv[1])) {
	case 1:
		two_dimensional_array_point_access();
	break;
	case 2:
	break;
	case 3:
	break;
	case 4:
	default:
	break;
	}

	return 0;
}


