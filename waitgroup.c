#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int gruppo1=fork();
    int gruppo2;
    if(gruppo1==0){ //Entra se è il primo figlio
        setpgid(0,getpid()); //Diventa il leader del gruppo
        fork();fork(); //Genera dei figli
        sleep(4);
        return 0;
    }
    else{
        gruppo2=fork();
        if(gruppo2==0){ //Entra il secondo figlio
            setpgid(0,getpid()); //Diventa il leader del gruppo
            fork();fork(); //Genera i figli
            sleep(4);
            return 0;
        }
    }
    sleep(1);
    while(waitpid(-gruppo1,NULL,0)>0);
    printf("Figli nel gruppo %d terminati\n",gruppo1);
    while(waitpid(-gruppo2,NULL,0)>0);
    printf("Figli nel gruppo %d terminati\n",gruppo2);
}