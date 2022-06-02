#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void scriviIlPID(FILE *file){
    int pid=getpid();
    fprintf(file,"%d\n",pid);
    fflush(file);
}

void handlerManager(int numSig){
    printf("Ora uccido un figlio");
}

int main(int argc,char **argv){
    if(argc!=3){
        exit(3);
    }
    int numero=atoi(argv[2]);
    if(numero<1 || numero>10){
        printf("Numero non compreso tra 1 e 10\n");
        exit(4);
    }
    FILE *file=fopen(argv[1],"r");
    if(file!=NULL){
        printf("Il file esite già\n");
        exit(5);
    }
    file=fopen(argv[1],"a");
    scriviIlPID(file);
    int *vettoreFigli=malloc((numero+1)*sizeof(int));
    int manager=fork();
    if(manager==0){
        vettoreFigli[0]=getpid();
        struct sigaction sa;
        sa.sa_handler=handlerManager;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags |= SA_SIGINFO;
        sa.sa_flags |= SA_RESTART;
        sigaddset(&sa.sa_mask,SIGUSR1);
        scriviIlPID(file);
        while(numero>0){
            int figlio=fork();
            if(figlio==0){
                scriviIlPID(file);
                pause();
            }
            else{
                vettoreFigli[numero]=figlio;
            }
            numero--;
        }
        pause();
    }
    else{
        printf("Ora uccido tutti hihihi\n");
        sleep(3);
        kill(manager,SIGUSR1);
    }

    free(vettoreFigli);
    fclose(file);
    return 0;
}