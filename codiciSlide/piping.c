#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

/*
Realizzare un tool che esegua due comandi (con possibili argomenti) “in
piping” avendo un primo parametro “token” da usare come separatore
*/

#define READ 0
#define WRITE 1
#define MAX 255

int main(int argc,const char **argv){

    if(argc<5){
        fprintf(stderr,"Numero di argomenti troppo basso\n");
        exit(-1);
    }

    char * separatore=(char *)malloc(strlen(argv[1])*sizeof(char));
    strncpy(separatore, argv[1], strlen(argv[1]));
    separatore[strlen(argv[1])]='\0';
    char *comando1[MAX],*comando2[MAX];
    int trovato=0;
    int fd[2],indexArgomenti=2,indexComandi=0;

    for(;indexArgomenti<argc;++indexArgomenti){
        if(strcmp(separatore,argv[indexArgomenti])==0){
            trovato++;
        }
        else if(indexArgomenti==argc-1 && strcmp(argv[indexArgomenti],separatore)!=0 && trovato==0){
            exit(-1);
        }
    }

    indexArgomenti=2;

    for(;indexArgomenti <argc && strcmp(argv[indexArgomenti],separatore)!=0 ; indexArgomenti++,indexComandi++){
        comando1[indexComandi]=(char *)malloc(strlen(argv[indexArgomenti])*sizeof(char));
        strncpy(comando1[indexComandi],argv[indexArgomenti],strlen(argv[indexArgomenti]));
        comando1[indexComandi][strlen(argv[indexArgomenti])]='\0';
    }

    comando1[indexComandi]=NULL;

    indexComandi=0;

    indexArgomenti++;

    for(;indexArgomenti<argc && strcmp(argv[indexArgomenti],separatore)!=0;++indexArgomenti,++indexComandi){
        comando2[indexComandi]=(char *)malloc(strlen(argv[indexArgomenti])*sizeof(char));
        strncpy(comando2[indexComandi],argv[indexArgomenti],strlen(argv[indexArgomenti]));
        comando2[indexComandi][strlen(argv[indexArgomenti])]='\0';
    }

    free(separatore);
    comando2[indexComandi]=NULL;

    pipe(fd);
    int figlio=fork();
    if(figlio>0){ //Qua entra il padre scrittore
        close(fd[READ]);
        dup2(fd[WRITE],1);
        close(fd[WRITE]);
        execle(comando1[0], (char *) comando1);
        fprintf(stderr,"Errore nel'esecuzione del primo programma\n");
    }
    else{ ///Qua entra il figlio lettore
        close(fd[WRITE]);
        dup2(fd[READ],0);
        close(fd[READ]);
        execle(comando2[0],(char *) comando2);
        fprintf(stderr,"Errore nel'esecuzione del secondo programma\n");
    }

    //Deallocazione delle matrici

    for(int i=0;comando1[i]!=NULL;++i){
        free(comando1[i]);
    }

    for(int i=0;comando2[i]!=NULL;++i){
        free(comando2[i]);
    }
    return 0;
}