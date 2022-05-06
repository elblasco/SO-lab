#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void mioHandler(int numeroSegnale){
    printf("There are two sexes\n");
    sleep(2);
    printf("The one that i had with your dad\n");
    sleep(2);
    printf("The one that i had with your mum\n");
}

int main(){
    signal(SIGCONT,mioHandler);
    signal(SIGUSR1,mioHandler);
    pause();
}