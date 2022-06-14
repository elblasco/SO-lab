#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    remove("/tmp/unique"); //Rimuove il file
    key_t chiaveCoda1=ftok("/tmp/unique",1); //Questa istruzione non funziona perchè il percorso non esiste
    creat("/tmp/unique",0777);
    chiaveCoda1=ftok("/tmp/unique",1);
    int idCoda=msgget(chiaveCoda1,0777|IPC_CREAT);
    printf("La coda %d ha chiave %d\n",idCoda,chiaveCoda1);
    idCoda=msgget(chiaveCoda1,0777);
    msgctl(chiaveCoda1,IPC_RMID,NULL); //Fa un fail perchè devo passare l'id
    msgctl(idCoda,IPC_RMID,NULL); //Rimuove la coda partendo dal suo id
    idCoda=msgget(chiaveCoda1,0777);
    printf("La coda non esiste quindi il return è: %d\n",idCoda);
    idCoda=msgget(chiaveCoda1,0777|IPC_CREAT);
    printf("La coda non esiste ma viene creata quindi il return è: %d\n",idCoda);
    idCoda=msgget(chiaveCoda1,0777|IPC_CREAT|IPC_EXCL);
    printf("La coda esiste già quindi il parametro IPC_EXCL resituisce: %d\n",idCoda);
    return 0;
}