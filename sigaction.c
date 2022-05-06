#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void handlerMio(int numeroSegnale){
    printf("segnale ricevuto\n");
}

int main(){
    struct sigaction sa;
    sa.sa_handler=handlerMio;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1,&sa,NULL);
    kill(getpid(),SIGUSR1);
    return 0;
}