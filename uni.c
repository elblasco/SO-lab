#include<stdio.h> //uni.c
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int vet[2];
    char buffer[50];
    pipe(vet);
    int p2= !fork();
    if(p2){
        close(vet[1]);
        int r=read(vet[0],&buffer,50); //read from the pipe
        close(vet[0]);
        printf("Buffer: %s\n",buffer);
    }
    else{
        close(vet[0]);
        write(vet[1],"scrivendo",10);
        close(vet[1]); 
    }
    while(wait(NULL)>0);
    return 0;
}