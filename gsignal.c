#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

/*
    1. Processo ‘ancestor’ crea un figlio
        a. Il figlio cambia il proprio gruppo e genera 3 figli (Gruppo1)
        b. I 4 processi aspettano fino all’arrivo di un segnale
    2. Processo ‘ancestor’ crea un secondo figlio
        a. Il figlio cambia il proprio gruppo e genera 3 figli (Gruppo2)
        b. I 4 processi aspettano fino all’arrivo di un segnale
    3. Processo ‘ancestor’ manda due segnali diversi ai due gruppi
*/





void mioHandler(int numeroSegnale){
    printf("Il processo con PID: %d e GID: %d ha ricevuto il segnale %d\n",getpid(),getpgid(0),numeroSegnale);
    sleep(1);
    exit(0);
}

int main(){
    signal(SIGUSR1,mioHandler);
    signal(SIGUSR2,mioHandler);
    int padre=getpid();
    int gruppo1=fork();//questo figlio ha accesso ancora alla variabile padre quindi la può usare
    int gruppo2;
    if(getpid()!=padre){ //Entra qua solo se è il primo figlio
        setpgid(0,getpid());//Diventa il group leader
        fork();fork();//Genera processi nel nuovo gruppo
    }
    else{
        gruppo2=fork();
        if(getpid()!=padre){ //Entra qua solo se è il secondo figlio
            setpgid(0,getpid());//Diventa group leader
            fork();fork();//Genera processi nel nuovo gruppo
        }
    }
    if(getpid()==padre){
        printf("Il processo con PID: %d è il padre e ora ucciderà i figli\n",getpid());
        sleep(1);
        kill(- gruppo2,SIGUSR2);//manda SIGUSR2 al gruppo2
        kill(-gruppo1,SIGUSR1);//manda SIGUSR1 al grippo1
    }
    else{
        printf("Il processo con PID: %d e GID: %d sta aspettando un segnale dal padre\n",getpid(),getpgid(0));
        while(1);
    }
    while(wait(NULL)>0);
    printf("Tutti i figli hanno terminato\n");
    return 0;
}