#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>

struct buffer{
    long mtype;
    char mtext[100];
} msgp,msgp2;

int main(){
    long tipo=20;
    msgp.mtype=tipo;
    strcpy(msgp.mtext,"Devo dire che sono proprio bello");
    key_t chiaveCoda1=ftok("/tmp/unique",1);
    int idCoda=msgget(chiaveCoda1,0777|IPC_CREAT);
    int esito=msgsnd(idCoda,&msgp,sizeof(msgp.mtext),0);
    printf("Il messaggio è stato mandato con esito %d\n",esito);
    esito=msgrcv(idCoda,&msgp2,sizeof(msgp2.mtext),tipo,0);
    printf("Il messaggio è stato letto con esito %d\n",esito);
    printf("L'effetivo messaggio ricevuto è %s\n",msgp2.mtext);
    return 0;
}
