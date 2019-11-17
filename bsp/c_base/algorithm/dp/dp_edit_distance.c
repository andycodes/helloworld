#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


#define MIN3(a,b,c) ((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
int minDistance(char * word1, char * word2)
{
	int row = (word1 == NULL) ? 0: strlen(word1);
	int col =  (word2 == NULL) ? 0: strlen(word2);

	row++;
	col++;

    int mat[row][col];                  /* C99 - variable-length array */


    for( int i=0; i<row; ++i ) {        /* 数组的行 */
        for( int j=0; j<col; ++j ) {    /* 数组的列 */
            if( i == 0 ) {
                mat[i][j] = j;          /* 初始化第1行为 [ 0 1 2 ... ] */
            }
            else if( j == 0 ) {
                mat[i][j] = i;          /* 初始化第1列为 [ 0 1 2 ... ] */
            }
            else {
                int cost = ( word1[i-1] == word2[j-1] ) ? 0 : 1;     /* 记录word1[i-1]与word2[j-1]是否相等 */
                mat[i][j] = MIN3( mat[i-1][j  ] + 1,           /* 取三者的最小值 */
                                  mat[i  ][j-1] + 1,
                                  mat[i-1][j-1] + cost);
            }
        }
    }

    return mat[row-1][col-1];
}}



