#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    char * pathFifo="/tmp/fifo1";
    mkfifo(pathFifo,S_IRUSR|S_IWUSR); //Crea la pipe se questa non esiste
    perror("Creato?.....capiamo\n");
    if(fork()==0){ //Parte il figlio
        open(pathFifo,O_RDONLY); //Apertura pipe in lettura
        printf("Pipe FIFO aperta in lettura\n");
    }
    else{
        sleep(1);
        open(pathFifo,O_WRONLY); //Apertura Pipe in scrittura
        printf("Pipe FIFO aperta in scrittura\n");
    }
}