#include <unistd.h> //writePipe.c
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

extern int errno;

void handler(int signo){
    printf("SIGPIPE ricevuto\n");
    perror("Error");
    exit(errno);
}

int main(){
    signal(SIGPIPE,handler);
    int vet[2];
    char buffer[50];
    int esitop=pipe(vet); //create un unnamed pipe
    close(vet[0]);
    printf("Sto cercando di scrivere\n");
    write(vet[1],"scrivendo",10);
    printf("Ho scritto qualcosa\n");
}