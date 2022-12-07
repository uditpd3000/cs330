#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int primes[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97}; // Primes till 100

int pipefd[2],n;

void solve(int x){                                                                     // x is the index of prime number list 

    if(n==1 || n<primes[x]){                                                           // If prime factorisation completes
        return;
    }

    if (read(pipefd[0], &n, 1) < 0) {                                                 // Read n which was passed after processing previous prime number
        printf("Error: cannot read. Aborting...\n");
        exit(0);
    }

    int f=0;
    while(n%primes[x]==0){
        f=1;
        printf("%d, ",primes[x]);
        n = n/primes[x];
    }
    if(f){
        printf("[%d]\n",getpid());
    }
    x++;

    if (write(pipefd[1], &n, 1) < 0) {                                                // Write back n after processing current prime
        printf("Error: cannot write. Aborting...\n");
        exit(0);
    }

    if(fork()==0){                                                                    // go to the next prime number
        solve(x);
        return;
    }
    else{
        wait(NULL);
    }
}

int main(int argc, char *argv[])
{   
    // fprintf(2,"%d %c%c %c\n", argc,*argv[1],*(argv[1]+1),*argv[2]);
    n =0;
    int notInt=0;
    char * c = argv[1];
    while(*c!='\0'){
        n = n*10 + (*c - '0');
        if((*c-'0')>9||(*c-'0')<0)notInt=1;
        c++;
    }
    
    // fprintf(2,"%d\n", n);

    if(n<2 || n>100 || notInt){
        printf("Expected : Positive integer in range [2,100]\n");
        exit(-1);
    }

    if (pipe(pipefd) < 0) {
        printf("Error: cannot create pipe. Aborting...\n");
        exit(0);
    }

    if (write(pipefd[1], &n, 1) < 0) {
        printf("Error: cannot write. Aborting...\n");
        exit(0);
    }

    solve(0);

    close(pipefd[0]);
    close(pipefd[1]);

    exit(0);
}