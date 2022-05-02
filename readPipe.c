#include <stdio.h> //readPipe.c
#include <unistd.h>

int main(){
    int vet[2];
    char buffer[50];
    int esito=pipe(vet);
    if(esito ==0){
        write(vet[1],"scrivendo",10);
        int r=read(vet[0],&buffer,50);
        printf("Ultima cosa letta %d, ricevuto: %s\n",r,buffer);
        close(vet[1]);
        r=read(vet[0],&buffer,50);
        printf("Ultima cosa letta %d, ricevuto: %s\n",r,buffer);
    }
}