#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

#define MAXARG 3

int main(int argc,char ** argv){
    if(argc!=MAXARG){
        fprintf(stderr,"Numero di argomenti errato\n");
        exit(1);
    }
    int figlio1=fork();
    if(figlio1==0){
        execl(argv[1],NULL);
    }
    else if(figlio1>0){
        while(wait(NULL)>0);
        int figlio2=fork();
        if(figlio2==0){
            execl(argv[2],NULL);
        }
        else if(figlio2>0){
            while(wait(NULL)>0);
        }
        else{
            fprintf(stderr,"Secondo filgio non creato\n");
            exit(3);
        }
    }
    else{
        fprintf(stderr,"Primo figlio non creato\n");
        exit(2);
    }
    return 0;
}