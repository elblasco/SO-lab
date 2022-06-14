#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

#define MAXARG 3

FILE *ptr;

int main(int argc,char ** argv){
    if(argc!=MAXARG){
        fprintf(stderr,"Numero di argomenti errato\n");
        exit(1);
    }
    int figlio1=fork();
    if(figlio1==0){
        ptr= fopen("output.txt","w");
        int fd=fileno(ptr);
        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDERR_FILENO);
        execl(argv[1],NULL);
        fclose(ptr);
    }
    else if(figlio1>0){
        while(wait(NULL)>0);
        int figlio2=fork();
        if(figlio2==0){
            ptr= fopen("output.txt","a");
            int fd=fileno(ptr);
            dup2(fd,STDOUT_FILENO);
            dup2(fd,STDERR_FILENO);
            execl(argv[2],NULL);
            fclose(ptr);
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