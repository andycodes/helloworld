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


    for( int i=0; i<row; ++i ) {        /* ������� */
        for( int j=0; j<col; ++j ) {    /* ������� */
            if( i == 0 ) {
                mat[i][j] = j;          /* ��ʼ����1��Ϊ [ 0 1 2 ... ] */
            }
            else if( j == 0 ) {
                mat[i][j] = i;          /* ��ʼ����1��Ϊ [ 0 1 2 ... ] */
            }
            else {
                int cost = ( word1[i-1] == word2[j-1] ) ? 0 : 1;     /* ��¼word1[i-1]��word2[j-1]�Ƿ���� */
                mat[i][j] = MIN3( mat[i-1][j  ] + 1,           /* ȡ���ߵ���Сֵ */
                                  mat[i  ][j-1] + 1,
                                  mat[i-1][j-1] + cost);
            }
        }
    }

    return mat[row-1][col-1];
}}



