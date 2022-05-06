#include <bits/types/sigset_t.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

sigset_t mod,pen;

void handlerMio(int numeroSegnale){
    printf("SIGUSR1 ricevuto\n");
    sigpending(&pen);
    if(!sigismember(&pen,SIGUSR1)){
        printf("SIGUSR1 non in pending\n");
    }
    exit(0);
}

int main(){
    signal(SIGUSR1,handlerMio);
    sigemptyset(&mod);
    sigaddset(&mod,SIGUSR1);
    sigprocmask(SIG_BLOCK,&mod,NULL);
    kill(getpid(),SIGUSR1);
    //manda il segnale ma è bloccato
    sigpending(&pen);
    if(sigismember(&pen,SIGUSR1)){
        printf("SIGUSR1 pending\n");
    }
    sigprocmask(SIG_UNBLOCK,&mod,NULL);
    return 0;
}