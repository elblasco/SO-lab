#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>

int main(){
    key_t chiaveCoda1=ftok("/tmp/unique",1);
    int idCoda=msgget(chiaveCoda1,0777|IPC_CREAT|IPC_EXCL);
    perror("Errore: "); //Le code sono persistenti quindi le devo deallocare a fine programma
}