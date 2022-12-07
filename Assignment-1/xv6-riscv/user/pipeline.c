#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int pipefd[2],x;

void solve(int n){                                    // n is the number of processes

    if(n==0){
        return;
    }

    if (read(pipefd[0], &x, 8) < 0) {                 // we read x which was passed from prev process  
        printf("Error: cannot read. Aborting...\n");
        exit(0);
    }

    fprintf(2,"%d: %d\n", getpid(),x+getpid());
    x = x + getpid();                                 // Then updayte it

    if (write(pipefd[1], &x, 8) < 0) {                // and write back for the next process
        printf("Error: cannot write. Aborting...\n");
        exit(0);
    }
 
    if(fork()==0){                                     // Then we create a new process and call solve() again
        solve(n-1);
        return;
    }
    else{
        wait(NULL);
    }
}

int main(int argc, char *argv[])
{   

    int n =0,x=0,notPosInt=0;
    char * c = argv[1];
    while(*c!='\0'){
        n = n*10 + (*c - '0');
        if((*c-'0')>9||(*c-'0')<0)notPosInt=1;
        c++;   
    }
    if(n<=0) notPosInt=1;                           

    c= argv[2];
    int notInt=0,neg=1;

    if(*c=='-'){neg=-1;c++;}                         // Handling negative input

    while(*c!='\0'){
        x = x*10 + (*c - '0');
        if((*c-'0')>9||(*c-'0')<0)notInt=1;          // Handling non integers
        c++;
    }
    x*=neg;

    if(notInt){
        printf("Second argument: expected integer\n");
        exit(-1);

    }
    if(notPosInt){
        printf("First argument: expected positive integer\n");
        exit(-1);
    }

    if (pipe(pipefd) < 0) {
        printf("Error: cannot create pipe. Aborting...\n");
        exit(0);
    }

    if (write(pipefd[1], &x, 8) < 0) {
        printf("Error: cannot write. Aborting...\n");
        exit(0);
    }

    solve(n);

    close(pipefd[0]);                                         // Close the descriptors
    close(pipefd[1]);

    exit(0);
}