/* m.c */
int i = 1;
int j = 2;
extern int sum();

void _exit(int parm)
{

}

void main()
{
        int s;
        s = sum(i, j);
}

/*
gcc -c m.c
*/

