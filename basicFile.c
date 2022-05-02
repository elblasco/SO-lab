#include <stdio.h>
#include <stdlib.h>
#define N 10

int main(int argc,char* argv[]){
    FILE *ptr; //Declaration of the file stream
    ptr=fopen("sebastiani.txt","r"); //Opening of the stream
    int lunghezzaRiga=atoi(argv[1]);
    char* riga=malloc(lunghezzaRiga*sizeof(*riga));
    while(!feof(ptr)){
        if(fscanf(ptr,"%s",riga)>0){
            printf("%s\n",riga);
        }
    }
    printf("Fine del file\n");
    fclose(ptr); //Close the file stream
    return 0;
}
