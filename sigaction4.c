#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void mioHandler(int numeroSegnale,siginfo_t * info,void * empty){
    //Stampa l'id del processo mandante del segnale
    printf("Segnale ricevuto da %d\n",info->si_pid);
}

int main(){
    printf("Il mio PID è: %d\n",getpid());
    struct sigaction sa;
    sa.sa_sigaction=mioHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags |=SA_SIGINFO; //Usa sa_sigaction
    sa.sa_flags |=SA_RESETHAND; //Ripristina il default handler
    sigaction(SIGUSR1,&sa,NULL);
    while(1);
    return 0;
}