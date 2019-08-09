#include <stdio.h>
#include <stdarg.h>


#define PR(...) printf(__VA_ARGS__)
void test_PR(void)
{
    int wt=1,sp=2;
    PR("hello\n");
    PR("weight = %d, shipping = %d\n",wt,sp);
}


/*采用C调用约定时，函数的参数是
从右到左入栈，个数可变*/

/*va_start
* 第1参数:参数列表
* 第2参数:不定参数前面的一个固定参数
*
*/
/*
*va_arg取参
*
*/
int sum(int n, ...)
 {
         va_list arglist;
         int result = 0;
         int i, value;

        va_start(arglist, n);

        printf("(");

        for (i = 0; i < n-1; i++)
         {
                 value = va_arg(arglist, int);
                 result += value;

                printf("%d+", value);
         }

        value = va_arg(arglist, int);
         result += value;

        printf("%d) = %d\n", value, result);

        va_end(arglist);

        return result;
 }


void my_printf( char *format, ... )
{
	va_list argptr;
	va_start( argptr, format );

	while( *format != '\0' ) {
		// string
		if( *format == 's' ) {
			 char* s = va_arg( argptr, char * );
			 printf( "Printing a string: %s\n", s );
		}
		// character
		else if( *format == 'c' ) {
			 char c = (char) va_arg( argptr, int );
			 printf( "Printing a character: %c\n", c );
			 break;
		}
		// integer
		else if( *format == 'd' ) {
			 int d = va_arg( argptr, int );
			 printf( "Printing an integer: %d\n", d );
		}

		format++;
	}

	va_end( argptr );
}


int main( void )
{
	 my_printf( "sdc", "This is a string", 29, 'X' );

	sum(1, 10);
	sum(2, 10, 20);
	sum(3, 10, 20, 30);
	sum(5, 1, 2, 3, 4, 5);

	test_PR();
	return 0;
}


