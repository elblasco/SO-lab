#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

short counter=2;

void mioHandler(int numeroSegnale){
    printf("ALARM\n");
    counter++;
}

int main(){
    signal(SIGALRM,mioHandler);
    while(counter>=0){
        alarm(5); //Set alrm in 5 seconds
        printf("secondi rimanenti dalla precedente allarme %d\n",alarm(2));
    }
    return 0;
}