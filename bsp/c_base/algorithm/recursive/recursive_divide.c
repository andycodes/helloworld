#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


int cmp(const void* i,const void* j){
    int* a = (int *) i ;
    int* b = (int *) j ;
    if(*a>*b)
        return 1 ;
    if(*a<*b)
        return -1 ;
    return 0 ;
}


bool computeTerminate(char* input){
    for(int i=0;i<strlen(input);i++){
        if(ispunct(input[i]))
            return false ;
    }
    return true ;
}

char* subString(char* input,int start ,int end){
    char* temp = (char*)malloc(sizeof(char)*(end-start+1)) ;
    for(int i=0;i<(end-start);i++){
        temp[i] = input[start+i] ;
    }
    temp[end-start] = '\0' ;
    return temp ;
}

int computeResult(int a,int b,char op){
    switch(op){
        case '+': return a+b ;
        case '-': return a-b ;
        case '*': return a*b ;
    }
}

//���ҵݹ飬��ֹ����ֻ����һ����������������ʱ
int* diffWaysToCompute(char* input,int* returnSize){
    //ֻ������һ����
    if(computeTerminate(input)){
	int* result = (int *)malloc(sizeof(int)*1) ;
	result[0] = atoi(input) ;
	*returnSize = 1 ;
	return result ;
    }

    int* result = (int *)malloc(sizeof(int)*1500) ;
    for(int i=0;i<strlen(input);i++){
        if(ispunct(input[i])){
            int lSize = 0 ;
            int RSize = 0 ;
            char* left = subString(input,0,i) ;
            char* right = subString(input,i+1,strlen(input)) ;
            int* l = diffWaysToCompute(left,&lSize) ;
            int* r = diffWaysToCompute(right,&RSize) ;
            for(int j=0;j<lSize;j++)
                for(int k=0;k<RSize;k++){
                    result[*returnSize] = computeResult(l[j],r[k],input[i]) ;
                    (*returnSize)++ ;
                }
        }
    }

    int* temp = (int*)malloc(sizeof(int)*(*returnSize-1)) ;
    for(int i=0;i<*returnSize;i++){
        temp[i] = result[i] ;
    }
    free(result) ;
    //�ͷ�result��ָ��Ŀռ�----����ϵͳ������ռ���Ա����·����ˡ���ʱresult�����ֵ������ָ��Ŀռ䲻�䣩
    //����Ϊ�˱�ָ֤��İ�ȫ�ԣ�ͨ��������free(result);֮�����һ��result=NULL,����result�ٴβ�����ԭ���Ŀռ䡣
    result = NULL ;
    return temp ;
}

int main(void){
    char array[2][20] = {
		"2-1-1",
		"2*3-4*5"
	};

for(int j = 0; j <2; j++) {
    int returnSize = 0 ;
    int* result = NULL ;
    result = diffWaysToCompute(array[j],&returnSize) ;
    qsort(result,returnSize,sizeof(int),cmp) ;
    for(int i=0;i<returnSize;i++){
        printf("%d ",result[i]) ;
    }
    printf("\n") ;
}
    return 0 ;
}

