#include <signal.h>
#include <stdio.h>

void mioHandler(int numeroSegnale){}

int main(){
    printf("DFL: %p\n",signal(SIGINT,SIG_IGN));
    printf("IGN: %p\n",signal(SIGINT,mioHandler));
    printf("Custom: %p==%p\n",signal(SIGINT,SIG_DFL),mioHandler);
    return 0;
}