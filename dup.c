#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    char buffer[255];
    int file=open("sebastiani.txt",O_RDWR); //check if the file exists
    read(file,buffer,255);
    printf("Vecchio contenuto: %s\n",buffer);
    int copia=dup(file); //Create copy of the fd
    int nuovoFile; //The int where i will store the fd
    dup2(copia,nuovoFile); //a function that copy copia to nuovoFile (close nuovoFile if it is opened)
    lseek(copia,0,SEEK_SET);
    write(nuovoFile,"Sono le 9 e tutto va bene",strlen("Sono le 9 e tutto va bene"));
    return 0;
}