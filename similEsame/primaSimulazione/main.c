#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXLEAF 10

FILE *ptr;
int array_leaf[MAXLEAF],index_leaf=0,n_figli;
int leaf_pipes[MAXLEAF][2];
int my_pid;

void manager_handler(int signo){
    if(signo==SIGUSR1 && index_leaf-1>=0){
        printf("Ho ricevuto un USR1 e adesso lo invio a %d\n",array_leaf[index_leaf-1]);
        kill(SIGUSR1,array_leaf[index_leaf-1]);
    }
    if(signo==SIGUSR2){
        printf("Ho ricevuto un USR2\n");
    }
}

void leaf_handler(int signo){
    if(signo==SIGUSR1){
        int padre;
        read(leaf_pipes[my_pid][0],&padre,sizeof(padre));
        printf("Sono il figlio e sto per mandare il segnale al padre %d\n",padre);
        kill(SIGUSR2,padre);
        exit(0);
    }
}

bool file_exists(const char* path){
    FILE* prova=fopen(path,"r+");
    bool trovato=false;
    if(prova!=NULL){
        trovato=true;
        fclose(prova);
    }
    return trovato;
}

void scrivi_pid(){
    fprintf(ptr,"%d\n",getpid());
    fflush(ptr);
}

void manager_logic(){
    signal(SIGUSR1,manager_handler);
    signal(SIGALRM,SIG_IGN);
    for(int i=0;i<n_figli;++i){
        int leaf=fork();
        if(leaf==0){
            my_pid=i;
            printf("Il mio offset è %d\n",my_pid);
            signal(SIGUSR1,leaf_handler);
            signal(SIGCHLD,SIG_IGN);
            signal(SIGCONT,SIG_IGN);
            scrivi_pid();
            while(true){
                pause();
            }
        }
        else{
            int pid_manager=getpid();
            pipe(leaf_pipes[index_leaf]);
            write(leaf_pipes[index_leaf][1],&pid_manager,sizeof(pid_manager));
            array_leaf[index_leaf]=leaf;
            index_leaf++;
        }
    }
}

int main(int argc, char **argv){
    int argomenti=argc;
    if(argomenti!=3){
        exit(3);
    }
    n_figli=atoi(argv[2]);
    if(n_figli<1 || n_figli>10){
        exit(4);
    }
    if(file_exists(argv[1])){
        exit(5);
    }
    ptr=fopen(argv[1],"w");
    scrivi_pid();
    int manager=fork();
    if(manager==0){
        printf("Sono il manager %d\n",getpid());
        scrivi_pid();
        manager_logic();
        while (wait(NULL)>0);
    }
    else{
        while(wait(NULL)>0);
    }
    return 0;
}