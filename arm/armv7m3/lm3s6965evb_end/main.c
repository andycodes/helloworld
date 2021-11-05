#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lm3s6965.h"

void ResetISR(void);

int main(){

	printf("\nResetISR:%x\n", ResetISR);
	printf("testing lm3s6965...\nAddress\n");

	char * p = NULL;
	p = (char *) malloc(sizeof(char)*100);
	if(p == NULL){
		printf("malloc error!!!\n");
		while(1){;}
	}

	strcpy(p, "!!!Hello, World!!!");
	for(;*p != 0;p++){
		printf("0x%x	%c\n",p,*p);
	}

	printf("\nDead cycle...\n");
	
	while(1){;}
	
	return 0;
}