#include<stdio.h>  //bi.c
#include<unistd.h>
#include<sys/wait.h>
#define READ 0
#define WRITE 1

int main(){
    int pipe1[2],pipe2[2];
    char buffer[50];
    pipe(pipe1);
    pipe(pipe2);
    int p2= !fork();
    if(p2){
        close(pipe1[WRITE]);
        close(pipe2[READ]);
        int r=read(pipe1[READ],&buffer,50);
        close(pipe1[READ]);
        printf("P2 ha ricevuto: %s\n",buffer);
        write(pipe2[WRITE],"Messaggio da p2",16); //scrive sulla pipe
        close(pipe2[WRITE]);
    }
    else{
        close(pipe1[READ]);
        close(pipe2[WRITE]);
        write(pipe1[WRITE],"Messaggio da p1",16);
        close(pipe1[WRITE]);
        int r=read(pipe2[READ],&buffer,50);
        close(pipe2[READ]);
        printf("P1 ha ricevuto: %s\n",buffer);
    }
    while (wait(NULL)>0);
    return 0;
}