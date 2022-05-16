#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void scriviIlPID(char *file){
    FILE *fpt=fopen(file,"a");
    int pid=getpid();
    fprintf(fpt,"%d\n",pid);
    fclose(fpt);
}

int main(int argc,char **argv){
    if(argc!=3){
        exit(3);
    }
    int numero=atoi(argv[2]);
    if(numero<1 || numero>10){
        printf("Numero non compreso tra 1 e 10\n");
        exit(4);
    }
    int fd=open(argv[1],O_CREAT|O_EXCL,777);
    if(fd<0){
        printf("Impossibile aprire il file\n");
        exit(5);
    }
    close(fd);
    scriviIlPID(argv[2]);
    return 0;
}