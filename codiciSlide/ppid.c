#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(){
    printf("$$ = ");
    fflush(stdout);
    system("echo $$");
    printf("PID:%d  PPID:%d\n",getpid(),getppid());
}