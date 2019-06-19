#include "save_princess.h"
#include <stdio.h>

#define M 10
#define N 10

int main()
{
	int ret = 0;
	int row = 0;
	int col = 0;

	char maze_info[M][N] = {\
	/*      0    1    2    3    4    5    6    7    8    9*/
	/*0*/ {'.', '.', '.', '*', '.', '.', '.', '.', '.', '.'},
	/*1*/ {'.', 'S', '*', '.', '.', '.', '.', '.', '.', '.'},
	/*2*/ {'.', '.', '*', '.', '.', '.', '.', '.', '.', '.'},
	/*3*/ {'.', '.', '*', '*', '.', '*', '.', '.', '.', '.'},
	/*4*/ {'.', '.', '.', '*', '.', '*', '.', '.', '.', '.'},
	/*5*/ {'.', '.', '.', '*', '.', '.', '.', '.', '.', '.'},
	/*6*/ {'.', '.', '*', '.', '.', '.', '.', '.', '.', '.'},
	/*7*/ {'.', '.', '*', '.', '*', '.', '*', '.', '.', '.'},
	/*8*/ {'.', '.', '.', '.', '*', '.', '*', '*', '*', '.'},
	/*9*/ {'.', '.', '*', '.', '*', '.', '*', 'P', '.', '.'}};

	fprintf(stdout, "\n  ");
	for (col = 0; col < N; col++)
	{
		fprintf(stdout, "%d ", col);
	}
	fprintf(stdout, "\n");

	for (row = 0; row < M; row++)
	{
		fprintf(stdout, "%d ", row);
		for (col = 0; col < N; col++)
		{
			fprintf(stdout, "%c ", maze_info[row][col]);
		}
		fprintf(stdout, "\n");
	}

	ret = save_princess(M, N, (char*)maze_info, 6);

	fprintf(stdout, "\n");
	//system("pause");
	return 0;
}