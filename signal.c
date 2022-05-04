#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handlerMio(int numeroSegnale){
    printf("CTRL+Z\n");
}

int main(){
    signal(SIGINT,SIG_IGN); //occhio che con questo CTRL+C viene ignorato
    printf("Ho ignorato il primo segnale\n");
    signal(SIGCHLD,SIG_DFL);
    printf("Ho usato l' handler di default\n");
    signal(SIGTSTP,handlerMio);
    while (1);
    return 0;
}