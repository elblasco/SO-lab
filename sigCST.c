#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handlerMio(int numeroSegnale){
    printf("CTRL+Z\n");
    exit(2);
}

int main(){
    signal(SIGTSTP,handlerMio);
    while(1);
}