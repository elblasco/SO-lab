#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void scriviIlPID(FILE *file){
    int pid=getpid();
    fprintf(file,"%d\n",pid);
    fflush(file);
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
    FILE *file=fopen(argv[1],"r");
    if(file!=NULL){
        printf("Il file esite già\n");
        exit(5);
    }
    file=fopen(argv[1],"a");
    scriviIlPID(file);
    while(numero>0){
        int figlio=fork();
        if(getpid()==0){
            scriviIlPID(file);
        }
        printf("Sono il figlio %d\n",numero);
        numero--;
    }
    fclose(file);
    return 0;
}