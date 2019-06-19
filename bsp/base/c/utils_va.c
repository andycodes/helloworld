#include <stdarg.h>
/*����C����Լ��ʱ�������Ĳ�����
���ҵ�����ջ�������ɱ�*/

/*va_start
* ��1����:�����б�
* ��2����:��������ǰ���һ���̶�����
*
*/
/*
*va_argȡ��
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
 
     return( 0 );
   }
#if 0
int main()
{
	sum(1, 10);
	sum(2, 10, 20);
	sum(3, 10, 20, 30);
	sum(5, 1, 2, 3, 4, 5);
}
#endif
