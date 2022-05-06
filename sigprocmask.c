#include <bits/types/sigset_t.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int counter=0;
sigset_t mod,old;

void mioHandler(int numeroSegnale){
    printf("seganle ricevuto\n");
    counter++;
}

int main(){
    printf("il mio PID è %d\n",getpid());
    signal(SIGUSR1,mioHandler);
    sigemptyset(&mod);
    sigaddset(&mod,SIGUSR1);
    while (1) {
        if(counter==1){
            sigprocmask(SIG_BLOCK,&mod,&old);
        }
    }
    return 0;
}