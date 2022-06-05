#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdbool.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<string.h>

#define MAXLEAF 10

FILE*out;
int foglie[MAXLEAF],indice_foglie=0,fd[2];

void manager_handler(int signo){
    if(signo==SIGUSR1){
        if(indice_foglie-1<0){
            exit(0);
        }
        else{
            printf("Faccio sesso\n");
            fflush(stdout);
            close(fd[0]);
            write(fd[1],"SIGUSR1",8);
            write(fd[1],getpid(),sizeof(int)*5);
            printf("Mo uccido la figlia con il PID %d\n",foglie[indice_foglie-1]);
            fflush(stdout);
            kill(SIGKILL,foglie[indice_foglie-1]);
            indice_foglie--;
        }
    }
    if(signo==SIGUSR2){
        printf("Mi è arrivato uno SIGUSR2 da una foglia\n");
        fflush(stdout);
    }
}

bool file_check(const char* file_name){
    FILE* tmp=fopen(file_name,"r");
    bool find=false;
    if(tmp!=NULL){
        find=true;
        fclose(tmp);
    }
    return find;
}

void scrivi_pid(){
    fprintf(out,"%d\n",getpid());
    fflush(out);
}

int genera_foglie(int n_foglie){
    for(int i=0;i<n_foglie;++i){
        int foglia=fork();
        foglie[indice_foglie]=foglia;
        indice_foglie++;
        if(foglia==0){
            scrivi_pid();
            char lettura_pipe[8];
            int pid_manager=0;
            close(fd[1]);
            read(fd[0],pid_manager,sizeof(int)*5);
            read(fd[0],lettura_pipe,8);
            if(strcmp("SIGUSR1",lettura_pipe)){
                kill(SIGUSR2,pid_manager);
            }
            while(true){
                pause();
            }
        }
    }
}

int logica_manager(int i){
    signal(SIGUSR1,manager_handler);
    signal(SIGUSR2,manager_handler);
    printf("Il manager ha PID %d\n",getpid());
    scrivi_pid();
    if(pipe(fd)<0){
        exit(-66);
    }
    genera_foglie(i);
    while(wait(NULL)>0);
    return 1;
}

int main(int argc ,char ** argv){
    int n=atoi(argv[2]);
    if(argc!=3){
        exit(3);
    }
    if(n<1 || n>10){
        exit(4);
    }
    if(file_check(argv[1])){
        exit(5);
    }
    out=fopen(argv[1],"w");
    if(out==NULL){
        exit(5);
    }
    scrivi_pid();
    int manager=fork();
    if(manager==0){
        //printf("Hey sono il manager il cui pid è %d\n",getpid());
        return logica_manager(n);
    }
    else{
        //printf("Il padre aspetta e ha il pid %d\n",getpid());
        while(wait(NULL)>0);
    }
    return 0;
}