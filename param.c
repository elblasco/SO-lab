#include <signal.h>
#include <stdio.h>

void mioHandler(int numeroSegnale){
    if(numeroSegnale==SIGINT){
        printf("CTRL+C\n");
    }
    else if (numeroSegnale==SIGTSTP) {
        printf("CRTL+Z\n");
    }
}

int main(){
    signal(SIGINT,mioHandler);
    signal(SIGTSTP,mioHandler);
    while(1);
}