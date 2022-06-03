#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 

#define MAXARG 3

FILE* file_out;

bool file_exists(const char* path){
    FILE* tmp=fopen(path,"r");
    bool trovato=false;
    if(tmp!=NULL){
        trovato=true;
        fclose(tmp);
    }
    return trovato;
}

void stampa_pid(){
    fprintf(file_out,"%d\n",getpid());
}

void fai_il_manager(int n_filgi){
    stampa_pid();
    for(int i=0;i<n_filgi;++i){
        int n_esimo_figlio=fork();
        if(n_esimo_figlio==0){
            stampa_pid();
            pause();
        }
        else{

        }
    }
}

int main(int argc, char ** argv){
    if(argc!=MAXARG){
        perror("Troppi argomenti");
        exit(3);
    }
    if(atoi(argv[2])<1 || atoi(argv[2])>10){
        perror("n non compreso tra 1 e 10");
        exit(4);
    }
    
    if(file_exists(argv[1])){
        perror("Errore nell'apertura del file");
        exit(5);
    }
    file_out=fopen(argv[1],"w");
    if(file_out==NULL){
        perror("Errore nell'apertura del file");
        exit(5);
    }
    stampa_pid();
    int manager=fork();
    if(manager==0){
        fai_il_manager(atoi(argv[2]));
    }
    else{

    }
    return 0;
}