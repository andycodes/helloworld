#include <stdio.h>
#include <getopt.h>

void case1_run_forever(void) 
{
        long int i = 0;
        while(1) {
                i++;
        }
}

static char array[10000][10000];
int case2_for_ji(void)
{
        int i, j;
        for (i = 0; i < 10000; i++)
            for (j = 0; j < 10000; j++)
                 array[j][i]=i;
                 return 0;
}

int case2_for_ij(void)
{
        int i, j;
        for (i = 0; i < 10000; i++)
            for (j = 0; j < 10000; j++)
                 array[i][j]=i;
                 return 0;
}


char *l_opt_arg;
char* const short_options = "nbcl:";
struct option long_options[] = {
        { "forever", 0, NULL, 'n' },
        { "case2_for_ji", 0, NULL, 'b' },
        { "case2_for_ij", 0, NULL, 'c' },
        { "love", 1, NULL, 'l' },
        { 0, 0, 0, 0},
};

int main(int argc, char *argv[])
{
        int c;

        while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1) {
        	switch (c){
        	case 'n':
                                printf("run_forever\n");
                                case1_run_forever();
        	break;
        	case 'b':
                                printf("case2_for_ji.\n");
                                case2_for_ji();
        	break;
          	case 'c':
                                printf("case2_for_ij.\n");
                                case2_for_ij();
        	break;
        	case 'l':
        		l_opt_arg = optarg;
        		printf("Our love is %s!\n", l_opt_arg);
        	break;
        	}
        }
        return 0;
}

/*./getopt -n -b -l forever*/
