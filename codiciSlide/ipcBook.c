#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct book{
    char titolo[10];
    char descrizione[200];
    short capitoli;
}Book;

struct buffer{
    long mtype;
    Book mtext;
}msgp_sent,msgp_recvived;

int main(){
    long tipo=20;
    msgp_sent.mtype=tipo;
    strcpy(msgp_sent.mtext.titolo,"Titolo");
    strcpy(msgp_sent.mtext.descrizione,"Breve descrizione");
    msgp_sent.mtext.capitoli=18;
    remove("/tmp/unique");
    key_t chiaveCoda1=ftok("/tmp/unique",1);
    int idCoda=msgget(chiaveCoda1,0777|IPC_CREAT);
    int esito=msgsnd(idCoda,&msgp_sent,sizeof(msgp_sent.mtext),0);
    esito=msgrcv(idCoda,&msgp_recvived,sizeof(msgp_recvived.mtext),tipo,0);
    printf("Ho ricevuto %s %s %d\n",
        msgp_recvived.mtext.titolo,msgp_recvived.mtext.descrizione,msgp_recvived.mtext.capitoli);
    return 0;
}
