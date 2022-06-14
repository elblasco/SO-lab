#include<stdio.h>
#include<unistd.h>

int main(){
    int i=23;
    fork();
    fork();
    printf("Il processo %d stampa %d\n",getpid(),i);
}

/*
* Tra i processi frokati sono condivise molte informazioni,
* una delle informazioni modificate è il pid e il ppid(parent pid)
*/