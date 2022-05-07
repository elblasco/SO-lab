#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

extern int errno;

int main(){
    int sistema=kill(3443,SIGUSR1);
    if(sistema==-1){
        fprintf(stderr,"Errore numero: %d\n",errno);
        perror("Errore stampato da perror");
        fprintf(stderr,"Strerror: %s\n",strerror(errno));
    }
    else{
        printf("Processo 3443 terminato con successo\n");
    }
    return 0;
}