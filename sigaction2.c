#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void mioHandler(int numeroSegnale){
    printf("Seganle %d ricevuto\n",numeroSegnale);
    sleep(2);
    printf("Segnale terminato\n");
}

int main(){
    printf("PID: %d\n",getpid());
    struct sigaction sa;
    sa.sa_handler=mioHandler;
    sigemptyset(&sa.sa_mask);//usa una mascher vuota, non blocca segnali
    sigaction(SIGUSR1,&sa,NULL);
    while (1);
    return 0;
}