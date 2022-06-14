#include <stdio.h>  //redirect.c
#include <unistd.h>
#define READ 0
#define WRITE 1

int main(int argc, char *argv[]){
    int vet[2];
    pipe(vet);
    if(fork()!=0){
        close(vet[READ]);
        dup2(vet[WRITE],1);
        close(vet[WRITE]);
        execlp(argv[1],argv[1],NULL);
        perror("Connesso");
    }
    else{
        close(vet[WRITE]);
        dup2(vet[READ],0);
        close(vet[READ]);
        execlp(argv[2],argv[2],NULL);
        perror("Connesso");
    }
    return 0;
}