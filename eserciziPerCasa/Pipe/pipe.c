#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAXARG 3
#define READ 0
#define WRITE 1

int master[2],slave[2];

int main(){
    char messaggio[256];
    pipe(master);
    pipe(slave);
    int figlio=fork();
    if(figlio==0){
        while(strcmp(messaggio,"EOF")!=0){
            read(master[READ],&messaggio,256);
            printf("Lo slave ha ricevuto %s\n",messaggio);
            scanf("%s",messaggio);
            write(slave[WRITE],messaggio,256);
        }
    }
    else if(figlio>0){
        write(master[WRITE],"Inizio",6);
        while(strcmp(messaggio,"EOF")!=0){
            read(slave[READ],&messaggio,256);
            printf("Il master ha ricevuto %s\n",messaggio);
            scanf("%s",messaggio);
            write(master[WRITE],messaggio,256);
        }
    }
    else{
        fprintf(stderr,"Figlio non creato\n");
    }
    return 0;
}