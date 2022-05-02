#include <stdlib.h>
#include <stdio.h>
#define N 23

int main(){
    FILE *file;
    file=fopen("sebastiani.txt","w+");
    fprintf(file,"Nuova riga da scrivere");
    fprintf(file,"Ciao mi chiamo Alessio");
    rewind(file); //restore the pointer to the beginning of the file
    char riga[N],indexChar;
    fgets(riga,N,file); //Store the next N-1 char from file to riga
    printf("%s\n",riga);
    do {
        indexChar=fgetc(file);
        if(indexChar!=EOF && indexChar!='\n'){
            printf("%c",indexChar);
        }
    }while (indexChar!=EOF);
    printf("\n");
    fclose(file);
    return 0;
}