#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void mioHandler(int numeroSegnale){
    printf("Figlio terminato dopo aver ricevuto %d\n",numeroSegnale);
}

int main(){
    signal(SIGCHLD,mioHandler);
    int figlio=fork();
    if(!figlio){
        return 0;
    }
    while (wait(NULL));
    return 0;
}