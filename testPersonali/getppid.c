#include<stdio.h>
#include<unistd.h>

int main(){
    fork();
    printf("Il PID del padre è %d\nMentre il mio è %d\n",getppid(),getpid());
    return 0;
}
/*
* Il PID viene modificato, il padre del processo padre è il PID della shell che si sta usando
*/