#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void mioHandler(int numeroSegnale){
    printf("[%d]ALLARM!\n",getpid());
}

int main(){
    signal(SIGALRM,mioHandler);
    printf("I'm %d\n",getpid());
    while(1);
    return 0;
}