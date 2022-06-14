#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void mioHandler(int numeroSegnale){
    printf("[%d]ALLARM!\n",getpid());

}

int main(){
    signal(SIGALRM,mioHandler);
    int figlio=fork();
    if(!figlio){
        while(1); //blokka il figlio
    }
    printf("[%d] mandando allarme a %d in 3 secondi\n",getpid(),figlio);
    sleep(3);
    kill(figlio,SIGKILL); //manda ALLARM al handler del figlio
    printf("[%d] mandando SIGTERM a %d in 3 secondi\n",getpid(),figlio);
    sleep(3);
    kill(figlio,SIGTERM); //manfa TERM
    while(wait(NULL)>0);
}