#include <stdio.h>

#include <getopt.h>

char *l_opt_arg;

char* const short_options = "nbl:";

struct option long_options[] = {

{ "name", 0, NULL, 'n' },

{ "bf_name", 0, NULL, 'b' },

{ "love", 1, NULL, 'l' },

{ 0, 0, 0, 0},

};

int main(int argc, char *argv[])
{
	int c;
	while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1){
		switch (c){
		case 'n':
			printf("My name is XL.\n");
		break;
		case 'b':
			printf("His name is ST.\n");
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