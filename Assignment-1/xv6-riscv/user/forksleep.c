#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int main(int argc, char *argv[])
{   
    // fprintf(2,"%d %c%c %c\n", argc,*argv[1],*(argv[1]+1),*argv[2]);
    int m =0,notPosInt=0;
    char * c = argv[1];
    while(*c!='\0'){
        if((*c-'0')>9||(*c-'0')<0)notPosInt=1;
        m = m*10 + (*c - '0');
        c++;
    }
    if(m<=0)notPosInt=1;
    
    if(notPosInt){
        printf("First argument should be a positive integer\n");
        exit(-1);
    }

    if(*argv[2]!='0' && *argv[2]!='1'){
        printf("2nd argument should be 0 or 1\n");
        exit(-1);
    }

    if(fork()==0){
        //child
        if(*argv[2]=='0'){
            sleep(m);
            printf("%d: Child\n",getpid());
        }
        else{
            printf("%d: Child\n",getpid());
        }
    }
    else{
        //parent
        if(*argv[2]=='0'){
            printf("%d: Parent\n",getpid());
            wait(NULL);
        }
        else{
            sleep(m);
            printf("%d: Parent\n",getpid());
            wait(NULL);
        }

    }

    exit(0);
}