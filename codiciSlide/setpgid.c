#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

//Di questo esempio non ho capito un cazzo crea troppi filgi a cazzo di cane

int main(){
    int figlio=!fork(); //nuovo figlio, ma la variabile filgio avrà valore negato
    printf("PID: %d PPID: %d GID: %d\n",getpid(),getppid(),getpgid(0));
    if(figlio){
        figlio=!fork();//Altro figlio
        if(!figlio){
            setpgid(0,0);//lo fa diventare group leader
        }
        sleep(1);
        fork();//altro figlio
        printf("PID: %d PPID: %d GID: %d\n",getpid(),getppid(),getpgid(0));
    }
    while (wait(NULL)>0);
    return 0;
}