#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
    if(argc<3){
        fprintf(stderr,"Troppi pochi argomenti\n");
        exit(-1);
    }
    int nFigli=argc-2;
    printf("%d\n",nFigli);
    return 0;
}